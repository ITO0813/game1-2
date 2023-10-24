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

int Mainscene(
	int posX
	) {

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
	int backgroundX[84]{
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
	    1280 * 64, 1280 * 65, 1280 * 66, 1280 * 67,
		1280 * 68, 1280 * 69, 1280 * 70, 1280 * 71,
	    1280 * 72, 1280 * 73, 1280 * 74, 1280 * 75,
		1280 * 76, 1280 * 77, 1280 * 78, 1280 * 79,
	    1280 * 80, 1280 * 81, 1280 * 82, 1280 * 83,
	};

	for (int i = 0; i < 84; i++) {
		Novice::LoadTexture("./images/Game_screen2.png");
	};

	int posX = 32;
	int posY = 560;
	int posrad = 1;
	int posW = 50;
	int posH = 50;
	int speed = 15;
	int ScrollX = posX + posrad;
	int playerScroll = posX - ScrollX;

	int titleHandle = Novice::LoadTexture("./images/title1.png");

	int backgroundHandle = Novice::LoadTexture("./images/Game_screen2.png");
	
	int clearHandle = Novice::LoadTexture("./images/CLEAR.png");

	int scene;
	scene = titlescene;

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
		}

		if (scene != nextScene) {
			scene = nextScene;
		}

		if (scene == mainscene) {
			nextScene = Mainscene(posX);

			posX += speed;

			ScrollX = posX + posrad;

			if (ScrollX < 0) {
				ScrollX = 0;
			}
			if (ScrollX > World_Width - 1280) {
				ScrollX = World_Width - 1280;
			}
			playerScroll = posX - ScrollX;

			if (posX >= backgroundX[21]) {
				speed = 20;
			}
			if (posX >= backgroundX[42]) {
				speed = 25;
			}
			if (posX >= backgroundX[63]) {
				speed = 30;
			}

			if (posX >= 1280 * 83) {
				speed = 0;
			}
			
			for (int i = 0; i < 84; i++) {
				Novice::DrawSprite(backgroundX[i] - ScrollX, 0, backgroundHandle, 1, 1, 0.0f, WHITE);
			}
			Novice::DrawBox(playerScroll - posrad, posY - posrad, posW, posH, 0.0, WHITE, kFillModeSolid);

		}

		if (scene != nextScene) {
			scene = nextScene;
		}

		if (scene == clearscene) {
			nextScene = Clearscene(keys, preKeys, clearHandle);
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

		Novice::ScreenPrintf(0, 0, "%d", posX);
		Novice::ScreenPrintf(0, 20, "%d", speed);
		
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
