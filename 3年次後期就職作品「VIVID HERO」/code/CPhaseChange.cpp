//◇-------------------------------------------------------------------------◇
//
//	File:CPhaseChangeのファイル[CPhaseChange.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CPhaseChange.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇
CPhase *CPhaseChange::m_pPhase = NULL;

//◇-----------------------------------◇
//CPhaseChangeのコンストラクタ
//◇-----------------------------------◇
CPhaseChange::CPhaseChange()
{
	m_pPhase = NULL;
	m_pPhaseNext = NULL;
}

//◇-----------------------------------◇
//CPhaseChangeのデストラクタ
//◇-----------------------------------◇
CPhaseChange::~CPhaseChange()
{

}

//◇-----------------------------------◇
//CPhaseChangeの初期化処理
//◇-----------------------------------◇
HRESULT CPhaseChange::Init(CPhase *pStartPhase)
{
	m_pPhase = pStartPhase;
	m_pPhaseNext = pStartPhase;

	m_pPhase->Init();


	m_pFade = NULL;
	CFade::Create(FADE_IN,D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),60);

	return S_OK;
}

//◇-----------------------------------◇
//CPhaseChangeの終了処理
//◇-----------------------------------◇
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

//◇-----------------------------------◇
//CPhaseChangeの更新処理
//◇-----------------------------------◇
void CPhaseChange::Update(void)
{
	m_pPhase->Update();
}

//◇-----------------------------------◇
//CPhaseChangeの描画処理
//◇-----------------------------------◇
void CPhaseChange::Draw(void)
{
	m_pPhase->Draw();

	//フェイズチェンジ

	if(m_pFade == NULL)
	{

		//次に行きたいのが今とはちがかったら変更する ドロウっぽくない処理
		if(m_pPhase != m_pPhaseNext)
		{
			m_pFade = CFade::Create(FADE_OUT,D3DXCOLOR(0.0f,0.0f,0.0f,0.0f),60);
		}
	}
	else
	{
		if(m_pFade->GetFade() == FADE_NONE)
		{
			m_pPhase->Uninit();		//前のは終了
			delete m_pPhase;			//前回のを消す
			m_pPhase = NULL;

			m_pPhase = m_pPhaseNext;	//次のに乗り移らせる
			m_pPhase->Init();			//次のやつの初期化

			//フェイドインを始める
			m_pFade = NULL;
			CFade::Create(FADE_IN,D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),60);
		}
	}
}




