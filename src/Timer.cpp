#include "Timer.h"
#include "Lista.h"
#include "PCB.h"

#ifndef BCC_BLOCK_IGNORE
#include <dos.h>
#endif
#include "SCHEDULE.H"
#include "Idle.h"

interPtr Timer::oldTimer = 0;
int Timer::vreme = 0;
unsigned char Timer::zahtevana_promena_konteksta = 0;

extern void tick();

void interrupt Timer::newTimer(...)
{
	if (zahtevana_promena_konteksta == 0) //pozvao CPU
	{
		Timer::oldTimer();
		Timer::vreme++;
		tick();

		if (PCB::listaUspavanih->prvi)
		{
			PCB::listaUspavanih->prvi->pcb->settimeToSleep(PCB::listaUspavanih->prvi->pcb->gettimeToSleep()-1);
			while (PCB::listaUspavanih->prvi && PCB::listaUspavanih->prvi->pcb->gettimeToSleep() == 0)
			{
				PCB* pcb = PCB::listaUspavanih->uzmiPrvi();
				pcb->stanje = PCB::Spremna;
				Scheduler::put(pcb);
			}
		}
	}

#ifndef BCC_BLOCK_IGNORE
	//ako je vreme isteklo ili je neko pozvao dispatch, menjam kontekst
	if (Timer::vreme == PCB::running->gettimeSlice() && PCB::running->gettimeSlice() != 0 || zahtevana_promena_konteksta == 1)
	{
		PCB::running->sp = _SP;
		PCB::running->ss = _SS;
		PCB::running->bp = _BP;


		if (PCB::running->stanje == PCB::Spremna && PCB::running != Idle::idle->getPcb())
			Scheduler::put(PCB::running);


		PCB::running = Scheduler::get();

		if (PCB::running == 0)
			PCB::running = Idle::idle->getPcb();


		_SP = PCB::running->sp;
		_SS = PCB::running->ss;
		_BP = PCB::running->bp;

		Timer::vreme = 0;
		Timer::zahtevana_promena_konteksta = 0;
	}

#endif


}
