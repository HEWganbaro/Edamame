#include "GameClear.h"

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

GameObject cBackGround;				//背景
GameObject cFade;

FADE GameClearFade;
//GameObjectを追加するときは必ずMAX_OBJECTの数を合わせないとエラーが出るよ！

//*****************************************************************************
// 関数の定義　ここから　↓
//*****************************************************************************

BOOL GameClear_Initialize()
{
	// ゲーム時間の初期化をし、FPSを60に設定した。
	GameTimer_Initialize(60);

	//BGM再生
	XA_Play(SOUND_LABEL(SOUND_LABEL_BGM_GAME));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_PLAYERCRUSH));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_SNOWHUNDA));

	//背景
	cBackGround.texture = new Sprite("assets/追加テクスチャ/GameClear.png", 8, 1);
	cBackGround.texture->SetSize(1280 * 2, 720 * 2);
	cBackGround.posX = -1;
	cBackGround.posY = 1;
	cBackGround.animator.speed = 8.0f;

	//フェード
	cFade.texture = new Sprite("assets/追加テクスチャ/GameClear.png", 8, 1);
	cFade.texture->SetSize(1280 * 2, 720 * 2);
	cFade.posX = -1;
	cFade.posY = 1;
	cFade.texture->color.r = 0.0f;
	cFade.texture->color.g = 0.0f;
	cFade.texture->color.b = 0.0f;
	cFade.texture->color.a = 0.0f;
	GameClearFade.framecnt = FADETIME - 0.1f;

	return TRUE;
}


// ゲームループ中に実行したい、ゲームの処理を書く関数
BOOL GameClear_Update()
{
	Input_Update();  // このゲームで使うキーの押下状態を調べて保
	XINPUT_STATE state;
	XInputGetState(0, &state);

	Animator_Update(&cBackGround.animator);
	cBackGround.animator.isActive = true;

	cBackGround.texture->SetPart(cBackGround.animator.frame, 0);

	GameObject_DrowUpdate(&cBackGround);

	GameObject_DrowUpdate(&cFade);

	if (Input_GetKeyTrigger(VK_SPACE))
	{
		GameClearFade.fadeout = true;
		XA_Play(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));
	}

	FadeChange(&GameClearFade);//フェードを司る関数、触らないで
	cFade.texture->color.a = GameClearFade.Alpha;
	if (GameClearFade.Alpha > 1.0f)
		return FALSE;

	return TRUE;
}

void GameClear_Draw()
{
	// 画面クリア（指定色で塗りつぶし）
	// 塗りつぶし色の指定（小数：0.0f～1.0f）
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
	Direct3D_GetContext()->ClearRenderTargetView(Direct3D_GetRenderTargetView(), clearColor);

	//ゲームオブジェクトを全部描画する
	cBackGround.texture->Draw();
	cFade.texture->Draw();
	// ダブル・バッファのディスプレイ領域へのコピー命令
	Direct3D_GetSwapChain()->Present(0, 0);
}

//作ったGameObjectはちゃんとdeleteしよう！
void GameClear_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM_GAME));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));
	delete cBackGround.texture;
	delete cFade.texture;
}