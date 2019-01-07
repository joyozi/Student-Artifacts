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
	SOUND_LABEL_TITLEBGM = 0,		// �����Ƃ�BGM 
	SOUND_LABEL_GAMEBGM,			//�Q�[��BGM
	SOUND_LABEL_GUNFIRE,			// �e�̔��ˉ�
	SOUND_LABEL_BULLET_EXPLOSION,	// ���e���̔�����
	SOUND_LABEL_JUMP,				// �W�����v��
	SOUND_LABEL_DAMAGE_SE,			// �{�̂��e�ɓ����������̉�
	SOUND_LABEL_MONSTER7,			// �H
	SOUND_LABEL_FANFALE,			// �t�@���t�@�[��
	SOUND_LABEL_SE_LOCKON,			// ���b�N�I����
	SOUND_LABEL_SE_HIT,				// �q�b�g��
	SOUND_LABEL_SE_GUARD,			// �K�[�h��
	SOUND_LABEL_SE_EXPLOSION,		// ������
	SOUND_LABEL_SE_JUMP,			// �W�����v��
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
