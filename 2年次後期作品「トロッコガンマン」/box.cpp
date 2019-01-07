//��-------------------------------------------------------------------------��
//
//	File	:���f�������t�@�C��[model.cpp]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "box.h"
#include "model.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 g_pTextureBox;		//
LPD3DXMESH g_pMeshBox;				//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatBox;			//�}�e���A�����ւ̃|�C���^

DWORD g_numMatBox;					//�}�e���A���̐�
D3DXVECTOR3 g_posBox;					//���f���̈ʒu
D3DXVECTOR3 g_rotBox;					//���f���̌���
D3DXVECTOR3 g_sclBox;					//���f���̑傫��

D3DXMATRIX g_mtxProjectionBox;		//�v���W�F�N�V�����}�g���b�N�X
D3DXMATRIX g_mtxViewBox;				//�r���[�}�g���b�N�X
D3DXMATRIX g_mtxWorldBox;				//���[���h�}�g���b�N�X

//��-------------------------------------------------------------------------��
//���f���̏���������
//��-------------------------------------------------------------------------��
void InitBox(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	VERTEX_3D *pVtx;

	//****���f���̏��Z�b�g****
	D3DXLoadMeshFromX("./data/MODEL/box006.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatBox,
					NULL,
					&g_numMatBox,
					&g_pMeshBox);

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posBox = D3DXVECTOR3(0.0f,30.0f,1000);
	g_rotBox = D3DXVECTOR3(0.0f,D3DX_PI,0.0f);
	g_sclBox = D3DXVECTOR3(1.0f,1.0f,1.0f);
}
//��-------------------------------------------------------------------------��
//���f���̏I������
//��-------------------------------------------------------------------------��
void UninitBox(void)
{
	//���b�V�����f���̃����[�X
	//==============================
	if(g_pMeshBox != NULL)
	{
		g_pMeshBox->Release();
		g_pMeshBox = NULL;
	}
	
	//�o�b�t�@�}�b�g�̃����[�X
	//=============================
	if(g_pBuffMatBox != NULL)
	{
		g_pBuffMatBox->Release();
		g_pBuffMatBox = NULL;
	}
}
//��-------------------------------------------------------------------------��
//���f���̍X�V����
//��-------------------------------------------------------------------------��
void UpdateBox(void)
{
	g_rotBox.y +=0.05f;
}
//��-------------------------------------------------------------------------��
//���f���̕`�揈��
//��-------------------------------------------------------------------------��
void DrawBox(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//�}�b�g�̃f�t�H���g

	//****���[���h�̐ݒ�****
	D3DXMatrixIdentity(&g_mtxWorldBox);
	D3DXMatrixScaling(&mtxScl,g_sclBox.x,
								g_sclBox.y,
								g_sclBox.z);			//�X�P�[���𔽉f

	D3DXMatrixMultiply(&g_mtxWorldBox,&g_mtxWorldBox,&mtxScl);

	//****���̑��̐ݒ�****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotBox.y,
									g_rotBox.x,
									g_rotBox.z);		//���|�@�s�b�`�@���[��

	D3DXMatrixMultiply(&g_mtxWorldBox,&g_mtxWorldBox,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,g_posBox.x,g_posBox.y,g_posBox.z);	//�ʒu�𔽉f
	D3DXMatrixMultiply(&g_mtxWorldBox,&g_mtxWorldBox,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldBox);	//�ݒ�

	//=========�}�e���A���Ȃǂ̎擾=========
	//======================================
	pDevice -> GetMaterial(&matDef);
	pMat = (D3DXMATERIAL*)g_pBuffMatBox -> GetBufferPointer();

	for(int nCntMat = 0;nCntMat < (int)g_numMatBox;nCntMat++)
	{
		pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
		pDevice -> SetTexture(0,NULL);
		g_pMeshBox -> DrawSubset(nCntMat);
	}

	pDevice -> SetMaterial(&matDef);
}
