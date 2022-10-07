%% CONSTANTES DEL ROBOT 
    %datos de la base del robot
    sB=185;% lado base superior
    uB=sB/(2*sin(pi/3))
    wB=sB/(2*tan(pi/3))
    
    %datos de el TCP del robot
    sP=60;%lado base inferior
    uP=sP/(2*sin(pi/3))
    wP=sP/(2*tan(pi/3))
    
    %datos de las articulaciones
    L=151; %largo biceps
    l=285; %largo varillas
    A=45; %dist entre varillas (juntas esfericas)
    
    %espacio de trabajo
    XMAX=500;
    XMIN=-505;
    YMAX=120;
    YMIN=-120;
    ZMAX=0;
    ZMIN=-350;
    XDELTA=230;
    
    %STEPPER
    StepsPerRevolution=5;
    XSTEPMAX=450;
    XSTEPMIN=-460;
    
    %espacio de trabajo espacio de las articulaciones
    QMAX=110;%angulos positivos hacia abajo
    QMIN=-35;%angulos negativos hacia arriba
 %%  SP auxiliares mas que na 
 x=0; y=0; z=-300;
 %% FUNCION QUE DESARROLLA LA CINEMATICA INVERSA
    function sp=ipkDelta(x,y,z)

    a=wB-uP;
    b=(sP/2)-(sqrt(3)/2)*wB;
    c=wP-0.5*wB;
    
    E1=2*L*(y+a);
    F1=2*z*L;
    G1=x^2+y^2+z^2+a^2+L^2+2*y*a-l^2;

    E2=-L*(sqrt(3)*(x+b)+y+c);
    F2=2*z*L;
    G2=x^2+y^2+z^2+b^2+c^2+L^2+2*(x*b+y*c)-l^2;

    E3=L*(sqrt(3)*(x-b)-y-c);
    F3=2*z*L;
    G3=x^2+y^2+z^2+b^2+c^2+L^2+2*(-x*b+y*c)-l^2;

    function qf=ti(E,F,G)
    ta=-(F+(sqrt(E^2+F^2-G^2)))/(G-E);
    tb=-(F-(sqrt(E^2+F^2-G^2)))/(G-E);
    qf=ta;
    end

    theta1=2*atan(ti(E1,F1,G1));
    theta2=2*atan(ti(E2,F2,G2));
    theta3=2*atan(ti(E3,F3,G3));
    sp=[theta1*180/pi theta2*180/pi theta3*180/pi]';
    end

 %% GENERADOR DE TRAYECTORIAS (ESPACIO CARTESIANO)
%vectores entrada: pi=[1 2 3]   pf=[11 22 33]   posicion inicial y posicion final 
%intervalo de tiempo tf =1;
function Tray=genTray2(pi,pf,tf) 
    %va a ser 3 (3 coordenadas)
        Tray=[];
        for i=1:3
            a(i)=2*(pi(i)-pf(i))/tf^3;
            b(i)=(-3*a(i)*tf)/2;
            c(i)=0;
            d(i)=pi(i);                %saco    a1 b1 c1  a2 b2 c2  a3 b3 c3
        end
        
        for t=0:0.1:tf  %llega a tf en intervalos de 0.1 tf*10 cálculos
for i=1:3
p(i)=a(i)*t^3 + b(i)*t^2 + c(i)*t + d(i);     %p1 p2 p3 tf*10 veces
end
            Tray=[Tray;p];                      % anade filas x debajo con los nuevos calculos  [ p1 p2 p3 ; p1 p2 p3;...] 
                                                % si tf=1 sera una matriz
                                                % de 11*3 tal que [ 1 2 3
                                                %                   .....
                                                %                   .....
                                                %                   .....
                                                %                 11 22 33]
                                                % filas con puntos rectas
                               
        end
end

%% FUNCION PARA MOVER EL ROBOT
function [Pulse,xs]=moverRobot(pi,pf,tf)
%distx=dist_esptdelta(pf); %dist x es para ver si mov esta dentro del rango del delta de las x 

            %me pregunto si la coordenada x es alcanzable por el delta
            %comparando XDELTA con la dif de posiciones i y f
            difx =difposx(pi,pf);
            if difx < pf(1) %el mov no alcanza a hacerlo con el delta so muevo el stepper hasta pf
            dstep=dist_esptstep(pf);
            ys=pf(2);zs=pf(3);
                if dstep>0 %estoy en el area de trabajo
                    xs=pf(1);
                    
                    %le mando la xs para que se mueva el stepper 
                    
                    %funcion que mande al stepper pps
                else if pf(1)<0    % si no estoy en el area de trabajo muevo al máx de las negativas o las positivas
                        xs=XSTEPMIN;
                        
                        %funcion que mande al stepper xs
                    else xs=XSTEPMAX;
                         
                         %funcion que mande al stepper xs
                    end
                end
                 pi(1)=xs; %mi pos inicial sera donde llegue con el stepper y si no he alcanzado la final tiraré con el delta
            end
           
            %ahora realizo el movimiento con el delta
            Tray=genTray2(pi,pf,tf);
            Pulse=mat_pulsos(Tray);
            
            
