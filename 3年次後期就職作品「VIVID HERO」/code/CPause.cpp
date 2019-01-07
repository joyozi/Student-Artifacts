//◇-------------------------------------------------------------------------◇
//
//	File:CPauseのファイル[CPause.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CPause.h"
#include "CManager.h"
#include "CPhaseTitle.h"
#include "CPhaseChange.h"
#include "CPhaseGame.h"
#include "joystick.h"
#include "sound.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CPauseのコンストラクタ
//◇-----------------------------------◇
CPause::CPause()
{
	m_PauseJudge = true;		//起動したらここに来るから
}

//◇-----------------------------------◇
//CPauseのデストラクタ
//◇-----------------------------------◇
CPause::~CPause()
{

}

//◇-----------------------------------◇
//CPauseの初期化処理
//◇-----------------------------------◇
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


	//背景白かの後に
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

//◇-----------------------------------◇
//CPauseの終了処理
//◇-----------------------------------◇
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

//◇-----------------------------------◇
//CPauseの更新処理
//◇-----------------------------------◇
void CPause::Update(void)
{
	//RETRYのときに下を押すとQUIT　上を押すとCONTINUE
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

	//CONTINUEのときに下を押すとRETRY
	else if(m_SelectMenu == PAUSE_MENU_CONTINUE)
	{
		if(CInput::GetKeyboardTrigger(DIK_S))
		{
			PlaySound(SOUND_LABEL_GunKamae);
			m_SelectMenu = PAUSE_MENU_RETRY;
		}
	}
	
	//QUITのときに上を押すとRETRY
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



	//決定する
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

	
	//×ボタンを押されても終わり
	if(CInput::GetKeyboardTrigger(DIK_P))
	{
		m_PauseJudge = false;
	}

	for(int i = 0;i < 7;i++)
	{
		m_pPause2D[i]->Update();
	}
}



//◇-----------------------------------◇
//CPauseの描画処理
//◇-----------------------------------◇
void CPause::Draw(void)
{
	for(int i = 0;i < 7;i++)
	{
		m_pPause2D[i]->Draw();
	}
}



//◇-----------------------------------◇
//CPauseの終了かどうかの判定
//◇-----------------------------------◇
bool CPause::PauseNowJudge(void)
{
	return m_PauseJudge;
}


