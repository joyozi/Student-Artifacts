//◇-------------------------------------------------------------------------◇
//
//	File:CBullet001のヘッダーファイル[CBullet001.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CBullet001_H_
#define _CBullet001_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CDegeneracyPolygon.h"
#include "CStructure.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CBullet001 : public CDegeneracyPolygon
{
public:
	CBullet001(int nPriority = 50);
	virtual ~CBullet001();

	virtual HRESULT Init(void)override;
	virtual void Uninit(void)override;
	virtual void Update(void)override;

	virtual float GetCollisionRadius(int Num)override;
	virtual D3DXVECTOR3 GetCollisionCenterPos(int Num)override;
	virtual void CollisionAction(CLASS_TYPE Type,int Num)override;
	virtual bool CollisionTargetSheet(CLASS_TYPE Type);

	static CBullet001 *Create();
	virtual void Bullet001Shot(D3DXVECTOR3 ShotPos,D3DXVECTOR3 TargetPos);

	virtual void Bullet001ShotUninit(int Num);


private:
	static const int SHOT_TEXNUM = 30;
	static const int SHOT_NUMMAX = 50;
	static const int BULLET001_MAX = SHOT_TEXNUM * SHOT_NUMMAX;

	static const int BULLET001_LIFEMAX = 90;

protected:
	int BulletNumCounter;					//あたり判定のカウント
	DEGENERACY_BULLET *m_pBulletInfo;

	float m_TexSize;
	float m_TexLength;

	int m_ShotTexNum;
	int m_ShotNumMax;
	int m_BulletMax;
	
	float m_Speed;

};


#endif