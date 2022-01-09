#pragma once
// ↑　この命令を書いておくと、ヘッダーが何度もインクルードされて定義重複エラーが
// 　　出るのを防ぐことができる。

#include "animator.h"
#include "CharController.h"
#include "Sprite.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#define MAP_LENGTH 0.075f // 一つのマスに対しての横移動量(DX座標)
#define MAP_LENGTH_HEIGHT 0.1f // 一つのマスに対しての縦移動量(DX座標)

using namespace std;

extern int Player_cut;
extern int Enemy_flg;
extern int turn;


enum Direction
{
	NULL_WAY,
	RIGHT_DOWN,
	LEFT_DOWN,
	LEFT_UP,
	RIGHT_UP,
};

//敵の視線
enum Enemyeye
{
	ENEMYEYE_IN,
	ENEMYEYE_OUT,
};

//敵の挙動
enum EnemyMove
{
	ENEMY_MOVE,
	ENEMY_STOP,
};

enum Turn
{
	PLAYER_TURN,
	ENEMY_TURN,
};

struct MapPos
{
	int Height;
	int LeftDown;
	int RightDown;	//高さ 左下 右下
};

// GameObjectクラスで必要になる変数セットを構造体として定義
struct GameObject {

	// 変数書いていく
	float posX, posY;  // 中心点の座標
	float sizeX, sizeY; // 大きさ
	bool changeFlag = false;//状態遷移などに使いたいとき用のフラグ

	MapPos mappos;	//マップ単位でいる場所

	MapPos tmp;	//一時保存場所

	Direction direction;	//進む方向

	Enemyeye enemyeye;//敵の視線

	EnemyMove enemymove;//敵の動き

	Turn turn;

	CharController charController;  // キャラ移動のクラス変数

	Animator animator;  // アニメーションのクラス変数

	//UvInfo uvinfo; // テクスチャの情報

	Sprite* texture;	//画像データ
};




// 左右上下の４つの座標値を持つ構造体
struct FRECT {

	float left;
	float right;
	float top;
	float bottom;
};


// ↓↓　メンバー関数のプロトタイプ宣言
void GameObject_DrowUpdate(GameObject*);

// スプライトの４隅のXY座標を計算して返す関数
FRECT GameObject_GetXY(GameObject* pThis);

// スプライトの４隅のUV座標を計算して返す関数
FRECT GameObject_GetUV(GameObject* pThis);

// 毎フレームの更新処理
void GameObject_Update(GameObject* pThis);

vector<string> split(string& input, char delimiter);

