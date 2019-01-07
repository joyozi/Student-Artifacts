//◇-------------------------------------------------------------------------◇
//
//	File:CEnemyPattern000のヘッダーファイル[CEnemyPattern000.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CEnemyPattern000_H_
#define _CEnemyPattern000_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CEnemyPattern.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CEnemyPattern000 : public CEnemyPattern
{
public:
	CEnemyPattern000();
	virtual ~CEnemyPattern000();

	virtual void Update(CScene *pEnemy)override;

private:
	float m_Angle;

};


#endif
