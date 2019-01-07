//��-------------------------------------------------------------------------��
//
//	File:CPause�̃t�@�C��[CPause.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CPause.h"
#include "CManager.h"
#include "CPhaseTitle.h"
#include "CPhaseChange.h"
#include "CPhaseGame.h"
#include "joystick.h"
#include "sound.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CPause�̃R���X�g���N�^
//��-----------------------------------��
CPause::CPause()
{
	m_PauseJudge = true;		//�N�������炱���ɗ��邩��
}

//��-----------------------------------��
//CPause�̃f�X�g���N�^
//��-----------------------------------��
CPause::~CPause()
{

}

//��-----------------------------------��
//CPause�̏���������
//��-----------------------------------��
HRESULT CPause::Init(void)
{
	m_SelectMenu = PAUSE_MENU_CONTINUE;

	m_pPause2D[0] = CScene2D::Create(PRIORITY_NUM - 4,NULL,D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f),D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f));

	D3DXCOLOR Col[4];

	Col[0] = D3DXCOLOR(0.0f,0.0f,0.0f,0.5f);
	Col[1] = D3DXCOLOR(0.0f,0.0f,0.0f,0.5f);
	Col[2] = D3DXCOLOR(0.0f,0.0f,0.0f,0.5f);
	Col[3] = D3DXCOLOR(0.0f,0.0f,0.0f,0.5f);

	m_pPause2D[0]->SetVertex_Col(Col);


	//�w�i�����̌��
	m_pPause2D[1] = CScene2D::Create(PRIORITY_NUM - 4,"./data/TEXTURE/Game/Pause/PauseFrame00.png",D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f),D3DXVECTOR3(700.0f,500.0f,0.0f));

	m_pPause2D[2] = CScene2D::Create(PRIORITY_NUM - 4,"./data/TEXTURE/Game/Pause/Carsol01.png",D3DXVECTOR3(SCREEN_WIDTH / 2,280.0f,0.0f),D3DXVECTOR3(350.0f,100.0f,0.0f));

	Col[0] = D3DXCOLOR(1.0f,0.0f,1.0f,0.8f);
	Col[1] = D3DXCOLOR(1.0f,0.0f,1.0f,0.8f);
	Col[2] = D3DXCOLOR(1.0f,0.0f,1.0f,0.8f);
	Col[3] = D3DXCOLOR(1.0f,0.0f,1.0f,0.8f);

	m_pPause2D[2]->SetVertex_Col(Col);

	m_pPause2D[3] = CScene2D::Create(PRIORITY_NUM - 3,"./data/TEXTURE/Game/Pause/Pause.png",D3DXVECTOR3(SCREEN_WIDTH / 2,170.0f,0.0f),D3DXVECTOR3(250.0f,100.0f,0.0f));
	m_pPause2D[4] = CScene2D::Create(PRIORITY_NUM - 3,"./data/TEXTURE/Game/Pause/Continue.png",D3DXVECTOR3(SCREEN_WIDTH / 2,280.0f,0.0f),D3DXVECTOR3(300.0f,100.0f,0.0f));
	m_pPause2D[5] = CScene2D::Create(PRIORITY_NUM - 3,"./data/TEXTURE/Game/Pause/Retry.png",D3DXVECTOR3(SCREEN_WIDTH / 2,380.0f,0.0f),D3DXVECTOR3(300.0f,100.0f,0.0f));
	m_pPause2D[6] = CScene2D::Create(PRIORITY_NUM - 3,"./data/TEXTURE/Game/Pause/Quit.png",D3DXVECTOR3(SCREEN_WIDTH / 2,480.0f,0.0f),D3DXVECTOR3(300.0f,100.0f,0.0f));


	return S_OK;
}

//��-----------------------------------��
//CPause�̏I������
//��-----------------------------------��
void CPause::Uninit(void)
{
	for(int i = 0;i < 7;i++)
	{
		if(m_pPause2D != NULL)
		{
			m_pPause2D[i]->Uninit();
		}
	}
}

//��-----------------------------------��
//CPause�̍X�V����
//��-----------------------------------��
void CPause::Update(void)
{
	//RETRY�̂Ƃ��ɉ���������QUIT�@���������CONTINUE
	if(m_SelectMenu == PAUSE_MENU_RETRY)
	{
		if(CInput::GetKeyboardTrigger(DIK_S))
		{
			PlaySound(SOUND_LABEL_GunKamae);
			m_SelectMenu = PAUSE_MENU_QUIT;
		}
		if(CInput::GetKeyboardTrigger(DIK_W))
		{
			PlaySound(SOUND_LABEL_GunKamae);
			m_SelectMenu = PAUSE_MENU_CONTINUE;
		}
	}

	//CONTINUE�̂Ƃ��ɉ���������RETRY
	else if(m_SelectMenu == PAUSE_MENU_CONTINUE)
	{
		if(CInput::GetKeyboardTrigger(DIK_S))
		{
			PlaySound(SOUND_LABEL_GunKamae);
			m_SelectMenu = PAUSE_MENU_RETRY;
		}
	}
	
	//QUIT�̂Ƃ��ɏ��������RETRY
	else if(m_SelectMenu == PAUSE_MENU_QUIT)
	{
		if(CInput::GetKeyboardTrigger(DIK_W))
		{
			PlaySound(SOUND_LABEL_GunKamae);
			m_SelectMenu = PAUSE_MENU_RETRY;
		}
	}



	switch(m_SelectMenu)
	{
	case PAUSE_MENU_CONTINUE:
		m_pPause2D[2]->SetPosition_Re(D3DXVECTOR3(SCREEN_WIDTH / 2,280.0f,0.0f));
		break;

	case PAUSE_MENU_RETRY:
		m_pPause2D[2]->SetPosition_Re(D3DXVECTOR3(SCREEN_WIDTH / 2,380.0f,0.0f));
		break;

	case PAUSE_MENU_QUIT:
		m_pPause2D[2]->SetPosition_Re(D3DXVECTOR3(SCREEN_WIDTH / 2,480.0f,0.0f));
		break;

	default:
		break;
	}



	//���肷��
	if(CInput::GetKeyboardTrigger(DIK_RETURN))
	{
		switch(m_SelectMenu)
		{
		case PAUSE_MENU_CONTINUE:
			PlaySound(SOUND_LABEL_Decision00);
			m_PauseJudge = false;
			break;

		case PAUSE_MENU_RETRY:
			PlaySound(SOUND_LABEL_Decision00);
			m_PauseJudge = false;
			CManager::GetPhaseChangePointer()->PhaseChange(new CPhaseGame());
			break;

		case PAUSE_MENU_QUIT:
			PlaySound(SOUND_LABEL_Decision00);
			m_PauseJudge = false;
			CManager::GetPhaseChangePointer()->PhaseChange(new CPhaseTitle());
			break;
		}
	}

	
	//�~�{�^����������Ă��I���
	if(CInput::GetKeyboardTrigger(DIK_P))
	{
		m_PauseJudge = false;
	}

	for(int i = 0;i < 7;i++)
	{
		m_pPause2D[i]->Update();
	}
}



//��-----------------------------------��
//CPause�̕`�揈��
//��-----------------------------------��
void CPause::Draw(void)
{
	for(int i = 0;i < 7;i++)
	{
		m_pPause2D[i]->Draw();
	}
}



//��-----------------------------------��
//CPause�̏I�����ǂ����̔���
//��-----------------------------------��
bool CPause::PauseNowJudge(void)
{
	return m_PauseJudge;
}


