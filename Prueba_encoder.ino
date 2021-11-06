#include "Parametros.h"
#include "Encoder.h"

Encoder myEncoder(PIN_MOTORA_CANALA, PIN_MOTORA_CANALB, GRADOS_POR_TIC);

void actualizar_encoder()
{
  myEncoder.actualizar_posicion();
}

void setup() {
  myEncoder.init();
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(PIN_MOTORA_CANALA),actualizar_encoder,CHANGE);
}


void loop() 
{
 
  Serial.print(myEncoder.getPosicionGrados());
  Serial.print(", ");
  Serial.println(myEncoder.getTics());
  
}
