//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternRapidUpのヘッダーファイル[CPlayerMotionPatternRapidUp.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPLAYERMOTIONPATTERN_RAPIDUP_H_
#define _CPLAYERMOTIONPATTERN_RAPIDUP_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CPlayerMotionPattern.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPlayerMotionPatternRapidUp : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternRapidUp(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternRapidUp();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);

private:
	int m_MoveUpCnt;
};



#endif
