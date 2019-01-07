//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternSwordAttackのヘッダーファイル[CPlayerMotionPatternSwordAttack.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPLAYERMOTIONPATTERN_SWORDATTACK_H_
#define _CPLAYERMOTIONPATTERN_SWORDATTACK_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CPlayerMotionPattern.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPlayerMotionPatternSwordAttack : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternSwordAttack(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternSwordAttack();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);

private:
	bool m_2ndSwordJudge;
	bool m_StartInfoJudge;

};



#endif
