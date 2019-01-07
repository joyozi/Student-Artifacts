//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternRapidDownのヘッダーファイル[CPlayerMotionPatternRapidDown.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPLAYERMOTIONPATTERN_RAPIDDOWN_H_
#define _CPLAYERMOTIONPATTERN_RAPIDDOWN_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CPlayerMotionPattern.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPlayerMotionPatternRapidDown : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternRapidDown(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternRapidDown();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);
	
private:
	int m_MoveDownCnt;
};



#endif
