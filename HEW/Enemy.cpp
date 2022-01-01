#include "Enemy.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Enemy_cut;

void Enemy_Initialize(GameObject * Enemy)
{
	Enemy->textuer = new Sprite("assets/player.png", 1, 1);
	Enemy->textuer->SetSize(80, 80);
	Enemy->posY = 0.5f;
	Enemy->mappos.Height = 0;
	Enemy->mappos.LeftDown = 0;
	Enemy->mappos.RightDown = 0;
	Enemy->direction = NULL_WAY;
	Enemy->enemyeye = ENEMYEYE_OUT;
}

void Enemy_SetLocation(GameObject * Enemy, GameObject * Location, int Height, int LeftDown, int RightDown)
{
	Enemy->posX = Location[Height * 100 + LeftDown * 10 + RightDown].posX + MAP_LENGTH / 2.0f;
	Enemy->posY = Location[Height * 100 + LeftDown * 10 + RightDown].posY;
	Enemy->mappos.Height = Height;
	Enemy->mappos.LeftDown = LeftDown;
	Enemy->mappos.RightDown = RightDown;
	Enemy->tmp = Enemy->mappos;
}

MapPos Enemy_GetMapPos(GameObject * Enemy)
{
	MapPos mappos;
	mappos.Height = Enemy->mappos.Height;
	return mappos;
}

void Enemy_Update(GameObject * Enemy)
{
}

void Enemy_Hit(GameObject * Enemy, GameObject * Player)
{
	/*int r;
	srand((unsigned int)time(NULL));
	r = rand() % 3 + 1;*/

	int flg = 0;

	/*if (Player->mappos.RightDown && Enemy_way == NULL_WAY && flg == 0) {
		Enemy_way = RIGHT_DOWN;
		Enemy->mappos.RightDown++;
		flg = 1;
	}

	if (Player->mappos.LeftDown && Enemy_way == NULL_WAY && flg == 0) {
		Enemy_way = LEFT_DOWN;
		Enemy->mappos.LeftDown++;
		flg = 1;
	}

	if (flg == 1)
	{
		flg = 0;
	}*/
	/*if (Enemy_way == NULL_WAY)
	{
		if (Player->direction == LEFT_UP) {
			Enemy_way = LEFT_UP;
			Enemy->mappos.RightDown--;
		}
		if (Player->direction == LEFT_DOWN) {
			Enemy_way = LEFT_DOWN;
			Enemy->mappos.LeftDown++;
		}
		if (Player->direction == RIGHT_UP) {
			Enemy_way = RIGHT_UP;
			Enemy->mappos.LeftDown--;
		}
		if (Player->direction == RIGHT_DOWN) {
			Enemy_way = RIGHT_DOWN;
			Enemy->mappos.RightDown++;
		}
	}*/

	switch (Enemy->direction)
	{
	case RIGHT_DOWN:
		if (Enemy_cut != ENEMY_SPEED) {
			Enemy->posX += MAP_LENGTH / ENEMY_SPEED;
			Enemy->posY -= MAP_LENGTH / ENEMY_SPEED;
			Enemy_cut++;
		}
		else {
			Enemy->direction = NULL_WAY;
			Enemy->mappos.RightDown++;
			Enemy_cut = 0;
		}
		break;

	case LEFT_DOWN:
		if (Enemy_cut != ENEMY_SPEED) {
			Enemy->posX -= MAP_LENGTH / ENEMY_SPEED;
			Enemy->posY -= MAP_LENGTH / ENEMY_SPEED;
			Enemy_cut++;
		}
		else {
			Enemy->direction = NULL_WAY;
			Enemy->mappos.LeftDown++;
			Enemy_cut = 0;
		}
		break;

	case LEFT_UP:
		if (Enemy_cut != ENEMY_SPEED) {
			Enemy->posX -= MAP_LENGTH / ENEMY_SPEED;
			Enemy->posY += MAP_LENGTH / ENEMY_SPEED;
			Enemy_cut++;
		}
		else {
			Enemy->direction = NULL_WAY;
			Enemy->mappos.RightDown--;
			Enemy_cut = 0;
		}
		break;

	case RIGHT_UP:
		if (Enemy_cut != ENEMY_SPEED) {
			Enemy->posX += MAP_LENGTH / ENEMY_SPEED;
			Enemy->posY += MAP_LENGTH / ENEMY_SPEED;
			Enemy_cut++;
		}
		else {
			Enemy->direction = NULL_WAY;
			Enemy->mappos.LeftDown--;
			Enemy_cut = 0;
		}
		break;
	}

}

