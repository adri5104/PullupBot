#include "Stepper.h"
#include <arduino.h>

Stepper::Stepper(int stp, int dir, int res) {

    step_pin=stp;
    dir_pin=dir;
    reset=res;
    is_moving = false;
    px=0;
    disableStepper();
}

void Stepper::Sinit(){

    pinMode(step_pin,OUTPUT);
    pinMode(dir_pin,OUTPUT);
    pinMode(reset,OUTPUT);

}

void Stepper::setPosition(float npx) {

    px = npx;

}

void Stepper::prepareMove(float newx) {

    obj = (newx - px) * STEPS_PER_MM;
    absobj = abs(obj);
    if (absobj) {
        is_moving = true;
        maxsteps = absobj;
        digitalWrite(dir_pin, obj > 0 ? HIGH : LOW);
        step_count = 0;
        prev_time = millis();
        setPosition(newx);
    }

    if(is_moving) enableStepper();

}


void Stepper::move() {

    unsigned long curtime = millis();

    if (is_moving && (curtime - prev_time) >= millisbetweensteps) {
        prev_time = curtime;
        if (step_count<maxsteps) {
            digitalWrite(step_pin, HIGH);
            digitalWrite(step_pin, LOW);
            step_count++;
        }
    }

    is_moving = !(step_count >= maxsteps);

    if(!is_moving) disableStepper();

}

float Stepper::getPosition(){

    if(digitalRead(dir_pin)==HIGH){
        return (previa+step_count);
    }

    else{ 
        return(previa-step_count);
    }
}

void Stepper::enableStepper(){

    digitalWrite(reset,HIGH);
}

void Stepper::disableStepper(){

    digitalWrite(reset,LOW);
}

