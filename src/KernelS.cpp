#include "KernelS.h"
#include "Lista.h"
#include "locks.h"
#include "SCHEDULE.h"
#include "PCB.h"
#include "Thread.h"

KernelSem::KernelSem(Semaphore* mySem, int ival)
{
	this->blocked = new Lista();
	this->mySem = mySem;
	this->val = ival;
	}

KernelSem::~KernelSem()
{
	delete blocked;
}

void KernelSem::wait(){
#ifndef BCC_BLOCK_IGNORE
	lock();
	if (--val < 0)
		block();
	unlock();
#endif
}

void KernelSem::signal(){
#ifndef BCC_BLOCK_IGNORE
	lock();
	if (val++ < 0)
		deblock();
	unlock();

#endif
}

void KernelSem::block(){
	PCB::running->stanje = PCB::Blokirana;
	blocked->dodaj(PCB::running);
	dispatch();
}

void KernelSem::deblock(){
	PCB* p = blocked->uzmiPrvi();
	p->stanje = PCB::Spremna;
	Scheduler::put(p);
}
