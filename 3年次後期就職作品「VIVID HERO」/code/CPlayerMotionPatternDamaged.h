//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternDamaged�̃w�b�_�[�t�@�C��[CPlayerMotionPatternDamaged.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CPLAYERMOTIONPATTERN_DAMAGED_H_
#define _CPLAYERMOTIONPATTERN_DAMAGED_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CPlayerMotionPattern.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CPlayerMotionPatternDamaged : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternDamaged(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternDamaged();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);

private:
	int m_DamagedTimeCnt;
};



#endif
