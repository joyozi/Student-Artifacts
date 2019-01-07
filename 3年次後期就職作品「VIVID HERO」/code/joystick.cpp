//��-------------------------------------------------------------------------��
//
//	File	:	�W���C�X�e�B�b�N���͏����v���O����[joystick.cpp]
//	Auther	:	Ikezawa Shintaro
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
///	�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include"joystick.h"
#include"main.h"

//��-------------------------------------------------------------------------��
//	�}�N����`
//��-------------------------------------------------------------------------��
#define REPEAT_INTERVAL		(200)	// ���s�[�g�Ԋu����[ms]
#define REPEAT_START_TIME	(400)	// ���s�[�g�J�n�܂ł̑҂�����[ms]

//��-------------------------------------------------------------------------��
//	�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);

//��-------------------------------------------------------------------------��
//	�O���[�o���ϐ��錾
//��-------------------------------------------------------------------------��
LPDIRECTINPUT8 g_pDInputJoystick = NULL;	// �C���v�b�g�I�u�W�F�N�g
LPDIRECTINPUTDEVICE8 g_pDIDevJoystick = NULL;	// �C���v�b�g�f�o�C�X(�L�[�{�[�h)
DIDEVCAPS             g_diDevCaps;          // �W���C�X�e�B�b�N�̔\��

BYTE g_aJoystickButton[128];		// �v���X���
BYTE g_aJoystickButtonTrigger[128];	// �g���K�[���
BYTE g_aJoystickButtonRelease[128];	// �����[�X���	
BYTE g_aJoystickButtonRepeatTrigger[128];	// ���s�[�g�g���K�[���
BYTE g_aJoystickButtonRepeatPress[128];	// ���s�[�g�v���X���
unsigned int g_aJoystickButtonRepeatCount[128];	// ���s�[�g����p

BYTE g_aJoystickCross[JCK_MAX];
BYTE g_aJoystickCrossTrigger[JCK_MAX];	// �g���K�[���
BYTE g_aJoystickCrossRelease[JCK_MAX];	// �����[�X���	
BYTE g_aJoystickCrossRepeatTrigger[JCK_MAX];	// ���s�[�g�g���K�[���
BYTE g_aJoystickCrossRepeatPress[JCK_MAX];	// ���s�[�g�v���X���
unsigned int g_aJoystickCrossRepeatCount[JCK_MAX];	// ���s�[�g����p

DIJOYSTATE2 g_JoyState;

BYTE g_aJoystickCrossKeyPov[JCKP_MAX];

//��----------------------------------��
//	�L�[�{�[�h���͂̏������֐�
//��----------------------------------��
HRESULT InitJoystick(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;	// �G���[�m�F�p

	if(g_pDInputJoystick == NULL)	// �܂��A����Ă��Ȃ��Ȃ���
	{
		// DirectInput�I�u�W�F�N�g����
		hr = DirectInput8Create( hInstance,
								DIRECTINPUT_VERSION,
								IID_IDirectInput8,
								(void**)&g_pDInputJoystick,
								NULL);
		// �G���[�`�F�b�N
		if(FAILED(hr))
		{
			MessageBox(hWnd,"DirectInput8�̐����Ɏ��s���܂����B","�G���[�ʒm", MB_OK);
			return hr;
		}

	}

	// �f�o�C�X��񋓂��č쐬(InputDevice�̍쐬)
	hr = g_pDInputJoystick->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback,
										NULL, DIEDFL_ATTACHEDONLY);
	
	// �G���[�`�F�b�N
	if(FAILED(hr))
	{
		MessageBox(hWnd,"�W���C�X�e�B�b�N�̐����Ɏ��s���܂����B","�G���[�ʒm", MB_OK);
		return hr;
	}

	if(g_pDIDevJoystick == NULL)
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�w��
	hr = g_pDIDevJoystick->SetDataFormat(&c_dfDIJoystick2);

	// �G���[�`�F�b�N
	if(FAILED(hr))
	{
		MessageBox(hWnd,"�f�[�^�t�H�[�}�b�g�w��(�W���C�X�e�B�b�N)�Ɏ��s���܂����B","�G���[�ʒm", MB_OK);
		return hr;
	}

	// �Z�b�g�R�[�I�y���C�e�B�u���x���w��( �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j)
	hr = g_pDIDevJoystick->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	// �G���[�`�F�b�N
	if(FAILED(hr))
	{
		MessageBox(hWnd,"�Z�b�g�R�[�I�y���C�e�B�u���x���w��(�W���C�X�e�B�b�N)�Ɏ��s���܂����B","�G���[�ʒm", MB_OK);
		return hr;
	}

	 // �R�[���o�b�N�֐����g���Ċe���̃��[�h��ݒ�
	hr = g_pDIDevJoystick->EnumObjects(EnumAxesCallback, NULL, DIDFT_AXIS);
	if (FAILED(hr))
	{
		MessageBox(NULL,"�����[�h�̐ݒ�Ɏ��s","Direct Input Error",MB_OK);
		return hr;
	}

	g_pDIDevJoystick->Acquire();	// �W���C�X�e�B�b�N�ւ̃A�N�Z�X���̊l��(���͐���J�n)

	return S_OK;
}

