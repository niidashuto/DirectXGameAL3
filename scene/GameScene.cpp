#include "GameScene.h"
#include "AxisIndicator.h"
#include "Enemy.h"
#include "PLayer.h"
#include "TextureManager.h"
#include <cassert>
#include <cmath>
#include <fstream>
#include <random>

#include "Item.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete debugCamera_;
	//自キャラの解放
	delete player_;
	delete model_;
	delete modelSkydome_;
	delete item_;
}



void GameScene::Initialize(GameScene* gameScene) {
	gameScene_ = gameScene;
	debugCamera_ = new DebugCamera(1280, 720);
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	soundDataHandle_ = audio_->LoadWave("sound/Irregular.wav");

	// 軸方向表示の表示を有効にする
	//AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetVisible(false);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	//自キャラの生成
	skydome_ = std::make_unique<Skydome>();
	railCamera_ = std::make_unique<RailCamera>();
	player_ = new Player();
	model_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	modelBullet_ = Model::CreateFromOBJ("bullet", true);
	modelPlayer_ = Model::CreateFromOBJ("body", true);
	modelEnemy_ = Model::CreateFromOBJ("cube", true);
	item_ = new Item();
	// 
	//自キャラの初期化
	player_->Initialize(modelPlayer_, textureHandle_);

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	railCamera_->Initialize(Vector3{ 0.0f, 0.0f, -80.0f }, Vector3{ 0.0f, 0.0f, 0.0f });

	player_->SetParent(railCamera_->GetWorldTransform());

	skydome_->Initialize(modelSkydome_);

	item_->Initialize();

	LoadEnemyPopData();

	//voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);


}

//乱数シード生成器
std::random_device seed_gem;
//メルセンヌ・ツイスター
std::mt19937_64 engine(seed_gem());
//乱数範囲（座標用）
std::uniform_real_distribution<float> posDist(-30.0f, 30.0f);
//乱数範囲（摘出現用）
std::uniform_real_distribution<float> numDist(0.0f, 10.0f);

void GameScene::Update() {

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_P) && isDebugcameraActive_ == false) {
		isDebugcameraActive_ = true;
	}
	else if (input_->TriggerKey(DIK_P) && isDebugcameraActive_ == true) {
		isDebugcameraActive_ = false;
	}

