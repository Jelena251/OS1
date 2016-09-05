#include "IVTEntry.h"
#ifndef BCC_BLOCK_IGNORE
#include <dos.h>
#endif
#include "EvLista.h"
#include "KernelE.h"
#include "Thread.h"

IVTEntry* IVTEntry::entries[256];
#ifndef BCC_BLOCK_IGNORE
IVTEntry::IVTEntry(unsigned char ivtNo, interPtr newRoutine)
{

	lock();
	this->ivtNo = ivtNo;
	this->events = new EvList();
	this->oldRoutine = getvect(ivtNo);
	setvect(ivtNo, newRoutine);
	IVTEntry::entries[ivtNo] = this;
	unlock();

}
#endif

IVTEntry::~IVTEntry()
{
#ifndef BCC_BLOCK_IGNORE
	lock();
	setvect(ivtNo, oldRoutine);
	delete events;
	IVTEntry::entries[ivtNo] = 0;
	unlock();
#endif
}


void IVTEntry::signal_all()
{
#ifndef BCC_BLOCK_IGNORE
	lock();
	for (EvList::Elem* tek = events->prvi; tek; tek = tek->sled)
	{
		tek->ev->signal();
	}
	unlock();
#endif
	dispatch();

}

