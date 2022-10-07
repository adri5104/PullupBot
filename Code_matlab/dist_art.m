function dart= dist_art(qi,qf)
    QMAX=110;%angulos positivos hacia abajo
    QMIN=-35;%angulos negativos hacia arriba
    
if qf>0 dart(1)=qi(1)+QMAX-qf(1);
else dart(1)=qi(1)-QMIN+qf(1);
end

if qf>0 dart(2)=qi(2)+QMAX-qf(2);
else dart(2)=qi(2)-QMIN+qf(2);
end

if qf>0 dart(3)=qi(3)+QMAX-qf(3);
else dart(3)=qi(3)-QMIN+qf(3);
end

end 