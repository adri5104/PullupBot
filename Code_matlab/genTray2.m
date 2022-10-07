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




        