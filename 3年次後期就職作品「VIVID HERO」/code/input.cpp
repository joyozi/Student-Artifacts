//◇-------------------------------------------------------------------------◇
//
//	File:インプットcppファイル[input.cpp]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include"input.h"

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
BYTE CInput::g_aKeyState[] = {NULL};

BYTE CInput::g_aKeyStateTrigger[] = {NULL};		//キートリガー情報
BYTE CInput::g_aKeyStateRelease[] = {NULL};		//キーリリース情報
BYTE CInput::g_aKeyStateRepeat[] = {NULL};		//キーリピート情報
int CInput::g_aKeyStateRepeatCount[] = {0};		//リピートのカウント

//◇---------------------------------◇
//コンストラクタ
//◇---------------------------------◇
CInput::CInput()
{
	g_pDInput = NULL;
	g_pDIDevKeyboard = NULL;

	for(int i = 0;i < 256;i++)
	{
		g_aKeyState[i] = NULL;

		CInput::g_aKeyStateTrigger[i] = NULL;
		CInput::g_aKeyStateRelease[i] = NULL;
		CInput::g_aKeyStateRepeat[i] = NULL;
		CInput::g_aKeyStateRepeatCount[i] = 0;
	}

}

//◇---------------------------------◇
//デストラクタ
//◇---------------------------------◇
CInput::~CInput()
{

}


//◇---------------------------------◇
//インプットの初期化処理
//◇---------------------------------◇
HRESULT CInput::InitKeyboard(HINSTANCE hInstance,HWND hWnd)
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

//◇---------------------------------◇
//インプットの終了処理
//◇---------------------------------◇
void CInput::UninitKeyboard(void)
{
	if(g_pDIDevKeyboard != NULL)
	{
		g_pDIDevKeyboard -> Unacquire();
		g_pDIDevKeyboard -> Release();
		g_pDIDevKeyboard = NULL;

	}
	if(g_pDInput != NULL)
	{
		//リリースNULL
		g_pDInput -> Release();
		g_pDInput = NULL;
	}
}

//◇---------------------------------◇
//インプットの更新処理
//◇---------------------------------◇
void CInput::UpdateKeyboard(void)
{
	BYTE aKeyState[256];

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

			g_aKeyState[nKey] = aKeyState[nKey];
		}
	}
	else
	{
		g_pDIDevKeyboard -> Acquire();
	}

}
//◇---------------------------------◇
//トリガー操作
//◇---------------------------------◇
bool CInput::GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey]&0x80)?true:false;
}
//◇---------------------------------◇
//リリース操作
//◇---------------------------------◇
bool CInput::GetKeyboardRelease(int nKey)
{
	return(g_aKeyStateRelease[nKey]&0x80)?true:false;
}
//◇---------------------------------◇
//プレス操作
//◇---------------------------------◇
bool CInput::GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey]&0x80)?true:false;
}

//◇---------------------------------◇
//リピート操作
//◇---------------------------------◇
bool CInput::GetKeyboardRepeat(int nKey)
{
	return(g_aKeyStateRepeat[nKey]&0x80)?true:false;
}

