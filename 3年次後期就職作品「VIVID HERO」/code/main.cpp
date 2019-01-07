//◇-------------------------------------------------------------------------◇
//
//	File:真っ暗ウィンドウ[main.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//===================
//メモリリークのファイル
//===================
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "CManager.h"
#include "resource.h"
#include "WndProc.h"
#include "CDebugProc.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇
HRESULT Init(HINSTANCE hInstance);

void Uninit(void);
void Update(void);
void Draw(void);

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
int g_nCountFPS = 0;	//FPSカウンタ

CManager *g_pCManager;

//◇-------------------------------------------------------------------------◇
//メイン関数
//◇-------------------------------------------------------------------------◇
int	WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	//メモリリークの検査
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	timeBeginPeriod(1);
	dwExecLastTime =
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	MSG msg;

	if(FAILED(Init(hInstance)))
	{
		return -1;
	}

	//メッセージループ
	while(1)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)!=0)
		{	//windowプログラム
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//メッセージ翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//FPS初期化処理
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	//0.5秒経過
			{
				g_nCountFPS = (dwFrameCount * 1000)/(dwCurrentTime - dwFPSLastTime);	//FPSを計測
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if((dwCurrentTime - dwExecLastTime) >= (1000/60))
			{
				dwExecLastTime = dwCurrentTime;

				//DirectXプログラム
				//更新処理
				Update();
				//描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}

	Uninit();	//終了処理

	timeEndPeriod(1);
	
	return(int)msg.wParam;
}

//◇-------------------------------------◇
//	(初期化処理)
//◇-------------------------------------◇
HRESULT Init(HINSTANCE hInstance)
{	
	CManager *pManager;
	pManager = new CManager;
	pManager -> Init(hInstance);

	g_pCManager = pManager;

	return S_OK;
}
//◇-------------------------------------◇
//終了処理
//◇-------------------------------------◇
void Uninit(void)
{	
	g_pCManager->Uninit();
	delete g_pCManager;
	g_pCManager = NULL;
}

//◇-------------------------------------◇
//更新処理
//◇-------------------------------------◇
void Update(void)
{
	CDebugProc::Print("FPS : %d\n",g_nCountFPS);
	
	g_pCManager->Update();// = pCamera;
}

//◇-------------------------------------◇
//描画処理
//◇-------------------------------------◇
void Draw(void)
{
	g_pCManager->Draw();// = pCamera;
}

//◇-------------------------------------◇
//デバイスの取得処理
//◇-------------------------------------◇
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pCManager->GetDevice();
}
