//◇-------------------------------------------------------------------------◇
//
//	File:CInput_Controllerのヘッダーファイル[CInput_Controller.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CINPUTCONTROLLER_H_
#define _CINPUTCONTROLLER_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "main.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CInput_Controller
{
public:
	CInput_Controller();
	virtual ~CInput_Controller();

	virtual HRESULT Init(HINSTANCE hInstance,HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	
	BOOL CALLBACK EnumJoyCallback( const DIDEVICEINSTANCE* pdidInstance,VOID* pContext);

private:
	LPDIRECTINPUT8 g_pDInput;				//DirectInputインタフェースへのポインタ
	LPDIRECTINPUTDEVICE8 g_pDIDevController;	//入力デバイス(キーボード)へのポインタ


};


#endif
