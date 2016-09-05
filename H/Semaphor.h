#ifndef _semaphore_h_
#define _semaphore_h_

class KernelSem;

class Semaphore {

public:

	Semaphore(int init = 1);

	virtual	~Semaphore();
	virtual void wait();
	virtual void signal();

	int val() const;  // Returns the current value of the semaphore

private:
	KernelSem* myImpl;
};
#endif