//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternNormalのファイル[CPlayerMotionPatternNormal.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CPlayerMotionPatternNormal.h"
#include "CPlayerMotionPatternShot.h"
#include "CPlayerMotionPatternDash.h"
#include "CPlayerMotionPatternMissile.h"
#include "CPlayerMotionPatternMelee.h"
#include "CPlayerMotionPatternDamaged.h"
#include "CPlayerMotionPatternRapidUp.h"
#include "CPlayerMotionPatternRapidDown.h"

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
//CPlayerMotionPatternNormalのコンストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternNormal::CPlayerMotionPatternNormal()
{
	m_DowblePushCntL = 0;
	m_DowblePushCntR = 0;

	m_DowblePushJudgeL = false;
	m_DowblePushJudgeR = false;
}

//◇-----------------------------------◇
//CPlayerMotionPatternNormalのコンストラクタ 引数付
//◇-----------------------------------◇
CPlayerMotionPatternNormal::CPlayerMotionPatternNormal(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_NUTORAL);

	m_DowblePushCntL = 0;
	m_DowblePushCntR = 0;

	m_DowblePushJudgeL = false;
	m_DowblePushJudgeR = false;
}

//◇-----------------------------------◇
//CPlayerMotionPatternNormalのデストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternNormal::~CPlayerMotionPatternNormal()
{

}

//◇-----------------------------------◇
//CPlayerMotionPatternNormalの更新処理
//◇-----------------------------------◇
void CPlayerMotionPatternNormal::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	CCharaMove::CharaMoveRobo(pPlayer,CManager::GetCameraPointer()->GetCameraRotationY(),90.0f);

	if(CInput::GetKeyboardPress(DIK_J))
	{
		pPlayer->MotionPatternChange(new CPlayerMotionPatternShot(pModelMotion));
		return;
	}
	
	else if(CInput::GetKeyboardPress(DIK_L))
	{
		pPlayer->MotionPatternChange(new CPlayerMotionPatternMissile(pModelMotion));
		return;
	}
	else if(CInput::GetKeyboardPress(DIK_K))
	{
		pPlayer->MotionPatternChange(new CPlayerMotionPatternMelee(pModelMotion));
		return;
	}
	else if(CInput::GetKeyboardTrigger(DIK_Q))
	{
		if(m_DowblePushJudgeL == false)
		{
			m_DowblePushJudgeL = true;
			m_DowblePushCntL = 0;
		}
	}
	else if(CInput::GetKeyboardTrigger(DIK_E))
	{
		if(m_DowblePushJudgeR == false)
		{
			m_DowblePushJudgeR = true;
			m_DowblePushCntR = 0;
		}
	}

	if(m_DowblePushJudgeL)
	{
		//制限時間内に2度押し && 次フレーム以降だったら急上昇
		if(CInput::GetKeyboardTrigger(DIK_Q) && m_DowblePushCntL > 0)
		{
			pPlayer->MotionPatternChange(new CPlayerMotionPatternRapidDown(pModelMotion));
			return;
		}

		m_DowblePushCntL++;

		if(m_DowblePushCntL >= 60)
		{
			m_DowblePushJudgeL = false;
		}
	}

	if(m_DowblePushJudgeR)
	{
		//制限時間内に2度押し && 次フレーム以降だったら急上昇
		if(CInput::GetKeyboardTrigger(DIK_E) && m_DowblePushCntR > 0)
		{
			pPlayer->MotionPatternChange(new CPlayerMotionPatternRapidUp(pModelMotion));
			return;
		}

		m_DowblePushCntR++;

		if(m_DowblePushCntR >= 60)
		{
			m_DowblePushJudgeR = false;
		}
	}
}