#endif // _DEBUG

	// カメラの処理
	if (isDebugcameraActive_ == true) {
		//デバッグカメラの更新
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		viewProjection_.TransferMatrix();
	}
	else {
		viewProjection_.UpdateMatrix();
		viewProjection_.TransferMatrix();
	}



	switch (stage) {
		XINPUT_STATE joyState;
	case TITLE:
		if (input_->PushKey(DIK_Q)) {
			stage = GAME;
		}

		if (!Input::GetInstance()->GetJoystickState(0, joyState)) {

			return;
		}
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
			stage = GAME;
		}

		break;

	case END:

		gameScene_->Initialize(gameScene_);
		//XINPUT_STATE joyState;
		time = 0;

		// 自キャラと敵弾すべての当たり判定
		for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
			bullet->IsDeath();
		}
		for (const std::unique_ptr<Enemy>& enemy : enemy_) {
			enemy->IsDeath();
		}
		for (const std::unique_ptr<Food>& food : foods_) {
			food->IsDeath();
		}


		if (!Input::GetInstance()->GetJoystickState(0, joyState)) {

			return;
		}
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
			stage = TITLE;
		}

		break;
	case INFO:

		if (!Input::GetInstance()->GetJoystickState(0, joyState)) {

			return;
		}
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
			stage = GAME;
		}
		//自キャラの更新
		player_->Update(viewProjection_, modelBullet_);
		railCamera_->Update(player_);

		break;
	case GAME:
		time++;
		if (player_->IsDead() == true) {
			stage = END;
		}
		//デスフラグの立った弾を削除
		enemyBullets_.remove_if(
			[](std::unique_ptr<EnemyBullet>& bullet) { return bullet->IsDead(); });
		//デスフラグの立った弾を削除
		enemy_.remove_if([](std::unique_ptr<Enemy>& enemy) { return enemy->IsDead(); });
		//デスフラグの立った弾を削除
		foods_.remove_if([](std::unique_ptr<Food>& food) { return food->IsDead(); });

		//自キャラの更新
		player_->Update(viewProjection_, modelBullet_);


		eneRand = numDist(engine);

		UpdateEnemyPopCommands(eneRand);

		//弾更新
		for (std::unique_ptr<Enemy>& enemy : enemy_) {
			//敵キャラの更新
			enemy->Update(modelBullet_);
		}
		//弾更新
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
			bullet->Update();
		}

		for (std::unique_ptr<Food>& food : foods_) {
			food->Update();
		}

		item_->Update();

		//衝突判定
		CheckAllCollisions();

		railCamera_->Update(player_);

		if (player_->GetPoint() < 20) {
			LoadEnemyPopData();
		}

		if (player_->GetPoint() >= 15) {
			stage = END;
		}


		break;
	}

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	/// 
	switch (stage) {
	case TITLE:
		debugText_->SetPos(1280 / 2, 300);
		debugText_->Printf(" OBJECTSHOOTER ");

		debugText_->SetPos(1280 / 2, 720 / 2);
		debugText_->Printf(" PRESS LB BUTTON ");

		break;

	case INFO:

		debugText_->SetPos(1280 / 2, 500);
		debugText_->Printf(" SHOT RB  ");

		//自キャラの描画
		player_->Draw(railCamera_->GetViewProjection());

		break;

	case END:
		debugText_->SetPos(1280 / 2, 300);
		debugText_->Printf(" E N D ");

		debugText_->SetPos(1280 / 2, 720 / 2);
		debugText_->Printf(" PRESS B BUTTON ");

		break;
	case GAME:


		//自キャラの描画
		player_->Draw(railCamera_->GetViewProjection());
		//弾描画
		for (std::unique_ptr<Enemy>& enemy : enemy_) {
			enemy->Draw(railCamera_->GetViewProjection());
		}
		//弾描画
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
			bullet->Draw(railCamera_->GetViewProjection());
		}
		// 
		for (std::unique_ptr<Food>& food : foods_) {
			food->Draw(railCamera_->GetViewProjection());
		}
		debugText_->SetPos(1280 / 2, 600);
		debugText_->Printf(" SHOT RB  ");
		break;
	}
	// 3Dモデル描画
	skydome_->Draw(railCamera_->GetViewProjection());
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	switch (stage) {
	case TITLE:

		break;

	case END:

		break;
	case INFO:
	case GAME:

		player_->DrawUI();
		break;
	}


	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {
	//判定対象AとBの座標
	Vector3 posA, posB;

	//自弾リストの取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();
	////敵弾リストの取得
	// const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets_ = GetBullets();

#pragma region 自キャラと敵弾の当たり判定
	{
		// 自キャラの座標
		posA = player_->GetWorldPosition();

		// 自キャラと敵弾すべての当たり判定
		for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {

			//敵弾の座標
			posB = bullet.get()->GetWorldPosition();
			float a = std::pow(posB.x - posA.x, 2.0f) + std::pow(posB.y - posA.y, 2.0f) +
				std::pow(posB.z - posA.z, 2.0f);
			float lenR = std::pow(bullet.get()->r + player_->r, 2.0);

			// 球と球の交差判定
			if (a <= lenR) {
				// 自キャラの衝突時コールバックを呼び出す
				player_->OnCollision();
				// 敵弾の衝突時コールバックを呼び出す
				bullet->OnCollision();
			}
		}
		for (const std::unique_ptr<Food>& food : foods_) {

			// foodの座標
			posB = food.get()->GetWorldPosition();
			float a = std::pow(posB.x - posA.x, 2.0f) + std::pow(posB.y - posA.y, 2.0f) +
				std::pow(posB.z - posA.z, 2.0f);
			float lenR = std::pow(food.get()->r + player_->r, 2.0);

			// 球と球の交差判定
			if (a <= lenR) {
				// 敵弾の衝突時コールバックを呼び出す
				item_->AddItem(food->GetTribe());
				food->OnCollision();
			}
		}
	}
#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	{
		for (const std::unique_ptr<Enemy>& enemy : enemy_) {
			posA = enemy->GetWorldPosition();
			// 自球と敵すべての当たり判定
			for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {
				//自弾の座標
				posB = bullet->GetWorldPosition();
				float a = std::pow(posB.x - posA.x, 2.0f) + std::pow(posB.y - posA.y, 2.0f) +
					std::pow(posB.z - posA.z, 2.0f);
				float lenR = std::pow((bullet.get()->r + enemy->r), 2.0);
				// 球と球の交差判定
				if (a <= lenR) {
					// キャラの衝突時コールバックを呼び出す
					enemy->OnCollision();
					// 弾の衝突時コールバックを呼び出す
					bullet->OnCollision();
				}
			}
		}
	}
