#include "Food.h"
#include "Affin.h"
#include <cassert>

/// <summary>
/// 初期化
/// </summary>
void Food::Initialize(Model* model, const Vector3& position) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	// textureHandle_ = TextureManager::Load("ddddog.png");
	textureHandle_ = TextureManager::Load("ddddog.png");

	// ワールドトランスフォーム
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	//worldTransform_.scale_ = {2, 2, 2};

	// worldTransform_.TransferMatrix();
}

/// <summary>
/// 更新
/// </summary>
void Food::Update() {

	// 座標を移動させる (1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ += velocity_;

	// 行列の更新
	worldTransform_.matWorld_ = Affin::matWorld(
		worldTransform_.translation_, worldTransform_.rotation_, worldTransform_.scale_);
	worldTransform_.TransferMatrix();

	if (worldTransform_.translation_.y >= 50) {
		worldTransform_.translation_.z = 0.0f;
		velocity_ = { 0.0f, -0.2f,0.0f };
	}

	// 時間経過でデス
	if (--dethTimer_ <= 0) {
		isDead_ = true;
	}
}

/// <summary>
/// 描画
/// </summary>
void Food::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
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
	//
	Vector3 worldPos;
	//
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}