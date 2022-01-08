#include "GameObject.h"
#include "GameTimer.h"


void GameObject_DrowUpdate(GameObject* obj)
{
	obj->texture->SetPos(obj->posX, obj->posY);
	obj->texture->SetPos(obj->posX, obj->posY);
}

//FRECT GameObject_GetXY(GameObject * pThis)
//{
//	// �|�C���^�@���@����ϐ��̑��݂��Ă�ꏊ��\�������i�Ԓn/�A�h���X�j�����邽�߂̔��i�ϐ��j
//
//	// �A�h���X����\���̂̒��̕ϐ��ɃA�N�Z�X����ɂ̓A���[���Z�q�i->�j���g��
//	float leftX = pThis->posX - pThis->sizeX / 2;
//	float rightX = leftX + pThis->sizeX;
//	float topY = pThis->posY + pThis->sizeY / 2;
//	float bottomY = topY - pThis->sizeY;
//
//	FRECT rect = { leftX, rightX, topY, bottomY };
//
//	return rect;
//}
//
//FRECT GameObject_GetUV(GameObject * pThis)
//{
//	float leftU =  pThis->uvinfo.offsetU + (float)pThis->animator.frame * pThis->uvinfo.sizeU;
//	float rightU = leftU + pThis->uvinfo.sizeU;
//	float topV =  pThis->uvinfo.offsetV + (float)pThis->charController.direction * pThis->uvinfo.sizeV;
//	float bottomV = topV + pThis->uvinfo.sizeV;
//
//	FRECT rect = { leftU, rightU, topV, bottomV };
//
//	return rect;
//}
//
//void GameObject_Update(GameObject * pThis)
//{
//	// �A�j���[�V�����̃R�}��i�߂�
//	Animator_Update(&pThis->animator);
//
//	// �L�����R���g���[�����g���Ă̈ړ�
//	CharController_Update(&pThis->charController, &pThis->posX, &pThis->posY);
//}

vector<string> split(string& input, char delimiter)
{
	istringstream stream(input);
	string field;
	vector<string> result;
	while (getline(stream, field, delimiter))
	{
		result.push_back(field);
	}
	return result;
}