#include "SnowBall.h"

Direction SnowBall_way;
Direction SnowBall2_way;

int SnowBall_cut = 0;
int SnowBall2_cut = 0;

void SnowBall_Initialize(GameObject * SnowBall, GameObject * SnowBall2)
{
	// 雪玉1
	SnowBall->textuer = new Sprite("assets/snowBall.png", 2, 1);
	SnowBall->textuer->SetSize(100, 100);
	SnowBall->posY = 0.5f;
	SnowBall->mappos.Height = 0;
	SnowBall->mappos.LeftDown = 0;
	SnowBall->mappos.RightDown = 0;
	// 雪玉2
	SnowBall2->textuer = new Sprite("assets/snowBall.png", 2, 1);
	SnowBall2->textuer->SetSize(100, 100);
	SnowBall2->posY = 0.5f;
	SnowBall2->mappos.Height = 0;
	SnowBall2->mappos.LeftDown = 0;
	SnowBall2->mappos.RightDown = 0;
}

void SnowBall_SetLocation(GameObject * SnowBall, GameObject * Location, int Height, int LeftDown, int RightDown
						, GameObject * SnowBall2, GameObject * Location2, int Height2, int LeftDown2, int RightDown2)
{
	// 雪玉1
	SnowBall->posX = Location[Height * 100 + LeftDown * 10 + RightDown].posX + MAP_LENGTH / 2.0f;
	SnowBall->posY = Location[Height * 100 + LeftDown * 10 + RightDown].posY;
	SnowBall->mappos.Height = Height;
	SnowBall->mappos.LeftDown = LeftDown;
	SnowBall->mappos.RightDown = RightDown;
	// 雪玉2
	SnowBall2->posX = Location2[Height2 * 100 + LeftDown2 * 10 + RightDown2].posX + MAP_LENGTH / 2.0f;
	SnowBall2->posY = Location2[Height2 * 100 + LeftDown2 * 10 + RightDown2].posY;
	SnowBall2->mappos.Height = Height2;
	SnowBall2->mappos.LeftDown = LeftDown2;
	SnowBall2->mappos.RightDown = RightDown2;
}

MapPos SnowBall_GetMapPos(GameObject * SnowBall, GameObject * SnowBall2)
{
	return MapPos();
}
/*地面の変更をいじるとしたらここ(テクスチャだけの変更じゃなくて、性質ごと変化させる。)*/
void SnowBall_Update(GameObject * SnowBall, GameObject* Map, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE]
				   , GameObject * SnowBall2, GameObject* Map2, int MapChip2[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE])
{
	// 雪玉1
	MapMove_Update(SnowBall, Map);
	if (Map_GetPlayerTile(SnowBall, Map) == SNOW_GROUND) {
		Map[SnowBall->mappos.Height * 100 + SnowBall->mappos.LeftDown * 10 + SnowBall->mappos.RightDown].textuer->SetPart(1, 0);
		SnowBall->textuer->SetPart(0, 0);
	}
	else if (Map_GetPlayerTile(SnowBall, Map) == SOIL_GROUND) {
		SnowBall->textuer->SetPart(1, 0);
	}
	// 雪玉2
	MapMove_Update(SnowBall2, Map2);
	if (Map_GetPlayerTile(SnowBall2, Map2) == SNOW_GROUND) {
		Map2[SnowBall2->mappos.Height * 100 + SnowBall2->mappos.LeftDown * 10 + SnowBall2->mappos.RightDown].textuer->SetPart(1, 0);
		SnowBall2->textuer->SetPart(0, 0);
	}
	else if (Map_GetPlayerTile(SnowBall2, Map) == SOIL_GROUND) {
		SnowBall2->textuer->SetPart(1, 0);
	}

}	

void SnowBall_Hit(GameObject * Player, GameObject * SnowBall)
{
	//雪玉1
	if (Player->mappos.LeftDown - 1 == SnowBall->mappos.LeftDown &&
		Player->mappos.RightDown == SnowBall->mappos.RightDown)
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

	if (Player->mappos.LeftDown == SnowBall->mappos.LeftDown && Player->mappos.RightDown == SnowBall->mappos.RightDown) {
		switch (SnowBall_way)
		{
		case RIGHT_UP:
			SnowBall->direction = RIGHT_UP;
			SnowBall->mappos.LeftDown--;
			break;

		case LEFT_DOWN:
			SnowBall->direction = LEFT_DOWN;
			SnowBall->mappos.LeftDown++;
			break;

		case LEFT_UP:
			SnowBall->direction = LEFT_UP;
			SnowBall->mappos.RightDown--;
			break;

		case RIGHT_DOWN:
			SnowBall->direction = RIGHT_DOWN;
			SnowBall->mappos.RightDown++;
			break;
		}
	}
	//	//雪玉2
	//	if (Player2->mappos.LeftDown - 1 == SnowBall2->mappos.LeftDown &&
	//		Player2->mappos.RightDown == SnowBall2->mappos.RightDown)
	//	{
	//		SnowBall2_way = RIGHT_UP;
	//	}
	//	if (Player2->mappos.LeftDown + 1 == SnowBall2->mappos.LeftDown &&
	//		Player2->mappos.RightDown == SnowBall2->mappos.RightDown)
	//	{
	//		SnowBall2_way = LEFT_DOWN;
	//	}
	//	if (Player2->mappos.RightDown - 1 == SnowBall2->mappos.RightDown &&
	//		Player2->mappos.LeftDown == SnowBall2->mappos.LeftDown)
	//	{
	//		SnowBall2_way = LEFT_UP;
	//	}
	//	if (Player2->mappos.RightDown + 1 == SnowBall2->mappos.RightDown &&
	//		Player2->mappos.LeftDown == SnowBall2->mappos.LeftDown)
	//	{
	//		SnowBall2_way = RIGHT_DOWN;
	//	}
	//	if (Player2->mappos.LeftDown == SnowBall2->mappos.LeftDown && Player2->mappos.RightDown == SnowBall2->mappos.RightDown) {
	//		switch (SnowBall2_way)
	//		{
	//		case RIGHT_UP:
	//			SnowBall2->direction = RIGHT_UP;
	//			SnowBall2->mappos.LeftDown--;
	//			break;

	//		case LEFT_DOWN:
	//			SnowBall2->direction = LEFT_DOWN;
	//			SnowBall2->mappos.LeftDown++;
	//			break;

	//		case LEFT_UP:
	//			SnowBall2->direction = LEFT_UP;
	//			SnowBall2->mappos.RightDown--;
	//			break;

	//		case RIGHT_DOWN:
	//			SnowBall2->direction = RIGHT_DOWN;
	//			SnowBall2->mappos.RightDown++;
	//			break;
	//		}
	//	}
	//}
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
