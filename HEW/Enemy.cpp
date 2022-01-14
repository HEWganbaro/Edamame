#include "Enemy.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Enemy_cut;
int Enemy_flg = 0;
int turn = PLAYER_TURN;

void Enemy_Initialize(GameObject * Enemy)
{
	Enemy->texture = new Sprite("assets/player.png", 1, 1);
	Enemy->texture->SetSize(80, 80);
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

void Enemy_Hit(GameObject * Enemy)
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
void Enemy_Move_Circle(GameObject * Enemy)
{

	if (Enemy->enemyeye == ENEMYEYE_OUT && Enemy_flg == 1)
	{
		if ((Enemy->tmp.LeftDown == Enemy->mappos.LeftDown && Enemy->tmp.RightDown == Enemy->mappos.RightDown) ||
			(Enemy->tmp.LeftDown == Enemy->mappos.LeftDown && Enemy->tmp.RightDown + 1 == Enemy->mappos.RightDown))
		{
			Enemy->direction = RIGHT_DOWN;
			Enemy_flg = 0;
			turn = PLAYER_TURN;
			return;
		}

		if ((Enemy->tmp.LeftDown == Enemy->mappos.LeftDown && Enemy->tmp.RightDown + 2 == Enemy->mappos.RightDown) ||
			(Enemy->tmp.LeftDown + 1 == Enemy->mappos.LeftDown && Enemy->tmp.RightDown + 2 == Enemy->mappos.RightDown))
		{
			Enemy->direction = LEFT_DOWN;
			Enemy_flg = 0;
			turn = PLAYER_TURN;
			return;
		}
		if ((Enemy->tmp.LeftDown + 2 == Enemy->mappos.LeftDown && Enemy->tmp.RightDown + 2 == Enemy->mappos.RightDown) ||
			(Enemy->tmp.LeftDown + 2 == Enemy->mappos.LeftDown && Enemy->tmp.RightDown + 1 == Enemy->mappos.RightDown))
		{
			Enemy->direction = LEFT_UP;
			Enemy_flg = 0;
			turn = PLAYER_TURN;
			return;
		}
		if ((Enemy->tmp.LeftDown + 2 == Enemy->mappos.LeftDown && Enemy->tmp.RightDown == Enemy->mappos.RightDown) ||
			(Enemy->tmp.LeftDown + 1 == Enemy->mappos.LeftDown && Enemy->tmp.RightDown == Enemy->mappos.RightDown))
		{
			Enemy->direction = RIGHT_UP;
			Enemy_flg = 0;
			turn = PLAYER_TURN;
			return;
		}
	}
}

//“G‚Ìá‹Ê‚Ö‚ÌÚ‹ß
void Enemy_Move_Chase(GameObject * Enemy, GameObject * Player, GameObject* Player2)
{
	//Player
	if (Player->mappos.LeftDown - 1 == Enemy->mappos.LeftDown &&
		Player->mappos.RightDown == Enemy->mappos.RightDown)
	{
		Enemy->enemyeye = ENEMYEYE_IN;
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = LEFT_DOWN;
		}
	}
	if (Player->mappos.LeftDown + 1 == Enemy->mappos.LeftDown &&
		Player->mappos.RightDown == Enemy->mappos.RightDown)
	{
		Enemy->enemyeye = ENEMYEYE_IN;
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = RIGHT_UP;
		}
	}

	if (Player->mappos.RightDown - 1 == Enemy->mappos.RightDown &&
		Player->mappos.LeftDown == Enemy->mappos.LeftDown)
	{
		Enemy->enemyeye = ENEMYEYE_IN;
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = RIGHT_DOWN;;
		}
	}

	if (Player->mappos.RightDown + 1 == Enemy->mappos.RightDown &&
		Player->mappos.LeftDown == Enemy->mappos.LeftDown)
	{
		Enemy->enemyeye = ENEMYEYE_IN;
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = LEFT_UP;
		}
	}

	//Player2
	if (Player2->mappos.LeftDown - 1 == Enemy->mappos.LeftDown &&
		Player2->mappos.RightDown == Enemy->mappos.RightDown)
	{
		Enemy->enemyeye = ENEMYEYE_IN;
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = LEFT_DOWN;
		}
	}
	if (Player2->mappos.LeftDown + 1 == Enemy->mappos.LeftDown &&
		Player2->mappos.RightDown == Enemy->mappos.RightDown)
	{
		Enemy->enemyeye = ENEMYEYE_IN;
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = RIGHT_UP;
		}
	}

	if (Player2->mappos.RightDown - 1 == Enemy->mappos.RightDown &&
		Player2->mappos.LeftDown == Enemy->mappos.LeftDown)
	{
		Enemy->enemyeye = ENEMYEYE_IN;
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = RIGHT_DOWN;
		}
	}

	if (Player2->mappos.RightDown + 1 == Enemy->mappos.RightDown &&
		Player2->mappos.LeftDown == Enemy->mappos.LeftDown)
	{
		Enemy->enemyeye = ENEMYEYE_IN;
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = LEFT_UP;
		}
	}
	turn = PLAYER_TURN;
}


//“G‚ÌƒXƒ^ƒ“
void Enemy_Stun(GameObject * Enemy, GameObject * Player, GameObject * Player2, GameObject* Map, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE])
{
	//Player
	if (Map_GetPlayerTile(Player, Map) &&
		Player->mappos.LeftDown >= Enemy->mappos.LeftDown - 1 && Player->mappos.RightDown == Enemy->mappos.RightDown &&
		Player->mappos.Height > Enemy->mappos.Height)
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

	if (Map_GetPlayerTile(Player, Map) &&
		Player->mappos.RightDown >= Enemy->mappos.RightDown - 1 && Player->mappos.LeftDown == Enemy->mappos.LeftDown &&
		Player->mappos.Height > Enemy->mappos.Height)
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

	//Player2
	if (Map_GetPlayerTile(Player2, Map) &&
		Player2->mappos.LeftDown >= Enemy->mappos.LeftDown - 1 && Player2->mappos.RightDown == Enemy->mappos.RightDown &&
		Player2->mappos.Height > Enemy->mappos.Height)
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

	if (Map_GetPlayerTile(Player2, Map) &&
		Player2->mappos.RightDown >= Enemy->mappos.RightDown - 1 && Player2->mappos.LeftDown == Enemy->mappos.LeftDown &&
		Player2->mappos.Height > Enemy->mappos.Height)
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