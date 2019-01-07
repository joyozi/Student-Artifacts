//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternSwordAttack�̃w�b�_�[�t�@�C��[CPlayerMotionPatternSwordAttack.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CPLAYERMOTIONPATTERN_SWORDATTACK_H_
#define _CPLAYERMOTIONPATTERN_SWORDATTACK_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CPlayerMotionPattern.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CPlayerMotionPatternSwordAttack : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternSwordAttack(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternSwordAttack();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);

private:
	bool m_2ndSwordJudge;
	bool m_StartInfoJudge;

};



#endif
