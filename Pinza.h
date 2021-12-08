#ifndef PINZA
#define PINZA

#include "Servo.h"

class Pinza {

public:

    bool estado; //Estado 1= Cerrado, Estado 2= Abierto


    Pinza();
    void move();
    bool getStado(); //la que envia la posicion en cada instante a matlab
    void setStado(bool);
    void Servinit(int);
    
private:
    int pinza_pin;
    Servo pinza;

};


#endif