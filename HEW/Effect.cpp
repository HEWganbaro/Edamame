#include "Effect.h"

void Effect_Init(GameObject * Effect){
	float spwnX = 0;//�ŏ��ɗN������ꏊ��ʁX�ɂ��邽�߂̊֐�
	spwnX = rand() % 40 - 30;
	Effect->texture = new Sprite("assets/Effect.png", 1, 3);
	Effect->texture->SetSize(1280 * 2, 720 * 2);
	Effect->posX = spwnX/10;
	Effect->posY = 1;
	Effect->texture->SetAlpha(1.0f);
}

void Efffect_Move(GameObject * Effect)
{
	int ForEff = 0;//���E�ɗh�炷����
	float yureX = 0;	//�h�ꕝ
	float fallSpd = 0;//�����鑬�x
	float spwnX = 0;//��ԉ��܂ōs�������ɂ��N���ꏊ���ς��悤��
	int alphaChange = rand() % 3;//�����x��ς��Ă�����悤��

	
	

	//���E�ɗh�炷
	if (rand() % 20 == 1) {
		yureX = rand() % 10;
		ForEff = rand() % 2;
		if (ForEff == 1) {
			yureX *= -1;
		}
		//�����_���œ����x��ς���
		if (alphaChange == 0) {
			Effect->texture->color.a -= 0.3f;
			if (Effect->texture->color.a < 0.0f) {
				Effect->texture->color.a = 1.0f;
			}
		}
		else {
			Effect->texture->color.a += 0.3f;
			if (Effect->texture->color.a > 1.0f) {
				Effect->texture->color.a = 1.0f;
			}
		}
	}
	Effect->posX += yureX / 1000;

	//�ォ�牺�ɍ~�炷
	fallSpd = rand() % 10 ;
	Effect->posY -= (fallSpd)/1000;
	if (Effect->posY < 0.6) {
		Effect->posY = 1.5f;
		spwnX = rand() % 40 - 30;
		Effect->posX = spwnX / 10;
	}



}


