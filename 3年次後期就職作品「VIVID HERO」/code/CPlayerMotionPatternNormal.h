//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternNormalのヘッダーファイル[CPlayerMotionPatternNormal.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPLAYERMOTIONPATTERN_NORMAL_H_
#define _CPLAYERMOTIONPATTERN_NORMAL_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CPlayerMotionPattern.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPlayerMotionPatternNormal : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternNormal();									//こいつにだけ引数なしコンスト作成
	CPlayerMotionPatternNormal(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternNormal();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);

private:
	int m_DowblePushCntL;
	int m_DowblePushCntR;

	bool m_DowblePushJudgeL;
	bool m_DowblePushJudgeR;
};



#endif
