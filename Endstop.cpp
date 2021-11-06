// 
// 
// 
#ifndef _ENDSTOP_
#define _ENDSTOP_

#include "Endstop.h"

void Endstop::init()
{
	pinMode(mypin, INPUT);

}

bool Endstop::pressed()
{
	if (digitalRead(mypin)) return true;
	else return false;
}

#endif

