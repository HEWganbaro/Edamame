#include "Player.h"
#include "input.h"

int frg = -1;
int tmp, cut;

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
	if (frg == -1) {
		if (Input_GetKeyTrigger('Q')) {
			frg = 0;
			tmp = Player->posX;
			Player->mappos.RightDown--;
		}
		if (Input_GetKeyTrigger('A')) {
			frg = 1;
			tmp = Player->posX;
			Player->mappos.LeftDown++;
		}
		if (Input_GetKeyTrigger('E')) {
			frg = 2;
			tmp = Player->posX;
			Player->mappos.LeftDown--;
		}
		if (Input_GetKeyTrigger('D')) {
			frg = 3;
			tmp = Player->posX;
			Player->mappos.RightDown++;
		}
	}
	else {
		switch (frg)
		{
		case -1:
			break;
		case 0:
			if (cut != PLAYER_SPEED) {
				Player->posX -= MAP_LENGTH / PLAYER_SPEED;
				Player->posY += MAP_LENGTH / PLAYER_SPEED;
				cut++;
			}
			else {
				frg = -1;
				cut = 0;
			}
			break;
		case 1:
			if (cut != PLAYER_SPEED) {
				Player->posX -= MAP_LENGTH / PLAYER_SPEED;
				Player->posY -= MAP_LENGTH / PLAYER_SPEED;
				cut++;
			}
			else {
				frg = -1;
				cut = 0;
			}
			break;
		case 2:
			if (cut != PLAYER_SPEED) {
				Player->posX += MAP_LENGTH / PLAYER_SPEED;
				Player->posY += MAP_LENGTH / PLAYER_SPEED;
				cut++;
			}
			else {
				frg = -1;
				cut = 0;
			}
			break;
		case 3:
			if (cut != PLAYER_SPEED) {
				Player->posX += MAP_LENGTH / PLAYER_SPEED;
				Player->posY -= MAP_LENGTH / PLAYER_SPEED;
				cut++;
			}
			else {
				frg = -1;
				cut = 0;
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
