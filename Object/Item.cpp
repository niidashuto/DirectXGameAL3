#include "Item.h"





void Item::Initialize() {

	//debugText_ = DebugText::GetInstance();

	//worldTransform_.Initialize();
	for (int i = 0; i < 5; i++) {
		strage[i]->item = false;
		strage[i]->tribe = 0;
	}

}
void Item::Update() {


}
void Item::Draw() {

}
void Item::SpriteDraw() {

}

void Item::AddItem(int tribe) {

	if (strage[0]->item == false) {
		strage[0]->item = true;
		strage[0]->tribe = tribe;
		
	}
	else if (strage[1]->item == false) {
		strage[1]->item = true;
		strage[1]->tribe = tribe;
		strage[1]->parent_ = strage[0];
	}
	else if (strage[2]->item == false) {
		strage[2]->item = true;
		strage[2]->tribe = tribe;
	}
	else if (strage[3]->item == false) {
		strage[3]->item = true;
		strage[3]->tribe = tribe;
	}
	else if (strage[4]->item == false) {
		strage[4]->item = true;
		strage[4]->tribe = tribe;
	}

}

int Item::CURRY(){
	bool meet;
	bool nijin;
	bool tama;
	bool kome;
	int keepnum[4];
	int result;
	
	for (int i = 0; i < 5; i++) {
		if (strage[i]->tribe == BUTANIKU 
			||strage[i]->tribe == GYUNIKU
			||strage[i]->tribe == TORINIKU
			&&meet==false) {
			meet = true;
			keepnum[0] = i;

		}
		if (strage[i]->tribe == NINNJINN && nijin == false) {
			nijin = true;
			keepnum[1] = i;
		}if (strage[i]->tribe == TAMANEGI && tama == false) {
			tama = true;
			keepnum[2] = i;
		}if (strage[i]->tribe == KOME && kome == false) {
			kome = true;
			keepnum[3] = i;
		}
	}
	
	if (meet && nijin && tama && kome) {

		for (int i = 0; i < 4; i++) {
			strage[keepnum[i]]->item = false;
			strage[keepnum[i]]->tribe = NONE;
		}
		return result;
	}
}

int Item::YAKINIKU(){
	bool usimeet;
	bool butameet;
	bool torimeet;
	bool kome;
	int keepnum[4];
	int result;

	for (int i = 0; i < 5; i++) {
		if (strage[i]->tribe == BUTANIKU && butameet == false) {
			butameet = true;
			keepnum[0] = i;

		}
		if (strage[i]->tribe == GYUNIKU && usimeet == false) {
			usimeet = true;
			keepnum[1] = i;
		}if (strage[i]->tribe == TORINIKU && torimeet == false) {
			torimeet = true;
			keepnum[2] = i;
		}if (strage[i]->tribe == KOME && kome == false) {
			kome = true;
			keepnum[3] = i;
		}
	}

	if (kome && butameet && usimeet && torimeet) {

		for (int i = 0; i < 4; i++) {
			strage[keepnum[i]]->item = false;
			strage[keepnum[i]]->tribe = NONE;
		}
		return result;
	}
}

int Item::MEDAMAYAKI(){
	bool egg1;
	bool egg2;
	bool butameet1;
	bool butameet2;
	int keepnum[4];
	int result;

	for (int i = 0; i < 5; i++) {
		if (strage[i]->tribe == BUTANIKU && butameet1 == false) {
			butameet1 = true;
			keepnum[0] = i;
		}
		if (strage[i]->tribe == BUTANIKU && butameet2 == false) {
			butameet2 = true;
			keepnum[1] = i;
		}if (strage[i]->tribe == TAMAGO && egg1 == false) {
			egg1 = true;
			keepnum[2] = i;
		}if (strage[i]->tribe == TAMAGO && egg2 == false) {
			egg2 = true;
			keepnum[3] = i;
		}
	}

	if (butameet1 && butameet2 && egg1 && egg2 ) {
		for (int i = 0; i < 4; i++) {
			strage[keepnum[i]]->item = false;
			strage[keepnum[i]]->tribe = NONE;
		}
		return result;
	}
}

