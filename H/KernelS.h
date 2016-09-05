#ifndef _kernelsem_h_ 
#define _kernelsem_h_ 

class Semaphore;
class Lista;

class KernelSem
{
public:

	KernelSem(Semaphore* mySem, int initValue = 1);
	~KernelSem();

	void wait();
	void signal();
	int value() { return val; }
	Lista* getBlocked(){
		return blocked; 
	}
protected:

	void block();
	void deblock();

private:

	int val;
	Lista* blocked;
	Semaphore* mySem;
};

#endif
