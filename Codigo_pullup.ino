
#include "DueTimer\DueTimer.h"
#include "Pullup.h"
//Nuestro robot
Pullup myPullup;



#include "Parametros.h"
#include "Encoder.h"
#include "ControlPosicion.h"
#include "Pullup.h"
#include "Motor.h"


void handler_encoderA()
{
  myPullup.getEncoder(A).actualizar_posicion();  
}
void handler_encoderB()
{
  myPullup.getEncoder(B).actualizar_posicion();
}
void handler_encoderC()
{
  myPullup.getEncoder(C).actualizar_posicion();
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
  myPullup.getControlposicion(A).setGains(KP_A,KI_A,KD_A);
  myPullup.getControlposicion(B).setGains(KP_B,KI_B,KD_B);
  myPullup.getControlposicion(C).setGains(KP_B,KI_B,KD_B);
  
  //Mensaje de bienvenida
  Serial.println("-----------------------------------");
  Serial.println("-------------- HOLI ---------------");
  Serial.println("-----------------------------------");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}

//Variables leidas en el Serial
int op,a,b,c,d;

//Lo que se repite
void loop() 
{
  //Lectura del serial
  while(Serial.available())
  {
    op = Serial.parseInt();
    a = Serial.parseInt();
    b = Serial.parseInt();
    c = Serial.parseInt();
    d = Serial.parseInt();
    if (Serial.read() == '\n') break;
  }
  //Cosas que hace el robot.
  

  switch(op)
  {
    case 0:
      myPullup.setPosicionArticulares(a,b,c,d);
    break;
    case 1: 
      myPullup.goHome();
    break;
    case 2:
      myPullup.SerialPrintPosicionTics();
    break;
    case 3:
      myPullup.setFree();
    break;
    case 4:
      myPullup.SerialPrintErrores();
    break;
    default:
    break;
  }
  op = 7;
//ab
  myPullup.RobotLogic();

  //Si no funciona a la primera, probar a descomentar la siguiente linea
  #ifdef PRINT_SERIAL
  Serial.print(op);
  Serial.print(",");
  Serial.print(a);
  Serial.print(",");
  Serial.print(b);
  Serial.print(",");
  Serial.print(c);
  Serial.print(",");
  Serial.println(d);
  #endif
  #ifdef DEBUGGING_
 //myPullup.printMovidas();
  //myPullup.printGrados();
  #endif
  #ifdef PRUEBAS_FINALES_DE_CARRERA
  if(myPullup.getEndstop(A).pressed()) Serial.println("ËNDSTOP_A PULSADO");
  if(myPullup.getEndstop(B).pressed()) Serial.println("ËNDSTOP_B PULSADO");
  if(myPullup.getEndstop(C).pressed()) Serial.println("ËNDSTOP_C PULSADO");
  #endif
  //#define SERIAL_PLOTTER
  #ifdef SERIAL_PLOTTER
  int a = digitalRead(PIN_MOTORB_CANALA);
  int b = digitalRead(PIN_MOTORB_CANALB);
  Serial.print(a*5);
  Serial.print(" ");
  Serial.print(b*5);
  Serial.println();
  #endif
  }