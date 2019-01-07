//◇-------------------------------------------------------------------------◇
//
//	File:CEnemyPatternRandamのファイル[CEnemyPatternRandam.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CEnemyPatternRandam.h"
#include "CItemList.h"
#include "CPlayerModel.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CEnemyPatternRandamのコンストラクタ
//◇-----------------------------------◇
CEnemyPatternRandam::CEnemyPatternRandam()
{
	m_Angle.x = CItemList::ConvRadian((float)(rand()%360));
	m_Angle.y = CItemList::ConvRadian((float)(rand()%360));

	m_MoveCntMax = rand()%300 + 120;
	m_MoveCnt = 0;
}

//◇-----------------------------------◇
//CEnemyPatternRandamのデストラクタ
//◇-----------------------------------◇
CEnemyPatternRandam::~CEnemyPatternRandam()
{

}

//◇-----------------------------------◇
//CEnemyPatternRandamの更新処理
//◇-----------------------------------◇
void CEnemyPatternRandam::Update(CScene *pEnemy)
{
	D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);

	Pos = pEnemy->GetPosition();

	float Speed = 6.0f;
	Pos.x += -(Speed) * cosf(m_Angle.x) * cosf(m_Angle.y);
	Pos.y += (Speed) * sinf(m_Angle.x);
	Pos.z += (Speed) * cosf(m_Angle.x) * sinf(m_Angle.y);

	//もしミッション圏外に出たら
	if(Pos.x < -STAGE_LENGTH_X || Pos.x > STAGE_LENGTH_X)	Pos.x = m_OldPos.x;
	if(Pos.y < -STAGE_LENGTH_Y || Pos.y > STAGE_LENGTH_Y)	Pos.y = m_OldPos.y;
	if(Pos.z < -STAGE_LENGTH_Z || Pos.z > STAGE_LENGTH_Z)	Pos.z = m_OldPos.z;

	pEnemy->SetPosition(Pos);



	//一定時間たったら方向転換
	m_MoveCnt++;
	if(m_MoveCnt >= m_MoveCntMax)
	{
		m_Angle.x = CItemList::ConvRadian((float)(rand()%360));
		m_Angle.y = CItemList::ConvRadian((float)(rand()%360));
			
		m_MoveCntMax = rand()%300 + 120;
		m_MoveCnt = 0;
	}

	m_OldPos = Pos;
}
