//◇-------------------------------------------------------------------------◇
//
//	File:マネージャのファイル[CManager.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _RENDERER_H_
#define _RENDERER_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "main.h"

class CDebugProc;

//◇-----------------------------------◇
//プロトタイプ宣言
//◇-----------------------------------◇
HRESULT ChangeWindowSize(void);
HRESULT InitGraphics(void);
void CleanupDXGraphics(void);

HWND GethWnd();
HINSTANCE GetHInstance();

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CRenderer
{
public:
	CRenderer(){}		//privateの２つにNULLを入れるだけ
	~CRenderer(){}

	//大文字のBOOLは４バイト、boolは１ビットとかいろいろ違いがあるらしい

	//デヴァイスの生成。boolで作成できたかどうかを教える
	HRESULT Init(HINSTANCE hInstance);
	void Update(void);
	void Uninit(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void);

protected:
	static CDebugProc *m_pDebugProcPointer;

};


#endif