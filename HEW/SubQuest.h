#pragma once
#include "GameObject.h"
#include "MapGeneration.h"

struct SubQuest{
	bool dirtFlag(GameObject*Player1,GameObject*Player2);
	bool iceFlag(GameObject* Map);
	bool stanFlag(GameObject* Enemy);
	//bool timeFlag();
};
