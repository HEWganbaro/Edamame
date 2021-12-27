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
#define MAX_OBJECT   309

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//ID3D11Buffer* gpVertexBuffer;  // ���_�o�b�t�@�p�̕ϐ�
//ID3D11ShaderResourceView* gpTexture; // �e�N�X�`���p�ϐ�

	//�X�e�[�W��[�X�e�[�W][����][����][�E��]
int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE];

GameObject gObjects[MAX_OBJECT];  // �I�u�W�F�N�g�z��
GameObject* gPlayer = gObjects + 300;
GameObject* NoHeight = gObjects + 301;
GameObject* NoLeftDown = gObjects + 302;
GameObject* NoRightDown = gObjects + 303;
GameObject* tile = gObjects + 304;
GameObject* SnowBall = gObjects + 305;
GameObject* gEnemy = gObjects + 306;
GameObject* gShield = gObjects + 307;
GameObject* gGoal = gObjects + 308;


GameObject gBackGround;				//�w�i
//GameObject��ǉ�����Ƃ��͕K��MAX_OBJECT�̐������킹�Ȃ��ƃG���[���o���I

//*****************************************************************************
// �֐��̒�`�@��������@��
//*****************************************************************************

BOOL Game_Initialize()
{
	// �Q�[�����Ԃ̏����������AFPS��60�ɐݒ肵���B
	GameTimer_Initialize(60);
	
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

	//�v���C���[������
	Player_Initialize(gPlayer);

	//�v���C���[�ꏊ�w��
	Player_SetLocation(gPlayer, gObjects, 0, 5, 5);

	//��ʂ̏�����
	SnowBall_Initialize(SnowBall);

	//��ʂ̏ꏊ�w��
	SnowBall_SetLocation(SnowBall, gObjects, 0, 6, 6);

	//�G�̏�����
	Enemy_Initialize(gEnemy);

	//�G�̏ꏊ�w��
	Enemy_SetLocation(gEnemy, gObjects, 0, 4, 4);

	//�Օ��̏�����
	Shield_Initialize(gShield);

	//�Օ��̏ꏊ�w��
	Shield_SetLocation(gShield, gObjects, 0, 3, 6);

	//�Օ��̏�����
	Goal_Initialize(gGoal);

	//�Օ��̏ꏊ�w��
	Goal_SetLocation(gGoal, gObjects, 0, 4, 5);

	//�f�o�b�N�p
	NoHeight->textuer = new Sprite("assets/No.png", 13, 7);
	NoHeight->textuer->SetSize(80, 80);
	NoLeftDown->textuer = new Sprite("assets/No.png", 13, 7);
	NoLeftDown->textuer->SetSize(80, 80);
	NoRightDown->textuer = new Sprite("assets/No.png", 13, 7);
	NoRightDown->textuer->SetSize(80, 80);
	tile->textuer = new Sprite("assets/MapSeat.png", 6, 1);
	tile->textuer->SetSize(200, 200);
	gBackGround.textuer = new Sprite("assets/BackGround.png", 1, 1);
	gBackGround.textuer->SetSize(1280*2, 720*2);

	return TRUE;
}


// �Q�[�����[�v���Ɏ��s�������A�Q�[���̏����������֐�
BOOL Game_Update()
{
	Input_Update();  // ���̃Q�[���Ŏg���L�[�̉�����Ԃ𒲂ׂĕ�

	//�f�o�b�N�p
	NoHeight->textuer->SetPart(gPlayer->mappos.Height, 0);
	NoHeight->posX = 0.5f;
	NoHeight->posY = 0.5f;
	NoLeftDown->textuer->SetPart(gPlayer->mappos.LeftDown, 0);
	NoLeftDown->posX = 0.6f;
	NoLeftDown->posY = 0.5f;
	NoRightDown->textuer->SetPart(gPlayer->mappos.RightDown, 0);
	NoRightDown->posX = 0.7f;
	NoRightDown->posY = 0.5f;
	tile->textuer->SetPart(Map_GetPlayerTile(gPlayer, MapChip), 0);
	tile->posX = 0.3;
	tile->posY = 0.6;
	gBackGround.posX = -1;
	gBackGround.posY = 1;

	Map_Update(gObjects, MapChip);	//�}�b�v�ύX����

	Player_Input(gPlayer, MapChip);	//�v���C���[�ړ�

	SnowBall_Hit(gPlayer, SnowBall); //��ʓ����蔻��

	SnowBall_Update(SnowBall, gObjects, MapChip);

	Enemy_Hit(gEnemy, SnowBall);

	if (gEnemy->direction == NULL_WAY)
	{
		//�G�̏���
		Enemy_Move_Circle(gEnemy, SnowBall);
	}

	if (gEnemy->enemyeye == ENEMYEYE_IN)
	{
		//�Օ��ł̃w�C�g���炵
		Shield_Cancel(gShield, SnowBall, gEnemy);
	}

	//�G�̐ڋ�
	Enemy_Move_Chase(gEnemy, SnowBall);

	//Shield_Hit(gShield, gPlayer);

	// �I�u�W�F�N�g�z���XY�v�Z�AUV�v�Z�A���_�z��ւ̓K�p���ꊇ����
	for (int i = 0; i < MAX_OBJECT; i++) {
		//GameObject�Ɖ摜�̍��W�����킹��
		GameObject_DrowUpdate(&gObjects[i]);
	}
	GameObject_DrowUpdate(&gBackGround);

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
	gBackGround.textuer->Draw();
	for (int i = 0; i < MAX_OBJECT; i++)
		gObjects[i].textuer->Draw();

	// �_�u���E�o�b�t�@�̃f�B�X�v���C�̈�ւ̃R�s�[����
	Direct3D_GetSwapChain()->Present(0, 0);
}

//�����GameObject�͂�����delete���悤�I
void Game_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM000));

	delete gBackGround.textuer;
	for (int i = 0; i < MAX_OBJECT; i++) {
		delete gObjects[i].textuer;
		gObjects[i].posX = 0;
		gObjects[i].posY = 0;
	}
}
