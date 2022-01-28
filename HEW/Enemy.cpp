#include "Enemy.h"
#include "animator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Enemy_cut;
int turn = PLAYER_TURN;

GameObject* Enemy_Initialize(GameObject * Enemy, EnemyType type)
{
	Enemy->texture = new Sprite("assets/penguin_tex.png", 16, 4);
	Enemy->texture->SetSize(175, 175);
	Enemy->mappos.Height = 0;
	Enemy->mappos.LeftDown = 0;
	Enemy->mappos.RightDown = 0;
	Enemy->IsEnemy = true;
	Enemy->animator.speed = 8.0f;
	Enemy->enemytype = type;
	Enemy->direction = NULL_WAY;
	Enemy->enemyeye = ENEMYEYE_OUT;

	return Enemy;
}

void Enemy_SetLocation(GameObject * Enemy, GameObject * Location, int Height, int LeftDown, int RightDown)
{
	Enemy->posX = Location[Height * 100 + LeftDown * 10 + RightDown].posX;
	Enemy->posY = Location[Height * 100 + LeftDown * 10 + RightDown].posY + MAP_LENGTH / 2.0f;
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
	Animator_Update(&Enemy->animator);

	int walk = 0;
	if (Enemy->animator.isActive == true)
		walk = 8;
	//アニメーション
	switch (Enemy->direction)
	{
	case NULL_WAY:
		Enemy->texture->SetPart(Enemy->animator.frame, 0);
		break;

	case RIGHT_DOWN:
		Enemy->texture->SetPart(Enemy->animator.frame + walk, 0);
		break;

	case LEFT_DOWN:
		Enemy->texture->SetPart(Enemy->animator.frame + walk, 1);
		break;

	case LEFT_UP:
		Enemy->texture->SetPart(Enemy->animator.frame + walk, 2);
		break;

	case RIGHT_UP:
		Enemy->texture->SetPart(Enemy->animator.frame + walk, 3);
		break;
	}
}

void Enemy_Hit(GameObject * Enemy)
{
	/*int r;
	srand((unsigned int)time(NULL));
	r = rand() % 3 + 1;*/

	//int flg = 0;

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

	//switch (Enemy->direction)
	//{
	//case RIGHT_DOWN:
	//	if (Enemy_cut != ENEMY_SPEED) {
	//		Enemy->posX += MAP_LENGTH / ENEMY_SPEED;
	//		Enemy->posY -= MAP_LENGTH / ENEMY_SPEED;
	//		Enemy_cut++;
	//	}
	//	else {
	//		Enemy->direction = NULL_WAY;
	//		Enemy->mappos.RightDown++;
	//		Enemy_cut = 0;
	//	}
	//	break;

	//case LEFT_DOWN:
	//	if (Enemy_cut != ENEMY_SPEED) {
	//		Enemy->posX -= MAP_LENGTH / ENEMY_SPEED;
	//		Enemy->posY -= MAP_LENGTH / ENEMY_SPEED;
	//		Enemy_cut++;
	//	}
	//	else {
	//		Enemy->direction = NULL_WAY;
	//		Enemy->mappos.LeftDown++;
	//		Enemy_cut = 0;
	//	}
	//	break;

	//case LEFT_UP:
	//	if (Enemy_cut != ENEMY_SPEED) {
	//		Enemy->posX -= MAP_LENGTH / ENEMY_SPEED;
	//		Enemy->posY += MAP_LENGTH / ENEMY_SPEED;
	//		Enemy_cut++;
	//	}
	//	else {
	//		Enemy->direction = NULL_WAY;
	//		Enemy->mappos.RightDown--;
	//		Enemy_cut = 0;
	//	}
	//	break;

	//case RIGHT_UP:
	//	if (Enemy_cut != ENEMY_SPEED) {
	//		Enemy->posX += MAP_LENGTH / ENEMY_SPEED;
	//		Enemy->posY += MAP_LENGTH / ENEMY_SPEED;
	//		Enemy_cut++;
	//	}
	//	else {
	//		Enemy->direction = NULL_WAY;
	//		Enemy->mappos.LeftDown--;
	//		Enemy_cut = 0;
	//	}
	//	break;
	//}

}

//敵の巡回
void Enemy_Move_Circle(GameObject * Enemy)
{
	if (Enemy->enemyeye == ENEMYEYE_OUT)
	{

	}
}

