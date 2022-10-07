#ifndef _PARAMETROS_
#define _PARAMETROS_


#include <Arduino.h>
#include <stdio.h>

#define TICS_A 2200

#define TICS_B 1093

#define GRADOS_POR_TIC_A 5.85
#define GRADOS_POR_TIC_B 5.85
#define GRADOS_POR_TIC_C 5.85
#define PULSOS_A_GRADOS(x) (x)/5.85
#define GRADOS_A_PULSOS(x) (x)*5.85

// ------- LIMITES -------
#define MAX_PID_PWM 255
#define HOMING_PWM  175
#define GRAVITY_PWM 150

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
#define KP_A 5
#define KI_A 1
#define KD_A 0.05

// Motor A
#define PIN_MOTORB_IN1 33
#define PIN_MOTORB_IN2 35
#define PIN_MOTORB_PWM 4
#define KP_B 5
#define KI_B 1
#define KD_B 0.05

// Motor c
#define PIN_MOTORC_IN1 45
#define PIN_MOTORC_IN2 43
#define PIN_MOTORC_PWM 5
#define KP_C 5
#define KI_C 1
#define KD_C 0.05

// Stepper
#define STEPS_PER_MM 5
#define PIN_STEP 6
#define PIN_DIR 53
#define RESET 50
#define SLEEP 48
#define millisbetweensteps 0.005

// Servo
#define ANG_MAX 180
#define ANG_MIN 0
#define PIN_PINZA 8
#define TRAP_TIME 500

// ------- FINALES DE CARRERA -------
#define PIN_ENDSTOPA 42
#define PIN_ENDSTOPB 44
#define PIN_ENDSTOPC 46
#define PIN_ENDSTOPS 40

// ------- DEBUGGING -------
//#define DEBUGGING_
//#define PRUEBAS_FINALES_DE_CARRERA
//#define PRINT_SERIAL

//Otras movidas
#define A 0
#define B 1
#define C 2
#define S 3

#endif