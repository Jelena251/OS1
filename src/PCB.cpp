#include "PCB.h"

#ifndef BCC_BLOCK_IGNORE
#include <dos.h>
#endif
#include "Semaphor.h"
#include "Lista.h"
#include "locks.h"


ID PCB::inic = 0;
PCB* PCB::running = 0;
Lista* PCB::listaUspavanih = new Lista();

#ifndef BCC_BLOCK_IGNORE
PCB::PCB(StackSize stackSize, Time timeSlice, Thread* myThread)
{
	this->stackSize = stackSize;
	this->timeSlice = timeSlice;
	this->myThread = myThread;
	id = ++inic;
	this->stack = 0;
	semWaitToComplete = new Semaphore(0);

}
#endif
PCB::~PCB()
{
	delete[] stack;
	delete semWaitToComplete;
}

#ifndef BCC_BLOCK_IGNORE
void PCB::create_stack()
{
	stack = new unsigned[stackSize];
	stack[stackSize - 1] = 0x200;
	stack[stackSize - 2] = FP_SEG(PCB::wrapper);
	stack[stackSize - 3] = FP_OFF(PCB::wrapper);
	this->ss = FP_SEG(&stack[stackSize - 12]);
	this->sp = FP_OFF(&stack[stackSize - 12]);
	this->bp = FP_OFF(&stack[stackSize - 12]);
}
#endif

void PCB::wrapper()
{
	PCB::running->myThread->run();

#ifndef BCC_BLOCK_IGNORE
	lock();
#endif
	PCB::running->stanje = PCB::Zavrsila;

	while (PCB::running->semWaitToComplete->val() < 0)
		PCB::running->semWaitToComplete->signal();

	dispatch();
}
