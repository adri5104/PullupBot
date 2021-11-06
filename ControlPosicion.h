#ifndef _CONTROLPOSICION_
#define _CONTROLPOSICION_
#include<Arduino.h>
#include"Motor.h"
#include"Encoder.h"
#include"Parametros.h"

class Controlposicion
{
    private:
        int kp;
        int kd;
        int ki;
        long tiempo_previo;
        int referencia_tics;
        float error_acumulado;
        float error_previo;
        bool motorApagado;

        Motor* myMotor;
        Encoder* myEncoder;

    public: 
        Controlposicion(Motor*, Encoder*);
        void setPosicionTics(int); //LLeva al motor a una posicion en tics;
        void setPosicionGrados(float); //Lleva al motor a una posicion en grados;
        void apagarMotor(); //deja libre el motor;
        void setGains(int, int, int); //Para dar las ganancias kp, ki y kd
        void control_logic(); // Donde se actualizan los valores del PID();
        

};


#endif