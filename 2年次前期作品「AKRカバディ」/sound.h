//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_TITLE_BGM = 0,			// BGM1
	SOUND_LABEL_GAME_MAIN,				// BGM2
	SOUND_LABEL_SE_DECIDE,				// ���艹
	SOUND_LABEL_SE_bomb000,				// ������
	SOUND_LABEL_SE_gakutyou_beam_05,	// ���[�U�[���ˉ�
	SOUND_LABEL_SE_sen_ge_bom18,		// ��Ĕ�����
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