#pragma endregion
#pragma region 自弾と敵弾の当たり判定
	{
		// 自球と敵弾すべての当たり判定
		for (const std::unique_ptr<PlayerBullet>& pBullet : playerBullets) {

			posA = pBullet->GetWorldPosition();

			// 敵弾
			for (const std::unique_ptr<EnemyBullet>& eBullet : enemyBullets_) {
				//敵弾の座標
				posB = eBullet->GetWorldPosition();
				float a = std::pow(posB.x - posA.x, 2.0f) + std::pow(posB.y - posA.y, 2.0f) +
					std::pow(posB.z - posA.z, 2.0f);
				float lenR = std::pow((eBullet.get()->r + pBullet.get()->r), 2.0);

				// 球と球の交差判定
				if (a <= lenR) {
					// 自キャラの衝突時コールバックを呼び出す
					pBullet->OnCollision();
					// 敵弾の衝突時コールバックを呼び出す
					eBullet->OnCollision();
				}
			}
		}
	}
#pragma endregion

}

void GameScene::AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet) {
	enemyBullets_.push_back(std::move(enemyBullet));
}

void GameScene::AddFood(std::unique_ptr<Food> food) {
	foods_.push_back(std::move(food));
}

void GameScene::Fire(Vector3 trans, int W) {
	assert(player_);

	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();

	enemy->SetTribe(W);
	enemy->Initialize(trans);
	enemy->SetPlayer(player_);
	enemy->SetGameScene(gameScene_);

	enemy_.push_back(std::move(enemy));
}

void GameScene::LoadEnemyPopData() {
	//ファイルを開く
	std::ifstream file;
	file.open("Resources/enemyState.csv");
	assert(file.is_open());

	//ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	//ファイルを閉じる
	file.close();
}

