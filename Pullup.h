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
        Endstop* myEndstop_A;
        Endstop* myEndstop_B;
        Endstop* myEndstop_C;
        Controlposicion* control_A;
        Controlposicion* control_B;
        Controlposicion* control_C;
        Motor* Motor_A;
        Motor* Motor_B;
        Motor* Motor_C;

        //stepper

    public:
        //pullup(mazo pines);
        // void pullup_logic(); // donde se actualizan los pids
        // lo que actualice los encoders

        void setPosicionArticulares(float, float, float, float);
        
}