//◇-------------------------------------------------------------------------◇
//
//	File:CBullet000のヘッダーファイル[CBullet000.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CBULLET000_H_
#define _CBULLET000_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CSceneBillboard.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CBullet000 : public CSceneBillboard
{
public:
	CBullet000(int nPriority = /*9*/50);
	virtual ~CBullet000();

	virtual void Update(void);

	float GetCollisionRadius(int Num)override;
	virtual void CollisionAction(CLASS_TYPE Type,int Num)override;

	static CBullet000 *Create(D3DXVECTOR3 ShotPos,D3DXVECTOR3 TargetPos);

private:

	float m_Speed;

	D3DXVECTOR3 m_ShotVec;
};


#endif
