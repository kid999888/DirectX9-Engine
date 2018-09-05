//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���ŝ�
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "Windows.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_TITLE = 0,	// BGM�^�C�g��
	SOUND_LABEL_BGM_GAME,		// BGM�Q�[��
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_BOM,			// �����ˉ�
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif