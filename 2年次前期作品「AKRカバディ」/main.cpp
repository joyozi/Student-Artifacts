//��-------------------------------------------------------------------------��
//
//	�^���ÃE�B���h�E[main.cpp]
//	AT12A271�@�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
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

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��
HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);
LRESULT CALLBACK WndProc(HWND nWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);
//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
LPD3DXFONT g_pD3DFont = NULL;
int g_nCountFPS = 0;	//FPS�J�E���^

MODE g_mode = MODE_TITTLE;
//��-------------------------------------------------------------------------��
//���C���֐�
//��-------------------------------------------------------------------------��
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

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�E�B���h�E�̐���
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

//����������
	if(FAILED(Init(hInstance,hWnd,TRUE)))
	{
		return -1;
	}

//�E�B���h�E�̕\��
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while(1)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)!=0)
		{		
			//window�v���O����
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//FPS����������
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	//0.5�b�o��
			{
				g_nCountFPS = (dwFrameCount * 1000)/(dwCurrentTime - dwFPSLastTime);	//FPS���v��
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if((dwCurrentTime - dwExecLastTime) >= (1000/60))
			{
				dwExecLastTime = dwCurrentTime;
				//DirectX�v���O����
				//�X�V����
				Update();
				//�`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}
	//�E�B���h�E�N���X�̓o�^����
	UnregisterClass(CLASS_NAME,wcex.hInstance);

	Uninit();	//�I������
	
	timeEndPeriod(1);
	
	return(int)msg.wParam;
}

//-------------------------------------
//	(����������)
//-------------------------------------
HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))
	{
		return E_FAIL;
	}

	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.BackBufferWidth	= SCREEN_WIDTH;		//�Q�[����ʂ̕�
	d3dpp.BackBufferHeight	= SCREEN_HEIGHT;	//�Q�[����ʂ̍���
	d3dpp.BackBufferFormat	= d3ddm.Format;		//�J���[���[�h
	d3dpp.BackBufferCount	= 1;				//�o�b�N�o�b�t�@�̐�

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = bWindow;					//�E�B���h�E/�t���X�N���[�����[�h
	d3dpp.EnableAutoDepthStencil = TRUE;		//�f�v�X�o�b�t�@�A�X�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//16bit�̃f�v�X�o�b�t�@�����悤

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

	//�f�o�C�X�I�u�W�F�N�g�̐���
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

	//�����_�[�e�X�g�̐ݒ�	�ǉ�������|���S��������
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	
//	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);


	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice -> SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
	g_pD3DDevice -> SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);
	g_pD3DDevice -> SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);		//�e�N�X�`���̊g�����̕�Ԑݒ�
	g_pD3DDevice -> SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);

	InitSound(hWnd);				//���y�̏�����
	InitKeyboard(hInstance,hWnd);	//�L�[�{�[�h�̏���������
	InitFade();						//�t�F�C�h�̏���������
	
	switch(g_mode)
	{
	case MODE_TITTLE:
		InitTittle();					//�^�C�g���̏���������		
		break;

	case MODE_GAME:
		InitGame();						//�Q�[���̏���������	
		break;

	case MODE_RESULT:
		InitResult();					//���U���g�̏���������		
		break;
	}
	

	//FPS�̏���������
	D3DXCreateFont(g_pD3DDevice,18,0,0,0,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"Terminal",&g_pD3DFont);

	return S_OK;
}
//-------------------------------------
//	(�I������)
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

	UninitKeyboard();		//�L�[�{�[�h�̏I������
	UninitTittle();			//�^�C�g���̏I������
	UninitGame();			//�Q�[���̏I������
	UninitResult();			//���U���g�̏I������
	UninitFade();			//�t�F�C�h�̏I������
	UninitSound();
}

//-------------------------------------
//	�X�V����
//-------------------------------------
void Update(void)
{
	static int ResultCnt;	//��ʑJ�ڂ̎��ԃJ�E���g������ϐ�

	UpdateKeyboard();		//�L�[�{�[�h�̍X�V����
	
	switch(g_mode)
	{
	case MODE_TITTLE:
		UpdateTittle();			//�A�b�v�f�[�g
		break;

	case MODE_GAME:
		UpdateGame();			//�A�b�v�f�[�g
		break;

	case MODE_RESULT:
		UpdateResult();			//�A�b�v�f�[�g

		switch(GetFade())
		{
			case FADE_NONE:
				//=====================
				//��ʑJ�ڂ̎��Ԑ���
				//=====================
				//���U���g��ʂɂȂ��Ă���̎��Ԃ̃J�E���g
				ResultCnt++;

				//��莞�Ԍo�߂������ʑJ�ڂ����܂�
				if(ResultCnt >= RESULT_END_TIME)
				{
					SetFade(FADE_OUT);
				}
				break;

			case FADE_IN:		//�t�F�C�h�C������Ƃ��ɃJ�E���g��0�ɂ���
				ResultCnt = 0;
		}
		break;

	case MODE_MAX:
		break;
	}

	UpdateFade();			//�t�F�C�h�A�b�v�f�[�g
}
//-------------------------------------
//�`�揈��
//-------------------------------------
void Draw(void)
{
	g_pD3DDevice->Clear(0,NULL,(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),D3DCOLOR_RGBA(0,0,0,0),1.0f,0);	//�N���A����F

	//�`��̊J�n
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch(g_mode)
		{
		case MODE_TITTLE:
			DrawTittle();		//�Q�[���̕`�揈��
			break;

		case MODE_GAME:
			DrawGame();			//�Q�[���̕`�揈��
			break;

		case MODE_RESULT:
			DrawResult();		//�w�i�̕`�揈��
			break;

		case MODE_MAX:
			break;
		}
	
		DrawFade();		//�t�F�C�h�̕`�揈�� ��ʂ̈�ԍŏ��ɍs������Ō�ɋL�q����
		
		#ifdef _DEBUG			//FPS�`�揈��
				DrawFPS();		//�f�o�b�N�r���h�̂Ƃ��̂ݗL��
		#endif

		g_pD3DDevice->EndScene();	//�`��̏I��
	}
		//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(0,NULL,NULL,NULL);

	//NULL������Ƃ��Ȃ�Ƃ�
}

//-------------------------------------
//�E�B���h�E�v���V�[�W��
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
							"�I������H",
							"�I������H",
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
//FPS�`�揈��
//-------------------------------------
void DrawFPS(void)
{
	RECT rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	char aStr[256];

	wsprintf(&aStr[0],"FPS : %d\n",g_nCountFPS);
	
	//�e�L�X�g�̕`��
	g_pD3DFont -> DrawText(NULL,&aStr[0],-1,&rect,DT_LEFT,D3DCOLOR_RGBA(255,255,255,255));
}

//-------------------------------------
//��ʑJ�� SetMode
//-------------------------------------
void SetMode(MODE mode)
{
	g_mode = mode;

	//��ʑJ�ڂ̐؂�ւ�
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
//��ʑJ�� GetMode
//-------------------------------------
MODE GetMode(void)
{
	return g_mode;
}


