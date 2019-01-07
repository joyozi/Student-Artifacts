//��-------------------------------------------------------------------------��
//
//	File:�}�l�[�W���̃t�@�C��[CManager.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CManager.h"
#include "main.h"
#include "CPhaseTitle.h"
#include "Joystick.h"
#include "CCamera.h"
#include "CLight.h"
#include "CTextureManager.h"
#include "input.h"
#include "CDebugProc.h"
#include "CPhaseChange.h"
#include "CPhaseGame.h"
#include "CXFileManager.h"
#include "sound.h"
#include "joystick.h"
#include "Renderer.h"

//��-------------------------------------------------------------------------��
//�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��
CRenderer *CManager::m_Renderer = {NULL};
CLight *CManager::m_pLight = {NULL};
CCamera *CManager::m_pCamera = NULL;
CInput *CManager::m_pInput = {NULL};
CTextureManager *CManager::m_pTexManager = {NULL};
CPhaseChange *CManager::m_pPhaseChange = NULL;
CXFileManager *CManager::m_pXFileManager = NULL;

CJoystick *CManager::m_pJoystick = NULL;

//��-----------------------------------��
//�}�l�[�W���̃R���X�g���N�^
//��-----------------------------------��
CManager::CManager()
{

}

//��-----------------------------------��
//�}�l�[�W���̃f�X�g���N�^
//��-----------------------------------��
CManager::~CManager()
{

}

//��-----------------------------------��
//�}�l�[�W���̏���������
//��-----------------------------------��
HRESULT CManager::Init(HINSTANCE hInstance)
{
	//�����_���̏�����
	m_Renderer = new CRenderer;
	m_Renderer->Init(hInstance);

	//���C�g������
	m_pLight = new CLight;
	m_pLight -> Init();
	
	//�e�N�X�`���}�l�[�W��������
	m_pTexManager = new CTextureManager;
	m_pTexManager->Init(256);

	//X�t�@�C���}�l�[�W��������
	m_pXFileManager = new CXFileManager;
	m_pXFileManager->Init(256);
	
	//�L�[�{�[�h�̏�����
	m_pInput = new CInput;
	m_pInput->InitKeyboard(hInstance,GethWnd());

	//�T�E���h�̏�����
	InitSound(GethWnd());

	//�t�F�C�h�̏����� �����ōŏ��̃t�F�C�Y�����߂�
	m_pPhaseChange = new CPhaseChange;
	m_pPhaseChange->Init(new CPhaseTitle());

	return S_OK;
}

//��-----------------------------------��
//�}�l�[�W���̏I������
//��-----------------------------------��
void CManager::Uninit(void)
{
	if(m_Renderer != NULL)
	{
		m_Renderer->Uninit();
		delete m_Renderer;
		m_Renderer = NULL;
	}

	if(m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	if(m_pInput != NULL)
	{
		m_pInput->UninitKeyboard();
		delete m_pInput;
		m_pInput = NULL;
	}

	if(m_pTexManager != NULL)
	{
		m_pTexManager->Uninit();
		delete m_pTexManager;
		m_pTexManager = NULL;
	}

	if(m_pXFileManager != NULL)
	{
		m_pXFileManager->Uninit();
		delete m_pXFileManager;
		m_pXFileManager = NULL;
	}

	if(m_pPhaseChange != NULL)
	{
		m_pPhaseChange->Uninit();
		delete m_pPhaseChange;
		m_pPhaseChange = NULL;
	}

	UninitJoystick();

	UninitSound();

	CScene::ReleaseAll();
}

//��-----------------------------------��
//�}�l�[�W���̍X�V����
//��-----------------------------------��
void CManager::Update(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	m_pLight->Update();
	m_pInput->UpdateKeyboard();



	m_pPhaseChange->Update();

	m_Renderer->Update();
}

//��-----------------------------------��
//�}�l�[�W���̕`�揈��
//��-----------------------------------��
void CManager::Draw(void)
{
	m_pPhaseChange->Draw();
	m_Renderer->Draw();
}

//��-----------------------------------��
//�f�o�C�X�̎擾�����i�o�R�j
//��-----------------------------------��
LPDIRECT3DDEVICE9 CManager::GetDevice(void)
{
	return m_Renderer->GetDevice();
}

//��-----------------------------------��
//�e�N�X�`���}�l�[�W���̃|�C���^�̃Q�b�g����
//��-----------------------------------��
CTextureManager *CManager::GetTextureManagerPointer(void)
{
	return m_pTexManager;
}

//��-----------------------------------��
//X�t�@�C���}�l�[�W���̃|�C���^�̃Q�b�g����
//��-----------------------------------��
CXFileManager *CManager::GetXFileManagerPointer(void)
{
	return m_pXFileManager;
}

//��-----------------------------------��
//�J�����̃|�C���^�̃Q�b�g����
//��-----------------------------------��
CCamera *CManager::GetCameraPointer(void)
{
	return m_pCamera;
}

//��-----------------------------------��
//�t�F�C�h�`�F���W�̃|�C���^�̃Q�b�g����
//��-----------------------------------��
CPhaseChange *CManager::GetPhaseChangePointer(void)
{
	return m_pPhaseChange;
}

//��-----------------------------------��
//�r���{�[�h�̂��ߎ�σJ�����Z�b�g����
//��-----------------------------------��
void CManager::SetMainCameraPointer(CCamera *pCamera)
{
	m_pCamera = pCamera;
}
