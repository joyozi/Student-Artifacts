//��-------------------------------------------------------------------------��
//
//	File	:�J���������t�@�C��[camera.cpp]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "camera.h"
#include "input.h"
#include "model.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��
#define CAMERA_MOVE (0.6f);			//�J�����̈ړ��̑���
#define CAMERA_ROLL (0.05f);		//�J�����̉�]�̑���

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��
D3DXVECTOR3 GetRotCamera(void);

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
D3DXVECTOR3 g_posCamera;					//�ʒu
D3DXVECTOR3 g_rotCamera;					//����
D3DXVECTOR3 g_sclCamera;					//�傫���i��{�ς��Ȃ��j
D3DXVECTOR3 g_posCameraP;					//�J�����̎��_
D3DXVECTOR3 g_posCameraR;					//�J�����̒����_
D3DXVECTOR3 g_posCameraU;					//�J�����̏�����x�N�g��

D3DXMATRIX g_mtxProjection;					//�v���W�F�N�V�����}�g���b�N�X
D3DXMATRIX g_mtxView;						//�r���[�}�g���b�N�X
D3DXMATRIX g_mtxWorld;						//���[���h�}�g���b�N�X

float g_fLengthCamera;						//���_�ƒ����_�̋���

D3DVIEWPORT9 viewport;

//��-------------------------------------------------------------------------��
//�J��������������
//��-------------------------------------------------------------------------��
void InitCamera(void)
{
	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posCamera = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_rotCamera = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclCamera = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//***�J�����̏�����***
	g_posCameraP = D3DXVECTOR3(0.0f,150.0f,120.0f);		//�J�����̎��_
	g_posCameraR = D3DXVECTOR3(0.0f,60.0f,150.0f);		//�J�����̒����_
	g_posCameraU = D3DXVECTOR3(0.0f,1.0f,0.0f);			//�J�����̏�����x�N�g��

	viewport.X      = 0;
	viewport.Y      = 0;
	viewport.Width  = SCREEN_WIDTH / 2;
	viewport.Height = SCREEN_HEIGHT;
	viewport.MinZ   = 0.0f;
	viewport.MaxZ   = 1.0f;
}

//��---------------------------------��
//�J�����I������
//��---------------------------------��
void UninitCamera(void)
{

}
//��---------------------------------��
//�J�����̍X�V����
//��---------------------------------��
void UpdateCamera(void)
{
	static float rad = D3DX_PI;
	static float tyuurad = 0;

	static bool change = true;


	if(change == true)
	{
		//���f���𒆐S�Ɉړ�
//		g_posCameraR.x = Getg_posModel().x - sinf(g_rotCamera.y) * 30;
		g_posCameraR.z = Getg_posModel().z - cosf(g_rotCamera.y) + 400;

		g_posCameraP.x = g_posCameraR.x - sinf(g_rotCamera.y) * 700;
		g_posCameraP.z = g_posCameraR.z - cosf(g_rotCamera.y) * 650;

	}
	else
	{	//���f���̐i�s�����̐�𒆐S�Ɉړ�
		g_posCameraR.x = Getg_posModel().x;
		g_posCameraR.z = Getg_posModel().z;

		g_posCameraP.x = g_posCameraR.x - sinf(g_rotCamera.y) * 300;
		g_posCameraP.z = g_posCameraR.z - cosf(g_rotCamera.y) * 300;
	}

}

//��---------------------------------��
//�J�����̃Z�b�g����
//��---------------------------------��
void SetCamera(void)
{
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;	//

	//****�v���W�F�N�V�����̐ݒ�****  ���̐ݒ��camera.cpp�ɂ�������Ȃ��炵���Iby toshiyama
	D3DXMatrixIdentity(&g_mtxProjection);									//������
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,							//�쐬
								D3DX_PI / 4,								//����p(��p)
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//�A�X�y�N�g��i��ʔ䗦�j
								10,											//Near�l
								CAMERA_LONG);								//Far�l		�����̕��̂������Ȃ��Ȃ鋫�E���̒l

	pDevice -> SetTransform(D3DTS_PROJECTION,&g_mtxProjection);

	//****�r���[�̐ݒ�****
	D3DXMatrixIdentity(&g_mtxView);
	D3DXMatrixLookAtLH(&g_mtxView,
						&g_posCameraP,
						&g_posCameraR,
						&g_posCameraU);

	pDevice -> SetTransform(D3DTS_VIEW,&g_mtxView);

	//****���[���h�̐ݒ�****
	D3DXMatrixIdentity(&g_mtxWorld);
	D3DXMatrixScaling(&mtxScl,g_sclCamera.x,
								g_sclCamera.y,
								g_sclCamera.z);			//�X�P�[���𔽉f

	D3DXMatrixMultiply(&g_mtxWorld,&g_mtxWorld,&mtxScl);

	//****���̑��̐ݒ�****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotCamera.y,
									g_rotCamera.x,
									g_rotCamera.z);		//���|�@�s�b�`�@���[��

	D3DXMatrixMultiply(&g_mtxWorld,&g_mtxWorld,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,g_posCamera.x,g_posCamera.y,g_posCamera.z);	//�ʒu�𔽉f
	D3DXMatrixMultiply(&g_mtxWorld,&g_mtxWorld,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorld);	//�ݒ�
}

//*********************************
//���낢��ȃQ�b�g
//*********************************
D3DXVECTOR3 GetposCamera(void)
{
	return g_posCamera;
}

D3DXVECTOR3 GetRotCamera(void)
{
	return g_rotCamera;
}

D3DXVECTOR3 GetsclCamera(void)
{
	return g_sclCamera;
}

D3DXMATRIX GetMtxView(void)
{
	return g_mtxView;
}