//◇-------------------------------------------------------------------------◇
//
//	File:CEnemy000のヘッダーファイル[CEnemy000.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CENEMY000_H_
#define _CENEMY000_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CSceneModelParts.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CEnemy000 : public CSceneModelParts
{
public:
	CEnemy000(int nPriority = 50);
	virtual ~CEnemy000();

	virtual void Update(void);
	
	virtual float GetCollisionRadius(void);
	virtual void CollisionAction(void);

	static CEnemy000 *Create(LPCTSTR ModelTxtName,D3DXVECTOR3 Pos);
};


#endif
