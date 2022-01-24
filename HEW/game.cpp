//*****************************************************************************
// DX21�@�T���v���\�[�X
// �Q�[���̃��C���ƂȂ鏈���������Ă����\�[�X�t�@�C��
//*****************************************************************************

#include "game.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

// ���_�P�������\���\����
//struct VERTEX_POSTEX {
//	float x, y, z;  // ���_�̈ʒu
//
//	float u, v;  // �e�N�X�`����UV���W
//};

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//#define MAX_SPRITE  2560 //(���\�K��)
//// �|���S���Q�łP�̎l�p�`�i�X�v���C�g�j�B�|���S���͂R���_�Ȃ̂ŁA�P�X�v���C�g�͂U���_�B
//#define VERTEX_PER_SPRITE  (3*2)
//#define VERTEX_BUFFER_SIZE  (MAX_SPRITE*sizeof(VERTEX_POSTEX)*VERTEX_PER_SPRITE)

// �I�u�W�F�N�g�̔����� (���������菭�Ȃ������肷��ƃG���[���o��)
#define MAX_OBJECT   304

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//ID3D11Buffer* gpVertexBuffer;  // ���_�o�b�t�@�p�̕ϐ�
//ID3D11ShaderResourceView* gpTexture; // �e�N�X�`���p�ϐ�

	//�X�e�[�W��[�X�e�[�W][����][����][�E��]
int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE];
vector<MapPos> StoneMap;

GameObject gObjects[MAX_OBJECT];  // �I�u�W�F�N�g�z��

GameObject* NoHeight = gObjects + 300;
GameObject* NoLeftDown = gObjects + 301;
GameObject* NoRightDown = gObjects + 302;
GameObject* tile = gObjects + 303;

GameObject gPlayer1;
GameObject gPlayer2;
GameObject gEnemy;
vector<GameObject> genemy;
GameObject gBackGround;				//�w�i

GameObject gEffect[4];

//GameObject��ǉ�����Ƃ��͕K��MAX_OBJECT�̐������킹�Ȃ��ƃG���[���o���I

//*****************************************************************************
// �֐��̒�`�@��������@��
//*****************************************************************************

BOOL Game_Initialize()
{
	// �Q�[�����Ԃ̏����������AFPS��60�ɐݒ肵���B
	GameTimer_Initialize(60);
	/* �����n��̕ύX */
	srand((unsigned)time(NULL));
	
	//BGM�Đ�
	XA_Play(SOUND_LABEL(SOUND_LABEL_BGM000));

	// CSV��z��Ɋi�[
	ifstream ifs("assets/data.csv");
	for (int l = 0; l < MAP_STAGE; l++) {
		string line;
		int j = 0;
		int k = 0;
		bool end = false; //�����̃t���O �iCSV�ł�-9�j
		bool stage = false;	//�X�e�[�W�̃t���O (CSV�ł�-99)
		while (getline(ifs, line)) {

			vector<string> strvec = split(line, ',');

			for (int i = 0; i < strvec.size(); i++) {
				if (-9 == stoi(strvec.at(i))) {
					end = true;
					break;
				}
				if (-99 == stoi(strvec.at(i))) {
					end = true;
					break;
				}
				MapChip[l][k][j][i] = stoi(strvec.at(i));
			}
			j++;
			if (end == true) {
				k++;
				j = 0;
				end = false;
			}
			if (stage == true) {
				l++;
				j = 0;
				k = 0;
				stage = false;
			}
		}
	}

	// �}�b�v����
	Map_Initialize(gObjects);

	//�G�t�F�N�g����
	for (int i = 0; i < 4; i++) {
		Effect_Init(&gEffect[i]);
	}

	//��ʂ̏�����
	Player_Initialize(&gPlayer1);
	Player_Initialize(&gPlayer2);

	////��ʂ̏ꏊ�w��
	Player_SetLocation(&gPlayer1, gObjects, 0, 5, 5);
	Player_SetLocation(&gPlayer2, gObjects, 0, 6, 6);

	//�G�̏�����
	Enemy_Initialize(&gEnemy);

	//�G�̏ꏊ�w��
	Enemy_SetLocation(&gEnemy, gObjects, 0, 4, 4);
	//�G�̏ꏊ���w�肵�Ă���
	//switch (switch_on)
	//{
	//default:
	//	break;
	//}

	//�w�i�`��
	gBackGround.texture = new Sprite("assets/BackGround.png", 1, 1);
	gBackGround.texture->SetSize(1280 * 2, 720 * 2);
	gBackGround.posX = -1;
	gBackGround.posY = 1;

	//�f�o�b�N�p
	NoHeight->texture = new Sprite("assets/dotFont.png", 16, 8);
	NoHeight->texture->SetSize(80, 160);
	NoLeftDown->texture = new Sprite("assets/dotFont.png", 16, 8);
	NoLeftDown->texture->SetSize(80, 160);
	NoRightDown->texture = new Sprite("assets/dotFont.png", 16, 8);
	NoRightDown->texture->SetSize(80, 160);
	tile->texture = new Sprite("assets/Mapseat_v2.png", 7, 1);
	tile->texture->SetSize(200, 200);

	//�}�b�v�ύX
	Map_Update(gObjects, &StoneMap, MapChip);	

	return TRUE;
}


