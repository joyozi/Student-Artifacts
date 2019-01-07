//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternShotのヘッダーファイル[CPlayerMotionPatternShot.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPLAYERMOTIONPATTERN_SHOT_H_
#define _CPLAYERMOTIONPATTERN_SHOT_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CPlayerMotionPattern.h"
#include "main.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
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
