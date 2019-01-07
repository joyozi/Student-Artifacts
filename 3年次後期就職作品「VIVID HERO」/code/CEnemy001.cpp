//◇-------------------------------------------------------------------------◇
//
//	File:CEnemy001のファイル[CEnemy001.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CEnemy001.h"
#include "CDegeneracyAnimation.h"
#include "input.h"
#include "CItemList.h"
#include "CBullet000.h"
#include "CScene3D.h"
#include "CEnemyPattern.h"
#include "CBulletPattern.h"
#include "CPhaseGame.h"
#include "CExplosion000.h"
#include "CBulletPatternEnemy001.h"
#include "CMiniMap.h"
#include "CParticleSystem.h"
#include "sound.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CEnemy001のコンストラクタ
//◇-----------------------------------◇
CEnemy001::CEnemy001(int nPriority) : CSceneX(nPriority)
{
	m_Type = CTYPE_ENEMY;

	m_pBulletPattern = NULL;
	m_pEnemyPattern = NULL;

	m_Life = 8;
	DeathCnt = 0;

	m_Scl *= 15.0f;

	SetCollisionHitNum(1);

	CMiniMap::MiniMapEnemySet(this);
}

//◇-----------------------------------◇
//CEnemy001のデストラクタ
//◇-----------------------------------◇
CEnemy001::~CEnemy001()
{
	CMiniMap::MiniMapEnemyRemove(this);
}

//◇----------------------------------◇
//CEnemy001の終了処理
//◇----------------------------------◇
void CEnemy001::Uninit(void)
{
	Release();

	SAFE_DELETE(m_pBulletPattern);
	SAFE_DELETE(m_pEnemyPattern);
}

//◇-----------------------------------◇
//CEnemy001の更新処理
//◇-----------------------------------◇
void CEnemy001::Update(void)
{
	if(m_Life > 0)
	{
		m_pBulletPattern->Update_Enemy001(this);
		m_pEnemyPattern->Update(this);

		CScene *pPlayer = NULL;
		CScene::SearchLinkList(&pPlayer,CTYPE_PLAYERMODEL);

		if(pPlayer != NULL)
		{
			//向きのセット
			D3DXVECTOR3 kariRot = CItemList::VecAngle_3D_D3DX(pPlayer->GetPosition() - m_Pos) ;
			m_Rot = D3DXVECTOR3(-kariRot.x,kariRot.y,0.0f);
		}
	}
	else
	{
		m_Rot.y += D3DX_PI / 45.0f;

		if(DeathCnt % 30 == 0)
		{
			float a = 5.0f;

//			CPhaseGame::GetExplosionPointer(EX_05_NORMALEX)->ExplosionPlayerBulletHit(m_Pos + D3DXVECTOR3((float)DeathCnt * a,(float)DeathCnt * a,(float)DeathCnt * a));
//			CPhaseGame::GetExplosionPointer(EX_05_NORMALEX)->ExplosionPlayerBulletHit(m_Pos + D3DXVECTOR3((float)DeathCnt * a,(float)DeathCnt * a,(float)DeathCnt * a));
//			CPhaseGame::GetExplosionPointer(EX_05_NORMALEX)->ExplosionPlayerBulletHit(m_Pos + D3DXVECTOR3((float)DeathCnt * a,(float)DeathCnt * a,(float)DeathCnt * a));
//			CPhaseGame::GetExplosionPointer(EX_05_NORMALEX)->ExplosionPlayerBulletHit(m_Pos + D3DXVECTOR3((float)DeathCnt * a,(float)DeathCnt * a,(float)DeathCnt * a));
//
//			CPhaseGame::GetExplosionPointer(EX_05_NORMALEX)->ExplosionPlayerBulletHit(m_Pos + D3DXVECTOR3(-((float)DeathCnt * a),-((float)DeathCnt * a),-((float)DeathCnt * a)));
//			CPhaseGame::GetExplosionPointer(EX_05_NORMALEX)->ExplosionPlayerBulletHit(m_Pos + D3DXVECTOR3(-((float)DeathCnt * a),-((float)DeathCnt * a),-((float)DeathCnt * a)));
//			CPhaseGame::GetExplosionPointer(EX_05_NORMALEX)->ExplosionPlayerBulletHit(m_Pos + D3DXVECTOR3(-((float)DeathCnt * a),-((float)DeathCnt * a),-((float)DeathCnt * a)));
//			CPhaseGame::GetExplosionPointer(EX_05_NORMALEX)->ExplosionPlayerBulletHit(m_Pos + D3DXVECTOR3(-((float)DeathCnt * a),-((float)DeathCnt * a),-((float)DeathCnt * a)));
			
			CPhaseGame::GetExplosionPointer(EX_05_NORMALEX)->ExplosionPlayerBulletHit(m_Pos + D3DXVECTOR3(0.0f,(float)DeathCnt * a,0.0f));
			CPhaseGame::GetExplosionPointer(EX_05_NORMALEX)->ExplosionPlayerBulletHit(m_Pos + D3DXVECTOR3(0.0f,(float)DeathCnt * a,0.0f));
			CPhaseGame::GetExplosionPointer(EX_05_NORMALEX)->ExplosionPlayerBulletHit(m_Pos + D3DXVECTOR3(0.0f,(float)DeathCnt * a,0.0f));
			CPhaseGame::GetExplosionPointer(EX_05_NORMALEX)->ExplosionPlayerBulletHit(m_Pos + D3DXVECTOR3(0.0f,(float)DeathCnt * a,0.0f));

		}
		if(DeathCnt == 1)
		{
			PlaySound(SOUND_LABEL_cannon1);
		}
		if(DeathCnt == 60)
		{
			Uninit();
		}

		DeathCnt++;
	}

	MatrixUpdate();
}

float CEnemy001::GetCollisionRadius(int Num)
{
	return 15.0f * m_Scl.x;
}

void CEnemy001::CollisionAction(CLASS_TYPE Type,int Num)
{
	if(Type == CTYPE_PLAYERMODEL && Num == 2)
	{
		m_Life -= 5;
	}

	if(Type == CTYPE_PLAYERMODEL)		//他のモデル本体だと何も起きない
	{

	}
	else
	{
		m_Life--;
	}
}

//銃口の数
int CEnemy001::GetMuzzleNum(void)
{
	return 3;
}
//銃口の位置
D3DXVECTOR3 CEnemy001::GetMuzzlePos(int Num)
{
	D3DXVECTOR3 Muzzle[3];

	Muzzle[0] = D3DXVECTOR3(-8.0f,5.0f,27.0f);
	Muzzle[1] = D3DXVECTOR3(8.0f,5.0f,27.0f);
	Muzzle[2] = D3DXVECTOR3(0.0f,-5.0f,27.0f);

	D3DXVec3TransformCoord(&Muzzle[Num],&Muzzle[Num],&m_mtxWorld);

	return Muzzle[Num];
}

//◇----------------------------------◇
//CEnemy001のクリエイト(引数付)
//◇----------------------------------◇
CEnemy001 *CEnemy001::Create(LPCTSTR ModelTxtName,D3DXVECTOR3 Pos,CBulletPattern *pBullet,CEnemyPattern *pEnemy)
{
	CEnemy001 *pEnemy000;
	pEnemy000 = new CEnemy001;

	pEnemy000->m_XfileName = ModelTxtName;
	pEnemy000->m_Pos = Pos;

	pEnemy000->m_pBulletPattern = pBullet;
	pEnemy000->m_pEnemyPattern = pEnemy;

	pEnemy000->Init();

	return pEnemy000;
}


