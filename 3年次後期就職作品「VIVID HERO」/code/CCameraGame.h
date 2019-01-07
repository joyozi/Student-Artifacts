//��-------------------------------------------------------------------------��
//
//	File:CCameraGame�̃w�b�_�[�t�@�C��[CCameraGame.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CCAMERAGAME_H_
#define _CCAMERAGAME_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CCamera.h"

#define CAMERA_MOVE (0.6f)
#define CAMERA_ROLL (0.02f)

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
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
	D3DXVECTOR3		m_AdjustmentPos;		//�J�����̔������������킹��������
	D3DXVECTOR3		m_AdjustmentNowPos;		//���݂̒������ꂽ�ʒu
};

#endif





