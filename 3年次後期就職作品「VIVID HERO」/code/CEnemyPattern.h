//◇-------------------------------------------------------------------------◇
//
//	File:CEnemyPatternのヘッダーファイル[CEnemyPattern.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CENEMYPATTERN_H_
#define _CENEMYPATTERN_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "main.h"
#include "CScene.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CEnemyPattern
{
public:
	CEnemyPattern(){}
	virtual ~CEnemyPattern() = 0{}

	virtual void Update(CScene *pEnemy) = 0;
};


#endif
