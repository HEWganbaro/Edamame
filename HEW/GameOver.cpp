#include "GameOver.h"

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

GameObject oBackGround;				//�w�i
GameObject oLogo;
GameObject oFade;
GameObject oFadeLogo;
GameObject oPlayer;

FADE GameOverFade;
FADE GameLogo;
//GameObject��ǉ�����Ƃ��͕K��MAX_OBJECT�̐������킹�Ȃ��ƃG���[���o���I

//*****************************************************************************
// �֐��̒�`�@��������@��
//*****************************************************************************

BOOL GameOver_Initialize()
{
	// �Q�[�����Ԃ̏����������AFPS��60�ɐݒ肵���B
	GameTimer_Initialize(60);

	//BGM�Đ�
	XA_Play(SOUND_LABEL(SOUND_LABEL_BGM_GAMEOVER));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_PLAYERCRUSH));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_SNOWHUNDA));

	//�w�i
	oBackGround.texture = new Sprite("assets/�ǉ��e�N�X�`��/gameover_1.png", 1, 1);
	oBackGround.texture->SetSize(1280 * 2, 720 * 2);
	oBackGround.posX = -1;
	oBackGround.posY = 1;

	oPlayer.texture = new Sprite("assets/Player_kansei.png", 48, 8);
	oPlayer.texture->SetSize(512, 512);
	oPlayer.posX = -0.25f;
	oPlayer.posY = -0.2f;
	oPlayer.animator.speed = 8.0f;

	oLogo.texture = new Sprite("assets/�ǉ��e�N�X�`��/gameover_2.png", 1, 1);
	oLogo.texture->SetSize(1280 * 2, 720 * 2);
	oLogo.posX = -1;
	oLogo.posY = 1;

	//�t�F�[�h
	oFade.texture = new Sprite("assets/�ǉ��e�N�X�`��/gameover_1.png", 1, 1);
	oFade.texture->SetSize(1280 * 2, 720 * 2);
	oFade.posX = -1;
	oFade.posY = 1;
	oFade.texture->color.r = 0.0f;
	oFade.texture->color.g = 0.0f;
	oFade.texture->color.b = 0.0f;
	oFade.texture->color.a = 0.0f;
	GameOverFade.framecnt = FADETIME - 0.1f;
	GameOverFade.fadeout = false;

	oFadeLogo.texture = new Sprite("assets/�ǉ��e�N�X�`��/gameover_2.png", 1, 1);
	oFadeLogo.texture->SetSize(1280 * 2, 720 * 2);
	oFadeLogo.posX = -1;
	oFadeLogo.posY = 1;
	oFadeLogo.texture->color.r = 0.0f;
	oFadeLogo.texture->color.g = 0.0f;
	oFadeLogo.texture->color.b = 0.0f;
	oFadeLogo.texture->color.a = 0.0f;
	GameLogo.framecnt = FADETIME - 0.1f;
	GameLogo.fadeout = true;

	

	return TRUE;
}


// �Q�[�����[�v���Ɏ��s�������A�Q�[���̏����������֐�
BOOL GameOver_Update()
{
	Input_Update();  // ���̃Q�[���Ŏg���L�[�̉�����Ԃ𒲂ׂĕ�
	XINPUT_STATE state;
	XInputGetState(0, &state);

	GameObject_DrowUpdate(&oBackGround);
	GameObject_DrowUpdate(&oPlayer);
	GameObject_DrowUpdate(&oLogo);
	GameObject_DrowUpdate(&oFade);
	GameObject_DrowUpdate(&oFadeLogo);

	Animator_Update(&oPlayer.animator);
	oPlayer.animator.isActive = true;

	oPlayer.texture->SetPart(oPlayer.animator.frame, 0);

	for (int i = 0; i < 10; i++)
	{
		oPlayer.posY += 0.0001;
	}

	if (Input_GetKeyTrigger(VK_SPACE) || Input_GetControllerTrigger(XINPUT_GAMEPAD_B))
	{
		GameOverFade.fadeout = true;
		XA_Play(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));
	}

	FadeChange(&GameLogo);//�t�F�[�h���i��֐��A�G��Ȃ���
	oFadeLogo.texture->color.a = GameLogo.Alpha;
	GameLogo.fadeout = false;

	FadeChange(&GameOverFade);//�t�F�[�h���i��֐��A�G��Ȃ���
	oFade.texture->color.a = GameOverFade.Alpha;
	if (GameOverFade.Alpha > 1.0f)
		return FALSE;

	return TRUE;
}

void GameOver_Draw()
{
	// ��ʃN���A�i�w��F�œh��Ԃ��j
	// �h��Ԃ��F�̎w��i�����F0.0f�`1.0f�j
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
	Direct3D_GetContext()->ClearRenderTargetView(Direct3D_GetRenderTargetView(), clearColor);

	//�Q�[���I�u�W�F�N�g��S���`�悷��
	oBackGround.texture->Draw();
	oPlayer.texture->Draw();
	oLogo.texture->Draw();
	oFade.texture->Draw();
	oFadeLogo.texture->Draw();

	// �_�u���E�o�b�t�@�̃f�B�X�v���C�̈�ւ̃R�s�[����
	Direct3D_GetSwapChain()->Present(0, 0);
}

//�����GameObject�͂�����delete���悤�I
void GameOver_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM_GAMEOVER));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));
	delete oBackGround.texture;
	delete oPlayer.texture;
	delete oLogo.texture;
	delete oFade.texture;
	delete oFadeLogo.texture;
}