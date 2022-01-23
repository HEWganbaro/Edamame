#include "Effect.h"

void Effect_Init(GameObject * Effect){
	float spwnX = 0;//Å‰‚É—N‚©‚¹‚éêŠ‚ð•ÊX‚É‚·‚é‚½‚ß‚ÌŠÖ”
	spwnX = rand() % 40 - 30;
	Effect->texture = new Sprite("assets/Effect.png", 1, 3);
	Effect->texture->SetSize(1280 * 2, 720 * 2);
	Effect->posX = spwnX/10;
	Effect->posY = 1;
	Effect->texture->SetAlpha(1.0f);
}

void Efffect_Move(GameObject * Effect)
{
	int ForEff = 0;//¶‰E‚É—h‚ç‚·‚½‚ß
	float yureX = 0;	//—h‚ê•
	float fallSpd = 0;//—Ž‚¿‚é‘¬“x
	float spwnX = 0;//ˆê”Ô‰º‚Ü‚Ås‚Á‚½Žž‚É‚à—N‚­êŠ‚ª•Ï‚í‚é‚æ‚¤‚É
	int alphaChange = rand() % 3;//“§–¾“x‚ð•Ï‚¦‚Ä‚¿‚ç‚Â‚­‚æ‚¤‚É

	
	

	//¶‰E‚É—h‚ç‚·
	if (rand() % 20 == 1) {
		yureX = rand() % 10;
		ForEff = rand() % 2;
		if (ForEff == 1) {
			yureX *= -1;
		}
		//ƒ‰ƒ“ƒ_ƒ€‚Å“§–¾“x‚ð•Ï‚¦‚é
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

	//ã‚©‚ç‰º‚É~‚ç‚·
	fallSpd = rand() % 10 ;
	Effect->posY -= (fallSpd)/1000;
	if (Effect->posY < 0.6) {
		Effect->posY = 1.5f;
		spwnX = rand() % 40 - 30;
		Effect->posX = spwnX / 10;
	}



}


