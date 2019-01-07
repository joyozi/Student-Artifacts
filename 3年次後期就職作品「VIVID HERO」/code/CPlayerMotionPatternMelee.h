//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternMeleeのヘッダーファイル[CPlayerMotionPatternMelee.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPLAYERMOTIONPATTERN_MELEE_H_
#define _CPLAYERMOTIONPATTERN_MELEE_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CPlayerMotionPattern.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPlayerMotionPatternMelee : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternMelee(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternMelee();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);

private:
	int m_AccessTimeCnt;
};



#endif