void Enemy_Move_Random(GameObject * Enemy)
{
	int ran = rand() % 4;
	if (ran == 0) {
		Enemy->direction = RIGHT_DOWN;
		Enemy->mappos.RightDown++;
		Enemy->animator.isActive = true;
		return;
	}
	if (ran == 1) {
		Enemy->direction = LEFT_DOWN;
		Enemy->mappos.LeftDown++;
		Enemy->animator.isActive = true;
		return;
	}
	if (ran == 2) {
		Enemy->direction = LEFT_UP;
		Enemy->mappos.RightDown--;
		Enemy->animator.isActive = true;
		return;
	}
	if (ran == 3) {
		Enemy->direction = RIGHT_UP;
		Enemy->mappos.LeftDown--;
		Enemy->animator.isActive = true;
		return;
	}
}

void Enemy_Player_Hit(GameObject * Enemy, GameObject * Player, GameObject * Player2)
{
	if (Player->Goalfrg == false) {
		if ((Player->mappos.LeftDown - 1 == Enemy->mappos.LeftDown && Player->mappos.RightDown == Enemy->mappos.RightDown) ||
			(Player->mappos.LeftDown + 1 == Enemy->mappos.LeftDown && Player->mappos.RightDown == Enemy->mappos.RightDown) ||
			(Player->mappos.LeftDown == Enemy->mappos.LeftDown && Player->mappos.RightDown + 1 == Enemy->mappos.RightDown) ||
			(Player->mappos.LeftDown == Enemy->mappos.LeftDown && Player->mappos.RightDown - 1 == Enemy->mappos.RightDown))
			turn = GAMEOVER;
	}
	if (Player2->Goalfrg == false) {
		if ((Player2->mappos.LeftDown - 1 == Enemy->mappos.LeftDown && Player2->mappos.RightDown == Enemy->mappos.RightDown) ||
			(Player2->mappos.LeftDown + 1 == Enemy->mappos.LeftDown && Player2->mappos.RightDown == Enemy->mappos.RightDown) ||
			(Player2->mappos.LeftDown == Enemy->mappos.LeftDown && Player2->mappos.RightDown + 1 == Enemy->mappos.RightDown) ||
			(Player2->mappos.LeftDown == Enemy->mappos.LeftDown && Player2->mappos.RightDown - 1 == Enemy->mappos.RightDown))
			turn = GAMEOVER;
	}
}

