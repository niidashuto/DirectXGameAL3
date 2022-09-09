#include "Enemy.h"
#include "Player.h"
#include "GameScene.h"
const float PI = 3.1415;
/// <summary>
/// 初期化
/// </summary>
void Enemy::Initialize(Model* model, Vector3 trans) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み

	//textureHandle_ = TextureManager::Load("ddddog.png");
	SetTexture();

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();

	worldTransform_.translation_ = trans;
	//worldTransform_.scale_ = {2,2,2};

	//弾更新
	//	Fire();

	//接近フェーズ初期化
	ApproachInitialize();

	enemyHp = 5;

	damage = 1;

	damageUp = 5;
}

/// <summary>
/// 初期化
/// </summary>
void Enemy::Initialize(Vector3 trans) {
	// モデル読み込み
	SetModel();

	// テクスチャ読み込み
	SetTexture();

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();

	worldTransform_.translation_ = trans;

	//接近フェーズ初期化
	ApproachInitialize();
}


/// <summary>
/// 更新
/// </summary>
void Enemy::Update(Model* model) {
	assert(model);

	// デスフラグの立った弾を削除
	//bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) { return bullet->IsDead(); });

	//行列更新
	MatUpdate(worldTransform_);

	switch (phase_) {
	case Phase::None:

	case Phase::Approach:
	default:
		worldTransform_.translation_.z += -0.1f;
		if (worldTransform_.translation_.z < -30.0f) {
			phase_ = Phase::Leave;
		}

		fireTimer_--;

		if (fireTimer_ <= 0) {
			// 弾を発射
			Fire(model);
			// 発射タイマーを初期化
			fireTimer_ = kFireInterval;
		}

		break;
	case Phase::Leave:

		worldTransform_.translation_.x += -0.1f;
		worldTransform_.translation_.y += 0.1f;
		if (worldTransform_.translation_.x <= -50) {
			isDead_ = true;
		}

		break;
	}


	//弾更新
	/*for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}*/

	debugText_->SetPos(10, 50);
	debugText_->Printf(
		"enemy : x,%f  y,%f z,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y,
		worldTransform_.translation_.z, tribe);

}

/// <summary>
/// 描画
/// </summary>
void Enemy::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//弾更新
	/*for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}*/
}

/// <summary>
/// 自キャラを借りてくる
/// </summary>
void Enemy::SetPlayer(Player* player) { player_ = player; }

/// <summary>
/// 行列更新
/// </summary>
void Enemy::MatUpdate(WorldTransform& worldTransform_) {

	// パーツの更新

	// ３移動合成行列を計算
	worldTransform_.matWorld_ = Affin::matWorld(
		worldTransform_.translation_, worldTransform_.rotation_, worldTransform_.scale_);

	// 親の行列を掛け算代入
	if (worldTransform_.parent_ != nullptr) {
		worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;
	}

	// 行列の転送
	worldTransform_.TransferMatrix();
}

/// <summary>
/// 弾発射
/// </summary>
void Enemy::Fire(Model* model) {

	assert(player_);
	assert(model);

	//弾の速度
	const float kBulletSpeed = 0.5f;

	const float angle = cos(PI / 4);

	Vector3 playerPos = player_->GetWorldPosition();
	Vector3 enePos = GetWorldPosition();

	Vector3 a;
	a.x = playerPos.x - enePos.x;
	a.y = playerPos.y - enePos.y;
	a.z = playerPos.z - enePos.z;
	Vector3 nomal = MathUtility::Vector3Normalize(a);

	Vector3 velocity(nomal.x * kBulletSpeed, nomal.y * kBulletSpeed, nomal.z * kBulletSpeed);

	// 速度ベクトルを自機の向きに合わせて回転させる
	velocity = Affin::VecMat(velocity, worldTransform_.matWorld_);

	// 弾を生成し、初期化
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model, worldTransform_.translation_, velocity);



	// 弾を登録する
	//bullets_.push_back(std::move(newBullet));
	gameScene_->AddEnemyBullet(std::move(newBullet));
}

/// <summary>
/// 接近フェーズ初期化
/// </summary>
void Enemy::ApproachInitialize() {
	// 発射タイマーを初期化
	fireTimer_ = kFireInterval;
}

void Enemy::Tackle(WorldTransform& worldTransform) {


}

/// <summary>
/// ワールド座標を取得
/// </summary>
Vector3 Enemy::GetWorldPosition() {
	//
	Vector3 worldPos;
	//
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

/// <summary>
/// 衝突を検知したら呼び出されるコールバック関数
/// </summary>
//void Enemy::OnCollision() {
//	enemyHp -= damageUp;
//	if (enemyHp <= 0) {
//		isDead_ = true;
//	}
//	player_->AddPoint();
//}

void Enemy::OnCollision() {
	enemyHp -= damage;
	if (enemyHp <= 0) {
		isDead_ = true;
	}
void Enemy::OnCollision(Model* model) {
	player_->AddPoint();

	Vector3 enePos = GetWorldPosition();
	std::unique_ptr<Food> newFood = std::make_unique<Food>();
	newFood->Initialize(model, enePos);
	newFood->SetTribe(tribe);
	gameScene_->AddFood(std::move(newFood));
	isDead_ = true;
}

void Enemy::SetTexture() {
	switch (tribe)
	{
	case 0:
		textureHandle_ = TextureManager::Load("eneTex/0.png");
		break;
	case 1:
		textureHandle_ = TextureManager::Load("eneTex/1.png");
		break;
	case 2:
		textureHandle_ = TextureManager::Load("eneTex/2.png");
		break;
	case 3:
		textureHandle_ = TextureManager::Load("eneTex/3.png");
		break;
	case 4:
		textureHandle_ = TextureManager::Load("eneTex/4.png");
		break;
	case 5:
		textureHandle_ = TextureManager::Load("eneTex/5.png");
		break;
	case 6:
		textureHandle_ = TextureManager::Load("eneTex/6.png");
		break;
	case 7:
		textureHandle_ = TextureManager::Load("eneTex/7.png");
		break;
	case 8:
		textureHandle_ = TextureManager::Load("eneTex/8.png");
		break;
	case 9:
		textureHandle_ = TextureManager::Load("eneTex/9.png");
		break;
	case 10:
		textureHandle_ = TextureManager::Load("eneTex/10.png");
		break;
	}


}
void Enemy::SetModel() {
	switch (tribe){
	case 0:
		model_ = Model::CreateFromOBJ("cube", true);
		break;
	case 1:
		model_ = Model::CreateFromOBJ("cube", true);
		break;
	case 2:
		model_ = Model::CreateFromOBJ("cube", true);
		break;
	case 3:
		model_ = Model::CreateFromOBJ("cube", true);
		break;
	case 4:
		model_ = Model::CreateFromOBJ("cube", true);
		break;
	case 5:
		model_ = Model::CreateFromOBJ("cube", true);
		break;
	case 6:
		model_ = Model::CreateFromOBJ("cube", true);
		break;
	case 7:
		model_ = Model::CreateFromOBJ("cube", true);
		break;
	case 8:
		model_ = Model::CreateFromOBJ("cube", true);
		break;
	case 9:
		model_ = Model::CreateFromOBJ("cube", true);
		break;
	case 10:
		model_ = Model::CreateFromOBJ("cube", true);
		break;
	}


}