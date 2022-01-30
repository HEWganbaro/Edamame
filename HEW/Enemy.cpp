#include "Enemy.h"
#include "animator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Enemy_cut;
int turn = PLAYER_TURN;

GameObject* Enemy_Initialize(GameObject * Enemy, EnemyType type)
{
	Enemy->texture = new Sprite("assets/penguin_tex.png", 48, 4);
	Enemy->texture->SetSize(175, 175);
	Enemy->mappos.Height = 0;
	Enemy->mappos.LeftDown = 0;
	Enemy->mappos.RightDown = 0;
	Enemy->IsEnemy = true;
	Enemy->animator.speed = 8.0f;
	Enemy->enemytype = type;
	Enemy->direction = NULL_WAY;
	Enemy->enemyeye = ENEMYEYE_OUT;
	Enemy->EnemyAttak = false;
	Enemy->Enemycount = 0;
	Enemy->IsStun = Nothing;

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

void Enemy_Update(GameObject * Enemy, GameObject* Player)
{
	Animator_Update(&Enemy->animator);

	int walk = 0, stun = 0, following = 0, gameover = 0;
	if (Enemy->animator.isActive == true)
		walk = 8;//歩くアニメーション
	if (Enemy->IsStun == Stun)
		stun = 16;//スタン
	if (Enemy->IsStun == Stun_) {
		stun++;
		if (stun == 18)
			stun = 17;
	}
	//追いかけるアニメーション
	if (Enemy->enemyeye == ENEMYEYE_IN_1 || Enemy->enemyeye == ENEMYEYE_IN_2) {
		following = 24 ;
		walk = 0;
	}
	//ぺちゃんこにするアニメーション
	if (turn == PENGUIN_ATTACK || turn == PENGUIN2 || turn == GAMEOVER) {
		gameover = 32;
		if (turn == PENGUIN2 || turn == GAMEOVER)
			gameover = 47;
		switch (Enemy->direction)
		{ 
		case NULL_WAY:
			Enemy->texture->SetPart(Enemy->animator.frame + gameover, 0);
			break;
		case RIGHT_DOWN:
			Enemy->texture->SetPart(Enemy->animator.frame + gameover, 0);
			break;
		case LEFT_DOWN:
			Enemy->texture->SetPart(Enemy->animator.frame + gameover, 1);
			break;
		case LEFT_UP:
			Enemy->texture->SetPart(Enemy->animator.frame + gameover, 2);
			break;
		case RIGHT_UP:
			Enemy->texture->SetPart(Enemy->animator.frame + gameover, 3);
			break;
		case NO_ACTION:
			Enemy->texture->SetPart(gameover, 0);
			break;
		}
	}
	//アニメーション
 	else if (Enemy->IsStun == Stun || Enemy->IsStun == Stun_) {
		Enemy->texture->SetPart(stun, 0);
	}
	else {
		switch (Enemy->direction)
		{
		case NULL_WAY:
			Enemy->texture->SetPart(Enemy->animator.frame + stun + following, 0);
			break;

		case RIGHT_DOWN:
			Enemy->texture->SetPart(Enemy->animator.frame + walk + following, 0);
			break;

		case LEFT_DOWN:
			Enemy->texture->SetPart(Enemy->animator.frame + walk + following, 1);
			break;

		case LEFT_UP:
			Enemy->texture->SetPart(Enemy->animator.frame + walk + following, 2);
			break;

		case RIGHT_UP:
			Enemy->texture->SetPart(Enemy->animator.frame + walk + following, 3);
			break;
		}
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
		if (Enemy->IsStun == Stun || Enemy->IsStun == Stun_) {}
		else {
			if ((Player->mappos.LeftDown - 1 == Enemy->mappos.LeftDown && Player->mappos.RightDown == Enemy->mappos.RightDown) ||
				(Player->mappos.LeftDown + 1 == Enemy->mappos.LeftDown && Player->mappos.RightDown == Enemy->mappos.RightDown) ||
				(Player->mappos.LeftDown == Enemy->mappos.LeftDown && Player->mappos.RightDown + 1 == Enemy->mappos.RightDown) ||
				(Player->mappos.LeftDown == Enemy->mappos.LeftDown && Player->mappos.RightDown - 1 == Enemy->mappos.RightDown) ||
				(Player->mappos.LeftDown == Enemy->mappos.LeftDown && Player->mappos.RightDown  == Enemy->mappos.RightDown)) {
				turn = PENGUIN_ATTACK;
				Enemy->EnemyAttak = true;
				Player->EnemyAttak = true;
			}
		}
	}
	if (Player2->Goalfrg == false) {
		if (Enemy->IsStun == Stun || Enemy->IsStun == Stun_) {}
		else {
			if ((Player2->mappos.LeftDown - 1 == Enemy->mappos.LeftDown && Player2->mappos.RightDown == Enemy->mappos.RightDown) ||
				(Player2->mappos.LeftDown + 1 == Enemy->mappos.LeftDown && Player2->mappos.RightDown == Enemy->mappos.RightDown) ||
				(Player2->mappos.LeftDown == Enemy->mappos.LeftDown && Player2->mappos.RightDown + 1 == Enemy->mappos.RightDown) ||
				(Player2->mappos.LeftDown == Enemy->mappos.LeftDown && Player2->mappos.RightDown - 1 == Enemy->mappos.RightDown) ||
				(Player2->mappos.LeftDown == Enemy->mappos.LeftDown && Player2->mappos.RightDown == Enemy->mappos.RightDown)) {
				turn = PENGUIN_ATTACK;
				Enemy->EnemyAttak = true;
				Player2->EnemyAttak = true;
			}
		}
	}
}

void Enemy_GameOver_Move(GameObject * Player)
{
	switch (Player->direction)
	{
	case RIGHT_DOWN:
		if (Player->animator.count != PLAYER_SPEED) {
			double tmp = (double)Player->animator.count / (double)PLAYER_SPEED;
			double tmp1 = 0;
			if (Player->animator.count != 0)
				tmp1 = (double)(Player->animator.count - 1) / (double)PLAYER_SPEED;
			Player->posX += (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH;
			Player->posY -= (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH;
			Player->animator.count++;
		}
		else {
			Player->direction = NULL_WAY;
			Player->animator.count = 0;
			Player->animator.isActive = false;
		}
		break;

	case LEFT_DOWN:
		if (Player->animator.count != PLAYER_SPEED) {
			double tmp = (double)Player->animator.count / (double)PLAYER_SPEED;
			double tmp1 = 0;
			if (Player->animator.count != 0)
				tmp1 = (double)(Player->animator.count - 1) / (double)PLAYER_SPEED;
			Player->posX -= (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH;
			Player->posY -= (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH;
			Player->animator.count++;
		}
		else {
			Player->direction = NULL_WAY;
			Player->animator.count = 0;
			Player->animator.isActive = false;
		}
		break;

	case LEFT_UP:
		if (Player->animator.count != PLAYER_SPEED) {
			double tmp = (double)Player->animator.count / (double)PLAYER_SPEED;
			double tmp1 = 0;
			if (Player->animator.count != 0)
				tmp1 = (double)(Player->animator.count - 1) / (double)PLAYER_SPEED;
			Player->posX -= (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH;
			Player->posY += (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH;
			Player->animator.count++;
		}
		else {
			Player->direction = NULL_WAY;
			Player->animator.count = 0;
			Player->animator.isActive = false;
			//Map[Player->mappos.Height * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown + 1].
		}
		break;

	case RIGHT_UP:
		if (Player->animator.count != PLAYER_SPEED) {
			double tmp = (double)Player->animator.count / (double)PLAYER_SPEED;
			double tmp1 = 0;
			if (Player->animator.count != 0)
				tmp1 = (double)(Player->animator.count - 1) / (double)PLAYER_SPEED;
			Player->posX += (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH;
			Player->posY += (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH;
			Player->animator.count++;
		}
		else {
			Player->direction = NULL_WAY;
			Player->animator.count = 0;
			Player->animator.isActive = false;
		}
		break;
	}
}

void Enemy_Move_Frg(GameObject * Enemy, GameObject * Player)
{
	if (Enemy->mappos.LeftDown == Player->mappos.LeftDown && Enemy->mappos.RightDown == Player->mappos.RightDown - 1)
		Enemy->direction = RIGHT_DOWN;
	if (Enemy->mappos.LeftDown == Player->mappos.LeftDown && Enemy->mappos.RightDown == Player->mappos.RightDown + 1)
		Enemy->direction = LEFT_UP;
	if (Enemy->mappos.LeftDown == Player->mappos.LeftDown - 1 && Enemy->mappos.RightDown == Player->mappos.RightDown)
		Enemy->direction = LEFT_DOWN;
	if (Enemy->mappos.LeftDown == Player->mappos.LeftDown + 1 && Enemy->mappos.RightDown == Player->mappos.RightDown)
		Enemy->direction = RIGHT_UP;
	if (Enemy->mappos.LeftDown == Player->mappos.LeftDown && Enemy->mappos.RightDown == Player->mappos.RightDown)
		Enemy->direction = NULL_WAY;
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
	if (Player2->Goalfrg == true) {
		if (Player_EnemyIn)
			Enemy->enemyeye = ENEMYEYE_IN_1;
		else
			Enemy->enemyeye = ENEMYEYE_OUT;
	}
	if (Player->Goalfrg == true) {
		if (Player_EnemyIn2)
			Enemy->enemyeye = ENEMYEYE_IN_2;
		else
			Enemy->enemyeye = ENEMYEYE_OUT;
	}

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
void Enemy_Stun(GameObject * Enemy, GameObject * Player, GameObject * Player2, GameObject* Map)
{
	if (RIGHTUP_SLOPE == Map_GetPlayerTile_TopRightUp(Enemy, Map)) {
		if (Player->mappos.LeftDown == Enemy->mappos.LeftDown &&
			Player->mappos.RightDown == Enemy->mappos.RightDown) {
			Enemy->IsStun = Stun_Release;
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_ENEMYSTAN));
		}
		else
		{
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_ENEMYSTAN));
		}
	}

	if (LEFTUP_SLOPE == Map_GetPlayerTile_TopLeftUp(Enemy, Map)) {
		if (Player->mappos.LeftDown == Enemy->mappos.LeftDown &&
			Player->mappos.RightDown == Enemy->mappos.RightDown) {
			Enemy->IsStun = Stun_Release;
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_ENEMYSTAN));
		}
		else
		{
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_ENEMYSTAN));
		}
	}
}