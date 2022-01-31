#include "GameOver.h"

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

GameObject oBackGround;				//背景
GameObject oLogo;
GameObject oFade;
GameObject oFadeLogo;
GameObject oPlayer;

FADE GameOverFade;
FADE GameLogo;
//GameObjectを追加するときは必ずMAX_OBJECTの数を合わせないとエラーが出るよ！

//*****************************************************************************
// 関数の定義　ここから　↓
//*****************************************************************************

BOOL GameOver_Initialize()
{
	// ゲーム時間の初期化をし、FPSを60に設定した。
	GameTimer_Initialize(60);

	//BGM再生
	XA_Play(SOUND_LABEL(SOUND_LABEL_BGM_GAMEOVER));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_PLAYERCRUSH));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_SNOWHUNDA));

	//背景
	oBackGround.texture = new Sprite("assets/追加テクスチャ/gameover_1.png", 1, 1);
	oBackGround.texture->SetSize(1280 * 2, 720 * 2);
	oBackGround.posX = -1;
	oBackGround.posY = 1;

	oPlayer.texture = new Sprite("assets/Player_kansei.png", 48, 8);
	oPlayer.texture->SetSize(512, 512);
	oPlayer.posX = -0.25f;
	oPlayer.posY = -0.2f;
	oPlayer.animator.speed = 8.0f;

	oLogo.texture = new Sprite("assets/追加テクスチャ/gameover_2.png", 1, 1);
	oLogo.texture->SetSize(1280 * 2, 720 * 2);
	oLogo.posX = -1;
	oLogo.posY = 1;

	//フェード
	oFade.texture = new Sprite("assets/追加テクスチャ/gameover_1.png", 1, 1);
	oFade.texture->SetSize(1280 * 2, 720 * 2);
	oFade.posX = -1;
	oFade.posY = 1;
	oFade.texture->color.r = 0.0f;
	oFade.texture->color.g = 0.0f;
	oFade.texture->color.b = 0.0f;
	oFade.texture->color.a = 0.0f;
	GameOverFade.framecnt = FADETIME - 0.1f;
	GameOverFade.fadeout = false;

	oFadeLogo.texture = new Sprite("assets/追加テクスチャ/gameover_2.png", 1, 1);
	oFadeLogo.texture->SetSize(1280 * 2, 720 * 2);
	oFadeLogo.posX = -1;
	oFadeLogo.posY = 1;
	oFadeLogo.texture->color.r = 0.0f;
	oFadeLogo.texture->color.g = 0.0f;
	oFadeLogo.texture->color.b = 0.0f;
	oFadeLogo.texture->color.a = 0.0f;
	GameLogo.framecnt = FADETIME - 0.1f;
	GameLogo.fadeout = true;

	

	return TRUE;
}


// ゲームループ中に実行したい、ゲームの処理を書く関数
BOOL GameOver_Update()
{
	Input_Update();  // このゲームで使うキーの押下状態を調べて保
	XINPUT_STATE state;
	XInputGetState(0, &state);

	GameObject_DrowUpdate(&oBackGround);
	GameObject_DrowUpdate(&oPlayer);
	GameObject_DrowUpdate(&oLogo);
	GameObject_DrowUpdate(&oFade);
	GameObject_DrowUpdate(&oFadeLogo);

	Animator_Update(&oPlayer.animator);
	oPlayer.animator.isActive = true;

	oPlayer.texture->SetPart(oPlayer.animator.frame, 0);

	for (int i = 0; i < 10; i++)
	{
		oPlayer.posY += 0.0001;
	}

	if (Input_GetKeyTrigger(VK_SPACE) || Input_GetControllerTrigger(XINPUT_GAMEPAD_B))
	{
		GameOverFade.fadeout = true;
		XA_Play(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));
	}

	FadeChange(&GameLogo);//フェードを司る関数、触らないで
	oFadeLogo.texture->color.a = GameLogo.Alpha;
	GameLogo.fadeout = false;

	FadeChange(&GameOverFade);//フェードを司る関数、触らないで
	oFade.texture->color.a = GameOverFade.Alpha;
	if (GameOverFade.Alpha > 1.0f)
		return FALSE;

	return TRUE;
}

void GameOver_Draw()
{
	// 画面クリア（指定色で塗りつぶし）
	// 塗りつぶし色の指定（小数：0.0f～1.0f）
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
	Direct3D_GetContext()->ClearRenderTargetView(Direct3D_GetRenderTargetView(), clearColor);

	//ゲームオブジェクトを全部描画する
	oBackGround.texture->Draw();
	oPlayer.texture->Draw();
	oLogo.texture->Draw();
	oFade.texture->Draw();
	oFadeLogo.texture->Draw();

	// ダブル・バッファのディスプレイ領域へのコピー命令
	Direct3D_GetSwapChain()->Present(0, 0);
}

//作ったGameObjectはちゃんとdeleteしよう！
void GameOver_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM_GAMEOVER));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));
	delete oBackGround.texture;
	delete oPlayer.texture;
	delete oLogo.texture;
	delete oFade.texture;
	delete oFadeLogo.texture;
}