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
GameObject glevel;
GameObject glevel2;
GameObject gchoice;
//GameObjectを追加するときは必ずMAX_OBJECTの数を合わせないとエラーが出るよ！

//*****************************************************************************
// 関数の定義　ここから　↓
//*****************************************************************************

BOOL Level_Initialize()
{
	// ゲーム時間の初期化をし、FPSを60に設定した。
	GameTimer_Initialize(60);

	//BGM再生
	XA_Play(SOUND_LABEL(SOUND_LABEL_BGM000));

	//背景
	lBackGround.texture = new Sprite("assets/BackGround.png", 1, 1);
	lBackGround.texture->SetSize(1280 * 2, 720 * 2);
	lBackGround.posX = -1;
	lBackGround.posY = 1;

	glevel.texture = new Sprite("assets/dotFont.png", 16, 8);
	glevel.texture->SetSize(80, 160);

	glevel2.texture = new Sprite("assets/dotFont.png", 16, 8);
	glevel2.texture->SetSize(80, 160);

	gchoice.texture = new Sprite("assets/dotFont.png", 16, 8);
	gchoice.texture->SetSize(80, 160);
	gchoice.texture->SetPart(0, 0);
	gchoice.posX = 0.8f;
	gchoice.posY = 0.8f;

	return TRUE;
}

BOOL Level_Update()
{
	Input_Update();  // このゲームで使うキーの押下状態を調べて保
	XINPUT_STATE state;
	XInputGetState(0, &state);

	glevel.texture->SetPart(1, 0);
	glevel.posX = -0.5f;
	glevel.posY = 0.1f;

	glevel2.texture->SetPart(2, 0);
	glevel2.posX = 0.4f;
	glevel2.posY = 0.1f;

	if (Input_GetKeyTrigger(VK_RETURN) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)) {
		return FALSE;
	}

	if (Input_GetKeyTrigger('1') || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFTUP))
	{
		stage = STAGE_1;
		gchoice.texture->SetPart(1, 0);
		gchoice.posX = 0.8f;
		gchoice.posY = 0.8f;
	}

	if (Input_GetKeyTrigger('2') || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHTUP))
	{
		stage = STAGE_2;
		gchoice.texture->SetPart(2, 0);
		gchoice.posX = 0.8f;
		gchoice.posY = 0.8f;
	}
	GameObject_DrowUpdate(&lBackGround);
	GameObject_DrowUpdate(&glevel);
	GameObject_DrowUpdate(&glevel2);
	GameObject_DrowUpdate(&gchoice);

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

	glevel.texture->Draw();
	glevel2.texture->Draw();
	gchoice.texture->Draw();

	// ダブル・バッファのディスプレイ領域へのコピー命令
	Direct3D_GetSwapChain()->Present(0, 0);
}

void Level_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM000));
	delete lBackGround.texture;
	delete glevel.texture;
	delete glevel2.texture;
	delete gchoice.texture;
}