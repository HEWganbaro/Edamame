#pragma once


// �e�[�u���A�j���[�V�����ŃJ�E���^�[���O�ɖ߂��A�Ƃ������}
#define ANIMATION_LOOP  -1


// Animator�N���X

// �K�v�ȕϐ���ϐ��Z�b�g�Ƃ��č\���̂ɂ���
struct Animator {
	int count;

	int frame;  // ���݂̃A�j���̃t���[���ԍ�������
	float time;  // �f���^�^�C�������Z�������Ԃ����ϐ�
	float speed;  // �A�j���[�V�����̍Đ����x

	//�A�j���[�V������ON/OFF��؂�ւ��邽�߂̕ϐ�
	bool isActive;

};


// �\���̂̕ϐ�������������֐�
void Animator_Initialize(Animator* pThis);

// ���t���[���Ăяo����A�A�j���[�V�����̃R�}��i�߂�֐�
void Animator_Update(Animator* pThis);