// �Q�[�����[�v���Ɏ��s�������A�Q�[���̏����������֐�
BOOL Game_Update()
{
	Input_Update();  // ���̃Q�[���Ŏg���L�[�̉�����Ԃ𒲂ׂĕ�

	//�f�o�b�N�p
	NoHeight->texture->SetPart(gPlayer1.mappos.Height, 0);
	NoHeight->posX = 0.5f;
	NoHeight->posY = 0.5f;
	NoLeftDown->texture->SetPart(gPlayer1.mappos.LeftDown, 1);
	NoLeftDown->posX = 0.6f;
	NoLeftDown->posY = 0.5f;
	NoRightDown->texture->SetPart(gPlayer1.mappos.RightDown, 2);
	NoRightDown->posX = 0.7f;
	NoRightDown->posY = 0.5f;
	tile->texture->SetPart(Map_GetPlayerTile(&gPlayer1, gObjects), 0);
	tile->posX = 0.3;
	tile->posY = 0.6;
	gBackGround.posX = -1;
	gBackGround.posY = 1;

	for (int i = 0; i < 4; i++) {
		Efffect_Move(&gEffect[i]);
	}

	switch (turn)
	{
	case PLAYER_TURN:
		//�v���C���[�ړ�
		gPlayer1.animator.isActive = true;
		gPlayer2.animator.isActive = true;
		Player_Input(&gPlayer1, &gPlayer2);	
		Player_Update(&gPlayer1, gObjects);
		Player_Update(&gPlayer2, gObjects);
		if (gPlayer1.animator.isActive == false || gPlayer2.animator.isActive == false)
			turn = ENEMY_TURN;
		break;

	case ENEMY_TURN:
		//�G�ړ�
		if (gEnemy.direction == NULL_WAY) {
			//�G�̐ڋ�
			//Enemy_Move_Chase(&gEnemy, &gPlayer1, &gPlayer2);
			if (gEnemy.direction == NULL_WAY) {
				//�G�̏���
				Enemy_Move_Circle(&gEnemy);
			}
		}
		else {
			//�G�̈ړ�����
			MapMove_Update(&gEnemy, gObjects);
			if (gEnemy.direction == NULL_WAY)
				turn = ENV_TURN;
		}
		//�G�̃X�^��
		//Enemy_Stun(&gEnemy, &gPlayer1, &gPlayer2, gObjects, MapChip);
		break;

	case ENV_TURN:
		toIce(gObjects);
		break;
	}

	//if (gEnemy.enemyeye == ENEMYEYE_IN)
	//{
	//	//�Օ��ł̃w�C�g���炵
	//	for (int i = 0; i < StoneMap.size(); i++) {
	//		Shield_Cancel(&StoneMap[i], &gPlayer1, &gPlayer2, &gEnemy);
	//	}
	//}

	// �I�u�W�F�N�g�z���XY�v�Z�AUV�v�Z�A���_�z��ւ̓K�p���ꊇ����
	//GameObject�Ɖ摜�̍��W�����킹��
	for (int i = 0; i < MAX_OBJECT; i++) {
		GameObject_DrowUpdate(&gObjects[i]);
	}
	GameObject_DrowUpdate(&gPlayer1);
	GameObject_DrowUpdate(&gPlayer2);
	GameObject_DrowUpdate(&gEnemy);
	GameObject_DrowUpdate(&gBackGround);
	for (int i = 0; i < 4; i++) {
		GameObject_DrowUpdate(&gEffect[i]);
	}

	//�^�C�g���֖߂�t���O
	if (Input_GetKeyTrigger(VK_SPACE))
		return FALSE;
		
	return TRUE;
}

void Game_Draw()
{
	// ��ʃN���A�i�w��F�œh��Ԃ��j
	// �h��Ԃ��F�̎w��i�����F0.0f�`1.0f�j
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
	Direct3D_GetContext()->ClearRenderTargetView(Direct3D_GetRenderTargetView(), clearColor);

	//�Q�[���I�u�W�F�N�g��S���`�悷��
	gBackGround.texture->Draw();
	gEffect[0].texture->Draw();
	gEffect[1].texture->Draw();
	for (int i = 0; i < MAX_OBJECT; i++)
		gObjects[i].texture->Draw();
	gPlayer1.texture->Draw();
	gPlayer2.texture->Draw();
	gEnemy.texture->Draw();

	gEffect[2].texture->Draw();
	gEffect[3].texture->Draw();

	// �_�u���E�o�b�t�@�̃f�B�X�v���C�̈�ւ̃R�s�[����
	Direct3D_GetSwapChain()->Present(0, 0);
}

//�����GameObject�͂�����delete���悤�I
void Game_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM000));

	delete gPlayer1.texture;
	delete gPlayer2.texture;
	delete gEnemy.texture;
	delete gBackGround.texture;
	for (int i = 0; i < 4; i++)
		delete gEffect[i].texture;
	for (int i = 0; i < MAX_OBJECT; i++) {
		delete gObjects[i].texture;
		gObjects[i].posX = 0;
		gObjects[i].posY = 0;
	}

}