//��----------------------------------��
//	�L�[�{�[�h���͂̏I���֐�
//��----------------------------------��
void UninitJoystick(void)
{
	if(g_pDIDevJoystick != NULL)
	{
		g_pDIDevJoystick->Unacquire();	// �L�[�{�[�h�ւ̃A�N�Z�X����j��(���͐���I��)
	}


	// ���̓f�o�C�X(�L�[�{�[�h�̔j��)
	if(g_pDIDevJoystick != NULL)
	{
		g_pDIDevJoystick->Release();	// �������

		g_pDIDevJoystick = NULL;		// NULL�ŏ�����
	}

	// InputDevice�̔j��
	if(g_pDInputJoystick != NULL)
	{
		g_pDInputJoystick->Release();	// �������

		g_pDInputJoystick = NULL;		// NULL�ŏ�����
	}

}

//��----------------------------------��
//	�W���C�X�e�B�b�N��񋓂��� CALLBACK �֐�
// �g�p����f�o�C�X��������� g_pDIDev �ɐݒ肵�āADIENUM_STOP �����^�[��
//��----------------------------------��
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	HRESULT hr;

	// �񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�[�t�F�C�X���擾����B
	hr = g_pDInputJoystick->CreateDevice(pdidInstance->guidInstance, &g_pDIDevJoystick, NULL);
	if (FAILED(hr))     return DIENUM_CONTINUE;
	// �W���C�X�e�B�b�N�̔\�͂𒲂ׂ�
	g_diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hr = g_pDIDevJoystick->GetCapabilities(&g_diDevCaps);
	if (FAILED(hr))
	{// �W���C�X�e�B�b�N�\�͂̎擾�Ɏ��s
		SAFE_RELEASE(g_pDIDevJoystick);
		return DIENUM_CONTINUE;
	}

	return DIENUM_STOP;
}

//��----------------------------------��
//	�W���C�X�e�B�b�N�̎���񋓂��� CALLBACK �֐�
//��----------------------------------��
// �ŏ��l�� -1000 �ɁA�ő�l�� +1000 �ɐݒ�
BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	HRESULT hr;

	// ���̒l�͈̔͂�ݒ�i-1000�`1000�j
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize       = sizeof(diprg); 
	diprg.diph.dwHeaderSize = sizeof(diprg.diph); 
	diprg.diph.dwObj        = lpddoi->dwType;
	diprg.diph.dwHow        = DIPH_BYID;
	diprg.lMin  = -1000;
	diprg.lMax  = +1000;
	hr = g_pDIDevJoystick->SetProperty(DIPROP_RANGE, &diprg.diph);
	if (FAILED(hr))     return DIENUM_STOP;
	return DIENUM_CONTINUE;
}




