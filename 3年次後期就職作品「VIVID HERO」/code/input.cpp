//��-------------------------------------------------------------------------��
//
//	File:�C���v�b�gcpp�t�@�C��[input.cpp]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include"input.h"

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
BYTE CInput::g_aKeyState[] = {NULL};

BYTE CInput::g_aKeyStateTrigger[] = {NULL};		//�L�[�g���K�[���
BYTE CInput::g_aKeyStateRelease[] = {NULL};		//�L�[�����[�X���
BYTE CInput::g_aKeyStateRepeat[] = {NULL};		//�L�[���s�[�g���
int CInput::g_aKeyStateRepeatCount[] = {0};		//���s�[�g�̃J�E���g

//��---------------------------------��
//�R���X�g���N�^
//��---------------------------------��
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

//��---------------------------------��
//�f�X�g���N�^
//��---------------------------------��
CInput::~CInput()
{

}


//��---------------------------------��
//�C���v�b�g�̏���������
//��---------------------------------��
HRESULT CInput::InitKeyboard(HINSTANCE hInstance,HWND hWnd)
{
	HRESULT hr;
	int nID;
	if(g_pDInput == NULL)
	{
		hr = DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&g_pDInput,NULL);
		
		if(FAILED(hr))
		{
			nID = MessageBox(NULL,"�C���v�b�g��������������������","�C���v�b�g���������������������ł�",MB_YESNO);
			return hr;
		}
	}
	hr = g_pDInput -> CreateDevice(GUID_SysKeyboard,&g_pDIDevKeyboard,NULL);
	if(FAILED(hr))
		{
			nID = MessageBox(NULL,"��������������","���������������ł�",MB_YESNO);
			return hr;
		}
	hr = g_pDIDevKeyboard -> SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
		{
			nID = MessageBox(NULL,"��������������","���������������ł�",
							MB_YESNO);
			return hr;
		}
	hr = g_pDIDevKeyboard -> SetCooperativeLevel(hWnd,DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);	//�������[�h��ݒ�
	if(FAILED(hr))
	{
		nID = MessageBox(NULL,
						"��������������","���������������ł�",MB_YESNO);
		return hr;
	}

	g_pDIDevKeyboard -> Acquire();
	return S_OK;
}

//��---------------------------------��
//�C���v�b�g�̏I������
//��---------------------------------��
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
		//�����[�XNULL
		g_pDInput -> Release();
		g_pDInput = NULL;
	}
}

//��---------------------------------��
//�C���v�b�g�̍X�V����
//��---------------------------------��
void CInput::UpdateKeyboard(void)
{
	BYTE aKeyState[256];

	if(SUCCEEDED(g_pDIDevKeyboard -> GetDeviceState(sizeof(aKeyState),&aKeyState[0])))
	{
		for(int nKey = 0;nKey < 256;nKey++)
		{
			//���������牺�̓m�[�g�ɏ����ĂȂ�----------------------
			//�L�[�g���K�[�̏���
			g_aKeyStateTrigger[nKey] = (g_aKeyState[nKey] ^ aKeyState[nKey]) & aKeyState[nKey];

			//�L�[�����[�X�̏���
			g_aKeyStateRelease[nKey] = (g_aKeyState[nKey] ^ aKeyState[nKey]) & g_aKeyState[nKey];

			//�L�[���s�[�g�̏���
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
//��---------------------------------��
//�g���K�[����
//��---------------------------------��
bool CInput::GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey]&0x80)?true:false;
}
//��---------------------------------��
//�����[�X����
//��---------------------------------��
bool CInput::GetKeyboardRelease(int nKey)
{
	return(g_aKeyStateRelease[nKey]&0x80)?true:false;
}
//��---------------------------------��
//�v���X����
//��---------------------------------��
bool CInput::GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey]&0x80)?true:false;
}

//��---------------------------------��
//���s�[�g����
//��---------------------------------��
bool CInput::GetKeyboardRepeat(int nKey)
{
	return(g_aKeyStateRepeat[nKey]&0x80)?true:false;
}