//敵の雪玉への接近
void Enemy_Move_Chase(GameObject * Enemy, GameObject * Player, GameObject* Player2)
{
	//プレイヤーを~マス圏内で索敵する
	const bool LeftDown_Player = SCANNING_RANGE >= abs(Enemy->mappos.LeftDown - Player->mappos.LeftDown);
	const bool LeftDown_Player2 = SCANNING_RANGE >= abs(Enemy->mappos.LeftDown - Player2->mappos.LeftDown);
	const bool RightDown_Player = SCANNING_RANGE >= abs(Enemy->mappos.RightDown - Player->mappos.RightDown);
	const bool RightDown_Player2 = SCANNING_RANGE >= abs(Enemy->mappos.RightDown - Player2->mappos.RightDown);
	bool Player_EnemyIn = LeftDown_Player && RightDown_Player;
	bool Player_EnemyIn2 = LeftDown_Player2 && RightDown_Player2;
	if (Player_EnemyIn == true && Player_EnemyIn2 == true)	//距離が近いほうを優先
		if ((abs(Enemy->mappos.LeftDown - Player->mappos.LeftDown) + abs(Enemy->mappos.RightDown - Player->mappos.RightDown))
			< (abs(Enemy->mappos.LeftDown - Player2->mappos.LeftDown) + abs(Enemy->mappos.RightDown - Player2->mappos.RightDown)))
			Player_EnemyIn2 = false;
		else
			Player_EnemyIn = false;

	if (Player_EnemyIn)
		Enemy->enemyeye = ENEMYEYE_IN_1;
	else if (Player_EnemyIn2)
		Enemy->enemyeye = ENEMYEYE_IN_2;
	else
		Enemy->enemyeye = ENEMYEYE_OUT;
	//ゴールしてないほうを追いかける
	if (Player->Goalfrg == true)
		Enemy->enemyeye = ENEMYEYE_IN_2;
	if (Player2->Goalfrg == true)
		Enemy->enemyeye = ENEMYEYE_IN_1;

	if (Enemy->enemyeye == ENEMYEYE_IN_1) {
		//距離を保存
		const int Player_LeftDown = -(Enemy->mappos.LeftDown - Player->mappos.LeftDown);
		const int Player_RightDown = -(Enemy->mappos.RightDown - Player->mappos.RightDown);

		//同じであればその方向のどちらかの2方向を選ぶ
		if (abs(Player_LeftDown) == abs(Player_RightDown)) {
			if (Player_LeftDown < 0 && Player_RightDown < 0) {
				if (rand() % 2) {
					Enemy->direction = RIGHT_UP;
					Enemy->mappos.LeftDown--;
				}
				else {
					Enemy->direction = LEFT_UP;
					Enemy->mappos.RightDown--;
				}
			}
			else if (Player_LeftDown > 0 && Player_RightDown > 0) {
				if (rand() % 2) {
					Enemy->direction = RIGHT_DOWN;
					Enemy->mappos.RightDown++;
				}
				else {
					Enemy->direction = LEFT_DOWN;
					Enemy->mappos.LeftDown++;
				}
			}
			else if (Player_LeftDown > 0 && Player_RightDown < 0) {
				if (rand() % 2) {
					Enemy->direction = LEFT_UP;
					Enemy->mappos.RightDown--;
				}
				else {
					Enemy->direction = LEFT_DOWN;
					Enemy->mappos.LeftDown++;
				}
			}
			else if (Player_LeftDown < 0 && Player_RightDown > 0) {
				if (rand() % 2) {
					Enemy->direction = RIGHT_UP;
					Enemy->mappos.LeftDown--;
				}
				else {
					Enemy->direction = RIGHT_DOWN;
					Enemy->mappos.RightDown++;
				}
			}
		}//プレイヤーがいる方向に近づく
		else if (Player_LeftDown > 1) {
			Enemy->direction = LEFT_DOWN;
			Enemy->mappos.LeftDown++;
		}
		else if (Player_RightDown > 1) {
			Enemy->direction = RIGHT_DOWN;
			Enemy->mappos.RightDown++;
		}
		else if (Player_LeftDown < -1) {
			Enemy->direction = RIGHT_UP;
			Enemy->mappos.LeftDown--;
		}
		else if (Player_RightDown < -1) {
			Enemy->direction = LEFT_UP;
			Enemy->mappos.RightDown--;
		}
		else {
			//攻撃範囲なら動かない
			Enemy->direction = NO_ACTION;
		}
		Enemy->animator.isActive = true;
	}
	else if (Enemy->enemyeye == ENEMYEYE_IN_2) {
		const int Player_LeftDown = -(Enemy->mappos.LeftDown - Player2->mappos.LeftDown);
		const int Player_RightDown = -(Enemy->mappos.RightDown - Player2->mappos.RightDown);

		if (abs(Player_LeftDown) == abs(Player_RightDown)) {
			if (Player_LeftDown < 0 && Player_RightDown < 0) {
				if (rand() % 2) {
					Enemy->direction = RIGHT_UP;
					Enemy->mappos.LeftDown--;
				}
				else {
					Enemy->direction = LEFT_UP;
					Enemy->mappos.RightDown--;
				}
			}
			else if (Player_LeftDown > 0 && Player_RightDown > 0) {
				if (rand() % 2) {
					Enemy->direction = RIGHT_DOWN;
					Enemy->mappos.RightDown++;
				}
				else {
					Enemy->direction = LEFT_DOWN;
					Enemy->mappos.LeftDown++;
				}
			}
			else if (Player_LeftDown > 0 && Player_RightDown < 0) {
				if (rand() % 2) {
					Enemy->direction = LEFT_UP;
					Enemy->mappos.RightDown--;
				}
				else {
					Enemy->direction = LEFT_DOWN;
					Enemy->mappos.LeftDown++;
				}
			}
			else if (Player_LeftDown < 0 && Player_RightDown > 0) {
				if (rand() % 2) {
					Enemy->direction = RIGHT_UP;
					Enemy->mappos.LeftDown--;
				}
				else {
					Enemy->direction = RIGHT_DOWN;
					Enemy->mappos.RightDown++;
				}
			}
		}//プレイヤーがいる方向に近づく
		else if (Player_LeftDown > 1) {
			Enemy->direction = LEFT_DOWN;
			Enemy->mappos.LeftDown++;
		}
		else if (Player_RightDown > 1) {
			Enemy->direction = RIGHT_DOWN;
			Enemy->mappos.RightDown++;
		}
		else if (Player_LeftDown < -1) {
			Enemy->direction = RIGHT_UP;
			Enemy->mappos.LeftDown--;
		}
		else if (Player_RightDown < -1) {
			Enemy->direction = LEFT_UP;
			Enemy->mappos.RightDown--;
		}
		else {
			//攻撃範囲なら動かない
			Enemy->direction = NO_ACTION;
		}
		Enemy->animator.isActive = true;
	}
	else {
		Enemy_Move_Random(Enemy);
	}
}

//敵のスタン
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
		Player1_cut = 0;
	}
	if (Player1_cut == 5)
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
		Player1_cut = 0;
	}
	if (Player1_cut == 5)
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
		Player2_cut = 0;
	}
	if (Player2_cut == 5)
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
		Player2_cut = 0;
	}
	if (Player2_cut == 5)
	{
		Enemy->enemymove = ENEMY_MOVE;
	}
}