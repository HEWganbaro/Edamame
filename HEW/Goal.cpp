#include "Goal.h"

void Goal_Initialize(GameObject * Goal)
{
	Goal->textuer = new Sprite("assets/goal.png", 1, 1);
	Goal->textuer->SetSize(120, 120);
	Goal->posY = 0.5f;
	Goal->mappos.Height = 0;
	Goal->mappos.LeftDown = 0;
	Goal->mappos.RightDown = 0;
	Goal->direction = NULL_WAY;
}

void Goal_SetLocation(GameObject * Goal, GameObject * Location, int Height, int LeftDown, int RightDown)
{
	Goal->posX = Location[Height * 100 + LeftDown * 10 + RightDown].posX + MAP_LENGTH / 2.0f;
	Goal->posY = Location[Height * 100 + LeftDown * 10 + RightDown].posY;
	Goal->mappos.Height = Height;
	Goal->mappos.LeftDown = LeftDown;
	Goal->mappos.RightDown = RightDown;
	Goal->tmp = Goal->mappos;
}

MapPos Goal_GetMapPos(GameObject * Goal)
{
	return MapPos();
}

void Goal_Update(GameObject * Goal)
{
}

//ŽÕ•Á‚Å‚Ì“G‚ÌƒwƒCƒg‚»‚ç‚µ
void Goal_Cancel(GameObject * Goal, GameObject * SnowBall, GameObject * Enemy)
{

	if (SnowBall->mappos.LeftDown - 1 == Goal->mappos.LeftDown && SnowBall->mappos.RightDown == Goal->mappos.RightDown &&
		Enemy->mappos.LeftDown + 1 == Goal->mappos.LeftDown && SnowBall->mappos.RightDown == Goal->mappos.RightDown)
	{
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = RIGHT_UP;
		}
		return;
	}

	if (SnowBall->mappos.LeftDown + 1 == Goal->mappos.LeftDown && SnowBall->mappos.RightDown == Goal->mappos.RightDown &&
		Enemy->mappos.LeftDown - 1 == Goal->mappos.LeftDown && SnowBall->mappos.RightDown == Goal->mappos.RightDown)
	{
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = LEFT_DOWN;
		}
		return;
	}

	if (SnowBall->mappos.RightDown - 1 == Goal->mappos.RightDown && SnowBall->mappos.LeftDown == Goal->mappos.LeftDown &&
		Enemy->mappos.RightDown + 1 == Goal->mappos.RightDown && SnowBall->mappos.LeftDown == Goal->mappos.LeftDown)
	{
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = LEFT_UP;
		}
		return;
	}

	if (SnowBall->mappos.RightDown + 1 == Goal->mappos.RightDown && SnowBall->mappos.LeftDown == Goal->mappos.LeftDown &&
		Enemy->mappos.RightDown - 1 == Goal->mappos.RightDown && SnowBall->mappos.LeftDown == Goal->mappos.LeftDown)
	{
		if (Enemy->enemyeye == ENEMYEYE_IN)
		{
			Enemy->direction = RIGHT_DOWN;;
		}
		return;
	}

}
