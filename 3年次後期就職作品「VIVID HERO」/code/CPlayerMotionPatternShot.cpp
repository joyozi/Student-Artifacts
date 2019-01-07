//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternShotのファイル[CPlayerMotionPatternShot.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CPlayerMotionPatternShot.h"
#include "CPlayerMotionPatternNormal.h"

#include "CCharaMove.h"
#include "input.h"
#include "CPlayerModel.h"
#include "CManager.h"
#include "CCamera.h"
#include "CItemList.h"
#include "joystick.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CPlayerMotionPatternShotのコンストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternShot::CPlayerMotionPatternShot(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_SHOT);

	m_SaveCameraMovedPos = 0.0f;
	m_NowCameraMovePos = 0.0f;

	m_GoMovePos = 0.0f;

	m_CameraMoveCnt = CAMERA_MOVECNT;

	PlaySound(SOUND_LABEL_GunKamae);

}

//◇-----------------------------------◇
//CPlayerMotionPatternShotのデストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternShot::~CPlayerMotionPatternShot()
{

}

//◇-----------------------------------◇
//CPlayerMotionPatternShotの更新処理
//◇-----------------------------------◇
void CPlayerMotionPatternShot::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	CCharaMove::CharaMoveRobo(pPlayer,CManager::GetCameraPointer()->GetCameraRotationY(),70.0f);

	D3DXVECTOR3 BasicRot = CItemList::VecAngle_3D_D3DX(CManager::GetCameraPointer()->GetCameraR() - pPlayer->GetPosition());
	pPlayer->SetRotation(D3DXVECTOR3(BasicRot.x,BasicRot.y + D3DX_PI,0.0f));

	if(pModelMotion->GetNowMotionNum() != -1)
	{
		pPlayer->SetBulletTrigger(true);
	}


	if(m_CameraMoveCnt < CAMERA_MOVECNT)
	{
		m_NowCameraMovePos += CItemList::lerp(m_SaveCameraMovedPos,m_GoMovePos,1.0f / CAMERA_MOVECNT) - m_SaveCameraMovedPos;

		m_CameraMoveCnt++;
	}

	D3DXVECTOR3 CameraAjdust = D3DXVECTOR3(0.0f,0.0f,0.0f);

	CameraAjdust.x = m_NowCameraMovePos * cosf(CManager::GetCameraPointer()->GetCameraRotationY());
	CameraAjdust.z = -m_NowCameraMovePos * sinf(CManager::GetCameraPointer()->GetCameraRotationY());

	CManager::GetCameraPointer()->SetCameraResultAdjustment(CameraAjdust);

	//左右移動時のモーション

	if(pModelMotion->GetMotionEndJudge())
	{
		if(CInput::GetKeyboardPress(DIK_D))
		{
			if(pModelMotion->GetActCommand() != PMOVE_SHOTMOVE_R)
			{
				m_GoMovePos = -150.0f;
				m_SaveCameraMovedPos = m_NowCameraMovePos;
				m_CameraMoveCnt = 0;
			}

			pModelMotion->SetActCommand(PMOVE_SHOTMOVE_R);
		}
		else if(CInput::GetKeyboardPress(DIK_A))
		{
			if(pModelMotion->GetActCommand() != PMOVE_SHOTMOVE_L)
			{
				m_GoMovePos = 150.0f;
				m_SaveCameraMovedPos = m_NowCameraMovePos;
				m_CameraMoveCnt = 0;
			}

			pModelMotion->SetActCommand(PMOVE_SHOTMOVE_L);
		}
		else
		{
			if(pModelMotion->GetActCommand() != PMOVE_SHOT)
				m_GoMovePos = 0.0f;
				m_SaveCameraMovedPos = m_NowCameraMovePos;
				m_CameraMoveCnt = 0;

			pModelMotion->SetActCommand(PMOVE_SHOT);
		}
	}

	if(CInput::GetKeyboardPress(DIK_J) == false)
	{
		pPlayer->SetBulletTrigger(false);

		CManager::GetCameraPointer()->SetCameraResultAdjustment(D3DXVECTOR3(0.0f,0.0f,0.0f));

		pPlayer->MotionPatternChange(new CPlayerMotionPatternNormal(pModelMotion));
	}
}
