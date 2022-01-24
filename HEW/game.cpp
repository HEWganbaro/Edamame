//*****************************************************************************
// DX21　サンプルソース
// ゲームのメインとなる処理を書いていくソースファイル
//*****************************************************************************

#include "game.h"

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

// オブジェクトの発生数 (多かったり少なかったりするとエラーが出る)
#define MAX_OBJECT   304

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//ID3D11Buffer* gpVertexBuffer;  // 頂点バッファ用の変数
//ID3D11ShaderResourceView* gpTexture; // テクスチャ用変数

	//ステージ数[ステージ][高さ][左下][右下]
int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE];
vector<MapPos> StoneMap;

GameObject gObjects[MAX_OBJECT];  // オブジェクト配列

GameObject* NoHeight = gObjects + 300;
GameObject* NoLeftDown = gObjects + 301;
GameObject* NoRightDown = gObjects + 302;
GameObject* tile = gObjects + 303;

GameObject gPlayer1;
GameObject gPlayer2;
GameObject gEnemy;
vector<GameObject> gEnemyVector;
GameObject gBackGround;				//背景

GameObject gEffect[4];

//GameObjectを追加するときは必ずMAX_OBJECTの数を合わせないとエラーが出るよ！

//*****************************************************************************
// 関数の定義　ここから　↓
//*****************************************************************************

BOOL Game_Initialize()
{
	// ゲーム時間の初期化をし、FPSを60に設定した。
	GameTimer_Initialize(60);
	/* 乱数系列の変更 */
	srand((unsigned)time(NULL));
	
	//BGM再生
	XA_Play(SOUND_LABEL(SOUND_LABEL_BGM000));

	// CSVを配列に格納
	ifstream ifs("assets/data.csv");
	for (int l = 0; l < MAP_STAGE; l++) {
		string line;
		int j = 0;
		int k = 0;
		bool end = false; //高さのフラグ （CSVでは-9）
		bool stage = false;	//ステージのフラグ (CSVでは-99)
		while (getline(ifs, line)) {

			vector<string> strvec = split(line, ',');

			for (int i = 0; i < strvec.size(); i++) {
				if (-9 == stoi(strvec.at(i))) {
					end = true;
					break;
				}
				if (-99 == stoi(strvec.at(i))) {
					end = true;
					break;
				}
				MapChip[l][k][j][i] = stoi(strvec.at(i));
			}
			j++;
			if (end == true) {
				k++;
				j = 0;
				end = false;
			}
			if (stage == true) {
				l++;
				j = 0;
				k = 0;
				stage = false;
			}
		}
	}

	turn = PLAYER_TURN;

	// マップ生成
	Map_Initialize(gObjects);

	//エフェクト生成
	for (int i = 0; i < 4; i++) {
		Effect_Init(&gEffect[i]);
	}

	//雪玉の初期化
	Player_Initialize(&gPlayer1);
	Player_Initialize(&gPlayer2);

	////雪玉の場所指定
	Player_SetLocation(&gPlayer1, gObjects, 0, 5, 5);
	Player_SetLocation(&gPlayer2, gObjects, 0, 6, 6);

	//マップ変更
	Map_Update(gObjects, &StoneMap, MapChip);

	//敵の場所指定
	//敵の場所を指定しておく
	switch (Map_GetStage())
	{
	case 0:
		//敵の初期化
		Enemy_Initialize(&gEnemy, RANDOM);
		Enemy_SetLocation(&gEnemy, gObjects, 0, 4, 6);
		gEnemyVector.emplace_back(gEnemy);

		Enemy_Initialize(&gEnemy, RANDOM);
		Enemy_SetLocation(&gEnemy, gObjects, 0, 5, 4);
		gEnemyVector.emplace_back(gEnemy);
		break;

	default:
		break;
	}

	//背景描画
	gBackGround.texture = new Sprite("assets/BackGround.png", 1, 1);
	gBackGround.texture->SetSize(1280 * 2, 720 * 2);
	gBackGround.posX = -1;
	gBackGround.posY = 1;

	//デバック用
	NoHeight->texture = new Sprite("assets/dotFont.png", 16, 8);
	NoHeight->texture->SetSize(80, 160);
	NoLeftDown->texture = new Sprite("assets/dotFont.png", 16, 8);
	NoLeftDown->texture->SetSize(80, 160);
	NoRightDown->texture = new Sprite("assets/dotFont.png", 16, 8);
	NoRightDown->texture->SetSize(80, 160);
	tile->texture = new Sprite("assets/Mapseat_v2.png", 7, 1);
	tile->texture->SetSize(200, 200);

	return TRUE;
}


