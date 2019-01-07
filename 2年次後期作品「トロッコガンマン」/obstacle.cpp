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
#include "obstacle.h"
#include "model.h"
#include "gameUI.h"
#include "camera.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��
#define MODEL_OBSTACLE_DATA	("./data/MODEL/rock_001.x")	//���f���̃f�[�^�̈ʒu�Ɩ��O

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 g_pTextureObstacle;		//
LPD3DXMESH g_pMeshObstacle;					//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatObstacle;			//�}�e���A�����ւ̃|�C���^

DWORD g_numMatObstacle;						//�}�e���A���̐�
D3DXVECTOR3 g_posObstacle;					//���f���̈ʒu
D3DXVECTOR3 g_rotObstacle[OBSTACLE_NUM];	//���f���̌���	��̌�����ς��邽�߂ɔz��ɂ���
D3DXVECTOR3 g_sclObstacle;					//���f���̑傫��

D3DXMATRIX g_mtxWorldObstacle;				//���[���h�}�g���b�N�X

PLAYER_MODE Obstacle_info[OBSTACLE_NUM];	//��Q���̏��̓���q

//��-------------------------------------------------------------------------��
//���f���̏���������
//��-------------------------------------------------------------------------��
void InitObstacle(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//��Q���̍��W������@�w��
	int Obstacle_posX_ORIGINAL[OBSTACLE_NUM] = {2,0,0,3,0,2,1,3,0,2,0,0,0,0,0,0,0,0,2,0,				//0�`19
												1,3,0,0,0,3,1,3,0,0,1,0,0,3,2,1,0,0,0,0,				//20�`39
												1,3,0,3,0,0,0,3,0,0,									//�S�O�`�S�X
												0,0,3,0,2,0,0,1,3,0,									//�T�O�`�T�X
												0,0,2,0,0,3,2,0,3,0,									//60~69
												1,2,0,0,0,1,3,0,0,0,									//70~79
												0,0,2,2,0,0,1,3,2,0,									//80~89
												0,0,0,0,0,0,0,0,0,0};

	//��Q���̍��W�@���ς��Ȃ��@�y��
	float Obstacle_posZ_ORIGINAL[OBSTACLE_NUM] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
												0,-600,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
												0,-600,0,0,0,0,0,0,0,0,									//40~49
												0,0,0,0,0,0,0,0,0,0,									//50~59
												0,0,0,0,0,0,0,0,0,0,									//60~69
												600,0,0,0,0,600,0,0,0,0,								//70~79
												0,0,0,0,0,0,0,0,0,0,									//80~89
												0,0,0,0,0,0,0,0,0,0};

	for(int nCnt = 0;nCnt < OBSTACLE_NUM;nCnt++)
	{
		//��Q���̈ʒu������
		Obstacle_info[nCnt].LR_Judge = Obstacle_posX_ORIGINAL[nCnt];
		Obstacle_info[nCnt].MOTO_pos.z = Obstacle_posZ_ORIGINAL[nCnt];

		//��Q���̕\�����������
		if(Obstacle_posX_ORIGINAL[nCnt] != 0)
		{
			Obstacle_info[nCnt].Thing_exist = true;
		}
		else
		{
			Obstacle_info[nCnt].Thing_exist = false;
		}

		//���l�̊ȗ����@��Q���ݒu�J�n�ʒu���v���X,�Ԋu�������Ă���
		Obstacle_info[nCnt].MOTO_pos.z = Obstacle_info[nCnt].MOTO_pos.z + OBSTACLE_SETTI_LINE + nCnt * 600;
	}

	//****���f���̏��Z�b�g****
	D3DXLoadMeshFromX(MODEL_OBSTACLE_DATA,
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatObstacle,
					NULL,
					&g_numMatObstacle,
					&g_pMeshObstacle);

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posObstacle = D3DXVECTOR3(40.0f,0.0f,0.0f);
	g_sclObstacle = D3DXVECTOR3(1.0f,1.0f,1.0f);

	for(int nCnt = 0;nCnt < OBSTACLE_NUM;nCnt++)
	{
		g_rotObstacle[nCnt] = D3DXVECTOR3(0.0f,0.0f,0.0f);

		switch(nCnt % 4)
		{
		case 0:
			g_rotObstacle[nCnt].y = 0.0f;
			break;
		case 1:
			g_rotObstacle[nCnt].y = D3DX_PI / 2;
			break;
		case 2:
			g_rotObstacle[nCnt].y = D3DX_PI;
			break;
		case 3:
			g_rotObstacle[nCnt].y = -D3DX_PI / 2;
			break;

		}
	}
}
//��-------------------------------------------------------------------------��
//���f���̏I������
//��-------------------------------------------------------------------------��
void UninitObstacle(void)
{
	//���b�V�����f���̃����[�X
	//==============================
	if(g_pMeshObstacle != NULL)
	{
		g_pMeshObstacle -> Release();
		g_pMeshObstacle = NULL;
	}
	
	//�o�b�t�@�}�b�g�̃����[�X
	//=============================
	if(g_pBuffMatObstacle != NULL)
	{
		g_pBuffMatObstacle -> Release();
		g_pBuffMatObstacle = NULL;
	}

	//�e�N�X�e���̃����[�X
	//=============================
	if(g_pTextureObstacle != NULL)
	{
		g_pTextureObstacle -> Release();
		g_pTextureObstacle = NULL;

	}
}
//��-------------------------------------------------------------------------��
//���f���̍X�V����
//��-------------------------------------------------------------------------��
void UpdateObstacle(void)
{

}
//��-------------------------------------------------------------------------��
//���f���̕`�揈��
//��-------------------------------------------------------------------------��
void DrawObstacle(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//�}�b�g�̃f�t�H���g

	//��Q���̐������J��Ԃ�
	for(int nCnt = 0;nCnt < OBSTACLE_NUM;nCnt++)
	{
		//�\�������邩�ۂ��̔���
		if(Obstacle_info[nCnt].Thing_exist == true)
		{
			//������ʒu�̂ݕ\�����邽�߂ɁA�\���͈͓̔���������`�悷��悤�ɂ���
			if(Getg_posModel().z - CAMERA_LONG < Obstacle_info[nCnt].MOTO_pos.z && Getg_posModel().z + CAMERA_LONG > Obstacle_info[nCnt].MOTO_pos.z)
			{
				//�p�ӂ��Ă������ʒu�������g_posObstacle�ɂ����
				g_posObstacle.z = Obstacle_info[nCnt].MOTO_pos.z;

				switch(Obstacle_info[nCnt].LR_Judge)
				{
				case 1:
					g_posObstacle.x = -60.0f;
					break;
				case 2:
					g_posObstacle.x = 0.0f;
					break;
				case 3:
					g_posObstacle.x = 60.0f;		
					break;
				}

				//****���[���h�̐ݒ�****
				D3DXMatrixIdentity(&g_mtxWorldObstacle);
				D3DXMatrixScaling(&mtxScl,g_sclObstacle.x,
											g_sclObstacle.y,
											g_sclObstacle.z);			//�X�P�[���𔽉f

				D3DXMatrixMultiply(&g_mtxWorldObstacle,&g_mtxWorldObstacle,&mtxScl);

				//****���̑��̐ݒ�****
				D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotObstacle[nCnt].y,
												g_rotObstacle[nCnt].x,
												g_rotObstacle[nCnt].z);		//���|�@�s�b�`�@���[��

				D3DXMatrixMultiply(&g_mtxWorldObstacle,&g_mtxWorldObstacle,&mtxRot);
				D3DXMatrixTranslation(&mtxTranslate,g_posObstacle.x,g_posObstacle.y,g_posObstacle.z);	//�ʒu�𔽉f
				D3DXMatrixMultiply(&g_mtxWorldObstacle,&g_mtxWorldObstacle,&mtxTranslate);
	
				pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldObstacle);	//�ݒ�

				//=========�}�e���A���Ȃǂ̎擾=========
				//======================================
				pDevice -> GetMaterial(&matDef);
				pMat = (D3DXMATERIAL*)g_pBuffMatObstacle -> GetBufferPointer();

				for(int nCntMat = 0;nCntMat < (int)g_numMatObstacle;nCntMat++)
				{
					pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
					pDevice -> SetTexture(0,NULL);
					g_pMeshObstacle -> DrawSubset(nCntMat);
				}

				pDevice -> SetMaterial(&matDef);
			}
		}
	}
}

//================================
//�ʒu�Ɗp�x�̎擾�֐�
//================================

PLAYER_MODE GetObstacle_info(int num)
{
	return Obstacle_info[num];
}

