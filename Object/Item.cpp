#include "Item.h"





void Item::Initialize() {

	debugText_ = DebugText::GetInstance();

	//worldTransform_.Initialize();
	for (int i = 0; i < 5; i++) {
		strage[i].item = false;
		strage[i].tribe = 0;
	}

}
void Item::Update() {
	itemTime--;

	debugText_->SetPos(600, 300);
	debugText_->Printf("%d		%d	%d	%d	%d", strage[0].tribe, strage[1].tribe, strage[2].tribe, strage[3].tribe, strage[4].tribe);
}
void Item::Draw() {

}
void Item::SpriteDraw() {

}


void Item::AddItem(int tribe) {

	if (itemTime < 0) {
		if (strage[0].item == false) {
			strage[0].item = true;
			strage[0].tribe = tribe;
		}
		else if (strage[1].item == false) {
			strage[1].item = true;
			strage[1].tribe = tribe;
		}
		else if (strage[2].item == false) {
			strage[2].item = true;
			strage[2].tribe = tribe;
		}
		else if (strage[3].item == false) {
			strage[3].item = true;
			strage[3].tribe = tribe;
		}
		else if (strage[4].item == false) {
			strage[4].item = true;
			strage[4].tribe = tribe;
		}

		itemTime = 10;
	}

}

int Item::CURRY() {
	bool meet = false;
	bool nijin = false;
	bool tama = false;
	bool kome = false;
	int keepnum[4];
	int result = 0;

	for (int i = 0; i < 5; i++) {
		if (strage[i].tribe == BUTANIKU
			|| strage[i].tribe == GYUNIKU
			|| strage[i].tribe == TORINIKU
			&& meet == false) {
			meet = true;
			keepnum[0] = i;

		}
		if (strage[i].tribe == NINNJINN && nijin == false) {
			nijin = true;
			keepnum[1] = i;
		}if (strage[i].tribe == TAMANEGI && tama == false) {
			tama = true;
			keepnum[2] = i;
		}if (strage[i].tribe == KOME && kome == false) {
			kome = true;
			keepnum[3] = i;
		}
	}

	if (meet && nijin && tama && kome) {

		for (int i = 0; i < 4; i++) {
			strage[keepnum[i]].item = false;
			strage[keepnum[i]].tribe = NONE;
		}
		return result;
	}
}

int Item::YAKINIKU() {
	bool usimeet = false;
	bool butameet = false;
	bool torimeet = false;
	bool kome = false;
	int keepnum[4];
	int result = 0;

	for (int i = 0; i < 5; i++) {
		if (strage[i].tribe == BUTANIKU && butameet == false) {
			butameet = true;
			keepnum[0] = i;

		}
		if (strage[i].tribe == GYUNIKU && usimeet == false) {
			usimeet = true;
			keepnum[1] = i;
		}if (strage[i].tribe == TORINIKU && torimeet == false) {
			torimeet = true;
			keepnum[2] = i;
		}if (strage[i].tribe == KOME && kome == false) {
			kome = true;
			keepnum[3] = i;
		}
	}

	if (kome && butameet && usimeet && torimeet) {

		for (int i = 0; i < 4; i++) {
			strage[keepnum[i]].item = false;
			strage[keepnum[i]].tribe = NONE;
		}
		return result;
	}
}

int Item::MEDAMAYAKI() {
	bool egg1 = false;
	bool egg2 = false;
	bool butameet1 = false;
	bool butameet2 = false;
	int keepnum[4];
	int result = 0;

	for (int i = 0; i < 5; i++) {
		if (strage[i].tribe == BUTANIKU && butameet1 == false) {
			butameet1 = true;
			keepnum[0] = i;
		}
		if (strage[i].tribe == BUTANIKU && butameet2 == false) {
			butameet2 = true;
			keepnum[1] = i;
		}if (strage[i].tribe == TAMAGO && egg1 == false) {
			egg1 = true;
			keepnum[2] = i;
		}if (strage[i].tribe == TAMAGO && egg2 == false) {
			egg2 = true;
			keepnum[3] = i;
		}
	}

	if (butameet1 && butameet2 && egg1 && egg2) {
		for (int i = 0; i < 4; i++) {
			strage[keepnum[i]].item = false;
			strage[keepnum[i]].tribe = NONE;
		}
		return result;
	}
}

