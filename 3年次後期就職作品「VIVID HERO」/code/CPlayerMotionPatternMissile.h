//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternMissile�̃w�b�_�[�t�@�C��[CPlayerMotionPatternMissile.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CPLAYERMOTIONPATTERN_MISSLE_H_
#define _CPLAYERMOTIONPATTERN_MISSLE_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CPlayerMotionPattern.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CPlayerMotionPatternMissile : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternMissile(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternMissile();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);

private:
	bool m_ShotMusicJudge;
};



#endif