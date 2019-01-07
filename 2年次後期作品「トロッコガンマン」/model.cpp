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
#include "model.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "meshfield.h"
#include "gameUI.h"
#include "obstacle.h"
#include "enemy_01.h"
#include "barricade.h"
#include "sound.h"
#include "fade.h"
#include "result.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 g_pTextureModel[MODEL_NUM];		//
LPD3DXMESH g_pMeshModel[MODEL_NUM];					//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel[MODEL_NUM];			//�}�e���A�����ւ̃|�C���^

DWORD g_numMatModel[MODEL_NUM];						//�}�e���A���̐�
D3DXVECTOR3 g_posModel[MODEL_NUM];					//���f���̈ʒu
D3DXVECTOR3 g_rotModel[MODEL_NUM];					//���f���̌���
D3DXVECTOR3 g_sclModel[MODEL_NUM];					//���f���̑傫��

D3DXMATRIX g_mtxWorldModel[MODEL_NUM];				//���[���h�}�g���b�N�X

D3DXMATRIX g_mtxWorldPlayer[MODEL_NUM];				//�v���C���[�}�g���b�N�X	5�Ԃ����f����������g_mtxWorldPlayer[5]�ɐe�̈ʒu��ۑ����Ă���

D3DXMATRIX p_GetTranslate[MODEL_NUM];				//���f���̈ʒu���݂̂�ۑ�����֐��@�e�̔��ˈʒu�ɗp����

int model_jump;										//�W�����v�̔���@0�Őڒn���@1�ŃW�����v��яオ�蒆�@2�ŗ�����

float Model_SpeedUP;								//�{�̂̃X�s�[�h�A�b�v�p�̕ϐ�

