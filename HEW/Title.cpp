#include "Title.h"

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

GameObject tBackGround;				//背景
GameObject tLogo;                   //タイトルロゴ
GameObject tFade;

FADE TitleFade;

//GameObjectを追加するときは必ずMAX_OBJECTの数を合わせないとエラーが出るよ！

//*****************************************************************************
// 関数の定義　ここから　↓
//*****************************************************************************

BOOL Title_Initialize()
{
	// ゲーム時間の初期化をし、FPSを60に設定した。
	GameTimer_Initialize(60);

	//BGM再生
	XA_Play(SOUND_LABEL(SOUND_LABEL_BGM_TITLE));

	//背景
	tBackGround.texture = new Sprite("assets/TitleBG.png", 1, 1);
	tBackGround.texture->SetSize(1280 * 2, 720 * 2);
	tBackGround.posX = -1;
	tBackGround.posY = 1;
	//ロゴ
	tLogo.texture = new Sprite("assets/TitleLOGO.png", 1, 1);
	tLogo.texture->SetSize(1280 * 2, 720 * 2);
	tLogo.posX = -1;
	tLogo.posY = 1;
	//フェード
	tFade.texture = new Sprite("assets/TitleBG.png", 1, 1);
	tFade.texture->SetSize(1280 * 2, 720 * 2);
	tFade.posX = -1;
	tFade.posY = 1;
	tFade.texture->color.r = 0.0f;
	tFade.texture->color.g = 0.0f;
	tFade.texture->color.b = 0.0f;
	tFade.texture->color.a = 0.0f;
	TitleFade.framecnt = FADETIME - 0.1f;

	return TRUE;
}


// ゲームループ中に実行したい、ゲームの処理を書く関数
BOOL Title_Update()
{
	Input_Update();  // このゲームで使うキーの押下状態を調べて保
	XINPUT_STATE state;
	XInputGetState(0, &state);

	GameObject_DrowUpdate(&tBackGround);
	GameObject_DrowUpdate(&tLogo);
	GameObject_DrowUpdate(&tFade);

	if (Input_GetKeyTrigger(VK_SPACE))
	{
		TitleFade.fadeout = true;
		XA_Play(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));
	}

	FadeChange(&TitleFade);//フェードを司る関数、触らないで
	tFade.texture->color.a = TitleFade.Alpha;
	if (TitleFade.Alpha > 1.0f)
		return FALSE;
	
	return TRUE;
}

void Title_Draw()
{
	// 画面クリア（指定色で塗りつぶし）
	// 塗りつぶし色の指定（小数：0.0f～1.0f）
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
	Direct3D_GetContext()->ClearRenderTargetView(Direct3D_GetRenderTargetView(), clearColor);

	//ゲームオブジェクトを全部描画する
	tBackGround.texture->Draw();
	tLogo.texture->Draw();
	tFade.texture->Draw();
	// ダブル・バッファのディスプレイ領域へのコピー命令
	Direct3D_GetSwapChain()->Present(0, 0);
}

//作ったGameObjectはちゃんとdeleteしよう！
void Title_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM_TITLE));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));
	delete tBackGround.texture;
	delete tLogo.texture;
	delete tFade.texture;
}