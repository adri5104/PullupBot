#ifndef _PARAMETROS_
#define _PARAMETROS_


#include <Arduino.h>
#include <stdio.h>

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
#define KP_A 1
#define KI_A 0
#define KD_A 0

// Motor A
#define PIN_MOTORB_IN1 6
#define PIN_MOTORB_IN2 7
#define PIN_MOTORB_PWM 8
#define KP_B 1
#define KI_B 0
#define KD_B 0

// Motor A
#define PIN_MOTORC_IN1 9
#define PIN_MOTORC_IN2 10
#define PIN_MOTORC_PWM 11
#define KP_C 1
#define KI_C 0
#define KD_C 0

// ------- FINALES DE CARRERA -------
#define PIN_ENDSTOPA 1
#define PIN_ENDSTOPB 2
#define PIN_ENDSTOPC 3

// ------- DEBUGGING -------
#define DEBUGGING_

//Otras movidas
#define A 0
#define B 1
#define C 2


#endif