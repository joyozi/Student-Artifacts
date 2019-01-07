//��-------------------------------------------------------------------------��
//
//	�C���v�b�gcpp�t�@�C��[input.cpp]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include"main.h"
#include"input.h"
//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECTINPUT8 g_pDInput = NULL;				//DirectInput�C���^�t�F�[�X�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDIDevKeyboard = NULL;	//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
BYTE g_aKeyState[256];			//�L�[�{�[�h���

//���m�[�g�ɏ����ĂȂ�
BYTE g_aKeyStateTrigger[256];	//�L�[�g���K�[���
BYTE g_aKeyStateRelease[256];	//�L�[�����[�X���
BYTE g_aKeyStateRepeat[256];	//�L�[���s�[�g���
int g_aKeyStateRepeatCount[256];//
//��-------------------------------------------------------------------------��
//�C���v�b�g�̏���������
//��-------------------------------------------------------------------------��
HRESULT InitKeyboard(HINSTANCE hInstance,HWND hWnd)
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

//-------------------------------------
//�C���v�b�g�̏I������
//-------------------------------------
void UninitKeyboard(void)
{
	if(g_pDIDevKeyboard != NULL)
	{
		g_pDIDevKeyboard -> Unacquire();
	}
	if(g_pDInput != NULL)
	{
		//�����[�XNULL
	}
}

//-------------------------------------
//�C���v�b�g�̍X�V����
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
//���m�[�g�ɏ����ĂȂ�-------------------------------------------
	//�g���K�[����
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey]&0x80)?true:false;
}

	//�����[�X����
bool GetKeyboardRelease(int nKey)
{
	return(g_aKeyStateRelease[nKey]&0x80)?true:false;
}
//��------------------------------------------------------------
	//�v���X����
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey]&0x80)?true:false;
}

	//���s�[�g����
bool GetKeyboardRepeat(int nKey)
{
	return(g_aKeyStateRepeat[nKey]&0x80)?true:false;
}