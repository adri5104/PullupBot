#ifndef _PARAMETROS_
#define _PARAMETROS_


#include <Arduino.h>

#define GRADOS_POR_TIC 5.50
#define PULSOS_A_GRADOS(x) (x)/5.50
#define GRADOS_A_PULSOS(x) (x)*5.50


// ------- ENCODERS -------
#define PIN_MOTORA_CANALA 18
#define PIN_MOTORA_CANALB 19

#define PIN_MOTORB_CANALA 18
#define PIN_MOTORB_CANALB 19

#define PIN_MOTORC_CANALA 18
#define PIN_MOTORC_CANALB 19

// ------- MOTORES -------
#define PIN_STBY_1 1
#define PIN_STBY_2 2

// Motor A
#define PIN_MOTORA_IN1 3
#define PIN_MOTORA_IN2 4
#define PIN_MOTORA_PWM 5

// Motor A
#define PIN_MOTORB_IN1 6
#define PIN_MOTORB_IN2 7
#define PIN_MOTORB_PWM 8

// Motor A
#define PIN_MOTORC_IN1 9
#define PIN_MOTORC_IN2 10
#define PIN_MOTORC_PWM 11

// ------- DEBUGGING -------
#define DEBUGGING_


#endif