void GameScene::UpdateEnemyPopCommands(int num) {

	//待機処理
	if (enemyPop) {
		enemyPopTime--;
		if (enemyPopTime <= 0) {
			//待機完了
			enemyPop = false;
		}
		return;
	}

	// 1行分の文字列を入れる
	std::string line;

	//コマンド実行ループ
	while (getline(enemyPopCommands, line)) {
		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');
		//"//"から始まる行はコメント
		if (word.find("//") == 0) {
			//コメント行を飛ばす
			continue;
		}
		/*if ()
		{
			break;
		}*/
		// POPコマンド

		switch (num)
		{
		case Monkey:
			if (word.find("MONKEY") == 0) {
				// x座標
				getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str()) + posDist(engine);

				// y座標
				getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str()) + posDist(engine);

				// z座標
				getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				// 種類
				int w = Monkey;

				//敵を発生させる
				Fire(Vector3(x, y, z), w);

			}
			else {
				break;
			}


		case Pig:

			if (word.find("PIG") == 0) {
				// x座標
				getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str()) + posDist(engine);

				// y座標
				getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str()) + posDist(engine);

				// z座標
				getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				// 種類
				int w = Pig;

				//敵を発生させる
				Fire(Vector3(x, y, z), w);

			}
			else {
				break;
			}



		case Cow:

			if (word.find("COW") == 0) {
				// x座標
				getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str()) + posDist(engine);

				// y座標
				getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str()) + posDist(engine);

				// z座標
				getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				// 種類
				int w = Cow;

				//敵を発生させる
				Fire(Vector3(x, y, z), w);

			}
			else {
				break;
			}


		case Chicken:
			if (word.find("CHICKEN") == 0) {
				// x座標
				getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str()) + posDist(engine);

				// y座標
				getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str()) + posDist(engine);

				// z座標
				getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				// 種類
				int w = Chicken;

				//敵を発生させる
				Fire(Vector3(x, y, z), w);

			}
			else {
				break;
			}


		case Lettuce:
			if (word.find("LETTUCE") == 0) {
				// x座標
				getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str()) + posDist(engine);
				// y座標
				getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str()) + posDist(engine);
				// z座標
				getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());
				// 種類
				int w = Lettuce;
				//敵を発生させる
				Fire(Vector3(x, y, z), w);

			}
			else {
				break;
			}


		case Tomato:
			if (word.find("TOMATO") == 0) {
				// x座標
				getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str()) + posDist(engine);
				// y座標
				getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str()) + posDist(engine);
				// z座標
				getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());
				// 種類
				int w = Tomato;
				//敵を発生させる
				Fire(Vector3(x, y, z), w);

			}
			else {
				break;
			}


		case Potato:
			if (word.find("POTATO") == 0) {
				// x座標
				getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str()) + posDist(engine);
				// y座標
				getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str()) + posDist(engine);
				// z座標
				getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());
				// 種類
				int w = Potato;
				//敵を発生させる
				Fire(Vector3(x, y, z), w);
			}
			else {
				break;
			}

		case Carrot:
			if (word.find("CARROT") == 0) {
				// x座標
				getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str()) + posDist(engine);
				// y座標
				getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str()) + posDist(engine);
				// z座標
				getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());
				// 種類
				int w = Carrot;
				//敵を発生させる
				Fire(Vector3(x, y, z), w);

			}
			else {
				break;
			}



		case Onion:
			if (word.find("ONION") == 0) {
				// x座標
				getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str()) + posDist(engine);
				// y座標
				getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str()) + posDist(engine);
				// z座標
				getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());
				// 種類
				int w = Onion;
				//敵を発生させる
				Fire(Vector3(x, y, z), w);

			}
			else {
				break;
			}


		case Rice:
			if (word.find("RICE") == 0) {
				// x座標
				getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str()) + posDist(engine);
				// y座標
				getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str()) + posDist(engine);
				// z座標
				getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());
				// 種類
				getline(line_stream, word, ',');
				int w = Rice;
				//敵を発生させる
				Fire(Vector3(x, y, z), w);

			}
			else {
				break;
			}

		case 10:
		default:

			if (word.find("FIRE") == 0) {
				// x座標
				getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str()) + posDist(engine);
				// y座標
				getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str()) + posDist(engine);
				// z座標
				getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());
				// 種類
				int w = 10;
				//敵を発生させる
				Fire(Vector3(x, y, z), w);

			}
			else {
				break;
			}
		}

		if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			//待ち時間
			int32_t waitTime = atoi(word.c_str());

			//待機開始
			enemyPop = true;

			enemyPopTime = waitTime;
			//コマンドループを抜ける
			break;
		}
	}
}

// リセット
void GameScene::Reset() {}