#pragma once

//*****************************************************************************
// DX21�@�T���v���\�[�X
// �Q�[���̃��C���ƂȂ鏈���̃v���g�^�C�v�錾���L�q�����w�b�_�[�t�@�C��
// �ʏ�A�����̊֐���WinMain�̓K�؂ȏꏊ�ŌĂяo���ăQ�[���������悤�ɂ���B
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
#include "SnowBall.h"
#include "Enemy.h"
#include "Shielding.h"


BOOL Game_Initialize();
BOOL Game_Update();
void Game_Draw();
void Game_Relese();