//��----------------------------------��
//�L�[�{�[�h���͂̍X�V�֐�
//��----------------------------------��
void UpdateJoystick(void)
{
	//BYTE aKeyState[256];
	 DIJOYSTATE2 dijs;

	// �W���C�X�e�B�b�N����f�[�^���擾
	if(SUCCEEDED(g_pDIDevJoystick->GetDeviceState(sizeof(DIJOYSTATE2), &dijs)))
	{
		// ���ݏ�Ԃ𔻕�
		for(int nKey = 0; nKey < 128; nKey++)
		{

			g_aJoystickButtonTrigger[nKey] = ~g_aJoystickButton[nKey] & dijs.rgbButtons[nKey];	// �g���K�[

			g_aJoystickButtonRelease[nKey] = g_aJoystickButton[nKey] & ~dijs.rgbButtons[nKey];	// �����[�X

			g_aJoystickButton[nKey] = dijs.rgbButtons[nKey];	// �v���X(�A������)


			//---- ���s�[�g���� ----
			if(GetJoystickTrigger(nKey))	// �{�^�����������Ƃ�(���s�[�g�J�n��)
			{
				g_aJoystickButtonRepeatCount[nKey] = 0;		// �J�E���g������
				// ON(�������u�Ԃ́A�P���t)
				g_aJoystickButtonRepeatTrigger[nKey] = 0x80;	// ���s�[�g�g���K�[	
				g_aJoystickButtonRepeatPress[nKey] = 0x80;	// ���s�[�g�v���X
			}
			else if(GetJoystickPress(nKey))	// ���������Ă���Ƃ�(���s�[�g��)
			{
				
				g_aJoystickButtonRepeatCount[nKey] += 1;	// �J�E���g�A�b�v

				if(g_aJoystickButtonRepeatCount[nKey] > 30000) g_aJoystickButtonRepeatCount[nKey] = 0;	// �I�[�o�[�t���[�΍�

				if(g_aJoystickButtonRepeatCount[nKey] > (float)FPS_DIRECTX * ((float)REPEAT_START_TIME / 1000.0f))		// ���s�[�^���J�n���鎞�Ԃ�ݒ�
				{
					// ���s�[�g�g���K�[�́AON/OFF���J��Ԃ�
					if((g_aJoystickButtonRepeatCount[nKey] % (int)(FPS_DIRECTX * REPEAT_INTERVAL / 1000)) == 0)	// �J��Ԃ��Ԋu
					{
						g_aJoystickButtonRepeatTrigger[nKey] = 0x80;	// �t���OON
					}
					else
					{
						g_aJoystickButtonRepeatTrigger[nKey] = 0x00;	// �t���OOFF
					}

					g_aJoystickButtonRepeatPress[nKey] = 0x80;	// ��Ƀt���OON(���s�[�g�v���X)
				}
				else
				{
					// OFF�i�ŏ��̂P���t��A��UOFF�ɂ��邽�߁j
					g_aJoystickButtonRepeatTrigger[nKey]	= 0x00;	// ���s�[�g�g���K�[	
					g_aJoystickButtonRepeatPress[nKey]	= 0x00;	// ���s�[�g�v���X
				}
			}
			else if(GetJoystickRelease(nKey))	// �{�^���𗣂����Ƃ�(���s�[�g�I����)
			{
				g_aJoystickButtonRepeatCount[nKey] = 0;		// �J�E���g������
				// OFF�i�{�^�����͏I�����j
				g_aJoystickButtonRepeatTrigger[nKey] = 0x00;	// ���s�[�g�g���K�[	
				g_aJoystickButtonRepeatPress[nKey]	= 0x00;	// ���s�[�g�v���X
			}
			//---- ���s�[�g���������܂� ----
		}
		//---- �{�^����Ԃ𔻕�(for��)�����܂� ----

		//�Ƃ肠���������𒲐�
		if(dijs.lX >= -100 &&  dijs.lX <= 100)		dijs.lX = 0;
		if(dijs.lY >= -100 &&  dijs.lY <= 100)		dijs.lY = 0;
		if(dijs.lZ >= -100 &&  dijs.lZ <= 100)		dijs.lZ = 0;
		if(dijs.lRx >= -100 && dijs.lRx <= 100)		dijs.lRx = 0;
		if(dijs.lRy >= -100 && dijs.lRy <= 100)		dijs.lRy = 0;
		if(dijs.lRz >= -100 && dijs.lRz <= 100)		dijs.lRz = 0;
		if(dijs.lARx >= -100 && dijs.lARx <= 100)	dijs.lARx = 0;
		if(dijs.lARy >= -100 && dijs.lARy <= 100)	dijs.lARy = 0;
		if(dijs.lARz >= -100 && dijs.lARz <= 100)	dijs.lARz = 0;

		g_JoyState = dijs;



		//========= ANALOG������ ==========================

		BYTE g_aTempJoystickCross[JCK_MAX];
		// ��U���Z�b�g
		for(int nKey = 0; nKey < JCK_MAX; nKey++)
		{
			g_aTempJoystickCross[nKey] = 0x00;
		}


		// �擾

		if(dijs.lX == +1000 && dijs.lY == -1000)
		{
			g_aTempJoystickCross[JCK_RIGHT_UP] = 0x80;
		}
		else if(dijs.lX == +1000 && dijs.lY == +1000)
		{
			g_aTempJoystickCross[JCK_RIGHT_DOWN] = 0x80;
		}
		else if(dijs.lX == -1000 && dijs.lY == +1000)
		{
			g_aTempJoystickCross[JCK_LEFT_DOWN] = 0x80;
		}
		else if(dijs.lX == -1000 && dijs.lY == -1000)
		{
			g_aTempJoystickCross[JCK_LEFT_UP] = 0x80;
		}
		else if(dijs.lY == -1000 )
		{
			g_aTempJoystickCross[JCK_UP] = 0x80;
		}
		else if(dijs.lY == +1000)
		{
			g_aTempJoystickCross[JCK_DOWN] = 0x80;
		}
		else if(dijs.lX == +1000)
		{
			g_aTempJoystickCross[JCK_RIGHT] = 0x80;
		}
		else if(dijs.lX == -1000)
		{
			g_aTempJoystickCross[JCK_LEFT] = 0x80;
		}



		if(dijs.lRz == +1000 && dijs.lZ == -1000)
		{
			g_aTempJoystickCross[JCK_RRIGHT_UP] = 0x80;
		}
		else if(dijs.lRz == +1000 && dijs.lZ == +1000)
		{
			g_aTempJoystickCross[JCK_RRIGHT_DOWN] = 0x80;
		}
		else if(dijs.lRz == -1000 && dijs.lZ == +1000)
		{
			g_aTempJoystickCross[JCK_RLEFT_DOWN] = 0x80;
		}
		else if(dijs.lRz == -1000 && dijs.lZ == -1000)
		{
			g_aTempJoystickCross[JCK_RLEFT_UP] = 0x80;
		}
		else if(dijs.lZ == -1000 )
		{
			g_aTempJoystickCross[JCK_RUP] = 0x80;
		}
		else if(dijs.lZ == +1000)
		{
			g_aTempJoystickCross[JCK_RDOWN] = 0x80;
		}
		else if(dijs.lRx == +1000)
		{
			g_aTempJoystickCross[JCK_RRIGHT] = 0x80;
		}
		else if(dijs.lRx == -1000)
		{
			g_aTempJoystickCross[JCK_RLEFT] = 0x80;
		}


		// ����
		for(int nKey = 0; nKey < JCK_MAX; nKey++)
		{

			
			g_aJoystickCrossTrigger[nKey] = ~g_aJoystickCross[nKey] & g_aTempJoystickCross[nKey];	// �g���K�[

			g_aJoystickCrossRelease[nKey] = g_aJoystickCross[nKey] & ~g_aTempJoystickCross[nKey];	// �����[�X

			g_aJoystickCross[nKey] = g_aTempJoystickCross[nKey];	// �v���X


			//---- ���s�[�g���� ----
			if(GetJoystickCrossTrigger((JoystickCrossKey)nKey))	// �{�^�����������Ƃ�(���s�[�g�J�n��)
			{
				g_aJoystickCrossRepeatCount[nKey] = 0;		// �J�E���g������
				// ON(�������u�Ԃ́A�P���t)
				g_aJoystickCrossRepeatTrigger[nKey] = 0x80;	// ���s�[�g�g���K�[	
				g_aJoystickCrossRepeatPress[nKey] = 0x80;	// ���s�[�g�v���X
			}
			else if(GetJoystickCrossPress((JoystickCrossKey)nKey))	// ���������Ă���Ƃ�(���s�[�g��)
			{
				
				g_aJoystickCrossRepeatCount[nKey] += 1;	// �J�E���g�A�b�v

				if(g_aJoystickCrossRepeatCount[nKey] > 30000) g_aJoystickCrossRepeatCount[nKey] = 0;	// �I�[�o�[�t���[�΍�

				if(g_aJoystickCrossRepeatCount[nKey] > (float)FPS_DIRECTX * ((float)REPEAT_START_TIME / 1000.0f))		// ���s�[�^���J�n���鎞�Ԃ�ݒ�
				{
					// ���s�[�g�g���K�[�́AON/OFF���J��Ԃ�
					if((g_aJoystickCrossRepeatCount[nKey] % (int)(FPS_DIRECTX * REPEAT_INTERVAL / 1000)) == 0)	// �J��Ԃ��Ԋu
					{
						g_aJoystickCrossRepeatTrigger[nKey] = 0x80;	// �t���OON
					}
					else
					{
						g_aJoystickCrossRepeatTrigger[nKey] = 0x00;	// �t���OOFF
					}

					g_aJoystickCrossRepeatPress[nKey] = 0x80;	// ��Ƀt���OON(���s�[�g�v���X)
				}
				else
				{
					// OFF�i�ŏ��̂P���t��A��UOFF�ɂ��邽�߁j
					g_aJoystickCrossRepeatTrigger[nKey]	= 0x00;	// ���s�[�g�g���K�[	
					g_aJoystickCrossRepeatPress[nKey]	= 0x00;	// ���s�[�g�v���X
				}
			}
			else if(GetJoystickCrossRelease((JoystickCrossKey)nKey))	// �{�^���𗣂����Ƃ�(���s�[�g�I����)
			{
				g_aJoystickCrossRepeatCount[nKey] = 0;		// �J�E���g������
				// OFF�i�{�^�����͏I�����j
				g_aJoystickCrossRepeatTrigger[nKey] = 0x00;	// ���s�[�g�g���K�[	
				g_aJoystickCrossRepeatPress[nKey]	= 0x00;	// ���s�[�g�v���X
			}
			//---- ���s�[�g���������܂� ----
			
		}



		//========= ANALOG�_���� ==========================
		// ����́A�C�ɂ����

		// ��U���Z�b�g
		for(int nNumCrossKey = 0; nNumCrossKey < JCKP_MAX; nNumCrossKey++)
		{
			g_aJoystickCrossKeyPov[nNumCrossKey] = 0x00;
		}




		//---- �\���L�[��ԏ���(���������ŋ������Ȃ��̂ŁA���[�v���Ȃ��ėǂ�) ----
		// �W�����ŏォ��E���
		switch(dijs.rgdwPOV[0])
		{
		case 0:
			g_aJoystickCrossKeyPov[JCKP_UP] = 0x80; 
			break;
		case 4500:
			g_aJoystickCrossKeyPov[JCKP_RIGHT_UP] = 0x80; 
			break;
		case 9000:
			g_aJoystickCrossKeyPov[JCKP_RIGHT] = 0x80; 
			break;
		case 13500:
			g_aJoystickCrossKeyPov[JCKP_RIGHT_DOWN] = 0x80; 
			break;
		case 18000:
			g_aJoystickCrossKeyPov[JCKP_DOWN] = 0x80; 
			break;
		case 22500:
			g_aJoystickCrossKeyPov[JCKP_LEFT_DOWN] = 0x80;
			break;
		case 27000:
			g_aJoystickCrossKeyPov[JCKP_LEFT] = 0x80; 
			break;
		case 31500:
			g_aJoystickCrossKeyPov[JCKP_LEFT_UP] = 0x80; 
			break;
		default:
			break;
		}
	}
	else
	{
		g_pDIDevJoystick->Acquire();	// �\�����ʎ��ɁA�L�[�{�[�h�̃A�N�Z�X�����Ď擾
	}
}


