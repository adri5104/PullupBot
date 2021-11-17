#include "Parametros.h"
#include "Stepper.h"
#include "Pullup.h"

Pullup::Pullup()
{
    //Motores
    misMotores[A] = new Motor(PIN_MOTORA_IN1, PIN_MOTORA_IN2, PIN_MOTORA_PWM);
    misMotores[B] = new Motor(PIN_MOTORB_IN1, PIN_MOTORB_IN2, PIN_MOTORB_PWM);
    misMotores[C] = new Motor(PIN_MOTORC_IN1, PIN_MOTORC_IN2, PIN_MOTORC_PWM);

    misEncoders[A] = new Encoder(PIN_MOTORA_CANALA, PIN_MOTORA_CANALB, GRADOS_POR_TIC_A);
    misEncoders[B] = new Encoder(PIN_MOTORB_CANALA, PIN_MOTORB_CANALB, GRADOS_POR_TIC_A);
    misEncoders[C] = new Encoder(PIN_MOTORC_CANALA, PIN_MOTORC_CANALB, GRADOS_POR_TIC_A);

    misEndstops[A] = new Endstop(PIN_ENDSTOPA);
    misEndstops[B] = new Endstop(PIN_ENDSTOPB);
    misEndstops[C] = new Endstop(PIN_ENDSTOPC);

    misControles[A] = new Controlposicion(misMotores[A], misEncoders[A]);
    misControles[B] = new Controlposicion(misMotores[B], misEncoders[B]);
    misControles[C] = new Controlposicion(misMotores[C], misEncoders[C]);

    miStepper = new Stepper(PIN_STEP,PIN_DIR,RESET,SLEEP);
    pidStatus = false;
    homing = false;
    setfree = true;
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
}

Motor* Pullup::getMotor(int quemotor)
{
    return misMotores[quemotor];
}

Encoder* Pullup::getEncoder(int queencoder)
{
    return misEncoders[queencoder];
}

Controlposicion* Pullup::getControlposicion(int quecontrol)
{
    return misControles[quecontrol];
}

Stepper* Pullup::getStepper()
{
    return miStepper;
}

void Pullup::setPosicionArticulares(float gradosA, float gradosB, float gradosC, float mmstepper)
{
    misControles[A]->setPosicionGrados(gradosA);
    misControles[B]->setPosicionGrados(gradosB);
    misControles[C]->setPosicionGrados(gradosC);
    pidStatus = true;
    setfree = false;
    homing = false;
    setlock = false;

    miStepper->prepareMove(mmstepper);
}

void Pullup::setPosicionArticulares_tics(int ticsA, int ticsB, int ticsC, float mmstepper)
{
    misControles[A]->setPosicionTics(ticsA);
    misControles[B]->setPosicionTics(ticsB);
    misControles[C]->setPosicionTics(ticsC);
    pidStatus = true;
    setfree = false;
    homing = false;
    setlock = false;
    miStepper->prepareMove(mmstepper);
}

void Pullup::goHome()
{
    //Serial.println("HOMING");
    #ifdef DEBUGGING_
    //1erial.println("HOMING");
    #endif
    //Si todos los endstop se pulsan
    if((misEndstops[C]->pressed() && (misEndstops[A]->pressed()) && (misEndstops[B]->pressed())))
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
    }
    else
    {
        misMotores[A]->setPWM(HOMING_PWM);
        misMotores[A]->setBack();
    }

    if(misEndstops[B]->pressed())
    {
        misMotores[B]->setStop();
        misEncoders[B]->setPosicionGrados(-45);
    }
    else
    {
        misMotores[B]->setPWM(HOMING_PWM);
        misMotores[B]->setBack();
    }

    if(misEndstops[C]->pressed())
    {
        misMotores[C]->setStop();
        misEncoders[C]->setPosicionGrados(-45);
    }
    else
    {
        misMotores[C]->setPWM(HOMING_PWM);
        misMotores[C]->setBack();
    }
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
   Serial.print(misEncoders[C]->getPosicionGrados());
   Serial.print(", ");
   Serial.print("MM:");
   Serial.print(miStepper->getPosition());
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

Endstop* Pullup::getEndstop(int queendstop)
{
    return misEndstops[queendstop];
}

void Pullup::SerialPrintPosicionTics()
{
    Serial.print(misEncoders[A]->getTics());
    Serial.print(" ");
    Serial.print(misEncoders[B]->getTics());
    Serial.print(" ");
    Serial.print(misEncoders[C]->getTics());
    Serial.print(" ");
    Serial.println(misEncoders[A]->getTics());
    
}

void Pullup::SerialPrintErrores()
{
    Serial.print(misControles[A]->getError());
    Serial.print(" ");
    Serial.print(misControles[B]->getError());
    Serial.print(" ");
    Serial.print(misControles[C]->getError());
    Serial.print(" ");
    Serial.println(misControles[A]->getError());
}

void Pullup::HomingAMano()
{
    misEncoders[A]->resetPosicion();
    misEncoders[B]->resetPosicion();
    misEncoders[C]->resetPosicion();
    this->setPosicionArticulares(0,0,0,0);
}