#pragma once
#include "GameObject.h"
#include "Player.h"

//敵を初期化する関数 
void Enemy_Initialize(GameObject* Enemy);
//敵の場所をセットする(雪玉オブジェクト, 高さ, 左下, 右下) 0から始まる
void Enemy_SetLocation(GameObject* Enemy, GameObject* Location, int Height, int LeftDown, int RightDown);
//敵のマップ座標取得
MapPos Enemy_GetMapPos(GameObject* Enemy);
//アップデート関数
void Enemy_Update(GameObject* Enemy);
//敵の当たり判定
void Enemy_Hit(GameObject* Enemy, GameObject* Player, GameObject* SnowBall);