// ゲームループ中に実行したい、ゲームの処理を書く関数
BOOL Game_Update()
{
	Input_Update();  // このゲームで使うキーの押下状態を調べて保
	XINPUT_STATE state;
	XInputGetState(0, &state);

	//デバック用
	NoHeight->texture->SetPart(gPlayer1.mappos.Height, 0);
	NoHeight->posX = 0.5f;
	NoHeight->posY = 0.5f;
	NoLeftDown->texture->SetPart(gPlayer1.mappos.LeftDown, 1);
	NoLeftDown->posX = 0.6f;
	NoLeftDown->posY = 0.5f;
	NoRightDown->texture->SetPart(gPlayer1.mappos.RightDown, 2);
	NoRightDown->posX = 0.7f;
	NoRightDown->posY = 0.5f;
	tile->texture->SetPart(Map_GetPlayerTile(&gPlayer1, gObjects), 0);
	tile->posX = 0.3;
	tile->posY = 0.6;
	gBackGround.posX = -1;
	gBackGround.posY = 1;

	for (int i = 0; i < 4; i++) {
		Efffect_Move(&gEffect[i]);
	}

	switch (turn)
	{
	case PLAYER_TURN:
		//プレイヤー移動
		gPlayer1.animator.isActive = true;
		gPlayer2.animator.isActive = true;
		Player_Input(&gPlayer1, &gPlayer2);	
		Player_Update(&gPlayer1, gObjects);
		Player_Update(&gPlayer2, gObjects);
		if (gPlayer1.animator.isActive == false || gPlayer2.animator.isActive == false)
			turn = ENEMY_TURN;
		break;

	case ENEMY_TURN:
	{
		bool end = false;
		//敵移動
		for (int i = 0; i < gEnemyVector.size(); i++) {
			if (gEnemyVector[i].direction == NULL_WAY && gEnemyVector[i].animator.oneAni == false) {
				//敵の接近
				if (gEnemyVector[i].direction == NULL_WAY) {
					//敵のタイプに合わせて行動変化
					switch (gEnemyVector[i].enemytype) {
					case RANDOM:
						Enemy_Move_Random(&gEnemyVector[i]);
						break;

					case FOLLOWING:
						Enemy_Move_Chase(&gEnemyVector[i], &gPlayer1, &gPlayer2);
						break;

					case CIRCUMFRENCE:
						Enemy_Move_Circle(&gEnemyVector[i]);
						break;
					}
				}
				end = true;
			}
			else {
				//敵の移動処理
				MapMove_Update(&gEnemyVector[i], gObjects);
				if (gEnemyVector[i].animator.isActive != false) {
					end = true;
					gEnemyVector[i].animator.oneAni = true;
				}
			}
			//敵のスタン
			//Enemy_Stun(&gEnemy, &gPlayer1, &gPlayer2, gObjects, MapChip);
		}
		if (end == false) {
			turn = ENV_TURN;
			for (int i = 0; i < gEnemyVector.size(); i++) 
				gEnemyVector[i].animator.oneAni = false;
		}
	}
		break;

	case ENV_TURN:
		toIce(gObjects);
		for (int i = 0; i < gEnemyVector.size(); i++)
			Enemy_Player_Hit(&gEnemyVector[i], &gPlayer1, &gPlayer2);
		if (gPlayer1.Goalfrg == true && gPlayer2.Goalfrg == true)
			turn = CLEAR;
		break;

	case GAMEOVER:
		//タイトルへ戻るフラグ
		if (Input_GetKeyTrigger(VK_SPACE) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A))
			return FALSE;
		break;

	case CLEAR:
		if (Input_GetKeyTrigger(VK_SPACE) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A))
			return FALSE;
		break;
	}

	//if (gEnemy.enemyeye == ENEMYEYE_IN)
	//{
	//	//遮蔽でのヘイトそらし
	//	for (int i = 0; i < StoneMap.size(); i++) {
	//		Shield_Cancel(&StoneMap[i], &gPlayer1, &gPlayer2, &gEnemy);
	//	}
	//}

	// オブジェクト配列のXY計算、UV計算、頂点配列への適用を一括処理
	//GameObjectと画像の座標を合わせる
	for (int i = 0; i < MAX_OBJECT; i++) {
		GameObject_DrowUpdate(&gObjects[i]);
	}
	GameObject_DrowUpdate(&gPlayer1);
	GameObject_DrowUpdate(&gPlayer2);
	for (int i = 0; i < gEnemyVector.size(); i++)
		GameObject_DrowUpdate(&gEnemyVector[i]);
	GameObject_DrowUpdate(&gBackGround);
	for (int i = 0; i < 4; i++) {
		GameObject_DrowUpdate(&gEffect[i]);
	}
		
	return TRUE;
}

void Game_Draw()
{
	// 画面クリア（指定色で塗りつぶし）
	// 塗りつぶし色の指定（小数：0.0f～1.0f）
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
	Direct3D_GetContext()->ClearRenderTargetView(Direct3D_GetRenderTargetView(), clearColor);

	//ゲームオブジェクトを全部描画する
	gBackGround.texture->Draw();
	gEffect[0].texture->Draw();
	gEffect[1].texture->Draw();
	for (int i = 0; i < MAX_OBJECT; i++)
		gObjects[i].texture->Draw();
	gPlayer1.texture->Draw();
	gPlayer2.texture->Draw();
	for (int i = 0; i < gEnemyVector.size(); i++)
		gEnemyVector[i].texture->Draw();
	gEffect[2].texture->Draw();
	gEffect[3].texture->Draw();

	// ダブル・バッファのディスプレイ領域へのコピー命令
	Direct3D_GetSwapChain()->Present(0, 0);
}

//作ったGameObjectはちゃんとdeleteしよう！
void Game_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM000));

	delete gPlayer1.texture;
	delete gPlayer2.texture;
	for (int i = 0; i < gEnemyVector.size(); i++)
		delete gEnemyVector[i].texture;
	gEnemyVector.clear();
	delete gBackGround.texture;
	for (int i = 0; i < 4; i++)
		delete gEffect[i].texture;
	for (int i = 0; i < MAX_OBJECT; i++) {
		delete gObjects[i].texture;
		gObjects[i].posX = 0;
		gObjects[i].posY = 0;
	}
}
