#include "Scene.h"

void Scene::Title()
{
	if (FALSE == Title_Update()) {	//�V�[���ύX
		Title_Relese();
		scene = GAME;
		if (FALSE == Game_Initialize());
			//�G���[
	}
	else {
		Title_Draw();
	}
}

void Scene::Game()
{
	if (FALSE == Game_Update()) {
		Game_Relese();
		scene = TITLE;
		if (FALSE == Title_Initialize());
			//�G���[
	}
	else {
		Game_Draw();
	}
}
