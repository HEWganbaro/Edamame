#include "Scene.h"

void Scene::Title()
{
	if (FALSE == Title_Update()) {	//シーン変更
		Title_Relese();
		scene = LEVEL;
		if (FALSE == Level_Initialize())
			scene == -1;
	}
	else {
		Title_Draw();
	}
}

void Scene::Level()
{
	if (FALSE == Level_Update()) {	//シーン変更
		Level_Relese();
		scene = GAME;
		if (FALSE == Game_Initialize())
			scene == -1;
	}
	else {
		Level_Draw();
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
