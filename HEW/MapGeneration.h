#pragma once
#include "GameObject.h"

//���̑傫��
#define BOX_HEIGHT 200	// �c
#define BOX_WIDTH 200	// ��

//�}�b�v�̗�
#define MAP_EDGE 10		// 10*10�̏�
#define MAP_HEIGHT 3	// ����
#define MAP_STAGE 2		// �X�e�[�W��

// 
#define MAP_HEIGH_FRG -9
#define MAP_STAGE_FRG -99

void Map_Initialize(GameObject* Map);
int Map_GetPlayerTile(GameObject* Player, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE]);
void Map_Update(GameObject* Map ,int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE]);