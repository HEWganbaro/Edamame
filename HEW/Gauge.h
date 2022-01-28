#pragma once
#include "GameObject.h"
#include "MapGeneration.h"

//ゲージを初期化する関数 
GameObject* Gauge_Initialize(GameObject* Gauge, GameObject* Gauge2);


//アップデート関数
void Gauge_Update(GameObject* Gauge2, GameObject* Player, GameObject* Player2);