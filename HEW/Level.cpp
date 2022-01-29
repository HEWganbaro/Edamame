#include "Level.h"
#include "MapGeneration.h"

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
//
//// �I�u�W�F�N�g�̔����� (���������菭�Ȃ������肷��ƃG���[���o��)
//#define MAX_OBJECT   308

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//ID3D11Buffer* gpVertexBuffer;  // ���_�o�b�t�@�p�̕ϐ�
//ID3D11ShaderResourceView* gpTexture; // �e�N�X�`���p�ϐ�

GameObject lBackGround;				//�w�i
GameObject gchoice;
GameObject groad;		//��
GameObject gstage1;
GameObject gstage2;
GameObject gstage3;
GameObject gstage4;
GameObject gstage5;
GameObject gstage6;
GameObject gstage7;
GameObject gstage8;
GameObject gstage9;
GameObject gstage10;
GameObject gcloud1;
GameObject gcloud2;
GameObject gcloud3;
GameObject gcloud4;
GameObject gcloud5;
GameObject gcloud6;
GameObject gcloud7;
GameObject gcloud8;
GameObject gcloud9;
GameObject gcloud10;


StageScore LevelScoreSheet[MAP_STAGE];
//GameObject��ǉ�����Ƃ��͕K��MAX_OBJECT�̐������킹�Ȃ��ƃG���[���o���I

//*****************************************************************************
// �֐��̒�`�@��������@��
//*****************************************************************************

BOOL Level_Initialize(StageScore score)
{
	// �Q�[�����Ԃ̏����������AFPS��60�ɐݒ肵���B
	GameTimer_Initialize(60);

	//BGM�Đ�
	XA_Play(SOUND_LABEL(SOUND_LABEL_BGM000));

	//�w�i
	lBackGround.texture = new Sprite("assets/level.png", 1, 1);
	lBackGround.texture->SetSize(1280 * 2, 720 * 2);
	lBackGround.posX = -1;
	lBackGround.posY = 1;

	gchoice.texture = new Sprite("assets/dotFont.png", 16, 8);
	gchoice.texture->SetSize(80, 160);
	gchoice.texture->SetPart(0, 0);
	gchoice.posX = 0.8f;
	gchoice.posY = 0.8f;

	groad.texture = new Sprite("assets/road.png", 1, 10);
	groad.texture->SetSize(1330 * 2, 720 * 2.3);

	gstage1.texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage1.texture->SetSize(320, 320);

	gstage2.texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage2.texture->SetSize(320, 320);

	gstage3.texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage3.texture->SetSize(320, 320);

	gstage4.texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage4.texture->SetSize(320, 320);

	gstage5.texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage5.texture->SetSize(320, 320);

	gstage6.texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage6.texture->SetSize(320, 320);

	gstage7.texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage7.texture->SetSize(320, 320);

	gstage8.texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage8.texture->SetSize(320, 320);

	gstage9.texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage9.texture->SetSize(320, 320);

	gstage10.texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage10.texture->SetSize(320, 320);

	gcloud1.texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud1.texture->SetSize(400, 160);

	gcloud2.texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud2.texture->SetSize(400, 160);

	gcloud3.texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud3.texture->SetSize(400, 160);

	gcloud4.texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud4.texture->SetSize(400, 160);

	gcloud5.texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud5.texture->SetSize(400, 160);

	gcloud6.texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud6.texture->SetSize(400, 160);

	gcloud7.texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud7.texture->SetSize(400, 160);

	gcloud8.texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud8.texture->SetSize(400, 160);

	gcloud9.texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud9.texture->SetSize(400, 160);

	gcloud10.texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud10.texture->SetSize(400, 160);

	//�X�R�A����
	if (score != TITLESCORE)
		LevelScoreSheet[stage - 1] = score;

	return TRUE;
}

