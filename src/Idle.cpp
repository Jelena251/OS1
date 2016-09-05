#include "Idle.h"

Idle* Idle::idle = 0;

Idle::Idle() : Thread(128, 2) {}

PCB* Idle::getPcb()
{
	return myPCB;
}

void Idle::run()
{
	while (1);
}


