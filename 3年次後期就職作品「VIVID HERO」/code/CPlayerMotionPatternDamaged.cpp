//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternDamagedのファイル[CPlayerMotionPatternDamaged.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CPlayerMotionPatternDamaged.h"
#include "CPlayerMotionPatternNormal.h"
#include "CCharaMove.h"
#include "input.h"
#include "CPlayerModel.h"
#include "CManager.h"
#include "CCamera.h"
#include "joystick.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CPlayerMotionPatternDamagedのコンストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternDamaged::CPlayerMotionPatternDamaged(CSceneModelMotion *pModelMotion)
{
	m_DamagedTimeCnt = 0;

	pModelMotion->SetActCommand(PMOVE_DAMAGE);
}

//◇-----------------------------------◇
//CPlayerMotionPatternDamagedのデストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternDamaged::~CPlayerMotionPatternDamaged()
{

}

//◇-----------------------------------◇
//CPlayerMotionPatternDamagedの更新処理
//◇-----------------------------------◇
void CPlayerMotionPatternDamaged::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	int DamagedTime = 60;

	if(m_DamagedTimeCnt < DamagedTime)
	{
		pModelMotion->SetActCommand(PMOVE_DAMAGE);
		m_DamagedTimeCnt++;
	}
	else
	{
		pPlayer->MotionPatternChange(new CPlayerMotionPatternNormal(pModelMotion));
	}
}
