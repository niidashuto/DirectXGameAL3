#pragma once
#include "Affin.h"
#include "DebugText.h"
#include "EnemyBullet.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include <list>
#include <memory>
#include <sstream>

class Player;
class GameScene;
class Food;
struct ItemStrage {
	bool item;
	int tribe;
	ItemStrage* parent = nullptr;
};


class Item
{
private:
	//	ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	std::unique_ptr<Sprite> sprite2DItem;

	std::stringstream itemCommands;
	int itemTime = 0;
	bool stay;

	// input
	Input* input_ = nullptr;
	// debugText
	DebugText* debugText_ = nullptr;

	// 外部
	Player* player_ = nullptr;
	GameScene* gameScene_ = nullptr;
	Food* food_ = nullptr;

	//int item = 0b00000000000;
	ItemStrage* strage[5];

public:
	void Initialize();
	void Update();
	void Draw();
	void SpriteDraw();

	void AddItem(int tribe);

	void LoadItemData();
	void UpdateItemCommands(int num);
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



