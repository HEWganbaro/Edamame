#pragma once
#include "game.h"
#include "Title.h"
#include "Level.h"

enum SCENE
{
	TITLE,
	LEVEL,
	GAME,
};

class Scene
{
public:
	SCENE scene;

	void Title();
	void Level();
	void Game();
};