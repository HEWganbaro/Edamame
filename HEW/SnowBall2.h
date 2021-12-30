#pragma once
#include "GameObject.h"
#include "Player.h"
#include "MapGeneration.h"

//��ʂ�����������֐� 
void SnowBall2_Initialize(GameObject* SnowBall2);
//��ʂ̏ꏊ���Z�b�g����(��ʃI�u�W�F�N�g, ����, ����, �E��) 0����n�܂�
void SnowBall2_SetLocation(GameObject* SnowBall2, GameObject* Location, int Height, int LeftDown, int RightDown);
//��ʃ}�b�v���W�擾
MapPos SnowBall2_GetMapPos(GameObject* SnowBall2);
//�A�b�v�f�[�g�֐�
void SnowBall2_Update(GameObject* SnowBall2, GameObject* Map, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE]);
//��ʂ̓����蔻��
void SnowBall2_Hit(GameObject* SnowBall2, GameObject* Player);