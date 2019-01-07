//◇-------------------------------------------------------------------------◇
//
//	File:CGameStartのファイル[CGameStart.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CGameStart.h"
#include "CItemList.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CGameStartのコンストラクタ
//◇-----------------------------------◇
CGameStart::CGameStart(int nPriority) : CScene2D(nPriority)
{
	m_Type = CTYPE_GAMESTART;

	m_pGameStart	 = NULL;
	m_GameStartTime	 = 0;
	m_EndJudge		 = false;
	m_FadeOutSize	 = D3DXVECTOR3(SCREEN_WIDTH-500.0f,200.0f,0.0f);
	m_FadeOutCol	= D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
}

//◇-----------------------------------◇
//CGameStartのデストラクタ
//◇-----------------------------------◇
CGameStart::~CGameStart()
{

}

//◇-----------------------------------◇
//CGameStartの初期化処理
//◇-----------------------------------◇
HRESULT CGameStart::Init(void)
{
	m_pGameStart = CScene2D::Create(100,"./data/TEXTURE/Game/UI/GameStartLogo00.png",
									D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f),
									m_FadeOutSize);

	return S_OK;
}

//◇-----------------------------------◇
//CGameStartの終了処理
//◇-----------------------------------◇
void CGameStart::Uninit(void)
{

}

//◇-----------------------------------◇
//CGameStartの更新処理
//◇-----------------------------------◇
void CGameStart::Update(void)
{
	m_GameStartTime++;

	if(m_GameStartTime == 1)
	{
		//全体に必要な処理を一度するため
		CScene::UpdateAll();
	}

	//ゲームスタートの制限時間まで表示する
	if(m_GameStartTime >= GAMESTARTLOGO_TIME && m_EndJudge == false)
	{
		m_EndJudge = true;
	}
	//制限時間が終了したらテクスチャを薄く大きくしていく
	else if(m_GameStartTime >= GAMESTARTLOGO_TIME
		 && m_GameStartTime <= GAMESTARTLOGO_TIME + GAMESTARTLOGO_FADEOUT_TIME
		 && m_EndJudge)
	{
		m_FadeOutCol.a -= 1.0f / (float)(GAMESTARTLOGO_FADEOUT_TIME);
		m_pGameStart->SetVertex_Col(m_FadeOutCol);

		m_FadeOutSize = CItemList::Vec3lerp(m_FadeOutSize,D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f),1.0f / (float)(GAMESTARTLOGO_FADEOUT_TIME));
		m_pGameStart->SetSize(m_FadeOutSize);
	}
	//消滅したら存在も消す
	else if(m_GameStartTime >= GAMESTARTLOGO_TIME + GAMESTARTLOGO_FADEOUT_TIME && m_EndJudge)
	{
		if(m_pGameStart)
		{
			m_pGameStart->Uninit();
			m_pGameStart = NULL;
		}
	}
}

//◇-----------------------------------◇
//CGameStartの描画処理
//◇-----------------------------------◇
void CGameStart::Draw(void)
{

}
//◇-----------------------------------◇
//CGameStartの終わったかの判定
//◇-----------------------------------◇
bool CGameStart::GetGameStartEnd(void)
{
	return m_EndJudge;
}

//◇-----------------------------------◇
//CGameStartのクリエイト
//◇-----------------------------------◇
CGameStart *CGameStart::Create(void)
{
	CGameStart *pGameStart;
	pGameStart = new CGameStart();

	pGameStart->Init();

	return pGameStart;
}

