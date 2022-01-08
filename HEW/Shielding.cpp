#include "Shielding.h"

void Shield_Initialize(GameObject * Shield)
{
	Shield->texture = new Sprite("assets/iwa.png", 1, 1);
	Shield->texture->SetSize(120, 120);
	Shield->posY = 0.5f;
	Shield->mappos.Height = 0;
	Shield->mappos.LeftDown = 0;
	Shield->mappos.RightDown = 0;
	Shield->direction = NULL_WAY;
}

void Shield_SetLocation(GameObject * Shield, GameObject * Location, int Height, int LeftDown, int RightDown)
{
	Shield->posX = Location[Height * 100 + LeftDown * 10 + RightDown].posX + MAP_LENGTH / 2.0f;
	Shield->posY = Location[Height * 100 + LeftDown * 10 + RightDown].posY;
	Shield->mappos.Height = Height;
	Shield->mappos.LeftDown = LeftDown;
	Shield->mappos.RightDown = RightDown;
	Shield->tmp = Shield->mappos;
}

MapPos Shield_GetMapPos(GameObject * Shield)
{
	return MapPos();
}

void Shield_Update(GameObject * Shield)
{
}

//ŽÕ•Á‚Å‚Ì“G‚ÌƒwƒCƒg‚»‚ç‚µ
void Shield_Cancel(GameObject * Shield, GameObject * SnowBall, GameObject * Enemy)
{

	if (SnowBall->mappos.LeftDown - 1 == Shield->mappos.LeftDown && SnowBall->mappos.RightDown == Shield->mappos.RightDown &&
		Enemy->mappos.LeftDown + 1 == Shield->mappos.LeftDown && SnowBall->mappos.RightDown == Shield->mappos.RightDown)
	{
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = RIGHT_UP;
		}
		return;
	}

	if (SnowBall->mappos.LeftDown + 1 == Shield->mappos.LeftDown && SnowBall->mappos.RightDown == Shield->mappos.RightDown &&
		Enemy->mappos.LeftDown - 1 == Shield->mappos.LeftDown && SnowBall->mappos.RightDown == Shield->mappos.RightDown)
	{
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = LEFT_DOWN;
		}
		return;
	}

	if (SnowBall->mappos.RightDown - 1 == Shield->mappos.RightDown && SnowBall->mappos.LeftDown == Shield->mappos.LeftDown &&
		Enemy->mappos.RightDown + 1 == Shield->mappos.RightDown && SnowBall->mappos.LeftDown == Shield->mappos.LeftDown)
	{
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = LEFT_UP;
		}
		return;
	}

	if (SnowBall->mappos.RightDown + 1 == Shield->mappos.RightDown && SnowBall->mappos.LeftDown == Shield->mappos.LeftDown &&
		Enemy->mappos.RightDown - 1 == Shield->mappos.RightDown && SnowBall->mappos.LeftDown == Shield->mappos.LeftDown)
	{
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = RIGHT_DOWN;;
		}
		return;
	}

}

//ŽÕ•Á‚Æ‚Ì“–‚½‚è”»’è
//void Shield_Hit(GameObject * Shield, GameObject * Player)
//{
//	//ƒvƒŒƒCƒ„[‚ÆŽÕ•Á‚Ì“–‚½‚è”»’è
//	if (Player->direction != NULL_WAY)
//	{
//		if (Player->mappos.LeftDown - 1 == Shield->mappos.LeftDown &&
//			Player->mappos.RightDown == Shield->mappos.RightDown)
//		{
//			Player->direction = LEFT_DOWN;
//		}
//		if (Player->mappos.LeftDown + 1 == Shield->mappos.LeftDown &&
//			Player->mappos.RightDown == Shield->mappos.RightDown)
//		{
//			Player->direction = RIGHT_UP;
//		}
//		if (Player->mappos.RightDown - 1 == Shield->mappos.RightDown &&
//			Player->mappos.LeftDown == Shield->mappos.LeftDown)
//		{
//			Player->direction = RIGHT_DOWN;
//		}
//		if (Player->mappos.RightDown + 1 == Shield->mappos.RightDown &&
//			Player->mappos.LeftDown == Shield->mappos.LeftDown)
//		{
//			Player->direction = LEFT_UP;
//		}
//	}

	//“G‚ÆŽÕ•Á‚Ì“–‚½‚è”»’è
	//if (Enemy->mappos.LeftDown - 1 == Shield->mappos.LeftDown &&
	//	Enemy->mappos.RightDown == Shield->mappos.RightDown)
	//{

	//}
	//if (Enemy->mappos.LeftDown + 1 == Shield->mappos.LeftDown &&
	//	Enemy->mappos.RightDown == Shield->mappos.RightDown)
	//{

	//}
	//if (Enemy->mappos.RightDown - 1 == Shield->mappos.RightDown &&
	//	Enemy->mappos.LeftDown == Shield->mappos.LeftDown)
	//{

	//}
	//if (Enemy->mappos.RightDown + 1 == Shield->mappos.RightDown &&
	//	Enemy->mappos.LeftDown == Shield->mappos.LeftDown)
	//{

	//}

	////á‹Ê‚ÆŽÕ•Á‚Ì“–‚½‚è”»’è
	//if (SnowBall->mappos.LeftDown - 1 == Shield->mappos.LeftDown &&
	//	SnowBall->mappos.RightDown == Shield->mappos.RightDown)
	//{

	//}
	//if (SnowBall->mappos.LeftDown + 1 == Shield->mappos.LeftDown &&
	//	SnowBall->mappos.RightDown == Shield->mappos.RightDown)
	//{

	//}
	//if (SnowBall->mappos.RightDown - 1 == Shield->mappos.RightDown &&
	//	SnowBall->mappos.LeftDown == Shield->mappos.LeftDown)
	//{

	//}
	//if (SnowBall->mappos.RightDown + 1 == Shield->mappos.RightDown &&
	//	SnowBall->mappos.LeftDown == Shield->mappos.LeftDown)
	//{

	//}
//}
