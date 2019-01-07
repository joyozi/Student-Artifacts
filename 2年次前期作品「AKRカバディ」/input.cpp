//◇-------------------------------------------------------------------------◇
//
//	インプットcppファイル[input.cpp]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include"main.h"
#include"input.h"
//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECTINPUT8 g_pDInput = NULL;				//DirectInputインタフェースへのポインタ
LPDIRECTINPUTDEVICE8 g_pDIDevKeyboard = NULL;	//入力デバイス(キーボード)へのポインタ
BYTE g_aKeyState[256];			//キーボード情報

//↓ノートに書いてない
BYTE g_aKeyStateTrigger[256];	//キートリガー情報
BYTE g_aKeyStateRelease[256];	//キーリリース情報
BYTE g_aKeyStateRepeat[256];	//キーリピート情報
int g_aKeyStateRepeatCount[256];//
//◇-------------------------------------------------------------------------◇
//インプットの初期化処理
//◇-------------------------------------------------------------------------◇
HRESULT InitKeyboard(HINSTANCE hInstance,HWND hWnd)
{
	HRESULT hr;
	int nID;
	if(g_pDInput == NULL)
	{
		hr = DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&g_pDInput,NULL);
		
		if(FAILED(hr))
		{
			nID = MessageBox(NULL,"インプット初期化処理がおかしい","インプット初期化処理がおかしいです",MB_YESNO);
			return hr;
		}
	}
	hr = g_pDInput -> CreateDevice(GUID_SysKeyboard,&g_pDIDevKeyboard,NULL);
	if(FAILED(hr))
		{
			nID = MessageBox(NULL,"処理がおかしい","処理がおかしいです",MB_YESNO);
			return hr;
		}
	hr = g_pDIDevKeyboard -> SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
		{
			nID = MessageBox(NULL,"処理がおかしい","処理がおかしいです",
							MB_YESNO);
			return hr;
		}
	hr = g_pDIDevKeyboard -> SetCooperativeLevel(hWnd,DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);	//強調モードを設定
	if(FAILED(hr))
	{
		nID = MessageBox(NULL,
						"処理がおかしい","処理がおかしいです",MB_YESNO);
		return hr;
	}

	g_pDIDevKeyboard -> Acquire();
	return S_OK;
}

//-------------------------------------
//インプットの終了処理
//-------------------------------------
void UninitKeyboard(void)
{
	if(g_pDIDevKeyboard != NULL)
	{
		g_pDIDevKeyboard -> Unacquire();
	}
	if(g_pDInput != NULL)
	{
		//リリースNULL
	}
}

//-------------------------------------
//インプットの更新処理
//-------------------------------------
void UpdateKeyboard(void)
{
	BYTE aKeyState[256];
	int nID;
	static int PlusCnt;

	if(SUCCEEDED(g_pDIDevKeyboard -> GetDeviceState(sizeof(aKeyState),&aKeyState[0])))
	{
		for(int nKey = 0;nKey < 256;nKey++)
		{
			//↓ここから下はノートに書いてない----------------------
			//キートリガーの処理
			g_aKeyStateTrigger[nKey] = (g_aKeyState[nKey] ^ aKeyState[nKey]) & aKeyState[nKey];

			//キーリリースの処理
			g_aKeyStateRelease[nKey] = (g_aKeyState[nKey] ^ aKeyState[nKey]) & g_aKeyState[nKey];

			//キーリピートの処理
			if(GetKeyboardPress(nKey) == true)
			{
				g_aKeyStateRepeatCount[nKey]++;
				if(g_aKeyStateRepeatCount[nKey] > Repeat_Num)
				{
					g_aKeyStateRepeat[nKey] = aKeyState[nKey];
				}
			}
			else
			{
				g_aKeyStateRepeatCount[nKey] = 0;
			}

/*			if(g_aKeyStateRepeatCount[nKey] > 5)
			{
				g_aKeyStateRepeat[nKey] = aKeyState[nKey];
				
				if(aKeyState[nKey] = false)
				{
					g_aKeyStateRepeatCount[nKey] = 0;
				}
			}
		}
*/			g_aKeyState[nKey] = aKeyState[nKey];
		}
	}
	else
	{
		g_pDIDevKeyboard -> Acquire();
	}

}
//↓ノートに書いてない-------------------------------------------
	//トリガー操作
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey]&0x80)?true:false;
}

	//リリース操作
bool GetKeyboardRelease(int nKey)
{
	return(g_aKeyStateRelease[nKey]&0x80)?true:false;
}
//↑------------------------------------------------------------
	//プレス操作
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey]&0x80)?true:false;
}

	//リピート操作
bool GetKeyboardRepeat(int nKey)
{
	return(g_aKeyStateRepeat[nKey]&0x80)?true:false;
}