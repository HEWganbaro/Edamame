#include "Player.h"

void Player_Initialize(GameObject* Player) {
	Player->textuer = new Sprite("assets/Player.png", 1, 1);
	Player->textuer->SetSize(80, 80);
}