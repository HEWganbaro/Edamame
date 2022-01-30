#pragma once

#include <Windows.h>

#include "direct3d.h"
#include "GameTimer.h"
#include "input.h"
#include "GameObject.h"
#include "ObjectGenerator.h"
#include "Sprite.h"
#include "XAudio2.h"

BOOL GameClear_Initialize();
BOOL GameClear_Update();
void GameClear_Draw();
void GameClear_Relese();