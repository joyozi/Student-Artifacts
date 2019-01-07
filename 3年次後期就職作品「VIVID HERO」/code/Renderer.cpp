//◇-------------------------------------------------------------------------◇
//
//	File:レンダラーcppファイル[Renderer.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "Renderer.h"
#include "WndProc.h"
#include "CScene.h"
#include "CDebugProc.h"

#pragma comment(lib,"imm32.lib")

#define CLASS_NAME	"class_name"		//(ウィンドウクラスの名前)
#define WINDOW_NAME	"VIVID HERO"				//(ウィンドウの名前)

//◇-------------------------------------------------------------------------◇
//静的変数の初期化
//◇-------------------------------------------------------------------------◇
CDebugProc *CRenderer::m_pDebugProcPointer = NULL;

//◇-------------------------------------------------------------------------◇
//グローバル変数の初期化
//◇-------------------------------------------------------------------------◇
HINSTANCE	g_hInstance		 = NULL;		// インスタンス・ハンドル
HWND		g_hWindow		 = NULL;		// ウインドウ・ハンドル
HMENU		g_hMenu			 = NULL;		// メニュー・ハンドル

RECT		g_rectWindow;					// ウインドウ・モードでの最後の位置

// 起動時の描画領域サイズ
bool		g_bWindow = true;				// 起動時の画面モード

SIZE		g_sizeWindowMode = { SCREEN_WIDTH, SCREEN_HEIGHT };// ウインドウ・モード
SIZE		g_sizeFullMode	 = { SCREEN_WIDTH, SCREEN_HEIGHT };// フルスクリーン・モード

// インターフェイス
LPDIRECT3D9				g_pD3D   = NULL;			// Direct3Dインターフェイス
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;		// Direct3DDeviceインターフェイス
D3DPRESENT_PARAMETERS	g_D3DPP;					// D3DDeviceの設定(現在)

D3DPRESENT_PARAMETERS	g_D3DPPWindow;				// D3DDeviceの設定(ウインドウ・モード用)
D3DPRESENT_PARAMETERS	g_D3DPPFull;				// D3DDeviceの設定(フルスクリーン・モード用)

//bool					g_bDeviceLost = false;		// デバイスの消失フラグ

