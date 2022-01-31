#include "Level.h"
#include "MapGeneration.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************

// 頂点１つあたりを表す構造体
//struct VERTEX_POSTEX {
//	float x, y, z;  // 頂点の位置
//
//	float u, v;  // テクスチャのUV座標
//};

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//#define MAX_SPRITE  2560 //(結構適当)
//// ポリゴン２つで１つの四角形（スプライト）。ポリゴンは３頂点なので、１スプライトは６頂点。
//#define VERTEX_PER_SPRITE  (3*2)
//#define VERTEX_BUFFER_SIZE  (MAX_SPRITE*sizeof(VERTEX_POSTEX)*VERTEX_PER_SPRITE)
//
//// オブジェクトの発生数 (多かったり少なかったりするとエラーが出る)
//#define MAX_OBJECT   308

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//ID3D11Buffer* gpVertexBuffer;  // 頂点バッファ用の変数
//ID3D11ShaderResourceView* gpTexture; // テクスチャ用変数

GameObject lBackGround;				//背景
GameObject gchoice;
GameObject groad;		//道
GameObject gstage[10];
GameObject gcloud[10];
GameObject gstar[10];
GameObject lFade;
GameObject lKorokoro;
GameObject lPause;
GameObject lCrystal;

FADE LevelFade;

int clear[10];

int countLevel = 10;

int pause;
int pauseChoice;

StageScore LevelScoreSheet[MAP_STAGE];
//GameObjectを追加するときは必ずMAX_OBJECTの数を合わせないとエラーが出るよ！

//*****************************************************************************
// 関数の定義　ここから　↓
//*****************************************************************************

