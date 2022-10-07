%% FUNCION PARA TRAY DE PULSOS
function Pulse=mat_pulsos(Tray) 
    Pasos=length(Tray);
    Pulse=[];
        for j=1:Pasos %hace la conversion a thetas segun el numero de filas de la matriz trayectoria
            sp=Tray(j,:);
            x=sp(1);y=sp(2);z=sp(3); %creo vector sp con cartesianas para pasarlas a articulares con la funcion de la cinemática inv
            qf=ipkDelta(x,y,z);
            
                ppf(1)=qf(1)*5.85;
                ppf(2)=qf(2)*3.036;
                ppf(3)=qf(3)*5.85;
                
               
           Pulse=[Pulse;ppf];
        end
end