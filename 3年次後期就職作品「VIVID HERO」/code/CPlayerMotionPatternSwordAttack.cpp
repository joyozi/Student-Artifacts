//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternSwordAttack�̃t�@�C��[CPlayerMotionPatternSwordAttack.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CPlayerMotionPatternSwordAttack.h"
#include "CPlayerMotionPatternSwordAttack_2nd.h"
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
//CPlayerMotionPatternSwordAttack�̃R���X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternSwordAttack::CPlayerMotionPatternSwordAttack(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_SWORDATTACK);

	m_2ndSwordJudge = false;
	m_StartInfoJudge = false;
}

//��-----------------------------------��
//CPlayerMotionPatternSwordAttack�̃f�X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternSwordAttack::~CPlayerMotionPatternSwordAttack()
{

}

//��-----------------------------------��
//CPlayerMotionPatternSwordAttack�̍X�V����
//��-----------------------------------��
void CPlayerMotionPatternSwordAttack::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	//��񂾂����̏�����������
	if(pModelMotion->GetNowMotionNum() == 2 && m_StartInfoJudge == false)
	{
		pPlayer->SetCollisionHitNum(3);
		pPlayer->SetOrbitDrawStartJudge(true);

		PlaySound(SOUND_LABEL_Sword1st);
		
		m_StartInfoJudge = true;
	}

	if(CInput::GetKeyboardTrigger(DIK_K))
		m_2ndSwordJudge = true;

	//���[�V�������I�������
	if(pModelMotion->GetMotionEndJudge())
	{
		//�I���O��Y���ēx������Ă�����U�������ցBfalse�Ȃ�m�[�}����
		if(m_2ndSwordJudge)
		{
			pPlayer->SetCollisionHitNum(2);
			pPlayer->MotionPatternChange(new CPlayerMotionPatternSwordAttack_2nd(pModelMotion));
		}
		else
		{
			pPlayer->SetOrbitDrawStartJudge(false);
			pPlayer->SetCollisionHitNum(2);
			pPlayer->MotionPatternChange(new CPlayerMotionPatternNormal(pModelMotion));
		}
	}
	

}