PLAYER_MODE p_Model_Original;						//���f���̃I���W�i���̏��
//��-------------------------------------------------------------------------��
//���f���̏���������
//��-------------------------------------------------------------------------��
void InitModel(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�W�����v��Ԃ̏�����
	model_jump = 0;

	//�X�s�[�h�A�b�v�̏�����
	Model_SpeedUP = 0.0f;

	//PLAYER_MODE�̏�����
	p_Model_Original.Jump_Judge = false;	//�W�����v���Ă��Ȃ�
	p_Model_Original.LR_Judge = 2;			//���S�ɂ���

	p_Model_Original.Model_Muteki = 1;		//���f���͒ʏ��Ԃł���

	//****���f���̏��Z�b�g****

	//�g���b�R�̃��f���ݒu	�e�ł���
	D3DXLoadMeshFromX("./data/MODEL/000_torokko.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[0],
					NULL,
					&g_numMatModel[0],
					&g_pMeshModel[0]);

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posModel[0] = D3DXVECTOR3(0.0f,8.0f,0.0f);
	g_rotModel[0] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclModel[0] = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//���́A���̃��f���ݒu	�e�̓g���b�R
	D3DXLoadMeshFromX("./data/MODEL/001_body.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[1],
					NULL,
					&g_numMatModel[1],
					&g_pMeshModel[1]);

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posModel[1] = D3DXVECTOR3(0.0f,15.0f,0.0f);
	g_rotModel[1] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclModel[1] = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//�O�ւ̃��f���ݒu	�e�̓g���b�R
	D3DXLoadMeshFromX("./data/MODEL/002_zenrin.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[2],
					NULL,
					&g_numMatModel[2],
					&g_pMeshModel[2]);

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posModel[2] = D3DXVECTOR3(0.0f,3.0f,13.0f);
	g_rotModel[2] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclModel[2] = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//��ւ̃��f���ݒu	�e�̓g���b�R
	D3DXLoadMeshFromX("./data/MODEL/003_kourin.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[3],
					NULL,
					&g_numMatModel[3],
					&g_pMeshModel[3]);

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posModel[3] = D3DXVECTOR3(0.0f,3.0f,-13.0f);
	g_rotModel[3] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclModel[3] = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//����̘r�̃��f���ݒu	�e�͓���
	D3DXLoadMeshFromX("./data/MODEL/004_ninoudeL.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[4],
					NULL,
					&g_numMatModel[4],
					&g_pMeshModel[4]);

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posModel[4] = D3DXVECTOR3(-3.0f,20.0f,0.0f);
	g_rotModel[4] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclModel[4] = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//�E��̘r�̃��f���ݒu	�e�͓���
	D3DXLoadMeshFromX("./data/MODEL/005_ninoudeR.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[5],
					NULL,
					&g_numMatModel[5],
					&g_pMeshModel[5]);

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posModel[5] = D3DXVECTOR3(3.0f,20.0f,0.0f);
	g_rotModel[5] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclModel[5] = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//����̏e�̃��f���ݒu	�e�͍���̘r
	D3DXLoadMeshFromX("./data/MODEL/006_juuL.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[6],
					NULL,
					&g_numMatModel[6],
					&g_pMeshModel[6]);

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posModel[6] = D3DXVECTOR3(-12.0f,1.6f,8.3f);
	g_rotModel[6] = D3DXVECTOR3(-D3DX_PI / 2,0.0f,0.0f);
	g_sclModel[6] = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//�E��̏e�̃��f���ݒu	�e�͉E��̘r
	D3DXLoadMeshFromX("./data/MODEL/007_juuR.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[7],
					NULL,
					&g_numMatModel[7],
					&g_pMeshModel[7]);

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posModel[7] = D3DXVECTOR3(12.0f,1.6f,8.3f);
	g_rotModel[7] = D3DXVECTOR3(-D3DX_PI / 2,0.0f,0.0f);
	g_sclModel[7] = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//�E��̏e�̃��f���ݒu	�e�͉E��̘r
	D3DXLoadMeshFromX("./data/MODEL/008_head.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[8],
					NULL,
					&g_numMatModel[8],
					&g_pMeshModel[8]);

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posModel[8] = D3DXVECTOR3(0.0f,25.0f,0.0f);
	g_rotModel[8] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclModel[8] = D3DXVECTOR3(1.0f,1.0f,1.0f);

}
//��-------------------------------------------------------------------------��
//���f���̏I������
//��-------------------------------------------------------------------------��
void UninitModel(void)
{
	for(int nCnt = 0;nCnt < MODEL_NUM;nCnt++)
	{
		//���b�V�����f���̃����[�X
		//==============================
		if(g_pMeshModel[nCnt] != NULL)
		{
			g_pMeshModel[nCnt] -> Release();
			g_pMeshModel[nCnt] = NULL;
		}
	
		//�o�b�t�@�}�b�g�̃����[�X
		//=============================
		if(g_pBuffMatModel[nCnt] != NULL)
		{
			g_pBuffMatModel[nCnt] -> Release();
			g_pBuffMatModel[nCnt] = NULL;
		}

		//�e�N�X�e���̃����[�X
		//=============================
		if(g_pTextureModel[nCnt] != NULL)
		{
			g_pTextureModel[nCnt] -> Release();
			g_pTextureModel[nCnt] = NULL;
		}
	}
}
//��-------------------------------------------------------------------------��
//���f���̍X�V����
//��-------------------------------------------------------------------------��
void UpdateModel(void)
{
	static float jump = 0.0f;	//�W�����v�̊����ړ��̌v�Z�p

	static int SpeedupCnt;

	//�����ɏ�����
	if(g_posModel[0].z <= OBSTACLE_SETTI_LINE)
	{
		SpeedupCnt = 1;
	}


	//�S�[���̔���
	if(g_posModel[0].z >= MODEL_GOAL)
	{
		//�t�@���t�@�[��
		PlaySound(SOUND_LABEL_FANFALE);

		SetResultJudge(true);
		SetFade(FADE_OUT);
	}

	//�X�s�[�h�A�b�v
	if(g_posModel[0].z >= OBSTACLE_SETTI_LINE + (600 * 20 * SpeedupCnt))
	{
		Model_SpeedUP +=0.5f;
		SpeedupCnt++;
	}

#ifdef _DEBUG	//�f�o�b�O�̂Ƃ��̓L�[���͂ňړ�
	if(GetKeyboardPress(DIK_W) == true)
#endif

	{
		//�O�i����
		g_posModel[0].z += MODEL_MOVE + Model_SpeedUP;
	}
#ifdef _DEBUG	//�f�o�b�O�̂Ƃ��̓L�[���͂ňړ�
	if(GetKeyboardPress(DIK_S) == true)
	{
		//�O�i����
		g_posModel[0].z -= MODEL_MOVE + Model_SpeedUP;
	}
#endif

	//�^�C������
	g_rotModel[2].x += MODE_WHEEL_ROT;
	g_rotModel[3].x += MODE_WHEEL_ROT;

	if(model_jump == 0)
	{
		//���ɌX����
		if(GetKeyboardPress(DIK_A) == true)
		{
			//���ɌX���Ă���Ƌ�����
			p_Model_Original.LR_Judge = 1;
		
			//�g���b�R���΂߂ɂ���
			g_posModel[0].x = -15.0f;
			g_posModel[0].y = 33.0f;
			g_rotModel[0].z = 1.2f;

			//�g�̂̈ʒu�����炷
			g_posModel[1].x = 0.0f;
			g_posModel[1].y = 25.0f;
			g_rotModel[1].z = -0.7f;

			//��̘r�A���̊p�x��ς���
			g_rotModel[4].z = -0.4f;
			g_rotModel[5].z = -0.15f;
			g_rotModel[8].z = -0.4f;
		}

		else if(GetKeyboardPress(DIK_D) == true)
		{
			//�E�ɌX���Ă���Ƌ�����
			p_Model_Original.LR_Judge = 3;

			//�g���b�R���΂߂ɂ���
			g_posModel[0].x = 15.0f;
			g_posModel[0].y = 33.0f;
			g_rotModel[0].z = -1.2f;

			//�g�̂̈ʒu�����炷
			g_posModel[1].x = 0.0f;
			g_posModel[1].y = 25.0f;
			g_rotModel[1].z = 0.7f;

			//��̘r�A���̊p�x��ς���
			g_rotModel[4].z = 0.15f;
			g_rotModel[5].z = 0.4f;
			g_rotModel[8].z = 0.4f;
		}
		else
		{
			//�X���Ă��Ȃ��Ƌ�����
			p_Model_Original.LR_Judge = 2;

			//�g���b�R�̈ʒu�����ɖ߂�
			g_posModel[0].x = 0.0f;
			g_posModel[0].y = 8.0f;
			g_rotModel[0].z = 0.0f;

			//�{�̂����ɖ߂�
			g_posModel[1].x = 0.0f;
			g_posModel[1].y = 15.0f;
			g_rotModel[1].z = 0.0f;

			//��̘r�A���̊p�x�����ɖ߂�
			g_rotModel[4].z = 0.0f;
			g_rotModel[5].z = 0.0f;
			g_rotModel[8].z = 0.0f;

			//���G��Ԃ̐ݒ肩�猳�ɖ߂�
			g_rotModel[0].x =0.0f;

		}
	}

	//�r�̏㉺�ړ�
	if(GetKeyboardPress(DIK_RETURN) == true)
	{
		if(g_rotModel[6].x < 0.0f)
		{
			g_rotModel[6].x += D3DX_PI / 6;
		}

		if(g_rotModel[7].x < 0.0f)
		{
			g_rotModel[7].x += D3DX_PI / 6;
		}
	}
	else
	{
		if(g_rotModel[6].x > -D3DX_PI / 2)
		{
			g_rotModel[6].x -= D3DX_PI / 6;
		}

		if(g_rotModel[7].x > -D3DX_PI / 2)
		{
			g_rotModel[7].x -= D3DX_PI / 6;
		}
	}

	if(p_Model_Original.Jump_Judge == true)
	{
		//�W�����v���Ă���Ƃ��́A���E�Ɉʒu�����点�Ȃ�
		//�W�����v���Ă���Ƌ�����
		p_Model_Original.Jump_Judge = true;
	}

	//�W�����v���[�V����
	if(model_jump == 0)
	{
		if(GetKeyboardTrigger(DIK_SPACE) == true)
		{
			//�X���Ă��Ȃ��Ƌ�����
			p_Model_Original.LR_Judge = 2;

			//*********���S�ł����W�����v�ł��Ȃ�************
			//�g���b�R�̈ʒu�����ɖ߂�
			g_posModel[0].x = 0.0f;
			g_posModel[0].y = 8.0f;
			g_rotModel[0].z = 0.0f;

			//�{�̂����ɖ߂�
			g_posModel[1].x = 0.0f;
			g_posModel[1].y = 15.0f;
			g_rotModel[1].z = 0.0f;

			//��̘r�A���̊p�x�����ɖ߂�
			g_rotModel[4].z = 0.0f;
			g_rotModel[5].z = 0.0f;
			g_rotModel[8].z = 0.0f;

			model_jump = 1;
			//�W�����v�̏���������
			jump = 12.0f;
		}
	}
	else if(model_jump == 1)	//�W�����v�㏸��
	{
		//�W�����v�̏d�͂ɂ��W�����v���x���グ��
		jump = jump * 0.9f;
		g_posModel[0].y += jump;
		
		if(g_posModel[0].y >= 60.0f)
		{
			model_jump = 2;

			//�������n�߂�
			jump = 0.05f;
		}
	}
	else if(model_jump == 2)	//�W�����v������
	{
		//�������x���グ�Ă���
		jump = jump * 1.15f;
		g_posModel[0].y -= jump;

		if(g_posModel[0].y <= 0.0f)
		{
			//������Ɩ��܂�̂ŏC������
			g_posModel[0].y= 0;
			model_jump = 0;

			//�W�����v���I������Ƌ�����
			p_Model_Original.Jump_Judge = false;
		}
	}
//=======================================================
//���G�ɂ��Ă̏���
//=======================================================

	static int MutekiCnt;	//���G���Ԃ��J�E���g����ϐ�	

	MutekiCnt++;			//�����ŃJ�E���g����@�ǂ����ʏ펞��0�ɂ��邩�炢��

	switch(p_Model_Original.Model_Muteki)
	{
	case 1:		//�ʏ��Ԃ�MutekiCnt���[���ɂ���
		MutekiCnt = 0;
		break;
	case 2:		//���G�A���ݏ��

		//�E�ӂ̕��������Ԃ��������狯�݂��甲����
		if(MutekiCnt >= 50)
		{
			p_Model_Original.Model_Muteki = 3;
			MutekiCnt = 0;
		}

		if(model_jump == 0)
		{	//�ڒn����������^�񒆂ł�����x�̍d��������
			//-------------------------------------
			//�g���b�R�̈ʒu�����ɖ߂�
			g_posModel[0].x = 0.0f;
			g_rotModel[0].z = 0.0f;

			//�{�̂����ɖ߂�
			g_posModel[1].x = 0.0f;
			g_posModel[1].y = 15.0f;
			g_rotModel[1].z = 0.0f;

			//��̘r�A���̊p�x�����ɖ߂�
			g_rotModel[4].z = 0.0f;
			g_rotModel[5].z = 0.0f;
			g_rotModel[8].z = 0.0f;

			g_posModel[0].y = 20.0f;
			g_rotModel[0].x = -0.5f;
			g_rotModel[6].x = -D3DX_PI / 2;
			g_rotModel[7].x = -D3DX_PI / 2;
			//--------------------------------------

		}
		else	//���̑��̃W�����v���������炻�̈ʒu�łȂȂ߂�
		{
			g_rotModel[0].x = -0.5f;
			g_rotModel[6].x = -D3DX_PI / 2;
			g_rotModel[7].x = -D3DX_PI / 2;
		}
		break;
	case 3:

		//���G��Ԃ̐ݒ肩�猳�ɖ߂�
		g_rotModel[0].x =0.0f;

		//�E�ӂ̕��������Ԃ��������疳�G���Ԃ��I����
		if(MutekiCnt >= 100)
		{
			p_Model_Original.Model_Muteki = 1;
		}
		break;
	}

	//�ŏI�I�ȃ��f���̈ʒu��ۑ����Ă���
	p_Model_Original.MOTO_pos = g_posModel[0];
}
//��-------------------------------------------------------------------------��
//���f���̕`�揈��
//��-------------------------------------------------------------------------��
void DrawModel(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	static int p_Playernum = 0;		//�v���C���[�̌��_�̑������Ă���ԍ��B g_mtxWorldPlayer[num]�̂���

	D3DXMATRIX Player_mtxScl,Player_mtxRot,Player_mtxTranslate;		//���_�̃}�g���b�N�X�p�̕ϐ�
	
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//�}�b�g�̃f�t�H���g
	
	for(int nCnt = 0;nCnt < MODEL_NUM;nCnt++)
	{
		//****���[���h�̐ݒ�****

		//==========�}�g���b�N�X�̏�����==========
		D3DXMatrixIdentity(&g_mtxWorldModel[nCnt]);

		//==========�X�P�[���̔��f================
		D3DXMatrixScaling(&mtxScl,g_sclModel[nCnt].x,g_sclModel[nCnt].y,g_sclModel[nCnt].z);
		D3DXMatrixMultiply(&g_mtxWorldModel[nCnt],&g_mtxWorldModel[nCnt],&mtxScl);

		//==========�p�x�̔��f====================
		D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotModel[nCnt].y,g_rotModel[nCnt].x,g_rotModel[nCnt].z);		//���|�@�s�b�`�@���[��
		D3DXMatrixMultiply(&g_mtxWorldModel[nCnt],&g_mtxWorldModel[nCnt],&mtxRot);

		//=========�ʒu�̔��f=====================
		D3DXMatrixTranslation(&mtxTranslate,g_posModel[nCnt].x,g_posModel[nCnt].y,g_posModel[nCnt].z);	//�ʒu�𔽉f
		D3DXMatrixMultiply(&g_mtxWorldModel[nCnt],&g_mtxWorldModel[nCnt],&mtxTranslate);

		//�e�̃}�g���b�N�X�@�~�@���̃}�g���b�N�X���s���B�������邱�ƂŌ��_�ɂ��Ă����悤�ɂȂ�
		//�g���b�R�͌��_(MD�ł���NULL)�����甽�f�����Ȃ�!
		//�g���b�R�����_�̂Ƃ�
		if(nCnt == 1 || nCnt == 2 || nCnt == 3)
		{
			D3DXMatrixMultiply(&g_mtxWorldModel[nCnt],&g_mtxWorldModel[nCnt],&g_mtxWorldPlayer[0]);
		}

		//���̂����_�̂Ƃ�
		else if(nCnt == 4 || nCnt == 5 || nCnt == 8)
		{
			D3DXMatrixMultiply(&g_mtxWorldModel[nCnt],&g_mtxWorldModel[nCnt],&g_mtxWorldPlayer[1]);
		}

		//����̘r�����_�̂Ƃ�
		else if(nCnt == 6)
		{
			D3DXMatrixMultiply(&g_mtxWorldModel[nCnt],&g_mtxWorldModel[nCnt],&g_mtxWorldPlayer[4]);
		}
		
		//�E��̘r�����_�̂Ƃ�
		else if(nCnt == 7)
		{
			D3DXMatrixMultiply(&g_mtxWorldModel[nCnt],&g_mtxWorldModel[nCnt],&g_mtxWorldPlayer[5]);
		}
		
		//���_�̃R�s�[������Ă��� ���E�̏e�́A�e���˂̂��߂̈ʒu�̕ۑ�
		if(nCnt == 0 /*�e�̓g���b�R*/|| nCnt == 1/*�g��*/ || nCnt == 4/*����̘r*/ || nCnt == 5/*�E��̘r*/ || nCnt == 6/*����̘r*/ || nCnt == 7/*�E��̘r*/)
		{
			//�e�̌��_���R�s�[���Ă���
			g_mtxWorldPlayer[nCnt] = g_mtxWorldModel[nCnt];
		}

		//BULLET�����̂��߂�
		//���e�ƉE�e�̈ʒu����ۑ�����
		if(nCnt == 6)
		{
			D3DXMatrixMultiply(&mtxTranslate,&mtxTranslate,&g_mtxWorldPlayer[4]);
			p_GetTranslate[6] = mtxTranslate;
		}
		//�E�e�̕ۑ�
		if(nCnt == 7)
		{
			D3DXMatrixMultiply(&mtxTranslate,&mtxTranslate,&g_mtxWorldPlayer[5]);
			p_GetTranslate[7] = mtxTranslate;
		}


		//=========���̃Z�b�g===================
		pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldModel[nCnt]);	//�ݒ�


		//���G��Ԃ̂Ƃ��͓_�ł�����
		static int Muteki_DisplayCnt;			//�_�ł̃J�E���g
		if(p_Model_Original.Model_Muteki == 1)
		{
			Muteki_DisplayCnt = 0;

			//=========�}�e���A���Ȃǂ̎擾=========
			//======================================
			pDevice -> GetMaterial(&matDef);
			pMat = (D3DXMATERIAL*)g_pBuffMatModel[nCnt] -> GetBufferPointer();

			for(int nCntMat = 0;nCntMat < (int)g_numMatModel[nCnt];nCntMat++)
			{
				pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
				pDevice -> SetTexture(0,NULL);
				g_pMeshModel[nCnt] -> DrawSubset(nCntMat);
			}

			pDevice -> SetMaterial(&matDef);

		}
		else if(p_Model_Original.Model_Muteki != 1)
		{
			Muteki_DisplayCnt++;

			if(Muteki_DisplayCnt % 120 >= 60)
			{
				//=========�}�e���A���Ȃǂ̎擾=========
				//======================================
				pDevice -> GetMaterial(&matDef);
				pMat = (D3DXMATERIAL*)g_pBuffMatModel[nCnt] -> GetBufferPointer();

				for(int nCntMat = 0;nCntMat < (int)g_numMatModel[nCnt];nCntMat++)
				{
					pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
					pDevice -> SetTexture(0,NULL);
					g_pMeshModel[nCnt] -> DrawSubset(nCntMat);
				}

				pDevice -> SetMaterial(&matDef);
			}
		}
	}
}

