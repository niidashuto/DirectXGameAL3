#pragma once
#include "Affin.h"
#include "DebugText.h"
#include "WorldTransform.h"
#include <cassert>
#include <sstream>


struct ItemStrage {
	bool item = false;
	int tribe = 0;
	
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
	ItemStrage strage[5];

public:
	void Initialize();
	void Update();
	void Draw();
	void SpriteDraw();

	void AddItem(int tribe);

	//void SendItem();

	void CURRY();
	void YAKINIKU();
	void MEDAMAYAKI();
	void NIKUJAGA();
	void SALADA();
	void SIOTOMATO();
	void OMURAISU();


};

//const int Butaniku = 0b1000000000;
//const int Gyuuniku = 0b0100000000;
//const int Toriniku = 0b0010000000;
//const int Tamago = 0b0001000000;
//const int Retasu = 0b0000100000;
//const int Imo = 0b0000010000;
//const int Tomato = 0b0000001000;
//const int Ninnjinn = 0b0000000100;
//const int Tamanegi = 0b0000000010;
//const int Kome = 0b0000000001;



