//◇-------------------------------------------------------------------------◇
//
//	File:CGameStartのヘッダーファイル[CGameStart.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CGAMESTART_H_
#define _CGAMESTART_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CScene2D.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CGameStart : public CScene2D
{
public:
	CGameStart(int nPriority = 120);
	virtual ~CGameStart();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual bool GetGameStartEnd(void);

	static CGameStart *Create(void);

private:
	static const int GAMESTARTLOGO_TIME = 120;
	static const int GAMESTARTLOGO_FADEOUT_TIME = 20;

	CScene2D*	m_pGameStart;
	int			m_GameStartTime;
	bool		m_EndJudge;
	D3DXVECTOR3	m_FadeOutSize;
	D3DXCOLOR	m_FadeOutCol;
};


#endif
