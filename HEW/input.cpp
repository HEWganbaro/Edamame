#include "input.h"
#include"Controller.h"
#include <Windows.h>
#include <d3d11_1.h>
#include <dxgi1_2.h>
#include <d2d1_2.h>


#define MAX_KEYS  256

static short gOldKeys[MAX_KEYS];
static short gKeys[MAX_KEYS];

void Input_Update()
{
	// 前のフレームのキー状態を保存
	memcpy_s(gOldKeys, sizeof(gOldKeys), gKeys, sizeof(gKeys));

	// 現在フレームのキー状態を取得
	gKeys[VK_UP] = GetAsyncKeyState(VK_UP);
	gKeys[VK_DOWN] = GetAsyncKeyState(VK_DOWN);
	gKeys[VK_LEFT] = GetAsyncKeyState(VK_LEFT);
	gKeys[VK_RIGHT] = GetAsyncKeyState(VK_RIGHT);
	gKeys[VK_SPACE] = GetAsyncKeyState(VK_SPACE);
	gKeys[VK_LBUTTON] = GetAsyncKeyState(VK_LBUTTON);
	gKeys['A'] = GetAsyncKeyState('A');
	gKeys['D'] = GetAsyncKeyState('D');
	gKeys['Q'] = GetAsyncKeyState('Q');
	gKeys['E'] = GetAsyncKeyState('E');
	gKeys['U'] = GetAsyncKeyState('U');
	gKeys['O'] = GetAsyncKeyState('O');
	gKeys['J'] = GetAsyncKeyState('J');
	gKeys['L'] = GetAsyncKeyState('L');
	////////////////////////////////////////////////
/*1129コントローラー入力芳山*/
//ゲームパッドの状態を取得
	XINPUT_STATE state;
	XInputGetState(0, &state);
	int iPad_left = 0, iPad_right = 0, iPad_up = 0, iPad_down = 0;
	int iPad_leftshoulder = 0, iPad_rightshoulder = 0;
	int iPad_A = 0, iPad_B = 0, iPad_X = 0, iPad_Y = 0;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) iPad_left = 1;//ゲームパッド十字キー左
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) iPad_right = 1;//ゲームパッド十字キー右
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) iPad_up = 1;//ゲームパッド十字キー上
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) iPad_down = 1;//ゲームパッド十字キー下

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFTUP) iPad_left = 1;//ゲームパッド十字キー左
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFTDOWN) iPad_right = 1;//ゲームパッド十字キー右
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHTUP) iPad_up = 1;//ゲームパッド十字キー上
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHTDOWN) iPad_down = 1;//ゲームパッド十字キー下

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) iPad_leftshoulder = 1;//ゲームパッドL
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) iPad_rightshoulder = 1;//ゲームパッドR
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) iPad_A = 1;//ゲームパッドA
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) iPad_B = 1;//ゲームパッドB
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) iPad_X = 1;//ゲームパッドX
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) iPad_Y = 1;//ゲームパッドY
	//ゲームパッドアナログスティックのデッドゾーン処理
	if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;
	}

	///////////////////////////////////////////////
//ゲームパッドのAまたはBを押した時の処理：ゲームパッドの振動
	XINPUT_VIBRATION vibration;
	vibration.wLeftMotorSpeed = 0;
	vibration.wRightMotorSpeed = 0;
	XInputSetState(0, &vibration);
	if (iPad_A)
	{
		vibration.wLeftMotorSpeed = 65535;
		XInputSetState(0, &vibration);
	}
	if (iPad_B)
	{
		vibration.wRightMotorSpeed = 65535;
		XInputSetState(0, &vibration);
	}
	//------------------------------------------------------------
   // 文字操作
   //------------------------------------------------------------
	//ゲームパッド入力状態表示用
	WCHAR wcText3[256] = { 0 };
	swprintf(wcText3, 256, L"PAD_LEFT=%d PAD_RIGHT=%d PAD_UP=%d PAD_DOWN=%d", iPad_left, iPad_right, iPad_up, iPad_down);
	WCHAR wcText4[256] = { 0 };
	swprintf(wcText4, 256, L"LEFT_SHOULDER=%d RIGHT_SHOULDER=%d", iPad_leftshoulder, iPad_rightshoulder);
	WCHAR wcText5[256] = { 0 };
	swprintf(wcText5, 256, L"PAD_A=%d PAD_B=%d PAD_X=%d PAD_Y=%d", iPad_A, iPad_B, iPad_X, iPad_Y);
	WCHAR wcText6[256] = { 0 };
	swprintf(wcText6, 256, L"sThumbLX=%d sThumbLY=%d", state.Gamepad.sThumbLX, state.Gamepad.sThumbLY);
	WCHAR wcText7[256] = { 0 };
	swprintf(wcText7, 256, L"bLeftTrigger=%d bRightTrigger=%d", state.Gamepad.bLeftTrigger, state.Gamepad.bRightTrigger);

}

bool Input_GetKeyPress(int vkey)
{
	return gKeys[vkey] & 0x8000;
}

bool Input_GetKeyTrigger(int vkey)
{
	return (gKeys[vkey] & 0x8000) != 0 && (gOldKeys[vkey] & 0x8000) == 0;
}
