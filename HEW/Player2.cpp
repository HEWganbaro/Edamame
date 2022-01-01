#include "Player2.h"

int Player2_cut = 0;

void Player2_Initialize(GameObject* Player2) {
	Player2->textuer = new Sprite("assets/Player.png", 1, 1);
	Player2->textuer->SetSize(80, 80);
	Player2->posY = 0.5f;
	Player2->mappos.Height = 0;
	Player2->mappos.LeftDown = 0;
	Player2->mappos.RightDown = 0;
	Player2->direction = NULL_WAY;
}

void Player2_SetLocation(GameObject* Player2, GameObject* Location,
					int Height, int LeftDown, int RightDown)
{
	Player2->posX = Location[Height * 100 + LeftDown * 10 + RightDown].posX + MAP_LENGTH / 2.0f;
	Player2->posY = Location[Height * 100 + LeftDown * 10 + RightDown].posY;
	Player2->mappos.Height = Height;
	Player2->mappos.LeftDown = LeftDown;
	Player2->mappos.RightDown = RightDown;
	
}

void Player2_Input(GameObject * Player2 , GameObject* Map){
	XINPUT_STATE state;
	XInputGetState(0, &state);
	//ステージマップによって分岐させる
	if (Player2->direction == NULL_WAY) {
		if (Input_GetKeyTrigger('Q') || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)) {
			Player2->direction = LEFT_UP;
			Player2->mappos.RightDown--;
			Player2_cut++;
		}
		if (Input_GetKeyTrigger('A')||(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)) {
			Player2->direction = LEFT_DOWN;
			Player2->mappos.LeftDown++;
			Player2_cut++;
		}
		if (Input_GetKeyTrigger('E')||(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) {
			Player2->direction = RIGHT_UP;
			Player2->mappos.LeftDown--;
			Player2_cut++;
		}
		if (Input_GetKeyTrigger('D')||(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) {
			Player2->direction = RIGHT_DOWN;
			Player2->mappos.RightDown++;
			Player2_cut++;
		}
	}// プレイヤー動く関数
	MapMove_Update(Player2, Map);
}

MapPos Player2_GetMapPos(GameObject * Player2)
{
	MapPos mappos;
	mappos.Height = Player2->mappos.Height;
	return mappos;
}

void Player2_Update(GameObject * Plyaer)
{

}
