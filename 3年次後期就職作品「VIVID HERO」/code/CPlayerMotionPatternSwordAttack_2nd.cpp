//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternSwordAttack_2ndのファイル[CPlayerMotionPatternSwordAttack_2nd.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
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
static bool soundJudge = false;


//◇-----------------------------------◇
//CPlayerMotionPatternSwordAttack_2ndのコンストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternSwordAttack_2nd::CPlayerMotionPatternSwordAttack_2nd(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_SWORDATTACK_2ND);

	soundJudge = false;
}

//◇-----------------------------------◇
//CPlayerMotionPatternSwordAttack_2ndのデストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternSwordAttack_2nd::~CPlayerMotionPatternSwordAttack_2nd()
{

}

//◇-----------------------------------◇
//CPlayerMotionPatternSwordAttack_2ndの更新処理
//◇-----------------------------------◇
void CPlayerMotionPatternSwordAttack_2nd::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	pPlayer->SetCollisionHitNum(3);
	pPlayer->SetOrbitDrawStartJudge(true);

	if(soundJudge == false && pModelMotion->GetNowMotionNum() == 2)
	{
		soundJudge = true;
		PlaySound(SOUND_LABEL_Sword2nd);

	}

	//モーションが終わったら
	if(pModelMotion->GetMotionEndJudge())
	{
		pPlayer->SetOrbitDrawStartJudge(false);
		pPlayer->SetCollisionHitNum(2);
		pPlayer->MotionPatternChange(new CPlayerMotionPatternNormal(pModelMotion));
	}
}
