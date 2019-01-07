//◇-------------------------------------------------------------------------◇
//
//	File:CPhaseResultのヘッダーファイル[CPhaseResult.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPHASERESULT_H_
#define _CPHASERESULT_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CPhase.h"

class CScene2D;

typedef enum{
	RESULT_NONE = 0,
	RESULT_CLEAR,
	RESULT_GAMEOVER,
	RESULT_MAX
}RESULT_JUDGE;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPhaseResult : public CPhase
{
public:
	CPhaseResult(PHASE Phase = PHASE_RESULT);
	CPhaseResult(PHASE Phase,RESULT_JUDGE Judge = RESULT_CLEAR);

	virtual ~CPhaseResult();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

private:
	CScene2D*		m_pScene2D;
	D3DXCOLOR		m_FlashCol[4];
	bool			m_FlashJudge;			//falseで減ってく
	RESULT_JUDGE	m_ResultJudge;
	int				m_GoTitleCnt;
};


#endif
