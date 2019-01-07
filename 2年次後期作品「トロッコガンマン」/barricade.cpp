//��-------------------------------------------------------------------------��
//
//	File	:�o���P�[�h�����t�@�C��[Barricade.cpp]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "barricade.h"
#include "obstacle.h"
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
LPDIRECT3DTEXTURE9 g_pTextureBarricade;			//
LPD3DXMESH g_pMeshBarricade;					//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatBarricade;				//�}�e���A�����ւ̃|�C���^

DWORD g_numMatBarricade;						//�}�e���A���̐�
D3DXVECTOR3 g_posBarricade;						//���f���̈ʒu
D3DXVECTOR3 g_rotBarricade;						//���f���̌���
D3DXVECTOR3 g_sclBarricade;						//���f���̑傫��

D3DXMATRIX g_mtxWorldBarricade;					//���[���h�}�g���b�N�X

PLAYER_MODE Barricade_info[BARRICADE_NUM];		//�G01�̏�Q���̓���q

//��-------------------------------------------------------------------------��
//���f���̏���������
//��-------------------------------------------------------------------------��
void InitBarricade(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//��Q���̍��W������@�w��
	int Barricade_posX_ORIGINAL[BARRICADE_NUM] = {2,1};
	//��Q���̍��W�@���ς��Ȃ��@�y��
	float Barricade_posZ_ORIGINAL[BARRICADE_NUM] = {0,0,0,0,0,0,0,0,0,0,600,600,0,0,600,0,0,0,0,0};

	//��Q����\�������邩�ǂ����̐���
	bool Barricade_Exist_ORIGINAL[BARRICADE_NUM] = {false,false,true,false,false,true,false,true,true ,true ,
													true ,true ,false,false,true ,true ,false,false,false,false};

	for(int nCnt = 0;nCnt < BARRICADE_NUM;nCnt++)
	{
		//��Q���̈ʒu������
//		Barricade_info[nCnt].LR_Judge = Barricade_posX_ORIGINAL[nCnt];
		Barricade_info[nCnt].LR_Judge = 0;										//���E�֌W�Ȃ��̂�0������
		Barricade_info[nCnt].MOTO_pos.z = Barricade_posZ_ORIGINAL[nCnt];

		//��Q���̕\�����������
		Barricade_info[nCnt].Thing_exist = Barricade_Exist_ORIGINAL[nCnt];

		//���l�̊ȗ����@��Q���ݒu�J�n�ʒu���v���X,�Ԋu�������Ă���
		Barricade_info[nCnt].MOTO_pos.z = Barricade_info[nCnt].MOTO_pos.z + OBSTACLE_SETTI_LINE + nCnt * 3000 + 600;
	}
	
	//****���f���̏��Z�b�g****
	D3DXLoadMeshFromX("./data/MODEL/barricade_000.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatBarricade,
					NULL,
					&g_numMatBarricade,
					&g_pMeshBarricade);

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posBarricade = D3DXVECTOR3(0.0f,0.0f,500.0f);
	g_rotBarricade = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclBarricade = D3DXVECTOR3(1.0f,1.0f,1.0f);
}
//��-------------------------------------------------------------------------��
//���f���̏I������
//��-------------------------------------------------------------------------��
void UninitBarricade(void)
{
	//���b�V�����f���̃����[�X
	//==============================
	if(g_pMeshBarricade != NULL)
	{
		g_pMeshBarricade -> Release();
		g_pMeshBarricade = NULL;
	}
	
	//�o�b�t�@�}�b�g�̃����[�X
	//=============================
	if(g_pBuffMatBarricade != NULL)
	{
		g_pBuffMatBarricade -> Release();
		g_pBuffMatBarricade = NULL;
	}

	//�e�N�X�e���̃����[�X
	//=============================
	if(g_pTextureBarricade != NULL)
	{
		g_pTextureBarricade -> Release();
		g_pTextureBarricade = NULL;

	}
}
//��-------------------------------------------------------------------------��
//���f���̍X�V����
//��-------------------------------------------------------------------------��
void UpdateBarricade(void)
{
	
}
//��-------------------------------------------------------------------------��
//���f���̕`�揈��
//��-------------------------------------------------------------------------��
void DrawBarricade(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//�}�b�g�̃f�t�H���g
	
	//��Q���̐������J��Ԃ�
	for(int nCnt = 0;nCnt < BARRICADE_NUM;nCnt++)
	{
		if(Barricade_info[nCnt].Thing_exist == true)
		{
			//������ʒu�̂ݕ\�����邽�߂ɁA�\���͈͓̔���������`�悷��悤�ɂ���
			if(Getg_posModel().z - CAMERA_LONG < Barricade_info[nCnt].MOTO_pos.z && Getg_posModel().z + CAMERA_LONG > Barricade_info[nCnt].MOTO_pos.z)
			{
				g_posBarricade.z = Barricade_info[nCnt].MOTO_pos.z;
			
				//****���[���h�̐ݒ�****
				D3DXMatrixIdentity(&g_mtxWorldBarricade);
				D3DXMatrixScaling(&mtxScl,g_sclBarricade.x,	g_sclBarricade.y,g_sclBarricade.z);			//�X�P�[���𔽉f

				D3DXMatrixMultiply(&g_mtxWorldBarricade,&g_mtxWorldBarricade,&mtxScl);

				//****���̑��̐ݒ�****
				D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotBarricade.y,g_rotBarricade.x,g_rotBarricade.z);		//���|�@�s�b�`�@���[��

				D3DXMatrixMultiply(&g_mtxWorldBarricade,&g_mtxWorldBarricade,&mtxRot);
				D3DXMatrixTranslation(&mtxTranslate,g_posBarricade.x,g_posBarricade.y,g_posBarricade.z);	//�ʒu�𔽉f
				D3DXMatrixMultiply(&g_mtxWorldBarricade,&g_mtxWorldBarricade,&mtxTranslate);
	
				pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldBarricade);	//�ݒ�

				//=========�}�e���A���Ȃǂ̎擾=========
				//======================================
				pDevice -> GetMaterial(&matDef);
 				pMat = (D3DXMATERIAL*)g_pBuffMatBarricade -> GetBufferPointer();

				for(int nCntMat = 0;nCntMat < (int)g_numMatBarricade;nCntMat++)
				{
					pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
					pDevice -> SetTexture(0,NULL);
					g_pMeshBarricade -> DrawSubset(nCntMat);
				}

				pDevice -> SetMaterial(&matDef);
			}
		}
	}
}
//======================================
//�G01�̊���̎󂯓n���֐�
//======================================
PLAYER_MODE GetBarricade_info(int num)
{
	return Barricade_info[num];
}
