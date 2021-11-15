#pragma once

//*****************************************************************************
// CharController�N���X
// �Q�[���L�����N�^�[�Ƃ��Ă̈ړ����i��
//*****************************************************************************

//*****************************************************************************
// �萔��`
//*****************************************************************************

#define ACCEL_LEFT  -1.0f
#define ACCEL_RIGHT  1.0f
#define CHAR_GRAVITY  1.0f

//*****************************************************************************
// �񋓌^��`
//*****************************************************************************

enum {
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP
};

//*****************************************************************************
// �\���̒�`�@���@���̃N���X�ɕK�v�ȕϐ��Z�b�g
//*****************************************************************************

struct CharController {

	bool isActive;// �L������
	int direction;// ����
	float moveSpeedX, moveSpeedY;// �ړ����xXY
	float maxMoveSpeedX;// �ő�ړ����x
	float accelForceX;// �����xX
	float stopForceX;// ��~��X�@���@���C�͓I�Ȃ���

};

//*****************************************************************************
// �N���X�֐��̃v���g�^�C�v�錾
//*****************************************************************************

// �\���́i�K�v�ȕϐ��Z�b�g�j�̏�����
void CharController_Initialize(CharController* pThis);

// ���t���[���Ăяo���āA�n���ꂽXY���W�������x�t���ړ�������
void CharController_Update(CharController* pThis, float* pPosX, float* pPosY);

// X�������ɂ��āA���x������������
void CharController_Accelerate(CharController* pThis, float directionX);