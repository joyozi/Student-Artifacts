//��-------------------------------------------------------------------------��
//
//	File	:�G01�����t�@�C��[Enemy01.cpp]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "enemy_01.h"
#include "obstacle.h"
#include "sound.h"
#include "model.h"
#include "camera.h"
#include "score.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 g_pTextureEnemy01;		//
LPD3DXMESH g_pMeshEnemy01;					//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatEnemy01;				//�}�e���A�����ւ̃|�C���^

DWORD g_numMatEnemy01;						//�}�e���A���̐�
D3DXVECTOR3 g_posEnemy01;					//���f���̈ʒu
D3DXVECTOR3 g_rotEnemy01;					//���f���̌���
D3DXVECTOR3 g_sclEnemy01;					//���f���̑傫��

D3DXMATRIX g_mtxWorldEnemy01;				//���[���h�}�g���b�N�X

PLAYER_MODE Enemy01_info[ENEMY01_NUM];		//�G01�̏�Q���̓���q

//��-------------------------------------------------------------------------��
//���f���̏���������
//��-------------------------------------------------------------------------��
void InitEnemy01(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//��Q���̍��W������@�w��
	int Enemy01_posX_ORIGINAL[ENEMY01_NUM] = {0,0,0,0,0,0,0,0,0,0,2,1,0,0,3,0,1,2,0,1,		//0~19
											2,0,1,3,0,0,0,0,3,0,1,0,0,0,1,2,3,1,3,0,		//20~39
											2,0,3,1,2,1,3,0,1,2,							//40~49
											2,0,1,2,0,1,2,3,0,0,							//50~59
											3,2,1,1,3,0,0,3,2,1,
											0,3,0,0,3,0,2,2,0,0,
											2,3,1,1,3,0,2,0,0,1,
											0,0,0,0,0,0,0,0,0,0};
	//��Q���̍��W�@���ς��Ȃ��@�y��
	float Enemy01_posZ_ORIGINAL[ENEMY01_NUM] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,				//0~19
												0,0,600,0,0,0,0,0,0,0,0,600,0,-600,0,0,0,0,-600,0,		//20~39
												0,0,0,0,-600,0,0,0,0,-600,								//40~49
												0,0,0,0,0,600,0,-600,0,0,								//50~59
												0,0,0,0,-600,0,0,0,600,0,
												0,0,0,0,0,0,0,0,0,0,
												0,0,0,600,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,0};

	for(int nCnt = 0;nCnt < ENEMY01_NUM;nCnt++)
	{
		//��Q���̈ʒu������
		Enemy01_info[nCnt].LR_Judge = Enemy01_posX_ORIGINAL[nCnt];
		Enemy01_info[nCnt].MOTO_pos.z = Enemy01_posZ_ORIGINAL[nCnt];

		//��Q���̕\�����������
//		Enemy01_info[nCnt].Thing_exist = Enemy01_Exist_ORIGINAL[nCnt];

		if(Enemy01_posX_ORIGINAL[nCnt] != 0)
		{
			Enemy01_info[nCnt].Thing_exist = true;
		}
		else
		{
			Enemy01_info[nCnt].Thing_exist = false;
		}

		//���l�̊ȗ����@��Q���ݒu�J�n�ʒu���v���X,�Ԋu�������Ă���
		Enemy01_info[nCnt].MOTO_pos.z = Enemy01_info[nCnt].MOTO_pos.z + OBSTACLE_SETTI_LINE + nCnt * 600;

		//�G01��HP������
		Enemy01_info[nCnt].Enemy_Damage = 4;
	}
	
	//****���f���̏��Z�b�g****
	D3DXLoadMeshFromX("./data/MODEL/obake_000.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatEnemy01,
					NULL,
					&g_numMatEnemy01,
					&g_pMeshEnemy01);

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posEnemy01 = D3DXVECTOR3(40.0f,20.0f,OBSTACLE_SETTI_LINE+500.0f);
	g_rotEnemy01 = D3DXVECTOR3(0.0f,D3DX_PI,0.0f);
	g_sclEnemy01 = D3DXVECTOR3(1.0f,1.0f,1.0f);
}
//��-------------------------------------------------------------------------��
//���f���̏I������
//��-------------------------------------------------------------------------��
void UninitEnemy01(void)
{
	//���b�V�����f���̃����[�X
	//==============================
	if(g_pMeshEnemy01 != NULL)
	{
		g_pMeshEnemy01 -> Release();
		g_pMeshEnemy01 = NULL;
	}
	
	//�o�b�t�@�}�b�g�̃����[�X
	//=============================
	if(g_pBuffMatEnemy01 != NULL)
	{
		g_pBuffMatEnemy01 -> Release();
		g_pBuffMatEnemy01 = NULL;
	}

	//�e�N�X�e���̃����[�X
	//=============================
	if(g_pTextureEnemy01 != NULL)
	{
		g_pTextureEnemy01 -> Release();
		g_pTextureEnemy01 = NULL;

	}
}
//��-------------------------------------------------------------------------��
//���f���̍X�V����
//��-------------------------------------------------------------------------��
void UpdateEnemy01(void)
{
	//�_���[�W����
	for(int nCnt = 0;nCnt < ENEMY01_NUM;nCnt++)
	{
		//�̗͂�0�ȉ��ɂȂ邩�ǂ���
		if(Enemy01_info[nCnt].Enemy_Damage <= 0)
		{
//			PlaySound(SOUND_LABEL_SE_SHOT);
			//�G01�̕\��������
			Enemy01_info[nCnt].Thing_exist = false;

			PlusScore(1000);


			Enemy01_info[nCnt].Enemy_Damage = 4;
		}
	}	
}
//��-------------------------------------------------------------------------��
//���f���̕`�揈��
//��-------------------------------------------------------------------------��
void DrawEnemy01(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//�}�b�g�̃f�t�H���g
	//��Q���̐������J��Ԃ�
	for(int nCnt = 0;nCnt < ENEMY01_NUM;nCnt++)
	{
		if(Enemy01_info[nCnt].Thing_exist == true)
		{
			//������ʒu�̂ݕ\�����邽�߂ɁA�\���͈͓̔���������`�悷��悤�ɂ���
			if(Getg_posModel().z - CAMERA_LONG < Enemy01_info[nCnt].MOTO_pos.z && Getg_posModel().z + CAMERA_LONG > Enemy01_info[nCnt].MOTO_pos.z)
			{
				g_posEnemy01.z = Enemy01_info[nCnt].MOTO_pos.z;

				switch(Enemy01_info[nCnt].LR_Judge)
				{
				case 1:
					g_posEnemy01.x = -60.0f;
					break;
				case 2:
					g_posEnemy01.x = 0.0f;
					break;
				case 3:
					g_posEnemy01.x = 60.0f;		
					break;
				}

				//****���[���h�̐ݒ�****
				D3DXMatrixIdentity(&g_mtxWorldEnemy01);
				D3DXMatrixScaling(&mtxScl,g_sclEnemy01.x,
											g_sclEnemy01.y,
											g_sclEnemy01.z);			//�X�P�[���𔽉f

				D3DXMatrixMultiply(&g_mtxWorldEnemy01,&g_mtxWorldEnemy01,&mtxScl);

				//****���̑��̐ݒ�****
				D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotEnemy01.y,
												g_rotEnemy01.x,
												g_rotEnemy01.z);		//���|�@�s�b�`�@���[��

				D3DXMatrixMultiply(&g_mtxWorldEnemy01,&g_mtxWorldEnemy01,&mtxRot);
				D3DXMatrixTranslation(&mtxTranslate,g_posEnemy01.x,g_posEnemy01.y,g_posEnemy01.z);	//�ʒu�𔽉f
				D3DXMatrixMultiply(&g_mtxWorldEnemy01,&g_mtxWorldEnemy01,&mtxTranslate);
	
				pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldEnemy01);	//�ݒ�

				//=========�}�e���A���Ȃǂ̎擾=========
				//======================================
				pDevice -> GetMaterial(&matDef);
				pMat = (D3DXMATERIAL*)g_pBuffMatEnemy01 -> GetBufferPointer();

				for(int nCntMat = 0;nCntMat < (int)g_numMatEnemy01;nCntMat++)
				{
					pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
					pDevice -> SetTexture(0,NULL);
					g_pMeshEnemy01 -> DrawSubset(nCntMat);
				}

				pDevice -> SetMaterial(&matDef);
			}
		}
	}
}
//======================================
//�G01�̊���̎󂯓n���֐�
//======================================
PLAYER_MODE GetEnemy01_info(int num)
{
	return Enemy01_info[num];
}

//�G01�̃_���[�W�����B������g���Ƒ̗͂�1����
void Enemy01_DamageCnt(int num)
{
	Enemy01_info[num].Enemy_Damage--;
}