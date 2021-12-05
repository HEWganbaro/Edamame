//*****************************************************************************
// DX21　サンプルソース
// ゲームのメインとなる処理を書いていくソースファイル
//*****************************************************************************

#include "game.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************

// 頂点１つあたりを表す構造体
struct VERTEX_POSTEX {
	float x, y, z;  // 頂点の位置

	float u, v;  // テクスチャのUV座標
};

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define MAX_SPRITE  2560
// ポリゴン２つで１つの四角形（スプライト）。ポリゴンは３頂点なので、１スプライトは６頂点。
#define VERTEX_PER_SPRITE  (3*2)
#define VERTEX_BUFFER_SIZE  (MAX_SPRITE*sizeof(VERTEX_POSTEX)*VERTEX_PER_SPRITE)


// オブジェクトの発生数 (多かったり少なかったりするとエラーが出る)
#define MAX_OBJECT   307

//*****************************************************************************
// グローバル変数
//*****************************************************************************

ID3D11Buffer* gpVertexBuffer;  // 頂点バッファ用の変数
ID3D11ShaderResourceView* gpTexture; // テクスチャ用変数

GameObject gObjects[MAX_OBJECT];  // オブジェクト配列
int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE]; //ステージ数[ステージ][高さ][左下][右下]

GameObject* gPlayer = gObjects + 300;
GameObject* NoHeight = gObjects + 301;
GameObject* NoLeftDown = gObjects + 302;
GameObject* NoRightDown = gObjects + 303;
GameObject* tile = gObjects + 304;
GameObject* SnowBall = gObjects + 305;
GameObject* gEnemy = gObjects + 306;

// ゲームシーン
SCENE gScene = SCENE_START;

//*****************************************************************************
// 関数の定義　ここから　↓
//*****************************************************************************

BOOL Game_Initialize()
{
	HRESULT hr;

	//// 頂点バッファ作成
	//D3D11_BUFFER_DESC bufferDesc;
	//bufferDesc.ByteWidth = VERTEX_BUFFER_SIZE;
	//bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bufferDesc.CPUAccessFlags = 0;
	//bufferDesc.MiscFlags = 0;
	//bufferDesc.StructureByteStride = 0;

	//hr = Direct3D_GetDevice()->CreateBuffer(&bufferDesc, NULL, &gpVertexBuffer);
	//if (FAILED(hr))
	//	return FALSE;
	// ↑　頂点バッファ作成　ここまで

	// ここで使用したい画像ファイルをテクスチャとして読み込む
	// 第一引数：画像ファイル名。もしフォルダに入っているならフォルダ名も一緒に書く。
	// 第二引数：読み込んだテクスチャが入る変数を指定
	//hr = Direct3D_LoadTexture("assets/texture.png", &gpTexture);
	//if (FAILED(hr)) {
	//	return FALSE;
	//}

	//オーディオの初期化
	hr = XA_Initialize();
	if (FAILED(hr))
		return FALSE;

	// ゲーム時間の初期化をし、FPSを60に設定した。
	GameTimer_Initialize(60);
	
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
	SnowBall_SetLocation(SnowBall, gObjects, 0, 3, 3);

	//敵の初期化
	Enemy_Initialize(gEnemy);

	//敵の場所指定
	Enemy_SetLocation(gEnemy, gObjects, 0, 4, 4);

	//デバック用
	NoHeight->texture = new Sprite("assets/No.png", 13, 7);
	NoHeight->texture->SetSize(80, 80);
	NoLeftDown->texture = new Sprite("assets/No.png", 13, 7);
	NoLeftDown->texture->SetSize(80, 80);
	NoRightDown->texture = new Sprite("assets/No.png", 13, 7);
	NoRightDown->texture->SetSize(80, 80);
	tile->texture = new Sprite("assets/blockseat.png", 4, 1);
	tile->texture->SetSize(200, 200);

	return TRUE;
}


