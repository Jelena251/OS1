#ifndef _ivtentry_h
#define _ivtentry_h

#include "locks.h"

class EvList;

class IVTEntry
{
public:
	IVTEntry(unsigned char ivtNo, interPtr newRoutine);
	~IVTEntry();

	unsigned char ivtNo;
	interPtr oldRoutine;
	EvList* events;

	void signal_all();

	static IVTEntry* entries[];


};

#endif // !_ivtentry_h

