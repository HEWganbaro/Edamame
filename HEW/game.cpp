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
#define MAX_OBJECT   308

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//ID3D11Buffer* gpVertexBuffer;  // 頂点バッファ用の変数
//ID3D11ShaderResourceView* gpTexture; // テクスチャ用変数

	//ステージ数[ステージ][高さ][左下][右下]
int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE];
vector<MapPos> StoneMap;

GameObject gObjects[MAX_OBJECT];  // オブジェクト配列
GameObject* gPlayer = gObjects + 300;
GameObject* NoHeight = gObjects + 301;
GameObject* NoLeftDown = gObjects + 302;
GameObject* NoRightDown = gObjects + 303;
GameObject* tile = gObjects + 304;
GameObject* gEnemy = gObjects + 305;
GameObject* gGoal = gObjects + 306;
GameObject* gPlayer2 = gObjects + 307;

GameObject gBackGround;				//背景
//GameObjectを追加するときは必ずMAX_OBJECTの数を合わせないとエラーが出るよ！

//*****************************************************************************
// 関数の定義　ここから　↓
//*****************************************************************************

BOOL Game_Initialize()
{
	// ゲーム時間の初期化をし、FPSを60に設定した。
	GameTimer_Initialize(60);
	
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

	// マップ生成
	Map_Initialize(gObjects);

	//プレイヤー初期化
	Player_Initialize(gPlayer, gPlayer2);

	//プレイヤー場所指定
	Player_SetLocation(gPlayer, gObjects, 0, 5, 5,
						gPlayer2, gObjects, 0, 6, 6);

	////雪玉の初期化
	//SnowBall_Initialize(SnowBall, SnowBall2);
	////雪玉の場所指定
	//SnowBall_SetLocation(SnowBall, gObjects, 0, 6, 4,
	//					 SnowBall2, gObjects, 0, 4, 6);

	//敵の初期化
	Enemy_Initialize(gEnemy);

	//敵の場所指定
	Enemy_SetLocation(gEnemy, gObjects, 0, 4, 4);

	//遮蔽の初期化
	//Shield_Initialize(gShield);
	//遮蔽の場所指定
	//Shield_SetLocation(gShield, gObjects, 0, 3, 6);

	//ゴールの初期化
	Goal_Initialize(gGoal);

	//ゴールの場所指定
	Goal_SetLocation(gGoal, gObjects, 0, 6, 7);

	//デバック用
	NoHeight->texture = new Sprite("assets/No.png", 13, 7);
	NoHeight->texture->SetSize(80, 80);
	NoLeftDown->texture = new Sprite("assets/No.png", 13, 7);
	NoLeftDown->texture->SetSize(80, 80);
	NoRightDown->texture = new Sprite("assets/No.png", 13, 7);
	NoRightDown->texture->SetSize(80, 80);
	tile->texture = new Sprite("assets/MapSeat.png", 6, 1);
	tile->texture->SetSize(200, 200);
	gBackGround.texture = new Sprite("assets/BackGround.png", 1, 1);
	gBackGround.texture->SetSize(1280*2, 720*2);

	return TRUE;
}


// ゲームループ中に実行したい、ゲームの処理を書く関数
BOOL Game_Update()
{
	Input_Update();  // このゲームで使うキーの押下状態を調べて保

	//デバック用
	NoHeight->texture->SetPart(gPlayer->mappos.Height, 0);
	NoHeight->posX = 0.5f;
	NoHeight->posY = 0.5f;
	NoLeftDown->texture->SetPart(gPlayer->mappos.LeftDown, 0);
	NoLeftDown->posX = 0.6f;
	NoLeftDown->posY = 0.5f;
	NoRightDown->texture->SetPart(gPlayer->mappos.RightDown, 0);
	NoRightDown->posX = 0.7f;
	NoRightDown->posY = 0.5f;
	tile->texture->SetPart(Map_GetPlayerTile(gPlayer, gObjects), 0);
	tile->posX = 0.3;
	tile->posY = 0.6;
	gBackGround.posX = -1;
	gBackGround.posY = 1;

	Map_Update(gObjects, &StoneMap, MapChip);	//マップ変更↑↓

	//SnowBall_Hit(gPlayer, SnowBall); //雪玉当たり判定
	//SnowBall_Hit(gPlayer, SnowBall2);
	//SnowBall_Hit(gPlayer2, SnowBall);
	//SnowBall_Hit(gPlayer2, SnowBall2);
	//SnowBall_Update(SnowBall, gObjects, MapChip, SnowBall2, gObjects, MapChip);

	switch (turn)
	{
	case PLAYER_TURN:

		Player_Update(gPlayer, gObjects, MapChip, gPlayer, gObjects, MapChip);
		Player_Input(gPlayer, gObjects, gPlayer2, gObjects);	//プレイヤー移動

		break;

	case ENEMY_TURN:

		if (gEnemy->direction == NULL_WAY)
		{
			//敵の巡回
			Enemy_Move_Circle(gEnemy);
			//敵の接近
			Enemy_Move_Chase(gEnemy, gPlayer, gPlayer2);
		}

		Enemy_Hit(gEnemy);
		//敵のスタン
		Enemy_Stun(gEnemy, gPlayer, gPlayer2, gObjects, MapChip);

		break;
	}

	if (gEnemy->enemyeye == ENEMYEYE_IN)
	{
		//遮蔽でのヘイトそらし
		for (int i = 0; i < StoneMap.size(); i++) {
			Shield_Cancel(&StoneMap[i], gPlayer, gPlayer2, gEnemy);
		}
	}
	//Shield_Hit(gShield, gPlayer);

	// オブジェクト配列のXY計算、UV計算、頂点配列への適用を一括処理
	//GameObjectと画像の座標を合わせる
	for (int i = 0; i < MAX_OBJECT; i++) {
		GameObject_DrowUpdate(&gObjects[i]);
	}
	GameObject_DrowUpdate(&gBackGround);

	if (Input_GetKeyTrigger(VK_SPACE))
		return FALSE;

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
	for (int i = 0; i < MAX_OBJECT; i++)
		gObjects[i].texture->Draw();

	// ダブル・バッファのディスプレイ領域へのコピー命令
	Direct3D_GetSwapChain()->Present(0, 0);
}

//作ったGameObjectはちゃんとdeleteしよう！
void Game_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM000));

	delete gBackGround.texture;
	for (int i = 0; i < MAX_OBJECT; i++) {
		delete gObjects[i].texture;
		gObjects[i].posX = 0;
		gObjects[i].posY = 0;
	}
}
