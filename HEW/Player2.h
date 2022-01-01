#pragma once
#include "GameObject.h"
#include "input.h"
#include "MapGeneration.h"

//プレイヤーを初期化する関数 
void Player2_Initialize(GameObject* Player2);
//プレイヤーの場所をセットする(プレイヤーオブジェクト, 高さ, 左下, 右下) 0から始まる
void Player2_SetLocation(GameObject* Player2, GameObject* Location, int Height, int LeftDown, int RightDown);
//ゲーム中で操作させたい事などをこの中に書く
void Player2_Input(GameObject* Player2 ,GameObject* Map);
//プレイヤーマップ座標取得
MapPos Player2_GetMapPos(GameObject* Player2);
//アップデート関数
void Player2_Update(GameObject* Plyaer2);