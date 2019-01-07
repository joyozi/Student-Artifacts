//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternDamaged�̃t�@�C��[CPlayerMotionPatternDamaged.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CPlayerMotionPatternDamaged.h"
#include "CPlayerMotionPatternNormal.h"
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
//CPlayerMotionPatternDamaged�̃R���X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternDamaged::CPlayerMotionPatternDamaged(CSceneModelMotion *pModelMotion)
{
	m_DamagedTimeCnt = 0;

	pModelMotion->SetActCommand(PMOVE_DAMAGE);
}

//��-----------------------------------��
//CPlayerMotionPatternDamaged�̃f�X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternDamaged::~CPlayerMotionPatternDamaged()
{

}

//��-----------------------------------��
//CPlayerMotionPatternDamaged�̍X�V����
//��-----------------------------------��
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
