#pragma once

#include <Windows.h>

#include "direct3d.h"
#include "GameTimer.h"
#include "input.h"
#include "GameObject.h"
#include "MapGeneration.h"
#include "ObjectGenerator.h"
#include "Sprite.h"
#include "XAudio2.h"

BOOL Level_Initialize(StageScore score);
BOOL Level_Update();
void Level_Draw();
void Level_Relese();