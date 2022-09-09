#include "Item.h"
#include "Food.h"
#include <fstream>


void Item::Initialize() {
	for (int i = 0; i < 10; i++) {
		strage[5]->item = 0;
	}


}
void Item::Update() {


}
void Item::Draw() {

}
void Item::SpriteDraw() {

}

void Item::AddItem(int tribe) {
	if (strage[0]->item == false) {
		strage[0]->item = true;
		strage[0]->tribe = tribe;
	}
	else if (strage[1]->item == false) {
		strage[1]->item = true;
		strage[1]->tribe = tribe;
	}
	else if (strage[2]->item == false) {
		strage[2]->item = true;
	}
	else if (strage[3]->item == false) {
		strage[3]->item = true;
		strage[3]->tribe = tribe;
	}
	else if (strage[4]->item == false) {
		strage[4]->item = true;
		strage[4]->tribe = tribe;
	}

}

void Item::LoadItemData() {
	//ファイルを開く
	std::ifstream file;
	file.open("Resources/enemyState.csv");
	assert(file.is_open());

	//ファイルの内容を文字列ストリームにコピー
	itemCommands << file.rdbuf();

	//ファイルを閉じる
	file.close();
}

void Item::UpdateItemCommands(int num) {

	//待機処理
	if (stay) {
		itemTime--;
		if (itemTime <= 0) {
			//待機完了
			stay = false;
		}
		return;
	}

	// 1行分の文字列を入れる
	std::string line;

	//コマンド実行ループ
	while (getline(itemCommands, line)) {
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
		// POPコマンド

		if (word.find("CURRY") == 0) {
			// x座標
			getline(line_stream, word, ',');
			int x = (int)std::atof(word.c_str());

			// 種類
			int w = curry;

		}

		if (word.find("SALAD") == 0) {
			// x座標
			getline(line_stream, word, ',');
			int x = (int)std::atof(word.c_str());

			// 種類
			int w = salada;
		}

		if (word.find("BBQ") == 0) {
			// x座標
			getline(line_stream, word, ',');
			int x = (int)std::atof(word.c_str());

			// 種類
			int w = yakiniku;
		}

		if (word.find("FRIEDEGG") == 0) {
			// x座標
			getline(line_stream, word, ',');
			int x = (int)std::atof(word.c_str());

			// 種類
			int w = medamayaki;
		}

		if (word.find("NIKUJAGA") == 0) {
			// x座標
			getline(line_stream, word, ',');
			int x = (int)std::atof(word.c_str());

			// 種類
			int w = nikujaga;
		}

		if (word.find("TOMATO") == 0) {
			// x座標
			getline(line_stream, word, ',');
			int x = (int)std::atof(word.c_str());

			// 種類
			int w = tomato;
		}

		if (word.find("OMURICE") == 0) {
			// x座標
			getline(line_stream, word, ',');
			int x = (int)std::atof(word.c_str());

			// 種類
			int w = omuraisu;

		}

		if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			//待ち時間
			int32_t waitTime = atoi(word.c_str());

			//待機開始
			stay = true;

			itemTime = waitTime;
			//コマンドループを抜ける
			break;
		}


	}

}
