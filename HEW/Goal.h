#pragma once
#include "GameObject.h"
#include "MapGeneration.h"

//遮蔽を初期化する関数 
void Goal_Initialize(GameObject* goal);
//遮蔽の場所をセットする(プレイヤーオブジェクト, 高さ, 左下, 右下) 0から始まる
void Goal_SetLocation(GameObject* Goal, GameObject* Location, int Height, int LeftDown, int RightDown);
//遮蔽のマップ座標取得
MapPos Goal_GetMapPos(GameObject* Goal);
//アップデート関数
void Goal_Update(GameObject* Goal);
//遮蔽の当たり判定
//void Goal_Hit(GameObject* Goal, GameObject* Player);