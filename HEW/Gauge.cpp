#include "Gauge.h"




GameObject * Gauge_Initialize(GameObject * Gauge, GameObject * Gauge2)
{
	Gauge->texture = new Sprite("assets/gauge_nakami.png", 2, 1);
	Gauge->texture->SetSize(800, 80);
	Gauge->texture->SetPart(1, 0);
	Gauge->posX = 0.3f;
	Gauge->posY = -0.8f;

	Gauge2->texture = new Sprite("assets/gauge_nakami.png", 2, 1);
	Gauge2->texture->SetSize(800, 80);
	Gauge2->texture->SetPart(0, 0);
	Gauge2->posX = 0.3f;
	Gauge2->posY = -0.8f;

	return Gauge, Gauge2;
}

void Gauge_Update(GameObject * Gauge2, GameObject * Player, GameObject * Player2)
{
	float gauge_change = 0;//大きい方の雪玉のサイズを合計で割って割合を出す関数
	float sumSnowSize = 0;//雪玉のサイズの合計を入れる
	sumSnowSize = Player->SnowSize + Player2->SnowSize;//合計を入れる式
	gauge_change = big_snowball / sumSnowSize;//大きい方のサイズを合計で割って割合を出す式
	//Gauge2->sizeX = gauge_change * 100;
	Gauge2->texture->SetSize(gauge_change * 900, 80);
}
