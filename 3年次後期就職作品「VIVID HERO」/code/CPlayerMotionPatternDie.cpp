//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternDieのファイル[CPlayerMotionPatternDie.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CPlayerMotionPatternDie.h"

#include "CPlayerModel.h"
#include "CManager.h"
#include "CItemList.h"
#include "CPhaseGame.h"
#include "CExplosion000.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CPlayerMotionPatternDieのコンストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternDie::CPlayerMotionPatternDie(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_DAMAGE);
}

//◇-----------------------------------◇
//CPlayerMotionPatternDieのデストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternDie::~CPlayerMotionPatternDie()
{

}

//◇-----------------------------------◇
//CPlayerMotionPatternDieの更新処理
//◇-----------------------------------◇
void CPlayerMotionPatternDie::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_DAMAGE);

	//たまに煙をプスプスさせる
	if(rand()%10 == 0)
	{
		D3DXVECTOR3 SmogAngle;
		D3DXVECTOR3 SmogPos;
		float Radius = (float)(rand()%300);

		SmogAngle.x = CItemList::ConvRadian((float)(rand()%360));
		SmogAngle.y = CItemList::ConvRadian((float)(rand()%360));

		SmogPos.x = -(Radius) * cosf(SmogAngle.x) * cosf(SmogAngle.y);
		SmogPos.y = (Radius) * sinf(SmogAngle.x);
		SmogPos.z = (Radius) * cosf(SmogAngle.x) * sinf(SmogAngle.y);



		CPhaseGame::GetExplosionPointer(EX_05_NORMALEX)->ExplosionSet1Set(pPlayer->GetPosition() + SmogPos,200.0f,200.0f);
	}
}





