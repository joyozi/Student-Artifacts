//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternNormal�̃w�b�_�[�t�@�C��[CPlayerMotionPatternNormal.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CPLAYERMOTIONPATTERN_NORMAL_H_
#define _CPLAYERMOTIONPATTERN_NORMAL_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CPlayerMotionPattern.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CPlayerMotionPatternNormal : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternNormal();									//�����ɂ��������Ȃ��R���X�g�쐬
	CPlayerMotionPatternNormal(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternNormal();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);

private:
	int m_DowblePushCntL;
	int m_DowblePushCntR;

	bool m_DowblePushJudgeL;
	bool m_DowblePushJudgeR;
};



#endif
