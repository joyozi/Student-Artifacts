//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternRapidUp�̃w�b�_�[�t�@�C��[CPlayerMotionPatternRapidUp.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CPLAYERMOTIONPATTERN_RAPIDUP_H_
#define _CPLAYERMOTIONPATTERN_RAPIDUP_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CPlayerMotionPattern.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CPlayerMotionPatternRapidUp : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternRapidUp(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternRapidUp();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);

private:
	int m_MoveUpCnt;
};



#endif
