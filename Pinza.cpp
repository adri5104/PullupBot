#include "Pinza.h"
#include "Parametros.h"
#include <arduino.h>
#include <Servo.h>

Pinza::Pinza() {

    estado=0;
}

void Pinza::Servinit(int servo_Pin){

    pinza.attach(servo_Pin);
}

void Pinza::move() {

    if(estado) pinza.write(ANG_MAX);                     //Estado en 0, abierto
    else pinza.write(ANG_MIN);                          //Estado en 1, cerrado
}

bool Pinza::getStado() { return estado; }

void Pinza::setStado(bool stat) { estado=stat; }