BOOL Level_Initialize(StageScore score)
{
	// ゲーム時間の初期化をし、FPSを60に設定した。
	GameTimer_Initialize(60);

	//BGM再生
	XA_Play(SOUND_LABEL(SOUND_LABEL_BGM_LEVEL));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_MOVE));

	//背景
	lBackGround.texture = new Sprite("assets/level.png", 1, 1);
	lBackGround.texture->SetSize(1280 * 2, 720 * 2);
	lBackGround.posX = -1;
	lBackGround.posY = 1;

	gchoice.texture = new Sprite("assets/dotFont.png", 16, 8);
	gchoice.texture->SetSize(80, 160);
	gchoice.texture->SetPart(0, 0);
	gchoice.posX = 0.8f;
	gchoice.posY = 0.8f;

	//フェード
	lFade.texture = new Sprite("assets/TitleBG.png", 1, 1);
	lFade.texture->SetSize(1280 * 2, 720 * 2);
	lFade.posX = -1;
	lFade.posY = 1;
	lFade.texture->color.r = 0.0f;
	lFade.texture->color.g = 0.0f;
	lFade.texture->color.b = 0.0f;
	lFade.texture->color.a = 0.0f;
	LevelFade.framecnt = FADETIME - 0.1f;
	LevelFade.fadeout = false;

	//ころころ
	lKorokoro.texture = new Sprite("assets/fadekorokoro.png", 20, 2);
	lKorokoro.texture->SetSize(1280 * 2, 720 * 2);
	lKorokoro.posX = -1;
	lKorokoro.posY = 1;

	//ポーズ
	lPause.texture = new Sprite("assets/pause.png", 2, 1);
	lPause.texture->SetSize(1280 * 2, 720 * 2);
	lPause.posX = -1;
	lPause.posY = 1;

	//ポーズ
	lCrystal.texture = new Sprite("assets/crystal.png", 1, 1);
	lCrystal.texture->SetSize(256, 256);
	lCrystal.posX = -1;
	lCrystal.posY = 1;

	groad.texture = new Sprite("assets/road.png", 1, 10);
	groad.texture->SetSize(1330 * 2, 720 * 2.3);

	for (int i = 0; i < 10; i++) {
		gstage[i].texture = new Sprite("assets/Level_tile.png", 4, 1);
		gstage[i].texture->SetSize(320, 320);

		gcloud[i].texture = new Sprite("assets/cloud.png", 1, 1);
		gcloud[i].texture->SetSize(400, 160);

		gstar[i].texture = new Sprite("assets/Star.png", 1, 8);
		gstar[i].texture->SetSize(272, 100);
		gstar[i].texture->SetPart(0, 0);
	}

	for (int i = 0; i < 10; i++) {
		if (LevelScoreSheet[i] == TITLESCORE || LevelScoreSheet[i] == ZERO) {
			clear[i] = 2;
		}
		else
			clear[i] = 0;
	}
	clear[0] = 0;

	gstage[0].texture->SetPart(clear[0], 0);
	gstage[0].posX = -0.97f;
	gstage[0].posY = 0.48f;

	gstage[1].texture->SetPart(clear[1], 0);
	gstage[1].posX = -0.77f;
	gstage[1].posY = -0.1f;

	gstage[2].texture->SetPart(clear[2], 0);
	gstage[2].posX = -0.58f;
	gstage[2].posY = 0.68f;

	gstage[3].texture->SetPart(clear[3], 0);
	gstage[3].posX = -0.24f;
	gstage[3].posY = 0.54f;

	gstage[4].texture->SetPart(clear[4], 0);
	gstage[4].posX = -0.36f;
	gstage[4].posY = -0.14f;

	gstage[5].texture->SetPart(clear[5] + 1, 0);
	gstage[5].posX = 0.02f;
	gstage[5].posY = -0.23f;

	gstage[6].texture->SetPart(clear[6] + 1, 0);
	gstage[6].posX = 0.068f;
	gstage[6].posY = 0.58f;

	gstage[7].texture->SetPart(clear[7] + 1, 0);
	gstage[7].posX = 0.48f;
	gstage[7].posY = 0.7f;

	gstage[8].texture->SetPart(clear[8] + 1, 0);
	gstage[8].posX = 0.43f;
	gstage[8].posY = 0.04f;

	gstage[9].texture->SetPart(clear[9] + 1, 0);
	gstage[9].posX = 0.7f;
	gstage[9].posY = -0.25f;

	gcloud[0].texture->SetPart(0, 0);
	gcloud[0].posX = -1.0f;
	gcloud[0].posY = 0.19f;

	gcloud[1].texture->SetPart(0, 0);
	gcloud[1].posX = -0.8f;
	gcloud[1].posY = -0.38f;

	gcloud[2].texture->SetPart(0, 0);
	gcloud[2].posX = -0.61f;
	gcloud[2].posY = 0.4f;

	gcloud[3].texture->SetPart(0, 0);
	gcloud[3].posX = -0.27f;
	gcloud[3].posY = 0.26f;

	gcloud[4].texture->SetPart(0, 0);
	gcloud[4].posX = -0.39f;
	gcloud[4].posY = -0.42f;

	gcloud[5].texture->SetPart(0, 0);
	gcloud[5].posX = -0.01f;
	gcloud[5].posY = -0.51f;

	gcloud[6].texture->SetPart(0, 0);
	gcloud[6].posX = 0.04f;
	gcloud[6].posY = 0.3f;

	gcloud[7].texture->SetPart(0, 0);
	gcloud[7].posX = 0.45f;
	gcloud[7].posY = 0.42f;

	gcloud[8].texture->SetPart(0, 0);
	gcloud[8].posX = 0.4f;
	gcloud[8].posY = -0.24f;

	gcloud[9].texture->SetPart(0, 0);
	gcloud[9].posX = 0.67f;
	gcloud[9].posY = -0.53f;

	gstar[0].posX= -0.95f;
	gstar[0].posY = 0.16f;

	gstar[1].posX = -0.75f;
	gstar[1].posY = -0.42f;

	gstar[2].posX = -0.56f;
	gstar[2].posY = 0.36f;

	gstar[3].posX = -0.22f;
	gstar[3].posY = 0.22f;

	gstar[4].posX = -0.34f;
	gstar[4].posY = -0.46f;

	gstar[5].posX = 0.04f;
	gstar[5].posY = -0.56f;

	gstar[6].posX = 0.09f;
	gstar[6].posY = 0.25f;

	gstar[7].posX = 0.50f;
	gstar[7].posY = 0.38f;

	gstar[8].posX = 0.45f;
	gstar[8].posY = -0.28f;

	gstar[9].posX = 0.72f;
	gstar[9].posY = -0.57f;

	//スコアを代入
	if (score != TITLESCORE)
		LevelScoreSheet[stage - 1] = score;
	pause = lLEVEL;

	return TRUE;
}

