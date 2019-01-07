//��-------------------------------------------------------------------------��
//
//	File:�J���������t�@�C��[CCamera.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CCamera.h"
#include "CManager.h"
#include "input.h"

//��---------------------------------��
//�R���X�g���N�^
//��---------------------------------��
CCamera::CCamera()
{
	//***�J�����̏�����***
	m_posCamera = D3DXVECTOR3(0.0f,0.0f,0.0f);				//�ʒu
	m_rotCamera = D3DXVECTOR3(0.0f,0.0f,0.0f);				//����
	m_sclCamera = D3DXVECTOR3(0.0f,0.0f,0.0f);				//�傫���i��{�ς��Ȃ��j

	m_posCameraP = D3DXVECTOR3(0.0f,0.0f,0.0f);				//�J�����̎��_
	m_posCameraR = D3DXVECTOR3(0.0f,0.0f,0.0f);				//�J�����̒����_
	m_posCameraU = D3DXVECTOR3(0.0f,1.0f,0.0f);				//�J�����̏�����x�N�g��

	m_CameraVec = D3DXVECTOR3(0.0f,0.0f,0.0f);
}

//��---------------------------------��
//�f�X�g���N�^
//��---------------------------------��
CCamera::~CCamera()
{

}
//��---------------------------------��
//�J��������������
//��---------------------------------��
HRESULT CCamera::Init(void)
{
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;	//

	//****�v���W�F�N�V�����̐ݒ�****  ���̐ݒ��camera.cpp�ɂ�������Ȃ��炵���Iby toshiyama
	D3DXMatrixIdentity(&m_mtxProjection);									//������
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,							//�쐬
								D3DX_PI / 4,								//����p(��p)
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//�A�X�y�N�g��i��ʔ䗦�j
								10,											//Near�l
								1000000);									//Far�l		�����̕��̂������Ȃ��Ȃ鋫�E���̒l

	pDevice -> SetTransform(D3DTS_PROJECTION,&m_mtxProjection);

	//****�r���[�̐ݒ�****
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixLookAtLH(&m_mtxView,
						&m_posCameraP,
						&m_posCameraR,
						&m_posCameraU);

	pDevice -> SetTransform(D3DTS_VIEW,&m_mtxView);

	//****���[���h�̐ݒ�****
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&mtxScl,m_sclCamera.x,
								m_sclCamera.y,
								m_sclCamera.z);			//�X�P�[���𔽉f

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

	//****���̑��̐ݒ�****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rotCamera.y,
									m_rotCamera.x,
									m_rotCamera.z);		//���|�@�s�b�`�@���[��

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,m_posCamera.x,m_posCamera.y,m_posCamera.z);	//�ʒu�𔽉f
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&m_mtxWorld);	//�ݒ�

	return S_OK;
}

//��---------------------------------��
//�J�����I������
//��---------------------------------��
void CCamera::Uninit(void)
{

}

//��---------------------------------��
//�J�����X�V����
//��---------------------------------��
void CCamera::Update(void)
{

}

//��---------------------------------��
//�J�����Z�b�g����
//��---------------------------------��
void CCamera::Set(void)
{
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;	//

	//****�v���W�F�N�V�����̐ݒ�****  ���̐ݒ��camera.cpp�ɂ�������Ȃ��炵���Iby toshiyama
	D3DXMatrixIdentity(&m_mtxProjection);									//������
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,							//�쐬
								D3DX_PI / 4,								//����p(��p)
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//�A�X�y�N�g��i��ʔ䗦�j
								10,											//Near�l
								1000000);									//Far�l		�����̕��̂������Ȃ��Ȃ鋫�E���̒l
								
	pDevice -> SetTransform(D3DTS_PROJECTION,&m_mtxProjection);

	//****�r���[�̐ݒ�****
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixLookAtLH(&m_mtxView,
						&m_posCameraP,
						&m_posCameraR,
						&m_posCameraU);

	pDevice -> SetTransform(D3DTS_VIEW,&m_mtxView);

	//****���[���h�̐ݒ�****
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&mtxScl,m_sclCamera.x,
								m_sclCamera.y,
								m_sclCamera.z);			//�X�P�[���𔽉f

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

	//****���̑��̐ݒ�****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rotCamera.y,
									m_rotCamera.x,
									m_rotCamera.z);		//���|�@�s�b�`�@���[��

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,m_posCamera.x,m_posCamera.y,m_posCamera.z);	//�ʒu�𔽉f
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&m_mtxWorld);	//�ݒ�
}

//��---------------------------------��
//�Q�b�g�}�g���b�N�X����
//��---------------------------------��
D3DXMATRIX CCamera::GetMtxView(void)
{
	return m_mtxView;
}
//��---------------------------------��
//���_�����@�v���X
//��---------------------------------��
void CCamera::CameraMovePPlus(D3DXVECTOR3 PlusPos)
{
	m_posCameraP += PlusPos;
}

//��---------------------------------��
//���_�����@�v���X ����2
//��---------------------------------��
void CCamera::CameraMovePPlus(float x,float y,float z)
{
	m_posCameraP.x += x;
	m_posCameraP.y += y;
	m_posCameraP.z += z;
}

//��---------------------------------��
//���_�����@�Z�b�g
//��---------------------------------��
void CCamera::CameraMovePSet(D3DXVECTOR3 SetPos)
{
	m_posCameraP = SetPos;
}

//��---------------------------------��
//���_����	�Z�b�g�@���̂Q
//��---------------------------------��
void CCamera::CameraMovePSet(float x,float y,float z)
{
	m_posCameraP.x = x;
	m_posCameraP.y = y;
	m_posCameraP.z = z;
}

//��---------------------------------��
//�����_�����@�v���X
//��---------------------------------��
void CCamera::CameraMoveRPlus(D3DXVECTOR3 PlusPos)
{
	m_posCameraR += PlusPos;
}

//��---------------------------------��
//�����_�Z�b�g�@�ǉ��ړ� ���̂Q
//��---------------------------------��
void CCamera::CameraMoveRPlus(float x,float y,float z)
{
	m_posCameraR.x += x;
	m_posCameraR.y += y;
	m_posCameraR.z += z;
}

//��---------------------------------��
//�����_�����@�Z�b�g
//��---------------------------------��
void CCamera::CameraMoveRSet(D3DXVECTOR3 SetPos)
{
	m_posCameraR = SetPos;
}

//��---------------------------------��
//�����_�ړ������@���̂Q
//��---------------------------------��
void CCamera::CameraMoveRSet(float x,float y,float z)
{
	m_posCameraR.x = x;
	m_posCameraR.y = y;
	m_posCameraR.z = z;
}

//��---------------------------------��
//���_�Q�b�g����
//��---------------------------------��
D3DXVECTOR3 CCamera::GetCameraP(void)
{
	return m_posCameraP;
}

//��---------------------------------��
//�����_�Q�b�g����
//��---------------------------------��
D3DXVECTOR3 CCamera::GetCameraR(void)
{
	return m_posCameraR;
}

//��---------------------------------��
//�J�����̃x�N�g���Q�b�g��������
//��---------------------------------��
D3DXVECTOR3 CCamera::GetCameraVector(void)
{
	m_CameraVec = m_posCameraR - m_posCameraP;

	//�g���₷���悤���K��
	D3DXVec3Normalize(&m_CameraVec,&m_CameraVec);

	return m_CameraVec;
}



