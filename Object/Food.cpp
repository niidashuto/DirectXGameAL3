#include "Food.h"
#include "Affin.h"
#include <cassert>
#include "Enemy.h"
#include <random>
#include "Item.h"

#include "Player.h"

/// <summary>
/// 初期化
/// </summary>
void Food::Initialize(const Vector3& position, int tribe) {
	// モデル読み込み
	SetModel(tribe);

	// テクスチャ読み込み
	SetTexture(tribe);
	SetTribe(tribe);

	// ワールドトランスフォーム
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	worldTransform_.matWorld_ = Affin::matWorld(
		worldTransform_.translation_, worldTransform_.rotation_, worldTransform_.scale_);

	worldTransform_.TransferMatrix();
}

/// <summary>
/// 更新
/// </summary>
void Food::Update() {
	// プレイヤーのZ座標に合わせ、加工させる
	if (worldTransform_.translation_.y >= 35) {
		worldTransform_.translation_.z = -40.0f;
		worldTransform_.translation_.x = worldTransform_.translation_.x / 2;;
		velocity_ = { 0.0f, -0.2f,0.0f };
	}

	// 座標を移動させる (1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ += velocity_;

	// 行列の更新
	worldTransform_.matWorld_ = Affin::matWorld(
		worldTransform_.translation_, worldTransform_.rotation_, worldTransform_.scale_);
	worldTransform_.TransferMatrix();

	// 時間経過でデス
	if (worldTransform_.translation_.y <= -30.0f) {
		isDead_ = true;
	}
}

/// <summary>
/// 描画
/// </summary>
void Food::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

/// <summary>
/// 衝突を検知したら呼び出されるコールバック関数
/// </summary>
void Food::OnCollision() {
	
	// デス
	isDead_ = true;
}

/// <summary>
/// ワールド座標を取得
/// </summary>
Vector3 Food::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Food::SetTexture(int tribe) {
	switch (tribe)
	{
	case 0:
		textureHandle_ = TextureManager::Load("item/11banana.png");
		break;
	case 1:
		textureHandle_ = TextureManager::Load("item/1butaniku.png");
		break;
	case 2:
		textureHandle_ = TextureManager::Load("item/2gyuniku.png");
		break;
	case 3:
		textureHandle_ = TextureManager::Load("item/4tamago.png");
		break;
	case 4:
		textureHandle_ = TextureManager::Load("item/5retasu.png");
		break;
	case 5:
		textureHandle_ = TextureManager::Load("item/7tomato.png");
		break;
	case 6:
		textureHandle_ = TextureManager::Load("item/6imo.png");
		break;
	case 7:
		textureHandle_ = TextureManager::Load("item/8ninjin.png");
		break;
	case 8:
		textureHandle_ = TextureManager::Load("item/9tamanegi.png");
		break;
	case 9:
		textureHandle_ = TextureManager::Load("item/10kome.png");
		break;
	case 10:
		textureHandle_ = TextureManager::Load("materialTex/10.png");
		break;
	}
}

void Food::SetModel(int tribe) {
	switch (tribe) {
	case 0:
		model_ = Model::CreateFromOBJ("kyu", true);
		break;
	case 1:
		model_ = Model::CreateFromOBJ("kyu", true);
		break;
	case 2:
		model_ = Model::CreateFromOBJ("kyu", true);
		break;
	case 3:
		model_ = Model::CreateFromOBJ("kyu", true);
		break;
	case 4:
		model_ = Model::CreateFromOBJ("kyu", true);
		break;
	case 5:
		model_ = Model::CreateFromOBJ("kyu", true);
		break;
	case 6:
		model_ = Model::CreateFromOBJ("kyu", true);
		break;
	case 7:
		model_ = Model::CreateFromOBJ("kyu", true);
		break;
	case 8:
		model_ = Model::CreateFromOBJ("kyu", true);
		break;
	case 9:
		model_ = Model::CreateFromOBJ("kyu", true);
		break;
	case 10:
		model_ = Model::CreateFromOBJ("kyu", true);
	}
}

void Food::SetTribe(int tribe) {
	switch (tribe) {

	case Pig:
		tribe_ = BUTANIKU;
		break;
	case Cow:
		tribe_ = GYUNIKU;
		break;
	case Chicken:
		/*if (posDist(engine) <= 15) {
			tribe_ = toriniku;
		}*/

		tribe_ = TAMAGO;

		break;
	case Lettuce:
		tribe_ = RETASU;
		break;
	case Potato:
		tribe_ = IMO;
		break;
	case Tomato:
		tribe_ = TOMATO;
		break;
	case Carrot:
		tribe_ = NINNJINN;
		break;
	case Onion:
		tribe_ = TAMANEGI;
		break;
	case Rice:
		tribe_ = KOME;
		break;
	case Monkey:
		tribe_ = BANANA;
		break;
	}
}