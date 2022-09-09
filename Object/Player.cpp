#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("block1.png");

	// 3Dレティクルのワールドトランスフォームの初期化
	worldTransform3DReticle_.Initialize();

	//スプライト生成
	sprite2DReticle_.reset(
	  Sprite::Create(textureReticle, Vector2{640, 360}, Vector4{1, 1, 1, 1}, Vector2(0.5, 0.5)));

	// worldTransform_.parent_ = &cameraWorldTransform_;
	Vector3 move(0, 0, 40);

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
	worldTransform_.translation_ = move;
	worldTransform_.matWorld_ = MathUtility::Matrix4Translation(
	  worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);

	hp = 100;
	point = 0;
}

/// <summary>
/// 更新
/// </summary>
void Player::Update(ViewProjection viewProjection, Model* model) {
	assert(model);
	// デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });

#pragma region キャラクター移動処理

	// キャラクター移動処理
	Move();
	Rotate();

	//行列更新
	MatUpdate(worldTransform_);

	//キャラ攻撃
	Attack(model);

	//弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	// Reticle(viewProjection);

	// 2Dレティクルのスクリーン座標から3Dレティクルのワールド座標を計算
	{
		// POINT mousePosition;
		////マウス座標（スクリーン座標）を取得する
		// GetCursorPos(&mousePosition);

		////クライアントエリア座標に変換する
		// HWND hwnd = WinApp::GetInstance()->GetHwnd();
		// ScreenToClient(hwnd, &mousePosition);

		// sprite2DReticle_->SetPosition(Vector2(mousePosition.x, mousePosition.y));

		//スプライトの現在座標を取得
		Vector2 spritePosition = sprite2DReticle_->GetPosition();

		XINPUT_STATE joyState;

		//ジョイスティック状態
		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			spritePosition.x += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 5.0f;
			spritePosition.y -= (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 5.0f;
			//スプライトの座標変更を反映
			sprite2DReticle_->SetPosition(spritePosition);
		}

		//ビューポート行列
		Matrix4 matViewport = {
		  640, 0, 0, 0, 0, -360, 0, 0, 0, 0, 1, 0, 640, 360, 0, 1,
		};

		//ビューポート行列
		Matrix4 viewportMat;
		viewportMat = viewProjection.matView;
		viewportMat *= viewProjection.matProjection;
		viewportMat *= matViewport;
		//合成行列の逆行列を計算する
		Matrix4 matInverseVPV = MathUtility::Matrix4Inverse(viewportMat);

		//スクリーン座標
		Vector3 posNear = Vector3(spritePosition.x, spritePosition.y, 0);
		Vector3 posFar = Vector3(spritePosition.x, spritePosition.y, 1);

		//スクリーン座標系からワールド座標系へ
		posNear = Affin::wDivision(posNear, matInverseVPV);
		posFar = Affin::wDivision(posFar, matInverseVPV);

		//マウスレイの方向
		Vector3 mouseDirection = posFar;
		mouseDirection -= posNear;
		float len = sqrt(
		  mouseDirection.x * mouseDirection.x + mouseDirection.y * mouseDirection.y +
		  mouseDirection.z * mouseDirection.z);
		if (len != 0) {
			mouseDirection /= len;
		}
		//カメラから照準オブジェクトの距離
		const float kDistanceTestObject = 100.0f;
		Vector3 A = posNear;
		A += Vector3(
		  mouseDirection.x * kDistanceTestObject, mouseDirection.y * kDistanceTestObject,
		  mouseDirection.z * kDistanceTestObject);
		worldTransform3DReticle_.translation_ = A;
		worldTransform3DReticle_.matWorld_ = Affin::matUnit();
		worldTransform3DReticle_.matWorld_ = Affin::matTrans(worldTransform3DReticle_.translation_);
		worldTransform3DReticle_.TransferMatrix();

		/*DebugText::GetInstance()->SetPos(20, 200);
		DebugText::GetInstance()->Printf(
		  "Mouse ScreenPos:(%d,%d)", spritePosition.x, spritePosition.y);
		DebugText::GetInstance()->SetPos(20, 220);
		DebugText::GetInstance()->Printf("Near:(%f,%f,%f)", posNear.x, posNear.y, posNear.z);
		DebugText::GetInstance()->SetPos(20, 240);
		DebugText::GetInstance()->Printf("Far:(%f,%f,%f)", posFar.x, posFar.y, posFar.z);
		DebugText::GetInstance()->SetPos(20, 260);
		DebugText::GetInstance()->Printf(
		  "MouseObject:(%f,%f,%f)", worldTransform3DReticle_.translation_.x,
		  worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);
	*/
	}

	/*debugText_->SetPos(10, 10);
	debugText_->Printf(
	  "player : x,%f  y,%f z,%f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
	debugText_->SetPos(10, 30);
	debugText_->Printf(
	  "player : x,%f  y,%f z,%f", worldTransform_.rotation_.x, worldTransform_.rotation_.y,
	  worldTransform_.rotation_.z);*/

	debugText_->SetPos(600, 500);
	debugText_->Printf("crushing : %d", point);
	debugText_->SetPos(600, 550);
	debugText_->Printf("   hp    : %d", hp);
#pragma endregion
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// model_->Draw(worldTransform3DReticle_, viewProjection, textureHandle_);
	//弾描画
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Player::MatUpdate(WorldTransform& worldTransform) {

	// パーツの更新

	// ３移動合成行列を計算
	worldTransform_.matWorld_ = Affin::matWorld(
	  worldTransform_.translation_, worldTransform_.rotation_, worldTransform_.scale_);

	// 親の行列を掛け算代入

	worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;

	// 行列の転送
	worldTransform_.TransferMatrix();
}

/// <summary>
/// 動作
/// </summary>
void Player::Move() {
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	//ゲームパッドの状態を得る変数（XINPUT）
	XINPUT_STATE joyState;
	//ジョイスティック状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * 0.1;
		move.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * 0.1;
	}

	//移動限界座標
	const float kMoveLimitX = 35;
	const float kMoveLimitY = 19;

	//範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	worldTransform_.translation_ += move;
}

