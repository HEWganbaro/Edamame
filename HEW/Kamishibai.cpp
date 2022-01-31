#include "Kamishibai.h"


//*****************************************************************************
// グローバル変数
//*****************************************************************************

GameObject kBackGround;				//背景
GameObject kFade;
GameObject kKorokoro;
GameObject kKamishibai;

FADE KamiFade;
int page = 0;

//*****************************************************************************
// 関数の定義　ここから　↓
//*****************************************************************************

BOOL Kamishibai_Initialize()
{
	// ゲーム時間の初期化をし、FPSを60に設定した。
	GameTimer_Initialize(60);

	//BGM再生
	XA_Play(SOUND_LABEL(SOUND_LABEL_BGM_TITLE));

	////背景
	//tBackGround.texture = new Sprite("assets/TitleBG.png", 1, 1);
	//tBackGround.texture->SetSize(1280 * 2, 720 * 2);
	//tBackGround.posX = -1;
	//tBackGround.posY = 1;

	//背景
	kBackGround.texture = new Sprite("assets/TitleBG.png", 1, 1);
	kBackGround.texture->SetSize(1280 * 2, 720 * 2);
	kBackGround.posX = -1;
	kBackGround.posY = 1;

	//背景
	kKamishibai.texture = new Sprite("assets/Kamishibai.png", 8, 1);
	kKamishibai.texture->SetSize(1280 * 2, 720 * 2);
	kKamishibai.posX = -1;
	kKamishibai.posY = 1;

	//フェード
	kFade.texture = new Sprite("assets/TitleBG.png", 1, 1);
	kFade.texture->SetSize(1280 * 2, 720 * 2);
	kFade.posX = -1;
	kFade.posY = 1;
	kFade.texture->color.r = 0.0f;
	kFade.texture->color.g = 0.0f;
	kFade.texture->color.b = 0.0f;
	kFade.texture->color.a = 0.0f;
	KamiFade.framecnt = FADETIME - 0.1f;
	KamiFade.fadeout = false;

	//ころころ
	kKorokoro.texture = new Sprite("assets/fadekorokoro.png", 20, 2);
	kKorokoro.texture->SetSize(1280 * 2, 720 * 2);
	kKorokoro.posX = -1;
	kKorokoro.posY = 1;

	page = 0;
	
	return TRUE;
}

// ゲームループ中に実行したい、ゲームの処理を書く関数
BOOL Kamishibai_Update()
{
	Input_Update();  // このゲームで使うキーの押下状態を調べて保
	XINPUT_STATE state;
	XInputGetState(0, &state);

	if (Input_GetKeyTrigger(VK_RIGHT)) {
		page++;
		if (page % 2 == 0) {
			//BGM再生
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_PAPER));
		}
		else
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_PAPER));
		if (page > 7) {
			korokoroX = 0;
			KamiFade.fadeout = true;
		}
	}
	kKamishibai.texture->SetPart(page, 0);

	GameObject_DrowUpdate(&kBackGround);
	GameObject_DrowUpdate(&kKamishibai);
	GameObject_DrowUpdate(&kFade);
	GameObject_DrowUpdate(&kKorokoro);
	
	kKorokoro.texture->SetPart(korokoroX / 4, 0);
	korokoroX++;
	FadeChange(&KamiFade);//フェードを司る関数、触らないで
	kFade.texture->color.a = KamiFade.Alpha;
	if (KamiFade.Alpha > 1.0f)
		return FALSE;
	
}
void Kamishibai_Draw()
{
	// 画面クリア（指定色で塗りつぶし）
	// 塗りつぶし色の指定（小数：0.0f～1.0f）
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
	Direct3D_GetContext()->ClearRenderTargetView(Direct3D_GetRenderTargetView(), clearColor);

	//ゲームオブジェクトを全部描画する
	kBackGround.texture->Draw();
	kKamishibai.texture->Draw();
	kFade.texture->Draw();
	kKorokoro.texture->Draw();

	// ダブル・バッファのディスプレイ領域へのコピー命令
	Direct3D_GetSwapChain()->Present(0, 0);

}
void Kamishibai_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM_TITLE));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_PAPER));
	delete kBackGround.texture;
	delete kKamishibai.texture;
	delete kFade.texture;
	delete kKorokoro.texture;

}
