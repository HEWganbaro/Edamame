#pragma once
#include "GameObject.h"
#include "Easing.h"

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

//�ړ��X�s�[�h
#define PLAYER_SPEED 30  //�傫�������x��

enum Mapchip
{
	SNOW_GROUND,
	NORMAL_GROUND,
	ICE_GROUND,
	SOIL_GROUND,
	RIGHTUP_SLOPE,
	LEFTUP_SLOPE,
};

void Map_Initialize(GameObject* Map);
int Map_GetPlayerTile(GameObject* Player, GameObject* Map);
int Map_GetPlayerTile_LeftUp(GameObject* Player, GameObject* Map);
int Map_GetPlayerTile_RightDown(GameObject* Player, GameObject* Map);
int Map_GetPlayerTile_LeftDown(GameObject* Player, GameObject* Map);
int Map_GetPlayerTile_RightUp(GameObject* Player, GameObject* Map);
int Map_GetPlayerTile_Top(GameObject* Player, GameObject* Map);
void Map_Update(GameObject* Map ,int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE]);
void MapMove_Update(GameObject* Player, GameObject* Map);