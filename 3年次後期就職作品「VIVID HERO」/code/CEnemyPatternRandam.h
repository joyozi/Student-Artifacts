//◇-------------------------------------------------------------------------◇
//
//	File:CEnemyPatternRandamのヘッダーファイル[CEnemyPatternRandam.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CENEMYPATTERNRANDAM_H_
#define _CENEMYPATTERNRANDAM_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CEnemyPattern.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CEnemyPatternRandam : public CEnemyPattern
{
public:
	CEnemyPatternRandam();
	virtual ~CEnemyPatternRandam();

	virtual void Update(CScene *pEnemy)override;

private:
	D3DXVECTOR3 m_Angle;
	D3DXVECTOR3 m_OldPos;

	int m_MoveCnt;
	int m_MoveCntMax;
};


#endif
