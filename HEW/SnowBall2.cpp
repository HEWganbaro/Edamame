#include "SnowBall2.h"

Direction SnowBall2_way;

int SnowBall2_cut = 0;

void SnowBall2_Initialize(GameObject * SnowBall2)
{
	SnowBall2->textuer = new Sprite("assets/snowBall.png", 2, 1);
	SnowBall2->textuer->SetSize(100, 100);
	SnowBall2->posY = 0.5f;
	SnowBall2->mappos.Height = 0;
	SnowBall2->mappos.LeftDown = 0;
	SnowBall2->mappos.RightDown = 0;
}

void SnowBall2_SetLocation(GameObject * SnowBall2, GameObject * Location, int Height, int LeftDown, int RightDown)
{
	SnowBall2->posX = Location[Height * 100 + LeftDown * 10 + RightDown].posX + MAP_LENGTH / 2.0f;
	SnowBall2->posY = Location[Height * 100 + LeftDown * 10 + RightDown].posY;
	SnowBall2->mappos.Height = Height;
	SnowBall2->mappos.LeftDown = LeftDown;
	SnowBall2->mappos.RightDown = RightDown;
}

MapPos SnowBall2_GetMapPos(GameObject * SnowBall2)
{
	return MapPos();
}

void SnowBall2_Update(GameObject * SnowBall2, GameObject* Map, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE])
{
	MapMove_Update(SnowBall2, Map);
	if (Map_GetPlayerTile(SnowBall2, Map) == SNOW_GROUND) {
		Map[SnowBall2->mappos.Height * 100 + SnowBall2->mappos.LeftDown * 10 + SnowBall2->mappos.RightDown].textuer->SetPart(1, 0);
		SnowBall2->textuer->SetPart(0, 0);
	}
	else if (Map_GetPlayerTile(SnowBall2, Map) == SOIL_GROUND) {
		SnowBall2->textuer->SetPart(1, 0);
	}
}	

void SnowBall2_Hit(GameObject * Player, GameObject * SnowBall2)
{

	if (Player->mappos.LeftDown - 1 == SnowBall2->mappos.LeftDown && 
		Player->mappos.RightDown == SnowBall2->mappos.RightDown )
	{
		SnowBall2_way = RIGHT_UP;
	}
	if (Player->mappos.LeftDown + 1 == SnowBall2->mappos.LeftDown &&
		Player->mappos.RightDown == SnowBall2->mappos.RightDown)
	{
		SnowBall2_way = LEFT_DOWN;
	}
	if (Player->mappos.RightDown - 1 == SnowBall2->mappos.RightDown &&
		Player->mappos.LeftDown == SnowBall2->mappos.LeftDown)
	{
		SnowBall2_way = LEFT_UP;
	}
	if (Player->mappos.RightDown + 1 == SnowBall2->mappos.RightDown &&
		Player->mappos.LeftDown == SnowBall2->mappos.LeftDown)
	{
		SnowBall2_way = RIGHT_DOWN;
	}

	if (Player->mappos.LeftDown == SnowBall2->mappos.LeftDown && Player->mappos.RightDown == SnowBall2->mappos.RightDown) {
		switch (SnowBall2_way)
		{
		case RIGHT_UP:
			SnowBall2->direction = RIGHT_UP;
			SnowBall2->mappos.LeftDown--;
			break;

		case LEFT_DOWN:
			SnowBall2->direction = LEFT_DOWN;
			SnowBall2->mappos.LeftDown++;
			break;

		case LEFT_UP:
			SnowBall2->direction = LEFT_UP;
			SnowBall2->mappos.RightDown--;
			break;

		case RIGHT_DOWN:
			SnowBall2->direction = RIGHT_DOWN;
			SnowBall2->mappos.RightDown++;
			break;
		}
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
