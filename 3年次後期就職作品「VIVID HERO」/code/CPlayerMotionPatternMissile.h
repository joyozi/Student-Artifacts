//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternMissileのヘッダーファイル[CPlayerMotionPatternMissile.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPLAYERMOTIONPATTERN_MISSLE_H_
#define _CPLAYERMOTIONPATTERN_MISSLE_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CPlayerMotionPattern.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPlayerMotionPatternMissile : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternMissile(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternMissile();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);

private:
	bool m_ShotMusicJudge;
};



#endif