//◇-------------------------------------------------------------------------◇
//
//	ヘッダー[input.h]
//	AT12A271　当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CINPUT_H_
#define _CINPUT_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "main.h"

#define Repeat_Num (30)		//キーリピートの待ち時間

//◇-----------------------------------◇
//クラス定義
//◇-----------------------------------◇
class CInput
{
public:
	CInput();
	~CInput();

	HRESULT InitKeyboard(HINSTANCE hInstance,HWND hWnd);
	void UninitKeyboard(void);
	void UpdateKeyboard(void);

	static bool GetKeyboardPress(int nKey);
	static bool GetKeyboardTrigger(int nKey);
	static bool GetKeyboardRelease(int nKey);
	static bool GetKeyboardRepeat(int nKey);

private:
	LPDIRECTINPUT8			g_pDInput;				//DirectInputインタフェースへのポインタ
	LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard;	//入力デバイス(キーボード)へのポインタ
	static BYTE				g_aKeyState[256];					//キーボード情報

	static BYTE				g_aKeyStateTrigger[256];	//キートリガー情報
	static BYTE				g_aKeyStateRelease[256];	//キーリリース情報
	static BYTE				g_aKeyStateRepeat[256];		//キーリピート情報
	static int				g_aKeyStateRepeatCount[256];		//リピートのカウント

	CInput * m_pInput;
};

#endif