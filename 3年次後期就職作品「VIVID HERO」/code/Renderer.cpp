//��-------------------------------------------------------------------------��
//
//	File:�����_���[cpp�t�@�C��[Renderer.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "Renderer.h"
#include "WndProc.h"
#include "CScene.h"
#include "CDebugProc.h"

#pragma comment(lib,"imm32.lib")

#define CLASS_NAME	"class_name"		//(�E�B���h�E�N���X�̖��O)
#define WINDOW_NAME	"VIVID HERO"				//(�E�B���h�E�̖��O)

//��-------------------------------------------------------------------------��
//�ÓI�ϐ��̏�����
//��-------------------------------------------------------------------------��
CDebugProc *CRenderer::m_pDebugProcPointer = NULL;

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ��̏�����
//��-------------------------------------------------------------------------��
HINSTANCE	g_hInstance		 = NULL;		// �C���X�^���X�E�n���h��
HWND		g_hWindow		 = NULL;		// �E�C���h�E�E�n���h��
HMENU		g_hMenu			 = NULL;		// ���j���[�E�n���h��

RECT		g_rectWindow;					// �E�C���h�E�E���[�h�ł̍Ō�̈ʒu

// �N�����̕`��̈�T�C�Y
bool		g_bWindow = true;				// �N�����̉�ʃ��[�h

SIZE		g_sizeWindowMode = { SCREEN_WIDTH, SCREEN_HEIGHT };// �E�C���h�E�E���[�h
SIZE		g_sizeFullMode	 = { SCREEN_WIDTH, SCREEN_HEIGHT };// �t���X�N���[���E���[�h

// �C���^�[�t�F�C�X
LPDIRECT3D9				g_pD3D   = NULL;			// Direct3D�C���^�[�t�F�C�X
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;		// Direct3DDevice�C���^�[�t�F�C�X
D3DPRESENT_PARAMETERS	g_D3DPP;					// D3DDevice�̐ݒ�(����)

D3DPRESENT_PARAMETERS	g_D3DPPWindow;				// D3DDevice�̐ݒ�(�E�C���h�E�E���[�h�p)
D3DPRESENT_PARAMETERS	g_D3DPPFull;				// D3DDevice�̐ݒ�(�t���X�N���[���E���[�h�p)

//bool					g_bDeviceLost = false;		// �f�o�C�X�̏����t���O

//��----------------------------------��
//�A�v���P�[�V�����������i�ŏ��Ɉ�x�����Ă΂��j
//��----------------------------------��
HRESULT CRenderer::Init(HINSTANCE hInstance)
{
	// ���������[�N�����p�B
	_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// �A�v���P�[�V�����̃C���X�^���X�E�n���h����ۑ�
	g_hInstance = hInstance;
	
	// IME���֎~����
	ImmDisableIME(-1); // ���̃X���b�h�ŋ֎~
	
	// �E�C���h�E�E�N���X�̓o�^
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
	
	//���C���E�E�C���h�E�쐬
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
		// (�E�C���h�E�E���[�h�p)
		rect.top	 = CW_USEDEFAULT;
		rect.left	 = CW_USEDEFAULT;
		rect.right	 = g_rectWindow.right;
		rect.bottom	 = g_rectWindow.bottom;
	}
	else
	{
		// (�t���X�N���[���E���[�h�p)
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
	
	// �E�C���h�E�\��
	ShowWindow(g_hWindow, SW_SHOWNORMAL);
	UpdateWindow(g_hWindow);
	


	g_pD3D = NULL;
	g_pD3DDevice = NULL;

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
		return E_FAIL;

	D3DDISPLAYMODE d3ddm;
	g_pD3D -> GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	// D3DDevice�I�u�W�F�N�g�̍쐬
	if (g_bWindow)
	{
		// D3DDevice�I�u�W�F�N�g�̐ݒ�(�E�C���h�E�E���[�h�p)
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
		// D3DDevice�I�u�W�F�N�g�̐ݒ�(�t���X�N���[���E���[�h)
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

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice -> SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice -> SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice -> SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice -> SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice -> SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice -> SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice -> SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	g_pD3DDevice -> SetSamplerState(D3DTEXF_ANISOTROPIC, D3DSAMP_ADDRESSU, 16);



	// �r���[�|�[�g�̐ݒ�
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

//��-------------------------------------��
// �A�v���P�[�V�����̏I�������i�Ō�ɌĂ΂��j
//��-------------------------------------��
void CRenderer::Uninit(void)
{
	if(m_pDebugProcPointer != NULL)
	{
		m_pDebugProcPointer->Uninit();
		delete m_pDebugProcPointer;
		m_pDebugProcPointer = NULL;
	
	}

	// �E�C���h�E�E�N���X�̓o�^����
	UnregisterClass(WINDOW_NAME, g_hInstance);
	
	CleanupDXGraphics();
}

//��-------------------------------------��
// ��ʂ̍X�V����
//��-------------------------------------��
void CRenderer::Update(void)
{

}

//��-------------------------------------��
// ��ʂ̕`�揈��
//��-------------------------------------��
void CRenderer::Draw(void)
{
	// �V�[���̃N���A
	g_pD3DDevice->Clear(0,NULL,(D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL),D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),1.0f,0);	//�N���A����F

	// �V�[���̕`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		CScene::DrawAll();
		

		m_pDebugProcPointer->Draw();

		// �V�[���̕`��I��
		g_pD3DDevice->EndScene();
	}
	
	// �V�[���̕\��
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//��-------------------------------------��
//DirectX Graphics������
//��-------------------------------------��
HRESULT InitGraphics(void)
{
	return S_OK;
}

//��-------------------------------------��
// DirectX Graphics�̏I������(�������Ɏ��s�����Ƃ����Ă΂��)
//��-------------------------------------��
void CleanupDXGraphics(void)
{
	// �f�o�C�ÃI�u�W�F�N�g�̉��
	if(g_pD3DDevice)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̉��
	if(g_pD3D)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//��-------------------------------------��
//�f�o�C�X�̎擾
//��-------------------------------------��
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return g_pD3DDevice;
}

//��-------------------------------------��
//�E�B���h�E�̃Q�b�g
//��-------------------------------------��
HWND GethWnd()
{
	return g_hWindow;
}

//��-------------------------------------��
//�C���X�^���X�̃Q�b�g
//��-------------------------------------��
HINSTANCE GetHInstance()
{
	return g_hInstance;
}


