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
	// �}�b�v����
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

int Map_GetPlayerTile(GameObject * Player, GameObject * Map)
{
	return Map[Player->mappos.Height * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown].textuer->GetPart();
}

int Map_GetPlayerTile_LeftUp(GameObject * Player, GameObject * Map)
{
	return Map[Player->mappos.Height * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown - 1].textuer->GetPart();
}

int Map_GetPlayerTile_RightDown(GameObject * Player, GameObject * Map)
{
	return Map[Player->mappos.Height * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown + 1].textuer->GetPart();
}

int Map_GetPlayerTile_LeftDown(GameObject * Player, GameObject * Map)
{
	return Map[Player->mappos.Height * 100 + (Player->mappos.LeftDown + 1) * 10 + Player->mappos.RightDown].textuer->GetPart();
}

int Map_GetPlayerTile_RightUp(GameObject * Player, GameObject * Map)
{
	return Map[Player->mappos.Height * 100 + (Player->mappos.LeftDown - 1) * 10 + Player->mappos.RightDown].textuer->GetPart();
}

int Map_GetPlayerTile_Top(GameObject * Player, GameObject * Map)
{
	return Map[(Player->mappos.Height + 1) * 100 + Player->mappos.LeftDown * 10 + Player->mappos.RightDown].textuer->GetPart();
}

//�v���C���[�̃^�C����Ԃ��֐�
void Map_Update(GameObject * Map, int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE])
{
	//CSV�̏��Ԓʂ�ɂȂ�
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
//�}�b�v�ɂ���I�u�W�F�N�g�͑S�Ă�����g���ē������Ăق���
//���� (�����������Q�[���I�u�W�F�N�g�AMapChip)
//�߂�l ����
//////////////////////////////////////////////////////////
void MapMove_Update(GameObject * Player, GameObject* Map) {
	// �}�b�v�O�ɂ͂����Ȃ�
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
				Player->posY += (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH * 1.75f * 2;
				Player->animator.count++;
			}
			else {
				Player->mappos.Height++;
				Player->mappos.LeftDown--;
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
			}
		} //�����̎�
		else if (Map_GetPlayerTile_Top(Player, Map) == LEFTUP_SLOPE && Player->direction == LEFT_UP) {
			if (Player->animator.count != PLAYER_SPEED) {
				double tmp = (double)Player->animator.count / (double)PLAYER_SPEED;
				double tmp1 = 0;
				if (Player->animator.count != 0)
					tmp1 = (double)(Player->animator.count - 1) / (double)PLAYER_SPEED;
				Player->posX -= (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH * 2;
				Player->posY += (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH * 1.75f * 2;
				Player->animator.count++;
			}
			else {
				Player->mappos.Height++;
				Player->mappos.RightDown--;
				Player->direction = NULL_WAY;
				Player->animator.count = 0;
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
				Map_GetPlayerTile_RightDown(Player, Map) == LEFTUP_SLOPE || Map_GetPlayerTile_RightDown(Player, Map) == RIGHTUP_SLOPE)
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
					if(Map_GetPlayerTile_RightDown(Player, Map) != LEFTUP_SLOPE)
						Player->direction = NULL_WAY;
					Player->animator.count = 0;
					Player->animator.ice = false;
					if (Player->mappos.RightDown + 1 != MAP_EDGE &&
						Map_GetPlayerTile_RightDown(Player, Map) != -1 &&//�}�b�v�O�̎��͓������Ȃ�
					    /*Map_GetPlayerTile_RightDown(Player, Map) != LEFTUP_SLOPE &&*/ Map_GetPlayerTile_RightDown(Player, Map) != RIGHTUP_SLOPE)
					Player->mappos.RightDown++;
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
				Map_GetPlayerTile_LeftDown(Player, Map) == RIGHTUP_SLOPE || Map_GetPlayerTile_LeftDown(Player, Map) == LEFTUP_SLOPE)
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
					if (Map_GetPlayerTile_LeftDown(Player, Map) != RIGHTUP_SLOPE)
						Player->direction = NULL_WAY;
					Player->animator.count = 0;
					Player->animator.ice = false;
					if (Player->mappos.LeftDown + 1 != MAP_EDGE &&
						Map_GetPlayerTile_LeftDown(Player, Map) != -1 &&
						/*Map_GetPlayerTile_LeftDown(Player, Map) != RIGHTUP_SLOPE &&*/ Map_GetPlayerTile_LeftDown(Player, Map) != LEFTUP_SLOPE)
						Player->mappos.LeftDown++;
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
			if (Player->mappos.RightDown - 1 == -1 || Map_GetPlayerTile_LeftUp(Player, Map) == -1)
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
					if (Player->mappos.RightDown - 1 != -1) {
						if (Map_GetPlayerTile_LeftUp(Player, Map) != -1)
							Player->mappos.RightDown--;
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
			if (Player->mappos.LeftDown - 1 == -1 || Map_GetPlayerTile_RightUp(Player, Map) == -1)
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
					if (Player->mappos.LeftDown - 1 != -1) {
						if (Map_GetPlayerTile_RightUp(Player, Map) != -1)
							Player->mappos.LeftDown--;
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
				Player->posY -= (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH * 1.75f * 2;
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
	} //�����̎�
	else if (Map_GetPlayerTile(Player, Map) == LEFTUP_SLOPE) {
		if (Player->direction == RIGHT_DOWN) {
			if (Player->animator.count != PLAYER_SPEED) {
				double tmp = (double)Player->animator.count / (double)PLAYER_SPEED;
				double tmp1 = 0;
				if (Player->animator.count != 0)
					tmp1 = (double)(Player->animator.count - 1) / (double)PLAYER_SPEED;
				Player->posX += (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH * 2;
				Player->posY -= (Move_Easing(tmp) - Move_Easing(tmp1))*MAP_LENGTH * 1.75f * 2;
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