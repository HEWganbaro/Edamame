#pragma once
#include "GameObject.h"

//箱の大きさ
#define BOX_HEIGHT 200	// 縦
#define BOX_WIDTH 200	// 横

//マップの列数
#define MAP_EDGE 10		// 10*10の床
#define MAP_HEIGHT 3	// 高さ
#define MAP_STAGE 2		// ステージ数

// 
#define MAP_HEIGH_FRG -9
#define MAP_STAGE_FRG -99

void Map_Initialize(GameObject* Map);
int Map_GetPlayerTile(GameObject* Player, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE]);
void Map_Update(GameObject* Map ,int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE]);