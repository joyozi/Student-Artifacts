//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternDamagedのヘッダーファイル[CPlayerMotionPatternDamaged.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPLAYERMOTIONPATTERN_DAMAGED_H_
#define _CPLAYERMOTIONPATTERN_DAMAGED_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CPlayerMotionPattern.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPlayerMotionPatternDamaged : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternDamaged(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternDamaged();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);

private:
	int m_DamagedTimeCnt;
};



#endif
