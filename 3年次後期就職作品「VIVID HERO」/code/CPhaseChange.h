//◇-------------------------------------------------------------------------◇
//
//	File:CPhaseChangeのヘッダーファイル[CPhaseChange.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPHASECHANGE_H_
#define _CPHASECHANGE_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "main.h"
#include "CPhase.h"
#include "CScene.h"

class CPhase;
class CPhaseChange;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPhaseChange
{
public:
	CPhaseChange();
	virtual ~CPhaseChange();

	virtual HRESULT Init(CPhase *pStartPhase);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void PhaseChange(CPhase *PhaseNext)
	{
		if(m_pFade == NULL)
		{
			m_pPhaseNext = PhaseNext;
		}
		else
		{
			delete PhaseNext;
		}
	}

	CPhase *GetPhasePointer(){return m_pPhase;}

private:
	static CPhase*	m_pPhase;		//今のフェーズ
	CPhase*			m_pPhaseNext;			//次に行きたいフェーズ
	CFade*			m_pFade;
};


#endif