//��----------------------------------��
//�W���C�X�e�B�b�N���͂̃v���X�擾�֐�
//��----------------------------------��
bool GetJoystickPress(int nKey)
{
	return (g_aJoystickButton[nKey] & 0x80) ? true : false;
}

//��----------------------------------��
//�W���C�X�e�B�b�N���͂̃g���K�[�擾�֐�
//��----------------------------------��
bool GetJoystickTrigger(int nKey)
{
	return (g_aJoystickButtonTrigger[nKey] & 0x80) ? true : false;
}

//��----------------------------------��
//�W���C�X�e�B�b�N���͂̃����[�X�擾�֐�
//��----------------------------------��
bool GetJoystickRelease(int nKey)
{
	return (g_aJoystickButtonRelease[nKey] & 0x80) ? true : false;
}

//��----------------------------------��
//�W���C�X�e�B�b�N���͂̃��s�[�g�g���K�[�擾�֐�
//��----------------------------------��
bool GetJoystickRepeatTrigger(int nKey)
{
	return (g_aJoystickButtonRepeatTrigger[nKey] & 0x80) ? true : false;
}

//��----------------------------------��
//�W���C�X�e�B�b�N���͂̃��s�[�g�擾�֐�
//��----------------------------------��
bool GetJoystickRepeatPress(int nKey)
{
	return (g_aJoystickButtonRepeatPress[nKey] & 0x80) ? true : false;
}

