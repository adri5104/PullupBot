#include "Parametros.h"
#include "Encoder.h"
#include "ControlPosicion.h"
#include "Pullup.h"








void setup() {
  
  Serial.begin(9600);
  

  //Interrupciones externas
  
}


void loop() 
{

  


  #ifdef DEBUGGING_
  Serial.print(myEncoder->getPosicionGrados());
  Serial.print(", ");
  Serial.println(myEncoder->getTics());
  #endif
}
