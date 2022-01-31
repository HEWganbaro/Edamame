#include "Scene.h"

StageScore score;

void Scene::Title()
{
	if (FALSE == Title_Update()) {	//シーン変更
		Title_Relese();
		scene = KAMISHIBAI;
		StageScore score = TITLESCORE;
		if (FALSE == Kamishibai_Initialize())
			scene == -1;
	}
	else {
		Title_Draw();
	}
}

void Scene::Kami()
{
	if (FALSE == Kamishibai_Update()) {	//シーン変更
		Kamishibai_Relese();
		scene = LEVEL;
		StageScore score = TITLESCORE;
		if (FALSE == Level_Initialize(score))
			scene == -1;
	}
	else {
		Kamishibai_Draw();
	}
}

void Scene::Level()
{
	if (FALSE == Level_Update()) {	//シーン変更
		Level_Relese();

		if (pause == lPAUSE) {
			scene = TITLE;
			if (FALSE == Title_Initialize())
				scene == -1;
		}
		else {
			scene = GAME;
			if (FALSE == Game_Initialize())
				scene == -1;
		}


	}
	else {
		Level_Draw();
	}
}

void Scene::Game()
{
	if (FALSE == Game_Update()) {
		score = Game_Relese();
		if (turn == CLEAR)
		{
			scene = GAME_CLEAR;
			if (FALSE == GameClear_Initialize())
				scene == -1;
		}
		if (turn == GAMEOVER)
		{
			scene = GAME_OVER;
			if (FALSE == GameOver_Initialize())
				scene == -1;
		}
		if (pauseChoice == gRESPAWN) {
			scene = GAME;
			if (FALSE == Game_Initialize())
				scene == -1;			
		}
		else if (pauseChoice == gLEVEL) {
			scene = LEVEL;
			StageScore score = TITLESCORE;
			if (FALSE == Level_Initialize(score))
				scene == -1;

		}
	}
	else {
		Game_Draw();
	}
}

void Scene::Clear()
{

	if (FALSE == GameClear_Update()) {	//シーン変更
		GameClear_Relese();
		scene = TITLE;
		if (FALSE == Title_Initialize())
			scene == -1;
	}
	else {
		GameClear_Draw();
	}

}

void Scene::Over()
{
	if (FALSE == GameOver_Update()) {	//シーン変更
		GameOver_Relese();
		scene = TITLE;
		if (FALSE == Title_Initialize())
			scene == -1;
	}
	else {
		GameOver_Draw();
	}
}
