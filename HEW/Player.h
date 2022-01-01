#pragma once
#include "GameObject.h"
#include "input.h"
#include "MapGeneration.h"

//プレイヤーを初期化する関数 
void Player_Initialize(GameObject* Player);
//プレイヤーの場所をセットする(プレイヤーオブジェクト, 高さ, 左下, 右下) 0から始まる
void Player_SetLocation(GameObject* Player, GameObject* Location, int Height, int LeftDown, int RightDown);
//ゲーム中で操作させたい事などをこの中に書く
void Player_Input(GameObject* Player , GameObject* Map);
//プレイヤーマップ座標取得
MapPos Player_GetMapPos(GameObject* Player);
//アップデート関数
void Player_Update(GameObject* Plyaer);