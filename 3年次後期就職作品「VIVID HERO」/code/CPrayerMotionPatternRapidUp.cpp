//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternRapidUpのファイル[CPlayerMotionPatternRapidUp.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CPlayerMotionPatternRapidUp.h"
#include "CPlayerMotionPatternNormal.h"

#include "CPlayerModel.h"
#include "joystick.h"
#include "CParticleEngine.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CPlayerMotionPatternRapidUpのコンストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternRapidUp::CPlayerMotionPatternRapidUp(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_RAPIDUP);
	m_MoveUpCnt = 0;
}

//◇-----------------------------------◇
//CPlayerMotionPatternRapidUpのデストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternRapidUp::~CPlayerMotionPatternRapidUp()
{

}

//◇-----------------------------------◇
//CPlayerMotionPatternRapidUpの更新処理
//◇-----------------------------------◇
void CPlayerMotionPatternRapidUp::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	pPlayer->SetPosition(pPlayer->GetPosition() + D3DXVECTOR3(0.0f,100.0f,0.0f));

	m_MoveUpCnt++;

	//こっちはモーションのフレームで計算してる。時間変更はtxtで
	if(pModelMotion->GetMotionEndJudge())
	{
		pPlayer->MotionPatternChange(new CPlayerMotionPatternNormal(pModelMotion));
		pPlayer->SetPlayerSpeed(D3DXVECTOR3(0.0f,30.0f,0.0f));
	}
}