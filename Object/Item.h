#pragma once
#include "Affin.h"
#include "DebugText.h"
#include "WorldTransform.h"
#include <cassert>
#include <sstream>

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
	ItemStrage* parent_ = nullptr;
};


class Item
{
private:
	//	ワールド変換データ
	//WorldTransform worldTransform_;

	//テクスチャハンドル
	//uint32_t textureHandle_ = 0u;

	//std::unique_ptr<Sprite> sprite2DItem;

	int itemTime = 0;
	bool stay;

	//DebugText* debugText_ = nullptr;

	

	int item = 0b0000000;
	ItemStrage* strage[5];

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


const int Tamago	= 0b1000000;
const int Retasu	= 0b0100000;
const int Imo		= 0b0010000;
const int Tomato	= 0b0001000;
const int Ninnjinn	= 0b0000100;
const int Tamanegi	= 0b0000010;
const int Kome		= 0b0000001;



