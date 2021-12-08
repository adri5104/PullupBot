#include "Parametros.h"
#include "Stepper.h"
#include "Pullup.h"
#include "Pinza.h"

Pullup::Pullup()
{
    //Motores
    misMotores[A] = new Motor(PIN_MOTORA_IN1, PIN_MOTORA_IN2, PIN_MOTORA_PWM);
    misMotores[B] = new Motor(PIN_MOTORB_IN1, PIN_MOTORB_IN2, PIN_MOTORB_PWM);
    misMotores[C] = new Motor(PIN_MOTORC_IN1, PIN_MOTORC_IN2, PIN_MOTORC_PWM);

    misEncoders[A] = new Encoder_p(PIN_MOTORA_CANALA, PIN_MOTORA_CANALB, TICS_A);
    misEncoders[B] = new Encoder_p(PIN_MOTORB_CANALA, PIN_MOTORB_CANALB, TICS_B);
    misEncoders[C] = new Encoder_p(PIN_MOTORC_CANALA, PIN_MOTORC_CANALB, TICS_A);

    misEndstops[A] = new Endstop(PIN_ENDSTOPA);
    misEndstops[B] = new Endstop(PIN_ENDSTOPB);
    misEndstops[C] = new Endstop(PIN_ENDSTOPC);

    misControles[A] = new Controlposicion(misMotores[A], misEncoders[A], TICS_A);
    misControles[B] = new Controlposicion(misMotores[B], misEncoders[B], TICS_B);
    misControles[C] = new Controlposicion(misMotores[C], misEncoders[C], TICS_A);

    miStepper = new Stepper(PIN_STEP,PIN_DIR,RESET,SLEEP);
    miPinza = new Pinza();

    pidStatus =true;
    homing = false;
    setfree = false;
    setlock = false;
    this->setPosicionArticulares(0,0,0,0);


}

void Pullup::init()
{
    misMotores[A]->init();
    misMotores[B]->init();
    misMotores[C]->init();

    misEncoders[A]->init();
    misEncoders[B]->init();
    misEncoders[C]->init();

    misEndstops[A]->init();
    misEndstops[B]->init();
    misEndstops[C]->init();

    miStepper->Sinit();
    miPinza->Servinit(PIN_PINZA);
}

Motor& Pullup::getMotor(int quemotor)
{
    return *misMotores[quemotor];
}

Encoder_p& Pullup::getEncoder(int queencoder)
{
    return *misEncoders[queencoder];
}

Controlposicion& Pullup::getControlposicion(int quecontrol)
{
    return *misControles[quecontrol];
}

Stepper& Pullup::getStepper()
{
    return *miStepper;
}

Pinza& Pullup::getPinza()
{
    return *miPinza;
}

void Pullup::setPosicionArticulares(float gradosA, float gradosB, float gradosC, float mmstepper)
{
  
    misControles[A]->setPosicionGrados(gradosA);
    //delay(400);
    misControles[B]->setPosicionGrados(gradosB);
    //delay(400);
    misControles[C]->setPosicionGrados(gradosC);
    //delay(400);
    
    pidStatus = true;
    setfree = false;
    homing = false;
    setlock = false;

    miStepper->prepareMove(mmstepper);
}

void Pullup::setPosicionArticulares_tics(int ticsA, int ticsB, int ticsC, float mmstepper)
{
    misControles[A]->setPosicionTics(ticsA);
    //delay(400);
    misControles[B]->setPosicionTics(ticsB);
    //delay(400);
    misControles[C]->setPosicionTics(ticsC);
    pidStatus = true;
    setfree = false;
    homing = false;
    setlock = false;
    miStepper->prepareMove(mmstepper);
}