BOOL Level_Update()
{
	Input_Update();  // このゲームで使うキーの押下状態を調べて保
	XINPUT_STATE state;
	XInputGetState(0, &state);

	groad.texture->SetPart(0, 0);
	groad.posX = -1.05f;
	groad.posY = 1.1f;

	GameObject_DrowUpdate(&lBackGround);
	GameObject_DrowUpdate(&gchoice);
	GameObject_DrowUpdate(&groad);
	GameObject_DrowUpdate(&lFade);
	GameObject_DrowUpdate(&lKorokoro);
	GameObject_DrowUpdate(&lPause);
	GameObject_DrowUpdate(&lCrystal);
	for (int i = 0; i < 10; i++)
	{
		//ステージ
		GameObject_DrowUpdate(&gstage[i]);
		//雲
		GameObject_DrowUpdate(&gcloud[i]);

		GameObject_DrowUpdate(&gstar[i]);
	}

	
	//if (Input_GetKeyTrigger('1') || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFTUP))
	//{
	//	stage = STAGE_1;
	//	gchoice.texture->SetPart(1, 0);
	//	gchoice.posX = 0.8f;
	//	gchoice.posY = 0.8f;

	//}
	//if (Input_GetKeyTrigger('2') || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHTUP))
	//{
	//	stage = STAGE_2;
	//	gchoice.texture->SetPart(2, 0);
	//	gchoice.posX = 0.8f;
	//	gchoice.posY = 0.8f;
	//}
	int size = 200;	//移動量の大きさ
	int cycle = 10;	//速さ
	switch (pause)
	{
	case lLEVEL:
		lPause.posX = 5.0f;
		lCrystal.posX = 5.0f;
		if (Input_GetKeyTrigger(VK_LEFT) || Input_GetControllerTrigger(XINPUT_GAMEPAD_DPAD_LEFT)) {
			stage--;
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_KA_SORU));
			if (stage == 0)
			{
				stage = 1;
				XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_KA_SORU));
			}
			gchoice.texture->SetPart(stage, 0);
			gchoice.posX = 0.8f;
			gchoice.posY = 0.8f;

			SetPos();
		}
		if (Input_GetKeyTrigger(VK_RIGHT) || Input_GetControllerTrigger(XINPUT_GAMEPAD_DPAD_RIGHT)) {
			stage++;
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_KA_SORU));
			if (stage == 11)
			{
				stage = 10;
				XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_KA_SORU));
			}
			gchoice.texture->SetPart(stage, 0);
			gchoice.posX = 0.8f;
			gchoice.posY = 0.8f;

			SetPos();
		}

		if (Input_GetKeyTrigger(VK_RETURN) || Input_GetControllerTrigger(XINPUT_GAMEPAD_B)) {
			LevelFade.fadeout = true;
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));
		}

		if (Input_GetKeyTrigger(VK_UP)) {
			pause = lPAUSE;
		}




		//上下にふわふわ移動する
		gstage[stage - 1].posY += sin(countLevel / cycle) / size;
		gcloud[stage - 1].posY += sin(countLevel / cycle) / size;
		countLevel++;
		break;
	case lPAUSE:
		lPause.posX = -1.0f;
		lCrystal.posX = -0.5f;
		if (Input_GetKeyTrigger(VK_LEFT)) {
			pauseChoice = 0;
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_KA_SORU));
			if (pauseChoice = -1)
			{
				pauseChoice = 0;
				//XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_KA_SORU));
			}
		}
		if (Input_GetKeyTrigger(VK_RIGHT)) {
			pauseChoice = 1;
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_KA_SORU));
			if (pauseChoice = 2)
			{
				pauseChoice = 1;
				//XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_KA_SORU));
			}
		}
		switch (pauseChoice)
		{
		case 0:
			lCrystal.posY = 0.3f;

			if (Input_GetKeyTrigger(VK_RETURN)) {
				XA_Play(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));
				LevelFade.fadeout = true;
			}
			break;
		case 1:
			lCrystal.posY = 0.0f;
			if (Input_GetKeyTrigger(VK_RETURN)) {
				XA_Play(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));
				pause = lLEVEL;
			}
		}
		break;
	}




	lKorokoro.texture->SetPart(korokoroX / 4, 0);
	korokoroX++;

	FadeChange(&LevelFade);//フェードを司る関数、触らないで
	lFade.texture->color.a = LevelFade.Alpha;
	if (LevelFade.Alpha > 1.0f)
		return FALSE;

	return TRUE;
}

