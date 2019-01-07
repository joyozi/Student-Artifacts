//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternRapidDown�̃t�@�C��[CPlayerMotionPatternRapidDown.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CPlayerMotionPatternRapidDown.h"
#include "CPlayerMotionPatternNormal.h"

#include "CPlayerModel.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CPlayerMotionPatternRapidDown�̃R���X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternRapidDown::CPlayerMotionPatternRapidDown(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_RAPIDDOWN);
	m_MoveDownCnt = 0;
}

//��-----------------------------------��
//CPlayerMotionPatternRapidDown�̃f�X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternRapidDown::~CPlayerMotionPatternRapidDown()
{

}

//��-----------------------------------��
//CPlayerMotionPatternRapidDown�̍X�V����
//��-----------------------------------��
void CPlayerMotionPatternRapidDown::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	pPlayer->SetPosition(pPlayer->GetPosition() + D3DXVECTOR3(0.0f,-100.0f,0.0f));
	pModelMotion->SetActCommand(PMOVE_RAPIDDOWN);

	m_MoveDownCnt++;

	//�������̓��[�V������������Ȃ��̂Ń^�C���Ōv�Z���Ă�
	if(m_MoveDownCnt >= 15)
	{
		pPlayer->MotionPatternChange(new CPlayerMotionPatternNormal(pModelMotion));
		pPlayer->SetPlayerSpeed(D3DXVECTOR3(0.0f,-30.0f,0.0f));
	}
	
}