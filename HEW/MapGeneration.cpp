#include "MapGeneration.h"
#include "input.h"

int gStarg = 0;

void Map_Initialize(GameObject * Map)
{
	for (int k = 0; k < MAP_HEIGHT; k++) {
		for (int j = 0; j < MAP_EDGE; j++) {
			for (int i = 0; i < MAP_EDGE; i++) {
				Map[i + MAP_EDGE * j + 100 * k].texture = new Sprite("assets/blockseat.png", 4, 1);
				Map[i + MAP_EDGE * j + 100 * k].texture->SetSize(BOX_HEIGHT, BOX_WIDTH);
			}
		}
	}
	// É}ÉbÉvê∂ê¨

	for (int k = 0; k < MAP_HEIGHT; k++) {
		for (int j = 0; j < MAP_EDGE; j++) {
			for (int i = 0; i < MAP_EDGE; i++) {
				Map[i + j * MAP_EDGE + 100 * k].posX += MAP_LENGTH * (i + 1 - j);
				Map[i + j * MAP_EDGE + 100 * k].posY -= MAP_LENGTH * (i + 1 + j);

				Map[i + j * MAP_EDGE + 100 * k].posY += 0.7f + k * MAP_LENGTH*1.5f;
				Map[i + j * MAP_EDGE + 100 * k].posX -= MAP_LENGTH * 2;
			}
		}
	}
}

int Map_GetPlayerTile(GameObject * Player, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE])
{
	return MapChip[gStarg][Player->mappos.Height][Player->mappos.LeftDown][Player->mappos.RightDown];
}

void Map_Update(GameObject * Map, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE])
{
	//CSVÇÃèáî‘í ÇËÇ…Ç»ÇÈ
	if (Input_GetKeyTrigger(VK_DOWN) && gStarg > 0) {
		gStarg--;
	}
	if (Input_GetKeyTrigger(VK_UP) && gStarg < MAP_STAGE - 1) {
		gStarg++;
	}
	for (int k = 0; k < MAP_HEIGHT; k++) {
		for (int j = 0; j < MAP_EDGE; j++) {
			for (int i = 0; i < MAP_EDGE; i++) {
				Map[i + MAP_EDGE * j + 100 * k].texture->SetPart(MapChip[gStarg][k][j][i], 0);
			}
		}
	}
}
