#pragma once
// ���@���̖��߂������Ă����ƁA�w�b�_�[�����x���C���N���[�h����Ē�`�d���G���[��
// �@�@�o��̂�h�����Ƃ��ł���B

#include "animator.h"
#include "CharController.h"
#include "Sprite.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#define MAP_LENGTH 0.075f // ��̃}�X�ɑ΂��Ẳ��ړ���(DX���W)
#define MAP_LENGTH_HEIGHT 0.1f // ��̃}�X�ɑ΂��Ă̏c�ړ���(DX���W)

using namespace std;

extern int Player_cut;
extern int Enemy_flg;
extern int turn;


enum Direction
{
	NULL_WAY,
	RIGHT_DOWN,
	LEFT_DOWN,
	LEFT_UP,
	RIGHT_UP,
};

//�G�̎���
enum Enemyeye
{
	ENEMYEYE_IN,
	ENEMYEYE_OUT,
};

//�G�̋���
enum EnemyMove
{
	ENEMY_MOVE,
	ENEMY_STOP,
};

enum Turn
{
	PLAYER_TURN,
	ENEMY_TURN,
};

struct MapPos
{
	int Height;
	int LeftDown;
	int RightDown;	//���� ���� �E��
};

// GameObject�N���X�ŕK�v�ɂȂ�ϐ��Z�b�g���\���̂Ƃ��Ē�`
struct GameObject {

	// �ϐ������Ă���
	float posX, posY;  // ���S�_�̍��W
	float sizeX, sizeY; // �傫��
	bool changeFlag = false;//��ԑJ�ڂȂǂɎg�������Ƃ��p�̃t���O

	MapPos mappos;	//�}�b�v�P�ʂł���ꏊ

	MapPos tmp;	//�ꎞ�ۑ��ꏊ

	Direction direction;	//�i�ޕ���

	Enemyeye enemyeye;//�G�̎���

	EnemyMove enemymove;//�G�̓���

	Turn turn;

	CharController charController;  // �L�����ړ��̃N���X�ϐ�

	Animator animator;  // �A�j���[�V�����̃N���X�ϐ�

	//UvInfo uvinfo; // �e�N�X�`���̏��

	Sprite* texture;	//�摜�f�[�^
};




// ���E�㉺�̂S�̍��W�l�����\����
struct FRECT {

	float left;
	float right;
	float top;
	float bottom;
};


// �����@�����o�[�֐��̃v���g�^�C�v�錾
void GameObject_DrowUpdate(GameObject*);

// �X�v���C�g�̂S����XY���W���v�Z���ĕԂ��֐�
FRECT GameObject_GetXY(GameObject* pThis);

// �X�v���C�g�̂S����UV���W���v�Z���ĕԂ��֐�
FRECT GameObject_GetUV(GameObject* pThis);

// ���t���[���̍X�V����
void GameObject_Update(GameObject* pThis);

vector<string> split(string& input, char delimiter);

