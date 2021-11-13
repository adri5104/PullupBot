#include "Parametros.h"

#include "Pullup.h"

Pullup::Pullup()
{
    //Motores
    misMotores[A] = new Motor(PIN_MOTORA_IN1, PIN_MOTORA_IN2, PIN_MOTORA_PWM);
    misMotores[B] = new Motor(PIN_MOTORB_IN1, PIN_MOTORB_IN2, PIN_MOTORB_PWM);
    misMotores[C] = new Motor(PIN_MOTORC_IN1, PIN_MOTORC_IN2, PIN_MOTORC_PWM);

    misEncoders[A] = new Encoder(PIN_MOTORA_CANALA, PIN_MOTORA_CANALB, GRADOS_POR_TIC);
    misEncoders[B] = new Encoder(PIN_MOTORB_CANALA, PIN_MOTORB_CANALB, GRADOS_POR_TIC);
    misEncoders[C] = new Encoder(PIN_MOTORC_CANALA, PIN_MOTORC_CANALB, GRADOS_POR_TIC);

    misEndstops[A] = new Endstop(PIN_ENDSTOPA);
    misEndstops[B] = new Endstop(PIN_ENDSTOPB);
    misEndstops[C] = new Endstop(PIN_ENDSTOPC);

    misControles[A] = new Controlposicion(misMotores[A], misEncoders[A]);
    misControles[B] = new Controlposicion(misMotores[B], misEncoders[B]);
    misControles[C] = new Controlposicion(misMotores[C], misEncoders[C]);

    miStepper = new Stepper(PIN_STEP,PIN_DIR,RESET);
    pidStatus = true;
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
    miStepper->prepareMove(mmstepper);
}

void Pullup::goHome()
{
    if(misEndstops[A]->pressed())
    {
        misMotores[A]->setFree();
        misEncoders[A]->resetPosicion();
    }
    else
    {
        misMotores[A]->setPWM(55);
        misMotores[A]->setBack();
    }

    if(misEndstops[B]->pressed())
    {
        misMotores[B]->setFree();
        misEncoders[B]->resetPosicion();
    }
    else
    {
        misMotores[B]->setPWM(55);
        misMotores[B]->setBack();
    }

    if(misEndstops[C]->pressed())
    {
        misMotores[C]->setFree();
        misEncoders[C]->resetPosicion();
    }
    else
    {
        misMotores[C]->setPWM(55);
        misMotores[C]->setBack();
    }
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
    misMotores[A]->setFree();
    misMotores[B]->setFree();
    misMotores[C]->setFree();
    pidStatus = false;
    miStepper->disableStepper();
}

Endstop* Pullup::getEndstop(int queendstop)
{
    return misEndstops[queendstop];
}