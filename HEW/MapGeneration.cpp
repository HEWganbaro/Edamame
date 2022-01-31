#include "MapGeneration.h"
#include "input.h"

int gStarg = 0;
int stage = STAGE_1;


void Map_Initialize(GameObject * Map)
{
	for (int k = 0; k < MAP_HEIGHT; k++) {
		for (int j = 0; j < MAP_EDGE; j++) {
			for (int i = 0; i < MAP_EDGE; i++) {
				Map[i + MAP_EDGE * j + 100 * k].texture = new Sprite("assets/Sprite_seat.png", 11, 1);
				Map[i + MAP_EDGE * j + 100 * k].texture->SetSize(BOX_HEIGHT, BOX_WIDTH);
			}
		}
	}
	// �}�b�v����
	for (int k = 0; k < MAP_HEIGHT; k++) {
		for (int j = 0; j < MAP_EDGE; j++) {
			for (int i = 0; i < MAP_EDGE; i++) {
				Map[i + j * MAP_EDGE + 100 * k].posX += MAP_LENGTH * (i + 1 - j);
				Map[i + j * MAP_EDGE + 100 * k].posY -= (MAP_LENGTH-0.0025f) * (i + 1 + j);

				Map[i + j * MAP_EDGE + 100 * k].posY += 0.7f + k * MAP_LENGTH*1.225f;
				Map[i + j * MAP_EDGE + 100 * k].posX -= MAP_LENGTH * 2;
			}
		}
	}
}

int Map_GetStage()
{
	return gStarg;
}

int Map_GetPlayerTile(GameObject * Player, GameObject * Map)
{
	return Map[Player->mappos.Height * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown].texture->GetPart();
}

int Map_GetPlayerTile_LeftUp(GameObject * Player, GameObject * Map)
{
	return Map[Player->mappos.Height * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown - 1].texture->GetPart();
}

int Map_GetPlayerTile_RightDown(GameObject * Player, GameObject * Map)
{
	return Map[Player->mappos.Height * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown + 1].texture->GetPart();
}

int Map_GetPlayerTile_LeftDown(GameObject * Player, GameObject * Map)
{
	return Map[Player->mappos.Height * 100 + (Player->mappos.LeftDown + 1) * 10 + Player->mappos.RightDown].texture->GetPart();
}

int Map_GetPlayerTile_RightUp(GameObject * Player, GameObject * Map)
{
	return Map[Player->mappos.Height * 100 + (Player->mappos.LeftDown - 1) * 10 + Player->mappos.RightDown].texture->GetPart();
}

int Map_GetPlayerTile_Top(GameObject * Player, GameObject * Map)
{
	return Map[(Player->mappos.Height + 1) * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown].texture->GetPart();
}

int Map_GetPlayerTile_TopRightUp(GameObject * Player, GameObject * Map)
{
	return Map[(Player->mappos.Height + 1) * 100 + (Player->mappos.LeftDown - 1) * 10 + Player->mappos.RightDown].texture->GetPart();
}

int Map_GetPlayerTile_TopLeftUp(GameObject * Player, GameObject * Map)
{
	return Map[(Player->mappos.Height + 1) * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown - 1].texture->GetPart();
}

//�v���C���[�̃^�C����Ԃ��֐�
void Map_Update(GameObject * Map, vector<MapPos>* StoneMap, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE])
{
	for (int k = 0; k < MAP_HEIGHT; k++) {
		for (int j = 0; j < MAP_EDGE; j++) {
			for (int i = 0; i < MAP_EDGE; i++) {
				Map[i + MAP_EDGE * j + 100 * k].changeFlag = false;
			}
		}
	}
	//CSV�̏��Ԓʂ�ɂȂ�
	if (stage == STAGE_1) {
		StoneMap->clear();
		gStarg = 0;
		for (int k = 0; k < MAP_HEIGHT; k++) {
			for (int j = 0; j < MAP_EDGE; j++) {
				for (int i = 0; i < MAP_EDGE; i++) {
					Map[i + MAP_EDGE * j + 100 * k].texture->SetPart(MapChip[stage - 1][k][j][i], 0);
				}
			}
		}
		Map_GetStone(StoneMap, Map);
	}
	if (stage == STAGE_2) {
		StoneMap->clear();
		gStarg = 1;
		for (int k = 0; k < MAP_HEIGHT; k++) {
			for (int j = 0; j < MAP_EDGE; j++) {
				for (int i = 0; i < MAP_EDGE; i++) {
					Map[i + MAP_EDGE * j + 100 * k].texture->SetPart(MapChip[stage - 1][k][j][i], 0);
				}
			}
		}
		Map_GetStone(StoneMap, Map);
	}
}

