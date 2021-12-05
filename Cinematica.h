#ifndef CINEMATICA_
#define CINEMATICA_
#include "Pullup.h"
#include <vector>
#include <iostream>

//using namespace std;

class Cinematica
{
    private:
        Pullup* myRobot;
        float pos_real[3];
        float pos_articulares[3];
        std::vector<float> cinematica_inversa(float x, float y, float z);
        //std::vector<float> cinematica_directa(std::vector<float>);
        float ti(float, float, float);
        //Datos
        //Base inferior
        float sB;
        float uB;
        float wB;
        //Base inferior
        float sP;
        float uP;
        float wP;
        //Articulaciones
      
        float a;
        float b;
        float c;
        float L;
        float l;
        float A_;


    public:
        Cinematica(Pullup*);
        void IrAPunto(float,float,float);
        //void LineaRecta(float,float,float,float,float,float);
        //void PrintPosicion();
};
#endif