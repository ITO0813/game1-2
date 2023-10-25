#include <Novice.h>
#include <math.h>

const char kWindowTitle[] = "かいひ！ボックス！";

enum scene { 
	titlescene,
	trialscene,
	mainscene,
	clearscene
};

int Titlescene(char keys[], char preKeys[], int titleHandle) {
	Novice::DrawSprite(0, 0, titleHandle, 1, 1, 0.0f, WHITE);
	
	if (!keys[DIK_SPACE] && preKeys[DIK_SPACE])	{
		return trialscene;
	}

	else {
		return titlescene;
	}
}

int Trialscene(
    char keys[], char preKeys[], int playerRedHandle, int boxHandle, int ElipseHandle,
    int BataconHandle,int playerBlueHandle) {

	Novice::DrawSprite(100, 300, playerRedHandle, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(200, 100, boxHandle, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(400, 200, ElipseHandle, 1, 1, 0.0f, WHITE);
	
	Novice::DrawSprite(100, 600, playerBlueHandle, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(200, 400, boxHandle, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(400, 500, BataconHandle, 1, 1, 0.0f, WHITE);

	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		return mainscene;
	}

	else {
		return trialscene;
	}

}

int Mainscene(int posX) {

	if (posX >= 106240) {
		return clearscene;
	}

	else {
		return mainscene;
	}
}

int Clearscene(char preKeys[], char keys[], int clearHandle) {

	Novice::DrawSprite(0, 0, clearHandle, 1, 1, 0.0f, WHITE);

	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		return titlescene;
	}

	else {
		return clearscene;
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	const int World_Width = 1280 * 83;

	//[42]で約１分　 2分=[84] ３分＝[126]
	int backgroundX[64]{
	    0,         1280 * 1,  1280 * 2,  1280 * 3,  
		1280 * 4,  1280 * 5,  1280 * 6,  1280 * 7,
	    1280 * 8,  1280 * 9,  1280 * 10, 1280 * 11,
		1280 * 12, 1280 * 13, 1280 * 14, 1280 * 15,
	    1280 * 16, 1280 * 17, 1280 * 18, 1280 * 19, 
		1280 * 20, 1280 * 21, 1280 * 22, 1280 * 23,
	    1280 * 24, 1280 * 25, 1280 * 26, 1280 * 27,
		1280 * 28, 1280 * 29, 1280 * 30, 1280 * 31,
	    1280 * 32, 1280 * 33, 1280 * 34, 1280 * 35,
		1280 * 36, 1280 * 37, 1280 * 38, 1280 * 39,
	    1280 * 40, 1280 * 41, 1280 * 42, 1280 * 43,
		1280 * 44, 1280 * 45, 1280 * 46, 1280 * 47,
	    1280 * 48, 1280 * 49, 1280 * 50, 1280 * 51,
		1280 * 52, 1280 * 53, 1280 * 54, 1280 * 55,
	    1280 * 56, 1280 * 57, 1280 * 58, 1280 * 59,
		1280 * 60, 1280 * 61, 1280 * 62, 1280 * 63,
	};

	for (int i = 0; i < 64; i++) {
		Novice::LoadTexture("./images/Game_screen2.png");
	};

	int posX = 32;
	int posY = 596;
	int posrad = 1;
	int speed = 10;
	int ScrollX = posX + posrad;

	int posAX1 = posX;
	
	int playerScrollAX1 = posAX1 - ScrollX;

	int posXAX1 = 0;
	int posXAX2 = 0;

	bool modeDefault = true;
	bool modeBreak = false;
	bool modeSlipthorugh = false;

	int playerWhiteHandle;
	playerWhiteHandle = Novice::LoadTexture("./images/playerWhite.png");
	int playerRedHandle;
	playerRedHandle = Novice::LoadTexture("./images/playerRed.png");
	int playerBlueHandle;
	playerBlueHandle = Novice::LoadTexture("./images/playerBlue.png");

	int ElipseHandle = Novice::LoadTexture("./images/Elipse.png");
	int BataconHandle = Novice::LoadTexture("./images/Batu.png");

	// 障害物当たり判定宣言
	int boxX = 400;
	int boxrad = 1;
	int ScrollY = boxX + boxrad;

	const int kBoxRedMax = 64;
	int boxXRed1[kBoxRedMax] = {};
	int boxXRed2[kBoxRedMax] = {};

	bool is_player_hit = false;
	bool is_player_hitX = false;

	int boxHandle;
	boxHandle = Novice::LoadTexture("./images/breakver.png");
	//int boxHandle2;
	//boxHandle2 = Novice::LoadTexture("./images/inbijiver.png");

	int titleHandle = Novice::LoadTexture("./images/title1.png");
	int backgroundHandle = Novice::LoadTexture("./images/Game_screen2.png");
	int clearHandle = Novice::LoadTexture("./images/CLEAR.png");

	int scene;
	scene = titlescene;

	int soundHandle = Novice::LoadAudio("./bgms/MusMus-BGM-141.mp3");
	int soundHandle2 = Novice::LoadAudio("./bgms/MusMus-BGM-130.mp3");
	int soundHandle3 = Novice::LoadAudio("./bgms/MusMus-BGM-131.mp3");

	int voiceHandle1 = -1;
	int voiceHandle2 = -1;
	int voiceHandle3 = -1;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		int nextScene = scene;

		if (scene == titlescene) {
			nextScene = Titlescene(keys, preKeys, titleHandle);

			Novice::StopAudio(voiceHandle2);

			if (Novice::IsPlayingAudio(voiceHandle1) == 0 || voiceHandle1 == -1) {
				voiceHandle1 = Novice::PlayAudio(soundHandle2, false, 1.0f);
			}
		}

		if (scene != nextScene) {
			scene = nextScene;
		}

		if (scene == trialscene) {
			nextScene = Trialscene(keys, preKeys, playerRedHandle, boxHandle,ElipseHandle,BataconHandle,playerBlueHandle);

			Novice::StopAudio(voiceHandle2);

			if (Novice::IsPlayingAudio(voiceHandle1) == 0 || voiceHandle1 == -1) {
				voiceHandle1 = Novice::PlayAudio(soundHandle2, false, 1.0f);
			}
		}

		if (scene != nextScene) {
			scene = nextScene;
		}

		if (scene == mainscene) {
			nextScene = Mainscene(posX);

			Novice::StopAudio(voiceHandle1);

			if (!Novice::IsPlayingAudio(voiceHandle2) || voiceHandle2 == -1) {
				voiceHandle2 = Novice::PlayAudio(soundHandle, false, 1.0f);
			}

			//スクロール関連
			posX += speed;

			ScrollX = posX + posrad;
			ScrollY = boxX + boxrad;

			
			// Playerの座標更新
			posAX1 = posX + posrad;

			for (int i = 0; i < kBoxRedMax; i++) {
				boxXRed1[i] = (boxX + 1280 * i);
				boxXRed2[i] = boxXRed1[i] + 100;
			
				posXAX1 = (posX + 32 * i);
				posXAX2 = posXAX1 + 32;
			}

			if (ScrollX < 0) {
				ScrollX = 0;
			}
			if (ScrollX > World_Width - 1280) {
				ScrollX = World_Width - 1280;
			}
			playerScrollAX1 = posAX1 - ScrollX;

			if (ScrollY < 0) {
				ScrollY = 0;
			}
			if (ScrollY > World_Width - 1280) {
				ScrollY = World_Width - 1280;
			}

			if (posX >= backgroundX[21]) {
				speed = 15;
			}
			if (posX >= backgroundX[42]) {
				speed = 20;
			}

			//当たり判定
			for (int i = 0; i < kBoxRedMax; i++) {
				
				if (modeBreak == true){
					if (boxXRed1[i] < posXAX2 && posXAX1 < boxXRed2[i]) {
						is_player_hitX = false;
					} else {
						is_player_hitX = false;
					}
				}

				else if (boxXRed1[i] < posXAX2 && posXAX1 < boxXRed2[i]) {
					is_player_hitX = true;
				} else {
					is_player_hitX = false;
				}

				if (is_player_hitX == true) {
					is_player_hit = true;
				} else {
					is_player_hit = false;
				}
			}
			
			//背景の描画
			for (int i = 0; i < kBoxRedMax; i++) {
				Novice::DrawSprite(backgroundX[i] - ScrollX, 0, backgroundHandle, 1, 1, 0.0f, WHITE);
			}
			for (int i = 0; i < kBoxRedMax; i++) {
				Novice::DrawSprite(boxXRed1[i] - ScrollX, 328, boxHandle, 1, 1, 0.0f, WHITE);
			}

			//モードの切り替え
			if (modeDefault == true) {
				Novice::DrawSprite(posAX1 - ScrollX, posY, playerWhiteHandle, 1, 1, 0.0f, WHITE);
				if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
					modeBreak = true;
					modeDefault = false;
					modeSlipthorugh = false;
				}
			}

			else if (modeBreak == true) {
				Novice::DrawSprite(posAX1 - ScrollX, posY, playerRedHandle, 1, 1, 0.0f, WHITE);
				if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
					modeSlipthorugh = true;
					modeDefault = false;
					modeBreak = false;
				}
			}

			else if (modeSlipthorugh == true) {
				Novice::DrawSprite(posAX1 - ScrollX, posY, playerBlueHandle, 1, 1, 0.0f, WHITE);
				if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
					modeDefault = true;
					modeBreak = false;
					modeSlipthorugh = false;
				}
			}
		}

		if (scene != nextScene) {
			scene = nextScene;
		}

		if (scene == clearscene) {
			nextScene =Clearscene(keys, preKeys, clearHandle);

			Novice::StopAudio(voiceHandle2);

			if (!Novice::IsPlayingAudio(voiceHandle3) || voiceHandle3 == -1) {
				voiceHandle3 = Novice::PlayAudio(soundHandle3, false, 1.0f);
			}
		}

		if (scene != nextScene) {
			scene = nextScene;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
