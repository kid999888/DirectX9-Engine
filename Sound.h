//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 王暁晨
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "Windows.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_TITLE = 0,	// BGMタイトル
	SOUND_LABEL_BGM_GAME,		// BGMゲーム
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_SE_BOM,			// 爆発射音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif