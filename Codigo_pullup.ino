
#include "Parametros.h"
#include "Encoder.h"
#include "ControlPosicion.h"
#include "Pullup.h"
#include "Motor.h"

//Nuestro robot
Pullup myPullup;
//HOLIWIS
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
//Funciones para manejar las interrupciones de los encoders. No se puede 
//llamar a un metodo de una clase desde una interrupcion.
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
//Setup. Movidas de cuando se hace reset
void setup() {

  //Se inicializan las movidas
  myPullup.init();
  pinMode(PIN_STBY_1, OUTPUT);
  pinMode(PIN_STBY_2, OUTPUT);
  digitalWrite(PIN_STBY_1, HIGH);
  digitalWrite(PIN_STBY_2, HIGH);
  digitalWrite(RESET,LOW);
  digitalWrite(SLEEP,LOW);

  //Interrupciones de los encoders
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

//Variables leidas en el Seria
int op;
float a,b,c;

//Lo que se repite
void loop() 
{
  //Lectura del serial
  while(Serial.available())
  {
    op = Serial.parseInt();
    a = Serial.parseFloat();
    b = Serial.parseFloat();
    c = Serial.parseFloat();
    if (Serial.read() == '\n') break;
  }

  //Cosas que hace el robot.
  myPullup.RobotLogic();
  
  if(op = 1) myPullup.setPosicionArticulares(a,b,c,0);
  
  if(op = 0) myPullup.goHome();
  
   //Para probar los motores
  //myPullup.getMotor(C)->setFwd();
  //myPullup.getMotor(C)->setPWM(255);
  //myPullup.getMotor(A)->setFwd();
  //myPullup.getMotor(A)->setPWM(255); 
  //myPullup.getMotor(B)->setFwd();
  //myPullup.getMotor(B)->setPWM(255);
  

  //Holi
  #ifdef DEBUGGING_
  myPullup.printMovidas();
  myPullup.printGrados();
  #endif

  #ifdef PRUEBAS_FINALES_DE_CARRERA
  if(myPullup.getEndstop(A)->pressed()) Serial.println("ËNDSTOP_A PULSADO");
  if(myPullup.getEndstop(B)->pressed()) Serial.println("ËNDSTOP_B PULSADO");
  if(myPullup.getEndstop(C)->pressed()) Serial.println("ËNDSTOP_C PULSADO");
  #endif
}