//=====================================
//�{�̂̂����蔻��
//=====================================
void ModelHITJUDGE(void)
{
	PLAYER_MODE Model_JudgeIreko;		//�{�̂̂����蔻��ɗp�������q

	//�ʏ��Ԃ̂Ƃ����������蔻����s��
	if(p_Model_Original.Model_Muteki == 1)
	{

		//�܂��A��Ƃ̂����蔻��
		//��Q���̐������J��Ԃ�
		for(int ObjectCnt = 0;ObjectCnt < OBSTACLE_NUM;ObjectCnt++)
		{
			//��Q���̈ʒu��������
			Model_JudgeIreko = GetObstacle_info(ObjectCnt);

			//���Ȃ画����s��
			if(Model_JudgeIreko.Thing_exist == true)
			{
				//�܂��AZ���̂����蔻��  
				if(g_posModel[0].z >= Model_JudgeIreko.MOTO_pos.z - 60 &&
					g_posModel[0].z <= Model_JudgeIreko.MOTO_pos.z + 30)
				{
					//X���̂����蔻��
					if(p_Model_Original.LR_Judge == Model_JudgeIreko.LR_Judge)
					{
						//�����܂ŗ���Ɠ����Ă�̂ł��̏���������
						PlaySound(SOUND_LABEL_DAMAGE_SE);
						p_Model_Original.Model_Muteki = 2;			//���G�ɂ���
						HitPointCNT();								//�_���[�W��H�炤
					}
				}
			}
		}

		//�G01�Ƃ̂����蔻��
		//�G01�̐������J��Ԃ�
		for(int Enemy01Cnt = 0;Enemy01Cnt < ENEMY01_NUM;Enemy01Cnt++)
		{
			//��Q���̈ʒu��������
			Model_JudgeIreko = GetEnemy01_info(Enemy01Cnt);

			//���Ȃ画����s��
			if(Model_JudgeIreko.Thing_exist == true)
			{
				//�܂��AZ���̂����蔻��  
				if(g_posModel[0].z >= Model_JudgeIreko.MOTO_pos.z - 60 &&
					g_posModel[0].z <= Model_JudgeIreko.MOTO_pos.z + 30)
				{
					//X���̂����蔻��
					if(p_Model_Original.LR_Judge == Model_JudgeIreko.LR_Judge)
					{
						//�����܂ŗ���Ɠ����Ă�̂ł��̏���������
						PlaySound(SOUND_LABEL_DAMAGE_SE);
						p_Model_Original.Model_Muteki = 2;			//���G�ɂ���
						HitPointCNT();								//�_���[�W��H�炤
					}
				}
			}
		}

		//�o���P�[�h�Ƃ̂����蔻��BZ����Y�����ׂ�
		for(int BarricadeCnt = 0;BarricadeCnt < BARRICADE_NUM;BarricadeCnt++)
		{
			//��Q���̈ʒu��������
			Model_JudgeIreko = GetBarricade_info(BarricadeCnt);

			//���Ȃ画����s��
			if(Model_JudgeIreko.Thing_exist == true)
			{
				//�܂��AZ���̂����蔻��  
				if(g_posModel[0].z >= Model_JudgeIreko.MOTO_pos.z - 20 &&
					g_posModel[0].z <= Model_JudgeIreko.MOTO_pos.z + 20)
				{
					//Y���̂����蔻��@�{�̂����̍��������������瓖����
					if(g_posModel[0].y < 45.0f)
					{
						//�����܂ŗ���Ɠ����Ă�̂ł��̏���������
						p_Model_Original.Model_Muteki = 2;			//���G�ɂ���
						HitPointCNT();								//�_���[�W��H�炤
					}
				}
			}
		}
	}
}

//================================
//�ʒu�Ɗp�x�̎擾�֐�
//================================
D3DXVECTOR3 Getg_posModel(void)
{
	//�e���f���̈ʒu��������
	return g_posModel[0];
}

D3DXVECTOR3 Getg_rotModel(void)
{
	//�e���f���̊p�x��������
	return g_rotModel[0];
}

//���̏e�̈ʒu�̎擾�֐��@��{�I�Ƀo���b�g�Ŏg��
D3DXMATRIX GetTranslate_juuL(void)
{
	return p_GetTranslate[6];
}

//�E�̏e�̈ʒu�̎擾�֐�
D3DXMATRIX GetTranslate_juuR(void)
{
	return p_GetTranslate[7];
}

//�����蔻��Ƃ��̂��߂Ɉʒu��������֐�
PLAYER_MODE GetModelOriginal(void)
{
	return p_Model_Original;
}

//�o���b�g�Ɏ����Ă����X�s�[�h�A�b�v�ϐ�
float GetModel_SpeedUP(void)
{
	return Model_SpeedUP;
}
