//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternMelee�̃w�b�_�[�t�@�C��[CPlayerMotionPatternMelee.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CPLAYERMOTIONPATTERN_MELEE_H_
#define _CPLAYERMOTIONPATTERN_MELEE_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CPlayerMotionPattern.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CPlayerMotionPatternMelee : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternMelee(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternMelee();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);

private:
	int m_AccessTimeCnt;
};



#endif
