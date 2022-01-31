//=============================================================================
//
// サウンド処理 [XAudio2.h]
//
//=============================================================================
#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_

#include <xaudio2.h>

// サウンドファイル
typedef enum
{
	SOUND_LABEL_BGM_TITLE,
	SOUND_LABEL_BGM_KAMISHIBAI,
	SOUND_LABEL_BGM_LEVEL,
	SOUND_LABEL_BGM_GAME,		// サンプルBGM
	SOUND_LABEL_BGM_GAMEOVER,
	SOUND_LABEL_BGM_CLEAR,
	SOUND_LABEL_SE_ENEMYSTAN,
	SOUND_LABEL_SE_PLAYERCRUSH,
	SOUND_LABEL_SE_SNOWHUNDA,
	SOUND_LABEL_SE_PLAYERGROW,
	SOUND_LABEL_SE_BUTTON,
	SOUND_LABEL_SE_MOVE,
	SOUND_LABEL_SE_PAPER,
	SOUND_LABEL_SE_ICEHUNDA,
	SOUND_LABEL_SE_KA_SORU,

	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT XA_Initialize(void);
void XA_Release(void);
void XA_Play(SOUND_LABEL label);
void XA_Stop(SOUND_LABEL label);
void XA_Pause(SOUND_LABEL label);
#endif
