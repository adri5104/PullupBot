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

#include "Motor.h"
#include "Encoder.h"
#include "ControlPosicion.h"
#include "Stepper.h"
#include "Endstop.h"


class Pullup
{
    private:
        Endstop* misEndstops[3];
        Controlposicion* misControles[3];
        Motor* misMotores[3];
        Encoder* misEncoders[3];

        //stepper

    public:
        Pullup();
        void init();
        Motor* getMotor(int);
        Encoder* getEncoder(int);
        Controlposicion* getControlposicion(int);

        void setPosicionArticulares(float, float, float, float);
        
};