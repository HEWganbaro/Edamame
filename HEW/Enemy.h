#pragma once
#include "GameObject.h"
#include"Player.h"

//�ړ��X�s�[�h
#define ENEMY_SPEED 25  //�傫�������x��



//�G������������֐� 
void Enemy_Initialize(GameObject* Enemy);
//�G�̏ꏊ���Z�b�g����(��ʃI�u�W�F�N�g, ����, ����, �E��) 0����n�܂�
void Enemy_SetLocation(GameObject* Enemy, GameObject* Location, int Height, int LeftDown, int RightDown);
//�G�̃}�b�v���W�擾
MapPos Enemy_GetMapPos(GameObject* Enemy);
//�A�b�v�f�[�g�֐�
void Enemy_Update(GameObject* Enemy);
//�G�̓����蔻��
void Enemy_Hit(GameObject* Enemy, GameObject* Player);
//�G���v���C���[��ǂ�������
void Enemy_Move_Chase(GameObject* Enemy, GameObject* Player);
//�G�̏���
void Enemy_Move_Circle(GameObject* Enemy);