int Item::NIKUJAGA(){	
	bool butameet;
	bool imo;
	bool ninjin;
	bool tama;
	int keepnum[4];
	int result;

	for (int i = 0; i < 5; i++) {
		if (strage[i]->tribe == BUTANIKU && butameet == false) {
			butameet = true;
			keepnum[0] = i;
		}
		if (strage[i]->tribe == IMO && imo == false) {
			imo = true;
			keepnum[1] = i;
		}if (strage[i]->tribe == NINNJINN && ninjin == false) {
			ninjin = true;
			keepnum[2] = i;
		}if (strage[i]->tribe == TAMANEGI && tama == false) {
			tama = true;
			keepnum[3] = i;
		}
	}

	if (butameet && imo && ninjin && tama) {
		for (int i = 0; i < 4; i++) {
			strage[keepnum[i]]->item = false;
			strage[keepnum[i]]->tribe = NONE;
		}
		return result;
	}
}

int Item::SALADA(){
	bool letasu;
	bool tomato;
	bool ninjin;
	bool tama;
	int keepnum[4];
	int result;

	for (int i = 0; i < 5; i++) {
		if (strage[i]->tribe == RETASU && letasu == false) {
			letasu = true;
			keepnum[0] = i;
		}
		if (strage[i]->tribe == TOMATO && tomato == false) {
			tomato = true;
			keepnum[1] = i;
		}if (strage[i]->tribe == NINNJINN && ninjin == false) {
			ninjin = true;
			keepnum[2] = i;
		}if (strage[i]->tribe == TAMANEGI && tama == false) {
			tama = true;
			keepnum[3] = i;
		}
	}

	if (letasu && tomato && ninjin && tama) {
		for (int i = 0; i < 4; i++) {
			strage[keepnum[i]]->item = false;
			strage[keepnum[i]]->tribe = NONE;
		}
		return result;
	}
}

int Item::SIOTOMATO(){
	bool tomato1;
	bool tomato2;
	bool tomato3;
	bool tomato4;
	int keepnum[4];
	int result;

	for (int i = 0; i < 5; i++) {
		if (strage[i]->tribe == TOMATO && tomato1 == false) {
			tomato1 = true;
			keepnum[0] = i;
		}
		if (strage[i]->tribe == TOMATO && tomato2 == false) {
			tomato2 = true;
			keepnum[1] = i;
		}if (strage[i]->tribe == TOMATO && tomato3 == false) {
			tomato3 = true;
			keepnum[2] = i;
		}if (strage[i]->tribe == TOMATO && tomato4 == false) {
			tomato4 = true;
			keepnum[3] = i;
		}
	}

	if (tomato1 && tomato2 && tomato3 && tomato4) {
		for (int i = 0; i < 4; i++) {
			strage[keepnum[i]]->item = false;
			strage[keepnum[i]]->tribe = NONE;
		}
		return result;
	}
}

int Item::OMURAISU() {
	bool egg;
	bool tomato;
	bool kome;
	bool tama;
	int keepnum[4];
	int result;

	for (int i = 0; i < 5; i++) {
		if (strage[i]->tribe == TAMAGO && egg == false) {
			egg = true;
			keepnum[0] = i;
		}
		if (strage[i]->tribe == TOMATO && tomato == false) {
			tomato = true;
			keepnum[1] = i;
		}if (strage[i]->tribe == KOME && kome == false) {
			kome = true;
			keepnum[2] = i;
		}if (strage[i]->tribe == TAMANEGI && tama == false) {
			tama = true;
			keepnum[3] = i;
		}
	}

	if (egg && tomato && kome && tama) {
		for (int i = 0; i < 4; i++) {
			strage[keepnum[i]]->item = false;
			strage[keepnum[i]]->tribe = NONE;
		}

		return result;
	}
}
