#include "Thread.h"
#include "PCB.h"
#include "Timer.h"
#include "locks.h"
#include "SCHEDULE.H"
#include "Semaphor.h"
#include "Lista.h"

Thread::Thread(StackSize stackSize, Time timeSlice)
{
	myPCB = new PCB(stackSize, timeSlice, this);
}

Thread::~Thread()
{
	waitToComplete();
	delete myPCB;
}

void Thread::sleep(Time timeToSleep)
{

#ifndef BCC_BLOCK_IGNORE
	lock();

	PCB::running->settimeToSleep(timeToSleep);
	PCB::running->stanje = PCB::Blokirana;
	PCB::listaUspavanih->dodajSort(PCB::running);
	dispatch();
	unlock();
#endif
}

void Thread::start()
{
	myPCB->create_stack();
	myPCB->stanje = PCB::Spremna;
	Scheduler::put(myPCB);
}

void Thread::waitToComplete()
{
	if (this->myPCB->stanje != PCB::Zavrsila)
		myPCB->semWaitToComplete->wait();
}

void dispatch()
{
#ifndef BCC_BLOCK_IGNORE
	lock();
	Timer::zahtevana_promena_konteksta = 1;
	Timer::newTimer();
	unlock();
#endif
}