//��----------------------------------��
//�\���L�[���͂̃v���X�擾�֐�
//��----------------------------------��
bool GetJoystickCrossPov(JoystickCrossKeyPov nKey)
{
	return (g_aJoystickCrossKeyPov[nKey] & 0x80) ? true : false;
}

//��----------------------------------��
//�\���L�[���͂̃v���X�擾�֐�
//��----------------------------------��
bool GetJoystickCrossPress(JoystickCrossKey nKey)
{
	return (g_aJoystickCross[nKey] & 0x80) ? true : false;
}


//��----------------------------------��
//�W���C�X�e�B�b�N���͂̃g���K�[�擾�֐�
//��----------------------------------��
bool GetJoystickCrossTrigger(JoystickCrossKey nKey)
{
	return (g_aJoystickCrossTrigger[nKey] & 0x80) ? true : false;
}

//��----------------------------------��
//�\���L�[���͂̃����[�X�擾�֐�
//��----------------------------------��
bool GetJoystickCrossRelease(JoystickCrossKey nKey)
{
	return (g_aJoystickCrossRelease[nKey] & 0x80) ? true : false;
}


//��----------------------------------��
//�\���L�[���͂̃��s�[�g�g���K�[�擾�֐�
//��----------------------------------��
bool GetJoystickCrossRepeatTrigger(JoystickCrossKey nKey)
{
	return (g_aJoystickCrossRepeatTrigger[nKey] & 0x80) ? true : false;
}

