#include "SnowBall.h"

Direction SnowBall_way;

int SnowBall_cut = 0;

void SnowBall_Initialize(GameObject * SnowBall)
{
	SnowBall->textuer = new Sprite("assets/snowBall.png", 1, 1);
	SnowBall->textuer->SetSize(100, 100);
	SnowBall->posY = 0.5f;
	SnowBall->mappos.Height = 0;
	SnowBall->mappos.LeftDown = 0;
	SnowBall->mappos.RightDown = 0;
}

void SnowBall_SetLocation(GameObject * SnowBall, GameObject * Location, int Height, int LeftDown, int RightDown)
{
	SnowBall->posX = Location[Height * 100 + LeftDown * 10 + RightDown].posX + MAP_LENGTH / 2.0f;
	SnowBall->posY = Location[Height * 100 + LeftDown * 10 + RightDown].posY;
	SnowBall->mappos.Height = Height;
	SnowBall->mappos.LeftDown = LeftDown;
	SnowBall->mappos.RightDown = RightDown;
}

MapPos SnowBall_GetMapPos(GameObject * SnowBall)
{
	return MapPos();
}

void SnowBall_Update(GameObject * SnowBall)
{
	
}

void SnowBall_Hit(GameObject * Player, GameObject * SnowBall)
{

	if (Player->mappos.LeftDown - 1 == SnowBall->mappos.LeftDown && 
		Player->mappos.RightDown == SnowBall->mappos.RightDown )
	{
		SnowBall_way = RIGHT_UP;
	}
	if (Player->mappos.LeftDown + 1 == SnowBall->mappos.LeftDown &&
		Player->mappos.RightDown == SnowBall->mappos.RightDown)
	{
		SnowBall_way = LEFT_DOWN;
	}
	if (Player->mappos.RightDown - 1 == SnowBall->mappos.RightDown &&
		Player->mappos.LeftDown == SnowBall->mappos.LeftDown)
	{
		SnowBall_way = LEFT_UP;
	}
	if (Player->mappos.RightDown + 1 == SnowBall->mappos.RightDown &&
		Player->mappos.LeftDown == SnowBall->mappos.LeftDown)
	{
		SnowBall_way = RIGHT_DOWN;
	}

	//if (Player->mappos.LeftDown == SnowBall->mappos.LeftDown && Player->mappos.RightDown == SnowBall->mappos.RightDown)
	//{
	//	switch (SnowBall_way)
	//	{
	//	case RIGHT_DOWN:
	//		if (SnowBall_cut != PLAYER_SPEED) {
	//			SnowBall->posX += MAP_LENGTH / PLAYER_SPEED;
	//			SnowBall->posY -= MAP_LENGTH / PLAYER_SPEED;
	//			SnowBall_cut++;
	//		}
	//		else {
	//			SnowBall->mappos.RightDown++;
	//			SnowBall_way = NULL_WAY;
	//			SnowBall_cut = 0;
	//		}
	//		break;

	//	case LEFT_DOWN:
	//		if (SnowBall_cut != PLAYER_SPEED) {
	//			SnowBall->posX -= MAP_LENGTH / PLAYER_SPEED;
	//			SnowBall->posY -= MAP_LENGTH / PLAYER_SPEED;
	//			SnowBall_cut++;
	//		}
	//		else {
	//			SnowBall->mappos.LeftDown++;
	//			SnowBall_way = NULL_WAY;
	//			SnowBall_cut = 0;
	//		}
	//		break;

	//	case LEFT_UP:
	//		if (SnowBall_cut != PLAYER_SPEED) {
	//			SnowBall->posX -= MAP_LENGTH / PLAYER_SPEED;
	//			SnowBall->posY += MAP_LENGTH / PLAYER_SPEED;
	//			SnowBall_cut++;
	//		}
	//		else {
	//			SnowBall->mappos.RightDown--;
	//			SnowBall_way = NULL_WAY;
	//			SnowBall_cut = 0;
	//		}
	//		break;

	//	case RIGHT_UP:
	//		if (SnowBall_cut != PLAYER_SPEED) {
	//			SnowBall->posX += MAP_LENGTH / PLAYER_SPEED;
	//			SnowBall->posY += MAP_LENGTH / PLAYER_SPEED;
	//			SnowBall_cut++;
	//		}
	//		else {
	//			SnowBall->mappos.LeftDown--;
	//			SnowBall_way = NULL_WAY;
	//			SnowBall_cut = 0;
	//		}
	//		break;
	//	}
	//}
}
