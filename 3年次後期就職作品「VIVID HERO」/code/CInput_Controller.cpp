//��-------------------------------------------------------------------------��
//
//	File:CInput_Controller�̃t�@�C��[CInput_Controller.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CInput_Controller.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CInput_Controller�̃R���X�g���N�^
//��-----------------------------------��
CInput_Controller::CInput_Controller()
{
	g_pDInput = NULL;
	g_pDIDevController = NULL;
}

//��-----------------------------------��
//CInput_Controller�̃f�X�g���N�^
//��-----------------------------------��
CInput_Controller::~CInput_Controller()
{

}

//��-----------------------------------��
//CInput_Controller�̏���������
//��-----------------------------------��
HRESULT CInput_Controller::Init(HINSTANCE hInstance,HWND hWnd)
{
	HRESULT hr;
	int nID;

	hr = DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&g_pDInput,NULL);
	if(FAILED(hr))
	{
		nID = MessageBox(NULL,"�C���v�b�g��������������������","�C���v�b�g���������������������ł�",MB_YESNO);
		return hr;
	}


	hr = g_pDInput -> CreateDevice(GUID_SysKeyboard,&g_pDIDevController,NULL);
	if(FAILED(hr))
	{
		nID = MessageBox(NULL,"��������������","���������������ł�",MB_YESNO);
		return hr;
	}



	//�g�p�\�ȃf�o�C�X�𒲂ׂ�
//	hr = g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL,EnumJoyCallback,NULL,DIEDFL_ATTACHEDONLY);

	if(FAILED(hr)|| g_pDIDevController == NULL)
	{
		////�I�u�W�F�N�g�쐬���s
	}

	hr = g_pDIDevController -> SetDataFormat(&c_dfDIJoystick2);
	if(FAILED(hr))
	{
		nID = MessageBox(NULL,"��������������","���������������ł�",
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

//��-----------------------------------��
//CInput_Controller�̏I������
//��-----------------------------------��
void CInput_Controller::Uninit(void)
{

}

//��-----------------------------------��
//CInput_Controller�̍X�V����
//��-----------------------------------��
void CInput_Controller::Update(void)
{

}

//��-----------------------------------��
//CInput_Controller�̕`�揈��
//��-----------------------------------��
void CInput_Controller::Draw(void)
{

}

BOOL CALLBACK CInput_Controller::EnumJoyCallback(const DIDEVICEINSTANCE* pdidInstance,VOID* pContext)
{
	HRESULT hr;

	DIDEVCAPS g_diDevCaps;

	//�񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�t�F�[�X���擾����
	hr = g_pDInput->CreateDevice(pdidInstance->guidInstance,&g_pDIDevController,NULL);

	if(FAILED(hr))
	{
		return DIENUM_CONTINUE;
	}


	//�W���C�X�e�B�b�N�̔\�͂𒲂ׂ�
	g_diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hr = g_pDIDevController->GetCapabilities(&g_diDevCaps);

	if(FAILED(hr))
	{
		//�W���C�X�e�B�b�N�̔\�͂̎擾�Ɏ��s
		g_pDIDevController->Release();
		g_pDIDevController = NULL;

		return DIENUM_CONTINUE;
	}

	//�W���C�X�e�B�b�N�̔\�͂��`�F�b�N����

	return DIENUM_STOP;
	return DIENUM_CONTINUE;
}