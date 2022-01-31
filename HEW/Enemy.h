#pragma once
#include "GameObject.h"
#include "MapGeneration.h"
#include "XAudio2.h"

#define SCANNING_RANGE 3

//敵を初期化する関数 
GameObject* Enemy_Initialize(GameObject* Enemy, EnemyType type);
//敵の場所をセットする(雪玉オブジェクト, 高さ, 左下, 右下) 0から始まる
void Enemy_SetLocation(GameObject* Enemy, GameObject* Location, int Height, int LeftDown, int RightDown);
//敵のマップ座標取得
MapPos Enemy_GetMapPos(GameObject* Enemy);
//アップデート関数
void Enemy_Update(GameObject* Enemy, GameObject* Player);
//敵がプレイヤーを追いかける
void Enemy_Move_Chase(GameObject* Enemy, GameObject* Player, GameObject* Player2);
//敵の巡回
void Enemy_Move_Circle(GameObject* Enemy);
//敵のランダム
void Enemy_Move_Random(GameObject* Enemy);
//ゲームオーバー処理
void Enemy_Player_Hit(GameObject* Enemy, GameObject* Player, GameObject* Player2);
//ゲームオーバー後移動
void Enemy_GameOver_Move(GameObject* Enemy);
//ゲームオーバー後の移動フラグ
void Enemy_Move_Frg(GameObject* Enemy, GameObject* Player);
//敵のスタン
void Enemy_Stun(GameObject* Enemy, GameObject* Player, GameObject * Player2, GameObject* Map);