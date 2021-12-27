#include "Scene.h"

void Scene::Title()
{
	if (FALSE == Title_Update()) {	//ÉVÅ[ÉìïœçX
		Title_Relese();
		scene = GAME;
		if (FALSE == Game_Initialize())
			scene == -1;
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
		if (FALSE == Title_Initialize())
			scene == -1;
	}
	else {
		Game_Draw();
	}
}
