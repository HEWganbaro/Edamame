#pragma once
#include "GameObject.h"
#include "Player.h"
#include "MapGeneration.h"

//*****************************************************************************
// 雪玉1
//*****************************************************************************
//雪玉を初期化する関数 
void SnowBall_Initialize(GameObject* SnowBall, GameObject* SnowBall2);
//雪玉の場所をセットする(雪玉オブジェクト, 高さ, 左下, 右下) 0から始まる
void SnowBall_SetLocation(GameObject* SnowBall, GameObject* Location, int Height, int LeftDown, int RightDown
						, GameObject* SnowBall2, GameObject* Location2, int Height2, int LeftDown2, int RightDown2);
//雪玉マップ座標取得
MapPos SnowBall_GetMapPos(GameObject* SnowBall, GameObject* SnowBall2);
//アップデート関数
void SnowBall_Update(GameObject* SnowBall, GameObject* Map, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE]
				   , GameObject* SnowBall2, GameObject* Map2, int MapChip2[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE]);
//雪玉の当たり判定
void SnowBall_Hit(GameObject * Player, GameObject * SnowBall);