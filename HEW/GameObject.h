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

extern int Player1_cut;
extern int Player2_cut;
extern int turn;
extern int stage;
extern int big_snowball;
extern int fade;
extern int fade_in_cnt;
extern int fade_out_cnt;



enum Direction
{
	NULL_WAY,
	RIGHT_DOWN,
	LEFT_DOWN,
	LEFT_UP,
	RIGHT_UP,
	NO_ACTION,
};

//�G�̃^�C�v
enum EnemyType
{
	RANDOM,
	FOLLOWING,
	CIRCUMFRENCE,
};
//�G�̎���
enum Enemyeye
{
	ENEMYEYE_OUT,
	ENEMYEYE_IN_1,
	ENEMYEYE_IN_2,
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
	ENV_TURN,
	GAMEOVER,
	CLEAR,
};

enum Stage
{
	NO_STAGE,
	STAGE_1,
	STAGE_2,
};

enum StageScore {
	TITLESCORE,	//�^�C�g������X�e�[�W��

	ZERO,	//���s�������̓v���C���ĂȂ�
	STAGE_CLEAR,	//�N���A�̂�

	BALANCE_CLEAR,	//�o�����X�̂�
	FACE_CLEAR,		//��A�C�e���̂�
	ARM_CLEAR,		//�r�A�C�e���̂�

	BALA_FACE_CLEAR,//�o�����X��̂�
	FACE_ARM_CLEAR,	//��r�̂�
	ARM_BALA_CLEAR,	//�r�o�����X�̂�

	ALL_CLEAR,		//�S�Ċ���
};

enum Fade
{
	NO_FADE,
	FADE_IN,
	FADE_OUT,
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
	int yobiFlag;//��ԑJ�ڂɎg�����\���̃t���O
	bool IsEnemy = false;//�G��

	bool Goalfrg = false;
	int SnowSize;//��ʂ̑傫��
	bool Item_Face = false;
	bool Item_Arm = false;

	MapPos mappos;	//�}�b�v�P�ʂł���ꏊ
	MapPos tmp;	//�ꎞ�ۑ��ꏊ

	Direction direction;	//�i�ޕ���

	Enemyeye enemyeye;//�G�̎���
	EnemyType enemytype;//�G�̎��
	EnemyMove enemymove;//�G�̓���

	Turn turn;

	CharController charController;  // �L�����ړ��̃N���X�ϐ�

	Animator animator;  // �A�j���[�V�����̃N���X�ϐ�

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

