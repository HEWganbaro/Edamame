#pragma once
#include "GameObject.h"
#include "input.h"
#include "MapGeneration.h"

//�v���C���[������������֐� 
void Player2_Initialize(GameObject* Player2);
//�v���C���[�̏ꏊ���Z�b�g����(�v���C���[�I�u�W�F�N�g, ����, ����, �E��) 0����n�܂�
void Player2_SetLocation(GameObject* Player2, GameObject* Location, int Height, int LeftDown, int RightDown);
//�Q�[�����ő��삳���������Ȃǂ����̒��ɏ���
void Player2_Input(GameObject* Player2 ,GameObject* Map);
//�v���C���[�}�b�v���W�擾
MapPos Player2_GetMapPos(GameObject* Player2);
//�A�b�v�f�[�g�֐�
void Player2_Update(GameObject* Plyaer2);