#pragma once
#include "Affin.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include <list>
#include <memory>

#include "PlayerBullet.h"

/// <summary>
/// 自キャラ
/// </summary>
class Player {
  private:
	//	ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//レティクル用テクスチャ取得
	uint32_t textureReticle = TextureManager::Load("reticle2D.png");

	// input
	Input* input_ = nullptr;
	// debugText
	DebugText* debugText_ = nullptr;

	// 弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

	// カメラ座標用
	WorldTransform cameraWorldTransform_;

	// 3Dレティクル用ワールドトランスフォーム
	WorldTransform worldTransform3DReticle_;
	// 2Dレティクル用スプライト
	std::unique_ptr<Sprite> sprite2DReticle_;

	int hp = 100;
	int point = 0;
	bool isDead = false;

  public:
	float r = 1;

  public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(ViewProjection viewprojection, Model* model);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection viewProjection);

	/// <summary>
	/// 平行移動
	/// </summary>
	void Move();
	/// <summary>
	/// 回転移動
	/// </summary>
	void Rotate();

	/// <summary>
	/// 行列の計算
	/// </summary>
	void MatUpdate(WorldTransform& worldTransfom);

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	Vector3 GetWorldPosition();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack(Model* model);

	/// <summary>
	/// 衝突を検知したら呼び出されるコールバック関数
	/// </summary>
	void OnCollision();

	/// <summary>
	/// 弾の取得
	/// </summary>
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	/// <summary>
	/// ワールド行列の取得
	/// </summary>
	WorldTransform GetWorldTransform() { return worldTransform_; }

	/// <summary>
	/// 親オブジェクトの設定
	/// </summary>
	void SetParent(WorldTransform* worldTransform) { worldTransform_.parent_ = worldTransform; };

	/// <summary>
	/// UI描画
	/// </summary>
	void DrawUI();

	/// <summary>
	/// 自機のワールド座標から3Dレティクルのワールド座標を計算
	/// </summary>
	void WorldReticle();

	// 3Dレティクルのワールド座標から2Dレティクルのスクリーン座標を計算
	void Reticle(ViewProjection viewprojection);

	//  加算
	void AddPoint();

	/// <summary>
	/// point
	/// </summary>
	int GetPoint() { return point; }

	bool IsDead() const { return isDead; }
};
