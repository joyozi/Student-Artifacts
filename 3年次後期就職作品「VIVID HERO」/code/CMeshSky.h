//◇-------------------------------------------------------------------------◇
//
//	File:メッシュスカイのヘッダーファイル[CMeshSky.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CMESHSKY_H_
#define _CMESHSKY_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CMeshBasisClass.h"

//◇-----------------------------------◇
//マクロ定義
//◇-----------------------------------◇
#define MESHSKY_PELYGON_WIDTH		(1000)		//ポリゴンの横
#define MESHSKY_POLYGON_HEIGHT		(4000)		//ポリゴン縦
#define MESHSKY_BUNKATSU			(20)		//横の分割　上から見たとき何角形に分割するか。3分割以上で
#define MESHSKY_DANSUU				(10)		//縦の分割　横から見た時の段数

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CMeshSky : public CMeshBasisClass
{
public:
	CMeshSky(int nPriority = 34);
	~CMeshSky();

	HRESULT Init(void);
	void Update(void);

	static CMeshSky *Create(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot);
};

#endif
