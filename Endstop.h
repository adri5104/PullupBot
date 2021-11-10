// Endstop.h
// Por Adrian Rieker.
// Controla si el final de carrera esta pulsado o no.

#ifndef _Endstop_h
#define _Endstop_h

#include<Arduino.h>
class Endstop
{
 protected:
	 int mypin;
 public:
	void init();
	Endstop(int pin) { mypin = pin; };
	bool pressed();
};



#endif

