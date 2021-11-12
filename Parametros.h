#ifndef _PARAMETROS_
#define _PARAMETROS_


#include <Arduino.h>
#include <stdio.h>

#define GRADOS_POR_TIC 5.85
#define PULSOS_A_GRADOS(x) (x)/5.85
#define GRADOS_A_PULSOS(x) (x)*5.85


// ------- ENCODERS -------
#define PIN_MOTORA_CANALA 24
#define PIN_MOTORA_CANALB 25

#define PIN_MOTORB_CANALA 26
#define PIN_MOTORB_CANALB 27

#define PIN_MOTORC_CANALA 22
#define PIN_MOTORC_CANALB 23

// ------- MOTORES -------
#define PIN_STBY_1 47
#define PIN_STBY_2 37

// Motor A
#define PIN_MOTORA_IN1 39
#define PIN_MOTORA_IN2 41
#define PIN_MOTORA_PWM 3
#define KP_A 2
#define KI_A 0
#define KD_A 0

// Motor A
#define PIN_MOTORB_IN1 33
#define PIN_MOTORB_IN2 35
#define PIN_MOTORB_PWM 4
#define KP_B 2
#define KI_B 0
#define KD_B 0

// Motor c
#define PIN_MOTORC_IN1 45
#define PIN_MOTORC_IN2 43
#define PIN_MOTORC_PWM 5
#define KP_C 2
#define KI_C 0
#define KD_C 0

// Stepper
#define STEPS_PER_MM 5
#define PIN_STEP 40
#define PIN_DIR 20
#define RESET 10

// ------- FINALES DE CARRERA -------
#define PIN_ENDSTOPA 42
#define PIN_ENDSTOPB 44
#define PIN_ENDSTOPC 46

// ------- DEBUGGING -------
#define DEBUGGING_

//Otras movidas
#define A 0
#define B 1
#define C 2


#endif