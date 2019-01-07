//◇-------------------------------------------------------------------------◇
//
//	File:CPauseのヘッダーファイル[CPause.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPAUSE_H_
#define _CPAUSE_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "main.h"
#include "CScene2D.h"
#include "input.h"

typedef enum
{
	PAUSE_MENU_CONTINUE,
	PAUSE_MENU_RETRY,
	PAUSE_MENU_QUIT,
	PAUSE_MENU_MAX
}PAUSE_MENU;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPause
{
public:
	CPause();
	virtual ~CPause();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual bool PauseNowJudge(void);

private:
	static const int	PAUSE_TYOUSEI = (200);

	PAUSE_MENU			m_SelectMenu;
	CScene2D*			m_pPause2D[7];
	bool				m_PauseJudge;
};


#endif
