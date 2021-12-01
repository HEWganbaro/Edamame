#pragma once
#include "GameObject.h"
#include "Player.h"

//�G������������֐� 
void Enemy_Initialize(GameObject* Enemy);
//�G�̏ꏊ���Z�b�g����(��ʃI�u�W�F�N�g, ����, ����, �E��) 0����n�܂�
void Enemy_SetLocation(GameObject* Enemy, GameObject* Location, int Height, int LeftDown, int RightDown);
//�G�̃}�b�v���W�擾
MapPos Enemy_GetMapPos(GameObject* Enemy);
//�A�b�v�f�[�g�֐�
void Enemy_Update(GameObject* Enemy);
//�G�̓����蔻��
void Enemy_Hit(GameObject* Enemy, GameObject* Player, GameObject* SnowBall);