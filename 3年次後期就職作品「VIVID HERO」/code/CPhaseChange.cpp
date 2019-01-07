//��-------------------------------------------------------------------------��
//
//	File:CPhaseChange�̃t�@�C��[CPhaseChange.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CPhaseChange.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��
CPhase *CPhaseChange::m_pPhase = NULL;

//��-----------------------------------��
//CPhaseChange�̃R���X�g���N�^
//��-----------------------------------��
CPhaseChange::CPhaseChange()
{
	m_pPhase = NULL;
	m_pPhaseNext = NULL;
}

//��-----------------------------------��
//CPhaseChange�̃f�X�g���N�^
//��-----------------------------------��
CPhaseChange::~CPhaseChange()
{

}

//��-----------------------------------��
//CPhaseChange�̏���������
//��-----------------------------------��
HRESULT CPhaseChange::Init(CPhase *pStartPhase)
{
	m_pPhase = pStartPhase;
	m_pPhaseNext = pStartPhase;

	m_pPhase->Init();


	m_pFade = NULL;
	CFade::Create(FADE_IN,D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),60);

	return S_OK;
}

//��-----------------------------------��
//CPhaseChange�̏I������
//��-----------------------------------��
void CPhaseChange::Uninit(void)
{
	if(m_pPhase == m_pPhaseNext)
	{
		if(m_pPhase != NULL)
		{
			m_pPhase->Uninit();
			delete m_pPhase;
			m_pPhase = NULL;
		}
	}
	else
	{
		if(m_pPhase != NULL)
		{
			m_pPhase->Uninit();
			delete m_pPhase;
			m_pPhase = NULL;
		}

		if(m_pPhaseNext != NULL)
		{
			m_pPhaseNext->Uninit();
			delete m_pPhaseNext;
			m_pPhaseNext = NULL;
		}
	}
}

//��-----------------------------------��
//CPhaseChange�̍X�V����
//��-----------------------------------��
void CPhaseChange::Update(void)
{
	m_pPhase->Update();
}

//��-----------------------------------��
//CPhaseChange�̕`�揈��
//��-----------------------------------��
void CPhaseChange::Draw(void)
{
	m_pPhase->Draw();

	//�t�F�C�Y�`�F���W

	if(m_pFade == NULL)
	{

		//���ɍs�������̂����Ƃ͂�����������ύX���� �h���E���ۂ��Ȃ�����
		if(m_pPhase != m_pPhaseNext)
		{
			m_pFade = CFade::Create(FADE_OUT,D3DXCOLOR(0.0f,0.0f,0.0f,0.0f),60);
		}
	}
	else
	{
		if(m_pFade->GetFade() == FADE_NONE)
		{
			m_pPhase->Uninit();		//�O�̂͏I��
			delete m_pPhase;			//�O��̂�����
			m_pPhase = NULL;

			m_pPhase = m_pPhaseNext;	//���̂ɏ��ڂ点��
			m_pPhase->Init();			//���̂�̏�����

			//�t�F�C�h�C�����n�߂�
			m_pFade = NULL;
			CFade::Create(FADE_IN,D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),60);
		}
	}
}




