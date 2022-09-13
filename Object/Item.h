#pragma once
#include "Affin.h"
#include "DebugText.h"
#include "WorldTransform.h"
#include <cassert>
#include <sstream>
#include "Sprite.h"

enum FoodID {
	curry,
	yakiniku,
	medamayaki,
	nikujaga,
	salada,
	siotomato,
	omuraisu,
};

enum ItemID {
	BUTANIKU,
	GYUNIKU,
	TORINIKU,
	TAMAGO,
	RETASU,
	IMO,
	TOMATO,
	NINNJINN,
	TAMANEGI,
	KOME,
	BANANA,
	NONE
};

struct ItemStrage {
	bool item = false;
	int tribe = 0;
};

class Item
{
private:
	//テクスチャハンドル
	uint32_t itemTextureHandle1_[12];
	uint32_t ryouriTextureHandle1_[8];

	Sprite* spriteItem1[5];
	Sprite* spriteRyouri[5];
	Vector2 size = { 1.0f,1.0f };
	Vector2 pos = { 0.0f,0.0f };
	Vector2 move;
	Vector2 scale;

	int itemTime = 10;
	bool stay;

	DebugText* debugText_ = nullptr;

	int item = 0b0000000;
	ItemStrage strage[5];

private:

	void loadSprite();
	void setSizePosAllItem(Vector2 size);
	Sprite* choiceSpriteItem(int tribe);

public:
	void Initialize();
	void Update();
	void Draw();
	void SpriteDraw();

	void AddItem(int tribe);

	int CURRY();
	int YAKINIKU();
	int MEDAMAYAKI();
	int NIKUJAGA();
	int SALADA();
	int SIOTOMATO();
	int OMURAISU();
};