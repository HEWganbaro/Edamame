#include "Title.h"

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

GameObject tBackGround;				//�w�i
GameObject tLogo;                   //�^�C�g�����S
GameObject tFade;

FADE TitleFade;

//GameObject��ǉ�����Ƃ��͕K��MAX_OBJECT�̐������킹�Ȃ��ƃG���[���o���I

//*****************************************************************************
// �֐��̒�`�@��������@��
//*****************************************************************************

BOOL Title_Initialize()
{
	// �Q�[�����Ԃ̏����������AFPS��60�ɐݒ肵���B
	GameTimer_Initialize(60);

	//BGM�Đ�
	XA_Play(SOUND_LABEL(SOUND_LABEL_BGM_TITLE));

	//�w�i
	tBackGround.texture = new Sprite("assets/TitleBG.png", 1, 1);
	tBackGround.texture->SetSize(1280 * 2, 720 * 2);
	tBackGround.posX = -1;
	tBackGround.posY = 1;
	//���S
	tLogo.texture = new Sprite("assets/TitleLOGO.png", 1, 1);
	tLogo.texture->SetSize(1280 * 2, 720 * 2);
	tLogo.posX = -1;
	tLogo.posY = 1;
	//�t�F�[�h
	tFade.texture = new Sprite("assets/TitleBG.png", 1, 1);
	tFade.texture->SetSize(1280 * 2, 720 * 2);
	tFade.posX = -1;
	tFade.posY = 1;
	tFade.texture->color.r = 0.0f;
	tFade.texture->color.g = 0.0f;
	tFade.texture->color.b = 0.0f;
	tFade.texture->color.a = 0.0f;
	TitleFade.framecnt = FADETIME - 0.1f;

	return TRUE;
}


// �Q�[�����[�v���Ɏ��s�������A�Q�[���̏����������֐�
BOOL Title_Update()
{
	Input_Update();  // ���̃Q�[���Ŏg���L�[�̉�����Ԃ𒲂ׂĕ�
	XINPUT_STATE state;
	XInputGetState(0, &state);

	GameObject_DrowUpdate(&tBackGround);
	GameObject_DrowUpdate(&tLogo);
	GameObject_DrowUpdate(&tFade);

	if (Input_GetKeyTrigger(VK_SPACE))
	{
		TitleFade.fadeout = true;
		XA_Play(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));
	}

	FadeChange(&TitleFade);//�t�F�[�h���i��֐��A�G��Ȃ���
	tFade.texture->color.a = TitleFade.Alpha;
	if (TitleFade.Alpha > 1.0f)
		return FALSE;
	
	return TRUE;
}

void Title_Draw()
{
	// ��ʃN���A�i�w��F�œh��Ԃ��j
	// �h��Ԃ��F�̎w��i�����F0.0f�`1.0f�j
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
	Direct3D_GetContext()->ClearRenderTargetView(Direct3D_GetRenderTargetView(), clearColor);

	//�Q�[���I�u�W�F�N�g��S���`�悷��
	tBackGround.texture->Draw();
	tLogo.texture->Draw();
	tFade.texture->Draw();
	// �_�u���E�o�b�t�@�̃f�B�X�v���C�̈�ւ̃R�s�[����
	Direct3D_GetSwapChain()->Present(0, 0);
}

//�����GameObject�͂�����delete���悤�I
void Title_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM_TITLE));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));
	delete tBackGround.texture;
	delete tLogo.texture;
	delete tFade.texture;
}