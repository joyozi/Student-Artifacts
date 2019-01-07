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
#include "taimatsu.h"
#include "model.h"
#include "camera.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 g_pTextureTaimatsu;		//
LPD3DXMESH g_pMeshTaimatsu;					//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatTaimatsu;			//�}�e���A�����ւ̃|�C���^

DWORD g_numMatTaimatsu;						//�}�e���A���̐�
D3DXVECTOR3 g_posTaimatsu;					//���f���̈ʒu
D3DXVECTOR3 g_rotTaimatsu;					//���f���̌���
D3DXVECTOR3 g_sclTaimatsu;					//���f���̑傫��

D3DXMATRIX g_mtxWorldTaimatsu;				//���[���h�}�g���b�N�X

float Taimatsu_POSZ;

bool taimatu_sayuu;						//�����̍��E�̔���
bool kisuu_taimatuOPSION;				//��Ԍ��̏��������E�ǂ���ɂ��邩������B�����̐�����ɂ���Ȃ�g��

//��-------------------------------------------------------------------------��
//���f���̏���������
//��-------------------------------------------------------------------------��
void InitTaimatsu(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	taimatu_sayuu = true;				//�����̍��E�ʒu�̏�����
	kisuu_taimatuOPSION = taimatu_sayuu;//��Ԍ��̏����̈ʒu�̑��
	Taimatsu_POSZ = -CAMERA_LONG;		//�����̈ʒu�̏�����

	//****���f���̏��Z�b�g****
	D3DXLoadMeshFromX("./data/MODEL/taimatsu_001.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatTaimatsu,
					NULL,
					&g_numMatTaimatsu,
					&g_pMeshTaimatsu);

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posTaimatsu = D3DXVECTOR3(70.0f,120.0f,Taimatsu_POSZ);
	g_rotTaimatsu = D3DXVECTOR3(0.0f,0.0f,0.5f);
	g_sclTaimatsu = D3DXVECTOR3(1.0f,1.0f,1.0f);
}
//��-------------------------------------------------------------------------��
//���f���̏I������
//��-------------------------------------------------------------------------��
void UninitTaimatsu(void)
{
	//���b�V�����f���̃����[�X
	//==============================
	if(g_pMeshTaimatsu != NULL)
	{
		g_pMeshTaimatsu -> Release();
		g_pMeshTaimatsu = NULL;
	}
	
	//�o�b�t�@�}�b�g�̃����[�X
	//=============================
	if(g_pBuffMatTaimatsu != NULL)
	{
		g_pBuffMatTaimatsu -> Release();
		g_pBuffMatTaimatsu = NULL;
	}

	//�e�N�X�e���̃����[�X
	//=============================
	if(g_pTextureTaimatsu != NULL)
	{
		g_pTextureTaimatsu -> Release();
		g_pTextureTaimatsu = NULL;

	}
}
//��-------------------------------------------------------------------------��
//���f���̍X�V����
//��-------------------------------------------------------------------------��
void UpdateTaimatsu(void)
{

}
//��-------------------------------------------------------------------------��
//���f���̕`�揈��
//��-------------------------------------------------------------------------��
void DrawTaimatsu(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//kisuu_taimatuOPSION����ŏ��ɂ��Ȃ��ƁA�����̈ʒu�����������Ȃ����肷��
	taimatu_sayuu = kisuu_taimatuOPSION;
	

	//���������E�̂ǂ����ɐݒu���邩�̃W���b�W
	//�{�̂̈ʒu��艓����������v���X�}�C�i�X����
	//�����̏���ۑ����Ȃ��ł��̏�̃m���ł���Ă�̂ŁA���l�̕ϊ�������Ƃ��܂Ɉʒu�����������Ȃ�
	while(Getg_posModel().z - CAMERA_LONG >= Taimatsu_POSZ)
	{
		Taimatsu_POSZ += TAIMATSU_KANKAKU;

		//���E�ړ�
		if(taimatu_sayuu == true)
			taimatu_sayuu = false;
		else
			taimatu_sayuu = true;

		//��Ԍ��̏����̍��E�ʒu�̔���
		if(kisuu_taimatuOPSION == true)
			kisuu_taimatuOPSION = false;
		else
			kisuu_taimatuOPSION = true;
	}

	while(Getg_posModel().z + CAMERA_LONG < Taimatsu_POSZ + CAMERA_LONG * 2)
	{
		Taimatsu_POSZ -= TAIMATSU_KANKAKU;

		//���E�ړ�
		if(taimatu_sayuu == true)
			taimatu_sayuu = false;
		else
			taimatu_sayuu = true;

		//��Ԍ��̏����̍��E�ʒu�̔���
		if(kisuu_taimatuOPSION == true)
			kisuu_taimatuOPSION = false;
		else
			kisuu_taimatuOPSION = true;

	}

	g_posTaimatsu.z = Taimatsu_POSZ;

	while(g_posTaimatsu.z < Taimatsu_POSZ + CAMERA_LONG * 2)
	{
		//�����̈ʒu����Ԍ��ɐݒ�
		g_posTaimatsu.z += TAIMATSU_KANKAKU;

		if(taimatu_sayuu == true)
		{
			//�������������獶���ɏ�����\������
			g_posTaimatsu.x = TAIMATSU_POSX;
			g_rotTaimatsu.y = 0.0f;
			taimatu_sayuu = false;
		}
		else
		{
			g_posTaimatsu.x = -TAIMATSU_POSX;
			g_rotTaimatsu.y = D3DX_PI;
			taimatu_sayuu = true;
		}

		D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
		D3DXMATERIAL *pMat;
		D3DMATERIAL9 matDef;		//�}�b�g�̃f�t�H���g

		//****���[���h�̐ݒ�****
		D3DXMatrixIdentity(&g_mtxWorldTaimatsu);
		D3DXMatrixScaling(&mtxScl,g_sclTaimatsu.x,
									g_sclTaimatsu.y,
									g_sclTaimatsu.z);			//�X�P�[���𔽉f

		D3DXMatrixMultiply(&g_mtxWorldTaimatsu,&g_mtxWorldTaimatsu,&mtxScl);

		//****���̑��̐ݒ�****
		D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotTaimatsu.y,
										g_rotTaimatsu.x,
										g_rotTaimatsu.z);		//���|�@�s�b�`�@���[��

		D3DXMatrixMultiply(&g_mtxWorldTaimatsu,&g_mtxWorldTaimatsu,&mtxRot);
		D3DXMatrixTranslation(&mtxTranslate,g_posTaimatsu.x,g_posTaimatsu.y,g_posTaimatsu.z);	//�ʒu�𔽉f
		D3DXMatrixMultiply(&g_mtxWorldTaimatsu,&g_mtxWorldTaimatsu,&mtxTranslate);
	
		pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldTaimatsu);	//�ݒ�

		//=========�}�e���A���Ȃǂ̎擾=========
		//======================================
		pDevice -> GetMaterial(&matDef);
		pMat = (D3DXMATERIAL*)g_pBuffMatTaimatsu -> GetBufferPointer();

		for(int nCntMat = 0;nCntMat < (int)g_numMatTaimatsu;nCntMat++)
		{
			pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
			pDevice -> SetTexture(0,NULL);
			g_pMeshTaimatsu -> DrawSubset(nCntMat);
		}

		pDevice -> SetMaterial(&matDef);
	}

	//�I������珼���̖���̂��߂Ɉʒu����Ԍ��ɖ߂�
	g_posTaimatsu.z = Taimatsu_POSZ;

}

//�����̈ʒu���̊֐�
D3DXVECTOR3 Getpostaimatsu(void)
{
	return g_posTaimatsu;
}