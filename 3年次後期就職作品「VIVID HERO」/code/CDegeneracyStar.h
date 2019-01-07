//◇-------------------------------------------------------------------------◇
//
//	File:CDegeneracyStarのヘッダーファイル[CDegeneracyStar.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CDEGENERACYSTAR_H_
#define _CDEGENERACYSTAR_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CDegeneracyPolygon.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CDegeneracyStar : public CDegeneracyPolygon
{
public:
	CDegeneracyStar(int nPriority = 52);
	virtual ~CDegeneracyStar();

	virtual void SetOnlyInit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CDegeneracyStar *Create(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot);

private:
	static const int DEGENERACYSTAR_MAX = 2048*3;

	D3DXCOLOR m_PolygonColor[DEGENERACYSTAR_MAX];
	bool m_PolygonColorJudge[DEGENERACYSTAR_MAX];

};

#endif