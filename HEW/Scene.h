#pragma once
#include "game.h"
#include "Title.h"
#include "Level.h"
#include "GameClear.h"
#include "GameOver.h"

enum SCENE
{
	TITLE,
	LEVEL,
	GAME,
	GAME_CLEAR,
	GAME_OVER,
};

class Scene
{
public:
	SCENE scene;

	void Title();
	void Level();
	void Game();
	void Clear();
	void Over();
};