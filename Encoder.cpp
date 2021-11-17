#include "Encoder.h"
#include "Parametros.h"

Encoder::Encoder(int canal_A, int canal_B, float grados_por_tic_)
{
    pin_canal_A = canal_A;
    pin_canal_B = canal_B;
    grados_por_tic = grados_por_tic_;
    posicion_tics = 0;
}

void Encoder::init()
{
    pinMode(pin_canal_A, INPUT_PULLUP);
    pinMode(pin_canal_B, INPUT_PULLUP);
}

void Encoder::actualizar_posicion()
{
    if(digitalRead(pin_canal_A) == HIGH)
    {
        if(digitalRead(pin_canal_B) == LOW)
            posicion_tics++;
        else
            posicion_tics--;
    }
    else
    {
        if(digitalRead(pin_canal_B) == LOW)
            posicion_tics--;
        else
            posicion_tics++;
    }

}


float Encoder::getPosicionGrados()
{
    return (posicion_tics/grados_por_tic);
}

int Encoder::getTics()
{
    return posicion_tics;
}

void Encoder::resetPosicion()
{
    posicion_grados = 0;
}

void Encoder::setPosicionGrados(int grados)
{
    posicion_tics = GRADOS_A_PULSOS(grados);
}