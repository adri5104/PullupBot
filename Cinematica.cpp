#include "Cinematica.h"

Cinematica::Cinematica(Pullup* unPullup)
{
    myRobot = unPullup;
    sB = 185;
    uB = sB/(2*sin(PI/3));
    wB = sB/(2*tan(PI/3));
    sP=60;
    uP=sP/(2*sin(PI/3));
    wP=sP/(2*tan(PI/3));
    a = wB-uP;
    b = (sP/(2*sin(PI/3)));
    c = wP -0.5*wB;
    L=151;
    l=285;
    A_=45;
}

float Cinematica::ti(float E, float F, float G )
{
    return (-(F+(sqrt(E*E+F*F-G*G)))/(G-E) );
}

std::vector<float> Cinematica::cinematica_inversa(float x, float y, float z)
{  
    std::vector<float> sp;
    float E1 = 2 * L * ( y + a);
    float F1 = 2 * z * L;
    float G1=x*x+y*y+z*z+b*b+c*c+L*L+2*(x*b+y*c)-l*l;

    float E2=-L*(sqrt(3)*(x+b)+y+c);
    float F2=2*z*L; 
    float G2=x*x+y*y+z*z+b*b+c*c+L*L+2*(x*b+y*c)-l*l;

    float E3=L*(sqrt(3)*(x-b)-y-c);
    float F3=2*z*L; 
    float G3=x*x+y*y+z*z+b*b+c*c+L*L+2*(-x*b+y*c)-l*l;
    
    sp[0] = 2*atan(ti(E1,F1,G1));
    sp[1] = 2*atan(ti(E2,F2,G2));
    sp[2] = 2*atan(ti(E3,F3,G3));

    return sp;
}

void Cinematica::IrAPunto(float x, float y, float z)
{
    std::vector<float> articulares = this -> cinematica_inversa(x,y,z);
    myRobot->setPosicionArticulares(articulares[0],articulares[1],articulares[2], 0);
}