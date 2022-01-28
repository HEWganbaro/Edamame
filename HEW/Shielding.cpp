#include "Shielding.h"

//void Shield_Initialize(GameObject * Shield)
//{
//	Shield->texture = new Sprite("assets/iwa.png", 1, 1);
//	Shield->texture->SetSize(120, 120);
//	Shield->posY = 0.5f;
//	Shield->mappos.Height = 0;
//	Shield->mappos.LeftDown = 0;
//	Shield->mappos.RightDown = 0;
//	Shield->direction = NULL_WAY;
//}
//
//void Shield_SetLocation(GameObject * Shield, GameObject * Location, int Height, int LeftDown, int RightDown)
//{
//	Shield->posX = Location[Height * 100 + LeftDown * 10 + RightDown].posX + MAP_LENGTH / 2.0f;
//	Shield->posY = Location[Height * 100 + LeftDown * 10 + RightDown].posY;
//	Shield->mappos.Height = Height;
//	Shield->mappos.LeftDown = LeftDown;
//	Shield->mappos.RightDown = RightDown;
//	Shield->tmp = Shield->mappos;
//}
//
//MapPos Shield_GetMapPos(GameObject * Shield)
//{
//	return MapPos();
//}
//
//void Shield_Update(GameObject * Shield)
//{
//}

//ŽÕ•Á‚Å‚Ì“G‚ÌƒwƒCƒg‚»‚ç‚µ
void Shield_Cancel(MapPos * mappos, GameObject * Player, GameObject * Player2, GameObject * Enemy)
{
	//Player
	if (Player->mappos.LeftDown - 1 == mappos->LeftDown && Player->mappos.RightDown == mappos->RightDown &&
		Enemy->mappos.LeftDown + 1 == mappos->LeftDown && Player->mappos.RightDown == mappos->RightDown)
	{
		if (Enemy->enemyeye == ENEMYEYE_IN_1)
		{
			Enemy->direction = RIGHT_UP;
			turn = ENV_TURN;
		}
		return;
	}

	if (Player->mappos.LeftDown + 1 == mappos->LeftDown && Player->mappos.RightDown == mappos->RightDown &&
		Enemy->mappos.LeftDown - 1 == mappos->LeftDown && Player->mappos.RightDown == mappos->RightDown)
	{
		if (Enemy->enemyeye == ENEMYEYE_IN_1)
		{
			Enemy->direction = LEFT_DOWN;
			turn = ENV_TURN;
		}
		return;
	}

	if (Player->mappos.RightDown - 1 == mappos->RightDown && Player->mappos.LeftDown == mappos->LeftDown &&
		Enemy->mappos.RightDown + 1 == mappos->RightDown && Player->mappos.LeftDown == mappos->LeftDown)
	{
		if (Enemy->enemyeye == ENEMYEYE_IN_1)
		{
			Enemy->direction = LEFT_UP;
			turn = ENV_TURN;
		}
		return;
	}

	if (Player->mappos.RightDown + 1 == mappos->RightDown && Player->mappos.LeftDown == mappos->LeftDown &&
		Enemy->mappos.RightDown - 1 == mappos->RightDown && Player->mappos.LeftDown == mappos->LeftDown)
	{
		if (Enemy->enemyeye == ENEMYEYE_IN_1)
		{
			Enemy->direction = RIGHT_DOWN;
			turn = ENV_TURN;
		}
		return;
	}

	//Player2
	if (Player2->mappos.LeftDown - 1 == mappos->LeftDown && Player2->mappos.RightDown == mappos->RightDown &&
		Enemy->mappos.LeftDown + 1 == mappos->LeftDown && Player2->mappos.RightDown == mappos->RightDown)
	{
		if (Enemy->enemyeye == ENEMYEYE_IN_1)
		{
			Enemy->direction = RIGHT_UP;
			turn = ENV_TURN;
		}
		return;
	}

	if (Player2->mappos.LeftDown + 1 == mappos->LeftDown && Player2->mappos.RightDown == mappos->RightDown &&
		Enemy->mappos.LeftDown - 1 == mappos->LeftDown && Player2->mappos.RightDown == mappos->RightDown)
	{
		if (Enemy->enemyeye == ENEMYEYE_IN_1)
		{
			Enemy->direction = LEFT_DOWN;
			turn = ENV_TURN;
		}
		return;
	}

	if (Player2->mappos.RightDown - 1 == mappos->RightDown && Player2->mappos.LeftDown == mappos->LeftDown &&
		Enemy->mappos.RightDown + 1 == mappos->RightDown && Player2->mappos.LeftDown == mappos->LeftDown)
	{
		if (Enemy->enemyeye == ENEMYEYE_IN_1)
		{
			Enemy->direction = LEFT_UP;
			turn = ENV_TURN;
		}
		return;
	}

	if (Player2->mappos.RightDown + 1 == mappos->RightDown && Player2->mappos.LeftDown == mappos->LeftDown &&
		Enemy->mappos.RightDown - 1 == mappos->RightDown && Player2->mappos.LeftDown == mappos->LeftDown)
	{
		if (Enemy->enemyeye == ENEMYEYE_IN_1)
		{
			Enemy->direction = RIGHT_DOWN;
			turn = ENV_TURN;
		}
		return;
	}
}
