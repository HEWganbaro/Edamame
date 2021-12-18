#pragma once
#include "GameObject.h"
#include "MapGeneration.h"

//�Օ�������������֐� 
void Shield_Initialize(GameObject* Shield);
//�Օ��̏ꏊ���Z�b�g����(�v���C���[�I�u�W�F�N�g, ����, ����, �E��) 0����n�܂�
void Shield_SetLocation(GameObject* Shield, GameObject* Location, int Height, int LeftDown, int RightDown);
//�Օ��̃}�b�v���W�擾
MapPos Shield_GetMapPos(GameObject* Shield);
//�A�b�v�f�[�g�֐�
void Shield_Update(GameObject* Shield);
//�Օ��̓����蔻��
//void Shield_Hit(GameObject* Shield, GameObject* Player);
//�Օ��ł̃w�C�g���炵
void Shield_Cancel(GameObject* Shield, GameObject* SnowBall, GameObject* Enemy);