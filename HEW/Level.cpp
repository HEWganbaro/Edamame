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
GameObject gstage[10];
GameObject gcloud[10];
GameObject lFade;

FADE LevelFade;

int countLevel = 10;
bool Right;
bool Left;

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

	//�t�F�[�h
	lFade.texture = new Sprite("assets/TitleBG.png", 1, 1);
	lFade.texture->SetSize(1280 * 2, 720 * 2);
	lFade.posX = -1;
	lFade.posY = 1;
	lFade.texture->color.r = 0.0f;
	lFade.texture->color.g = 0.0f;
	lFade.texture->color.b = 0.0f;
	lFade.texture->color.a = 0.0f;
	LevelFade.framecnt = FADETIME - 0.1f;
	LevelFade.fadeout = false;

	groad.texture = new Sprite("assets/road.png", 1, 10);
	groad.texture->SetSize(1330 * 2, 720 * 2.3);

	/*gstage[0].texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage[0].texture->SetSize(320, 320);

	gstage[1].texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage[1].texture->SetSize(320, 320);

	gstage[2].texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage[2].texture->SetSize(320, 320);

	gstage[3].texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage[3].texture->SetSize(320, 320);

	gstage[4].texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage[4].texture->SetSize(320, 320);

	gstage[5].texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage[5].texture->SetSize(320, 320);

	gstage[6].texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage[6].texture->SetSize(320, 320);

	gstage[7].texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage[7].texture->SetSize(320, 320);

	gstage[8].texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage[8].texture->SetSize(320, 320);

	gstage[9].texture = new Sprite("assets/Level_tile.png", 2, 1);
	gstage[9].texture->SetSize(320, 320);
*/
	for (int i = 0; i < 10; i++) {
		gstage[i].texture = new Sprite("assets/Level_tile.png", 2, 1);
		gstage[i].texture->SetSize(320, 320);

		gcloud[i].texture = new Sprite("assets/cloud.png", 1, 1);
		gcloud[i].texture->SetSize(400, 160);
	}


	/*gcloud[0].texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud[0].texture->SetSize(400, 160);

	gcloud[1].texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud[1].texture->SetSize(400, 160);

	gcloud[2].texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud[2].texture->SetSize(400, 160);

	gcloud[3].texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud[3].texture->SetSize(400, 160);

	gcloud[4].texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud[4].texture->SetSize(400, 160);

	gcloud[5].texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud[5].texture->SetSize(400, 160);

	gcloud[6].texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud[6].texture->SetSize(400, 160);

	gcloud[7].texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud[7].texture->SetSize(400, 160);

	gcloud[8].texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud[8].texture->SetSize(400, 160);

	gcloud[9].texture = new Sprite("assets/cloud.png", 1, 1);
	gcloud[9].texture->SetSize(400, 160);*/

	gstage[0].texture->SetPart(0, 0);
	gstage[0].posX = -0.97f;
	gstage[0].posY = 0.48f;

	gstage[1].texture->SetPart(0, 0);
	gstage[1].posX = -0.77f;
	gstage[1].posY = -0.1f;

	gstage[2].texture->SetPart(0, 0);
	gstage[2].posX = -0.58f;
	gstage[2].posY = 0.68f;

	gstage[3].texture->SetPart(0, 0);
	gstage[3].posX = -0.24f;
	gstage[3].posY = 0.54f;

	gstage[4].texture->SetPart(0, 0);
	gstage[4].posX = -0.36f;
	gstage[4].posY = -0.14f;

	gstage[5].texture->SetPart(1, 0);
	gstage[5].posX = 0.02f;
	gstage[5].posY = -0.23f;

	gstage[6].texture->SetPart(1, 0);
	gstage[6].posX = 0.068f;
	gstage[6].posY = 0.58f;

	gstage[7].texture->SetPart(1, 0);
	gstage[7].posX = 0.48f;
	gstage[7].posY = 0.7f;

	gstage[8].texture->SetPart(1, 0);
	gstage[8].posX = 0.43f;
	gstage[8].posY = 0.04f;

	gstage[9].texture->SetPart(1, 0);
	gstage[9].posX = 0.7f;
	gstage[9].posY = -0.25f;

	gcloud[0].texture->SetPart(0, 0);
	gcloud[0].posX = -1.0f;
	gcloud[0].posY = 0.19f;

	gcloud[1].texture->SetPart(0, 0);
	gcloud[1].posX = -0.8f;
	gcloud[1].posY = -0.38f;

	gcloud[2].texture->SetPart(0, 0);
	gcloud[2].posX = -0.61f;
	gcloud[2].posY = 0.4f;

	gcloud[3].texture->SetPart(0, 0);
	gcloud[3].posX = -0.27f;
	gcloud[3].posY = 0.26f;

	gcloud[4].texture->SetPart(0, 0);
	gcloud[4].posX = -0.39f;
	gcloud[4].posY = -0.42f;

	gcloud[5].texture->SetPart(0, 0);
	gcloud[5].posX = -0.01f;
	gcloud[5].posY = -0.51f;

	gcloud[6].texture->SetPart(0, 0);
	gcloud[6].posX = 0.04f;
	gcloud[6].posY = 0.3f;

	gcloud[7].texture->SetPart(0, 0);
	gcloud[7].posX = 0.45f;
	gcloud[7].posY = 0.42f;

	gcloud[8].texture->SetPart(0, 0);
	gcloud[8].posX = 0.4f;
	gcloud[8].posY = -0.24f;

	gcloud[9].texture->SetPart(0, 0);
	gcloud[9].posX = 0.67f;
	gcloud[9].posY = -0.53f;

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

	GameObject_DrowUpdate(&lBackGround);
	GameObject_DrowUpdate(&gchoice);
	GameObject_DrowUpdate(&groad);
	GameObject_DrowUpdate(&lFade);
	for (int i = 0; i < 10; i++)
	{
		//�X�e�[�W
		GameObject_DrowUpdate(&gstage[i]);
		//�_
		GameObject_DrowUpdate(&gcloud[i]);
	}

	
	//if (Input_GetKeyTrigger('1') || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFTUP))
	//{
	//	stage = STAGE_1;
	//	gchoice.texture->SetPart(1, 0);
	//	gchoice.posX = 0.8f;
	//	gchoice.posY = 0.8f;

	//}
	//if (Input_GetKeyTrigger('2') || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHTUP))
	//{
	//	stage = STAGE_2;
	//	gchoice.texture->SetPart(2, 0);
	//	gchoice.posX = 0.8f;
	//	gchoice.posY = 0.8f;
	//}
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFTUP)
		Left = true;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHTUP)
		Right = true;

	if (state.Gamepad.wButtons == 0 && Left == true) {
		stage--;
		if (stage == 0)
			stage = 1;
		gchoice.texture->SetPart(1, 0);
		gchoice.posX = 0.8f;
		gchoice.posY = 0.8f;
		Left = false;
	}
	if (state.Gamepad.wButtons == 0 && Right == true) {
		stage++;
		if (stage == 11)
			stage = 10;
		gchoice.texture->SetPart(2, 0);
		gchoice.posX = 0.8f;
		gchoice.posY = 0.8f;
		Right = false;
	}

	if (Input_GetKeyTrigger(VK_RETURN) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)) {
		LevelFade.fadeout = true;
	}

	FadeChange(&LevelFade);//�t�F�[�h���i��֐��A�G��Ȃ���
	lFade.texture->color.a = LevelFade.Alpha;
	if (LevelFade.Alpha > 1.0f)
		return FALSE;

	//�㉺�ɂӂ�ӂ�ړ�����
	gstage[stage - 1].posY += sin(countLevel / 5) / 600;
	gcloud[stage - 1].posY += sin(countLevel / 5) / 600;
	countLevel++;

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

	for (int i = 0; i < 10; i++)
	{
		gcloud[i].texture->Draw();

		gstage[i].texture->Draw();
	}
	lFade.texture->Draw();

	// �_�u���E�o�b�t�@�̃f�B�X�v���C�̈�ւ̃R�s�[����
	Direct3D_GetSwapChain()->Present(0, 0);
}

void Level_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM000));
	delete lBackGround.texture;
	delete gchoice.texture;
	delete groad.texture;
	delete lFade.texture;
	for (int i = 0; i < 10; i++)
	{
		delete gstage[i].texture;
		delete gcloud[i].texture;
	}
}