#pragma once
#include "GameObject.h"
#include "MapGeneration.h"

//移動スピード
#define ENEMY_SPEED 25  //大きい方が遅い

//敵を初期化する関数 
void Enemy_Initialize(GameObject* Enemy);
//敵の場所をセットする(雪玉オブジェクト, 高さ, 左下, 右下) 0から始まる
void Enemy_SetLocation(GameObject* Enemy, GameObject* Location, int Height, int LeftDown, int RightDown);
//敵のマップ座標取得
MapPos Enemy_GetMapPos(GameObject* Enemy);
//アップデート関数
void Enemy_Update(GameObject* Enemy);
//敵の当たり判定
void Enemy_Hit(GameObject* Enemy, GameObject* Player);
//敵がプレイヤーを追いかける
void Enemy_Move_Chase(GameObject* Enemy, GameObject* SnowBall);
//敵の巡回
void Enemy_Move_Circle(GameObject* Enemy, GameObject* Player, GameObject* SnowBall);
//敵のスタン
void Enemy_Stun(GameObject* Enemy, GameObject* SnowBall, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE]);