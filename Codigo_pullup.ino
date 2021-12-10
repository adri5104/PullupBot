#include <arm.h>
#include <SimplyAtomic.h>
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
  
  DueTimer::getAvailable().attachInterrupt(timer_handler).setPeriod(1000).start();

  Serial.begin(9600);

  //Se ponen los parametros de los pids
  myPullup.getControlposicion(A).setGains(KP_A,KI_A,KD_A);
  myPullup.getControlposicion(B).setGains(KP_B,KI_B,KD_B);
  myPullup.getControlposicion(C).setGains(KP_B,KI_B,KD_B);
  
  //Mensaje de bienvenida
  //Serial.println("-----------------------------------");
  //Serial.println("-------------- HOLI ---------------");
  //Serial.println("-----------------------------------");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}

//Variables leidas en el Serial
int op,a,b,c,d;

//Lo que se repite
void loop() 
{
  //myPullup.RobotLogic();
  //Lectura del serial
 if(Serial.available() > 0){ //si el serial está vacio no hace nada. Si tiene algo hace:
    char op;    //almacena el número que puede ser 0 al 3 (en caracter)
    op = Serial.read();
    switch(op)
      {        
        
      case '0': //este es en caso de SetFree por lo que las instrucciones son:
        myPullup.setFree(); 
      break;
        
      case '1': //Este es el caso de Homing por lo que las instrucciones son:
        //Ejecutar la función de Homing que en nuestro caso será encender los leds 8 veces con intervalos de 0.5 segundos y al acabar poner Hecho
        myPullup.goHome();        
      break;
        
      case '2': //Este es el caso de Enviar posición por lo que las instrucciones son:
      //Recibir 4 valores que son los pulsos de los 4 motores (Vamos a suponer que los valores los vamos a dar en float.
      //Como lo que enviaremos desde MatLab será algo así como "2" y luego "1.11111 2.22222 3.333333 4.444444\n". Tendremos que eliminar el \n del final

      float valores[4];
          
      for(int i=0; i<4; i++){     //cogemos los 4 valores y los almacenamos en ese valor
        valores[i] = Serial.parseFloat(SKIP_WHITESPACE);  //Con ese comando eliminamos el espacio entre los float    (Tiene TimeOut naiss)
      }

      myPullup.setPosicionArticulares_tics( valores[0], valores[1], valores[2], valores[3]);

      //Aqui esperamos a que los motores se muevan a la posición asignada para que no haya desborde de datos
      //Y enviamos a MatLab los valores nuevos para que se actualicen los pulsos en la interfaz (que dará paso a que matlab envíe nuevos datos).

      myPullup.SerialPrintPosicionTics();
              
      // El problema es que en el serial ahora hay dentro un terminator que hay que quitar. Ahora lo va eliminando el Serial.read de op pero no es tan eficiente.
        
        break;


        case '3': //Este es el caso de Recibir posición por lo que las instrucciones son:

        //Iría lo mismo que la ultima parte de la operación 2 (o no haría falta, puede usarse esta operacion) pero daré datos escritos por el serial para probar si funciona esta parte.
        
        myPullup.SerialPrintPosicionTics();

        break;

        case '4': //Este es el caso de Pedir error por lo que las intrucciones son:
          //Aqui le eviaríamos a matlab el error
          myPullup.SerialPrintErrores();
         break;  

        case '5': 
          
          myPullup.CambiaPinza();
         break; 

         case '6': //Este es el caso de Enviar posición por lo que las instrucciones son:
        //Recibir 4 valores que son los pulsos de los 4 motores (Vamos a suponer que los valores los vamos a dar en float.
        //Como lo que enviaremos desde MatLab será algo así como "2" y luego "1.11111 2.22222 3.333333 4.444444\n". Tendremos que eliminar el \n del final

        float valores_[4];
            
        for(int i=0; i<4; i++){     //cogemos los 4 valores y los almacenamos en ese valor
          valores_[i] = Serial.parseFloat(SKIP_WHITESPACE);  //Con ese comando eliminamos el espacio entre los float    (Tiene TimeOut naiss)
        }

        myPullup.setPosicionArticulares_tics_BESTIA( valores_[0], valores_[1], valores_[2], valores_[3]);

        //Aqui esperamos a que los motores se muevan a la posición asignada para que no haya desborde de datos
        //Y enviamos a MatLab los valores nuevos para que se actualicen los pulsos en la interfaz (que dará paso a que matlab envíe nuevos datos).

        myPullup.SerialPrintPosicionTics();
                
      // El problema es que en el serial ahora hay dentro un terminator que hay que quitar. Ahora lo va eliminando el Serial.read de op pero no es tan eficiente.
        
        break;  
    }
  }

 
  #ifdef DEBUGGING_
// myPullup.printMovidas();
 //myPullup.printGrados();
 //myPullup.SerialPrintPosicionTics();
  #endif
  #ifdef PRUEBAS_FINALES_DE_CARRERA
  if(myPullup.getEndstop(A).pressed()) Serial.println("ËNDSTOP_A PULSADO");
  if(myPullup.getEndstop(B).pressed()) Serial.println("ËNDSTOP_B PULSADO");
  if(myPullup.getEndstop(C).pressed()) Serial.println("ËNDSTOP_C PULSADO");
  #endif
  //#define SERIAL_PLOTTER
  
  }
