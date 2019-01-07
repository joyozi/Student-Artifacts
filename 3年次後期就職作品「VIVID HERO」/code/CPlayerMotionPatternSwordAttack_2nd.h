//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternSwordAttack_2ndのヘッダーファイル[CPlayerMotionPatternSwordAttack_2nd.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPLAYERMOTIONPATTERN_SWORDATTACK_2ND_H_
#define _CPLAYERMOTIONPATTERN_SWORDATTACK_2ND_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CPlayerMotionPattern.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPlayerMotionPatternSwordAttack_2nd : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternSwordAttack_2nd(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternSwordAttack_2nd();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);

};



#endif
