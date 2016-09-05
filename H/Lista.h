#ifndef _lista_h_
#define _lista_h_

class PCB;
class Lista{
protected:
	struct Elem{
		PCB* pcb;
		Elem* sled;
		Elem(PCB* p){
			pcb=p;
			sled=0;
		}
		
	};
private:
	Elem *prvi,* posl;


public:
	Lista(){
			prvi=posl=0;
		}
	void dodaj(PCB* pcb);
	PCB* uzmiPrvi();
	void obrisi(PCB* pcb);
	void dodajSort(PCB* p);
	Elem* first(){
		return prvi;
	}
	~Lista(){
			delete prvi; delete posl;
		}
protected:
	friend void main(int argc, char* argv[]);
	friend class PCB;
	friend class Timer;
};

#endif
