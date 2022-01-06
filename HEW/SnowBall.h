#pragma once
#include "GameObject.h"
#include "Player.h"
#include "MapGeneration.h"

//*****************************************************************************
// ���1
//*****************************************************************************
//��ʂ�����������֐� 
void SnowBall_Initialize(GameObject* SnowBall, GameObject* SnowBall2);
//��ʂ̏ꏊ���Z�b�g����(��ʃI�u�W�F�N�g, ����, ����, �E��) 0����n�܂�
void SnowBall_SetLocation(GameObject* SnowBall, GameObject* Location, int Height, int LeftDown, int RightDown
						, GameObject* SnowBall2, GameObject* Location2, int Height2, int LeftDown2, int RightDown2);
//��ʃ}�b�v���W�擾
MapPos SnowBall_GetMapPos(GameObject* SnowBall, GameObject* SnowBall2);
//�A�b�v�f�[�g�֐�
void SnowBall_Update(GameObject* SnowBall, GameObject* Map, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE]
				   , GameObject* SnowBall2, GameObject* Map2, int MapChip2[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE]);
//��ʂ̓����蔻��
void SnowBall_Hit(GameObject * Player, GameObject * SnowBall);