BOOL Level_Update()
{
	Input_Update();  // ���̃Q�[���Ŏg���L�[�̉�����Ԃ𒲂ׂĕ�
	XINPUT_STATE state;
	XInputGetState(0, &state);

	groad.texture->SetPart(0, 0);
	groad.posX = -1.05f;
	groad.posY = 1.1f;

	gstage1.texture->SetPart(0, 0);
	gstage1.posX = -0.97f;
	gstage1.posY = 0.48f;

	gstage2.texture->SetPart(0, 0);
	gstage2.posX = -0.77f;
	gstage2.posY = -0.1f;

	gstage3.texture->SetPart(0, 0);
	gstage3.posX = -0.58f;
	gstage3.posY = 0.68f;

	gstage4.texture->SetPart(0, 0);
	gstage4.posX = -0.24f;
	gstage4.posY = 0.54f;

	gstage5.texture->SetPart(0, 0);
	gstage5.posX = -0.36f;
	gstage5.posY = -0.14f;

	gstage6.texture->SetPart(1, 0);
	gstage6.posX = 0.02f;
	gstage6.posY = -0.23f;

	gstage7.texture->SetPart(1, 0);
	gstage7.posX = 0.068f;
	gstage7.posY = 0.58f;

	gstage8.texture->SetPart(1, 0);
	gstage8.posX = 0.48f;
	gstage8.posY = 0.7f;

	gstage9.texture->SetPart(1, 0);
	gstage9.posX = 0.43f;
	gstage9.posY = 0.04f;

	gstage10.texture->SetPart(1, 0);
	gstage10.posX = 0.7f;
	gstage10.posY = -0.25f;

	gcloud1.texture->SetPart(0, 0);
	gcloud1.posX = -1.0f;
	gcloud1.posY = 0.19f;

	gcloud2.texture->SetPart(0, 0);
	gcloud2.posX = -0.8f;
	gcloud2.posY = -0.38f;

	gcloud3.texture->SetPart(0, 0);
	gcloud3.posX = -0.61f;
	gcloud3.posY = 0.4f;

	gcloud4.texture->SetPart(0, 0);
	gcloud4.posX = -0.27f;
	gcloud4.posY = 0.26f;

	gcloud5.texture->SetPart(0, 0);
	gcloud5.posX = -0.39f;
	gcloud5.posY = -0.42f;

	gcloud6.texture->SetPart(0, 0);
	gcloud6.posX = -0.01f;
	gcloud6.posY = -0.51f;

	gcloud7.texture->SetPart(0, 0);
	gcloud7.posX = 0.04f;
	gcloud7.posY = 0.3f;

	gcloud8.texture->SetPart(0, 0);
	gcloud8.posX = 0.45f;
	gcloud8.posY = 0.42f;

	gcloud9.texture->SetPart(0, 0);
	gcloud9.posX = 0.4f;
	gcloud9.posY = -0.24f;

	gcloud10.texture->SetPart(0, 0);
	gcloud10.posX = 0.67f;
	gcloud10.posY = -0.53f;

	if (Input_GetKeyTrigger(VK_RETURN) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)) {
		return FALSE;
	}

	if (Input_GetKeyTrigger('1') || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFTUP))
	{
		stage = STAGE_1;
		gchoice.texture->SetPart(1, 0);
		gchoice.posX = 0.8f;
		gchoice.posY = 0.8f;
	}

	if (Input_GetKeyTrigger('2') || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHTUP))
	{
		stage = STAGE_2;
		gchoice.texture->SetPart(2, 0);
		gchoice.posX = 0.8f;
		gchoice.posY = 0.8f;
	}
	GameObject_DrowUpdate(&lBackGround);
	GameObject_DrowUpdate(&gchoice);
	GameObject_DrowUpdate(&groad);
	//�X�e�[�W
	GameObject_DrowUpdate(&gstage1);
	GameObject_DrowUpdate(&gstage2);
	GameObject_DrowUpdate(&gstage3);
	GameObject_DrowUpdate(&gstage4);
	GameObject_DrowUpdate(&gstage5);
	GameObject_DrowUpdate(&gstage6);
	GameObject_DrowUpdate(&gstage7);
	GameObject_DrowUpdate(&gstage8);
	GameObject_DrowUpdate(&gstage9);
	GameObject_DrowUpdate(&gstage10);
	//�_
	GameObject_DrowUpdate(&gcloud1);
	GameObject_DrowUpdate(&gcloud2);
	GameObject_DrowUpdate(&gcloud3);
	GameObject_DrowUpdate(&gcloud4);
	GameObject_DrowUpdate(&gcloud5);
	GameObject_DrowUpdate(&gcloud6);
	GameObject_DrowUpdate(&gcloud7);
	GameObject_DrowUpdate(&gcloud8);
	GameObject_DrowUpdate(&gcloud9);
	GameObject_DrowUpdate(&gcloud10);

	return TRUE;
}

void Level_Draw()
{
	// ��ʃN���A�i�w��F�œh��Ԃ��j
	// �h��Ԃ��F�̎w��i�����F0.0f�`1.0f�j
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
	Direct3D_GetContext()->ClearRenderTargetView(Direct3D_GetRenderTargetView(), clearColor);

	//�Q�[���I�u�W�F�N�g��S���`�悷��
	lBackGround.texture->Draw();

	gchoice.texture->Draw();
	groad.texture->Draw();

	gcloud1.texture->Draw();
	gcloud2.texture->Draw();
	gcloud3.texture->Draw();
	gcloud4.texture->Draw();
	gcloud5.texture->Draw();
	gcloud6.texture->Draw();
	gcloud7.texture->Draw();
	gcloud8.texture->Draw();
	gcloud9.texture->Draw();
	gcloud10.texture->Draw();

	gstage1.texture->Draw();
	gstage2.texture->Draw();
	gstage3.texture->Draw();
	gstage4.texture->Draw();
	gstage5.texture->Draw();
	gstage6.texture->Draw();
	gstage7.texture->Draw();
	gstage8.texture->Draw();
	gstage9.texture->Draw();
	gstage10.texture->Draw();

	// �_�u���E�o�b�t�@�̃f�B�X�v���C�̈�ւ̃R�s�[����
	Direct3D_GetSwapChain()->Present(0, 0);
}

void Level_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM000));
	delete lBackGround.texture;
	delete gchoice.texture;
	delete groad.texture;
	delete gstage1.texture;
	delete gstage2.texture;
	delete gstage3.texture;
	delete gstage4.texture;
	delete gstage5.texture;
	delete gstage6.texture;
	delete gstage7.texture;
	delete gstage8.texture;
	delete gstage9.texture;
	delete gstage10.texture;
	delete gcloud1.texture;
	delete gcloud2.texture;
	delete gcloud3.texture;
	delete gcloud4.texture;
	delete gcloud5.texture;
	delete gcloud6.texture;
	delete gcloud7.texture;
	delete gcloud8.texture;
	delete gcloud9.texture;
	delete gcloud10.texture;
}