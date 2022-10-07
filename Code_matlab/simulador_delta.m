
function delta
%% INICIALIZACIÓN
    clear;
    clf;
    clc;
%% ESPACIO GRÁFICO
    v = 1500;
    axis([-400 400 -400 400 -650 50]);
    figure(gcf);
    xlabel('X');
    ylabel('Y');
    zlabel('Z');
    set(gca, 'drawmode', 'fast');
    view(0,0)
    grid;
%% CONSTANTES DEL ROBOT
    %datos de la base del robot
    sB=185;%567
    uB=sB/(2*sin(pi/3))
    wB=sB/(2*tan(pi/3))
    %datos de el TCP del robot
    sP=60;
    uP=sP/(2*sin(pi/3))
    wP=sP/(2*tan(pi/3))
    %datos de las articulaciones
    L=151;%524
    l=285;%1244
    A=45;%131;
    %Colores
    C= [0 0 1];
    C2=[1 0 0];
%% SP
x=0; y=0;
z=-300;
%% FUNCION QUE DESARROLLA LA CINEMÁTICA INVERSA
    function sp=ipkDelta(x,y,z)
        a=wB-uP;
        b=(sP/2)-(sqrt(3)/2)*wB;
        c=wP-0.5*wB;
E1=2*L*(y+a);
F1=2*z*L; G1=x^2+y^2+z^2+a^2+L^2+2*y*a-l^2;
E2=-L*(sqrt(3)*(x+b)+y+c);
F2=2*z*L; G2=x^2+y^2+z^2+b^2+c^2+L^2+2*(x*b+y*c)-l^2;
E3=L*(sqrt(3)*(x-b)-y-c);
F3=2*z*L; G3=x^2+y^2+z^2+b^2+c^2+L^2+2*(-x*b+y*c)-l^2;
function qf=ti(E,F,G)
    ta=-(F+(sqrt(E^2+F^2-G^2)))/(G-E); 
    tb=-(F-(sqrt(E^2+F^2-G^2)))/(G-E); qf=ta;
end
theta1=2*atan(ti(E1,F1,G1)); theta2=2*atan(ti(E2,F2,G2));
theta3=2*atan(ti(E3,F3,G3));
sp=[theta1*180/pi theta2*180/pi theta3*180/pi]';
    end



%% PUNTOS SUPERIORES DEL ROBOT
    %PUNTOS DE LA BASE
    P1B=[eye(3) [-sB/2;-wB;0];0 0 0 1];
    P2B=[eye(3) [sB/2;-wB;0];0 0 0 1];
    P3B=[eye(3) [0;uB;0];0 0 0 1];
    %PUNTOS DE LOS MOTORES
B1=[eye(3) [0;-wB;0];0 0 0 1];
B2=[eye(3) [wB*sin(pi/3);wB*cos(pi/3);0];0 0 0 1]; 
B3=[eye(3) [-wB*sin(pi/3);wB*cos(pi/3);0];0 0 0 1];
%%  OBTENCIÓN DE ÁNGULOS MEDIANTE IPK
x=0;y=0;z=-200;
qi=ipkDelta(x,y,z) 
lDelta=dibujaRobot(qi);
pause(1); 
Tr=genTray2([x,y,z],[124,-75,-350],2); 
tic
moverRobot(Tr,lDelta); 
toc

Tr=genTray2([x,y,z],[0,-75,-200],2); 
moverRobot(Tr,lDelta); 
Tr=genTray2([x,y,z],[-124,-75,-350],2); 
moverRobot(Tr,lDelta);


%% FUNCIÓN QUE OBTIENE LOS PUNTOS INFERIORES DEL ROBOT
function lDelta=dibujaRobot(q) 
        THETA1=q(1);
        THETA2=q(2);
        THETA3=q(3);
