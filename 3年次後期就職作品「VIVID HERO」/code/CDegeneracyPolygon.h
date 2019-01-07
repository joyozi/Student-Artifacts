//◇-------------------------------------------------------------------------◇
//
//	File:CDegeneracyPolygonのヘッダーファイル[CDegeneracyPolygon.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CDEGENERACYPOLYGON_H_
#define _CDEGENERACYPOLYGON_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CMeshBasisClass.h"

struct DEGENERACYPOLYGON_SORT
{
	float Length;
	int Number;

	bool operator < (const DEGENERACYPOLYGON_SORT& right) const {
		return Length < right.Length;
	}

	bool operator > (const DEGENERACYPOLYGON_SORT& right) const {
		return Length > right.Length;
	}

	bool operator <= (const DEGENERACYPOLYGON_SORT& right) const {
		return Length <= right.Length;
	}

	bool operator >= (const DEGENERACYPOLYGON_SORT& right) const {
		return Length >= right.Length;
	}
};

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CDegeneracyPolygon : public CMeshBasisClass
{
public:
	CDegeneracyPolygon(int nPriority = 36);
	virtual ~CDegeneracyPolygon();

	virtual HRESULT Init(void);
	virtual void SetOnlyInit(void);
	virtual void Uninit(void);
	virtual void Draw(void);

	static CDegeneracyPolygon *Create(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot);
	virtual int SetPolygon(D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,float Width,float Height);
	virtual int ParticleSetColor(int Num,D3DXCOLOR Col);
	virtual int ParticleSetPosition(int Num,D3DXVECTOR3 Pos);
	virtual int ParticleUninitPosition(int Num);

private:
	static const int DEGENERACYPOLYGON_MAX = 5;

protected:
	//イニシャライザで数値を設定する
	int m_DegeneracyPolygon_Max;	//作成できるオブジェクトの最大数
	int m_DegeneracyPolygonNum;

	bool m_BillboardJudge;
	bool m_AlphaBlendJudge;
	bool m_SortJudge;
	bool m_LoopJudge;

	D3DXVECTOR3 *m_pDegeneracyPolygonPos;
	D3DXVECTOR3 *m_pDegeneracyPolygonRot;
	float *m_pLength;
	float *m_pAngle;
	bool *m_pPolygonExistJudge;
	bool *m_pPolygonUninitFlag;

	VERTEX_3D *m_VtxBox;
};


#endif