/// <summary>
/// 回転移動
/// </summary>
void Player::Rotate() {
	Vector3 rotate = {0, 0, 0};

	// 回転
	{ // X方向
		if (input_->PushKey(DIK_Q)) {
			rotate.x = 1;
		} else if (input_->PushKey(DIK_E)) {
			rotate.x = -1;
		}
		// Y方向
		if (input_->PushKey(DIK_1)) {
			rotate.y = 1;
		} else if (input_->PushKey(DIK_2)) {
			rotate.y = -1;
		}
	}

	//移動限界座標
	const float kRotateLimitX = 80;
	const float kRotateLimitY = 80;

	//範囲を超えない処理
	worldTransform_.rotation_.x = max(worldTransform_.rotation_.x, -kRotateLimitX);
	worldTransform_.rotation_.x = min(worldTransform_.rotation_.x, +kRotateLimitX);
	worldTransform_.rotation_.y = max(worldTransform_.rotation_.y, -kRotateLimitY);
	worldTransform_.rotation_.y = min(worldTransform_.rotation_.y, +kRotateLimitY);

	worldTransform_.rotation_ += rotate;
}

/// <summary>
/// 攻撃
/// </summary>
void Player::Attack(Model* model) {
	bulletModel_ = model;
	XINPUT_STATE joyState;

	if (!Input::GetInstance()->GetJoystickState(0, joyState)) {

		return;
	}
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		//弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		velocity = Affin::VecMat(velocity, worldTransform_.parent_->matWorld_);
		velocity = Affin::VecMat(velocity, worldTransform_.matWorld_);
		velocity = MathUtility::operator-(
		  Affin::GetWorldTrans(worldTransform3DReticle_.matWorld_),
		  Affin::GetWorldTrans(worldTransform_.matWorld_));
		float len =
		  sqrt(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);
		if (len != 0) {
			velocity /= len;
		}
		velocity *= kBulletSpeed;

		//弾の生成し、初期化
		Vector3 playerRot, playerPos;
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		// 平行
		playerPos = worldTransform_.parent_->translation_;
		playerPos += worldTransform_.translation_;
		// 回転
		playerRot = worldTransform_.parent_->rotation_;
		playerRot += worldTransform_.rotation_;
		newBullet->Initialize(bulletModel_, GetWorldPosition(), velocity);

		//弾の登録する
		bullets_.push_back(std::move(newBullet));
	}
}

/// <summary>
/// ワールド座標を取得
/// </summary>
Vector3 Player::GetWorldPosition() {
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
void Player::OnCollision() {
	hp -= 1;
	if (hp <= 0) {
		isDead = true;
	}
}
// point 加算
void Player::AddPoint() { point += 1; }

/// <summary>
/// UI描画
/// </summary>
void Player::DrawUI() { sprite2DReticle_->Draw(); }

/// <summary>
/// 自機のワールド座標から3Dレティクルのワールド座標を計算
/// </summary>
void Player::WorldReticle() {
	//自機のワールド座標から3Dレティクルのワールド座標を計算
	//自機から3Dレティクルへの距離
	const float kDistancePlayerTo3DReticle = 50.0f;
	//自機から3Dレティクルへのオフセット(Z+向き)
	Vector3 offset = {0, 0, 1.0f};
	//自機のワールド行列の回転を反映
	offset = Affin::VecMat(offset, worldTransform_.matWorld_);
	//ベクトルの長さを整える
	float len = sqrt(offset.x * offset.x + offset.y * offset.y + offset.z * offset.z);
	if (len != 0) {
		offset /= len;
	}
	offset *= kDistancePlayerTo3DReticle;
	worldTransform3DReticle_.translation_ = offset;
	worldTransform3DReticle_.matWorld_ = Affin::matTrans(worldTransform_.translation_);
	worldTransform3DReticle_.TransferMatrix();
}

// 3Dレティクルのワールド座標から2Dレティクルのスクリーン座標を計算
void Player::Reticle(ViewProjection viewprojection) {
	WorldReticle();

	Vector3 positionReticle = Affin::GetWorldTrans(worldTransform3DReticle_.matWorld_);

	//ビューポート行列
	Matrix4 matViewport = {
	  640, 0, 0, 0, 
	  0, -360, 0, 0,
	  0, 0, 1, 0,
	  640, 360, 0, 1,
	};

	//ビューポート行列
	Matrix4 matViewProjectionViewport;
	matViewProjectionViewport = viewprojection.matView;
	matViewProjectionViewport *= viewprojection.matProjection;
	matViewProjectionViewport *= matViewport;

	//ワールド→スクリーン座標変換(ここで3Dから2Dになる)
	positionReticle = Affin::wDivision(positionReticle, matViewProjectionViewport);

	//スプライトのレティクルに座標設定
	sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));

	debugText_->SetPos(100, 100);
	debugText_->Printf("X:%f,Y:%f", positionReticle.x, positionReticle.y);
}