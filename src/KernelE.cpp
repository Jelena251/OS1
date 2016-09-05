#include "KernelE.h"
#include "EvLista.h"
#include "PCB.h"
#include "SCHEDULE.h"
#include "IVTEntry.h"

KernelEv::KernelEv(Event* myEvent, unsigned char ivtNo){
	this->myEvent = myEvent;
	this->ivtNo = ivtNo;
	this->val = 0;
	owner = PCB::running;

	if (IVTEntry::entries[ivtNo])
		IVTEntry::entries[ivtNo]->events->dodaj(this);
}

KernelEv::~KernelEv()
{
	if (IVTEntry::entries[ivtNo])
		IVTEntry::entries[ivtNo]->events->obrisi(this);
}

void KernelEv::wait(){
	if (owner != PCB::running) return;

#ifndef BCC_BLOCK_IGNORE
	lock();
	if (--val < 0) block();
	unlock();
#endif
}

void KernelEv::signal(){
#ifndef BCC_BLOCK_IGNORE
	lock();
	if (val++ < 0) deblock();
	unlock();
#endif
}

void KernelEv::deblock(){
	owner->stanje = PCB::Spremna;
	Scheduler::put(owner);
}

void KernelEv::block(){
	PCB::running->stanje = PCB::Blokirana;
	dispatch();
}


