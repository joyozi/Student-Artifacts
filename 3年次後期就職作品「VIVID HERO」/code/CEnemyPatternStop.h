//◇-------------------------------------------------------------------------◇
//
//	File:CEnemyPatternStopのヘッダーファイル[CEnemyPatternStop.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CEnemyPatternStop_H_
#define _CEnemyPatternStop_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CEnemyPattern.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CEnemyPatternStop : public CEnemyPattern
{
public:
	CEnemyPatternStop(){}
	virtual ~CEnemyPatternStop(){}

	virtual void Update(CScene *pEnemy)override{}
};


#endif
