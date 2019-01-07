//◇-------------------------------------------------------------------------◇
//
//	File:CExplosion000のヘッダーファイル[CExplosion000.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CExplosion000_H_
#define _CExplosion000_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CDegeneracyAnimation.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CExplosion000 : public CDegeneracyAnimation
{
public:
	CExplosion000(int nPriority = 60);

	static CExplosion000 *Create(LPCTSTR TexName,int DivideNumX,int DivideNumY,int AnimTime,int NeedPolygonNum);
	
	int ExplosionSet1Set(D3DXVECTOR3 Pos);
	int ExplosionSet1Set(D3DXVECTOR3 Pos,float TexWidth,float TexHeight);
	void ExplosionSet3Set(D3DXVECTOR3 Pos);

	void ExplosionSetCustom(int SetNum,D3DXVECTOR3 Pos[],D3DXVECTOR3 Size[]);
	void ExplosionMuzzleFlash(D3DXVECTOR3 CenterPos);
	void ExplosionPlayerBulletHit(D3DXVECTOR3 CenterPos);

private:
	int m_NeedPolygonNum;
};


#endif
