//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternMeleeのファイル[CPlayerMotionPatternMelee.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CPlayerMotionPatternMelee.h"
#include "CPlayerMotionPatternSwordAttack.h"
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
//CPlayerMotionPatternMeleeのコンストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternMelee::CPlayerMotionPatternMelee(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_SWORDACCEL);

	m_AccessTimeCnt = 0;
}

//◇-----------------------------------◇
//CPlayerMotionPatternMeleeのデストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternMelee::~CPlayerMotionPatternMelee()
{

}

//◇-----------------------------------◇
//CPlayerMotionPatternMeleeの更新処理
//◇-----------------------------------◇
void CPlayerMotionPatternMelee::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();
	D3DXVECTOR3 TargetPos;

	//慣性を消す
	pPlayer->SetPlayerSpeed(D3DXVECTOR3(0.0f,0.0f,0.0f));

	//角度のセット
	D3DXVECTOR3 BasicRot = CItemList::VecAngle_3D_D3DX(CManager::GetCameraPointer()->GetCameraR() - pPlayer->GetPosition());
	pPlayer->SetRotation(D3DXVECTOR3(BasicRot.x,BasicRot.y + D3DX_PI,0.0f));

	//もし近くに敵がいなかった場合
	if(pPlayer->GetTargetEnemyPointer() != NULL)
	{
		TargetPos = pPlayer->GetTargetEnemyPointer()->GetPosition();
	}
	else
	{
		TargetPos = CManager::GetCameraPointer()->GetCameraR();
	}


	//敵と自分の距離を計算
	D3DXVECTOR3 D3DX_Length = PlayerPos - TargetPos;
	D3DXVec3Normalize(&D3DX_Length,&D3DX_Length);
	float fLength = CItemList::GetLength(PlayerPos,TargetPos);
	
	//もし距離が長かったり、対象の敵がいなかったりしたらその辺で素振りをする
	if(fLength <= 10000.0f && pPlayer->GetTargetEnemyPointer() != NULL)
	{
		pModelMotion->SetActCommand(PMOVE_SWORDACCEL);

		//近くに来たら接近攻撃
		if(fLength <= 600.0f)
		{
			pPlayer->MotionPatternChange(new CPlayerMotionPatternSwordAttack(pModelMotion));
		}
		else
		{
			pPlayer->SetPosition(PlayerPos - D3DX_Length * 150.0f);
		}
	}
	else
	{
		pPlayer->MotionPatternChange(new CPlayerMotionPatternSwordAttack(pModelMotion));
	}
}
