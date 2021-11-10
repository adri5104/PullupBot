#include "Parametros.h"
#include "Encoder.h"
#include "ControlPosicion.h"
#include "Pullup.h"

Pullup MyRobot;

void handler_encoderA()
{
  MyRobot.getEncoder(A)->actualizar_posicion();
}
void handler_encoderB()
{
  MyRobot.getEncoder(B)->actualizar_posicion();
}
void handler_encoderC()
{
  MyRobot.getEncoder(C)->actualizar_posicion();
}

void setup() {
  MyRobot.init();
  attachInterrupt(digitalPinToInterrupt(PIN_MOTORA_CANALA), handler_encoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_MOTORB_CANALA), handler_encoderB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_MOTORC_CANALA), handler_encoderC, CHANGE);
  Serial.begin(9600);  
  MyRobot.getControlposicion(A)->setGains(KP_A,KI_A,KD_A);
  MyRobot.getControlposicion(B)->setGains(KP_B,KI_B,KD_B);
  MyRobot.getControlposicion(C)->setGains(KP_C,KP_C,KD_C);

  //Activamos los enable
  pinMode(PIN_STBY_1, OUTPUT);
  pinMode(PIN_STBY_2, OUTPUT);
  digitalWrite(PIN_STBY_1, HIGH);
  digitalWrite(PIN_STBY_2, HIGH);
}

void loop() 
{
  MyRobot.getControlposicion(A)->control_logic();
  MyRobot.getControlposicion(B)->control_logic();
  MyRobot.getControlposicion(C)->control_logic();
  #ifdef DEBUGGING_
  Serial.print(MyRobot.getEncoder(A)->getPosicionGrados());
  Serial.print(",");
  Serial.print(MyRobot.getEncoder(A)->getPosicionGrados());
  Serial.print(",");
  Serial.print(MyRobot.getEncoder(A)->getPosicionGrados());
  #endif
  MyRobot.goHome();
}