void Level_Draw()
{
	// 画面クリア（指定色で塗りつぶし）
	// 塗りつぶし色の指定（小数：0.0f～1.0f）
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
	Direct3D_GetContext()->ClearRenderTargetView(Direct3D_GetRenderTargetView(), clearColor);

	//ゲームオブジェクトを全部描画する
	lBackGround.texture->Draw();

	gchoice.texture->Draw();
	groad.texture->Draw();

	for (int i = 0; i < 10; i++)
	{
		gcloud[i].texture->Draw();

		gstage[i].texture->Draw();

		gstar[i].texture->Draw();
	}
	lPause.texture->Draw();
	lCrystal.texture->Draw();
	lFade.texture->Draw();
	lKorokoro.texture->Draw();

	// ダブル・バッファのディスプレイ領域へのコピー命令
	Direct3D_GetSwapChain()->Present(0, 0);
}

void Level_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM_LEVEL));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_KA_SORU));
	delete lBackGround.texture;
	delete gchoice.texture;
	delete groad.texture;
	delete lFade.texture;
	delete lKorokoro.texture;
	delete lPause.texture;
	delete lCrystal.texture;
	for (int i = 0; i < 10; i++)
	{
		delete gstage[i].texture;
		delete gcloud[i].texture;
	}
}

void SetPos()
{
	gstage[0].texture->SetPart(clear[0], 0);
	gstage[0].posX = -0.97f;
	gstage[0].posY = 0.48f;

	gstage[1].texture->SetPart(clear[1], 0);
	gstage[1].posX = -0.77f;
	gstage[1].posY = -0.1f;

	gstage[2].texture->SetPart(clear[2], 0);
	gstage[2].posX = -0.58f;
	gstage[2].posY = 0.68f;

	gstage[3].texture->SetPart(clear[3], 0);
	gstage[3].posX = -0.24f;
	gstage[3].posY = 0.54f;

	gstage[4].texture->SetPart(clear[4], 0);
	gstage[4].posX = -0.36f;
	gstage[4].posY = -0.14f;

	gstage[5].texture->SetPart(clear[5] + 1, 0);
	gstage[5].posX = 0.02f;
	gstage[5].posY = -0.23f;

	gstage[6].texture->SetPart(clear[6] + 1, 0);
	gstage[6].posX = 0.068f;
	gstage[6].posY = 0.58f;

	gstage[7].texture->SetPart(clear[7] + 1, 0);
	gstage[7].posX = 0.48f;
	gstage[7].posY = 0.7f;

	gstage[8].texture->SetPart(clear[8] + 1, 0);
	gstage[8].posX = 0.43f;
	gstage[8].posY = 0.04f;

	gstage[9].texture->SetPart(clear[9] + 1, 0);
	gstage[9].posX = 0.7f;
	gstage[9].posY = -0.25f;

	gcloud[0].texture->SetPart(0, 0);
	gcloud[0].posX = -1.0f;
	gcloud[0].posY = 0.19f;

	gcloud[1].texture->SetPart(0, 0);
	gcloud[1].posX = -0.8f;
	gcloud[1].posY = -0.38f;

	gcloud[2].texture->SetPart(0, 0);
	gcloud[2].posX = -0.61f;
	gcloud[2].posY = 0.4f;

	gcloud[3].texture->SetPart(0, 0);
	gcloud[3].posX = -0.27f;
	gcloud[3].posY = 0.26f;

	gcloud[4].texture->SetPart(0, 0);
	gcloud[4].posX = -0.39f;
	gcloud[4].posY = -0.42f;

	gcloud[5].texture->SetPart(0, 0);
	gcloud[5].posX = -0.01f;
	gcloud[5].posY = -0.51f;

	gcloud[6].texture->SetPart(0, 0);
	gcloud[6].posX = 0.04f;
	gcloud[6].posY = 0.3f;

	gcloud[7].texture->SetPart(0, 0);
	gcloud[7].posX = 0.45f;
	gcloud[7].posY = 0.42f;

	gcloud[8].texture->SetPart(0, 0);
	gcloud[8].posX = 0.4f;
	gcloud[8].posY = -0.24f;

	gcloud[9].texture->SetPart(0, 0);
	gcloud[9].posX = 0.67f;
	gcloud[9].posY = -0.53f;
}