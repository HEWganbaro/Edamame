#pragma once
#include "GameObject.h"
#include "MapGeneration.h"

#define SCANNING_RANGE 3

//�G������������֐� 
GameObject* Enemy_Initialize(GameObject* Enemy, EnemyType type);
//�G�̏ꏊ���Z�b�g����(��ʃI�u�W�F�N�g, ����, ����, �E��) 0����n�܂�
void Enemy_SetLocation(GameObject* Enemy, GameObject* Location, int Height, int LeftDown, int RightDown);
//�G�̃}�b�v���W�擾
MapPos Enemy_GetMapPos(GameObject* Enemy);
//�A�b�v�f�[�g�֐�
void Enemy_Update(GameObject* Enemy);
//�G�̓����蔻��
void Enemy_Hit(GameObject* Enemy);
//�G���v���C���[��ǂ�������
void Enemy_Move_Chase(GameObject* Enemy, GameObject* Player, GameObject* Player2);
//�G�̏���
void Enemy_Move_Circle(GameObject* Enemy);
//�G�̃����_��
void Enemy_Move_Random(GameObject* Enemy);
//�Q�[���I�[�o�[����
void Enemy_Player_Hit(GameObject* Enemy, GameObject* Player, GameObject* Player2);
//�G�̃X�^��
void Enemy_Stun(GameObject* Enemy, GameObject* Player, GameObject * Player2, GameObject* Map, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE]);