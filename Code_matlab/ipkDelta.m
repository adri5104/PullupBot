%% FUNCION QUE DESARROLLA LA CINEMÁTICA INVERSA


    function sp=ipkDelta(x,y,z)
    %Datos base superior robot
    sB=185;
    uB=sB/(2*sin(pi/3));
    wB=sB/(2*tan(pi/3));
    
    %datos base inferior robot
    sP=60;
    uP=sP/(2*sin(pi/3));
    wP=sP/(2*tan(pi/3));
    
    %datos de las articulaciones
    L=151;
    l=285;
    A=45;
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