void Pullup::goHome()
{

    uint8_t x = misEncoders[A]->getTics();
    while ((misEndstops[A]->pressed()))
    {
        misControles[A]->setPosicionTics(x);
        delay(200);
        x -= 10;
    }
    misEncoders[A]->setPosicionGrados(40);
    delay(50);
    misControles[A] -> setPosicionTics(0);
    delay(50);

    x = misEncoders[C]->getTics();
    while ((misEndstops[C]->pressed()))
    {
        misControles[C]->setPosicionTics(x);
        delay(200);
        x -= 10;
    }
    misEncoders[C]->setPosicionGrados(40);
    delay(50);
    misControles[C] -> setPosicionTics(0);
    delay(50);

    x = misEncoders[B]->getTics();
    while ((misEndstops[B]->pressed()))
    {
        misControles[B]->setPosicionTics(x);
        delay(200);
        x -= 10;
    }
    misEncoders[B]->setPosicionGrados(40);
    delay(50);
    misControles[B] -> setPosicionTics(0);
    delay(50);
    
    //Si todos los endstop se pulsan
    /*if(a && (b && c))
    {
        homing = false;
        setfree = false;
        setlock = false;
        pidStatus = true;
        misControles[A]->setPosicionGrados(0);
        misControles[B]->setPosicionGrados(0);
        misControles[C]->setPosicionGrados(0);
        
        return;
    }
    else
    {
        pidStatus = false;
        homing = true;
        setfree = false;
        setlock = false;
    }

    if(misEndstops[A]->pressed())
    {
        misMotores[A]->setStop();
        misEncoders[A]->setPosicionGrados(-45);
        misControles[A]->setPosicionGrados(0);
         a = true;

    }
    else
    {
        misMotores[A]->setPWM(HOMING_PWM);
        misMotores[A]->setBack();
        a = false;
    }

    if(misEndstops[B]->pressed())
    {
        misMotores[B]->setStop();
        misEncoders[B]->setPosicionGrados(-45);
        misControles[B]->setPosicionGrados(0);
         b = true;
    }
    else
    {
        misMotores[B]->setPWM(HOMING_PWM);
        misMotores[B]->setBack();
        
        b = false;
    }

    if(misEndstops[C]->pressed())
    {
        misMotores[C]->setStop();
        misEncoders[C]->setPosicionGrados(-45);
        misControles[C]->setPosicionGrados(0);
        c = true;
        
    }
    else
    {
        misMotores[C]->setPWM(HOMING_PWM);
        misMotores[C]->setBack();
        c = false;
    }*/
    
}

void Pullup::setLock()
{
    setlock = true;
    setfree = false;
    pidStatus = false;
    homing = false;
    misMotores[A]->setStop();
    misMotores[B]->setStop();
    misMotores[C]->setStop();
}

void Pullup::printMovidas()
{
    Serial.print("Errores: ");
    Serial.print(misControles[A]->getError());
    Serial.print(", ");
    Serial.print(misControles[B]->getError());
    Serial.print(", ");
    Serial.println(misControles[C]->getError());
}

void Pullup::RobotLogic()
{
    if(pidStatus == true) //Enciende o apaga el PID
    {
    misControles[A]->control_logic();
    misControles[B]->control_logic();
    misControles[C]->control_logic();
    };

    if(homing == true)
    {
        this -> goHome();
    }

    if(setfree == true)
    {
        this -> setFree();
    }

    if(setlock == true)
    {
        this->setLock();
    }

    if((misEndstops[C]->pressed() && (misEndstops[A]->pressed()) && (misEndstops[B]->pressed()))) digitalWrite(LED_BUILTIN, HIGH);
    else digitalWrite(LED_BUILTIN, 0x0);
    /*
    if(misEndstops[A]->pressed()) misMotores[A]->setFree();
    if(misEndstops[B]->pressed()) misMotores[B]->setFree();
    if(misEndstops[C]->pressed()) misMotores[C]->setFree(); 
    */
    miStepper->move();
    miPinza->move();
}

void Pullup::printGrados()
{
   Serial.print("Grados: ");
   Serial.print(misEncoders[A]->getPosicionGrados());
   Serial.print(", ");
   Serial.print("Grados: ");
   Serial.print(misEncoders[B]->getPosicionGrados());
   Serial.print(", ");
   Serial.print("Grados: ");
   Serial.println(misEncoders[C]->getPosicionGrados());
  
}

void Pullup::setFree()
{
    setfree = true;
    pidStatus = false;
    homing = false;
    misMotores[A]->setFree();
    misMotores[B]->setFree();
    misMotores[C]->setFree();
    //miStepper->disableStepper();
}

Endstop& Pullup::getEndstop(int queendstop)
{
    return *misEndstops[queendstop];
}

void Pullup::SerialPrintPosicionTics()
{
    Serial.println(misEncoders[A]->getTics());  
    Serial.println(misEncoders[B]->getTics());
    Serial.println(misEncoders[C]->getTics());
    Serial.println(misEncoders[A]->getTics());    
}

void Pullup::SerialPrintErrores()
{
    Serial.println(misControles[A]->getError());
    Serial.println(misControles[B]->getError());
    Serial.println(misControles[C]->getError());
    Serial.println(misControles[A]->getError());
}

void Pullup::HomingAMano()
{
    misEncoders[A]->resetPosicion();
    misEncoders[B]->resetPosicion();
    misEncoders[C]->resetPosicion();
    this->setPosicionArticulares(0,0,0,0);
}

void Pullup::CambiaPinza()
{
    miPinza->setStado(!miPinza->getStado());
}