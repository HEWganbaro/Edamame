#pragma once
#include "GameObject.h"
#include "Player.h"
#include "MapGeneration.h"

//雪玉を初期化する関数 
void SnowBall2_Initialize(GameObject* SnowBall2);
//雪玉の場所をセットする(雪玉オブジェクト, 高さ, 左下, 右下) 0から始まる
void SnowBall2_SetLocation(GameObject* SnowBall2, GameObject* Location, int Height, int LeftDown, int RightDown);
//雪玉マップ座標取得
MapPos SnowBall2_GetMapPos(GameObject* SnowBall2);
//アップデート関数
void SnowBall2_Update(GameObject* SnowBall2, GameObject* Map, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE]);
//雪玉の当たり判定
void SnowBall2_Hit(GameObject* SnowBall2, GameObject* Player);