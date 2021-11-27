#pragma once
#include "GameObject.h"
#include "Player.h"

//雪玉を初期化する関数 
void SnowBall_Initialize(GameObject* SnowBall);
//雪玉の場所をセットする(雪玉オブジェクト, 高さ, 左下, 右下) 0から始まる
void SnowBall_SetLocation(GameObject* SnowBall, GameObject* Location, int Height, int LeftDown, int RightDown);
//雪玉マップ座標取得
MapPos SnowBall_GetMapPos(GameObject* SnowBall);
//アップデート関数
void SnowBall_Update(GameObject* SnowBall);
//雪玉の当たり判定
void SnowBall_Hit(GameObject* SnowBall, GameObject* Player);