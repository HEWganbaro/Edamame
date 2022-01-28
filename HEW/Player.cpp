#include "Player.h"

//*****************************************************************************
// プレイヤー1
//*****************************************************************************

int Player1_cut = 0;
int Player2_cut = 0;
int big_snowball = 0;

void Player_Initialize(GameObject* Player) {
	Player->texture = new Sprite("assets/yukichara.png", 32, 4);
	Player->texture->SetSize(INIT_SNOW_SIZE, INIT_SNOW_SIZE);
	Player->posY = 0.5f;
	Player->mappos.Height = 0;
	Player->mappos.LeftDown = 0;
	Player->mappos.RightDown = 0;
	Player->SnowSize = 1;
	Player->animator.speed = 8.0f;
	Player->Goalfrg = false;
	Player->Item_Face = false;
	Player->Item_Arm = false;
	Player->direction = NULL_WAY;
}

void Player_SetLocation(GameObject* Player, GameObject* Location,
					int Height, int LeftDown, int RightDown)
{
	Player->posX = Location[Height * 100 + LeftDown * 10 + RightDown].posX;
	Player->posY = Location[Height * 100 + LeftDown * 10 + RightDown].posY + MAP_LENGTH / 2.0f;
	Player->mappos.Height = Height;
	Player->mappos.LeftDown = LeftDown;
	Player->mappos.RightDown = RightDown;
}

void Player_Input(GameObject * Player, GameObject * Player2)
{
	//プレイヤー1
	XINPUT_STATE state;
	XInputGetState(0, &state);

	//ステージマップによって分岐させる
	if (Player->direction == NULL_WAY && Player->Goalfrg == false) {
		if (Input_GetKeyTrigger('Q') || (state.Gamepad.sThumbLX < DEADZONE_MSTICK&&state.Gamepad.sThumbLY > DEADZONE_STICK)) {
			Player->direction = LEFT_UP;
			Player->mappos.RightDown--;
			Player1_cut++;
		}
		if (Input_GetKeyTrigger('A') || (state.Gamepad.sThumbLX < DEADZONE_MSTICK&&state.Gamepad.sThumbLY < DEADZONE_MSTICK)){
			Player->direction = LEFT_DOWN;
			Player->mappos.LeftDown++;
			Player1_cut++;
		}
		if (Input_GetKeyTrigger('E') || (state.Gamepad.sThumbLX > DEADZONE_STICK&&state.Gamepad.sThumbLY > DEADZONE_STICK)) {
			Player->direction = RIGHT_UP;
			Player->mappos.LeftDown--;
			Player1_cut++;
		}
		if (Input_GetKeyTrigger('D') || (state.Gamepad.sThumbLX > DEADZONE_STICK&&state.Gamepad.sThumbLY < DEADZONE_MSTICK)) {
			Player->direction = RIGHT_DOWN;
			Player->mappos.RightDown++;
			Player1_cut++;
		}
	}

	//プレイヤー2
	if (Player2->direction == NULL_WAY && Player2->Goalfrg == false) {
		if (Input_GetKeyTrigger('U') || (state.Gamepad.sThumbRX < DEADZONE_MSTICK&&state.Gamepad.sThumbRY > DEADZONE_STICK)) {
			Player2->direction = LEFT_UP;
			Player2->mappos.RightDown--;
			Player2_cut++;
		}
		if (Input_GetKeyTrigger('J') || (state.Gamepad.sThumbRX < DEADZONE_MSTICK&&state.Gamepad.sThumbRY < DEADZONE_MSTICK)) {
			Player2->direction = LEFT_DOWN;
			Player2->mappos.LeftDown++;
			Player2_cut++;
		}
		if (Input_GetKeyTrigger('O') || (state.Gamepad.sThumbRX > DEADZONE_STICK&&state.Gamepad.sThumbRY > DEADZONE_STICK)) {
			Player2->direction = RIGHT_UP;
			Player2->mappos.LeftDown--;
			Player2_cut++;
		}
		if (Input_GetKeyTrigger('L') || (state.Gamepad.sThumbRX > DEADZONE_STICK&&state.Gamepad.sThumbRY < DEADZONE_MSTICK)) {
			Player2->direction = RIGHT_DOWN;
			Player2->mappos.RightDown++;
			Player2_cut++;
		}
	}
}

void Player_Update(GameObject * Player, GameObject* Map)
{
	MapMove_Update(Player, Map);
	//地面状態移行をしてない
	if (Map_GetPlayerTile(Player, Map) == SNOW_GROUND) {
		Map[Player->mappos.Height * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown].texture->SetPart(1, 0);
		Map[Player->mappos.Height * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown].yobiFlag = true;
		//Player->texture->SetPart(0, 0);
		Player->SnowSize++;
	}
	else if (Map_GetPlayerTile(Player, Map) == NORMAL_GROUND) {
		Map[Player->mappos.Height * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown].changeFlag = true;
		//Player->texture->SetPart(0, 0);

	}
	else if (Map_GetPlayerTile(Player, Map) == SOIL_GROUND) {
		//Player->texture->SetPart(1, 0);
	}
	Player->texture->SetSize(INIT_SNOW_SIZE * (1 + Player->SnowSize*0.05f), INIT_SNOW_SIZE * (1 + Player->SnowSize*0.05f));
}

void Player_AniUpdate(GameObject * Player)
{
	//アニメーション
	Animator_Update(&Player->animator);

	int walk = 0, growth = 0;
	if (Player->animator.isActive == true)
		walk = 8;
	if (Player->SnowSize > 3)
		growth = 16;
	//アニメーション
	switch (Player->direction)
	{
	case NULL_WAY:
		Player->texture->SetPart(Player->animator.frame + growth, 0);
		break;

	case RIGHT_DOWN:
		Player->texture->SetPart(Player->animator.frame + walk + growth, 0);
		break;

	case LEFT_DOWN:
		Player->texture->SetPart(Player->animator.frame + walk + growth, 1);
		break;

	case LEFT_UP:
		Player->texture->SetPart(Player->animator.frame + walk + growth, 2);
		break;

	case RIGHT_UP:
		Player->texture->SetPart(Player->animator.frame + walk + growth, 3);
		break;
	}
}

void toIce(GameObject* Map) {
	for (int i = 0; i < 300; i++) {
		if (Map[i].texture->GetPart() != GOAL_LATER) {
			if (Map[i].yobiFlag == false) {
				if (Map[i].changeFlag == true) {
					Map[i].texture->SetPart(2, 0);
				}
			}
			else
				Map[i].yobiFlag = false;
		}
	}
	turn = PLAYER_TURN;
}

float Big_SnowBall(GameObject * Player, GameObject * Player2)
{
	big_snowball = (Player->SnowSize > Player2->SnowSize) ? Player->SnowSize : Player2->SnowSize;
	return big_snowball;
}