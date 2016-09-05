#include "Event.h"
#include "KernelE.h"

Event::Event(IVTNo ivtNo){

	myImpl = new KernelEv(this, ivtNo);
}

Event::~Event(){
	delete myImpl;
}

void Event::wait(){
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}

