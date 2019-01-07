//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternShot�̃w�b�_�[�t�@�C��[CPlayerMotionPatternShot.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CPLAYERMOTIONPATTERN_SHOT_H_
#define _CPLAYERMOTIONPATTERN_SHOT_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CPlayerMotionPattern.h"
#include "main.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CPlayerMotionPatternShot : public CPlayerMotionPattern
{
public:
	CPlayerMotionPatternShot(CSceneModelMotion *pModelMotion);
	virtual ~CPlayerMotionPatternShot();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);

private:
	static const int CAMERA_MOVECNT = 20;
	
	float m_NowCameraMovePos;
	float m_SaveCameraMovedPos;
	float m_GoMovePos;


	int m_CameraMoveCnt;
};



#endif
