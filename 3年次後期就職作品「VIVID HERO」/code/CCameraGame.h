//◇-------------------------------------------------------------------------◇
//
//	File:CCameraGameのヘッダーファイル[CCameraGame.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CCAMERAGAME_H_
#define _CCAMERAGAME_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CCamera.h"

#define CAMERA_MOVE (0.6f)
#define CAMERA_ROLL (0.02f)

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CCameraGame : public CCamera
{
public:
	CCameraGame();
	
	virtual void Update(void);
	
	virtual void SetCameraResultAdjustment(D3DXVECTOR3 Ajdust)override{m_AdjustmentPos = Ajdust;}
	virtual D3DXVECTOR3 GetCameraResultAdjustment()override{return m_AdjustmentPos;}


private:
	D3DVIEWPORT9	m_Viewport;

	float			m_LengthCamera;
	D3DXVECTOR3		m_CameraLength;
	D3DXVECTOR3		m_AdjustmentPos;		//カメラの微調整を向かわせたい方向
	D3DXVECTOR3		m_AdjustmentNowPos;		//現在の調整された位置
};

#endif





