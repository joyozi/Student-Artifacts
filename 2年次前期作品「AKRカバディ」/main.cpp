//◇-------------------------------------------------------------------------◇
//
//	真っ暗ウィンドウ[main.cpp]
//	AT12A271　当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include"main.h"
#include"Tittle.h"
#include"Game.h"
#include"Result.h"
#include"TittlePolygon.h"
#include"GamePlayer.h"
#include"ResultPolygon.h"
#include"TittleBG.h"
#include"GameBG.h"
#include"ResultBG.h"
#include"input.h"
#include"score.h"
#include "fade.h"
#include "sound.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇
HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);
LRESULT CALLBACK WndProc(HWND nWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);
//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
LPD3DXFONT g_pD3DFont = NULL;
int g_nCountFPS = 0;	//FPSカウンタ

MODE g_mode = MODE_TITTLE;
//◇-------------------------------------------------------------------------◇
//メイン関数
//◇-------------------------------------------------------------------------◇
int	WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,BOOL nCmdShow)
{
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	timeBeginPeriod(1);
	dwExecLastTime =
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	WNDCLASSEX wcex=
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	MSG msg;
	HWND hWnd;

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//ウィンドウの生成
	hWnd = CreateWindowEx(0,
						CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						SCREEN_WIDTH,
						SCREEN_HEIGHT,
						NULL,
						NULL,
						hInstance,
						NULL);

//初期化処理
	if(FAILED(Init(hInstance,hWnd,TRUE)))
	{
		return -1;
	}

//ウィンドウの表示
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	//メッセージループ
	while(1)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)!=0)
		{		
			//windowプログラム
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
	//ウィンドウクラスの登録解除
	UnregisterClass(CLASS_NAME,wcex.hInstance);

	Uninit();	//終了処理
	
	timeEndPeriod(1);
	
	return(int)msg.wParam;
}

//-------------------------------------
//	(初期化処理)
//-------------------------------------
HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))
	{
		return E_FAIL;
	}

	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.BackBufferWidth	= SCREEN_WIDTH;		//ゲーム画面の幅
	d3dpp.BackBufferHeight	= SCREEN_HEIGHT;	//ゲーム画面の高さ
	d3dpp.BackBufferFormat	= d3ddm.Format;		//カラーモード
	d3dpp.BackBufferCount	= 1;				//バックバッファの数

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = bWindow;					//ウィンドウ/フルスクリーンモード
	d3dpp.EnableAutoDepthStencil = TRUE;		//デプスバッファ、ステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//16bitのデプスバッファをしよう

	if(bWindow == TRUE)
	{
		d3dpp.FullScreen_RefreshRateInHz = 0;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else
	{
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	//デバイスオブジェクトの生成
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dpp,&g_pD3DDevice)))
	{
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&g_pD3DDevice)))
		{
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_REF,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーテストの設定	追加したらポリゴン消える
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	
//	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);


	//サンプラーステートの設定
	g_pD3DDevice -> SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
	g_pD3DDevice -> SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);
	g_pD3DDevice -> SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);		//テクスチャの拡張時の補間設定
	g_pD3DDevice -> SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);

	InitSound(hWnd);				//音楽の初期化
	InitKeyboard(hInstance,hWnd);	//キーボードの初期化処理
	InitFade();						//フェイドの初期化処理
	
	switch(g_mode)
	{
	case MODE_TITTLE:
		InitTittle();					//タイトルの初期化処理		
		break;

	case MODE_GAME:
		InitGame();						//ゲームの初期化処理	
		break;

	case MODE_RESULT:
		InitResult();					//リザルトの初期化処理		
		break;
	}
	

	//FPSの初期化処理
	D3DXCreateFont(g_pD3DDevice,18,0,0,0,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"Terminal",&g_pD3DFont);

	return S_OK;
}
//-------------------------------------
//	(終了処理)
//-------------------------------------
void Uninit(void)
{
	if(g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice=NULL;
	}
	if(g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	UninitKeyboard();		//キーボードの終了処理
	UninitTittle();			//タイトルの終了処理
	UninitGame();			//ゲームの終了処理
	UninitResult();			//リザルトの終了処理
	UninitFade();			//フェイドの終了処理
	UninitSound();
}

//-------------------------------------
//	更新処理
//-------------------------------------
void Update(void)
{
	static int ResultCnt;	//画面遷移の時間カウントを入れる変数

	UpdateKeyboard();		//キーボードの更新処理
	
	switch(g_mode)
	{
	case MODE_TITTLE:
		UpdateTittle();			//アップデート
		break;

	case MODE_GAME:
		UpdateGame();			//アップデート
		break;

	case MODE_RESULT:
		UpdateResult();			//アップデート

		switch(GetFade())
		{
			case FADE_NONE:
				//=====================
				//画面遷移の時間制限
				//=====================
				//リザルト画面になってからの時間のカウント
				ResultCnt++;

				//一定時間経過したら画面遷移をします
				if(ResultCnt >= RESULT_END_TIME)
				{
					SetFade(FADE_OUT);
				}
				break;

			case FADE_IN:		//フェイドインするときにカウントを0にする
				ResultCnt = 0;
		}
		break;

	case MODE_MAX:
		break;
	}

	UpdateFade();			//フェイドアップデート
}
//-------------------------------------
//描画処理
//-------------------------------------
void Draw(void)
{
	g_pD3DDevice->Clear(0,NULL,(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),D3DCOLOR_RGBA(0,0,0,0),1.0f,0);	//クリアする色

	//描画の開始
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch(g_mode)
		{
		case MODE_TITTLE:
			DrawTittle();		//ゲームの描画処理
			break;

		case MODE_GAME:
			DrawGame();			//ゲームの描画処理
			break;

		case MODE_RESULT:
			DrawResult();		//背景の描画処理
			break;

		case MODE_MAX:
			break;
		}
	
		DrawFade();		//フェイドの描画処理 画面の一番最初に行くから最後に記述する
		
		#ifdef _DEBUG			//FPS描画処理
				DrawFPS();		//デバックビルドのときのみ有効
		#endif

		g_pD3DDevice->EndScene();	//描画の終了
	}
		//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(0,NULL,NULL,NULL);

	//NULLを入れるとかなんとか
}

//-------------------------------------
//ウィンドウプロシージャ
//-------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	int nID;

	switch(uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
				break;

		case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(NULL,
							"終了する？",
							"終了する？",
							MB_YESNO);			
			if(nID == IDYES)
			{
				DestroyWindow(hWnd);
				break;
			}
		}	
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//-------------------------------------
//FPS描画処理
//-------------------------------------
void DrawFPS(void)
{
	RECT rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	char aStr[256];

	wsprintf(&aStr[0],"FPS : %d\n",g_nCountFPS);
	
	//テキストの描画
	g_pD3DFont -> DrawText(NULL,&aStr[0],-1,&rect,DT_LEFT,D3DCOLOR_RGBA(255,255,255,255));
}

//-------------------------------------
//画面遷移 SetMode
//-------------------------------------
void SetMode(MODE mode)
{
	g_mode = mode;

	//画面遷移の切り替え
	switch(g_mode)
	{
		case MODE_TITTLE:
			UninitResult();
			InitTittle();
			break;

		case MODE_GAME:
			UninitTittle();
			InitGame();
			break;

		case MODE_RESULT:
			UninitGame();
			InitResult();
			break;

		case MODE_MAX:
			break;
	}
}
//-------------------------------------
//画面遷移 GetMode
//-------------------------------------
MODE GetMode(void)
{
	return g_mode;
}


