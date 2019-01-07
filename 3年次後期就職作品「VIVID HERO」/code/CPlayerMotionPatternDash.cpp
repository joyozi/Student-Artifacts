//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternDashのファイル[CPlayerMotionPatternDash.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CPlayerMotionPatternDash.h"
#include "CPlayerMotionPatternNormal.h"

#include "CCharaMove.h"
#include "CPlayerModel.h"
#include "CManager.h"
#include "CCamera.h"
#include "joystick.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CPlayerMotionPatternDashのコンストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternDash::CPlayerMotionPatternDash(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_NUTORAL);
}

//◇-----------------------------------◇
//CPlayerMotionPatternDashのデストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternDash::~CPlayerMotionPatternDash()
{

}

//◇-----------------------------------◇
//CPlayerMotionPatternDashの更新処理
//◇-----------------------------------◇
void CPlayerMotionPatternDash::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	CCharaMove::CharaMoveRobo(pPlayer,CManager::GetCameraPointer()->GetCameraRotationY(),120.0f);

	//ニュートラル時に要求されたら
	if(GetJoystickPress(JS_A) == false)
	{
		pPlayer->MotionPatternChange(new CPlayerMotionPatternNormal(pModelMotion));
	}
}





