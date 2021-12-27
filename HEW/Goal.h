#pragma once
#include "GameObject.h"
#include "MapGeneration.h"

//�Օ�������������֐� 
void Goal_Initialize(GameObject* goal);
//�Օ��̏ꏊ���Z�b�g����(�v���C���[�I�u�W�F�N�g, ����, ����, �E��) 0����n�܂�
void Goal_SetLocation(GameObject* Goal, GameObject* Location, int Height, int LeftDown, int RightDown);
//�Օ��̃}�b�v���W�擾
MapPos Goal_GetMapPos(GameObject* Goal);
//�A�b�v�f�[�g�֐�
void Goal_Update(GameObject* Goal);
//�Օ��̓����蔻��
//void Goal_Hit(GameObject* Goal, GameObject* Player);