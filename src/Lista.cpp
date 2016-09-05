#include "Lista.h"

#include "pcb.h"

void Lista::dodaj(PCB *pcb){
	Elem* novi=new Elem(pcb);
	novi->sled=0;
	if(prvi==0){
		prvi=novi;
	}else{
		//ako prvi nije 0 nije ni poslednji
		posl->sled=novi;
	}
	posl=novi;
}

PCB* Lista::uzmiPrvi(){
	PCB* res=0;
	if(prvi!=0){
	res=prvi->pcb;
	Elem *pom=prvi;
	if(posl==prvi) posl=0; //imali smo samo jedan element
	prvi=prvi->sled;
	delete pom;
	}
 	return res;
}

void Lista::obrisi(PCB* pcb){
	Elem* pom=prvi;
	Elem* preth=0;
	while(pom!=0){
		if(pom->pcb==pcb){

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


void Lista::dodajSort(PCB* pcb){
	Elem* novi=new Elem(pcb);

	if(prvi==0) {
		prvi=novi;
		posl=novi;
	}else{
		Elem* tek=prvi;
		Elem* preth=0;
		while(tek){
			if(tek->pcb->gettimeToSleep()<novi->pcb->gettimeToSleep()){
			novi->pcb->settimeToSleep(novi->pcb->gettimeToSleep()-tek->pcb->gettimeToSleep());
			preth=tek;
			tek=tek->sled;
			}else{break;}
		}
		if(!tek){ 
			posl->sled=novi;
			posl=novi;
		}else{ 
			if(tek==prvi){
			tek->pcb->settimeToSleep(tek->pcb->gettimeToSleep()-novi->pcb->gettimeToSleep());
			novi->sled=tek;
			prvi=novi;
			}else{
			preth->sled=novi;
			novi->sled=tek;
			tek->pcb->settimeToSleep(tek->pcb->gettimeToSleep()-novi->pcb->gettimeToSleep());
			}
		}
	}
}
