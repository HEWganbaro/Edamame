#include "Player.h"

void Player_Initialize(GameObject* Player) {
	Player->textuer = new Sprite("assets/Player.png", 1, 1);
	Player->textuer->SetSize(80, 80);
	Player->posY = 0.5f;
	Player->mappos.Height = 0;
	Player->mappos.LeftDown = 0;
	Player->mappos.RightDown = 0;
	Player->direction = NULL_WAY;
}

void Player_SetLocation(GameObject* Player, GameObject* Location,
					int Height, int LeftDown, int RightDown)
{
	Player->posX = Location[Height * 100 + LeftDown * 10 + RightDown].posX + MAP_LENGTH / 2.0f;
	Player->posY = Location[Height * 100 + LeftDown * 10 + RightDown].posY;
	Player->mappos.Height = Height;
	Player->mappos.LeftDown = LeftDown;
	Player->mappos.RightDown = RightDown;
	
}

void Player_Input(GameObject * Player ,int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE])
{
	XINPUT_STATE state;
	XInputGetState(0, &state);
	//ステージマップによって分岐させる
	if (Player->direction == NULL_WAY) {
		if (Input_GetKeyTrigger('Q') || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)) {
			Player->direction = LEFT_UP;
			Player->mappos.RightDown--;
		}
		if (Input_GetKeyTrigger('A')||(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)) {
			Player->direction = LEFT_DOWN;
			Player->mappos.LeftDown++;
		}
		if (Input_GetKeyTrigger('E')||(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) {
			Player->direction = RIGHT_UP;
			Player->mappos.LeftDown--;
		}
		if (Input_GetKeyTrigger('D')||(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) {
			Player->direction = RIGHT_DOWN;
			Player->mappos.RightDown++;
		}
	}// プレイヤー動く関数
	MapMove_Update(Player, MapChip);
}

MapPos Player_GetMapPos(GameObject * Player)
{
	MapPos mappos;
	mappos.Height = Player->mappos.Height;
	return mappos;
}

void Player_Update(GameObject * Plyaer)
{

}
