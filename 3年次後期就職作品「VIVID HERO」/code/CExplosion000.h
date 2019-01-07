//��-------------------------------------------------------------------------��
//
//	File:CExplosion000�̃w�b�_�[�t�@�C��[CExplosion000.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CExplosion000_H_
#define _CExplosion000_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CDegeneracyAnimation.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
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
