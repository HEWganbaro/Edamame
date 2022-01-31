#include "SubQuest.h"

bool SubQuest::dirtFlag(GameObject * Player1, GameObject * Player2)
{
	if (Player1->dirtF == false && Player2->dirtF == false)
		return false;
	else
		return true;
}

bool SubQuest::iceFlag(GameObject * Map)
{// ƒ}ƒbƒv¶¬
	for (int k = 0; k < MAP_HEIGHT; k++) {
		for (int j = 0; j < MAP_EDGE; j++) {
			for (int i = 0; i < MAP_EDGE; i++) {
				if (Map[i + j * MAP_EDGE + 100 * k].texture->GetPart() != 0, 1)
					return true;
			
			}
		}
	}
	return false;
}

bool SubQuest::stanFlag(GameObject * Enemy)
{
	if (Enemy->stanF == true) {
		return true;
	}
	else
	return false;
}
