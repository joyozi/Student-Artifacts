//◇-------------------------------------------------------------------------◇
//
//	File:CInput_Controllerのファイル[CInput_Controller.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CInput_Controller.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CInput_Controllerのコンストラクタ
//◇-----------------------------------◇
CInput_Controller::CInput_Controller()
{
	g_pDInput = NULL;
	g_pDIDevController = NULL;
}

//◇-----------------------------------◇
//CInput_Controllerのデストラクタ
//◇-----------------------------------◇
CInput_Controller::~CInput_Controller()
{

}

//◇-----------------------------------◇
//CInput_Controllerの初期化処理
//◇-----------------------------------◇
HRESULT CInput_Controller::Init(HINSTANCE hInstance,HWND hWnd)
{
	HRESULT hr;
	int nID;

	hr = DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&g_pDInput,NULL);
	if(FAILED(hr))
	{
		nID = MessageBox(NULL,"インプット初期化処理がおかしい","インプット初期化処理がおかしいです",MB_YESNO);
		return hr;
	}


	hr = g_pDInput -> CreateDevice(GUID_SysKeyboard,&g_pDIDevController,NULL);
	if(FAILED(hr))
	{
		nID = MessageBox(NULL,"処理がおかしい","処理がおかしいです",MB_YESNO);
		return hr;
	}



	//使用可能なデバイスを調べる
//	hr = g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL,EnumJoyCallback,NULL,DIEDFL_ATTACHEDONLY);

	if(FAILED(hr)|| g_pDIDevController == NULL)
	{
		////オブジェクト作成失敗
	}

	hr = g_pDIDevController -> SetDataFormat(&c_dfDIJoystick2);
	if(FAILED(hr))
	{
		nID = MessageBox(NULL,"処理がおかしい","処理がおかしいです",
						MB_YESNO);
		return hr;
	}
	
	bool g_bActice = false;

	hr = g_pDIDevController->Poll();
	if(FAILED(hr))
	{
		hr = g_pDIDevController->Acquire();
		while(g_bActice && hr == DIERR_INPUTLOST)
			hr = g_pDIDevController->Acquire();
	}

	return S_OK;
}

//◇-----------------------------------◇
//CInput_Controllerの終了処理
//◇-----------------------------------◇
void CInput_Controller::Uninit(void)
{

}

//◇-----------------------------------◇
//CInput_Controllerの更新処理
//◇-----------------------------------◇
void CInput_Controller::Update(void)
{

}

//◇-----------------------------------◇
//CInput_Controllerの描画処理
//◇-----------------------------------◇
void CInput_Controller::Draw(void)
{

}

BOOL CALLBACK CInput_Controller::EnumJoyCallback(const DIDEVICEINSTANCE* pdidInstance,VOID* pContext)
{
	HRESULT hr;

	DIDEVCAPS g_diDevCaps;

	//列挙されたジョイスティックへのインタフェースを取得する
	hr = g_pDInput->CreateDevice(pdidInstance->guidInstance,&g_pDIDevController,NULL);

	if(FAILED(hr))
	{
		return DIENUM_CONTINUE;
	}


	//ジョイスティックの能力を調べる
	g_diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hr = g_pDIDevController->GetCapabilities(&g_diDevCaps);

	if(FAILED(hr))
	{
		//ジョイスティックの能力の取得に失敗
		g_pDIDevController->Release();
		g_pDIDevController = NULL;

		return DIENUM_CONTINUE;
	}

	//ジョイスティックの能力をチェックする

	return DIENUM_STOP;
	return DIENUM_CONTINUE;
}