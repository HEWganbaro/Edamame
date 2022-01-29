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

extern int Player1_cut;
extern int Player2_cut;
extern int turn;
extern int stage;
extern int big_snowball;
extern int fade;
extern int fade_in_cnt;
extern int fade_out_cnt;



enum Direction
{
	NULL_WAY,
	RIGHT_DOWN,
	LEFT_DOWN,
	LEFT_UP,
	RIGHT_UP,
	NO_ACTION,
};

//敵のタイプ
enum EnemyType
{
	RANDOM,
	FOLLOWING,
	CIRCUMFRENCE,
};
//敵の視線
enum Enemyeye
{
	ENEMYEYE_OUT,
	ENEMYEYE_IN_1,
	ENEMYEYE_IN_2,
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
	ENV_TURN,
	GAMEOVER,
	CLEAR,
};

enum Stage
{
	NO_STAGE,
	STAGE_1,
	STAGE_2,
};

enum StageScore {
	TITLESCORE,	//タイトルからステージへ

	ZERO,	//失敗もしくはプレイしてない
	STAGE_CLEAR,	//クリアのみ

	BALANCE_CLEAR,	//バランスのみ
	FACE_CLEAR,		//顔アイテムのみ
	ARM_CLEAR,		//腕アイテムのみ

	BALA_FACE_CLEAR,//バランス顔のみ
	FACE_ARM_CLEAR,	//顔腕のみ
	ARM_BALA_CLEAR,	//腕バランスのみ

	ALL_CLEAR,		//全て完璧
};

enum Fade
{
	NO_FADE,
	FADE_IN,
	FADE_OUT,
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
	int yobiFlag;//状態遷移に使った予備のフラグ
	bool IsEnemy = false;//敵か

	bool Goalfrg = false;
	int SnowSize;//雪玉の大きさ
	bool Item_Face = false;
	bool Item_Arm = false;

	MapPos mappos;	//マップ単位でいる場所
	MapPos tmp;	//一時保存場所

	Direction direction;	//進む方向

	Enemyeye enemyeye;//敵の視線
	EnemyType enemytype;//敵の種類
	EnemyMove enemymove;//敵の動き

	Turn turn;

	CharController charController;  // キャラ移動のクラス変数

	Animator animator;  // アニメーションのクラス変数

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

