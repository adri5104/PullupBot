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
}

void Pullup::init()
{
    int i;
    for(i=0; i<3; i++)
    {
        misMotores[i]->init();
        misEncoders[i]->init();
        misEndstops[i]->init();
    }
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