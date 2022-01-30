#pragma once
#include "game.h"
#include "Kamishibai.h"
#include "Title.h"
#include "Level.h"
#include "GameClear.h"
#include "GameOver.h"

enum SCENE
{
	TITLE,
	KAMISHIBAI,
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
	void Kami();
	void Level();
	void Game();
	void Clear();
	void Over();
};