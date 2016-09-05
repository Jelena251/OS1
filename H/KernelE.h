#ifndef _kernelev_h_ 
#define _kernelev_h_

class Event;
class PCB;

class KernelEv{
public:
	KernelEv(Event* myEvent, unsigned char ivtNo);
	~KernelEv();

	void wait();
	void signal();
	Event* getEvent(){
		return myEvent;
	}
	int getivtNo(){
		return ivtNo;
	}
	int getVal(){
		return val;
	}
private:
	Event* myEvent;
	unsigned char ivtNo;
	int val;

	PCB* owner;

protected:
	void deblock();
	void block(); 
	
};

#endif
