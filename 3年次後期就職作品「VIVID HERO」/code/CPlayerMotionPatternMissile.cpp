//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternMissileのファイル[CPlayerMotionPatternMissile.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CPlayerMotionPatternMissile.h"
#include "CPlayerMotionPatternNormal.h"

#include "CCharaMove.h"
#include "input.h"
#include "CPlayerModel.h"
#include "CManager.h"
#include "CCamera.h"
#include "joystick.h"
#include "CBulletHoming.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CPlayerMotionPatternMissileのコンストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternMissile::CPlayerMotionPatternMissile(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_HOMINGMISSILE);
	m_ShotMusicJudge = false;
}

//◇-----------------------------------◇
//CPlayerMotionPatternMissileのデストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternMissile::~CPlayerMotionPatternMissile()
{

}

//◇-----------------------------------◇
//CPlayerMotionPatternMissileの更新処理
//◇-----------------------------------◇
void CPlayerMotionPatternMissile::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	D3DXVECTOR3 BasicRot = CItemList::VecAngle_3D_D3DX(CManager::GetCameraPointer()->GetCameraR() - pPlayer->GetPosition());

	//プレイヤ角度のセット
	D3DXVECTOR3 MoveRot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	MoveRot = D3DXVECTOR3(0.0f,BasicRot.y + D3DX_PI,0.0f);
	pPlayer->SetRotation(MoveRot);

	//プレイヤの慣性移動のセット
	D3DXVECTOR3 MovePos = CItemList::Vec3lerp(pPlayer->GetPlayerSpeed(),D3DXVECTOR3(0.0f,0.0f,0.0f),0.1f);
	
	pPlayer->SetPlayerSpeed(MovePos);
	pPlayer->SetPosition(pPlayer->GetPosition()+ 
							D3DXVECTOR3(MovePos.x,
							MovePos.y,
							MovePos.z));



	if(pModelMotion->GetNowMotionNum() == 1 && m_ShotMusicJudge == false)
	{
		PlaySound(SOUND_LABEL_Missle_Shot);
		m_ShotMusicJudge = true;
	}

	if(pModelMotion->GetNowMotionNum() == 2)
	{
		if(pPlayer->GetTargetEnemyPointer() !=NULL)
		{
			CBulletHoming::Create(pPlayer->GetPosition(), pPlayer->GetTargetEnemyPointer()->GetCollisionCenterPos(0));
			CBulletHoming::Create(pPlayer->GetPosition(), pPlayer->GetTargetEnemyPointer()->GetCollisionCenterPos(0));
		}
		else
		{
			CBulletHoming::Create(pPlayer->GetPosition(),CManager::GetCameraPointer()->GetCameraR() );
		}
	}

	//線形補間の段階に入ってたとしたらやめる
	if(pModelMotion->GetMotionEndJudge())
	{
		pPlayer->MotionPatternChange(new CPlayerMotionPatternNormal(pModelMotion));
	}
}
