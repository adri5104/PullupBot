%% GENERADOR DE TRAYECTORIAS (ESPACIO DE LAS ARTICULACIONES)
function Tray_art=genTray_art(qi,qf,tf)
    
    Tray_art=[];
        for i=1:3
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