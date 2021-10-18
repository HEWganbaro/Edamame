#include "CharController.h"
#include "GameTimer.h"
#include <math.h>

void CharController_Initialize(CharController * pThis)
{
	pThis->isActive = true;
	pThis->direction = DIR_RIGHT;
	pThis->maxMoveSpeedX = 0.6f;
	pThis->accelForceX = pThis->maxMoveSpeedX * 0.1f;
	pThis->stopForceX = pThis->accelForceX * 0.6f;
}

void CharController_Update(CharController * pThis, float* pPosX, float* pPosY)
{
	if (pThis->isActive) {
		// �ړ�����
		*pPosX += 1;

		// ����
	}
}

void CharController_Accelerate(CharController * pThis, float directionX)
{
	// ���������@directionX���g����

	// ���x���ō����x�𒴂��Ȃ��悤�ɂ���
}
