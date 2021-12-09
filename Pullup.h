


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
#include "Pinza.h"
#include <Arduino.h>
class Pullup 
{
    private:
        Endstop* misEndstops[4];
        Controlposicion* misControles[3];
        Motor* misMotores[3];
        Motor* Motor_A;
        Encoder_p* misEncoders[3];
        Stepper* miStepper;
        //stepper
        Pinza* miPinza;
        
        bool pidStatus;
        bool homing; // variable que indica a logic que debe estar en homing
        bool setfree; // variable que indica a logic que debe estar en free
        bool setlock; // variable que indica a logic que debe estar en lock
        bool a,b,c; //variable que indica si endstop esta en ON
    public:
        Pullup();
        void init();

        Motor& getMotor(int);
        Encoder_p& getEncoder(int);
        Controlposicion& getControlposicion(int);
        Stepper& getStepper();
        Endstop& getEndstop(int);
        Pinza& getPinza();
        
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
        void CambiaPinza();

};
#endif

