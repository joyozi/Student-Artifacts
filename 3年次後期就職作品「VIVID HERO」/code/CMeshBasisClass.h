//◇-------------------------------------------------------------------------◇
//
//	File:CMeshBasisClassのヘッダーファイル[CMeshBasisClass.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _MESHBASISCLASS_H_
#define _MESHBASISCLASS_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
//#include "main.h"
#include "CScene3D.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CMeshBasisClass : public CScene3D
{
public:
	CMeshBasisClass(int nPriority = 31);
	virtual ~CMeshBasisClass();

	virtual void Uninit(void);
	virtual void Draw(void);

protected:
	LPDIRECT3DINDEXBUFFER9	m_IdxBuffer;
	int						m_VtxNum;
	int						m_IndexNum;
	int						m_PolygonNum;
	WORD*					m_pIdx;
};


#endif