//◇----------------------------------◇
//アプリケーション初期化（最初に一度だけ呼ばれる）
//◇----------------------------------◇
HRESULT CRenderer::Init(HINSTANCE hInstance)
{
	// メモリリーク調査用。
	_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// アプリケーションのインスタンス・ハンドルを保存
	g_hInstance = hInstance;
	
	// IMEを禁止する
	ImmDisableIME(-1); // このスレッドで禁止
	
	// ウインドウ・クラスの登録
	WNDCLASSEX wcex;
	wcex.cbSize			 = sizeof(WNDCLASSEX);
	wcex.style			 = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	 = WndProc;
	wcex.cbClsExtra		 = 0;
	wcex.cbWndExtra		 = 0;
	wcex.hInstance		 = g_hInstance;
	wcex.hIcon			 = LoadIcon(NULL, "");;
	wcex.hIconSm		 = LoadIcon(NULL, "");;
	wcex.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	 = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	 = NULL;
	wcex.lpszClassName	 = CLASS_NAME;
	
	if (!RegisterClassEx(&wcex))
		return E_FAIL;
	
	//メイン・ウインドウ作成
	g_rectWindow.top		 = 0;
	g_rectWindow.left		 = 0;
	g_rectWindow.right		 = g_sizeWindowMode.cx;
	g_rectWindow.bottom		 = g_sizeWindowMode.cy;
	AdjustWindowRect(&g_rectWindow, WS_OVERLAPPEDWINDOW, FALSE);
	g_rectWindow.right		 = g_rectWindow.right - g_rectWindow.left;
	g_rectWindow.bottom		 = g_rectWindow.bottom - g_rectWindow.top;
	g_rectWindow.top		 = 0;
	g_rectWindow.left		 = 0;
	
	RECT rect;

	if (g_bWindow)
	{
		// (ウインドウ・モード用)
		rect.top	 = CW_USEDEFAULT;
		rect.left	 = CW_USEDEFAULT;
		rect.right	 = g_rectWindow.right;
		rect.bottom	 = g_rectWindow.bottom;
	}
	else
	{
		// (フルスクリーン・モード用)
		rect.top		 = 0;
		rect.left		 = 0;
		rect.right		 = g_sizeFullMode.cx;
		rect.bottom		 = g_sizeFullMode.cy;
	}
	
	g_hWindow = CreateWindow(CLASS_NAME, WINDOW_NAME,
							g_bWindow ? WS_OVERLAPPEDWINDOW : WS_POPUP,
							rect.left,
							rect.top,
							rect.right,
							rect.bottom,
							NULL, NULL, g_hInstance, NULL);

	if (g_hWindow == NULL)
		return E_FAIL;
	
	// ウインドウ表示
	ShowWindow(g_hWindow, SW_SHOWNORMAL);
	UpdateWindow(g_hWindow);
	


	g_pD3D = NULL;
	g_pD3DDevice = NULL;

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
		return E_FAIL;

	D3DDISPLAYMODE d3ddm;
	g_pD3D -> GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	// D3DDeviceオブジェクトの作成
	if (g_bWindow)
	{
		// D3DDeviceオブジェクトの設定(ウインドウ・モード用)
		ZeroMemory(&g_D3DPPWindow, sizeof(g_D3DPPWindow));
	
		g_D3DPPWindow.BackBufferWidth				 = g_sizeWindowMode.cx;
		g_D3DPPWindow.BackBufferHeight				 = g_sizeWindowMode.cy;
		g_D3DPPWindow.BackBufferFormat				 = D3DFMT_UNKNOWN;
		g_D3DPPWindow.BackBufferCount				 = 1;
		g_D3DPPWindow.MultiSampleType				 = D3DMULTISAMPLE_NONE;
		g_D3DPPWindow.MultiSampleQuality			 = 0;
		g_D3DPPWindow.SwapEffect					 = D3DSWAPEFFECT_DISCARD;
		g_D3DPPWindow.hDeviceWindow					 = g_hWindow;
		g_D3DPPWindow.Windowed						 = TRUE;
		g_D3DPPWindow.EnableAutoDepthStencil		 = TRUE;
		g_D3DPPWindow.AutoDepthStencilFormat		 = D3DFMT_D24S8;
		g_D3DPPWindow.Flags							 = 0;
		g_D3DPPWindow.FullScreen_RefreshRateInHz	 = 0;
		g_D3DPPWindow.PresentationInterval			 = D3DPRESENT_INTERVAL_IMMEDIATE;
	
		g_D3DPP = g_D3DPPWindow;
	}
	else
	{
		// D3DDeviceオブジェクトの設定(フルスクリーン・モード)
		ZeroMemory(&g_D3DPPFull, sizeof(g_D3DPPFull));
	
		g_D3DPPFull.BackBufferWidth				 = g_sizeFullMode.cx;
		g_D3DPPFull.BackBufferHeight			 = g_sizeFullMode.cy;
		g_D3DPPFull.BackBufferFormat			 = d3ddm.Format;
		g_D3DPPFull.BackBufferCount				 = 1;
		g_D3DPPFull.MultiSampleType				 = D3DMULTISAMPLE_NONE;
		g_D3DPPFull.MultiSampleQuality			 = 0;
		g_D3DPPFull.SwapEffect					 = D3DSWAPEFFECT_DISCARD;
		g_D3DPPFull.hDeviceWindow				 = g_hWindow;
		g_D3DPPFull.Windowed					 = FALSE;
		g_D3DPPFull.EnableAutoDepthStencil		 = TRUE;
		g_D3DPPFull.AutoDepthStencilFormat		 = D3DFMT_D24S8;
		g_D3DPPFull.Flags						 = 0;
		g_D3DPPFull.FullScreen_RefreshRateInHz	 = D3DPRESENT_RATE_DEFAULT;
		g_D3DPPFull.PresentationInterval		 = D3DPRESENT_INTERVAL_IMMEDIATE;
	
		g_D3DPP = g_D3DPPFull;
	}



	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL,
									g_hWindow,
									D3DCREATE_HARDWARE_VERTEXPROCESSING,
									&g_D3DPP,
									&g_pD3DDevice);
	if (FAILED(hr))
	{
		hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
								D3DDEVTYPE_HAL,
								g_hWindow,
								D3DCREATE_SOFTWARE_VERTEXPROCESSING,
								&g_D3DPP,
								&g_pD3DDevice);
		if (FAILED(hr))
		{	
			hr = g_pD3D -> CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_REF,
										g_hWindow,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&g_D3DPP,
										&g_pD3DDevice);
			if (FAILED(hr))
			{	
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice -> SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice -> SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice -> SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice -> SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// テクスチャステージステートの設定
	g_pD3DDevice -> SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice -> SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice -> SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	g_pD3DDevice -> SetSamplerState(D3DTEXF_ANISOTROPIC, D3DSAMP_ADDRESSU, 16);



	// ビューポートの設定
	D3DVIEWPORT9 vp;
	vp.X  = 0;
	vp.Y  = 0;
	vp.Width = g_D3DPP.BackBufferWidth;
	vp.Height = g_D3DPP.BackBufferHeight;
	vp.MinZ  = 0.0f;
	vp.MaxZ  = 1.0f;
	HRESULT hr2 = g_pD3DDevice->SetViewport(&vp);
	
	if (FAILED(hr2))
		return E_FAIL;




	m_pDebugProcPointer = new CDebugProc;
	m_pDebugProcPointer->Init();

	return S_OK;
}

