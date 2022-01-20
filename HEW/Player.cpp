#include "Player.h"

//*****************************************************************************
// プレイヤー1
//*****************************************************************************

int Player_cut = 0;
int Player2_cut = 0;

void Player_Initialize(GameObject* Player , GameObject* Player2) {
	//プレイヤー1
	Player->texture = new Sprite("assets/snowBall.png", 2, 1);
	Player->texture->SetSize(100, 100);
	Player->posY = 0.5f;
	Player->mappos.Height = 0;
	Player->mappos.LeftDown = 0;
	Player->mappos.RightDown = 0;
	Player->direction = NULL_WAY;
	//プレイヤー2
	Player2->texture = new Sprite("assets/snowBall.png", 2, 1);
	Player2->texture->SetSize(100, 100);
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
	//プレイヤー1
	Player->posX = Location[Height * 100 + LeftDown * 10 + RightDown].posX + MAP_LENGTH / 2.0f;
	Player->posY = Location[Height * 100 + LeftDown * 10 + RightDown].posY;
	Player->mappos.Height = Height;
	Player->mappos.LeftDown = LeftDown;
	Player->mappos.RightDown = RightDown;
	//プレイヤー2
	Player2->posX = Location[Height2 * 100 + LeftDown2 * 10 + RightDown2].posX + MAP_LENGTH / 2.0f;
	Player2->posY = Location[Height2 * 100 + LeftDown2 * 10 + RightDown2].posY;
	Player2->mappos.Height = Height2;
	Player2->mappos.LeftDown = LeftDown2;
	Player2->mappos.RightDown = RightDown2;
}

void Player_Input(GameObject * Player , GameObject* Map
				 ,GameObject * Player2, GameObject* Map2)
{
	//プレイヤー1
	XINPUT_STATE state;
	XInputGetState(0, &state);

	//ステージマップによって分岐させる
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
	}// プレイヤー動く関数
	MapMove_Update(Player, Map);

	//プレイヤー2
	XINPUT_STATE state2;
	XInputGetState(0, &state2);

	//ステージマップによって分岐させる
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
	}// プレイヤー動く関数
	MapMove_Update(Player2, Map2);
}

MapPos Player_GetMapPos(GameObject * Player, GameObject * Player2)
{
	MapPos mappos;
	mappos.Height = Player->mappos.Height;
	mappos.Height = Player2->mappos.Height;
	return mappos;
}

void Player_Update(GameObject * Player, GameObject* Map, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE]
	, GameObject * Player2, GameObject* Map2, int MapChip2[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE])
{
	// 雪玉1
	MapMove_Update(Player, Map);
	if (Map_GetPlayerTile(Player, Map) == SNOW_GROUND) {
		Map[Player->mappos.Height * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown].texture->SetPart(1, 0);
		Map[Player->mappos.Height * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown].yobiFlag = true;
		Player->texture->SetPart(0, 0);

	}
	else if (Map_GetPlayerTile(Player, Map) == NORMAL_GROUND) {
		Map[Player->mappos.Height * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown].changeFlag = true;
		Player->texture->SetPart(0, 0);

	}
	else if (Map_GetPlayerTile(Player, Map) == SOIL_GROUND) {
		Player->texture->SetPart(1, 0);
	}
	// 雪玉2
	MapMove_Update(Player2, Map2);
	if (Map_GetPlayerTile(Player2, Map2) == SNOW_GROUND) {
		Map2[Player2->mappos.Height * 100 + Player2->mappos.LeftDown * 10 + Player2->mappos.RightDown].texture->SetPart(1, 0);
		Map2[Player2->mappos.Height * 100 + Player2->mappos.LeftDown * 10 + Player2->mappos.RightDown].yobiFlag = true;
		Player2->texture->SetPart(0, 0);
	}
	else if (Map_GetPlayerTile(Player2, Map) == NORMAL_GROUND) {
		Map[Player2->mappos.Height * 100 + Player2->mappos.LeftDown * 10 + Player2->mappos.RightDown].changeFlag = true;
		Player2->texture->SetPart(0, 0);
	}
	else if (Map_GetPlayerTile(Player2, Map) == SOIL_GROUND) {
		Player2->texture->SetPart(1, 0);
	}
}

void toIce(GameObject* Map) {
	for (int i = 0; i < 300; i++) {
		if (Map[i].yobiFlag == false) {
			if (Map[i].changeFlag == true) {
				Map[i].texture->SetPart(2, 0);
			}
		}
		else
			Map[i].yobiFlag = false;
	}
	turn = PLAYER_TURN;
}