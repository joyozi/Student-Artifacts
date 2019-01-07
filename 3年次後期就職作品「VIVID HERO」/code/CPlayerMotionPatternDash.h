//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternDashのヘッダーファイル[CPlayerMotionPatternDash.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPLAYERMOTIONPATTERN_DASH_H_
#define _CPLAYERMOTIONPATTERN_DASH_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CPlayerMotionPattern.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPlayerMotionPatternDash : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternDash(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternDash();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);

};



#endif
