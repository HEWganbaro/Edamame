#include "Gauge.h"




GameObject * Gauge_Initialize(GameObject * Gauge, GameObject * Gauge2)
{
	Gauge->texture = new Sprite("assets/gauge_nakami.png", 2, 1);
	Gauge->texture->SetSize(810, 80);
	Gauge->texture->SetPart(1, 0);
	Gauge->posX = 0.29f;
	Gauge->posY = -0.77f;

	Gauge2->texture = new Sprite("assets/gauge_nakami.png", 2, 1);
	Gauge2->texture->SetSize(800, 80);
	Gauge2->texture->SetPart(0, 0);
	Gauge2->posX = 0.2895f;
	Gauge2->posY = -0.77f;

	return Gauge, Gauge2;
}

void Gauge_Update(GameObject* Gauge, GameObject * Gauge2, GameObject * Player, GameObject * Player2)
{
	float gauge_change = 0;//�傫�����̐�ʂ̃T�C�Y�����v�Ŋ����Ċ������o���֐�
	float sumSnowSize = 0;//��ʂ̃T�C�Y�̍��v������
	sumSnowSize = Player->SnowSize + Player2->SnowSize;//���v�����鎮
	gauge_change = big_snowball / sumSnowSize;//�傫�����̃T�C�Y�����v�Ŋ����Ċ������o����
	//Gauge2->sizeX = gauge_change * 100;
	Gauge2->texture->SetSize(gauge_change * 800, 80);
	if (Player->SnowSize > Player2->SnowSize) {
		Gauge->texture->SetPart(1, 0);
		Gauge2->texture->SetPart(0, 0);
	}
	else {
		Gauge->texture->SetPart(0, 0);
		Gauge2->texture->SetPart(1, 0);
	}
}
