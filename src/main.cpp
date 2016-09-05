#include "Timer.h"
#ifndef BCC_BLOCK_IGNORE
#include <dos.h>
#endif
#include "Idle.h"
#include "PCB.h"

extern int userMain(int argc, char* argv[]);

void main(int argc, char* argv[])
{
#ifndef BCC_BLOCK_IGNORE
	Timer::oldTimer = getvect(8);
	setvect(8, Timer::newTimer);
#endif

	Idle::idle = new Idle();
	Idle::idle->start();

	PCB::running = new PCB(0, 0, 0);

	userMain(argc, argv);
#ifndef BCC_BLOCK_IGNORE
	setvect(8, Timer::oldTimer);
#endif
}
