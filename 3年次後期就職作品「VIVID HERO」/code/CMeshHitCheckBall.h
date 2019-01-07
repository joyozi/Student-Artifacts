//◇-------------------------------------------------------------------------◇
//
//	File:CMeshHitCheckBallのヘッダーファイル[CMeshHitCheckBall.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CMESHHITCHECKBALL_H_
#define _CMESHHITCHECKBALL_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CMeshBasisClass.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CMeshHitCheckBall : public CMeshBasisClass
{
public:
	CMeshHitCheckBall(int nPriority = 80);
	virtual ~CMeshHitCheckBall();

	virtual HRESULT Init(void);
	virtual void Draw(void);

	virtual void SetBallRadius(float Radius);

	static CMeshHitCheckBall *Create();

private:
	static const int	CHECKBALL_DANSUU = 5;
	static const int	CHECLBALL_ONEVTX = 6;							//一つの横の広がりにある頂点数
	static const int	CHECKBALL_VTXNUM = CHECKBALL_DANSUU * CHECLBALL_ONEVTX;

	float				m_BallRadius;
	D3DXVECTOR3			m_BallVtxVec[CHECKBALL_VTXNUM];
};


#endif
