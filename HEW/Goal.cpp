#include "Goal.h"

void Goal_Initialize(GameObject* Goal)
{
	Goal->textuer = new Sprite("assets/Goal.png", 1, 1);
	Goal->textuer->SetSize(100, 100);
	Goal->posY = 0.5f;
	Goal->mappos.Height = 0;
	Goal->mappos.LeftDown = 0;
	Goal->mappos.RightDown = 0;
	Goal->direction = NULL_WAY;
}

void Goal_SetLocation(GameObject* Goal, GameObject* Location, int Height, int LeftDown, int RightDown)
{
	Goal->posX = Location[Height * 100 + LeftDown * 10 + RightDown].posX + MAP_LENGTH / 2.0f;
	Goal->posY = Location[Height * 100 + LeftDown * 10 + RightDown].posY;
	Goal->mappos.Height = Height;
	Goal->mappos.LeftDown = LeftDown;
	Goal->mappos.RightDown = RightDown;
	Goal->tmp = Goal->mappos;
}

MapPos Goal_GetMapPos(GameObject* Goal)
{
	return MapPos();
}

void Goal_Update(GameObject* Goal)
{

}
