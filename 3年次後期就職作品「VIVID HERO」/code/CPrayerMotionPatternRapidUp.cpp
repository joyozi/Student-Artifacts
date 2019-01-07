//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternRapidUp�̃t�@�C��[CPlayerMotionPatternRapidUp.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CPlayerMotionPatternRapidUp.h"
#include "CPlayerMotionPatternNormal.h"

#include "CPlayerModel.h"
#include "joystick.h"
#include "CParticleEngine.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CPlayerMotionPatternRapidUp�̃R���X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternRapidUp::CPlayerMotionPatternRapidUp(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_RAPIDUP);
	m_MoveUpCnt = 0;
}

//��-----------------------------------��
//CPlayerMotionPatternRapidUp�̃f�X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternRapidUp::~CPlayerMotionPatternRapidUp()
{

}

//��-----------------------------------��
//CPlayerMotionPatternRapidUp�̍X�V����
//��-----------------------------------��
void CPlayerMotionPatternRapidUp::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	pPlayer->SetPosition(pPlayer->GetPosition() + D3DXVECTOR3(0.0f,100.0f,0.0f));

	m_MoveUpCnt++;

	//�������̓��[�V�����̃t���[���Ōv�Z���Ă�B���ԕύX��txt��
	if(pModelMotion->GetMotionEndJudge())
	{
		pPlayer->MotionPatternChange(new CPlayerMotionPatternNormal(pModelMotion));
		pPlayer->SetPlayerSpeed(D3DXVECTOR3(0.0f,30.0f,0.0f));
	}
}