%PUNTO A1
A1=B1;
A1=rot(A1,'X',-90);
A1=rot(A1,'Y',90);
A1=rot(A1,'Z',THETA1);
A1=tra(A1,[L 0 0]);
%PUNTO A2
A2=B2;
A2=rot(A2,'X',-90);
A2=rot(A2,'Y',-30);
A2=rot(A2,'Z',THETA2);
A2=tra(A2,[L 0 0]);
%PUNTO A3
A3=B3;
A3=rot(A3,'X',-90);
A3=rot(A3,'Y',-150);
A3=rot(A3,'Z',THETA3);
A3=tra(A3,[L 0 0]);
%PUNTOS DEL TCP
P1=[eye(3) [x;y-uP;z];0 0 0 1];
P2=[eye(3) [x+0.5*sP;y+wP;z];0 0 0 1];
P3=[eye(3) [x-0.5*sP;y+wP;z];0 0 0 1];
%PUNTOS PARALELOGRAMO A1
A1A=tra(A1,[0 0 -A/2]);
A1B=tra(A1,[0 0 +A/2]);
%PUNTOS PARALELOGRAMO A2
A2A=tra(A2,[0 0 -A/2]);
A2B=tra(A2,[0 0 +A/2]);
%PUNTOS PARALELOGRAMO A3
A3A=tra(A3,[0 0 -A/2]);
A3B=tra(A3,[0 0 +A/2]);
%PUNTOS PARALELOGRAMO l1
l1A=tra(P1,[-A/2 0 0]);
l1B=tra(P1,[+A/2 0 0]);
%PUNTOS PARALELOGRAMO l2 
l2A=tra(P2,[(cos(pi/3))*(A/2) -sin(pi/3)*(A/2) 0]);
l2B=tra(P2,[(-cos(pi/3))*(A/2) sin(pi/3)*(A/2) 0]);
%PUNTOS PARALELOGRAMO l3
l3A=tra(P3,[(cos(pi/3))*(A/2) sin(pi/3)*(A/2) 0]); l3B=tra(P3,[(-cos(pi/3))*(A/2) -sin(pi/3)*(A/2) 0]);
%***************CREACIÓN DE LINEAS************************ 
%LINEAS DE LA BASE
lbase1=crealin(P1B,P2B,C); 
lbase2=crealin(P2B,P3B,C); 
lbase3=crealin(P3B,P1B,C); 
lbase=[lbase1,lbase2,lbase3]; 
%LINEAS DEL TCP 
ltcp1=crealin(P1,P2,C2); 
ltcp2=crealin(P2,P3,C2); 
ltcp3=crealin(P3,P1,C2); 
ltcp=[ltcp1,ltcp2,ltcp3];
%LINEAS DE ARTICULACIONES SUPERIORES 
las1=crealin(A1,B1,C); 
las2=crealin(A2,B2,C); 
las3=crealin(A3,B3,C); 
las=[las1,las2,las3];
%LINEAS DE ARTICULACIONES INFERIORES
lai1=crealin(A1A,l1A,C); 
lai2=crealin(A1B,l1B,C); 
lai3=crealin(A2A,l2A,C); 
lai4=crealin(A2B,l2B,C); 
lai5=crealin(A3A,l3A,C); 
lai6=crealin(A3B,l3B,C); 
lai=[lai1,lai2,lai3,lai4,lai5,lai6];
%LINEAS DE PARALELOGRAMOS SUPERIORES 
lps1=crealin(A1A,A1B,C); 
lps2=crealin(A2A,A2B,C); 
lps3=crealin(A3A,A3B,C); 
lps=[lps1,lps2,lps3];
%LINEAS DE PARALELOGRAMOS INFERIORES
lpi1=crealin(l1A,l1B,C);
lpi2=crealin(l2A,l2B,C);
lpi3=crealin(l3A,l3B,C); 
lpi=[lpi1,lpi2,lpi3];
lDelta=[lbase,ltcp,las,lai,lps,lpi];
end
%%  FUNCIÓN QUE MODIFICA EL ROBOT
function modificaRobot(q,lineas)
        THETA1=q(1);
        THETA2=q(2);
        THETA3=q(3);
%PUNTO A1
A1=B1;
A1=rot(A1,'X',-90);
A1=rot(A1,'Y',90);
A1=rot(A1,'Z',THETA1);
A1=tra(A1,[L 0 0]);
%PUNTO A2
A2=B2;
A2=rot(A2,'X',-90);
A2=rot(A2,'Y',-30);
A2=rot(A2,'Z',THETA2);
A2=tra(A2,[L 0 0]);
%PUNTO A3
A3=B3;
A3=rot(A3,'X',-90); 
A3=rot(A3,'Y',-150);
A3=rot(A3,'Z',THETA3);
A3=tra(A3,[L 0 0]);
%PUNTOS DEL TCP
P1=[eye(3) [x;y-uP;z];0 0 0 1];
P2=[eye(3) [x+0.5*sP;y+wP;z];0 0 0 1]; 
P3=[eye(3) [x-0.5*sP;y+wP;z];0 0 0 1]; 
%PUNTOS PARALELOGRAMO A1
A1A=tra(A1,[0 0 -A/2]);
A1B=tra(A1,[0 0 +A/2]);
%PUNTOS PARALELOGRAMO A2
A2A=tra(A2,[0 0 -A/2]);
A2B=tra(A2,[0 0 +A/2]);
%PUNTOS PARALELOGRAMO A3
A3A=tra(A3,[0 0 -A/2]);
A3B=tra(A3,[0 0 +A/2]);
%PUNTOS PARALELOGRAMO l1
l1A=tra(P1,[-A/2 0 0]);
l1B=tra(P1,[+A/2 0 0]);
%PUNTOS PARALELOGRAMO l2 
l2A=tra(P2,[(cos(pi/3))*(A/2) -sin(pi/3)*(A/2) 0]); 
l2B=tra(P2,[(-cos(pi/3))*(A/2) sin(pi/3)*(A/2) 0]);
%PUNTOS PARALELOGRAMO l3
l3A=tra(P3,[(cos(pi/3))*(A/2) sin(pi/3)*(A/2) 0]);
l3B=tra(P3,[(-cos(pi/3))*(A/2) -sin(pi/3)*(A/2) 0]);
%LINEAS TCP
modlin(lineas(4),P1,P2); 
modlin(lineas(5),P2,P3); 
modlin(lineas(6),P3,P1);
%LINEAS ARTICULACIONES SUPERIORES 
modlin(lineas(7),A1,B1);
modlin(lineas(8),A2,B2); 
modlin(lineas(9),A3,B3);
%LINEAS ARTICULACIONES INFERIORES
modlin(lineas(10),A1A,l1A); modlin(lineas(11),A1B,l1B); 
modlin(lineas(12),A2A,l2A); modlin(lineas(13),A2B,l2B);
modlin(lineas(14),A3A,l3A); modlin(lineas(15),A3B,l3B); 
%LINEAS PARALELOGRAMOS SUPERIORES
modlin(lineas(16),A1A,A1B);
modlin(lineas(17),A2A,A2B); 
modlin(lineas(18),A3A,A3B); 
%LINEAS PARALELOGRAMOS INFERIORES 
modlin(lineas(19),l1A,l1B);
modlin(lineas(20),l2A,l2B);
modlin(lineas(21),l3A,l3B);
end
%%  FUNCION PARA LA CREACIÓN DE LINEAS

