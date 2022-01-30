#include "Player.h"

//*****************************************************************************
// プレイヤー1
//*****************************************************************************

int Player1_cut = 0;
int Player2_cut = 0;
int big_snowball = 0;
//プレイヤーの初期化
void Player_Initialize(GameObject* Player) {
	Player->texture = new Sprite("assets/Player_kansei.png", 48, 8);
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
	Player->SoilFrg = false;
	Player->EnemyAttak = false;
	Player->direction = NULL_WAY;
}
//カーソルの初期化
void Cursor_Initialize(GameObject * Cursor)
{
	Cursor->texture = new Sprite("assets/cursor.png", 2, 1);
	Cursor->texture->SetSize(INIT_CURSOR_SIZE, INIT_CURSOR_SIZE * 2);
	Cursor->posX = 0.5f;
	Cursor->posY = 0.5f;
}
//プレイヤーを指定の座標にスポーンさせる
void Player_SetLocation(GameObject* Player, GameObject* Location,
					int Height, int LeftDown, int RightDown)
{
	Player->posX = Location[Height * 100 + LeftDown * 10 + RightDown].posX;
	Player->posY = Location[Height * 100 + LeftDown * 10 + RightDown].posY + MAP_LENGTH / 2.0f;
	Player->mappos.Height = Height;
	Player->mappos.LeftDown = LeftDown;
	Player->mappos.RightDown = RightDown;
}
//プレイヤーの移動入力
void Player_Input(GameObject * Player, GameObject * Player2)
{
	//プレイヤー1
	XINPUT_STATE state;
	XInputGetState(0, &state);

	//ステージマップによって分岐させる
	if (Player->direction == NULL_WAY && Player2->direction == NULL_WAY && Player->Goalfrg == false) {
		if (Input_GetKeyTrigger('Q') || (state.Gamepad.sThumbLX < DEADZONE_MSTICK&&state.Gamepad.sThumbLY > DEADZONE_STICK)) {
			Player->direction = LEFT_UP;
			Player->mappos.RightDown--;
			Player1_cut++;
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_SNOWHUNDA));
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_PLAYERGROW));
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_MOVE));
		}
		if (Input_GetKeyTrigger('A') || (state.Gamepad.sThumbLX < DEADZONE_MSTICK&&state.Gamepad.sThumbLY < DEADZONE_MSTICK)){
			Player->direction = LEFT_DOWN;
			Player->mappos.LeftDown++;
			Player1_cut++;
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_SNOWHUNDA));
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_PLAYERGROW));
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_MOVE));
		}
		if (Input_GetKeyTrigger('E') || (state.Gamepad.sThumbLX > DEADZONE_STICK&&state.Gamepad.sThumbLY > DEADZONE_STICK)) {
			Player->direction = RIGHT_UP;
			Player->mappos.LeftDown--;
			Player1_cut++;
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_SNOWHUNDA));
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_PLAYERGROW));
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_MOVE));
		}
		if (Input_GetKeyTrigger('D') || (state.Gamepad.sThumbLX > DEADZONE_STICK&&state.Gamepad.sThumbLY < DEADZONE_MSTICK)) {
			Player->direction = RIGHT_DOWN;
			Player->mappos.RightDown++;
			Player1_cut++;
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_SNOWHUNDA));
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_PLAYERGROW));
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_MOVE));
		}
	}

	//プレイヤー2
	if (Player->direction == NULL_WAY && Player2->direction == NULL_WAY && Player2->Goalfrg == false) {
		if (Input_GetKeyTrigger('U') || (state.Gamepad.sThumbRX < DEADZONE_MSTICK&&state.Gamepad.sThumbRY > DEADZONE_STICK)) {
			Player2->direction = LEFT_UP;
			Player2->mappos.RightDown--;
			Player2_cut++;
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_SNOWHUNDA));
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_PLAYERGROW));
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_MOVE));
		}
		if (Input_GetKeyTrigger('J') || (state.Gamepad.sThumbRX < DEADZONE_MSTICK&&state.Gamepad.sThumbRY < DEADZONE_MSTICK)) {
			Player2->direction = LEFT_DOWN;
			Player2->mappos.LeftDown++;
			Player2_cut++;
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_SNOWHUNDA));
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_PLAYERGROW));
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_MOVE));
		}
		if (Input_GetKeyTrigger('O') || (state.Gamepad.sThumbRX > DEADZONE_STICK&&state.Gamepad.sThumbRY > DEADZONE_STICK)) {
			Player2->direction = RIGHT_UP;
			Player2->mappos.LeftDown--;
			Player2_cut++;
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_SNOWHUNDA));
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_PLAYERGROW));
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_MOVE));
		}
		if (Input_GetKeyTrigger('L') || (state.Gamepad.sThumbRX > DEADZONE_STICK&&state.Gamepad.sThumbRY < DEADZONE_MSTICK)) {
			Player2->direction = RIGHT_DOWN;
			Player2->mappos.RightDown++;
			Player2_cut++;
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_SNOWHUNDA));
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_PLAYERGROW));
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_MOVE));
		}
	}
}
//プレイヤーの見た目の更新(サイズ)
void Player_Update(GameObject * Player, GameObject* Map)
{
	MapMove_Update(Player, Map);
	//地面状態移行をしてない
	Player->texture->SetSize(INIT_SNOW_SIZE * (1 + Player->SnowSize*0.05f), INIT_SNOW_SIZE * (1 + Player->SnowSize*0.05f));
}
//カーソルがプレイヤーを追尾するように
void Cursor_Update(GameObject * Player, GameObject * Cursor)
{
	Cursor->posX = Player->posX + 0.05f;
	Cursor->posY = Player->posY + 0.1f;
}
//プレイヤーのアニメーション
void Player_AniUpdate(GameObject * Player)
{
	//アニメーション
	Animator_Update(&Player->animator);

	int walk = 0, growth = 0, soil = 0, gameover = 0;
	if (Player->animator.isActive == true)
		walk = 8;
	if (Player->SnowSize > 3)
		growth = 24;
	if (Player->SoilFrg == true)
		soil = 1;
	if (turn == GAMEOVER || turn == PENGUIN2)
		gameover = 16;
	//アニメーション
	switch (Player->direction)
	{
	case NULL_WAY:
		switch (Player->diretmp)
		{
		case NULL_WAY:
			Player->texture->SetPart(Player->animator.frame +  growth, 0 + soil);
			break;
		case RIGHT_DOWN:
			Player->texture->SetPart(Player->animator.frame +  growth, 0 + soil);
			break;

		case LEFT_DOWN:
			Player->texture->SetPart(Player->animator.frame +  growth, 2 + soil);
			break;

		case LEFT_UP:
			Player->texture->SetPart(Player->animator.frame +  growth, 4 + soil);
			break;

		case RIGHT_UP:
			Player->texture->SetPart(Player->animator.frame +  growth, 6 + soil);
			break;
		}
		break;

	case RIGHT_DOWN:
		Player->texture->SetPart(Player->animator.frame + walk + growth, 0 + soil);
		break;

	case LEFT_DOWN:
		Player->texture->SetPart(Player->animator.frame + walk + growth, 2 + soil);
		break;

	case LEFT_UP:
		Player->texture->SetPart(Player->animator.frame + walk + growth, 4 + soil);
		break;

	case RIGHT_UP:
		Player->texture->SetPart(Player->animator.frame + walk + growth, 6 + soil);
		break;
	}
	if (turn == GAMEOVER || turn == PENGUIN2) {
		switch (Player->direction)
		{
		case NULL_WAY:
			Player->texture->SetPart(Player->animator.frame + gameover + growth, 0 + soil);
			break;

		case RIGHT_DOWN:
			Player->texture->SetPart(Player->animator.frame + gameover + growth, 0 + soil);
			break;

		case LEFT_DOWN:
			Player->texture->SetPart(Player->animator.frame + gameover + growth, 2 + soil);
			break;

		case LEFT_UP:
			Player->texture->SetPart(Player->animator.frame + gameover + growth, 4 + soil);
			break;

		case RIGHT_UP:
			Player->texture->SetPart(Player->animator.frame + gameover + growth, 6 + soil);
			break;
		}
	}
}
//プレイヤーがマップを通った時の更新処理
void MapUpdate(GameObject* Map, GameObject* Player, GameObject* Player2) {
	for (int i = 0; i < 300; i++) {
		if (Map[i].texture->GetPart() != GOAL_LATER) {
			if (Map[i].changeFlag == true) {
				Map[i].texture->SetPart(2, 0);
			}
		}
	}
	if (Map_GetPlayerTile(Player, Map) == SNOW_GROUND) {
		Map[Player->mappos.Height * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown].texture->SetPart(1, 0);
		Map[Player->mappos.Height * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown].yobiFlag = SNOW_STATE;
		//Player->texture->SetPart(0, 0);
		if (Player->SoilFrg == true)
			Player->SoilFrg = false;
		Player->SnowSize++;
		XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_MOVE));
		XA_Play(SOUND_LABEL(SOUND_LABEL_SE_SNOWHUNDA));
		if (Player2->SnowSize == 4)
		{
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_PLAYERGROW));
		}
	}
	else if (Map_GetPlayerTile(Player, Map) == NORMAL_GROUND) {
		Map[Player->mappos.Height * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown].changeFlag = true;
		//Player->texture->SetPart(0, 0);
		XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_MOVE));
		if (Player->SoilFrg == true)
			Player->SoilFrg = false;
	}
	else if (Map_GetPlayerTile(Player, Map) == SOIL_GROUND) {
		Player->SoilFrg = true;
		//Player->texture->SetPart(1, 0);
		XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_MOVE));
	}

	if (Map_GetPlayerTile(Player2, Map) == SNOW_GROUND) {
		Map[Player2->mappos.Height * 100 + Player2->mappos.LeftDown * 10 + Player2->mappos.RightDown].texture->SetPart(1, 0);
		Map[Player2->mappos.Height * 100 + Player2->mappos.LeftDown * 10 + Player2->mappos.RightDown].yobiFlag = SNOW_STATE;
		//Player2->texture->SetPart(0, 0);
		if (Player2->SoilFrg == true)
			Player2->SoilFrg = false;
		Player2->SnowSize++;
		XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_MOVE));
		XA_Play(SOUND_LABEL(SOUND_LABEL_SE_SNOWHUNDA));
		if (Player2->SnowSize == 4)
		{
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_PLAYERGROW));
		}
	}
	else if (Map_GetPlayerTile(Player2, Map) == NORMAL_GROUND) {
		Map[Player2->mappos.Height * 100 + Player2->mappos.LeftDown * 10 + Player2->mappos.RightDown].changeFlag = true;
		XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_MOVE));
		//Player2->texture->SetPart(0, 0);
		if (Player2->SoilFrg == true)
			Player2->SoilFrg = false;
	}
	else if (Map_GetPlayerTile(Player2, Map) == SOIL_GROUND) {
		//Player2->texture->SetPart(1, 0);
		XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_MOVE));
		Player2->SoilFrg = true;
	}
	turn = PLAYER_TURN;
}
//どっちの雪玉が大きいかを出す処理
float Big_SnowBall(GameObject * Player, GameObject * Player2)
{
	big_snowball = (Player->SnowSize > Player2->SnowSize) ? Player->SnowSize : Player2->SnowSize;
	return big_snowball;
}