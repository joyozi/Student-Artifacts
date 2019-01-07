//◇-------------------------------------------------------------------------◇
//
//	File:CTargetUIのヘッダーファイル[CTargetUI.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CTARGETUI_H_
#define _CTARGETUI_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CSceneBillboard.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CTargetUI : public CSceneBillboard
{
public:
	CTargetUI(int nPriority = 101);
	virtual ~CTargetUI();

	virtual void Update(void)override;
	virtual void Draw(void)override;

	static CTargetUI *Create(LPCTSTR TextureName);

private:
	bool		m_DrawJudge;
	D3DXCOLOR	m_FadeOutColor;


};


#endif
