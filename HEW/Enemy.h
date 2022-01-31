#pragma once
#include "GameObject.h"
#include "MapGeneration.h"
#include "XAudio2.h"

#define SCANNING_RANGE 3

//�G������������֐� 
GameObject* Enemy_Initialize(GameObject* Enemy, EnemyType type);
//�G�̏ꏊ���Z�b�g����(��ʃI�u�W�F�N�g, ����, ����, �E��) 0����n�܂�
void Enemy_SetLocation(GameObject* Enemy, GameObject* Location, int Height, int LeftDown, int RightDown);
//�G�̃}�b�v���W�擾
MapPos Enemy_GetMapPos(GameObject* Enemy);
//�A�b�v�f�[�g�֐�
void Enemy_Update(GameObject* Enemy, GameObject* Player);
//�G���v���C���[��ǂ�������
void Enemy_Move_Chase(GameObject* Enemy, GameObject* Player, GameObject* Player2);
//�G�̏���
void Enemy_Move_Circle(GameObject* Enemy);
//�G�̃����_��
void Enemy_Move_Random(GameObject* Enemy);
//�Q�[���I�[�o�[����
void Enemy_Player_Hit(GameObject* Enemy, GameObject* Player, GameObject* Player2);
//�Q�[���I�[�o�[��ړ�
void Enemy_GameOver_Move(GameObject* Enemy);
//�Q�[���I�[�o�[��̈ړ��t���O
void Enemy_Move_Frg(GameObject* Enemy, GameObject* Player);
//�G�̃X�^��
void Enemy_Stun(GameObject* Enemy, GameObject* Player, GameObject * Player2, GameObject* Map);