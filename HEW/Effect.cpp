#include "Effect.h"

void Effect_Init(GameObject * Effect){
	float spwnX = 0;//Å‰‚É—N‚©‚¹‚éêŠ‚ð•ÊX‚É‚·‚é‚½‚ß‚ÌŠÖ”
	spwnX = rand() % 40 - 30;
	Effect->texture = new Sprite("assets/Effect.png", 1, 3);
	Effect->texture->SetSize(1280 * 2, 720 * 2);
	Effect->posX = spwnX/10;
	Effect->posY = 1;
}

void Efffect_Move(GameObject * Effect)
{
	int ForEff = 0;//¶‰E‚É—h‚ç‚·‚½‚ß
	float yureX = 0;	//—h‚ê•
	float fallSpd = 0;//—Ž‚¿‚é‘¬“x
	float spwnX = 0;//ˆê”Ô‰º‚Ü‚Ås‚Á‚½Žž‚É‚à—N‚­êŠ‚ª•Ï‚í‚é‚æ‚¤‚É
	int alphaChange = rand() % 5;//“§–¾“x‚ð•Ï‚¦‚Ä‚¿‚ç‚Â‚­‚æ‚¤‚É
	int alpha = Effect->texture->mPartY;//Œ»Ý‚Ì“§–¾“x

	//ƒ‰ƒ“ƒ_ƒ€‚Å“§–¾“x‚ð•Ï‚¦‚é
	if (rand() % 30 == 1) {
		switch (alpha) {
		case 0:
			alpha = 1;
			break;
		case 1:
			//Á‚¦‚é‚Æ‚«‚ÆF‚ª–ß‚é‚Æ‚«‚ÅŠm—¦‚ð•ª‚¯‚é(1/5‚ÅÁ‚¦‚éA4/5‚Å‚Í‚Á‚«‚èŒ©‚¦‚é‚æ‚¤‚É‚È‚é)
			if (alphaChange == 0) {
				alpha = 2;
			}
			else
				alpha = 0;
			break;
		case 2:
			alpha = 1;
			break;
		}
	}
	Effect->texture->mPartY = alpha;

	//¶‰E‚É—h‚ç‚·
	if (rand() % 20 == 1) {
		yureX = rand() % 10;
		ForEff = rand() % 2;
		if (ForEff == 1) {
			yureX *= -1;
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


