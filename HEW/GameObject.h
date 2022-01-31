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
#define FADETIME 30

using namespace std;

extern int Player1_cut;
extern int Player2_cut;
extern int turn;
extern int stage;
extern int big_snowball;
extern int korokoroX;
extern int korokoroY;

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
	PENGUIN_ATTACK,
	PENGUIN2,
	GAMEOVER,
	CLEAR,
	TUTORIAL,
};

enum Stage
{
	NO_STAGE,
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_5,
	STAGE_6,
	STAGE_7,
	STAGE_8,
	STAGE_9,
	STAGE_10,
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



struct MapPos
{
	int Height;
	int LeftDown;
	int RightDown;	//���� ���� �E��
};

enum STUN
{
	Nothing,
	Stun_Release,
	Stun,
	Stun_,
};

// GameObject�N���X�ŕK�v�ɂȂ�ϐ��Z�b�g���\���̂Ƃ��Ē�`
struct GameObject {

	// �ϐ������Ă���
	float posX, posY;  // ���S�_�̍��W

	bool changeFlag = false;//��ԑJ�ڂȂǂɎg�������Ƃ��p�̃t���O
	int yobiFlag;//��ԑJ�ڂɎg�����\���̃t���O
	bool IsEnemy = false;//�G��
	bool EnemyAttak = false;
	int Enemycount = 0;
	STUN IsStun = Nothing;//�X�^�����Ă��邩

	bool GoalFast = false;
	bool Goalfrg = false;
	bool GoalEffect = false;
	int SnowSize;//��ʂ̑傫��
	bool SoilFrg;//�y�𓥂񂾂�
	bool Item_Face = false;
	bool Item_Arm = false;

	MapPos mappos;	//�}�b�v�P�ʂł���ꏊ
	MapPos tmp;	//�ꎞ�ۑ��ꏊ

	Direction diretmp;		//�O��ۑ��ꏊ
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

struct FADE {
	bool fadeout = false;
	float framecnt;
	float Alpha = 0;
};

// �����@�����o�[�֐��̃v���g�^�C�v�錾
void GameObject_DrowUpdate(GameObject*);

//�t�F�[�h�֐��ł��Ԏ؂肵�܂�
void FadeChange(FADE* fade);

// �X�v���C�g�̂S����XY���W���v�Z���ĕԂ��֐�
FRECT GameObject_GetXY(GameObject* pThis);

// �X�v���C�g�̂S����UV���W���v�Z���ĕԂ��֐�
FRECT GameObject_GetUV(GameObject* pThis);

// ���t���[���̍X�V����
void GameObject_Update(GameObject* pThis);

vector<string> split(string& input, char delimiter);

