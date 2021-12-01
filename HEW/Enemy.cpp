#include "Enemy.h"

void Enemy_Initialize(GameObject * Enemy)
{
	Enemy->textuer = new Sprite("assets/player.png", 1, 1);
	Enemy->textuer->SetSize(80, 80);
	Enemy->posY = 0.5f;
	Enemy->mappos.Height = 0;
	Enemy->mappos.LeftDown = 0;
	Enemy->mappos.RightDown = 0;
}

void Enemy_SetLocation(GameObject * Enemy, GameObject * Location, int Height, int LeftDown, int RightDown)
{
	Enemy->posX = Location[Height * 100 + LeftDown * 10 + RightDown].posX + MAP_LENGTH / 2.0f;
	Enemy->posY = Location[Height * 100 + LeftDown * 10 + RightDown].posY;
	Enemy->mappos.Height = Height;
	Enemy->mappos.LeftDown = LeftDown;
	Enemy->mappos.RightDown = RightDown;
}

MapPos Enemy_GetMapPos(GameObject * Enemy)
{
	return MapPos();
}

void Enemy_Update(GameObject * Enemy)
{
}

void Enemy_Hit(GameObject * Enemy, GameObject * Player, GameObject * SnowBall)
{
}