function linea=crealin(P1,P2,color) 
    X=[P1(1,4);P2(1,4)]; 
    Y=[P1(2,4);P2(2,4)]; 
    Z=[P1(3,4);P2(3,4)];
linea=line('xdata',X,'ydata',Y,'zdata',Z,'color',color,'erasemode','xor','linewidth',1.5); 
end
%% FUNCION PARA LA MODIFICACIÓN DE LINEAS
function modlin(linea,P1,P2) 
X=[P1(1,4);P2(1,4)];
Y=[P1(2,4);P2(2,4)];
Z=[P1(3,4);P2(3,4)];
set(linea, 'xdata',X,'ydata',Y,'zdata',Z)
end
%%  FUNCIÓN PARA ROTACIÓN
function matOut=rot(matIn,eje,a) 
    a=(a*pi)/180;

        if(eje=='X')
matOut=matIn*[1 0 0 0;0 cos(a) -sin(a) 0;0 sin(a) cos(a) 0;0 0 0 1];
        end
        if(eje=='Y')
matOut=matIn*[cos(a) 0 sin(a) 0;0 1 0 0;-sin(a) 0 cos(a) 0;0 0 0 1];
        end
        if(eje=='Z')
matOut=matIn*[cos(a) -sin(a) 0 0;sin(a) cos(a) 0 0;0 0 1 0;0 0 0 1];
        end
end
%%  FUNCIÓN PARA TRASLACIÓN
function matOut=tra(matIn,a)
matOut=matIn*[eye(3) [a(1) a(2) a(3)]';0 0 0 1];
end

%% GENERADOR DE TRAYECTORIAS (ESPACIO CARTESIANO)
function Tray=genTray2(pi,pf,tf) %(
    N=length(pi);
        Tray=[];
        for i=1:N
            a(i)=2*(pi(i)-pf(i))/tf^3;
            b(i)=(-3*a(i)*tf)/2;
            c(i)=0;
            d(i)=pi(i);
        end
        
        for t=0:0.1:tf  %tf regula la velocidad y que recorre el espacio en incrementos de 0.1, este valor se puede modificar tb 
            for i=1:N
                p(i)=a(i)*t^3 + b(i)*t^2 + c(i)*t + d(i);
            end
            Tray=[Tray;p];
        end
end 
        
        
 %% GENERADOR DE TRAYECTORIAS (ESPACIO DE LAS ARTICULACIONES)
    function Tray=genTray(qi,qf,tf)
        N=length(qi);
        Tray=[];
        for i=1:N
            a(i)=2*(qi(i)-qf(i))/tf^3;
            b(i)=(-3*a(i)*tf)/2;
            c(i)=0;
            d(i)=qi(i);
        end
        for t=0:0.1:tf
            for i=1:N
                q(i)=a(i)*t^3 + b(i)*t^2 + c(i)*t + d(i);
end
            Tray=[Tray;q];
        end
    end

%%  FUNCION PARA MOVEL EL ROBOT
function moverRobot(Tray,lineas) 
    Pasos=length(Tray)
        for j=1:Pasos
            sp=Tray(j,:);
             x=sp(1);y=sp(2);z=sp(3);
            qf=ipkDelta(x,y,z)
            modificaRobot(qf,lineas);
            pause(0.01);
        end
end
end


%% stepper(shieldObject,portNum,StepsPerRevolution)
function steppperMotor= stepper(StepsPerRevolution)
for j=1:5
stepperMotor.RPM=StepsPerRevolution;
move(stepperMotor,50);
pause(1);
move(stepperMotor,-50);
pause(1);
end %release stepper motor
end



    
    
    
    
    
    
 
    
    
    
    
    
    
    
    
    
    
    
    
    
    
