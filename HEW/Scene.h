#pragma once
#include "game.h"
#include "Title.h"

enum SCENE
{
	TITLE,
	GAME,
};

class Scene
{
public:
	SCENE scene;

	void Title();
	void Game();
};