#include "KernelE.h"
#include "EvLista.h"

//lista za dogadjaje
void EvList::dodaj(KernelEv *e){
	Elem* novi=new Elem(e);
	novi->sled=0;
	if(prvi==0){
		prvi=novi;
	}else{
		//ako prvi nije 0 nije ni poslednji
		posl->sled=novi;
	}
	posl=novi;
}

KernelEv* EvList::uzmiPrvi(){
	KernelEv* res=0;
	if(prvi!=0){
	res=prvi->ev;
	Elem *pom=prvi;
	if(posl==prvi) posl=0; //imali smo samo jedan element
	prvi=prvi->sled;
	delete pom;
	}
 	return res;
}

void EvList::obrisi(KernelEv* e){
	Elem* pom=prvi;
	Elem* preth=0;
	while(pom!=0){
		if(pom->ev==e){

			if(preth!=0){
				preth->sled=pom->sled;
			}else{
				prvi=pom->sled;
			}

			if(posl==pom){
				posl=preth; //ako je prvi onda ce da bude null posle ovog
			}
			delete pom;
			pom=0;
		}else{
			preth=pom;
			pom=pom->sled;
		}
	}
}
