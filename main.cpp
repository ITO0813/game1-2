#include <Novice.h>
#include <math.h>

const char kWindowTitle[] = "GC1D_03_イトウヒビキ_タイトル";

enum scene { 
	titlescene,
	mainscene,
	clearscene
};

int Titlescene(char keys[], char preKeys[], int titleHandle) {
	Novice::DrawSprite(0, 0, titleHandle, 1, 1, 0.0f, WHITE);
	
	if (!keys[DIK_SPACE] && preKeys[DIK_SPACE])	{
		return mainscene;
	}

	else {
		return titlescene;
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
	int speed = 15;
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

	// 障害物当たり判定宣言
	int boxX = 400;

	int boxXRed1 = 0;
	int boxXRed2 = 0;

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

		if (scene == mainscene) {
			nextScene = Mainscene(posX);

			Novice::StopAudio(voiceHandle1);

			if (!Novice::IsPlayingAudio(voiceHandle2) || voiceHandle2 == -1) {
				voiceHandle2 = Novice::PlayAudio(soundHandle, false, 1.0f);
			}

			//スクロール関連
			posX += speed;

			ScrollX = posX + posrad;

			for (int i = 0; i < 64; i++) {
				boxXRed1 = (boxX + 980 * i) - ScrollX;
				boxXRed2 = boxXRed1 + 100;
			}
			for (int i = 0; i < 64; i++) {
				posXAX1 = (posX + 32 * i) - ScrollX;
				posXAX2 = posXAX1 + 32;
			}

			if (ScrollX < 0) {
				ScrollX = 0;
			}
			if (ScrollX > World_Width - 1280) {
				ScrollX = World_Width - 1280;
			}
			playerScrollAX1 = posAX1 - ScrollX;

			if (posX >= backgroundX[21]) {
				speed = 25;
			}
			if (posX >= backgroundX[42]) {
				speed = 25;
			}

			if (posX >= 1280 * 64) {
				speed = 0;
			}

			//当たり判定
			if (boxXRed1 < posXAX2 && posXAX1 < boxXRed2) {
				is_player_hitX = true;
			} else {
				is_player_hitX = false;
			}

			if (is_player_hitX == true) {
				is_player_hit = true;
			} else {
				is_player_hit = false;
			}
			
			//背景の描画
			for (int i = 0; i < 64; i++) {
				Novice::DrawSprite(backgroundX[i] - ScrollX, 0, backgroundHandle, 1, 1, 0.0f, WHITE);
			}
			for (int i = 0; i < 64; i++) {
				Novice::DrawSprite((boxX + 980 * i) - ScrollX, 328, boxHandle, 1, 1, 0.0f, WHITE);
			}

			//モードの切り替え
			if (modeDefault == true) {
				Novice::DrawSprite(posAX1, posY, playerWhiteHandle, 1, 1, 0.0f, WHITE);
				if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
					modeBreak = true;
					modeDefault = false;
					modeSlipthorugh = false;
				}
			}

			else if (modeBreak == true) {
				Novice::DrawSprite(posAX1, posY, playerRedHandle, 1, 1, 0.0f, WHITE);
				if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
					modeSlipthorugh = true;
					modeDefault = false;
					modeBreak = false;
				}
			}

			else if (modeSlipthorugh == true) {
				Novice::DrawSprite(posAX1, posY, playerBlueHandle, 1, 1, 0.0f, WHITE);
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
		
		Novice::ScreenPrintf(0, 0, "%d", is_player_hit);
		Novice::ScreenPrintf(0, 10, "%d", is_player_hitX);
		Novice::ScreenPrintf(0, 20, "%d<%d", posXAX1, boxXRed2);
		Novice::ScreenPrintf(0, 40, "%d<%d", boxXRed1, posXAX2);		

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
