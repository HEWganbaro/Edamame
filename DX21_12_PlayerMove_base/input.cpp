#include "input.h"
#include <Windows.h>


#define MAX_KEYS  256

static short gOldKeys[MAX_KEYS];
static short gKeys[MAX_KEYS];

void Input_Update()
{
	// �O�̃t���[���̃L�[��Ԃ�ۑ�
	memcpy_s(gOldKeys, sizeof(gOldKeys), gKeys, sizeof(gKeys));

	// ���݃t���[���̃L�[��Ԃ��擾
	gKeys[VK_UP] = GetAsyncKeyState(VK_UP);
	gKeys[VK_DOWN] = GetAsyncKeyState(VK_DOWN);
	gKeys[VK_LEFT] = GetAsyncKeyState(VK_LEFT);
	gKeys[VK_RIGHT] = GetAsyncKeyState(VK_RIGHT);
	gKeys[VK_LBUTTON] = GetAsyncKeyState(VK_LBUTTON);
	gKeys['A'] = GetAsyncKeyState('A');
	gKeys['D'] = GetAsyncKeyState('D');
}

bool Input_GetKeyPress(int vkey)
{
	return gKeys[vkey] & 0x8000;
}

bool Input_GetKeyTrigger(int vkey)
{
	return (gKeys[vkey] & 0x8000) != 0 && (gOldKeys[vkey] & 0x8000) == 0;
}