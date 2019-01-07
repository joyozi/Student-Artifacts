//◇-------------------------------------------------------------------------◇
//
//	File:CTimerのヘッダーファイル[CTimer.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CTIMER_H_
#define _CTIMER_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CScore.h"
#include "CScene2D.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CTimer : public CScore
{
public:
	CTimer(int nPriority = 26);
	virtual ~CTimer();
	virtual void Update(void);
	
	static CTimer *Create(LPCTSTR TextureName,int SetTime,int KetaNum,float Pos_Right,float TexWidth,float TexHeight);
	static void PlusTime(int time);

private:
	int				m_TimeCnt;
	static int		m_Time;									//合計の数値。
};


#endif
