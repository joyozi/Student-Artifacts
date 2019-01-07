//◇-------------------------------------------------------------------------◇
//
//	File:CPhaseResultのファイル[CPhaseResult.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CPhaseResult.h"
#include "CManager.h"
#include "CPhaseChange.h"
#include "CPhaseTitle.h"
#include "input.h"
#include "joystick.h"
#include "sound.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CPhaseResultのコンストラクタ
//◇-----------------------------------◇
CPhaseResult::CPhaseResult(PHASE Phase)
{
	m_ResultJudge	= RESULT_NONE;
	m_NowPhase		= Phase;
	m_FlashJudge	= false;
	m_GoTitleCnt	= 0;

	for(int i = 0;i < 4;i++)
	{
		m_FlashCol[i] = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	}
}

//◇-----------------------------------◇
//CPhaseResultのコンストラクタ　その２
//◇-----------------------------------◇
CPhaseResult::CPhaseResult(PHASE Phase,RESULT_JUDGE Judge)
{
	m_ResultJudge = Judge;
	m_NowPhase = Phase;
	
	for(int i = 0;i < 4;i++)
	{
		m_FlashCol[i] = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	}
	m_FlashJudge = false;
}

//◇-----------------------------------◇
//CPhaseResultのデストラクタ
//◇-----------------------------------◇
CPhaseResult::~CPhaseResult()
{

}

//◇-----------------------------------◇
//CPhaseResultの初期化処理
//◇-----------------------------------◇
HRESULT CPhaseResult::Init(void)
{
	D3DXVECTOR3 PushA_Size = D3DXVECTOR3(400.0f,100.0f,0.0f);

	m_pScene2D = CScene2D::Create(60,"./data/TEXTURE/Title/PressEnter00.png",
									D3DXVECTOR3(SCREEN_WIDTH - PushA_Size.x/2 - 50.0f,SCREEN_HEIGHT - PushA_Size.y/2 - 20.0f,0.0f),
									PushA_Size);

	D3DXVECTOR3 LogoPos = D3DXVECTOR3(450.0f,200.0f,0.0f);
	D3DXVECTOR3 LogoSize = D3DXVECTOR3(800.0f,240.0f,0.0f);

	switch(m_ResultJudge)
	{
	case RESULT_NONE:
		break;

	case RESULT_CLEAR:
		PlaySound(SOUND_LABEL_GAMECLEAR);
		CScene2D::Create("./data/TEXTURE/Result/BackGround_GameClear.jpg",D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f),D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f));
		CScene2D::Create("./data/TEXTURE/Result/Logo_Clear.png",LogoPos,LogoSize);
		break;

	case RESULT_GAMEOVER:
		PlaySound(SOUND_LABEL_GAMEOVER);
		CScene2D::Create("./data/TEXTURE/Result/BackGround_GameOver.jpg",D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f),D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f));
		CScene2D::Create("./data/TEXTURE/Result/Logo_GameOver.png",LogoPos,LogoSize);
		break;
	default:
		break;
	}
	return S_OK;
}

//◇-----------------------------------◇
//CPhaseResultの終了処理
//◇-----------------------------------◇
void CPhaseResult::Uninit(void)
{
	switch(m_ResultJudge)
	{
	case RESULT_NONE:
		break;

	case RESULT_CLEAR:
		StopSound(SOUND_LABEL_GAMECLEAR);
		break;

	case RESULT_GAMEOVER:
		StopSound(SOUND_LABEL_GAMEOVER);
		break;

	default:
		break;
	}

	CScene::ReleaseAll();
}

//◇-----------------------------------◇
//CPhaseResultの更新処理
//◇-----------------------------------◇
void CPhaseResult::Update(void)
{
	CScene::UpdateAll();

	float FlashSpeed = 0.03f;

	m_pScene2D->SetVertex_Col(m_FlashCol);
	//点滅させる
	for(int i = 0;i < 4;i++)
	{
		if(m_FlashJudge)
			m_FlashCol[i].a +=FlashSpeed;
		else
			m_FlashCol[i].a -=FlashSpeed;
	}

	if(m_FlashCol[0].a < 0.0f)
	{
		m_FlashJudge = true;
	}
	else if(m_FlashCol[0].a > 1.0f)
	{
		m_FlashJudge = false;
	}



	if(m_GoTitleCnt >= 15 * 60 && m_GoTitleCnt < 15 * 60)
	{
		CManager::GetPhaseChangePointer()->PhaseChange(new CPhaseTitle());
		m_GoTitleCnt = 15 * 60;		//一度通ったらもう来ないよう
	}
	else if(m_GoTitleCnt < 15 * 60)
	{
		m_GoTitleCnt++;
	}

	if(CInput::GetKeyboardTrigger(DIK_RETURN))
	{
		PlaySound(SOUND_LABEL_Decision00);
		CManager::GetPhaseChangePointer()->PhaseChange(new CPhaseTitle());
	}
}

//◇-----------------------------------◇
//CPhaseResultの描画処理
//◇-----------------------------------◇
void CPhaseResult::Draw(void)
{

}


