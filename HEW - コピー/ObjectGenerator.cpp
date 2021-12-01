//#include "ObjectGenerator.h"
//
//void ObjectGenerator_SetDragon(GameObject * pObj)
//{
//	// �|�C���^�ϐ��̍��Ɂ�������ƁA�A�h���X�������Ă���ϐ����̂��̂Ƃ��ĐU�镑��
//	*pObj = {
//		0, 0,  // ���S���W
//		0.25f, 0.25f,  // �T�C�Y
//	};
//
//	Animator_Initialize(&pObj->animator);  // �A�j���[�V����������
//
//	pObj->uvinfo = { 0, 0, 80.0f/TEXTURE_SIZE_X, 64.0f/TEXTURE_SIZE_Y };  // �e�N�X�`������n��
//}
//
//void ObjectGenerator_SetBG(GameObject * pObj)
//{
//	*pObj = {
//		0, 0,  // ���S���W
//		2, 2,  // �T�C�Y
//	};
//
//	Animator_Initialize(&pObj->animator);  // �A�j���[�V����������
//	pObj->animator.isActive = false;  // �A�j���[�V����OFF
//
//	pObj->uvinfo = { 0, 0.5f, 640.0f / TEXTURE_SIZE_X, 480.0f / TEXTURE_SIZE_Y };  // �e�N�X�`������n��
//}
//
//// ���̊֐��𐬗������邽�߂ɂ́A�e�N�X�`�����ȉ��̏����ō쐬����
//// �E32x32�L�����͉����тŔz�u����
//// �E32x32�L������UV(0, 0.25f)�̈ʒu������Ƃ��ĕ��ׂ�
//void ObjectGenerator_Character32x32(GameObject * pObj, int id)
//{
//	// �|�C���^�ϐ��̍��Ɂ�������ƁA�A�h���X�������Ă���ϐ����̂��̂Ƃ��ĐU�镑��
//	*pObj = {
//		0, 0,  // ���S���W
//		0.15f, 0.20f,  // �T�C�Y
//	};
//
//	Animator_Initialize(&pObj->animator);  // �A�j���[�V����������
//
//	// �e�N�X�`������n��
//	pObj->uvinfo = {
//		(float)id*96.0f/ TEXTURE_SIZE_X, 0.25f,  // �I�t�Z�b�gUV
//		32.0f / TEXTURE_SIZE_X, 32.0f / TEXTURE_SIZE_Y  // �P�R�}�T�C�YUV
//	};
//
//	// �L�����N�^�[�R���g���[��������
//	CharController_Initialize(&pObj->charController);
//}
