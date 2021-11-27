#include "Player.h"
#include "input.h"

Direction Player_way;
int Player_cut;

void Player_Initialize(GameObject* Player) {
	Player->textuer = new Sprite("assets/Player.png", 1, 1);
	Player->textuer->SetSize(80, 80);
	Player->posY = 0.5f;
	Player->mappos.Height = 0;
	Player->mappos.LeftDown = 0;
	Player->mappos.RightDown = 0;
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

void Player_Input(GameObject * Player)
{
	//ステージマップによって分岐させる
	if (Player_way == NULL_WAY) {
		if (Input_GetKeyTrigger('Q')) {
			Player_way = LEFT_UP;
			Player->mappos.RightDown--;
		}
		if (Input_GetKeyTrigger('A')) {
			Player_way = LEFT_DOWN;
			Player->mappos.LeftDown++;
		}
		if (Input_GetKeyTrigger('E')) {
			Player_way = RIGHT_UP;
			Player->mappos.LeftDown--;
		}
		if (Input_GetKeyTrigger('D')) {
			Player_way = RIGHT_DOWN;
			Player->mappos.RightDown++;
		}
	}
	else {
		switch (Player_way)
		{
		case RIGHT_DOWN:
			if (Player_cut != PLAYER_SPEED) {
				Player->posX += MAP_LENGTH / PLAYER_SPEED;
				Player->posY -= MAP_LENGTH / PLAYER_SPEED;
				Player_cut++;
			}
			else {
				Player_way = NULL_WAY;
				Player_cut = 0;
			}
			break;

		case LEFT_DOWN:
			if (Player_cut != PLAYER_SPEED) {
				Player->posX -= MAP_LENGTH / PLAYER_SPEED;
				Player->posY -= MAP_LENGTH / PLAYER_SPEED;
				Player_cut++;
			}
			else {
				Player_way = NULL_WAY;
				Player_cut = 0;
			}
			break;

		case LEFT_UP:
			if (Player_cut != PLAYER_SPEED) {
				Player->posX -= MAP_LENGTH / PLAYER_SPEED;
				Player->posY += MAP_LENGTH / PLAYER_SPEED;
				Player_cut++;
			}
			else {
				Player_way = NULL_WAY;
				Player_cut = 0;
			}
			break;

		case RIGHT_UP:
			if (Player_cut != PLAYER_SPEED) {
				Player->posX += MAP_LENGTH / PLAYER_SPEED;
				Player->posY += MAP_LENGTH / PLAYER_SPEED;
				Player_cut++;
			}
			else {
				Player_way = NULL_WAY;
				Player_cut = 0;
			}
			break;
		}
	}
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
