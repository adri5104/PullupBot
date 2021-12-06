//FIchero con la implementacion de la clase controlposicion
#include "ControlPosicion.h"



Controlposicion::Controlposicion(Motor* Motor, Encoder_p* Encoder_p, float tics_vuelta)
{
    myMotor = Motor;
    myEncoder = Encoder_p;
    kp = 1;
    ki = 0;
    kd = 0;
    myMotor ->setFree();
    tiempo_previo = 0;
    referencia_tics = 0;
    error_acumulado = 0;
    error_previo = 0;
    grados_por_tic = 360.0/ tics_vuelta;
    //motorApagado = true;
    myPID = new PID(&in,&out,&set,kp,ki,kd,DIRECT);
    myPID->SetMode(AUTOMATIC);
    myPID->SetSampleTime(1);
    myPID->SetOutputLimits(-155,155);
    in = 0;
    out = 0;
    set = 0;
}

void Controlposicion::setGains(int kp_, int ki_, int kd_)
{
    kp = kp_;
    ki = ki_;
    kd = kd_;
}

void Controlposicion::setPosicionTics(int ref)
{
    referencia_tics = ref;
    motorApagado = false;
}

void Controlposicion::setPosicionGrados(float ref)
{
    referencia_tics = ref/ grados_por_tic;
    motorApagado = false;
}

void Controlposicion::apagarMotor()
{
    motorApagado = true;
}
void Controlposicion::control_logic()
{
        /*
        int pwr; //senal de pwr para el motor
        float deltaT = ((float)(micros()-tiempo_previo)) / 1.0e6; //intervalo de tiempo
        int error = (myEncoder->getTics()) - referencia_tics;
        error_acumulado+=(error*deltaT);

        //derivada del error
        float derivada_error = (error - error_previo)/ deltaT;

        //integral del error
        float integral_error = error_acumulado;

        //senal de control
        float u = kp*error + kd*derivada_error + ki*integral_error + 50;
        //map(pwr,0,255,60,255);
        pwr = fabs(u);
        
        if(pwr > MAX_PID_PWM) pwr = MAX_PID_PWM; // velocidad maxima

        if(u < 0)
        {
            myMotor ->setFwd();
            myMotor ->setPWM(pwr);
        }
        else
        {
            myMotor->setBack();
            myMotor->setPWM(pwr);
        }
        error_previo = error;
        */
       
       set = referencia_tics;
       
       in = myEncoder->getTics();
       myPID->Compute();
       if(out > 0)
        {
            myMotor ->setFwd();
            myMotor ->setPWM(out);
        }
        else
        {
            myMotor->setBack();
            myMotor->setPWM(abs(out));
        }
}
