//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternDash�̃w�b�_�[�t�@�C��[CPlayerMotionPatternDash.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CPLAYERMOTIONPATTERN_DASH_H_
#define _CPLAYERMOTIONPATTERN_DASH_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CPlayerMotionPattern.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CPlayerMotionPatternDash : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternDash(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternDash();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);

};



#endif
