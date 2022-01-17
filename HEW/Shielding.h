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
//遮蔽でのヘイトそらし
void Shield_Cancel(MapPos* Shield, GameObject* Player, GameObject * Player2, GameObject* Enemy);