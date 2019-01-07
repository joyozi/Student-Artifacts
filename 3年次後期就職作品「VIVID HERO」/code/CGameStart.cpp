//��-------------------------------------------------------------------------��
//
//	File:CGameStart�̃t�@�C��[CGameStart.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CGameStart.h"
#include "CItemList.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CGameStart�̃R���X�g���N�^
//��-----------------------------------��
CGameStart::CGameStart(int nPriority) : CScene2D(nPriority)
{
	m_Type = CTYPE_GAMESTART;

	m_pGameStart	 = NULL;
	m_GameStartTime	 = 0;
	m_EndJudge		 = false;
	m_FadeOutSize	 = D3DXVECTOR3(SCREEN_WIDTH-500.0f,200.0f,0.0f);
	m_FadeOutCol	= D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
}

//��-----------------------------------��
//CGameStart�̃f�X�g���N�^
//��-----------------------------------��
CGameStart::~CGameStart()
{

}

//��-----------------------------------��
//CGameStart�̏���������
//��-----------------------------------��
HRESULT CGameStart::Init(void)
{
	m_pGameStart = CScene2D::Create(100,"./data/TEXTURE/Game/UI/GameStartLogo00.png",
									D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f),
									m_FadeOutSize);

	return S_OK;
}

//��-----------------------------------��
//CGameStart�̏I������
//��-----------------------------------��
void CGameStart::Uninit(void)
{

}

//��-----------------------------------��
//CGameStart�̍X�V����
//��-----------------------------------��
void CGameStart::Update(void)
{
	m_GameStartTime++;

	if(m_GameStartTime == 1)
	{
		//�S�̂ɕK�v�ȏ�������x���邽��
		CScene::UpdateAll();
	}

	//�Q�[���X�^�[�g�̐������Ԃ܂ŕ\������
	if(m_GameStartTime >= GAMESTARTLOGO_TIME && m_EndJudge == false)
	{
		m_EndJudge = true;
	}
	//�������Ԃ��I��������e�N�X�`���𔖂��傫�����Ă���
	else if(m_GameStartTime >= GAMESTARTLOGO_TIME
		 && m_GameStartTime <= GAMESTARTLOGO_TIME + GAMESTARTLOGO_FADEOUT_TIME
		 && m_EndJudge)
	{
		m_FadeOutCol.a -= 1.0f / (float)(GAMESTARTLOGO_FADEOUT_TIME);
		m_pGameStart->SetVertex_Col(m_FadeOutCol);

		m_FadeOutSize = CItemList::Vec3lerp(m_FadeOutSize,D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f),1.0f / (float)(GAMESTARTLOGO_FADEOUT_TIME));
		m_pGameStart->SetSize(m_FadeOutSize);
	}
	//���ł����瑶�݂�����
	else if(m_GameStartTime >= GAMESTARTLOGO_TIME + GAMESTARTLOGO_FADEOUT_TIME && m_EndJudge)
	{
		if(m_pGameStart)
		{
			m_pGameStart->Uninit();
			m_pGameStart = NULL;
		}
	}
}

//��-----------------------------------��
//CGameStart�̕`�揈��
//��-----------------------------------��
void CGameStart::Draw(void)
{

}
//��-----------------------------------��
//CGameStart�̏I��������̔���
//��-----------------------------------��
bool CGameStart::GetGameStartEnd(void)
{
	return m_EndJudge;
}

//��-----------------------------------��
//CGameStart�̃N���G�C�g
//��-----------------------------------��
CGameStart *CGameStart::Create(void)
{
	CGameStart *pGameStart;
	pGameStart = new CGameStart();

	pGameStart->Init();

	return pGameStart;
}

