//◇-------------------------------------------------------------------------◇
//
//	File:CPhaseTitleのヘッダーファイル[CPhaseTitle.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPHASETITLE_H_
#define _CPHASETITLE_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CPhase.h"

class CTitleMenu;
class CCamera;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPhaseTitle : public CPhase
{
public:
	CPhaseTitle(PHASE Phase = PHASE_TITLE);
	virtual ~CPhaseTitle();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

private:
	CTitleMenu*		m_pTitleMenu;
	CCamera*		m_pCamera;

};


#endif
