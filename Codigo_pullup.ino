

//#include <Encoder.h>

#include <PID_v1.h>

#include <DueTimer.h>


#include "DueTimer\DueTimer.h"
#include "Pullup.h"


//Nuestro robot
Pullup myPullup;
//PID myPID(&in,&out,&set,1,1,1,1);

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

void timer_handler()
{
  myPullup.RobotLogic();
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
  
  Timer4.attachInterrupt(timer_handler).setPeriod(100).start();

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
    a = Serial.parseFloat();
    b = Serial.parseFloat();
    c = Serial.parseFloat();
    d = Serial.parseInt();
    if (Serial.read() == '\n') break;
  }
  //Cosas que hace el robot.
  //delay(20);
  switch(op)
  {
    case 0:
      myPullup.setPosicionArticulares( a, b, c,d);
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

  #ifdef DEBUGGING_
// myPullup.printMovidas();
 myPullup.printGrados();
 //myPullup.SerialPrintPosicionTics();
  #endif
  #ifdef PRUEBAS_FINALES_DE_CARRERA
  if(myPullup.getEndstop(A).pressed()) Serial.println("ËNDSTOP_A PULSADO");
  if(myPullup.getEndstop(B).pressed()) Serial.println("ËNDSTOP_B PULSADO");
  if(myPullup.getEndstop(C).pressed()) Serial.println("ËNDSTOP_C PULSADO");
  #endif
  //#define SERIAL_PLOTTER
  
  }
