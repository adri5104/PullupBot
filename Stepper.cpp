#include "Stepper.h"
#include <arduino.h>

stepper::stepper() {

    is_moving = false;

}

void stepper::setPosition(float npx) {

    px = npx;

}

void stepper::prepareMove(float newx) {

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

    if (is_moving) enableMotor();

}


void stepper::move() {

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

    if (!is_moving) {
        disableMotor();
    }

}


void stepper::disableMotor() {

    digitalWrite(enable_pin, HIGH);

}

void stepper::enableMotor() {

    digitalWrite(enable_pin, LOW);

}
