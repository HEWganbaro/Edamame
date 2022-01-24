#include "animator.h"
#include "GameTimer.h"

void Animator_Initialize(Animator * pThis)
{
	pThis->frame = 0;
	pThis->time = 0.0f;
	pThis->speed = 8.0;  // �f�t�H���g�̃A�j���[�V�������x
	pThis->isActive = false;  // �f�t�H���g�̓A�j���[�V����ON
}

void Animator_Update(Animator * pThis)
{
	if (pThis->isActive) {  // �A�j���[�V������ON�̎��������������s
		// �f���^�^�C�����擾���ĉ��Z
		pThis->time += GameTimer_GetDeltaTime() * pThis->speed;

		// �e�[�u���A�j���[�V�����̃f�[�^�錾
		static const int dragon_animationTable[] = { 0, 0, 1, 2, 2, 1, ANIMATION_LOOP };

		// �e�[�u�����Q�Ƃ���̂Ɏg���Y�����ϐ�
		// �Q�[�����[�v��~���ɔz��̈�I�[�o�[��h�����߁����g��
		int animationCounter = (int)pThis->time % ARRAYSIZE(dragon_animationTable);

		// ���[�v�̍Ō�ɒB������
		if (dragon_animationTable[animationCounter] == ANIMATION_LOOP) {
			animationCounter = 0;
			pThis->time = 0;
		}

		pThis->frame = dragon_animationTable[animationCounter];  // �e�[�u�����猻�݂̃R�}�ԍ����
	}
}
