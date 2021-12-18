#pragma once
#include "GameObject.h"
#include "MapGeneration.h"

//遮蔽を初期化する関数 
void Shield_Initialize(GameObject* Shield);
//遮蔽の場所をセットする(プレイヤーオブジェクト, 高さ, 左下, 右下) 0から始まる
void Shield_SetLocation(GameObject* Shield, GameObject* Location, int Height, int LeftDown, int RightDown);
//遮蔽のマップ座標取得
MapPos Shield_GetMapPos(GameObject* Shield);
//アップデート関数
void Shield_Update(GameObject* Shield);
//遮蔽の当たり判定
//void Shield_Hit(GameObject* Shield, GameObject* Player);
//遮蔽でのヘイトそらし
void Shield_Cancel(GameObject* Shield, GameObject* SnowBall, GameObject* Enemy);