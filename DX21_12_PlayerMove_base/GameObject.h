#pragma once
// ���@���̖��߂������Ă����ƁA�w�b�_�[�����x���C���N���[�h����Ē�`�d���G���[��
// �@�@�o��̂�h�����Ƃ��ł���B

#include "animator.h"
#include "CharController.h"
#include "UvInfo.h"
#include "Sprite.h"

// GameObject�N���X

// GameObject�N���X�ŕK�v�ɂȂ�ϐ��Z�b�g���\���̂Ƃ��Ē�`
struct GameObject {

	// �ϐ������Ă���
	float posX, posY;  // ���S�_�̍��W
	float sizeX, sizeY; // �傫��

	CharController charController;  // �L�����ړ��̃N���X�ϐ�

	Animator animator;  // �A�j���[�V�����̃N���X�ϐ�

	UvInfo uvinfo; // �e�N�X�`���̏��

	Sprite* textuer;	//�摜�f�[�^
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


