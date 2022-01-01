#pragma once
#include "GameObject.h"
#include "input.h"
#include "MapGeneration.h"

//�v���C���[������������֐� 
void Player_Initialize(GameObject* Player);
//�v���C���[�̏ꏊ���Z�b�g����(�v���C���[�I�u�W�F�N�g, ����, ����, �E��) 0����n�܂�
void Player_SetLocation(GameObject* Player, GameObject* Location, int Height, int LeftDown, int RightDown);
//�Q�[�����ő��삳���������Ȃǂ����̒��ɏ���
void Player_Input(GameObject* Player , GameObject* Map);
//�v���C���[�}�b�v���W�擾
MapPos Player_GetMapPos(GameObject* Player);
//�A�b�v�f�[�g�֐�
void Player_Update(GameObject* Plyaer);