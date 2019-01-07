//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternSwordAttackのファイル[CPlayerMotionPatternSwordAttack.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CPlayerMotionPatternSwordAttack.h"
#include "CPlayerMotionPatternSwordAttack_2nd.h"
#include "CPlayerMotionPatternNormal.h"
#include "CCharaMove.h"
#include "input.h"
#include "CPlayerModel.h"
#include "CManager.h"
#include "CCamera.h"
#include "joystick.h"
#include "CItemList.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CPlayerMotionPatternSwordAttackのコンストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternSwordAttack::CPlayerMotionPatternSwordAttack(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_SWORDATTACK);

	m_2ndSwordJudge = false;
	m_StartInfoJudge = false;
}

//◇-----------------------------------◇
//CPlayerMotionPatternSwordAttackのデストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternSwordAttack::~CPlayerMotionPatternSwordAttack()
{

}

//◇-----------------------------------◇
//CPlayerMotionPatternSwordAttackの更新処理
//◇-----------------------------------◇
void CPlayerMotionPatternSwordAttack::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	//一回だけこの処理をしたい
	if(pModelMotion->GetNowMotionNum() == 2 && m_StartInfoJudge == false)
	{
		pPlayer->SetCollisionHitNum(3);
		pPlayer->SetOrbitDrawStartJudge(true);

		PlaySound(SOUND_LABEL_Sword1st);
		
		m_StartInfoJudge = true;
	}

	if(CInput::GetKeyboardTrigger(DIK_K))
		m_2ndSwordJudge = true;

	//モーションが終わったら
	if(pModelMotion->GetMotionEndJudge())
	{
		//終わる前にYが再度押されていたら袈裟懸けへ。falseならノーマルへ
		if(m_2ndSwordJudge)
		{
			pPlayer->SetCollisionHitNum(2);
			pPlayer->MotionPatternChange(new CPlayerMotionPatternSwordAttack_2nd(pModelMotion));
		}
		else
		{
			pPlayer->SetOrbitDrawStartJudge(false);
			pPlayer->SetCollisionHitNum(2);
			pPlayer->MotionPatternChange(new CPlayerMotionPatternNormal(pModelMotion));
		}
	}
	

}
