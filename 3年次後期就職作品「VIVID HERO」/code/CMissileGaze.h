//◇-------------------------------------------------------------------------◇
//
//	File:CMissileGazeのヘッダーファイル[CMissileGaze.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CMISSILEGAZE_H_
#define _CMISSILEGAZE_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CScene2D.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CMissileGaze : public CScene2D
{
public:
	CMissileGaze(int nPriority = 80);
	virtual ~CMissileGaze();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CMissileGaze *Create();
};


#endif
