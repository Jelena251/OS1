#ifndef _idle_h_
#define _idle_h_

#include "Thread.h"

class Idle : public Thread
{
public:
	Idle();

	static Idle* idle;


	PCB* getPcb();
	void run();
};

#endif

