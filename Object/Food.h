#include "Model.h"
#include "WorldTransform.h"
#pragma once

enum FoodID {
	curry,
	yakiniku,
	medamayaki,
	nikujaga,
	salada
};

enum materialID {
	butaniku,
	gyuuniku,
	toriniku,
	tamago,
	retasu,
	imo,
	tomato,
	ninnjinn,
	tamanegi,
	kome
};

/// <summary>
/// 料理素材用クラス
/// </summary>
class Food {
private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 速度
	Vector3 velocity_ = { 0.0f,0.5f,0.0f };

	// デスフラグ
	bool isDead_ = false;


public:
	// 半径
	float r = 1.0f;

	bool IsDead() const { return isDead_; }
	void IsDeath() { isDead_ = true; }

	// texture を設定
	void SetTexture(int tribe);
	void SetModel(int tribe);

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const Vector3& position, int tribe);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// 衝突を検知したら呼び出されるコールバック関数
	/// </summary>
	void OnCollision();

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	Vector3 GetWorldPosition();
};
