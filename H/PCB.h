#ifndef _pcb_h_
#define _pcb_h_

#include "Thread.h"

class Semaphore;
class Lista;

class PCB
{


private:
	StackSize stackSize;
	Time timeSlice;
	Thread* myThread;
	ID id;
	static ID inic;
	Time timeToSleep;




public:
	PCB(StackSize stackSize, Time timeSlice, Thread* myThread);
		~PCB();
	void create_stack();
	Time gettimeToSleep(){
		return timeToSleep;
	}
	void settimeToSleep(Time t){
			timeToSleep=t;
		}
	Time gettimeSlice(){
		return timeSlice;
	}
	void settimeSlice(Time t){
			timeSlice=t;
		}
	static void wrapper();

	enum States { Nova, Spremna, Blokirana, Zavrsila };
	States stanje;
	static Lista* listaUspavanih;
		static PCB* running;
	Semaphore* semWaitToComplete;

	unsigned* stack;
	unsigned sp;
	unsigned ss;
	unsigned bp;


};

#endif

