#include "Stepper.h"
#include <arduino.h>

stepper::stepper() {
    feed_rate = 0;
    is_moving = false;
}

void stepper::setFeedrate(float nfr) {

    nfr = nfr * STEPS_PER_MM / 60;
    if (feed_rate == nfr || nfr > MAX_FEEDRATE || nfr < MIN_FEEDRATE) return;

    step_delay = MAX_FEEDRATE / nfr;
    feed_rate = nfr;

}

void stepper::setPosition(float npx) {

    px = npx;

}

void stepper::prepareMove(float newx) {
    maxsteps = 0;
    obj = (newx - px) * STEPS_PER_MM;
    absobj = abs(obj);
    if (absobj) {
        is_moving = true;
        maxsteps = absobj;
    }

    digitalWrite(dir_pin, obj > 0 ? HIGH : LOW);

    delay_t = MAX_FEEDRATE / 5000;
    accel = 1;
    steps_to_accel = delay_t - step_delay;

    if (steps_to_accel > maxsteps / 2) steps_to_accel = maxsteps / 2;
    steps_to_decel = maxsteps - steps_to_accel;

    step_count = 0;
    prev_time = 0;

    if (is_moving) enableMotor();
    setPosition(newx);
}


void stepper::move() {

    unsigned long curtime = micros();
    unsigned int _delay;

    if (is_moving && (curtime - prev_time) >= delay_t) {
        prev_time = curtime;
        over = over + absobj;
        if (over >= maxsteps) {
            over = over - maxsteps;
            _delay = 100;
            digitalWrite(step_pin, HIGH);
            delayMicroseconds(_delay);
            digitalWrite(step_pin, LOW);
            delayMicroseconds(_delay);
        }
    }

    if (step_count < steps_to_accel) {
        delay_t = delay_t - accel;
    }
    if (step_count >= steps_to_decel) {
        delay_t = delay_t + accel;
    }
    step_count++;

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
