#include "MapGeneration.h"
#include "input.h"

int gStarg = 0;

void Map_Initialize(GameObject * Map)
{
	for (int k = 0; k < MAP_HEIGHT; k++) {
		for (int j = 0; j < MAP_EDGE; j++) {
			for (int i = 0; i < MAP_EDGE; i++) {
				Map[i + MAP_EDGE * j + 100 * k].textuer = new Sprite("assets/MapSeat.png", 6, 1);
				Map[i + MAP_EDGE * j + 100 * k].textuer->SetSize(BOX_HEIGHT, BOX_WIDTH);
			}
		}
	}
	// マップ生成

	for (int k = 0; k < MAP_HEIGHT; k++) {
		for (int j = 0; j < MAP_EDGE; j++) {
			for (int i = 0; i < MAP_EDGE; i++) {
				Map[i + j * MAP_EDGE + 100 * k].posX += MAP_LENGTH * (i + 1 - j);
				Map[i + j * MAP_EDGE + 100 * k].posY -= MAP_LENGTH * (i + 1 + j);

				Map[i + j * MAP_EDGE + 100 * k].posY += 0.7f + k * MAP_LENGTH*1.375f;
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
	//CSVの順番通りになる
	if (Input_GetKeyTrigger(VK_DOWN) && gStarg > 0) {
		gStarg--;
		for (int k = 0; k < MAP_HEIGHT; k++) {
			for (int j = 0; j < MAP_EDGE; j++) {
				for (int i = 0; i < MAP_EDGE; i++) {
					Map[i + MAP_EDGE * j + 100 * k].textuer->SetPart(MapChip[gStarg][k][j][i], 0);
				}
			}
		}
	}
	if (Input_GetKeyTrigger(VK_UP) && gStarg < MAP_STAGE - 1) {
		gStarg++;
		for (int k = 0; k < MAP_HEIGHT; k++) {
			for (int j = 0; j < MAP_EDGE; j++) {
				for (int i = 0; i < MAP_EDGE; i++) {
					Map[i + MAP_EDGE * j + 100 * k].textuer->SetPart(MapChip[gStarg][k][j][i], 0);
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////
//マップにあるオブジェクトは全てこれを使って動かしてほしい
//引数 (動かしたいゲームオブジェクト、MapChip)
//戻り値 無し
//////////////////////////////////////////////////////////
void MapMove_Update(GameObject * Player, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE]) {
	// マップ外にはいかない
	if (Player->mappos.LeftDown == -1) {
		Player->mappos.LeftDown++;
		Player->direction = NULL_WAY;
		return;
	}
	if (Player->mappos.RightDown == -1) {
		Player->mappos.RightDown++;
		Player->direction = NULL_WAY;
		return;
	}
	if (Player->mappos.LeftDown == MAP_EDGE) {
		Player->mappos.LeftDown--;
		Player->direction = NULL_WAY;
		return;
	}
	if (Player->mappos.RightDown == MAP_EDGE) {
		Player->mappos.RightDown--;
		Player->direction = NULL_WAY;
		return;
	}
	//進むマスが何か取得
	//地面がないとき
	if (MapChip[gStarg][Player->mappos.Height][Player->mappos.LeftDown][Player->mappos.RightDown] == -1) {
		//右上坂の時
		if (MapChip[gStarg][Player->mappos.Height + 1][Player->mappos.LeftDown][Player->mappos.RightDown] == RIGHTUP_SLOPE) {
			if (Player->animator.count != PLAYER_SPEED * 2) {
				Player->posX += MAP_LENGTH / PLAYER_SPEED;
				Player->posY += (MAP_LENGTH / PLAYER_SPEED) * 2;
				Player->animator.count++;
			}
			else {
				Player->mappos.Height++;
				Player->mappos.LeftDown--;
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
		} //左上坂の時
		else if (MapChip[gStarg][Player->mappos.Height + 1][Player->mappos.LeftDown][Player->mappos.RightDown] == LEFTUP_SLOPE) {
			if (Player->animator.count != PLAYER_SPEED * 2) {
				Player->posX -= MAP_LENGTH / PLAYER_SPEED;
				Player->posY += (MAP_LENGTH / PLAYER_SPEED) * 2;
				Player->animator.count++;
			}
			else {
				Player->mappos.Height++;
				Player->mappos.RightDown--;
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
		}
		else {	//移動せず終わる
			switch (Player->direction) {
			case RIGHT_DOWN:
				Player->mappos.RightDown--;
				break;
			case LEFT_DOWN:
				Player->mappos.LeftDown--;
				break;
			case LEFT_UP:
				Player->mappos.RightDown++;
				break;
			case RIGHT_UP:
				Player->mappos.LeftDown++;
				break;
			}
			Player->direction = NULL_WAY;
			return;
		}
	}//雪の上の時
	else if (MapChip[gStarg][Player->mappos.Height][Player->mappos.LeftDown][Player->mappos.RightDown] == SNOW_GROUND) {
		switch (Player->direction)
		{
		case RIGHT_DOWN:
			if (Player->animator.count != PLAYER_SPEED) {
				Player->posX += MAP_LENGTH / PLAYER_SPEED;
				Player->posY -= MAP_LENGTH / PLAYER_SPEED;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
			break;

		case LEFT_DOWN:
			if (Player->animator.count != PLAYER_SPEED) {
				Player->posX -= MAP_LENGTH / PLAYER_SPEED;
				Player->posY -= MAP_LENGTH / PLAYER_SPEED;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
			break;

		case LEFT_UP:
			if (Player->animator.count != PLAYER_SPEED) {
				Player->posX -= MAP_LENGTH / PLAYER_SPEED;
				Player->posY += MAP_LENGTH / PLAYER_SPEED;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
			break;

		case RIGHT_UP:
			if (Player->animator.count != PLAYER_SPEED) {
				Player->posX += MAP_LENGTH / PLAYER_SPEED;
				Player->posY += MAP_LENGTH / PLAYER_SPEED;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
			break;
		}
	} //普通の地面
	else if (MapChip[gStarg][Player->mappos.Height][Player->mappos.LeftDown][Player->mappos.RightDown] == NORMAL_GROUND) {
		switch (Player->direction)
		{
		case RIGHT_DOWN:
			if (Player->animator.count != PLAYER_SPEED) {
				Player->posX += MAP_LENGTH / PLAYER_SPEED;
				Player->posY -= MAP_LENGTH / PLAYER_SPEED;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
			break;

		case LEFT_DOWN:
			if (Player->animator.count != PLAYER_SPEED) {
				Player->posX -= MAP_LENGTH / PLAYER_SPEED;
				Player->posY -= MAP_LENGTH / PLAYER_SPEED;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
			break;

		case LEFT_UP:
			if (Player->animator.count != PLAYER_SPEED) {
				Player->posX -= MAP_LENGTH / PLAYER_SPEED;
				Player->posY += MAP_LENGTH / PLAYER_SPEED;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
			break;

		case RIGHT_UP:
			if (Player->animator.count != PLAYER_SPEED) {
				Player->posX += MAP_LENGTH / PLAYER_SPEED;
				Player->posY += MAP_LENGTH / PLAYER_SPEED;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
			break;
		}
	} //氷の時
	else if (MapChip[gStarg][Player->mappos.Height][Player->mappos.LeftDown][Player->mappos.RightDown] == ICE_GROUND) {
		switch (Player->direction)
		{
		case RIGHT_DOWN:
			if (Player->animator.count != PLAYER_SPEED) {
				Player->posX += MAP_LENGTH / PLAYER_SPEED;
				Player->posY -= MAP_LENGTH / PLAYER_SPEED;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
			break;

		case LEFT_DOWN:
			if (Player->animator.count != PLAYER_SPEED) {
				Player->posX -= MAP_LENGTH / PLAYER_SPEED;
				Player->posY -= MAP_LENGTH / PLAYER_SPEED;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
			break;

		case LEFT_UP:
			if (Player->animator.count != PLAYER_SPEED) {
				Player->posX -= MAP_LENGTH / PLAYER_SPEED;
				Player->posY += MAP_LENGTH / PLAYER_SPEED;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
			break;

		case RIGHT_UP:
			if (Player->animator.count != PLAYER_SPEED) {
				Player->posX += MAP_LENGTH / PLAYER_SPEED;
				Player->posY += MAP_LENGTH / PLAYER_SPEED;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
			break;
		}
	} //土の時
	else if (MapChip[gStarg][Player->mappos.Height][Player->mappos.LeftDown][Player->mappos.RightDown] == SOIL_GROUND) {
		switch (Player->direction)
		{
		case RIGHT_DOWN:
			if (Player->animator.count != PLAYER_SPEED) {
				Player->posX += MAP_LENGTH / PLAYER_SPEED;
				Player->posY -= MAP_LENGTH / PLAYER_SPEED;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
			break;

		case LEFT_DOWN:
			if (Player->animator.count != PLAYER_SPEED) {
				Player->posX -= MAP_LENGTH / PLAYER_SPEED;
				Player->posY -= MAP_LENGTH / PLAYER_SPEED;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
			break;

		case LEFT_UP:
			if (Player->animator.count != PLAYER_SPEED) {
				Player->posX -= MAP_LENGTH / PLAYER_SPEED;
				Player->posY += MAP_LENGTH / PLAYER_SPEED;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
			break;

		case RIGHT_UP:
			if (Player->animator.count != PLAYER_SPEED) {
				Player->posX += MAP_LENGTH / PLAYER_SPEED;
				Player->posY += MAP_LENGTH / PLAYER_SPEED;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
			break;
		}
	} //右上坂の時
	else if (MapChip[gStarg][Player->mappos.Height][Player->mappos.LeftDown][Player->mappos.RightDown] == RIGHTUP_SLOPE) {
		if (Player->direction == LEFT_DOWN) {
			if (Player->animator.count != PLAYER_SPEED * 2) {
				Player->posX -= MAP_LENGTH / PLAYER_SPEED;
				Player->posY -= MAP_LENGTH / PLAYER_SPEED * 2;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->mappos.LeftDown++;
				Player->mappos.Height--;
				Player->animator.count = 0;
			}
		}
		else {
			switch (Player->direction) {
			case RIGHT_DOWN:
				Player->mappos.RightDown--;
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
				return;
			case LEFT_UP:
				Player->mappos.RightDown++;
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
				return;
			}
		}
	} //左上坂の時
	else if (MapChip[gStarg][Player->mappos.Height][Player->mappos.LeftDown][Player->mappos.RightDown] == LEFTUP_SLOPE) {
		if (Player->direction == RIGHT_DOWN) {
			if (Player->animator.count != PLAYER_SPEED * 2) {
				Player->posX += MAP_LENGTH / PLAYER_SPEED;
				Player->posY -= MAP_LENGTH / PLAYER_SPEED * 2;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->mappos.RightDown++;
				Player->mappos.Height--;
				Player->animator.count = 0;
			}
		}
		else {
			switch (Player->direction)
			{
				case RIGHT_UP:
					Player->mappos.LeftDown++;
					Player->direction = NULL_WAY;
					Player->animator.count = 0;
					return;
				case LEFT_DOWN:
					Player->mappos.LeftDown--;
					Player->direction = NULL_WAY;
					Player->animator.count = 0;
					return;
			}
		}
	}
}