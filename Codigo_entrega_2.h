/*


[17:13, 21/10/2021] Victoria Clase: //Pines con los cuales controlar los motores
#define CanalA 2
#define CanalB 3
#define Pwm 5
#define IN2 6
#define IN1 7
#define stdy 4

// Pin conectado al boton
#define BOT 30

//Constantes utilizadas para calcuar el PID
#define pulses_per_rev 60 //                MEDIRLO DE NUEVO
#define vel_0 155 //Valor limite para la velocidad cuando busca su posicion
#define kp 6
#define kd 10
#define ki 1
//Otras constantes que hemos probado: kp 6 kd 2 ki 0

//Constantes utilizadas para calcuar el PID de velocidad
#define kpv 1 //en principio solo usamos controlador proporcional
  // si añadimos ki: Ki=0;
[17:13, 21/10/2021] Victoria Clase: // INICIALIZACION
int caso;
int dato;
int vel; //en rpm
int objetivo;

//Con contador medimos la posición, que multiplicaod por 6 son los grados
//volatile long contador = 0;
int contador=0; //Se puede comentar y descomentar la anterior

long prevT = 0;
float errorprev = 0;
//float errorintegral = 0;

int contPrev=0;
int intervalo = 10; //1 segundo
long prevMillis = 0;
long actMillis = 0;
float rpm = 0;

float pwr; //La velocidad para el motor
int dir=0; //La direccion dpara el motor


void setup() {
  Serial.begin(9600); // Inicializar puerto serie
  
  pinMode(CanalA, INPUT_PULLUP);
  pinMode(CanalB, INPUT_PULLUP);
  pinMode(BOT, INPUT);
  pinMode( Pwm , OUTPUT );
  pinMode( IN1 , OUTPUT );
  pinMode( IN2 , OUTPUT );

  digitalWrite(stdy, HIGH);

  attachInterrupt(digitalPinToInterrupt(CanalA), Lectura_encoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(CanalB), Lectura_encoderB, CHANGE);
  
}


// BUCLE
void loop() {
 
  while (Serial.available())
  {
    caso = Serial.parseInt();
    dato = Serial.parseInt();

    vel=0; //Comando para detener el PID de velocidad al recibir un nuevo comando
    
    if (Serial.read() == '\n') break;
  }
  
  /*
  Serial.println(caso);
  Serial.println(dato);
  */
  
  switch (caso)
  {
    case 1: // Pongo a 0 el robot
      // Serial.println("Caso 1");
      set_Origen();
      break;
    case 2: // Pongo el motor en la posición que quiera
      // Serial.println("Caso 2");
      objetivo = dato; 
      break;
    case 3: // Mando la posicion
      // Serial.println("Caso 3");
      Serial.println(contador*6); //Devuelvo la posicion en grado
      break;
    case 4: // Pongo la velocidad
      // Serial.println("Caso 4");
      vel = dato; 
      break;
    default:
      break;
  }

// ++ IMPORTANTE ++
  caso = 0;

  if(!vel) PID();
  else if(vel){
    PID_vel();
  }

  setMotor(dir, pwr);

  /*
   Serial.print(objetivo);
   Serial.print(" ");
   Serial.print(contador);
   Serial.println();
   Serial.print(objetivo);
   Serial.print(rpm);
  */
}


//Control de posicion
//Funciones que por medio de interrupciones nos dice si 
//estamos girando hacia adelante o hacia atras y mide los pulsos
void Lectura_encoderA() {
  int b = digitalRead(CanalB);
  if (digitalRead(CanalA) == b ) contador++;
  else contador--;
}

void Lectura_encoderB() {
  int a = digitalRead(CanalA);
  if (digitalRead(CanalB) != a ) contador++;
  else contador--;
}


void PID(){
  long currT = micros();
  float deltaT = ((float)(currT - prevT)) / 1.0e6;
  prevT = currT;

  int error = contador - objetivo; //la diferencia entre la posicion actual y la que me piden que este, luego debo mandarsela a matlab
  
  //derivada
  float dedt = (error - errorprev) / (deltaT);
  
  //integral
  float errorintegral = errorintegral + error * deltaT;
  
  //señal de control
  float u = kp * error + kd * dedt + ki * errorintegral;
  pwr = fabs(u);
  if (pwr > 155) pwr = 155;
  
  if (u < 0) dir = -1;
  else if (u > 0) dir = 1;
  errorprev = error;
}


void PID_vel(){
  
  volatile long contadorv=contador;
  actMillis = millis();
  
  if ( actMillis-prevMillis > intervalo ) {  //si ha transcurrido un segundo
    
    prevMillis = actMillis;
    rpm=(float)(((contador-contPrev)/intervalo)*60/pulses_per_rev);
    contPrev=contadorv;
    contadorv=0;
  }
  
  // si añadimos ki: long currT=micros();
  // float deltaT=((float)(currT-prevT))/1.0e6;
  // prevT=currT;
  // errorintegral=errorintegral+error*deltaT;
  
  float error=vel-rpm;
  float u=kpv*error; //si añadimos Ki: float u=kp*error+ki*errorintegral;
  
  //Damos valores a la velocidad y direccion
  dir=1;
  if (u<0) dir=-1;
  pwr=(int)fabs(u);
  if(pwr>255) pwr=255;
}


// Funcion que atrapa el programa en un bucle de velocidad 
// constante hasta que llega al origen
void set_Origen(){
      while(!digitalRead(BOT)){
        //Serial.println(digitalRead(BOT));
        objetivo+=10;
        PID();
        setMotor(dir, vel_0);
      }
      contador=0;
      objetivo=0;
}


void setMotor(int dir, int pwmVal) { //dir de rot, velocidad de pwm
  
  analogWrite(Pwm, pwmVal); //set speed
  if (dir == 1) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else if (dir == -1) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
}

*/