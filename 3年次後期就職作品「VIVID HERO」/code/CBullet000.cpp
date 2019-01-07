//◇-------------------------------------------------------------------------◇
//
//	File:CBullet000のファイル[CBullet000.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CBullet000.h"
#include "CItemList.h"
#include "CExplosion000.h"
#include "CPhaseGame.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CBullet000のコンストラクタ
//◇-----------------------------------◇
CBullet000::CBullet000(int nPriority) : CSceneBillboard(nPriority)
{
	m_Type = CTYPE_BULLET000;

	TextureWidth = 30.0f;
	TextureHeight = 30.0f;
	m_TextureName = "./data/TEXTURE/Game/shadow000.jpg";

	m_Speed = 50.0f;

	SetCollisionHitNum(1);
}

//◇-----------------------------------◇
//CBullet000のデストラクタ
//◇-----------------------------------◇
CBullet000::~CBullet000()
{

}

//◇-----------------------------------◇
//CBullet000の更新処理
//◇-----------------------------------◇
void CBullet000::Update(void)
{
	if(m_CollisionHitJudge)
	{
		CPhaseGame::GetExplosionPointer(0)->ExplosionSet3Set(m_Pos);

		Uninit();
	}

	m_Pos += m_ShotVec * m_Speed;
}


//◇-----------------------------------◇
//CBullet000のあたり判定関数
//◇-----------------------------------◇
float CBullet000::GetCollisionRadius(int Num)
{
	return 5.0f;
}

void CBullet000::CollisionAction(CLASS_TYPE Type,int Num)
{
	m_CollisionHitJudge = true;
}

//◇-----------------------------------◇
//CBullet000の更新処理
//◇-----------------------------------◇
CBullet000 *CBullet000::Create(D3DXVECTOR3 ShotPos,D3DXVECTOR3 TargetPos)
{
	CBullet000 *pBullet000;
	pBullet000 = new CBullet000;

	pBullet000->m_Pos = ShotPos;
	pBullet000->m_ShotVec = TargetPos - ShotPos;
	D3DXVec3Normalize(&pBullet000->m_ShotVec,&pBullet000->m_ShotVec);

	pBullet000->Init();

	return pBullet000;
}


