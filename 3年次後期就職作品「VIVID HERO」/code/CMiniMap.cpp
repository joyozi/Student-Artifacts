//◇-------------------------------------------------------------------------◇
//
//	File:CMiniMapのファイル[CMiniMap.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CMiniMap.h"
#include "CScene2D.h"
#include "CEnemyIcon.h"
#include "CPlayerModel.h"
#include "CScore.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇
std::vector<CEnemy001*> CMiniMap::m_pEnemyBucket;
int CMiniMap::m_StaticEnemyNum = ENEMY_MAXNUM;

//◇-----------------------------------◇
//CMiniMapのコンストラクタ
//◇-----------------------------------◇
CMiniMap::CMiniMap(int nPriority) : CScene2D(nPriority)
{
	m_StaticEnemyNum = ENEMY_MAXNUM;
}

//◇-----------------------------------◇
//CMiniMapのデストラクタ
//◇-----------------------------------◇
CMiniMap::~CMiniMap()
{

}

//◇-----------------------------------◇
//CMiniMapの初期化処理
//◇-----------------------------------◇
HRESULT CMiniMap::Init(void)
{
	m_MiniMapSize = D3DXVECTOR3(200.0f,200.0f,0.0f);
	
	float MiniMapAdjustment = 30.0f;


	float NumTexSizeX = 130.0f;
	float NumTexSizeY = 80.0f;
	CScene2D::Create(100,"./data/TEXTURE/Game/UI/EnemyNumTex02.png",D3DXVECTOR3(NumTexSizeX/2 + 20.0f,NumTexSizeY/2 + 20.0f,0.0f),D3DXVECTOR3(NumTexSizeX,NumTexSizeY,0.0f));



	float NumCountSizeX = 50.0f;
	float NumCountSizeY = 80.0f;
	
	m_pScorePointer = CScore::Create("./data/TEXTURE/Game/UI/text000.png",2,NumTexSizeX + 30.0f + NumCountSizeX * 2,
																			20.0f,
																			NumCountSizeX,NumCountSizeY,ENEMY_MAXNUM);


	m_MiniMapPos.x = -MiniMapAdjustment + SCREEN_WIDTH - m_MiniMapSize.x / 2;
	m_MiniMapPos.y = +MiniMapAdjustment + m_MiniMapSize.y / 2;

	CScene2D::Create(70,"./data/TEXTURE/Game/UI/MiniMap007.png",m_MiniMapPos,m_MiniMapSize);
	m_pPlayerTex = CScene2D::Create(70,"./data/TEXTURE/Game/UI/PrayerIcon001.png",m_MiniMapPos,D3DXVECTOR3(80.0f,80.0f,0.0f));

	for(int i = 0;i < ENEMYICON_MAX;i++)
		m_pEnemyIcon[i] = CEnemyIcon::Create("./data/TEXTURE/Game/UI/EnemyIcon002.png",D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(40.0f,40.0f,0.0f));

	return S_OK;
}

//◇-----------------------------------◇
//CMiniMapの終了処理
//◇-----------------------------------◇
void CMiniMap::Uninit(void)
{
	for(int i = 0,Num = m_pEnemyBucket.size();i < Num;i++)
		m_pEnemyBucket.pop_back();
}

//◇-----------------------------------◇
//CMiniMapの更新処理
//◇-----------------------------------◇
void CMiniMap::Update(void)
{
	m_pScorePointer->ResetScore(m_StaticEnemyNum);


	D3DXVECTOR3 PIconPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 PlayerPos;

	CScene *pPlayer = NULL;
	CScene::SearchLinkList(&pPlayer,CTYPE_PLAYERMODEL);

	if(pPlayer != NULL)
	{
		PlayerPos = pPlayer->GetPosition();

		PIconPos.x = m_MiniMapPos.x + m_MiniMapSize.x / 2 * (PlayerPos.x / STAGE_LENGTH_X);
		PIconPos.y = m_MiniMapPos.y - m_MiniMapSize.y / 2 * (PlayerPos.z / STAGE_LENGTH_Z);
		
		D3DXVECTOR3 PlayerRot = pPlayer->GetRotation();
		m_pPlayerTex->SetRotation(D3DXVECTOR3(PlayerRot.x,-PlayerRot.y,PlayerRot.z));
		m_pPlayerTex->SetPosition_Re(PIconPos);
	}

	for(unsigned int i = 0;i < ENEMYICON_MAX;i++)
	{
		if(i < m_pEnemyBucket.size())
		{
			m_pEnemyIcon[i]->SetDrawJudge(true);

			D3DXVECTOR3 EnemyPos = m_pEnemyBucket[i]->GetPosition();
			D3DXVECTOR3 EIconPos;

			EIconPos.x = m_MiniMapPos.x + m_MiniMapSize.x / 2 * (EnemyPos.x / STAGE_LENGTH_X);
			EIconPos.y = m_MiniMapPos.y - m_MiniMapSize.y / 2 * (EnemyPos.z / STAGE_LENGTH_Z);
			EIconPos.z = 0.0f;

			m_pEnemyIcon[i]->SetPosition_Re(EIconPos);
		}
		else
		{
			m_pEnemyIcon[i]->SetDrawJudge(false);
		}
	}

}

//◇-----------------------------------◇
//CMiniMapの描画処理
//◇-----------------------------------◇
void CMiniMap::Draw(void)
{

}

void CMiniMap::MiniMapEnemySet(CEnemy001 *pEnemy)
{
	m_pEnemyBucket.push_back(pEnemy);
}

void CMiniMap::MiniMapEnemyRemove(CEnemy001 *pEnemy)
{
	m_StaticEnemyNum--;

	auto itr = m_pEnemyBucket.begin();

	for(int i = 0,Num = m_pEnemyBucket.size();i < Num;i++)
	{
		if(m_pEnemyBucket[i] == pEnemy)
		{
			m_pEnemyBucket.erase(itr);       //  3番目の要素（9）を削除
			break;
		}
		else
		{
			++itr;
		}
	}
}


CMiniMap *CMiniMap::Create()
{
	CMiniMap *pMiniMap;
	pMiniMap = new CMiniMap;

	pMiniMap->Init();

	return pMiniMap;

}
