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
GameObject glevel;
GameObject glevel2;
GameObject gchoice;
//GameObject��ǉ�����Ƃ��͕K��MAX_OBJECT�̐������킹�Ȃ��ƃG���[���o���I

//*****************************************************************************
// �֐��̒�`�@��������@��
//*****************************************************************************

BOOL Level_Initialize()
{
	// �Q�[�����Ԃ̏����������AFPS��60�ɐݒ肵���B
	GameTimer_Initialize(60);

	//BGM�Đ�
	XA_Play(SOUND_LABEL(SOUND_LABEL_BGM000));

	//�w�i
	lBackGround.texture = new Sprite("assets/BackGround.png", 1, 1);
	lBackGround.texture->SetSize(1280 * 2, 720 * 2);
	lBackGround.posX = -1;
	lBackGround.posY = 1;

	glevel.texture = new Sprite("assets/dotFont.png", 16, 8);
	glevel.texture->SetSize(80, 160);

	glevel2.texture = new Sprite("assets/dotFont.png", 16, 8);
	glevel2.texture->SetSize(80, 160);

	gchoice.texture = new Sprite("assets/dotFont.png", 16, 8);
	gchoice.texture->SetSize(80, 160);
	gchoice.texture->SetPart(0, 0);
	gchoice.posX = 0.8f;
	gchoice.posY = 0.8f;

	return TRUE;
}

BOOL Level_Update()
{
	Input_Update();  // ���̃Q�[���Ŏg���L�[�̉�����Ԃ𒲂ׂĕ�
	XINPUT_STATE state;
	XInputGetState(0, &state);

	glevel.texture->SetPart(1, 0);
	glevel.posX = -0.5f;
	glevel.posY = 0.1f;

	glevel2.texture->SetPart(2, 0);
	glevel2.posX = 0.4f;
	glevel2.posY = 0.1f;

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
	GameObject_DrowUpdate(&glevel);
	GameObject_DrowUpdate(&glevel2);
	GameObject_DrowUpdate(&gchoice);

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

	glevel.texture->Draw();
	glevel2.texture->Draw();
	gchoice.texture->Draw();

	// �_�u���E�o�b�t�@�̃f�B�X�v���C�̈�ւ̃R�s�[����
	Direct3D_GetSwapChain()->Present(0, 0);
}

void Level_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM000));
	delete lBackGround.texture;
	delete glevel.texture;
	delete glevel2.texture;
	delete gchoice.texture;
}