//◇-------------------------------------------------------------------------◇
//
//	File:CPhaseのヘッダーファイル[CPhase.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPHASE_H_
#define _CPHASE_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CFade.h"

class CPhase;			//前方宣言。変数が後に定義されていてもこれで解決
class CPhaseChange;		//

//◇-----------------------------------◇
//列挙型
//◇-----------------------------------◇
typedef enum{
	PHASE_NONE,
	PHASE_TITLE,
	PHASE_GAME,
	PHASE_RESULT,
	PHASE_MAX
}PHASE;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPhase
{
public:
	CPhase(PHASE Phase = PHASE_NONE){}
	virtual ~CPhase(){}

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	PHASE GetNowPhase(){return m_NowPhase;}

protected:
	CPhaseChange *GetPhaseChange(void)
	{
		return m_pPhaseChange;
	}

protected:
	PHASE m_NowPhase;

private:
	CPhaseChange *m_pPhaseChange;
};

#endif
