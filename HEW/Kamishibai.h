#pragma once

#include <Windows.h>

#include "direct3d.h"
#include "GameTimer.h"
#include "input.h"
#include "GameObject.h"
#include "ObjectGenerator.h"
#include "Sprite.h"
#include "XAudio2.h"

BOOL Kamishibai_Initialize();
BOOL Kamishibai_Update();
void Kamishibai_Draw();
void Kamishibai_Relese();