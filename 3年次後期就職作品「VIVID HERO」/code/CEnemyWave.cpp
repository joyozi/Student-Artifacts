//◇-------------------------------------------------------------------------◇
//
//	File:CEnemyWaveのファイル[CEnemyWave.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CEnemyWave.h"
#include "CEnemy001.h"
#include "CEnemyPattern000.h"
#include "CBulletPatternEnemy000.h"
#include "CBulletPatternEnemy001.h"
#include "CEnemyPatternStop.h"
#include "CEnemyPatternRandam.h"
#include "CManager.h"
#include "CPhaseChange.h"
#include "CPhaseResult.h"
#include "CPhase.h"
#include "sound.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CEnemyWaveのコンストラクタ
//◇-----------------------------------◇
CEnemyWave::CEnemyWave(int nPriority) : CScene2D(nPriority)
{
	m_WaveChangeJudge = 0;

	for(int i = 0;i < ENEMYWAVE_MAX;i++)
	{
		m_pEnemyCounter[i] = NULL;
	}
}

//◇-----------------------------------◇
//CEnemyWaveのデストラクタ
//◇-----------------------------------◇
CEnemyWave::~CEnemyWave()
{

}

//◇-----------------------------------◇
//CEnemyWaveの初期化処理
//◇-----------------------------------◇
HRESULT CEnemyWave::Init(void)
{
	EnemyWave_First(2);

	return S_OK;
}

//◇-----------------------------------◇
//CEnemyWaveの終了処理
//◇-----------------------------------◇
void CEnemyWave::Uninit(void)
{
	for(int i = 0;i < ENEMYWAVE_MAX;i++)
	{

	}
}

//◇-----------------------------------◇
//CEnemyWaveの更新処理
//◇-----------------------------------◇
void CEnemyWave::Update(void)
{
	CScene *pEnemyPointer[ENEMYWAVE_MAX] = {NULL};

	CScene::SearchLinkList(pEnemyPointer,CTYPE_ENEMY);

	//探しても誰もいなかったらスイッチ！
	if(pEnemyPointer[0] == NULL)
	{
		if(m_WaveChangeJudge < 5)
		{
			PlaySound(SOUND_LABEL_EnemyPop00);
			EnemyWave_Second(m_WaveChangeJudge + 2);
			m_WaveChangeJudge++;
		}
		else
		{
			CManager::GetPhaseChangePointer()->PhaseChange(new CPhaseResult(PHASE_RESULT,RESULT_CLEAR));
		}
	}

}

//◇-----------------------------------◇
//CEnemyWaveの何もしないドロウ
//◇-----------------------------------◇
void CEnemyWave::Draw(void)
{

}

//◇-----------------------------------◇
//CEnemyWaveのウェーブ
//◇-----------------------------------◇
CEnemyWave *CEnemyWave::Create()
{
	CEnemyWave *pEnemyWave;
	pEnemyWave = new CEnemyWave;

	pEnemyWave->Init();

	return pEnemyWave;

}

//◇-----------------------------------◇
//CEnemyWaveのウェーブその１
//◇-----------------------------------◇
void CEnemyWave::EnemyWave_First(int Num)
{
	m_pEnemyCounter[0] = CEnemy001::Create("./data/MODEL/Enemy/Enemy002.x",D3DXVECTOR3(0.0f,0.0f,0.500f),new CBulletPatternEnemy001,new CEnemyPatternRandam);
	m_pEnemyCounter[1] = CEnemy001::Create("./data/MODEL/Enemy/Enemy002.x",D3DXVECTOR3(3000.0f,0.0f,0.0f),new CBulletPatternEnemy001,new CEnemyPatternRandam);
	m_pEnemyCounter[2] = CEnemy001::Create("./data/MODEL/Enemy/Enemy002.x",D3DXVECTOR3(-3000.0f,0.0f,500.0f),new CBulletPatternEnemy001,new CEnemyPatternRandam);
}

//◇-----------------------------------◇
//CEnemyWaveのウェーブその２
//◇-----------------------------------◇
void CEnemyWave::EnemyWave_Second(int Num)
{

	for(int i = 0;i < Num;i++)
	{
		D3DXVECTOR3 Pos;
		
		Pos.x = (float)(rand()%6000) - 3000.0f;
		Pos.y = (float)(rand()%3000) - 1500.0f;
		Pos.z = (float)(rand()%6000) - 3000.0f;
		m_pEnemyCounter[i] = CEnemy001::Create("./data/MODEL/Enemy/Enemy002.x",Pos,new CBulletPatternEnemy001,new CEnemyPatternRandam);
	}
}