// ゲームループ中に実行したい、ゲームの処理を書く関数
void Game_Update()
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
	tile->texture->SetPart(Map_GetPlayerTile(gPlayer, MapChip), 0);
	tile->posX = 0.3;
	tile->posY = 0.6;

	Map_Update(gObjects, MapChip);	//マップ変更↑↓

	Player_Input(gPlayer);			//プレイヤー移動

	SnowBall_Hit(gPlayer, SnowBall);

	Enemy_Hit(gEnemy, gPlayer);

	if (gEnemy->direction == NULL_WAY)
	{
		Enemy_Move_Circle(gEnemy);
	}

	// ゲームシーン別
	switch (gScene)
	{
	case SCENE_START:
		break;
	case SCENE_SLECT:
		break;
	case SCENE_GAME:
		break;
	default:
		break;
	}

	// ポリゴンの頂点を定義
	// 頂点を結んでポリゴンを形成するときの法則
	// ・頂点は、配列の番号の若い順番に使用される
	// ・頂点を結んでポリゴンが形成されたとき、その結び順が時計回りになる場合だけポリゴンが表示される
	//VERTEX_POSTEX vx[MAX_SPRITE*VERTEX_PER_SPRITE];

	// オブジェクト配列のXY計算、UV計算、頂点配列への適用を一括処理
	for (int i = 0; i < MAX_OBJECT; i++) {
		//GameObjectと画像の座標を合わせる
		GameObject_DrowUpdate(&gObjects[i]);
		//GameObject_Update(&gObjects[i]);
		// XY計算
		//FRECT xy = GameObject_GetXY( &gObjects[i] );
		//// UV計算
		//FRECT uv = GameObject_GetUV( gObjects+i );
		//// 頂点配列への適用
		//vx[0 + i * 6 + 0] = { xy.left, xy.top, 0, uv.left, uv.top },  // １つめの頂点   �@左上
		//vx[0 + i * 6 + 1] = { xy.right, xy.top, 0, uv.right, uv.top },  // ２つめの頂点　�A右上
		//vx[0 + i * 6 + 2] = { xy.right,  xy.bottom, 0, uv.right, uv.bottom },  // ３つめの頂点　�B右下

		//vx[0 + i * 6 + 3] = { xy.right,  xy.bottom, 0, uv.right, uv.bottom },  // ４つめの頂点　�B右下
		//vx[0 + i * 6 + 4] = { xy.left,  xy.bottom, 0, uv.left, uv.bottom },  // ５つめの頂点　�C左下
		//vx[0 + i * 6 + 5] = { xy.left,  xy.top, 0, uv.left, uv.top };  // ６つめの頂点　　  �@左上　　  �@左上
	}

	//// 頂点バッファのデータをvx配列のデータで更新する
	//Direct3D_GetContext()->UpdateSubresource(
	//	gpVertexBuffer,		// 更新対象のバッファ
	//	0,				// インデックス(0)
	//	NULL,				// 更新範囲(nullptr)
	//	vx,		// 反映データ
	//	0,				// データの1行のサイズ(0)
	//	0);				// 1深度スライスのサイズ(0)
}


void Game_Draw()
{
	// 画面クリア（指定色で塗りつぶし）
	// 塗りつぶし色の指定（小数：0.0f〜1.0f）
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha

	Direct3D_GetContext()->ClearRenderTargetView(Direct3D_GetRenderTargetView(), clearColor);

	// ↓　自前の描画処理をここに書く *******

	// 描画で使用するテクスチャを指定する関数呼び出し
	// ここで指定されたテクスチャが、ピクセルシェーダーのグローバル変数にセットされる
	//Direct3D_GetContext()->PSSetShaderResources(0, 1, &gpTexture);

	// 描画に使う頂点バッファを指定する
	//UINT strides = sizeof(VERTEX_POSTEX);
	//UINT offsets = 0;
	//Direct3D_GetContext()->IASetVertexBuffers(0, 1, &gpVertexBuffer, &strides, &offsets);   // gpVertexBufferが頂点バッファ

	// これまでの設定で実際に描画する
	//Direct3D_GetContext()->Draw(MAX_SPRITE*VERTEX_PER_SPRITE, 0);

	//ゲームオブジェクトを全部描画する
	for (int i = 0; i < MAX_OBJECT; i++)
		gObjects[i].texture->Draw();
	//gPlayer->textuer->Draw();
	//No->textuer->Draw();

	// ↑　自前の描画処理をここに書く *******

	// ダブル・バッファのディスプレイ領域へのコピー命令
	Direct3D_GetSwapChain()->Present(0, 0);
}

void Game_Relese()
{
	XA_Release();	//オーディオのリリース

	COM_SAFE_RELEASE(gpTexture);  // テクスチャを読み込んだら、忘れずリリースすること
	COM_SAFE_RELEASE(gpVertexBuffer); // 頂点バッファを作成したら、忘れずにリリースすること
}

