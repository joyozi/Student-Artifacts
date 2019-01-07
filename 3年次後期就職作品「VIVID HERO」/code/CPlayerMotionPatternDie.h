//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternDie�̃w�b�_�[�t�@�C��[CPlayerMotionPatternDie.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CPLAYERMOTIONPATTERN_DIE_H_
#define _CPLAYERMOTIONPATTERN_DIE_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CPlayerMotionPattern.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CPlayerMotionPatternDie : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternDie(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternDie();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);
};



#endif
