
#ifndef _timer_h_
#define _timer_h_

#include "locks.h"

class Timer
{
public:
	static interPtr oldTimer;
	static void interrupt newTimer(...);
	static int vreme;
	static unsigned char zahtevana_promena_konteksta;

};


#endif

