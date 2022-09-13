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
	omuraisu
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
class Player;

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
	Sprite* spriteRyouri1[7];
	Vector2 size = { 0.5f,0.5f };
	Vector2 posItem = { 0.0f,0.0f };
	Vector2 move;
	Vector2 scale;
	Vector2 anchor;

	Vector2 moveRyo;
	Vector2 sizeRyo = { 1.0f,1.0f };
	Vector2 posRyo;
	Vector2 scaleRyo;
	Vector2 anchorRyo;

	int itemTime = 10;
	bool stay;
	bool ryouri[7];

	DebugText* debugText_ = nullptr;

	int item = 0b0000000;
	ItemStrage strage[5];
	Player* player_;

	int buffDrawTime[7];

private:
	void loadSprite();
	void setSizePosAllItem(Vector2 size);
	void setSizePosRyouri(Vector2 size);
	Sprite* choiceSpriteItem(int tribe);
	void spriteRyouri();

public:
	void Initialize();
	void Update();
	void Draw();
	void SpriteDraw();

	void AddItem(int tribe);
	void Replacement(int tribe);
	void DrawFlag(int num){ 
		ryouri[num] = true;
		buffDrawTime[num] = 900;
	}
	void DrawDEFlag(int num){ ryouri[num] = false; }

	int CURRY();
	int YAKINIKU();
	int MEDAMAYAKI();
	int NIKUJAGA();
	int SALADA();
	int SIOTOMATO();
	int OMURAISU();
};

enum Buff {
	POWERBUFF = 1 << 0,
	SPEEDBUFF = 1 << 1,
	TWOWAY = 1 << 2,
	THREEWAY = 1 << 3,
	POWERDEBUFF = 1 << 4,
	SPEEDDEBUFF = 1 << 5
};