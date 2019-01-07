//◇-------------------------------------------------------------------------◇
//
//	File:CPhaseGameのファイル[CPhaseGame.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CPhaseGame.h"
#include "CManager.h"

#include "CPhaseChange.h"
#include "CPhaseResult.h"
#include "input.h"
#include "CFade.h"
#include "CDebugProc.h"
#include "CSceneModelParts.h"
#include "CPlayerModel.h"
#include "CDegeneracyPolygon.h"
#include "CCameraGame.h"
#include "CDegeneracyStar.h"
#include "CScore.h"
#include "CEnemy000.h"
#include "CTimer.h"
#include "CSceneBillboard.h"
#include "CMeshSky.h"
#include "CParticleSystem.h"
#include "CDegeneracyAnimation.h"
#include "CEnemy001.h"
#include "CExplosion000.h"
#include "CBulletPattern1Shot.h"
#include "sound.h"
#include "CMiniMap.h"
#include "CTargetUI.h"
#include "CPause.h"
#include "joystick.h"
#include "CEnemyBullet001.h"
#include "CMissileGaze.h"
#include "CEnemyWave.h"
#include "CMeshHitCheckBall.h"
#include "CGameStart.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇
CPhaseGame *CPhaseGame::m_pPhaseGame = NULL;
CExplosion000 *CPhaseGame::m_pExplosionPointer[EX_MAX] = {NULL};
CEnemyBullet001 *CPhaseGame::m_pEnemyBullet001Pointer = NULL;

static int MusicCnt = 0;

//◇-----------------------------------◇
//CPhaseGameのコンストラクタ
//◇-----------------------------------◇
CPhaseGame::CPhaseGame(PHASE Phase)
{
	m_NowPhase = Phase;

	m_pCameraGame = NULL;
	m_pPause = NULL;
	m_PauseJudge = false;
	m_pPhaseGame = this;

	m_pGameStartPointer = NULL;
}

//◇-----------------------------------◇
//CPhaseGameのデストラクタ
//◇-----------------------------------◇
CPhaseGame::~CPhaseGame()
{

}

//◇-----------------------------------◇
//CPhaseGameの初期化処理
//◇-----------------------------------◇
HRESULT CPhaseGame::Init(void)
{
	PlaySound(SOUND_LABEL_GAMEMAINBGM);
	MusicCnt = 0;

	//カメラ初期化
	m_pCameraGame = new CCameraGame;
	m_pCameraGame -> Init();
	CManager::SetMainCameraPointer(m_pCameraGame);

	//テクスチャをロードさせるため
	m_pPause = new CPause;
	m_pPause->Init();
	m_pPause->Uninit();
	delete m_pPause;
	m_pPause = NULL;

#ifdef _DEBUG
	CMeshHitCheckBall::Create();
#endif

	CPlayerModel::Create(D3DXVECTOR3(0.0f,0.0f,-3000.0f));
	CDegeneracyStar::Create("./data/TEXTURE/Game/shadow000.jpg",D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	
	//縮退アニメーションのセット
	m_pExplosionPointer[EX_00] = CExplosion000::Create("./data/TEXTURE/Game/Effect/btleffect015.png",8,1,32,128);
	m_pExplosionPointer[EX_01] = CExplosion000::Create("./data/TEXTURE/Game/Effect/100_Effect.png",10,1,60,128);
	m_pExplosionPointer[EX_02_SMOG] = CExplosion000::Create("./data/TEXTURE/Game/Effect/101_Effect.png",10,1,60,4096);
	m_pExplosionPointer[EX_03_BIGBANG] = CExplosion000::Create("./data/TEXTURE/Game/Effect/108_Effect.png",1,7,21,32);
	m_pExplosionPointer[EX_04_MAZZLEFLASH] = CExplosion000::Create("./data/TEXTURE/Game/Effect/110_Effect.png",8,1,16,1024);
	m_pExplosionPointer[EX_05_NORMALEX] = CExplosion000::Create("./data/TEXTURE/Game/Effect/105_Effect.png",10,1,30,158);

	//バレットのセット
	m_pEnemyBullet001Pointer = CEnemyBullet001::Create();

	//その他のセット
	CTargetUI::Create("./data/TEXTURE/Game/UI/TargetTex000.png");
	CEnemyWave::Create();
	CMiniMap::Create();
	CMissileGaze::Create();

	m_pGameStartPointer = CGameStart::Create();

	return S_OK;
}

//◇-----------------------------------◇
//CPhaseGameの終了処理
//◇-----------------------------------◇
void CPhaseGame::Uninit(void)
{
	CScene::ReleaseAll();

	if(m_pCameraGame != NULL)
	{
		m_pCameraGame->Uninit();
		delete m_pCameraGame;
		m_pCameraGame = NULL;
	}

	SAFE_DELETE(m_pPause);
	
	StopSound(SOUND_LABEL_GAMEMAINBGM);
}

//◇-----------------------------------◇
//CPhaseGameの更新処理
//◇-----------------------------------◇
void CPhaseGame::Update(void)
{
	MusicCnt++;

	if(MusicCnt >= 60*77)
	{
		PlaySound(SOUND_LABEL_GAMEMAINBGM);
		MusicCnt = 0;
	}

	if(m_pGameStartPointer->GetGameStartEnd() == false)
	{
		m_pGameStartPointer->Update();

		//FADEだけ回す
		CScene *pFade = NULL;
		CScene::SearchLinkList(&pFade,CTYPE_FADE);

		if(pFade != NULL)
			pFade->Update();
	}
	else
	{
		if(m_PauseJudge)
		{
			m_pPause->Update();

			//FADEだけ回す
			CScene *pFade = NULL;
			CScene::SearchLinkList(&pFade,CTYPE_FADE);

			if(pFade != NULL)
				pFade->Update();

			if(m_pPause->PauseNowJudge() == false)
			{//向こうのuninitが呼ばれたらこっちもなる
				m_pPause->Uninit();
				delete m_pPause;
				m_pPause = NULL;
				m_PauseJudge = false;
			}

			if(CInput::GetKeyboardTrigger(DIK_P) && m_PauseJudge)
			{
				m_pPause->Uninit();
				delete m_pPause;
				m_pPause = NULL;
				m_PauseJudge = false;
			}
		}
		else
		{
			CScene::UpdateAll();

			if(CInput::GetKeyboardTrigger(DIK_P))
			{
				if(m_PauseJudge == false)
				{
					PlaySound(SOUND_LABEL_GunKamae);
		
					m_pPause = new CPause;
					m_pPause->Init();
					m_PauseJudge = true;
				}
			}
		}
	}

	m_pCameraGame->Update();
	CManager::SetMainCameraPointer(m_pCameraGame);
}

//◇-----------------------------------◇
//CPhaseGameの描画処理
//◇-----------------------------------◇
void CPhaseGame::Draw(void)
{
	if(m_PauseJudge)
	{
		m_pPause->Draw();
	}

	m_pCameraGame->Set();
}
