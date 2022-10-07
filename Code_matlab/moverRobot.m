%% FUNCION PARA MOVER EL ROBOT
function [Pulse,xs]=moverRobot(pi,pf,tf)

XSTEPMAX=450;
XSTEPMIN=-460;
%distx=dist_esptdelta(pf); %dist x es para ver si mov esta dentro del rango del delta de las x 

            %me pregunto si la coordenada x es alcanzable por el delta
            %comparando XDELTA con la dif de posiciones i y f
            difx =difposx(pi,pf);
            if difx < pf(1) %el mov no alcanza a hacerlo con el delta so muevo el stepper hasta pf
            dstep=dist_etstep(pf);
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
                 %mi pos inicial sera donde llegue con el stepper y si no he alcanzado la final tiraré con el delta
                 pf(1)=pi(1)-xs;
            else xs=pi(4);
            end
           
            %ahora realizo el movimiento con el delta
            Tray=genTray2(pi,pf,tf);
            Pulse=mat_pulsos(Tray);  
            
end