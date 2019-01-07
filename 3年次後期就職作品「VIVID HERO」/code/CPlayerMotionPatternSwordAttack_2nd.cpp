//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternSwordAttack_2nd�̃t�@�C��[CPlayerMotionPatternSwordAttack_2nd.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
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
static bool soundJudge = false;


//��-----------------------------------��
//CPlayerMotionPatternSwordAttack_2nd�̃R���X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternSwordAttack_2nd::CPlayerMotionPatternSwordAttack_2nd(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_SWORDATTACK_2ND);

	soundJudge = false;
}

//��-----------------------------------��
//CPlayerMotionPatternSwordAttack_2nd�̃f�X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternSwordAttack_2nd::~CPlayerMotionPatternSwordAttack_2nd()
{

}

//��-----------------------------------��
//CPlayerMotionPatternSwordAttack_2nd�̍X�V����
//��-----------------------------------��
void CPlayerMotionPatternSwordAttack_2nd::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	pPlayer->SetCollisionHitNum(3);
	pPlayer->SetOrbitDrawStartJudge(true);

	if(soundJudge == false && pModelMotion->GetNowMotionNum() == 2)
	{
		soundJudge = true;
		PlaySound(SOUND_LABEL_Sword2nd);

	}

	//���[�V�������I�������
	if(pModelMotion->GetMotionEndJudge())
	{
		pPlayer->SetOrbitDrawStartJudge(false);
		pPlayer->SetCollisionHitNum(2);
		pPlayer->MotionPatternChange(new CPlayerMotionPatternNormal(pModelMotion));
	}
}
