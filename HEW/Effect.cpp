#include "Effect.h"

void Effect_Init(GameObject * Effect) {
	float spwnX = 0;//最初に湧かせる場所を別々にするための関数
	spwnX = rand() % 40 - 30;
	Effect->texture = new Sprite("assets/Effect.png", 1, 3);
	Effect->texture->SetSize(1280 * 2, 720 * 2);
	Effect->posX = spwnX / 10;
	Effect->posY = 1;
	Effect->texture->SetAlpha(1.0f);
}

void Efffect_Move(GameObject * Effect)
{
	int ForEff = 0;//左右に揺らすため
	float yureX = 0;	//揺れ幅
	float fallSpd = 0;//落ちる速度
	float spwnX = 0;//一番下まで行った時にも湧く場所が変わるように
	int alphaChange = rand() % 3;//透明度を変えてちらつくように




	//左右に揺らす
	if (rand() % 20 == 1) {
		yureX = rand() % 10;
		ForEff = rand() % 2;
		if (ForEff == 1) {
			yureX *= -1;
		}
		//ランダムで透明度を変える
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

	//上から下に降らす
	fallSpd = rand() % 10;
	Effect->posY -= (fallSpd) / 1000;
	if (Effect->posY < 0.6) {
		Effect->posY = 1.5f;
		spwnX = rand() % 40 - 30;
		Effect->posX = spwnX / 10;
	}



}


