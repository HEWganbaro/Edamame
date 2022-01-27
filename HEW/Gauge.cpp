#include "Gauge.h"

GameObject * Gauge_Initialize(GameObject * Gauge, GameObject * Gauge2)
{
	Gauge->texture = new Sprite("assets/Image_Load.png", 1, 4);
	Gauge->texture->SetSize(800, 80);
	Gauge->texture->SetPart(0, 0);
	Gauge->posX = 0.3f;
	Gauge->posY = -0.8f;

	Gauge2->texture = new Sprite("assets/Image_Load.png", 1, 4);
	Gauge2->texture->SetSize(800, 80);
	Gauge2->texture->SetPart(0, 2);
	Gauge2->posX = 0.3f;
	Gauge2->posY = -0.79f;

	return Gauge, Gauge2;
}
