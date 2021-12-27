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
#define MAX_OBJECT   309

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//ID3D11Buffer* gpVertexBuffer;  // 頂点バッファ用の変数
//ID3D11ShaderResourceView* gpTexture; // テクスチャ用変数

	//ステージ数[ステージ][高さ][左下][右下]
int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE];

GameObject gObjects[MAX_OBJECT];  // オブジェクト配列
GameObject* gPlayer = gObjects + 300;
GameObject* NoHeight = gObjects + 301;
GameObject* NoLeftDown = gObjects + 302;
GameObject* NoRightDown = gObjects + 303;
GameObject* tile = gObjects + 304;
GameObject* SnowBall = gObjects + 305;
GameObject* gEnemy = gObjects + 306;
GameObject* gShield = gObjects + 307;
GameObject* gGoal = gObjects + 308;


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
	Player_Initialize(gPlayer);

	//プレイヤー場所指定
	Player_SetLocation(gPlayer, gObjects, 0, 5, 5);

	//雪玉の初期化
	SnowBall_Initialize(SnowBall);

	//雪玉の場所指定
	SnowBall_SetLocation(SnowBall, gObjects, 0, 6, 6);

	//敵の初期化
	Enemy_Initialize(gEnemy);

	//敵の場所指定
	Enemy_SetLocation(gEnemy, gObjects, 0, 4, 4);

	//遮蔽の初期化
	Shield_Initialize(gShield);

	//遮蔽の場所指定
	Shield_SetLocation(gShield, gObjects, 0, 3, 6);

	//遮蔽の初期化
	Goal_Initialize(gGoal);

	//遮蔽の場所指定
	Goal_SetLocation(gGoal, gObjects, 0, 4, 5);

	//デバック用
	NoHeight->textuer = new Sprite("assets/No.png", 13, 7);
	NoHeight->textuer->SetSize(80, 80);
	NoLeftDown->textuer = new Sprite("assets/No.png", 13, 7);
	NoLeftDown->textuer->SetSize(80, 80);
	NoRightDown->textuer = new Sprite("assets/No.png", 13, 7);
	NoRightDown->textuer->SetSize(80, 80);
	tile->textuer = new Sprite("assets/MapSeat.png", 6, 1);
	tile->textuer->SetSize(200, 200);
	gBackGround.textuer = new Sprite("assets/BackGround.png", 1, 1);
	gBackGround.textuer->SetSize(1280*2, 720*2);

	return TRUE;
}


// ゲームループ中に実行したい、ゲームの処理を書く関数
BOOL Game_Update()
{
	Input_Update();  // このゲームで使うキーの押下状態を調べて保

	//デバック用
	NoHeight->textuer->SetPart(gPlayer->mappos.Height, 0);
	NoHeight->posX = 0.5f;
	NoHeight->posY = 0.5f;
	NoLeftDown->textuer->SetPart(gPlayer->mappos.LeftDown, 0);
	NoLeftDown->posX = 0.6f;
	NoLeftDown->posY = 0.5f;
	NoRightDown->textuer->SetPart(gPlayer->mappos.RightDown, 0);
	NoRightDown->posX = 0.7f;
	NoRightDown->posY = 0.5f;
	tile->textuer->SetPart(Map_GetPlayerTile(gPlayer, MapChip), 0);
	tile->posX = 0.3;
	tile->posY = 0.6;
	gBackGround.posX = -1;
	gBackGround.posY = 1;

	Map_Update(gObjects, MapChip);	//マップ変更↑↓

	Player_Input(gPlayer, MapChip);	//プレイヤー移動

	SnowBall_Hit(gPlayer, SnowBall); //雪玉当たり判定

	SnowBall_Update(SnowBall, gObjects, MapChip);

	Enemy_Hit(gEnemy, SnowBall);

	if (gEnemy->direction == NULL_WAY)
	{
		//敵の巡回
		Enemy_Move_Circle(gEnemy, SnowBall);
	}

	if (gEnemy->enemyeye == ENEMYEYE_IN)
	{
		//遮蔽でのヘイトそらし
		Shield_Cancel(gShield, SnowBall, gEnemy);
	}

	//敵の接近
	Enemy_Move_Chase(gEnemy, SnowBall);

	//Shield_Hit(gShield, gPlayer);

	// オブジェクト配列のXY計算、UV計算、頂点配列への適用を一括処理
	for (int i = 0; i < MAX_OBJECT; i++) {
		//GameObjectと画像の座標を合わせる
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
	gBackGround.textuer->Draw();
	for (int i = 0; i < MAX_OBJECT; i++)
		gObjects[i].textuer->Draw();

	// ダブル・バッファのディスプレイ領域へのコピー命令
	Direct3D_GetSwapChain()->Present(0, 0);
}

//作ったGameObjectはちゃんとdeleteしよう！
void Game_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM000));

	delete gBackGround.textuer;
	for (int i = 0; i < MAX_OBJECT; i++) {
		delete gObjects[i].textuer;
		gObjects[i].posX = 0;
		gObjects[i].posY = 0;
	}
}
