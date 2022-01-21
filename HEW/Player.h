#pragma once
#include "GameObject.h"
#include "input.h"
#include "MapGeneration.h"

#define INIT_SNOW_SIZE 100

//プレイヤーを初期化する関数 
void Player_Initialize(GameObject* Player);
//プレイヤーの場所をセットする(プレイヤーオブジェクト, 高さ, 左下, 右下) 0から始まる
void Player_SetLocation(GameObject* Player, GameObject* Location, int Height, int LeftDown, int RightDown);
//ゲーム中で操作させたい事などをこの中に書く
void Player_Input(GameObject* Player, GameObject* Player2);
//プレイヤーマップ座標取得
//MapPos Player_GetMapPos(GameObject* Player);
//アップデート関数
void Player_Update(GameObject* Player, GameObject* Map);
//時間差で氷に変えるための関数
void toIce(GameObject* Map);