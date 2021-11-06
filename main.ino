#include "Parametros.h"
#include "Encoder.h"
#include "ControlPosicion.h"


Encoder* myEncoder = new Encoder(PIN_MOTORA_CANALA, PIN_MOTORA_CANALB, GRADOS_POR_TIC);
Motor* myMotor = new Motor(PIN_MOTORA_IN1, PIN_MOTORA_IN2,PIN_MOTORA_PWM);
Controlposicion myControlposicion(myMotor,myEncoder);



void actualizar_encoder()
{
  myEncoder->actualizar_posicion();
}

void setup() {
  myEncoder->init();
  myMotor->init();
  Serial.begin(9600);

  //Interrupciones externas
  attachInterrupt(digitalPinToInterrupt(PIN_MOTORA_CANALA),actualizar_encoder,CHANGE);
}


void loop() 
{

 


  #ifdef DEBUGGING_
  Serial.print(myEncoder->getPosicionGrados());
  Serial.print(", ");
  Serial.println(myEncoder->getTics());
  #endif
}
