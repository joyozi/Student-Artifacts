//◇-------------------------------------------------------------------------◇
//
// サウンド処理 [sound.h]
// Author : Tanaka Akira
//
//◇-------------------------------------------------------------------------◇
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//◇-------------------------------------------------------------------------◇
// サウンドファイル
//◇-------------------------------------------------------------------------◇
typedef enum
{
	SOUND_LABEL_GAMEMAINBGM = 0,
	SOUND_LABEL_TITLE,
	SOUND_LABEL_GAMECLEAR,
	SOUND_LABEL_GAMEOVER,
	SOUND_LABEL_cannon1,

	SOUND_LABEL_Damage,
	SOUND_LABEL_GunKamae,
	SOUND_LABEL_Missle_Explosion,
	SOUND_LABEL_Missle_Shot,
	SOUND_LABEL_Sword1st,
	SOUND_LABEL_Sword2nd,
	SOUND_LABEL_WeaponShot,
	SOUND_LABEL_EnemyDied,
	SOUND_LABEL_Decision00,
	SOUND_LABEL_Decision01,
	SOUND_LABEL_EnemyPop00,
	
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//◇-------------------------------------------------------------------------◇
// プロトタイプ宣言
//◇-------------------------------------------------------------------------◇
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