//“G‚Ì„‰ñ
void Enemy_Move_Circle(GameObject * Enemy, GameObject* Player, GameObject* SnowBall)
{

	if (Player->direction != NULL_WAY)
	{

		if (Enemy->enemyeye == ENEMYEYE_OUT)
		{
			if ((Enemy->tmp.LeftDown == Enemy->mappos.LeftDown && Enemy->tmp.RightDown == Enemy->mappos.RightDown) ||
				(Enemy->tmp.LeftDown == Enemy->mappos.LeftDown && Enemy->tmp.RightDown + 1 == Enemy->mappos.RightDown))
			{
				Enemy->direction = RIGHT_DOWN;
				return;
			}

			if ((Enemy->tmp.LeftDown == Enemy->mappos.LeftDown && Enemy->tmp.RightDown + 2 == Enemy->mappos.RightDown) ||
				(Enemy->tmp.LeftDown + 1 == Enemy->mappos.LeftDown && Enemy->tmp.RightDown + 2 == Enemy->mappos.RightDown))
			{
				Enemy->direction = LEFT_DOWN;
				return;
			}
			if ((Enemy->tmp.LeftDown + 2 == Enemy->mappos.LeftDown && Enemy->tmp.RightDown + 2 == Enemy->mappos.RightDown) ||
				(Enemy->tmp.LeftDown + 2 == Enemy->mappos.LeftDown && Enemy->tmp.RightDown + 1 == Enemy->mappos.RightDown))
			{
				Enemy->direction = LEFT_UP;
				return;
			}
			if ((Enemy->tmp.LeftDown + 2 == Enemy->mappos.LeftDown && Enemy->tmp.RightDown == Enemy->mappos.RightDown) ||
				(Enemy->tmp.LeftDown + 1 == Enemy->mappos.LeftDown && Enemy->tmp.RightDown == Enemy->mappos.RightDown))
			{
				Enemy->direction = RIGHT_UP;
				return;
			}
		}
	}

}

//“G‚Ìá‹Ê‚Ö‚ÌÚ‹ß
void Enemy_Move_Chase(GameObject * Enemy, GameObject * SnowBall)
{

	if (SnowBall->mappos.LeftDown - 1 == Enemy->mappos.LeftDown &&
		SnowBall->mappos.RightDown == Enemy->mappos.RightDown)
	{
		Enemy->enemyeye = ENEMYEYE_IN;
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = LEFT_DOWN;
		}
	}
	if (SnowBall->mappos.LeftDown + 1 == Enemy->mappos.LeftDown &&
		SnowBall->mappos.RightDown == Enemy->mappos.RightDown)
	{
		Enemy->enemyeye = ENEMYEYE_IN;
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = RIGHT_UP;
		}
	}

	if (SnowBall->mappos.RightDown - 1 == Enemy->mappos.RightDown &&
		SnowBall->mappos.LeftDown == Enemy->mappos.LeftDown)
	{
		Enemy->enemyeye = ENEMYEYE_IN;
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = RIGHT_DOWN;;
		}
	}

	if (SnowBall->mappos.RightDown + 1 == Enemy->mappos.RightDown &&
		SnowBall->mappos.LeftDown == Enemy->mappos.LeftDown)
	{
		Enemy->enemyeye = ENEMYEYE_IN;
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = LEFT_UP;
		}
	}

}


//“G‚ÌƒXƒ^ƒ“
void Enemy_Stun(GameObject * Enemy, GameObject * SnowBall, GameObject* Map, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE])
{
	if (Map_GetPlayerTile(SnowBall, Map) &&
		SnowBall->mappos.LeftDown >= Enemy->mappos.LeftDown - 1 && SnowBall->mappos.RightDown == Enemy->mappos.RightDown &&
		SnowBall->mappos.Height > Enemy->mappos.Height)
	{
		Enemy->direction = LEFT_DOWN;
		Enemy->enemyeye = ENEMYEYE_OUT;
		Enemy->enemymove = ENEMY_STOP;
		Player_cut = 0;
	}
	if (Player_cut == 5)
	{
		Enemy->enemymove = ENEMY_MOVE;
	}

	if (Map_GetPlayerTile(SnowBall, Map) &&
		SnowBall->mappos.RightDown >= Enemy->mappos.RightDown - 1 && SnowBall->mappos.LeftDown == Enemy->mappos.LeftDown &&
		SnowBall->mappos.Height > Enemy->mappos.Height)
	{
		Enemy->direction = RIGHT_DOWN;
		Enemy->enemyeye = ENEMYEYE_OUT;
		Enemy->enemymove = ENEMY_STOP;
		Player_cut = 0;
	}
	if (Player_cut == 5)
	{
		Enemy->enemymove = ENEMY_MOVE;
	}

}