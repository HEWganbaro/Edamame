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
	SOUND_LABEL_BGM_LEVEL,
	SOUND_LABEL_BGM_GAME,		// サンプルBGM
	SOUND_LABEL_SE_ENEMYSTAN,
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
