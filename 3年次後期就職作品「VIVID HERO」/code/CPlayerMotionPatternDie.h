//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternDieのヘッダーファイル[CPlayerMotionPatternDie.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPLAYERMOTIONPATTERN_DIE_H_
#define _CPLAYERMOTIONPATTERN_DIE_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CPlayerMotionPattern.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPlayerMotionPatternDie : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternDie(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternDie();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);
};



#endif