//��----------------------------------��
//�\���L�[���͂̃��s�[�g�擾�֐�
//��----------------------------------��
bool GetJoystickCrossRepeatPress(JoystickCrossKey nKey)
{
	return (g_aJoystickCrossRepeatPress[nKey] & 0x80) ? true : false;
}

float GetJoysticklX()		{return (float)(g_JoyState.lX);}
float GetJoysticklY()		{return (float)(g_JoyState.lY);}
float GetJoysticklZ()		{return (float)(g_JoyState.lZ);}
float GetJoysticklRx()		{return (float)(g_JoyState.lRx);}
float GetJoysticklRy()		{return (float)(g_JoyState.lRy);}
float GetJoysticklRz()		{return (float)(g_JoyState.lRz);}
float GetJoysticklARx()		{return (float)(g_JoyState.lARx);}
float GetJoysticklARy()		{return (float)(g_JoyState.lARy);}
float GetJoysticklARz()		{return (float)(g_JoyState.lARz);}

float GetJoysticklFX()		{return (float)(g_JoyState.lFX);}
float GetJoysticklFY()		{return (float)(g_JoyState.lFY);}
float GetJoysticklFZ()		{return (float)(g_JoyState.lFZ);}

float GetJoysticklFRx()		{return (float)(g_JoyState.lFRx);}
float GetJoysticklFRy()		{return (float)(g_JoyState.lFRy);}
float GetJoysticklFRz()		{return (float)(g_JoyState.lFRz);}
