//◇-------------------------------------------------------------------------◇
//
//	File:CEnemyBullet000のヘッダーファイル[CEnemyBullet000.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CEnemyBullet000_H_
#define _CEnemyBullet000_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CSceneBillboard.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CEnemyBullet000 : public CSceneBillboard
{
public:
	CEnemyBullet000(int nPriority = /*9*/50);
	virtual ~CEnemyBullet000();

	virtual void Update(void);

	float GetCollisionRadius(int Num)override;
	virtual void CollisionAction(CLASS_TYPE Type,int Num)override;

	static CEnemyBullet000 *Create(D3DXVECTOR3 ShotPos,D3DXVECTOR3 TargetPos);

private:

	float m_Speed;

	D3DXVECTOR3 m_ShotVec;
};


#endif
