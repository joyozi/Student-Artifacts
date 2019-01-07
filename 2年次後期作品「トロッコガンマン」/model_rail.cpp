//��-------------------------------------------------------------------------��
//
//	File	:���f�������t�@�C��[rail.cpp]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "input.h"
#include "model_rail.h"
#include "model.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��
#define MODEL_RAIL_DATA	("./data/MODEL/rail_002.x")	//���f���̃f�[�^�̈ʒu�Ɩ��O

#define MODEL_RAILLONG	(6000)								//���[���̒���

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 g_pTextureRail;		//
LPD3DXMESH g_pMeshRail;					//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatRail;			//�}�e���A�����ւ̃|�C���^

DWORD g_numMatRail;						//�}�e���A���̐�
D3DXVECTOR3 g_posRail;					//���f���̈ʒu
D3DXVECTOR3 g_rotRail;					//���f���̌���
D3DXVECTOR3 g_sclRail;					//���f���̑傫��

D3DXMATRIX g_mtxWorldRail;				//���[���h�}�g���b�N�X

float railLong;		//���[���̈�Ԍ��̍��W

//��-------------------------------------------------------------------------��
//���f���̏���������
//��-------------------------------------------------------------------------��
void InitRail(void)
{
	//���[���ʒu�̏��������Ȃ��Ƃ�
	railLong = -MODEL_RAILLONG / 2;

	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//****���f���̏��Z�b�g****
	D3DXLoadMeshFromX(MODEL_RAIL_DATA,
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatRail,
					NULL,
					&g_numMatRail,
					&g_pMeshRail);

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posRail = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_rotRail = D3DXVECTOR3(0.0f,D3DX_PI,0.0f);
	g_sclRail = D3DXVECTOR3(1.0f,1.0f,1.0f);
}
//��-------------------------------------------------------------------------��
//���f���̏I������
//��-------------------------------------------------------------------------��
void UninitRail(void)
{
	//���b�V�����f���̃����[�X
	//==============================
	if(g_pMeshRail != NULL)
	{
		g_pMeshRail -> Release();
		g_pMeshRail = NULL;
	}
	
	//�o�b�t�@�}�b�g�̃����[�X
	//=============================
	if(g_pBuffMatRail != NULL)
	{
		g_pBuffMatRail -> Release();
		g_pBuffMatRail = NULL;
	}

	//�e�N�X�e���̃����[�X
	//=============================
	if(g_pTextureRail != NULL)
	{
		g_pTextureRail -> Release();
		g_pTextureRail = NULL;

	}
}
//��-------------------------------------------------------------------------��
//���f���̍X�V����
//��-------------------------------------------------------------------------��
void UpdateRail(void)
{

}
//��-------------------------------------------------------------------------��
//���f���̕`�揈��
//��-------------------------------------------------------------------------��
void DrawRail(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//�}�b�g�̃f�t�H���g

	while(Getg_posModel().z - MODEL_RAILLONG / 2 >= railLong)
	{
		railLong += 98;
	}

	while(Getg_posModel().z + MODEL_RAILLONG / 2 < railLong + MODEL_RAILLONG)
	{
		railLong -= 98;
	}

	g_posRail.z = railLong;//Getg_posModel().z - 2000;

	while(g_posRail.z < railLong + MODEL_RAILLONG)
	{
		g_posRail.z += 98; 

		//****���[���h�̐ݒ�****
		D3DXMatrixIdentity(&g_mtxWorldRail);
		D3DXMatrixScaling(&mtxScl,g_sclRail.x,
									g_sclRail.y,
									g_sclRail.z);			//�X�P�[���𔽉f

		D3DXMatrixMultiply(&g_mtxWorldRail,&g_mtxWorldRail,&mtxScl);

		//****���̑��̐ݒ�****
		D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotRail.y,
										g_rotRail.x,
										g_rotRail.z);		//���|�@�s�b�`�@���[��

		D3DXMatrixMultiply(&g_mtxWorldRail,&g_mtxWorldRail,&mtxRot);
		D3DXMatrixTranslation(&mtxTranslate,g_posRail.x,g_posRail.y,g_posRail.z);	//�ʒu�𔽉f
		D3DXMatrixMultiply(&g_mtxWorldRail,&g_mtxWorldRail,&mtxTranslate);
	
		pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldRail);	//�ݒ�

		//=========�}�e���A���Ȃǂ̎擾=========
		//======================================
		pDevice -> GetMaterial(&matDef);
		pMat = (D3DXMATERIAL*)g_pBuffMatRail -> GetBufferPointer();

		for(int nCntMat = 0;nCntMat < (int)g_numMatRail;nCntMat++)
		{
			pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
			pDevice -> SetTexture(0,NULL);
			g_pMeshRail -> DrawSubset(nCntMat);
		}

		pDevice -> SetMaterial(&matDef);
	}
}

//================================
//�ʒu�Ɗp�x�̎擾�֐�
//================================
D3DXVECTOR3 Getg_posRail(void)
{
	return g_posRail;
}

D3DXVECTOR3 Getg_rotRail(void)
{
	return g_rotRail;
}
