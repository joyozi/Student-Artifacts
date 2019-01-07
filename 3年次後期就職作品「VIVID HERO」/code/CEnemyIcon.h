//◇-------------------------------------------------------------------------◇
//
//	File:CEnemyIconのヘッダーファイル[CEnemyIcon.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CEnemyIcon_H_
#define _CEnemyIcon_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CScene2D.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CEnemyIcon : public CScene2D
{
public:
	CEnemyIcon(int nPriority = 71);
	virtual ~CEnemyIcon();

	virtual void Draw(void)override;
	virtual void SetDrawJudge(bool Judge){m_DrawJudge = Judge;}

	static CEnemyIcon *Create(LPCTSTR TextureName,D3DXVECTOR3 Pos,D3DXVECTOR3 Size);

private:
	bool m_DrawJudge;
};


#endif
