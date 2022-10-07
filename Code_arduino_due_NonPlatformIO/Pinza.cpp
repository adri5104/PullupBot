#include "Pinza.h"
#include "Parametros.h"
#include <arduino.h>
#include <Servo.h>

Pinza::Pinza() {

    estado=false;
}

void Pinza::init(int servo_Pin){

    pinza.attach(servo_Pin);
}

void Pinza::move() {

    if(estado == true)
    { 
        pinza.write(ANG_MAX);
        estado = !estado;   
        }                  //Estado en 0, abierto
    else
    {
        pinza.write(ANG_MIN);  
        estado = !estado;
    }                         //Estado en 1, cerrado
}

bool Pinza::getStado() { return estado; }

void Pinza::setStado(bool stat) { estado=stat; }
