//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternSwordAttack_2nd�̃w�b�_�[�t�@�C��[CPlayerMotionPatternSwordAttack_2nd.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CPLAYERMOTIONPATTERN_SWORDATTACK_2ND_H_
#define _CPLAYERMOTIONPATTERN_SWORDATTACK_2ND_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CPlayerMotionPattern.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CPlayerMotionPatternSwordAttack_2nd : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternSwordAttack_2nd(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternSwordAttack_2nd();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);

};



#endif
