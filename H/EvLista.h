#ifndef _EvList_h_
#define _EvList_h_
class KernelEv;

class EvList{
	public:
	struct Elem{
		KernelEv* ev;
		Elem* sled;
		Elem(KernelEv* e){
			ev=e;
			sled=0;
		}
	};
	Elem *prvi, *posl;
	EvList(){ //konstruktor
		prvi=0;
		posl=0;
	}
	//jel treba destruktor
	void dodaj(KernelEv* e);
	KernelEv* uzmiPrvi();
	void obrisi(KernelEv* e);
};

#endif
