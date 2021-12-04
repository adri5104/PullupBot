#include "Stepper.h"
#include "Parametros.h"
#include <arduino.h>

Stepper::Stepper(int stp, int dir, int res, int slp) {

    step_pin=stp;
    dir_pin=dir;
    reset=res;
    sleep=slp;
    is_moving = false;
    px=0;
    previa = 0;
    step_count = 0;
    maxsteps=0;
   // disableStepper();
}

void Stepper::Sinit(){

    pinMode(step_pin,OUTPUT);
    pinMode(dir_pin,OUTPUT);
    pinMode(reset,OUTPUT);
    pinMode(sleep,OUTPUT);

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

    //if(is_moving) enableStepper();

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

    //if(!is_moving) disableStepper();

}

float Stepper::getPosition(){

    if(digitalRead(dir_pin)==HIGH){
        return (previa+(step_count/STEPS_PER_MM));
    }

    else{ 
        return(previa-(step_count/STEPS_PER_MM));
    }
}

/*void Stepper::enableStepper(){

    digitalWrite(reset,HIGH);
}

void Stepper::disableStepper(){

    digitalWrite(reset,LOW);
}
*/
