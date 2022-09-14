#include "Item.h"
#include "TextureManager.h"
#include "Player.h"

void Item::Initialize() {

	debugText_ = DebugText::GetInstance();

	anchor = { 500,600 };
	anchorRyo = { 430,500 };

	//worldTransform_.Initialize();
	for (int i = 0; i < 5; i++) {
		strage[i].item = false;
		strage[i].tribe = 11;
	}

	loadSprite();

	//
	for (int i = 0; i < 5; i++)
	{
		spriteItem1[i] = Sprite::Create(itemTextureHandle1_[11], anchor);
	}
	for (int i = 0; i < 5; i++)
	{
		spriteItem1[i] = choiceSpriteItem(strage[i].tribe);
	}
	for (int i = 0; i < 7; i++)
	{
		spriteRyouri1[i] = Sprite::Create(ryouriTextureHandle1_[i], anchorRyo);
	}

	scale = spriteItem1[0]->GetSize();
  


	posItem = spriteItem1[0]->GetPosition();
	scaleRyo = spriteRyouri1[0]->GetSize();
	posRyo = spriteRyouri1[0]->GetPosition();

	/*for (int i = 0; i < 7; i++) {
			ryouri[i] = false;
		}*/

}
void Item::Update() {
	itemTime--;

	for (int i = 0; i < 5; i++)
	{
		spriteItem1[i] = choiceSpriteItem(strage[i].tribe);
	}
	for (int i = 0; i < 7; i++)
	{
		buffDrawTime[i] -= 1;
	}
	setSizePosAllItem(size);
	setSizePosRyouri(sizeRyo);

	// debugText_->SetPos(600, 300);
	// debugText_->Printf("%d	%d	%d	%d	%d", strage[0].tribe, strage[1].tribe, strage[2].tribe, strage[3].tribe, strage[4].tribe);

}
void Item::Draw() {

}
void Item::SpriteDraw() {

	for (int i = 0; i < 5; i++)
	{
		spriteItem1[i]->Draw();
	}
	spriteRyouri();

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
		else {
			Replacement(tribe);
		}

		itemTime = 10;
	}

}

void Item::Replacement(int tribe) {
	strage[0].item = false;
	strage[0].tribe = NONE;

	for (int i = 0; i < 4; i++) {
		strage[i].item = strage[i + 1].item;
		strage[i].tribe = strage[i + 1].tribe;
	}

	strage[4].item = true;
	strage[4].tribe = tribe;
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
		return true;
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
		return true;
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
		return true;
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
		return true;
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
		return true;
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
		return true;
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

		return true;
	}
}
void Item::loadSprite() {

	itemTextureHandle1_[0] = TextureManager::Load("item/1butaniku.png");
	itemTextureHandle1_[1] = TextureManager::Load("item/2gyuniku.png");
	itemTextureHandle1_[2] = TextureManager::Load("item/3toriniku.png");
	itemTextureHandle1_[3] = TextureManager::Load("item/4tamago.png");
	itemTextureHandle1_[4] = TextureManager::Load("item/5retasu.png");
	itemTextureHandle1_[5] = TextureManager::Load("item/6imo.png");
	itemTextureHandle1_[6] = TextureManager::Load("item/7tomato.png");
	itemTextureHandle1_[7] = TextureManager::Load("item/8ninjin.png");
	itemTextureHandle1_[8] = TextureManager::Load("item/9tamanegi.png");
	itemTextureHandle1_[9] = TextureManager::Load("item/10kome.png");
	itemTextureHandle1_[10] = TextureManager::Load("item/11banana.png");
	itemTextureHandle1_[11] = TextureManager::Load("none.png");

	ryouriTextureHandle1_[0] = TextureManager::Load("ryouri/1carry.png");
	ryouriTextureHandle1_[1] = TextureManager::Load("ryouri/2yakiniku.png");
	ryouriTextureHandle1_[2] = TextureManager::Load("ryouri/3medamayaki.png");
	ryouriTextureHandle1_[3] = TextureManager::Load("ryouri/4nikujaga.png");
	ryouriTextureHandle1_[4] = TextureManager::Load("ryouri/5sarada.png");
	ryouriTextureHandle1_[5] = TextureManager::Load("ryouri/6siotomato.png");
	ryouriTextureHandle1_[6] = TextureManager::Load("ryouri/7omuraisu.png");
	ryouriTextureHandle1_[7] = TextureManager::Load("none.png");

}

void Item::setSizePosAllItem(Vector2 size) {
	Vector2 size_;
	size_ = scale;
	move = posItem;
	size_.x *= size.x;
	size_.y *= size.y;
	for (int i = 0; i < 5; i++) {
		spriteItem1[i]->SetSize(size_);
		spriteItem1[i]->SetPosition(move);
		move.x += 64;
	}
}
void Item::setSizePosRyouri(Vector2 size) {
	Vector2 size_;

	size_ = scaleRyo;
	moveRyo = posRyo;
	size_.x *= size.x;
	size_.y *= size.y;
	for (int i = 0; i < 7; i++) {
		spriteRyouri1[i]->SetSize(size_);
		spriteRyouri1[i]->SetPosition(moveRyo);
		moveRyo.x += 64;
	}
}



Sprite* Item::choiceSpriteItem(int tribe) {

	switch (tribe)
	{
	case 0:
		return Sprite::Create(itemTextureHandle1_[0], anchor);
	case 1:
		return Sprite::Create(itemTextureHandle1_[1], anchor);
	case 2:
		return Sprite::Create(itemTextureHandle1_[2], anchor);
	case 3:
		return Sprite::Create(itemTextureHandle1_[3], anchor);
	case 4:
		return Sprite::Create(itemTextureHandle1_[4], anchor);
	case 5:
		return Sprite::Create(itemTextureHandle1_[5], anchor);
	case 6:
		return Sprite::Create(itemTextureHandle1_[6], anchor);
	case 7:
		return Sprite::Create(itemTextureHandle1_[7], anchor);
	case 8:
		return Sprite::Create(itemTextureHandle1_[8], anchor);
	case 9:
		return Sprite::Create(itemTextureHandle1_[9], anchor);
	case 10:
		return Sprite::Create(itemTextureHandle1_[10], anchor);
	case 11:
		return Sprite::Create(itemTextureHandle1_[11], anchor);

	}

}

void Item::spriteRyouri() {
	for (int i = 0; i < 7; i++)
	{
		if (ryouri[i] == true&& 0<=buffDrawTime[i]) {
			spriteRyouri1[i]->Draw();
		}
	}
}