end
%% FUNCION PARA TRAY DE PULSOS
function Pulse=mat_pulsos(Tray) 
    Pasos=length(Tray)
        for j=1:Pasos %hace la conversion a thetas segun el numero de filas de la matriz trayectoria
            sp=Tray(j,:);
            x=sp(1);y=sp(2);z=sp(3); %creo vector sp con cartesianas para pasarlas a articulares con la funcion de la cinemática inv
            qf=ipkDelta(x,y,z);
            for k=1:3
                ppf(k)=grad_pulse(qf(k)); %de grados a pulsos por 5.85        
                                            %vector ppf con 3 coordenadas d
                                            %posicion a alcanzar en pulsos
            end
           Pulse=[Pulse;ppf];
        end
end
%% FUNCION QUE CALCULA LA DIST DEL PUNTO AL QUE QUIERO LLEGAR AL LIMITE DEL ESPACIO DE TRABAJO
function d= dist_espt(sp)

if sp(1)>0
d(1)=XMAX-sp(1);
else d(1)=-XMIN+sp(1);
end  

if sp(2)>0
d(2)=YMAX-sp(2);
else d(2)=-YMIN+sp(2);
end  

if sp(3)>0
d(3)=ZMAX-sp(3);
else d(3)=-ZMIN+sp(3);
end 

end
%% FUNCION QUE CALCULA LA DIST (EN X) DEL PUNTO AL QUE QUIERO LLEGAR AL LIMITE DEL ESPACIO DE RABAJO DEL DELTA
function ddelta= dist_esptdelta(sp)
ddelta=XDELTA-abs(sp(1));
end 
%% AL PULSAR BOTON COORDENADAS INTRODUCIDAS ¿ESTOY DENTRO DEL AREA DE TRABAJO?
%dist=dist_espt(sp);
 %if  any(dist<0)    frpintf ('Estas fuera del area de trabajo\n')
 %end
 
 %dq=dist_art(sq);
            %if any((dq)>0)
 %% FUNCION DE PULSOS A GRADOS
    function pulse=grad_pulse(grad)
        pulse=grad*5.85;
    end
 %% FUNCION PARA DIFERENCIA ENTRE POSICION FINAL E INICIAL EN X
 function difx =difposx(pi,pf)
 if pf(1)>0 difx = pi(4)+XDELTA;
 else difx = pi(4)-XDELTA;
     end 
 end
%% FUNCION QUE CALCULA LA DIST DEL PUNTO AL QUE QUIERO LLEGAR AL LIMITE DEL ESPACIO DE TRABAJO DEL STEPPER
function d= dist_esptstep(pf)
if pf(1)>0
d=XMAX-pf(1);
else d=-XMIN+pf(1);
end 
end


%% GENERADOR DE TRAYECTORIAS (ESPACIO DE LAS ARTICULACIONES)
function Tray_art=genTray_art(qi,qf,tf)
    N=length(qi);%va a ser 3 coordenadas
    Tray_art=[];
        for i=1:N
        a(i)=2*(qi(i)-qf(i))/tf^3;
        b(i)=(-3*a(i)*tf)/2;
        c(i)=0;
        d(i)=qi(i);
        end
        
    for t=0:0.1:tf %llega a tf en intervalos de 0.1 tf*10 cálculos
        for i=1:N
        q(i)=a(i)*t^3 + b(i)*t^2 + c(i)*t + d(i); %q1 q2 q3 tf*10 veces
        end
    Tray_art=[Tray_art;q];
    end
end
%% FUNCION PARA MOVER EL DELTA PASANDO COORDENADAS ARTICUALARES
    function moverDelta_art(Tray_art,distStep)
    Pasos=length(Tray_art)
    dstep=dist_esptstep([distStep,0, 0 ]);
          
                if dstep>0 %estoy en el area de trabajo
                    xs=distStep;
                    
                    %le mando la xs para que se mueva el stepper 
                    
                    %funcion que mande al stepper pps
                else if pf(1)<0    % si no estoy en el area de trabajo muevo al máx de las negativas o las positivas
                        xs=XSTEPMIN;
                        
                        %funcion que mande al stepper xs
                    else xs=XSTEPMAX;
                         
                         %funcion que mande al stepper xs
                    end
                end
                 
    
        for j=1:Pasos %mueve el robot hacia arriba o hacia abajo en función de dq
        sq=Tray_art(j,:);
            for k=1:3
            ppq(k)=grad_pulse(qf(k)); %de grados a pulsos por 5.85
            %vector ppq con 3 coordenadas d
            %posicion a alcanzar en pulsos
            %funcion para pasar este vector ppq de info de pulsos al
            %arduino
            end
            
    pause(0.01);
        end
    end
%% FUNCION QUE CALCULA LA DIST DEL PUNTO AL QUE QUIERO LLEGAR AL LIMITE ANGULAR DEL ESPACIO DE TRABAJO
    function dq= dist_art(qf)
    
        if qf(1)>0
        dq(1)=QMAX-qf(1);
        else dq(1)=-QMIN+qf(1);
        end
        
        if qf(2)>0
        dq(2)=QMAX-qf(2);
        else dq(2)=-QMIN+qf(2);
        end
        
        if qf(3)>0
        dq(3)=QMAX-qf(3);
        else dq(3)=-QMIN+qf(3);
        end
        
    end

