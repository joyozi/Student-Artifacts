//◇-------------------------------------------------------------------------◇
//
//	File:CEnemyBullet000のファイル[CEnemyBullet000.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CEnemyBullet000.h"
#include "CItemList.h"
#include "CExplosion000.h"
#include "CPhaseGame.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CEnemyBullet000のコンストラクタ
//◇-----------------------------------◇
CEnemyBullet000::CEnemyBullet000(int nPriority) : CSceneBillboard(nPriority)
{
	m_Type = CTYPE_ENEMYBULLET000;

	TextureWidth = 30.0f;
	TextureHeight = 30.0f;
	m_TextureName = "./data/TEXTURE/Game/bullet000.png";

	m_Speed = 200.0f;

	SetCollisionHitNum(1);
}

//◇-----------------------------------◇
//CEnemyBullet000のデストラクタ
//◇-----------------------------------◇
CEnemyBullet000::~CEnemyBullet000()
{

}

//◇-----------------------------------◇
//CEnemyBullet000の更新処理
//◇-----------------------------------◇
void CEnemyBullet000::Update(void)
{
	if(m_CollisionHitJudge)
	{
		CPhaseGame::GetExplosionPointer(0)->ExplosionSet3Set(m_Pos);

		Uninit();
	}

	m_Pos += m_ShotVec * m_Speed;
}

//◇-----------------------------------◇
//CEnemyBullet000のあたり判定関数
//◇-----------------------------------◇
float CEnemyBullet000::GetCollisionRadius(int Num)
{
	return 5.0f;
}

void CEnemyBullet000::CollisionAction(CLASS_TYPE Type,int Num)
{
	if(Type == CTYPE_PLAYERMODEL)
		m_CollisionHitJudge = true;
}

//◇-----------------------------------◇
//CEnemyBullet000のクリエイト
//◇-----------------------------------◇
CEnemyBullet000 *CEnemyBullet000::Create(D3DXVECTOR3 ShotPos,D3DXVECTOR3 TargetPos)
{
	CEnemyBullet000 *pBullet000;
	pBullet000 = new CEnemyBullet000;

	pBullet000->m_Pos = ShotPos;
	pBullet000->m_ShotVec = TargetPos - ShotPos;
	D3DXVec3Normalize(&pBullet000->m_ShotVec,&pBullet000->m_ShotVec);

	pBullet000->Init();

	return pBullet000;
}


