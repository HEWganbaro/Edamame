#include "Player.h"

//*****************************************************************************
// �v���C���[1
//*****************************************************************************

int Player_cut = 0;
int Player2_cut = 0;

void Player_Initialize(GameObject* Player , GameObject* Player2) {
	//�v���C���[1
	Player->textuer = new Sprite("assets/Player.png", 1, 1);
	Player->textuer->SetSize(80, 80);
	Player->posY = 0.5f;
	Player->mappos.Height = 0;
	Player->mappos.LeftDown = 0;
	Player->mappos.RightDown = 0;
	Player->direction = NULL_WAY;
	//�v���C���[2
	Player2->textuer = new Sprite("assets/Player2.png", 1, 1);
	Player2->textuer->SetSize(80, 80);
	Player2->posY = 0.5f;
	Player2->mappos.Height = 0;
	Player2->mappos.LeftDown = 0;
	Player2->mappos.RightDown = 0;
	Player2->direction = NULL_WAY;
}

void Player_SetLocation(GameObject* Player, GameObject* Location,
					int Height, int LeftDown, int RightDown
					  , GameObject* Player2, GameObject* Location2,
					int Height2, int LeftDown2, int RightDown2)
{
	//�v���C���[1
	Player->posX = Location[Height * 100 + LeftDown * 10 + RightDown].posX + MAP_LENGTH / 2.0f;
	Player->posY = Location[Height * 100 + LeftDown * 10 + RightDown].posY;
	Player->mappos.Height = Height;
	Player->mappos.LeftDown = LeftDown;
	Player->mappos.RightDown = RightDown;
	//�v���C���[2
	Player2->posX = Location[Height2 * 100 + LeftDown2 * 10 + RightDown2].posX + MAP_LENGTH / 2.0f;
	Player2->posY = Location[Height2 * 100 + LeftDown2 * 10 + RightDown2].posY;
	Player2->mappos.Height = Height2;
	Player2->mappos.LeftDown = LeftDown2;
	Player2->mappos.RightDown = RightDown2;
}

void Player_Input(GameObject * Player , GameObject* Map
				 ,GameObject * Player2, GameObject* Map2)
{
	//�v���C���[1
	XINPUT_STATE state;
	XInputGetState(0, &state);

	//�X�e�[�W�}�b�v�ɂ���ĕ��򂳂���
	if (Player->direction == NULL_WAY) {
		if (Input_GetKeyTrigger('Q') || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)) {
			Player->direction = LEFT_UP;
			Player->mappos.RightDown--;
			Player_cut++;
			Enemy_flg = 1;
		}
		if (Input_GetKeyTrigger('A')||(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)) {
			Player->direction = LEFT_DOWN;
			Player->mappos.LeftDown++;
			Player_cut++;
			Enemy_flg = 1;
		}
		if (Input_GetKeyTrigger('E')||(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) {
			Player->direction = RIGHT_UP;
			Player->mappos.LeftDown--;
			Player_cut++;
			Enemy_flg = 1;
		}
		if (Input_GetKeyTrigger('D')||(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) {
			Player->direction = RIGHT_DOWN;
			Player->mappos.RightDown++;
			Player_cut++;
			Enemy_flg = 1;
		}
	}// �v���C���[�����֐�
	MapMove_Update(Player, Map);

	//�v���C���[2
	XINPUT_STATE state2;
	XInputGetState(0, &state2);

	//�X�e�[�W�}�b�v�ɂ���ĕ��򂳂���
	if (Player2->direction == NULL_WAY) {
		if (Input_GetKeyTrigger('U') || (state2.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && (state2.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)) {
			Player2->direction = LEFT_UP;
			Player2->mappos.RightDown--;
			Player2_cut++;
		}
		if (Input_GetKeyTrigger('J') || (state2.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && (state2.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)) {
			Player2->direction = LEFT_DOWN;
			Player2->mappos.LeftDown++;
			Player2_cut++;
		}
		if (Input_GetKeyTrigger('O') || (state2.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && (state2.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) {
			Player2->direction = RIGHT_UP;
			Player2->mappos.LeftDown--;
			Player2_cut++;
		}
		if (Input_GetKeyTrigger('L') || (state2.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && (state2.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) {
			Player2->direction = RIGHT_DOWN;
			Player2->mappos.RightDown++;
			Player2_cut++;
		}
	}// �v���C���[�����֐�
	MapMove_Update(Player2, Map2);
}

MapPos Player_GetMapPos(GameObject * Player, GameObject * Player2)
{
	MapPos mappos;
	mappos.Height = Player->mappos.Height;
	mappos.Height = Player2->mappos.Height;
	return mappos;
}

void Player_Update(GameObject * Player, GameObject * Player2)
{

}