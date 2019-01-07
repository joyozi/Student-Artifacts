//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionChanger�̃t�@�C��[CPlayerMotionChanger.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CPlayerMotionChanger.h"

#include "CPlayerModel.h"
#include "CSceneModelMotion.h"
#include "CPlayerMotionPattern.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CPlayerMotionChanger�̃R���X�g���N�^
//��-----------------------------------��
CPlayerMotionChanger::CPlayerMotionChanger(CPlayerMotionPattern *pPattern) : m_pPatternNow(pPattern)
{

}

//��-----------------------------------��
//CPlayerMotionChanger�̃f�X�g���N�^
//��-----------------------------------��
CPlayerMotionChanger::~CPlayerMotionChanger()
{
	delete m_pPatternNow;
}

//��-----------------------------------��
//CPlayerMotionChanger�̍X�V����
//��-----------------------------------��
void CPlayerMotionChanger::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	m_pPatternNow->Update(pPlayer,pModelMotion);
}

//��-----------------------------------��
//CPlayerMotionChanger�̃p�^�[���ύX
//��-----------------------------------��
void CPlayerMotionChanger::ChangedPattern(CPlayerMotionPattern *pPattern)
{
	if(m_pPatternNow != pPattern)
	{
		CPlayerMotionPattern *pChangePattern = m_pPatternNow;

		delete pChangePattern;
		pChangePattern = NULL;

		m_pPatternNow = pPattern;
	}
}


