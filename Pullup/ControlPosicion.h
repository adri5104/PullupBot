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
        long tiempo_previo; //para calcular deltaT
        int referencia_tics; //referencia para el PID en pulsos
        float error_acumulado; //Se va sumando el error
        float error_previo;
        bool motorApagado; //senal digital que habilita o deshabilita el PID();
        Motor* myMotor;
        Encoder* myEncoder;
    public: 
        Controlposicion(Motor*, Encoder*);
        void setPosicionTics(int); //LLeva al motor a una posicion en tics;
        void setPosicionGrados(float); //Lleva al motor a una posicion en grados;
        void apagarMotor(); //deja libre el motor;
        void setGains(int, int, int); //Para dar las ganancias kp, ki y kd
        void control_logic(); // Donde se actualizan los valores del PID();
        float getError(){return error_previo;};
};
#endif