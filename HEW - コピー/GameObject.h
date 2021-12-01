#pragma once
// ↑　この命令を書いておくと、ヘッダーが何度もインクルードされて定義重複エラーが
// 　　出るのを防ぐことができる。

#include "animator.h"
#include "CharController.h"
#include "UvInfo.h"
#include "Sprite.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#define MAP_LENGTH 0.08f // 一つのマスに対しての移動量(DX座標)

using namespace std;

enum Direction
{
	NULL_WAY,
	RIGHT_DOWN,
	LEFT_DOWN,
	LEFT_UP,
	RIGHT_UP,
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

	MapPos mappos;

	CharController charController;  // キャラ移動のクラス変数

	Animator animator;  // アニメーションのクラス変数

	UvInfo uvinfo; // テクスチャの情報

	Sprite* textuer;	//画像データ
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

