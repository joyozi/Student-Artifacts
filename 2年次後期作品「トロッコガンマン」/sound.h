//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_TITLEBGM = 0,		// たいとるBGM 
	SOUND_LABEL_GAMEBGM,			//ゲームBGM
	SOUND_LABEL_GUNFIRE,			// 弾の発射音
	SOUND_LABEL_BULLET_EXPLOSION,	// 着弾時の爆発音
	SOUND_LABEL_JUMP,				// ジャンプ音
	SOUND_LABEL_DAMAGE_SE,			// 本体が弾に当たった時の音
	SOUND_LABEL_MONSTER7,			// ？
	SOUND_LABEL_FANFALE,			// ファンファーレ
	SOUND_LABEL_SE_LOCKON,			// ロックオン音
	SOUND_LABEL_SE_HIT,				// ヒット音
	SOUND_LABEL_SE_GUARD,			// ガード音
	SOUND_LABEL_SE_EXPLOSION,		// 爆発音
	SOUND_LABEL_SE_JUMP,			// ジャンプ音
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
