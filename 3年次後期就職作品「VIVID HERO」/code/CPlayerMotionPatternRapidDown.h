//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternRapidDown�̃w�b�_�[�t�@�C��[CPlayerMotionPatternRapidDown.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CPLAYERMOTIONPATTERN_RAPIDDOWN_H_
#define _CPLAYERMOTIONPATTERN_RAPIDDOWN_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CPlayerMotionPattern.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CPlayerMotionPatternRapidDown : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternRapidDown(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternRapidDown();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);
	
private:
	int m_MoveDownCnt;
};



#endif