//◇-------------------------------------◇
// アプリケーションの終了処理（最後に呼ばれる）
//◇-------------------------------------◇
void CRenderer::Uninit(void)
{
	if(m_pDebugProcPointer != NULL)
	{
		m_pDebugProcPointer->Uninit();
		delete m_pDebugProcPointer;
		m_pDebugProcPointer = NULL;
	
	}

	// ウインドウ・クラスの登録解除
	UnregisterClass(WINDOW_NAME, g_hInstance);
	
	CleanupDXGraphics();
}

//◇-------------------------------------◇
// 画面の更新処理
//◇-------------------------------------◇
void CRenderer::Update(void)
{

}

//◇-------------------------------------◇
// 画面の描画処理
//◇-------------------------------------◇
void CRenderer::Draw(void)
{
	// シーンのクリア
	g_pD3DDevice->Clear(0,NULL,(D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL),D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),1.0f,0);	//クリアする色

	// シーンの描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		CScene::DrawAll();
		

		m_pDebugProcPointer->Draw();

		// シーンの描画終了
		g_pD3DDevice->EndScene();
	}
	
	// シーンの表示
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//◇-------------------------------------◇
//DirectX Graphics初期化
//◇-------------------------------------◇
HRESULT InitGraphics(void)
{
	return S_OK;
}

//◇-------------------------------------◇
// DirectX Graphicsの終了処理(初期化に失敗したときも呼ばれる)
//◇-------------------------------------◇
void CleanupDXGraphics(void)
{
	// デバイづオブジェクトの解放
	if(g_pD3DDevice)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの解放
	if(g_pD3D)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//◇-------------------------------------◇
//デバイスの取得
//◇-------------------------------------◇
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return g_pD3DDevice;
}

//◇-------------------------------------◇
//ウィンドウのゲット
//◇-------------------------------------◇
HWND GethWnd()
{
	return g_hWindow;
}

//◇-------------------------------------◇
//インスタンスのゲット
//◇-------------------------------------◇
HINSTANCE GetHInstance()
{
	return g_hInstance;
}


