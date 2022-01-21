#include "Scene.h"

void Scene::Title()
{
	if (FALSE == Title_Update()) {	//シーン変更
		Title_Relese();
		scene = GAME;
		if (FALSE == Game_Initialize());
			//エラー
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
			//エラー
	}
	else {
		Game_Draw();
	}
}
