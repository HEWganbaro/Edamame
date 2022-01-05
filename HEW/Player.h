#pragma once
#include "GameObject.h"
#include "input.h"
#include "MapGeneration.h"

//�v���C���[������������֐� 
void Player_Initialize(GameObject* Player, GameObject* Player2);
//�v���C���[�̏ꏊ���Z�b�g����(�v���C���[�I�u�W�F�N�g, ����, ����, �E��) 0����n�܂�
void Player_SetLocation(GameObject* Player, GameObject* Location, int Height, int LeftDown, int RightDown
					  , GameObject* Player2, GameObject* Location2, int Height2, int LeftDown2, int RightDown2);
//�Q�[�����ő��삳���������Ȃǂ����̒��ɏ���
void Player_Input(GameObject* Player , GameObject* Map, GameObject* Player2, GameObject* Map2);
//�v���C���[�}�b�v���W�擾
MapPos Player_GetMapPos(GameObject* Player, GameObject* Player2);
//�A�b�v�f�[�g�֐�
void Player_Update(GameObject* Player, GameObject* Player2);