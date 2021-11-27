#pragma once
#include "GameObject.h"
#include "Player.h"

//��ʂ�����������֐� 
void SnowBall_Initialize(GameObject* SnowBall);
//��ʂ̏ꏊ���Z�b�g����(��ʃI�u�W�F�N�g, ����, ����, �E��) 0����n�܂�
void SnowBall_SetLocation(GameObject* SnowBall, GameObject* Location, int Height, int LeftDown, int RightDown);
//��ʃ}�b�v���W�擾
MapPos SnowBall_GetMapPos(GameObject* SnowBall);
//�A�b�v�f�[�g�֐�
void SnowBall_Update(GameObject* SnowBall);
//��ʂ̓����蔻��
void SnowBall_Hit(GameObject* SnowBall, GameObject* Player);