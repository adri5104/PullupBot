



#include "Parametros.h"
#include "Encoder.h"
#include "ControlPosicion.h"
#include "Pullup.h"
#include "Motor.h"
Pullup myPullup;

/*
Motor* Motor_A = new Motor(PIN_MOTORA_IN1, PIN_MOTORA_IN2, PIN_MOTORA_PWM);
Encoder* Encoder_A = new Encoder(PIN_MOTORA_CANALA, PIN_MOTORA_CANALB, GRADOS_POR_TIC);
Controlposicion* Control_A= new Controlposicion(Motor_A, Encoder_A); 
Motor* Motor_B = new Motor(PIN_MOTORB_IN1, PIN_MOTORB_IN2, PIN_MOTORB_PWM);
Encoder* Encoder_B = new Encoder(PIN_MOTORB_CANALA, PIN_MOTORB_CANALB, GRADOS_POR_TIC);
Controlposicion* Control_B= new Controlposicion(Motor_B, Encoder_B); 
Motor* Motor_C = new Motor(PIN_MOTORC_IN1, PIN_MOTORC_IN2, PIN_MOTORC_PWM);
Encoder* Encoder_C = new Encoder(PIN_MOTORC_CANALA, PIN_MOTORC_CANALB, GRADOS_POR_TIC);
Controlposicion* Control_C= new Controlposicion(Motor_C, Encoder_C); 
*/

void handler_encoderA()
{
  myPullup.getEncoder(A)->actualizar_posicion();  
}
void handler_encoderB()
{
  myPullup.getEncoder(B)->actualizar_posicion();
}
void handler_encoderC()
{
  myPullup.getEncoder(C)->actualizar_posicion();
}

void setup() {
  //Se inicializan las movidas
  myPullup.init();

  attachInterrupt(digitalPinToInterrupt(PIN_MOTORA_CANALA), handler_encoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_MOTORB_CANALA), handler_encoderB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_MOTORC_CANALA), handler_encoderC, CHANGE);
 
  Serial.begin(9600);
  //Se ponen los parametros de los pids
  myPullup.getControlposicion(A)->setGains(KP_A,KI_A,KD_A);
  myPullup.getControlposicion(B)->setGains(KP_B,KI_B,KD_B);
  myPullup.getControlposicion(C)->setGains(KP_B,KI_B,KD_B);
  
  //Mensaje de bienvenida
  Serial.println("-----------------------------------");
  Serial.println("-------------- HOLI ---------------");
  Serial.println("-----------------------------------");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);

}

//Variables leidas en el Serial
float a,b,c;

void loop() 
{
  //Lectura del serial
  while(Serial.available())
  {
    a = Serial.parseFloat();
    b = Serial.parseFloat();
    c = Serial.parseFloat();
    if (Serial.read() == '\n') break;
  }

  myPullup.RobotLogic();
  myPullup.setPosicionArticulares(a,b,c,0);
  myPullup.printMovidas();



  #ifdef DEBUGGING_
  Serial.print(Control_A->getError());
  Serial.print(",");
  Serial.print(Control_B->getError());
  Serial.print(",");
  Serial.println(Control_C->getError());
  #endif
  
}
