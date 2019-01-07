//◇-------------------------------------------------------------------------◇
//
//	File:CItemListのヘッダーファイル[CItemList.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CITEMLIST_H_
#define _CITEMLIST_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "main.h"

class CCamera;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CItemList
{
public:
	static D3DXVECTOR3		MatrixTruePos(int num...);
	static float			lerp(float FromA,float ToB,float Time);
	static D3DXVECTOR3		Vec3lerp(D3DXVECTOR3 FromA,D3DXVECTOR3 ToB,float Time);

	static float			AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B );

	static float			RotationOptisitacion(float Rot);
	static float			RotationOptisitacion(float ChangeRot,float Rot);
	static void				AddPosition(D3DXVECTOR3 &vec3Pos, D3DXVECTOR3 vec3Move, CCamera* pCamera);

	static float			GetLength(D3DXVECTOR3 vec3A, D3DXVECTOR3 vec3B);
	static float			GetLengthSimple(D3DXVECTOR3 vec3);

	static float			WaveHeight(D3DXVECTOR3 vecBeginWavePos, D3DXVECTOR3& vecPos, float fFrame, float fFrequency, float fDisstanceColl, float fAmplitude);
	static float			ConvDegree(float fRad);
	static float			ConvRadian(float fDeg);

	static void				SortNumber(float *pSub,int Kazu);

	static float			VecAngle_3D(D3DXVECTOR3 VecA,D3DXVECTOR3 VecB);
	static float			VecAngle_2D(D3DXVECTOR3 VecA,D3DXVECTOR3 VecB);
	static float			VecAngle_2D(float VecA_X,float VecA_Y,float VecB_X,float VecB_Y);
	static float			VecAngle_2DSimple(D3DXVECTOR3 Vec);
	static D3DXVECTOR3		VecAngle_3D_D3DX(D3DXVECTOR3 Vec);
};



#endif
