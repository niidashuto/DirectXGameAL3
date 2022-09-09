#include "Item.h"



void Item::Initialize() {

	//debugText_ = DebugText::GetInstance();

	//worldTransform_.Initialize();
	for (int i = 0; i < 5; i++) {
		strage[i].item = false;
		strage[i].tribe = 0;
	}

}
void Item::Update() {


}
void Item::Draw() {

}
void Item::SpriteDraw() {

}

void Item::AddItem(int tribe) {

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
	}
	else if (strage[3].item == false) {
		strage[3].item = true;
		strage[3].tribe = tribe;
	}
	else if (strage[4].item == false) {
		strage[4].item = true;
		strage[4].tribe = tribe;
	}

}

void Item::CURRY(){}

void Item::YAKINIKU(){}

void Item::MEDAMAYAKI(){}

void Item::NIKUJAGA(){}

void Item::SALADA(){}

void Item::SIOTOMATO(){}

void Item::OMURAISU() {

}
