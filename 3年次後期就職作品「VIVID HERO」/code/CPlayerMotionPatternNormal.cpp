//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternNormal�̃t�@�C��[CPlayerMotionPatternNormal.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
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

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CPlayerMotionPatternNormal�̃R���X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternNormal::CPlayerMotionPatternNormal()
{
	m_DowblePushCntL = 0;
	m_DowblePushCntR = 0;

	m_DowblePushJudgeL = false;
	m_DowblePushJudgeR = false;
}

//��-----------------------------------��
//CPlayerMotionPatternNormal�̃R���X�g���N�^ �����t
//��-----------------------------------��
CPlayerMotionPatternNormal::CPlayerMotionPatternNormal(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_NUTORAL);

	m_DowblePushCntL = 0;
	m_DowblePushCntR = 0;

	m_DowblePushJudgeL = false;
	m_DowblePushJudgeR = false;
}

//��-----------------------------------��
//CPlayerMotionPatternNormal�̃f�X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternNormal::~CPlayerMotionPatternNormal()
{

}

//��-----------------------------------��
//CPlayerMotionPatternNormal�̍X�V����
//��-----------------------------------��
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
		//�������ԓ���2�x���� && ���t���[���ȍ~��������}�㏸
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
		//�������ԓ���2�x���� && ���t���[���ȍ~��������}�㏸
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