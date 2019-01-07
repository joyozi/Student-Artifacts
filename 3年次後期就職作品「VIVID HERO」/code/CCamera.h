//��-------------------------------------------------------------------------��
//
//	File:CCamera�̃w�b�_�[�t�@�C��[CCamera.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CAMERA_A_H_
#define _CAMERA_A_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "main.h"
#include "CItemList.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CCamera
{
public:
	CCamera();
	virtual ~CCamera();
	
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Set(void);
	
	virtual D3DXMATRIX GetMtxView(void);
	virtual void CameraMovePPlus(D3DXVECTOR3 PlusPos);
	virtual void CameraMovePPlus(float x,float y,float z);
	virtual void CameraMovePSet(D3DXVECTOR3 SetPos);
	virtual void CameraMovePSet(float x,float y,float z);
	virtual void CameraMoveRPlus(D3DXVECTOR3 PlusPos);		//���l�����Z����
	virtual void CameraMoveRPlus(float x,float y,float z);		//���l�����Z����
	virtual void CameraMoveRSet(D3DXVECTOR3 SetPos);			//���l�����̂܂ܑ������
	virtual void CameraMoveRSet(float x,float y,float z);		//���l�����̂܂ܑ������
	
	virtual D3DXVECTOR3 GetCameraP(void);
	virtual D3DXVECTOR3 GetCameraR(void);

	virtual D3DXVECTOR3 GetRotationP(void){return D3DXVECTOR3(0.0f,atan2f(m_posCameraP.z - m_posCameraR.z,m_posCameraP.x - m_posCameraR.x),0.0f);}

	virtual D3DXVECTOR3 GetCameraVector(void);

	virtual void SetCameraResultAdjustment(D3DXVECTOR3 Ajdust){}
	virtual D3DXVECTOR3 GetCameraResultAdjustment(){return D3DXVECTOR3(0.0f,0.0f,0.0f);}


	virtual D3DXVECTOR3 GetCameraPosition(){return m_posCamera;}
	virtual D3DXVECTOR3 GetCameraRotation(){return m_rotCamera;}

	virtual float GetCameraRotationY(){
		return CItemList::VecAngle_2DSimple(m_posCameraR - m_posCameraP);
	}


protected:
	D3DXVECTOR3 m_posCamera;					//�ʒu
	D3DXVECTOR3 m_rotCamera;					//����
	D3DXVECTOR3 m_sclCamera;					//�傫���i��{�ς��Ȃ��j
	D3DXVECTOR3 m_posCameraP;					//�J�����̎��_
	D3DXVECTOR3 m_posCameraR;					//�J�����̒����_
	D3DXVECTOR3 m_posCameraU;					//�J�����̏�����x�N�g��

	D3DXMATRIX m_mtxProjection;					//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;						//�r���[�}�g���b�N�X
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_CameraVec;
};



#endif





