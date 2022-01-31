#pragma once

//*****************************************************************************
// DX21　サンプルソース
// ゲームのメインとなる処理のプロトタイプ宣言を記述したヘッダーファイル
// 通常、これらの関数をWinMainの適切な場所で呼び出してゲームが動くようにする。
//*****************************************************************************

#include <Windows.h>

#include "direct3d.h"
#include "GameTimer.h"
#include "input.h"
#include "GameObject.h"
#include "ObjectGenerator.h"
#include "Sprite.h"
#include "XAudio2.h"

#include "Player.h"
#include "MapGeneration.h"
#include "Enemy.h"
#include "Shielding.h"
#include "Effect.h"
#include "Gauge.h"


#define ASPECT 16/9

BOOL Game_Initialize();
BOOL Game_Update();
void Game_Draw();
StageScore Game_Relese();

enum GamePause {
	gGAME,
	gPAUSE
};

enum PauseChoice {
	gRERURN,
	gRESPAWN,
	gLEVEL,
};