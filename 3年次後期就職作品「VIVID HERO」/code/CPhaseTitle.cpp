//��-------------------------------------------------------------------------��
//
//	File:CPhaseTitle�̃t�@�C��[CPhaseTitle.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CPhaseTitle.h"
#include "CManager.h"

#include "CCamera.h"
#include "CSceneModelParts.h"
#include "CScene3D.h"
#include "CDegeneracyStar.h"
#include "CTitleMenu.h"
#include "sound.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��
static int g_SoundTime = 0;

//��-----------------------------------��
//CPhaseTitle�̃R���X�g���N�^
//��-----------------------------------��
CPhaseTitle::CPhaseTitle(PHASE Phase)
{
	g_SoundTime = 0;

	m_NowPhase = Phase;

}

//��-----------------------------------��
//CPhaseTitle�̃f�X�g���N�^
//��-----------------------------------��
CPhaseTitle::~CPhaseTitle()
{

}

//��-----------------------------------��
//CPhaseTitle�̏���������
//��-----------------------------------��
HRESULT CPhaseTitle::Init(void)
{
	m_pCamera = new CCamera;
	m_pCamera->Init();
	CManager::SetMainCameraPointer(m_pCamera);

	m_pCamera->CameraMovePSet(D3DXVECTOR3(0.0f,0.0f,-350.0f));
	m_pCamera->CameraMoveRSet(D3DXVECTOR3(0.0f,0.0f,0.0f));

	CDegeneracyStar::Create("./data/TEXTURE/Game/shadow000.jpg",D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	CSceneModelParts::Create("./data/TEXTDATA/motion_TitileMotion.txt",D3DXVECTOR3(-150.0f,-80.0f,0.0f));

	CScene2D::Create(60,"./data/TEXTURE/Title/TitleLogo00.png",D3DXVECTOR3(500,200,0.0f),D3DXVECTOR3(1000.0f,250.0f,0.0f));

	m_pTitleMenu = new CTitleMenu;
	m_pTitleMenu->Init();


	PlaySound(SOUND_LABEL_TITLE);



	return S_OK;
}

//��-----------------------------------��
//CPhaseTitle�̏I������
//��-----------------------------------��
void CPhaseTitle::Uninit(void)
{
	CScene::ReleaseAll();

	if(m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	if(m_pTitleMenu != NULL)
	{
		m_pTitleMenu->Uninit();
		delete m_pTitleMenu;
		m_pTitleMenu = NULL;
	}

	StopSound(SOUND_LABEL_TITLE);
}

//��-----------------------------------��
//CPhaseTitle�̍X�V����
//��-----------------------------------��
void CPhaseTitle::Update(void)
{
	if(g_SoundTime >= 60 * 109)
	{
		g_SoundTime = 0;
		PlaySound(SOUND_LABEL_TITLE);

	}
	g_SoundTime++;

	m_pCamera->Update();
	CManager::SetMainCameraPointer(m_pCamera);

	m_pTitleMenu->Update();

	CScene::UpdateAll();
}

//��-----------------------------------��
//CPhaseTitle�̕`�揈��
//��-----------------------------------��
void CPhaseTitle::Draw(void)
{
	m_pTitleMenu->Draw();

	m_pCamera->Set();
}


