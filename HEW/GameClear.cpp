#include "GameClear.h"

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

GameObject cBackGround;				//�w�i
GameObject cFade;

FADE GameClearFade;
//GameObject��ǉ�����Ƃ��͕K��MAX_OBJECT�̐������킹�Ȃ��ƃG���[���o���I

//*****************************************************************************
// �֐��̒�`�@��������@��
//*****************************************************************************

BOOL GameClear_Initialize()
{
	// �Q�[�����Ԃ̏����������AFPS��60�ɐݒ肵���B
	GameTimer_Initialize(60);

	//BGM�Đ�
	XA_Play(SOUND_LABEL(SOUND_LABEL_BGM_GAME));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_PLAYERCRUSH));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_SNOWHUNDA));

	//�w�i
	cBackGround.texture = new Sprite("assets/�ǉ��e�N�X�`��/GameClear.png", 8, 1);
	cBackGround.texture->SetSize(1280 * 2, 720 * 2);
	cBackGround.posX = -1;
	cBackGround.posY = 1;
	cBackGround.animator.speed = 8.0f;

	//�t�F�[�h
	cFade.texture = new Sprite("assets/�ǉ��e�N�X�`��/GameClear.png", 8, 1);
	cFade.texture->SetSize(1280 * 2, 720 * 2);
	cFade.posX = -1;
	cFade.posY = 1;
	cFade.texture->color.r = 0.0f;
	cFade.texture->color.g = 0.0f;
	cFade.texture->color.b = 0.0f;
	cFade.texture->color.a = 0.0f;
	GameClearFade.framecnt = FADETIME - 0.1f;

	return TRUE;
}


// �Q�[�����[�v���Ɏ��s�������A�Q�[���̏����������֐�
BOOL GameClear_Update()
{
	Input_Update();  // ���̃Q�[���Ŏg���L�[�̉�����Ԃ𒲂ׂĕ�
	XINPUT_STATE state;
	XInputGetState(0, &state);

	Animator_Update(&cBackGround.animator);
	cBackGround.animator.isActive = true;

	cBackGround.texture->SetPart(cBackGround.animator.frame, 0);

	GameObject_DrowUpdate(&cBackGround);

	GameObject_DrowUpdate(&cFade);

	if (Input_GetKeyTrigger(VK_SPACE))
	{
		GameClearFade.fadeout = true;
		XA_Play(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));
	}

	FadeChange(&GameClearFade);//�t�F�[�h���i��֐��A�G��Ȃ���
	cFade.texture->color.a = GameClearFade.Alpha;
	if (GameClearFade.Alpha > 1.0f)
		return FALSE;

	return TRUE;
}

void GameClear_Draw()
{
	// ��ʃN���A�i�w��F�œh��Ԃ��j
	// �h��Ԃ��F�̎w��i�����F0.0f�`1.0f�j
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
	Direct3D_GetContext()->ClearRenderTargetView(Direct3D_GetRenderTargetView(), clearColor);

	//�Q�[���I�u�W�F�N�g��S���`�悷��
	cBackGround.texture->Draw();
	cFade.texture->Draw();
	// �_�u���E�o�b�t�@�̃f�B�X�v���C�̈�ւ̃R�s�[����
	Direct3D_GetSwapChain()->Present(0, 0);
}

//�����GameObject�͂�����delete���悤�I
void GameClear_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM_GAME));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));
	delete cBackGround.texture;
	delete cFade.texture;
}