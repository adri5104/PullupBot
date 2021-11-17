/* En esta clase ya quedaran implementadas todas las clases anteriores
Tendra como atributos 3 clases Motor con sus 3 encoders, sus 3 Endstop y sus 3
controles de posicion. Tambien el stepper
Como metodos tendra todas las acciones que le pueda pedir la clase ComunicacionSerial.
Por ejemplo llevar a los motores a una posicion en concreto (coordenadas articulares),
devolver la posicion de los motores (en coordenadas articulares), llevar al robot a una posicion concreta (cinematica inversa)
y devolver la posicion del robot (cinematica directa)
*/


/* get coordenadas articulares
    homing

    */

#ifndef _PULLUP_
#define _PULLUP_

#include "Motor.h"
#include "Encoder.h"
#include "ControlPosicion.h"
#include "Stepper.h"
#include "Endstop.h"
#include <Arduino.h>
class Pullup 
{
    private:
        Endstop* misEndstops[3];
        Controlposicion* misControles[3];
        Motor* misMotores[3];
        Motor* Motor_A;
        Encoder* misEncoders[3];
        Stepper* miStepper;
        //stepper
        bool pidStatus;
        bool homing;
        bool setfree;
        bool setlock;
    public:
        Pullup();
        void init();

        Motor* getMotor(int);
        Encoder* getEncoder(int);
        Controlposicion* getControlposicion(int);
        Stepper* getStepper();
        Endstop* getEndstop(int);
        
        void setPosicionArticulares(float, float, float, float);     
        void setPosicionArticulares_tics(int,int,int,float);
        void goHome(); //Hace homing al robot
        void setFree();
        void setLock(); //apaga los motores
        void printMovidas(); //imprime coas
        void printGrados();
        void RobotLogic(); //Maquina de estados del robot
        void SerialPrintPosicionTics();
        void SerialPrintErrores();
        void HomingAMano();
};
#endif

