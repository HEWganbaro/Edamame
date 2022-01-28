#pragma once
#include "GameObject.h"
#include "input.h"
#include "MapGeneration.h"

#define INIT_SNOW_SIZE 175

enum SNOW_STATE {
	SNOW_STATE,
	NORMAL_STATE,
	ICE_STATE,
};

//�v���C���[������������֐� 
void Player_Initialize(GameObject* Player);
//�v���C���[�̏ꏊ���Z�b�g����(�v���C���[�I�u�W�F�N�g, ����, ����, �E��) 0����n�܂�
void Player_SetLocation(GameObject* Player, GameObject* Location, int Height, int LeftDown, int RightDown);
//�Q�[�����ő��삳���������Ȃǂ����̒��ɏ���
void Player_Input(GameObject* Player, GameObject* Player2);
//�v���C���[�}�b�v���W�擾
//MapPos Player_GetMapPos(GameObject* Player);
//�A�b�v�f�[�g�֐�
void Player_Update(GameObject* Player, GameObject* Map);
void Player_AniUpdate(GameObject* Player);
//���ԍ��ŕX�ɕς��邽�߂̊֐�
void MapUpdate(GameObject* Map, GameObject* Player, GameObject* Player2);
//�傫����ʂ�Ԃ��֐�
float Big_SnowBall(GameObject* Player, GameObject* Player2);