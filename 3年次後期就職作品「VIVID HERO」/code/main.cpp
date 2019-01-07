//��-------------------------------------------------------------------------��
//
//	File:�^���ÃE�B���h�E[main.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//===================
//���������[�N�̃t�@�C��
//===================
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "CManager.h"
#include "resource.h"
#include "WndProc.h"
#include "CDebugProc.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��
HRESULT Init(HINSTANCE hInstance);

void Uninit(void);
void Update(void);
void Draw(void);

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
int g_nCountFPS = 0;	//FPS�J�E���^

CManager *g_pCManager;

//��-------------------------------------------------------------------------��
//���C���֐�
//��-------------------------------------------------------------------------��
int	WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	//���������[�N�̌���
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

	//���b�Z�[�W���[�v
	while(1)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)!=0)
		{	//window�v���O����
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

	Uninit();	//�I������

	timeEndPeriod(1);
	
	return(int)msg.wParam;
}

//��-------------------------------------��
//	(����������)
//��-------------------------------------��
HRESULT Init(HINSTANCE hInstance)
{	
	CManager *pManager;
	pManager = new CManager;
	pManager -> Init(hInstance);

	g_pCManager = pManager;

	return S_OK;
}
//��-------------------------------------��
//�I������
//��-------------------------------------��
void Uninit(void)
{	
	g_pCManager->Uninit();
	delete g_pCManager;
	g_pCManager = NULL;
}

//��-------------------------------------��
//�X�V����
//��-------------------------------------��
void Update(void)
{
	CDebugProc::Print("FPS : %d\n",g_nCountFPS);
	
	g_pCManager->Update();// = pCamera;
}

//��-------------------------------------��
//�`�揈��
//��-------------------------------------��
void Draw(void)
{
	g_pCManager->Draw();// = pCamera;
}

//��-------------------------------------��
//�f�o�C�X�̎擾����
//��-------------------------------------��
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pCManager->GetDevice();
}