int Item::NIKUJAGA() {
	bool butameet = false;
	bool imo = false;
	bool ninjin = false;
	bool tama = false;
	int keepnum[4];
	int result = 0;

	for (int i = 0; i < 5; i++) {
		if (strage[i].tribe == BUTANIKU && butameet == false) {
			butameet = true;
			keepnum[0] = i;
		}
		if (strage[i].tribe == IMO && imo == false) {
			imo = true;
			keepnum[1] = i;
		}if (strage[i].tribe == NINNJINN && ninjin == false) {
			ninjin = true;
			keepnum[2] = i;
		}if (strage[i].tribe == TAMANEGI && tama == false) {
			tama = true;
			keepnum[3] = i;
		}
	}

	if (butameet && imo && ninjin && tama) {
		for (int i = 0; i < 4; i++) {
			strage[keepnum[i]].item = false;
			strage[keepnum[i]].tribe = NONE;
		}
		return result;
	}
}

int Item::SALADA() {
	bool letasu = false;
	bool tomato = false;
	bool ninjin = false;
	bool tama = false;
	int keepnum[4];
	int result = 0;

	for (int i = 0; i < 5; i++) {
		if (strage[i].tribe == RETASU && letasu == false) {
			letasu = true;
			keepnum[0] = i;
		}
		if (strage[i].tribe == TOMATO && tomato == false) {
			tomato = true;
			keepnum[1] = i;
		}if (strage[i].tribe == NINNJINN && ninjin == false) {
			ninjin = true;
			keepnum[2] = i;
		}if (strage[i].tribe == TAMANEGI && tama == false) {
			tama = true;
			keepnum[3] = i;
		}
	}

	if (letasu && tomato && ninjin && tama) {
		for (int i = 0; i < 4; i++) {
			strage[keepnum[i]].item = false;
			strage[keepnum[i]].tribe = NONE;
		}
		return result;
	}
}

int Item::SIOTOMATO() {
	bool tomato1 = false;
	bool tomato2 = false;
	bool tomato3 = false;
	bool tomato4 = false;
	int keepnum[4];
	int result = 0;

	for (int i = 0; i < 5; i++) {
		if (strage[i].tribe == TOMATO && tomato1 == false) {
			tomato1 = true;
			keepnum[0] = i;
		}
		if (strage[i].tribe == TOMATO && tomato2 == false) {
			tomato2 = true;
			keepnum[1] = i;
		}if (strage[i].tribe == TOMATO && tomato3 == false) {
			tomato3 = true;
			keepnum[2] = i;
		}if (strage[i].tribe == TOMATO && tomato4 == false) {
			tomato4 = true;
			keepnum[3] = i;
		}
	}

	if (tomato1 && tomato2 && tomato3 && tomato4) {
		for (int i = 0; i < 4; i++) {
			strage[keepnum[i]].item = false;
			strage[keepnum[i]].tribe = NONE;
		}
		return result;
	}
}

int Item::OMURAISU() {
	bool egg = false;
	bool tomato = false;
	bool kome = false;
	bool tama = false;
	int keepnum[4];
	int result = 0;

	for (int i = 0; i < 5; i++) {
		if (strage[i].tribe == TAMAGO && egg == false) {
			egg = true;
			keepnum[0] = i;
		}
		if (strage[i].tribe == TOMATO && tomato == false) {
			tomato = true;
			keepnum[1] = i;
		}if (strage[i].tribe == KOME && kome == false) {
			kome = true;
			keepnum[2] = i;
		}if (strage[i].tribe == TAMANEGI && tama == false) {
			tama = true;
			keepnum[3] = i;
		}
	}

	if (egg && tomato && kome && tama) {
		for (int i = 0; i < 4; i++) {
			strage[keepnum[i]].item = false;
			strage[keepnum[i]].tribe = NONE;
		}

		return result;
	}
}