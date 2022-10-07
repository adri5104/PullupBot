function Pulseq=moverDelta_art(qi,qf,tf)
pi= fpkDelta(qi(1),qi(2),qi(3));
pf= fpkDelta(qf(1),qf(2),qf(3));
pi(4)=qi(4);
difx =difposx(pi,pf);
 Tray_art=[];
if difx > pf(1) %Dentrodel espacio de trabajo delta
   
Tray_art=genTray_art(qi,qf,tf);
else
    Tray_art=[Tray_art;qi];
end

Pulseq=mat_pulsos(Tray_art); 

end