void Map_GetStone(vector<MapPos>* StoneMap, GameObject* Map)
{
	for (int k = 0; k < MAP_HEIGHT; k++) {
		for (int j = 0; j < MAP_EDGE; j++) {
			for (int i = 0; i < MAP_EDGE; i++) {
				if (Map[i + MAP_EDGE * j + 100 * k].texture->GetPart() == STONE) {
					MapPos tmp;
					tmp.Height = k;
					tmp.LeftDown = j;
					tmp.RightDown = i;
					StoneMap->emplace_back(tmp);
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////
//�}�b�v�ɂ���I�u�W�F�N�g�͑S�Ă�����g���ē������Ăق���
//���� (�����������Q�[���I�u�W�F�N�g�AMapChip)
//�߂�l ����
//////////////////////////////////////////////////////////
void MapMove_Update(GameObject * Player, GameObject* Map) {
	if (Player->direction != NULL_WAY)
		Player->diretmp = Player->direction;
	// �}�b�v�O�ɂ͂����Ȃ�
	if (Player->mappos.LeftDown == -1) {
		Player->mappos.LeftDown++;
		Player->direction = NULL_WAY;
		Player->animator.isActive = false;
		return;
	}
	if (Player->mappos.RightDown == -1) {
		Player->mappos.RightDown++;
		Player->direction = NULL_WAY;
		Player->animator.isActive = false;
		return;
	}
	if (Player->mappos.LeftDown == MAP_EDGE) {
		Player->mappos.LeftDown--;
		Player->direction = NULL_WAY;
		Player->animator.isActive = false;
		return;
	}
	if (Player->mappos.RightDown == MAP_EDGE) {
		Player->mappos.RightDown--;
		Player->direction = NULL_WAY;
		Player->animator.isActive = false;
		return;
	}
	//�������Ȃ�
	if (Player->direction == NO_ACTION) {
		Player->animator.isActive = false;
		return;
	}

	//�i�ރ}�X�������擾
	//�n�ʂ��Ȃ��Ƃ�
	if (Map_GetPlayerTile(Player, Map) == -1) {
		//�E���̎�
		if (Map_GetPlayerTile_Top(Player, Map) == RIGHTUP_SLOPE &&
			Player->direction == RIGHT_UP) {
			if (Player->animator.count != PLAYER_SPEED) {
				double tmp = (double)Player->animator.count / (double)PLAYER_SPEED;
				double tmp1 = 0;
				if (Player->animator.count != 0)
					tmp1 = (double)(Player->animator.count - 1) / (double)PLAYER_SPEED;
				Player->posX += (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH * 2;
				Player->posY += (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH * 1.55f * 2;
				Player->animator.count++;
			}
			else {
				Player->mappos.Height++;
				Player->mappos.LeftDown--;
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
				Player->animator.isActive = false;
			}
		} //�����̎�
		else if (Map_GetPlayerTile_Top(Player, Map) == LEFTUP_SLOPE && Player->direction == LEFT_UP) {
			if (Player->animator.count != PLAYER_SPEED) {
				double tmp = (double)Player->animator.count / (double)PLAYER_SPEED;
				double tmp1 = 0;
				if (Player->animator.count != 0)
					tmp1 = (double)(Player->animator.count - 1) / (double)PLAYER_SPEED;
				Player->posX -= (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH * 2;
				Player->posY += (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH * 1.55f * 2;
				Player->animator.count++;
			}
			else {
				Player->mappos.Height++;
				Player->mappos.RightDown--;
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
				Player->animator.isActive = false;
			}
		}
		else {	//�ړ������I���
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
			Player->animator.isActive = false;
			return;
		}
	}//��̏�̎�
	else if (Map_GetPlayerTile(Player, Map) == SNOW_GROUND) {
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
	} //���ʂ̒n��
	else if (Map_GetPlayerTile(Player, Map) == NORMAL_GROUND) {
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
	} //�X�̎�
	else if (Map_GetPlayerTile(Player, Map) == ICE_GROUND) {
		switch (Player->direction)
		{
		case RIGHT_DOWN:	//�C�[�W���O����>�ő呬�x�Ŋ��炷>�C�[�W���O����
			if (Player->mappos.RightDown + 1 == MAP_EDGE ||
				Map_GetPlayerTile_RightDown(Player, Map) == -1 ||//�}�b�v�O�܂Ŋ���Ȃ�
				Map_GetPlayerTile_RightDown(Player, Map) == LEFTUP_SLOPE ||
				Map_GetPlayerTile_RightDown(Player, Map) == RIGHTUP_SLOPE ||
				Map_GetPlayerTile_RightDown(Player, Map) == STONE ||
				(Map_GetPlayerTile_RightDown(Player, Map) == GOAL && Player->IsEnemy == true) ||
				(Map_GetPlayerTile_RightDown(Player, Map) == GOAL_LATER && Player->IsEnemy == true))
					Player->animator.ice = true;
			if (Player->animator.count < PLAYER_SPEED / 2 || Player->animator.ice == true) {
				double tmp = (double)Player->animator.count / (double)PLAYER_SPEED;
				double tmp1 = 0;
				if (Player->animator.count != 0)
					tmp1 = (double)(Player->animator.count - 1) / (double)PLAYER_SPEED;
				Player->posX += (Ice_Easing(tmp) - Ice_Easing(tmp1))*MAP_LENGTH;
				Player->posY -= (Ice_Easing(tmp) - Ice_Easing(tmp1))*MAP_LENGTH;
				Player->animator.count++;
				if (Player->animator.count == PLAYER_SPEED) {	//�~�߂�
					if (Map_GetPlayerTile_RightDown(Player, Map) != LEFTUP_SLOPE) {
						Player->animator.count = 0;
						Player->animator.ice = false;
						Player->animator.isActive = false;
						Player->direction = NULL_WAY;
					}
					else {
						Player->animator.ice = false;
						Player->animator.count = 0;
					}
					bool mapedge = Player->mappos.RightDown + 1 != MAP_EDGE;
					bool mapout = Map_GetPlayerTile_RightDown(Player, Map) != -1;
					bool mapslope = Map_GetPlayerTile_RightDown(Player, Map) != RIGHTUP_SLOPE;
					bool mapstone = Map_GetPlayerTile_RightDown(Player, Map) != STONE;
					bool enemygoal = Map_GetPlayerTile_RightDown(Player, Map) == GOAL && Player->IsEnemy == true;
					bool enemygoallater = Map_GetPlayerTile_RightDown(Player, Map) == GOAL_LATER && Player->IsEnemy == true;
					if (mapedge && mapout && mapslope && mapstone)
						Player->mappos.RightDown++;
					if (enemygoal || enemygoallater)
						Player->mappos.RightDown--;
					//�S�[���Ȃ�~�߂�
					if (Map_GetPlayerTile(Player, Map) == GOAL || Map_GetPlayerTile(Player, Map) == GOAL_LATER)
						Player->Goalfrg = true;
					if (Map_GetPlayerTile(Player, Map) == GOAL && Player->IsEnemy == false)
						Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(8, 0);
					if (Map_GetPlayerTile(Player, Map) == ITEM_FACE) {
						if (Player->Item_Arm == false) {	//�A�C�e���͓�����2���ĂȂ�
							Player->Item_Face = true;
							Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(1, 0);
						}
					}
					if (Map_GetPlayerTile(Player, Map) == ITEM_ARM) {
						if (Player->Item_Face == false) {	//�A�C�e���͓�����2���ĂȂ�
							Player->Item_Arm = true;
							Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(1, 0);
						}
					}
				}
			}
			else {
				if (Player->animator.count == PLAYER_SPEED + EASING_OFFSET) {//�����̃C�[�W���O
					Player->animator.ice = true;
					Player->animator.count = PLAYER_SPEED / 2;	//�����ĕX�Ȃ犊�炷
					if (Map_GetPlayerTile_RightDown(Player, Map) == ICE_GROUND) {
						Player->animator.ice = false;
						Player->animator.count = PLAYER_SPEED / 2;
						Player->mappos.RightDown++;
					}
				}//�C�[�W���O�̈�ԑ������x�Ŋ��点��
				Player->posX += (Ice_Easing((double)(PLAYER_SPEED / 2) / (double)PLAYER_SPEED) - Ice_Easing((double)((PLAYER_SPEED / 2) - 1) / (double)PLAYER_SPEED))*MAP_LENGTH;
				Player->posY -= (Ice_Easing((double)(PLAYER_SPEED / 2) / (double)PLAYER_SPEED) - Ice_Easing((double)((PLAYER_SPEED / 2) - 1) / (double)PLAYER_SPEED))*MAP_LENGTH;
				Player->animator.count++;
			}
			break;
		case LEFT_DOWN:
			if (Player->mappos.LeftDown + 1 == MAP_EDGE ||
				Map_GetPlayerTile_LeftDown(Player, Map) == -1 ||
				Map_GetPlayerTile_LeftDown(Player, Map) == RIGHTUP_SLOPE ||
				Map_GetPlayerTile_LeftDown(Player, Map) == LEFTUP_SLOPE ||
				Map_GetPlayerTile_LeftDown(Player, Map) == STONE ||
				(Map_GetPlayerTile_LeftDown(Player, Map) == GOAL && Player->IsEnemy == true) ||
				(Map_GetPlayerTile_LeftDown(Player, Map) == GOAL_LATER && Player->IsEnemy == true))
					Player->animator.ice = true;
			if (Player->animator.count < PLAYER_SPEED / 2 || Player->animator.ice == true) {
				double tmp = (double)Player->animator.count / (double)PLAYER_SPEED;
				double tmp1 = 0;
				if (Player->animator.count != 0)
					tmp1 = (double)(Player->animator.count - 1) / (double)PLAYER_SPEED;
				Player->posX -= (Ice_Easing(tmp) - Ice_Easing(tmp1))*MAP_LENGTH;
				Player->posY -= (Ice_Easing(tmp) - Ice_Easing(tmp1))*MAP_LENGTH;
				Player->animator.count++;
				if (Player->animator.count == PLAYER_SPEED) {	//�~�߂�
					if (Map_GetPlayerTile_LeftDown(Player, Map) != RIGHTUP_SLOPE) {
						Player->animator.count = 0;
						Player->animator.ice = false;
						Player->animator.isActive = false;
						Player->direction = NULL_WAY;
					}
					else {
						Player->animator.ice = false;
						Player->animator.count = 0;
					}
					bool mapedge = Player->mappos.LeftDown + 1 != MAP_EDGE;
					bool mapout = Map_GetPlayerTile_LeftDown(Player, Map) != -1;
					bool mapslope = Map_GetPlayerTile_LeftDown(Player, Map) != LEFTUP_SLOPE;
					bool mapstone = Map_GetPlayerTile_LeftDown(Player, Map) != STONE;
					bool enemygoal = Map_GetPlayerTile_LeftDown(Player, Map) == GOAL && Player->IsEnemy == true;
					bool enemygoallater = Map_GetPlayerTile_LeftDown(Player, Map) == GOAL_LATER && Player->IsEnemy == true;
					if (mapedge && mapout && mapslope && mapstone)
						Player->mappos.LeftDown++;
					if (enemygoal || enemygoallater)
						Player->mappos.LeftDown--;
					if (Map_GetPlayerTile(Player, Map) == GOAL || Map_GetPlayerTile(Player, Map) == GOAL_LATER)
						Player->Goalfrg = true;
					if (Map_GetPlayerTile(Player, Map) == GOAL && Player->IsEnemy == false)
						Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(8, 0);
					if (Map_GetPlayerTile(Player, Map) == ITEM_FACE) {
						if (Player->Item_Arm == false) {	//�A�C�e���͓�����2���ĂȂ�
							Player->Item_Face = true;
							Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(1, 0);
						}
					}
					if (Map_GetPlayerTile(Player, Map) == ITEM_ARM) {
						if (Player->Item_Face == false) {	//�A�C�e���͓�����2���ĂȂ�
							Player->Item_Arm = true;
							Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(1, 0);
						}
					}
				}
			}
			else {
				if (Player->animator.count == PLAYER_SPEED + EASING_OFFSET) {//�����̃C�[�W���O
					Player->animator.ice = true;
					Player->animator.count = PLAYER_SPEED / 2;	//�����ĕX�Ȃ犊�炷
					if (Map_GetPlayerTile_LeftDown(Player, Map) == ICE_GROUND) {
						Player->animator.ice = false;
						Player->animator.count = PLAYER_SPEED / 2;
						Player->mappos.LeftDown++;
					}
				}//�C�[�W���O�̈�ԑ������x�Ŋ��点��
				Player->posX -= (Ice_Easing((double)(PLAYER_SPEED / 2) / (double)PLAYER_SPEED) - Ice_Easing((double)((PLAYER_SPEED / 2) - 1) / (double)PLAYER_SPEED))*MAP_LENGTH;
				Player->posY -= (Ice_Easing((double)(PLAYER_SPEED / 2) / (double)PLAYER_SPEED) - Ice_Easing((double)((PLAYER_SPEED / 2) - 1) / (double)PLAYER_SPEED))*MAP_LENGTH;
				Player->animator.count++;
			}
			break;

		case LEFT_UP:
			if (Player->mappos.RightDown - 1 == -1 ||
				Map_GetPlayerTile_LeftUp(Player, Map) == -1 || 
				Map_GetPlayerTile_LeftUp(Player, Map) == STONE || 
				(Map_GetPlayerTile_LeftUp(Player, Map) == GOAL && Player->IsEnemy == true) || 
				(Map_GetPlayerTile_LeftUp(Player, Map) == GOAL_LATER && Player->IsEnemy == true))
				Player->animator.ice = true;
			if (Player->animator.count < PLAYER_SPEED / 2 || Player->animator.ice == true) {
				double tmp = (double)Player->animator.count / (double)PLAYER_SPEED;
				double tmp1 = 0;
				if (Player->animator.count != 0)
					tmp1 = (double)(Player->animator.count - 1) / (double)PLAYER_SPEED;
				Player->posX -= (Ice_Easing(tmp) - Ice_Easing(tmp1))*MAP_LENGTH;
				Player->posY += (Ice_Easing(tmp) - Ice_Easing(tmp1))*MAP_LENGTH;
				Player->animator.count++;
				if (Player->animator.count == PLAYER_SPEED) {	//�~�߂�
					Player->direction = NULL_WAY;
					Player->animator.count = 0;
					Player->animator.ice = false;
					Player->animator.isActive = false;

					bool mapedge = Player->mappos.RightDown + 1 != MAP_EDGE;
					bool mapout = Map_GetPlayerTile_LeftUp(Player, Map) != -1;
					bool mapslope = Map_GetPlayerTile_LeftUp(Player, Map) != RIGHTUP_SLOPE;
					bool mapstone = Map_GetPlayerTile_LeftUp(Player, Map) != STONE;
					bool enemygoal = Map_GetPlayerTile_LeftUp(Player, Map) == GOAL && Player->IsEnemy == true;
					bool enemygoallater = Map_GetPlayerTile_LeftUp(Player, Map) == GOAL_LATER && Player->IsEnemy == true;
					if (mapedge && mapout && mapslope && mapstone)
						Player->mappos.RightDown--;
					if (enemygoal || enemygoallater)
						Player->mappos.RightDown++;
					if (Map_GetPlayerTile(Player, Map) == GOAL || Map_GetPlayerTile(Player, Map) == GOAL_LATER)
						Player->Goalfrg = true;
					if (Map_GetPlayerTile(Player, Map) == GOAL && Player->IsEnemy == false)
						Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(8, 0);
					if (Map_GetPlayerTile(Player, Map) == ITEM_FACE) {
						if (Player->Item_Arm == false) {	//�A�C�e���͓�����2���ĂȂ�
							Player->Item_Face = true;
							Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(1, 0);
						}
					}
					if (Map_GetPlayerTile(Player, Map) == ITEM_ARM) {
						if (Player->Item_Face == false) {	//�A�C�e���͓�����2���ĂȂ�
							Player->Item_Arm = true;
							Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(1, 0);
						}
					}
				}
			}
			else {
				if (Player->animator.count == PLAYER_SPEED + EASING_OFFSET) {//�����̃C�[�W���O
					Player->animator.ice = true;
					Player->animator.count = PLAYER_SPEED / 2;	//�����ĕX�Ȃ犊�炷
					if (Map_GetPlayerTile_LeftUp(Player, Map) == ICE_GROUND) {
						Player->animator.ice = false;
						Player->animator.count = PLAYER_SPEED / 2;
						Player->mappos.RightDown--;
					}
				}//�C�[�W���O�̈�ԑ������x�Ŋ��点��
				Player->posX -= (Ice_Easing((double)(PLAYER_SPEED / 2) / (double)PLAYER_SPEED) - Ice_Easing((double)((PLAYER_SPEED / 2) - 1) / (double)PLAYER_SPEED))*MAP_LENGTH;
				Player->posY += (Ice_Easing((double)(PLAYER_SPEED / 2) / (double)PLAYER_SPEED) - Ice_Easing((double)((PLAYER_SPEED / 2) - 1) / (double)PLAYER_SPEED))*MAP_LENGTH;
				Player->animator.count++;
			}
			break;

		case RIGHT_UP:
			if (Player->mappos.LeftDown - 1 == -1 ||
				Map_GetPlayerTile_RightUp(Player, Map) == -1 ||
				Map_GetPlayerTile_RightUp(Player, Map) == STONE || 
				(Map_GetPlayerTile_RightUp(Player, Map) == GOAL && Player->IsEnemy == true) || 
				(Map_GetPlayerTile_RightUp(Player, Map) == GOAL_LATER && Player->IsEnemy == true))
				Player->animator.ice = true;
			if (Player->animator.count < PLAYER_SPEED / 2 || Player->animator.ice == true) {
				double tmp = (double)Player->animator.count / (double)PLAYER_SPEED;
				double tmp1 = 0;
				if (Player->animator.count != 0)
					tmp1 = (double)(Player->animator.count - 1) / (double)PLAYER_SPEED;
				Player->posX += (Ice_Easing(tmp) - Ice_Easing(tmp1))*MAP_LENGTH;
				Player->posY += (Ice_Easing(tmp) - Ice_Easing(tmp1))*MAP_LENGTH;
				Player->animator.count++;
				if (Player->animator.count == PLAYER_SPEED) {	//�~�߂�
					Player->direction = NULL_WAY;
					Player->animator.count = 0;
					Player->animator.ice = false;
					Player->animator.isActive = false;

					bool mapedge = Player->mappos.LeftDown + 1 != MAP_EDGE;
					bool mapout = Map_GetPlayerTile_RightUp(Player, Map) != -1;
					bool mapslope = Map_GetPlayerTile_RightUp(Player, Map) != RIGHTUP_SLOPE;
					bool mapstone = Map_GetPlayerTile_RightUp(Player, Map) != STONE;
					bool enemygoal = Map_GetPlayerTile_RightUp(Player, Map) == GOAL && Player->IsEnemy == true;
					bool enemygoallater = Map_GetPlayerTile_RightUp(Player, Map) == GOAL_LATER && Player->IsEnemy == true;
					if (mapedge && mapout && mapslope && mapstone)
						Player->mappos.LeftDown--;
					if (enemygoal || enemygoallater)
						Player->mappos.LeftDown++;
					if (Map_GetPlayerTile(Player, Map) == GOAL || Map_GetPlayerTile(Player, Map) == GOAL_LATER)
						Player->Goalfrg = true;
					if (Map_GetPlayerTile(Player, Map) == GOAL && Player->IsEnemy == false)
						Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(8, 0);
					if (Map_GetPlayerTile(Player, Map) == ITEM_FACE) {
						if (Player->Item_Arm == false) {	//�A�C�e���͓�����2���ĂȂ�
							Player->Item_Face = true;
							Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(1, 0);
						}
					}
					if (Map_GetPlayerTile(Player, Map) == ITEM_ARM) {
						if (Player->Item_Face == false) {	//�A�C�e���͓�����2���ĂȂ�
							Player->Item_Arm = true;
							Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(1, 0);
						}
					}
				}
			}
			else {
				if (Player->animator.count == PLAYER_SPEED + EASING_OFFSET) {//�����̃C�[�W���O
					Player->animator.ice = true;
					Player->animator.count = PLAYER_SPEED / 2;	//�����ĕX�Ȃ犊�炷
					if (Map_GetPlayerTile_RightUp(Player, Map) == ICE_GROUND) {
						Player->animator.ice = false;
						Player->animator.count = PLAYER_SPEED / 2;
						Player->mappos.LeftDown--;
					}
				}//�C�[�W���O�̈�ԑ������x�Ŋ��点��
				Player->posX += (Ice_Easing((double)(PLAYER_SPEED / 2) / (double)PLAYER_SPEED) - Ice_Easing((double)((PLAYER_SPEED / 2) - 1) / (double)PLAYER_SPEED))*MAP_LENGTH;
				Player->posY += (Ice_Easing((double)(PLAYER_SPEED / 2) / (double)PLAYER_SPEED) - Ice_Easing((double)((PLAYER_SPEED / 2) - 1) / (double)PLAYER_SPEED))*MAP_LENGTH;
				Player->animator.count++;
			}
			break;
		}
	} //�y�̎�
	else if (Map_GetPlayerTile(Player, Map) == SOIL_GROUND) {
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
	} //�E���̎�
	else if (Map_GetPlayerTile(Player, Map) == RIGHTUP_SLOPE) {
		if (Player->direction == LEFT_DOWN) {
			if (Player->animator.count != PLAYER_SPEED) {
				double tmp = (double)Player->animator.count / (double)PLAYER_SPEED;
				double tmp1 = 0;
				if (Player->animator.count != 0)
					tmp1 = (double)(Player->animator.count - 1) / (double)PLAYER_SPEED;
				Player->posX -= (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH * 2;
				Player->posY -= (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH * 1.55f * 2;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->mappos.LeftDown++;
				Player->mappos.Height--;
				Player->animator.count = 0;
				Player->animator.isActive = false;
			}
		}
		else {
			switch (Player->direction) {
			case RIGHT_DOWN:
				Player->mappos.RightDown--;
				Player->direction = NULL_WAY;
				Player->animator.isActive = false;
				Player->animator.count = 0;
				return;
			case LEFT_UP:
				Player->mappos.RightDown++;
				Player->direction = NULL_WAY;
				Player->animator.isActive = false;
				Player->animator.count = 0;
				return;
			}
		}
	} //�����̎�
	else if (Map_GetPlayerTile(Player, Map) == LEFTUP_SLOPE) {
		if (Player->direction == RIGHT_DOWN) {
			if (Player->animator.count != PLAYER_SPEED) {
				double tmp = (double)Player->animator.count / (double)PLAYER_SPEED;
				double tmp1 = 0;
				if (Player->animator.count != 0)
					tmp1 = (double)(Player->animator.count - 1) / (double)PLAYER_SPEED;
				Player->posX += (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH * 2;
				Player->posY -= (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH * 1.55f * 2;
				Player->animator.count++;
			}
			else {
				Player->direction = NULL_WAY;
				Player->mappos.RightDown++;
				Player->mappos.Height--;
				Player->animator.count = 0;
				Player->animator.isActive = false;
			}
		}
		else {
			switch (Player->direction)
			{
			case RIGHT_UP:
				Player->mappos.LeftDown++;
				Player->direction = NULL_WAY;
				Player->animator.isActive = false;
				Player->animator.count = 0;
				return;
			case LEFT_DOWN:
				Player->mappos.LeftDown--;
				Player->direction = NULL_WAY;
				Player->animator.isActive = false;
				Player->animator.count = 0;
				return;
			}
		}
	}
	//�΂̎�
	else if (Map_GetPlayerTile(Player, Map) == STONE) {
		switch (Player->direction) {
		case RIGHT_DOWN:
			Player->mappos.RightDown--;
			Player->animator.isActive = false;
			break;
		case LEFT_DOWN:
			Player->mappos.LeftDown--;
			Player->animator.isActive = false;
			break;
		case LEFT_UP:
			Player->mappos.RightDown++;
			Player->animator.isActive = false;
			break;
		case RIGHT_UP:
			Player->mappos.LeftDown++;
			Player->animator.isActive = false;
			break;
		}
		Player->direction = NULL_WAY;
	}
	//�S�[���̎�
	else if (Map_GetPlayerTile(Player, Map) == GOAL|| Map_GetPlayerTile(Player, Map) == GOAL_LATER) {
	//�G�̓S�[���ɓ���Ȃ�
	if (Player->IsEnemy == true) {
		switch (Player->direction) {
		case RIGHT_DOWN:
			Player->mappos.RightDown--;
			Player->animator.isActive = false;
			break;
		case LEFT_DOWN:
			Player->mappos.LeftDown--;
			Player->animator.isActive = false;
			break;
		case LEFT_UP:
			Player->mappos.RightDown++;
			Player->animator.isActive = false;
			break;
		case RIGHT_UP:
			Player->mappos.LeftDown++;
			Player->animator.isActive = false;
			break;
		}
		Player->direction = NULL_WAY;
	}
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
				Player->Goalfrg = true;//�v���C���[�𓮂��Ȃ�����
				delete Player->texture;
				Player->texture = new Sprite("assets/yukidaruma.png", 27, 1);
				Player->posY += 0.225f;
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
				Player->animator.isActive = false;
				Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(8, 0);
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
				Player->Goalfrg = true;//�v���C���[�𓮂��Ȃ�����
				delete Player->texture;
				Player->texture = new Sprite("assets/yukidaruma.png", 27, 1);
				Player->posY += 0.225f;
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
				Player->animator.isActive = false;
				Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(8, 0);
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
				Player->Goalfrg = true;//�v���C���[�𓮂��Ȃ�����
				delete Player->texture;
				Player->texture = new Sprite("assets/yukidaruma.png", 27, 1);
				Player->posY += 0.225f;
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
				Player->animator.isActive = false;
				Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(8, 0);
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
				Player->Goalfrg = true;//�v���C���[�𓮂��Ȃ�����
				delete Player->texture;
				Player->texture = new Sprite("assets/yukidaruma.png", 27, 1);
				Player->posY += 0.225f;
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
				Player->animator.isActive = false;
				Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(8, 0);
			}
			break;
		}
	}
	//��A�C�e���̎�
	else if (Map_GetPlayerTile(Player, Map) == ITEM_FACE) {
	if (Player->Item_Arm == false)	//�A�C�e���͓�����2���ĂȂ�
			Player->Item_Face = true;
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
				if (Player->Item_Arm == false)
					Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(1, 0);
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
				if (Player->Item_Arm == false)
					Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(1, 0);
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
				if (Player->Item_Arm == false)
					Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(1, 0);
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
				if (Player->Item_Arm == false)
					Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(1, 0);
			}
			break;
		}
	}
	//�r�A�C�e���̎�
	else if (Map_GetPlayerTile(Player, Map) == ITEM_ARM) {
	if (Player->Item_Face == false)	//�A�C�e���͓�����2���ĂȂ�
			Player->Item_Arm = true;
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
				if (Player->Item_Face == false)
					Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(1, 0);
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
				if (Player->Item_Face == false)
					Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(1, 0);
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
				if (Player->Item_Face == false)
					Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(1, 0);
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
				if (Player->Item_Face == false)
					Map[Player->mappos.RightDown + MAP_EDGE * Player->mappos.LeftDown + 100 * Player->mappos.Height].texture->SetPart(1, 0);
			}
			break;
		}
	}
}