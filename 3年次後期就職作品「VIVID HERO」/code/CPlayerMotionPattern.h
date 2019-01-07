//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternのヘッダーファイル[CPlayerMotionPattern.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPLAYERMOTIONPATTERN_BASIC_H_
#define _CPLAYERMOTIONPATTERN_BASIC_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include <Windows.h>
#include "sound.h"

class CPlayerModel;
class CSceneModelMotion;

//◇-----------------------------------◇
//列挙型
//◇-----------------------------------◇

typedef enum{
	PMOVE_NUTORAL = 0,
	PMOVE_MOVE,
	PMOVE_SHOT,
	PMOVE_SWORDACCEL,
	PMOVE_SWORDATTACK,
	PMOVE_HOMINGMISSILE,
	PMOVE_DAMAGE,
	PMOVE_RAPIDUP,
	PMOVE_RAPIDDOWN,

	PMOVE_SHOTMOVE_L,
	PMOVE_SHOTMOVE_R,

	PMOVE_SWORDATTACK_2ND,

	PMOVE_MAX
}PLAYER_MOTION;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPlayerMotionPattern
{
public:
	CPlayerMotionPattern(){}
//	virtual ~CPlayerMotionPattern() = 0{}
	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion) = 0;
};


#endif
