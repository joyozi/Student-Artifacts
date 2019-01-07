//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternMelee�̃t�@�C��[CPlayerMotionPatternMelee.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
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

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CPlayerMotionPatternMelee�̃R���X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternMelee::CPlayerMotionPatternMelee(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_SWORDACCEL);

	m_AccessTimeCnt = 0;
}

//��-----------------------------------��
//CPlayerMotionPatternMelee�̃f�X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternMelee::~CPlayerMotionPatternMelee()
{

}

//��-----------------------------------��
//CPlayerMotionPatternMelee�̍X�V����
//��-----------------------------------��
void CPlayerMotionPatternMelee::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();
	D3DXVECTOR3 TargetPos;

	//����������
	pPlayer->SetPlayerSpeed(D3DXVECTOR3(0.0f,0.0f,0.0f));

	//�p�x�̃Z�b�g
	D3DXVECTOR3 BasicRot = CItemList::VecAngle_3D_D3DX(CManager::GetCameraPointer()->GetCameraR() - pPlayer->GetPosition());
	pPlayer->SetRotation(D3DXVECTOR3(BasicRot.x,BasicRot.y + D3DX_PI,0.0f));

	//�����߂��ɓG�����Ȃ������ꍇ
	if(pPlayer->GetTargetEnemyPointer() != NULL)
	{
		TargetPos = pPlayer->GetTargetEnemyPointer()->GetPosition();
	}
	else
	{
		TargetPos = CManager::GetCameraPointer()->GetCameraR();
	}


	//�G�Ǝ����̋������v�Z
	D3DXVECTOR3 D3DX_Length = PlayerPos - TargetPos;
	D3DXVec3Normalize(&D3DX_Length,&D3DX_Length);
	float fLength = CItemList::GetLength(PlayerPos,TargetPos);
	
	//��������������������A�Ώۂ̓G�����Ȃ������肵���炻�̕ӂőf�U�������
	if(fLength <= 10000.0f && pPlayer->GetTargetEnemyPointer() != NULL)
	{
		pModelMotion->SetActCommand(PMOVE_SWORDACCEL);

		//�߂��ɗ�����ڋߍU��
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
