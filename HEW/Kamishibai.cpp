#include "Kamishibai.h"


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

GameObject kBackGround;				//�w�i
GameObject kFade;
GameObject kKorokoro;
GameObject kKamishibai;

FADE KamiFade;
int page = 0;

//*****************************************************************************
// �֐��̒�`�@��������@��
//*****************************************************************************

BOOL Kamishibai_Initialize()
{
	// �Q�[�����Ԃ̏����������AFPS��60�ɐݒ肵���B
	GameTimer_Initialize(60);

	//BGM�Đ�
	XA_Play(SOUND_LABEL(SOUND_LABEL_BGM_KAMISHIBAI));

	////�w�i
	//tBackGround.texture = new Sprite("assets/TitleBG.png", 1, 1);
	//tBackGround.texture->SetSize(1280 * 2, 720 * 2);
	//tBackGround.posX = -1;
	//tBackGround.posY = 1;

	//�w�i
	kBackGround.texture = new Sprite("assets/TitleBG.png", 1, 1);
	kBackGround.texture->SetSize(1280 * 2, 720 * 2);
	kBackGround.posX = -1;
	kBackGround.posY = 1;

	//�w�i
	kKamishibai.texture = new Sprite("assets/Kamishibai.png", 8, 1);
	kKamishibai.texture->SetSize(1280 * 2, 720 * 2);
	kKamishibai.posX = -1;
	kKamishibai.posY = 1;

	//�t�F�[�h
	kFade.texture = new Sprite("assets/TitleBG.png", 1, 1);
	kFade.texture->SetSize(1280 * 2, 720 * 2);
	kFade.posX = -1;
	kFade.posY = 1;
	kFade.texture->color.r = 0.0f;
	kFade.texture->color.g = 0.0f;
	kFade.texture->color.b = 0.0f;
	kFade.texture->color.a = 0.0f;
	KamiFade.framecnt = FADETIME - 0.1f;
	KamiFade.fadeout = false;

	//���낱��
	kKorokoro.texture = new Sprite("assets/fadekorokoro.png", 20, 2);
	kKorokoro.texture->SetSize(1280 * 2, 720 * 2);
	kKorokoro.posX = -1;
	kKorokoro.posY = 1;

	page = 0;
	
	return TRUE;
}

// �Q�[�����[�v���Ɏ��s�������A�Q�[���̏����������֐�
BOOL Kamishibai_Update()
{
	Input_Update();  // ���̃Q�[���Ŏg���L�[�̉�����Ԃ𒲂ׂĕ�
	XINPUT_STATE state;
	XInputGetState(0, &state);
		//#define XINPUT_GAMEPAD_DPAD_UP          0x0001
		//#define XINPUT_GAMEPAD_DPAD_DOWN        0x0002
		//#define XINPUT_GAMEPAD_DPAD_LEFT        0x0004
		//#define XINPUT_GAMEPAD_DPAD_RIGHT       0x0008
		//#define XINPUT_GAMEPAD_START            0x0010
		//#define XINPUT_GAMEPAD_BACK             0x0020
	if (Input_GetKeyTrigger(VK_RIGHT)||Input_GetControllerTrigger(XINPUT_GAMEPAD_B)) {
		page++;
		if (page % 2 == 0) {
			//BGM�Đ�
			XA_Play(SOUND_LABEL(SOUND_LABEL_SE_PAPER));
		}
		else
			XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_PAPER));
		if (page > 7) {
			korokoroX = 0;
			KamiFade.fadeout = true;
		}
	}
	kKamishibai.texture->SetPart(page, 0);

	GameObject_DrowUpdate(&kBackGround);
	GameObject_DrowUpdate(&kKamishibai);
	GameObject_DrowUpdate(&kFade);
	GameObject_DrowUpdate(&kKorokoro);
	
	kKorokoro.texture->SetPart(korokoroX / 4, 0);
	korokoroX++;
	FadeChange(&KamiFade);//�t�F�[�h���i��֐��A�G��Ȃ���
	kFade.texture->color.a = KamiFade.Alpha;
	if (KamiFade.Alpha > 1.0f)
		return FALSE;
	
}
void Kamishibai_Draw()
{
	// ��ʃN���A�i�w��F�œh��Ԃ��j
	// �h��Ԃ��F�̎w��i�����F0.0f�`1.0f�j
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
	Direct3D_GetContext()->ClearRenderTargetView(Direct3D_GetRenderTargetView(), clearColor);

	//�Q�[���I�u�W�F�N�g��S���`�悷��
	kBackGround.texture->Draw();
	kKamishibai.texture->Draw();
	kFade.texture->Draw();
	kKorokoro.texture->Draw();

	// �_�u���E�o�b�t�@�̃f�B�X�v���C�̈�ւ̃R�s�[����
	Direct3D_GetSwapChain()->Present(0, 0);

}
void Kamishibai_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM_KAMISHIBAI));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_PAPER));
	delete kBackGround.texture;
	delete kKamishibai.texture;
	delete kFade.texture;
	delete kKorokoro.texture;

}
