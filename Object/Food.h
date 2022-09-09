#include "Model.h"
#include "WorldTransform.h"
#pragma once
class Player;

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
	int tribe_ = 0;
	Player* player_ = nullptr;

public:
	// 半径
	float r = 1.0f;

	bool IsDead() const { return isDead_; }
	void IsDeath() { isDead_ = true; }

	// texture を設定
	void SetTexture(int tribe);
	void SetModel(int tribe);
	void SetTribe(int T);
	int GetTribe() { return tribe_; }

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
