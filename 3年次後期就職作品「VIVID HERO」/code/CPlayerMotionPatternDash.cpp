//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternDash�̃t�@�C��[CPlayerMotionPatternDash.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CPlayerMotionPatternDash.h"
#include "CPlayerMotionPatternNormal.h"

#include "CCharaMove.h"
#include "CPlayerModel.h"
#include "CManager.h"
#include "CCamera.h"
#include "joystick.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CPlayerMotionPatternDash�̃R���X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternDash::CPlayerMotionPatternDash(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_NUTORAL);
}

//��-----------------------------------��
//CPlayerMotionPatternDash�̃f�X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternDash::~CPlayerMotionPatternDash()
{

}

//��-----------------------------------��
//CPlayerMotionPatternDash�̍X�V����
//��-----------------------------------��
void CPlayerMotionPatternDash::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	CCharaMove::CharaMoveRobo(pPlayer,CManager::GetCameraPointer()->GetCameraRotationY(),120.0f);

	//�j���[�g�������ɗv�����ꂽ��
	if(GetJoystickPress(JS_A) == false)
	{
		pPlayer->MotionPatternChange(new CPlayerMotionPatternNormal(pModelMotion));
	}
}





