#pragma once
#include "GameObject.h"
#include "input.h"
#include "MapGeneration.h"

//プレイヤーを初期化する関数 
void Player_Initialize(GameObject* Player, GameObject* Player2);
//プレイヤーの場所をセットする(プレイヤーオブジェクト, 高さ, 左下, 右下) 0から始まる
void Player_SetLocation(GameObject* Player, GameObject* Location, int Height, int LeftDown, int RightDown
					  , GameObject* Player2, GameObject* Location2, int Height2, int LeftDown2, int RightDown2);
//ゲーム中で操作させたい事などをこの中に書く
void Player_Input(GameObject* Player , GameObject* Map, GameObject* Player2, GameObject* Map2);
//プレイヤーマップ座標取得
MapPos Player_GetMapPos(GameObject* Player, GameObject* Player2);
//アップデート関数
void Player_Update(GameObject* Player, GameObject* Player2);