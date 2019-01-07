//◇-------------------------------------------------------------------------◇
//
//	File:CDebugProcのヘッダーファイル[CDebugProc.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CDEBUGPROC_H_
#define _CDEBUGPROC_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "main.h"
//#include <stdarg.h>

//◇-----------------------------------◇
//マクロ定義
//◇-----------------------------------◇
#define INT_MAX_DIGITS (10)		//ゆび？

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇

class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static void Print(const char *fmt,...);
	static bool IsEnableDisp(void)		{ return m_bDisp; };
	static void EnableDisp(bool bDisp)	{ m_bDisp = bDisp; };
	
private:
	static LPD3DXFONT m_D3DXFont;
	static char m_aStr[1024];
	static bool m_bDisp;
};

#endif
