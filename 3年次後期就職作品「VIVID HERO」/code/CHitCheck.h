//��-------------------------------------------------------------------------��
//
//	File:CHitCheck�̃w�b�_�[�t�@�C��[CHitCheck.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CHITCHECK_H_
#define _CHITCHECK_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "main.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CHitCheck
{
public:
	CHitCheck();
	virtual ~CHitCheck();

	static int HitCheck(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1);

	static float dotProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr);
	static D3DXVECTOR3 crossProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr );

	static D3DXVECTOR3 HitIntersection( D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1 );

	static float ConnectYVertex(const D3DXVECTOR3 Player_Pos,const D3DXVECTOR3 Polygon_Pos0,const D3DXVECTOR3 Polygon_Nor);
	static float ConnectYVertex(const D3DXVECTOR3 Player_Pos,const D3DXVECTOR3 Polygon_Pos0,const D3DXVECTOR3 Polygon_Pos1,const D3DXVECTOR3 Polygon_Pos2);
};


#endif
