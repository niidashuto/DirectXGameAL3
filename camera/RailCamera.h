#pragma once
#include "Affin.h"
#include "DebugText.h"
#include "Input.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Player;

/// <summary>
/// レールカメラ
/// </summary>
class RailCamera {
  private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	DebugText* debugText_ = nullptr;
	Input* input_ = nullptr;

	float focalLengs = 60;

  public:
	// fov(画角変更)関数
	float FieldOfViewY(float focalLengs, float sensor);

	/// <summary>
	/// 描画
	/// </summary>
	void Initialize(Vector3 wTrans, Vector3 rad);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(Player* player);

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	/// <summary>
	/// 回転
	/// </summary>
	void Rotate();

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	Vector3 GetWorldPosition();

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	WorldTransform* GetWorldTransform() { return &worldTransform_; }

	/// <returns>ビュープロジェクション</returns>
	const ViewProjection& GetViewProjection() { return viewProjection_; }
};
