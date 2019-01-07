//◇-------------------------------------------------------------------------◇
//
//	File:CEnemy001のヘッダーファイル[CEnemy001.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CEnemy001_H_
#define _CEnemy001_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CSceneX.h"

class CBulletPattern;
class CEnemyPattern;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CEnemy001 : public CSceneX
{
public:
	CEnemy001(int nPriority = 20);
	virtual ~CEnemy001();

	virtual void Uninit(void);
	virtual void Update(void);
	
	virtual float GetCollisionRadius(int Num)override;
	virtual void CollisionAction(CLASS_TYPE Type,int Num)override;

	//銃口の数
	virtual int GetMuzzleNum(void);
	//銃口の位置
	virtual D3DXVECTOR3 GetMuzzlePos(int Num);

	static CEnemy001 *Create(LPCTSTR ModelTxtName,D3DXVECTOR3 Pos,CBulletPattern *pBullet,CEnemyPattern *pEnemy );



private:
	CBulletPattern *m_pBulletPattern;
	CEnemyPattern *m_pEnemyPattern;

	int m_Life;

	int DeathCnt;

};


#endif
