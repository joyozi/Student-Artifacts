//��-------------------------------------------------------------------------��
//
//	File	:���b�V���J�[�u�t�@�C��[meshcave.cpp]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "meshcave.h"
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
LPDIRECT3DTEXTURE9 g_pTextureMeshCave;				//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCave;		//

LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCave;			//

D3DXVECTOR3 g_posMeshCave;						//���f���̈ʒu
D3DXVECTOR3 g_rotMeshCave;						//���f���̌���
D3DXVECTOR3 g_sclMeshCave;						//���f���̑傫��

D3DXMATRIX g_mtxProjectionMeshCave;			//�v���W�F�N�V�����}�g���b�N�X
D3DXMATRIX g_mtxViewMeshCave;					//�r���[�}�g���b�N�X
D3DXMATRIX g_mtxWorldMeshCave;					//���[���h�}�g���b�N�X

D3DXVECTOR3 g_posMeshCaveP;					//�J�����̎��_
D3DXVECTOR3 g_posMeshCaveR;					//�J�����̒����_
D3DXVECTOR3 g_posMeshCaveU;					//�J�����̏�����x�N�g��

//��-------------------------------------------------------------------------��
//���b�V���J�[�u����������
//��-------------------------------------------------------------------------��
void InitMeshCave(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	VERTEX_3D *pVtx;

	WORD *pIdx;
	
	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posMeshCave = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_rotMeshCave = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclMeshCave = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//***�J�����̏�����***
	g_posMeshCaveP = D3DXVECTOR3(0.0f,0.0f,0.0f);		//�J�����̎��_
	g_posMeshCaveR = D3DXVECTOR3(0.0f,0.0f,0.0f);		//�J�����̒����_
	g_posMeshCaveU = D3DXVECTOR3(0.0f,1.0f,0.0f);		//�J�����̏�����x�N�g��


	//***�e�N�X�e���̓ǂݍ���***
	D3DXCreateTextureFromFile(GetDevice(),CAVE_TEXTURE_FILE,&g_pTextureMeshCave);

	//***���_���̐ݒ�***
	//****���_�o�b�t�@�̐ݒ�****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*CAVE_MESH_VTX_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffMeshCave,NULL);

	//****�C���f�b�N�X�o�b�t�@�̊m��****
	pDevice -> CreateIndexBuffer(sizeof(WORD) * CAVE_MESH_INDEX_NUM,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&g_pIdxBuffMeshCave,NULL);

	//===================���_�o�b�t�@�f�[�^�����b�N==========================
	g_pVtxBuffMeshCave->Lock(0,0,(void**)&pVtx,0);
	
	//****���_�̈ʒu�̐ݒ�****
//	int ChangeCntX = 0;																			//�c���̐؂�ւ��̂Ƃ��Ɏg�p����ϐ�
	int ChangeCntZ = 0;
	float VtxCntx = (CAVE_MESH_TYOKKEI / 2) - (CAVE_MESH_POYGON_LENGTH * CAVE_TYOKUSEN);		//X���̈�ԉE�̍��W
	float VtxCnty = 0;																			//Y��
	float VtxCntz = (CAVE_MESH_OKU_LONG / 2);													//Z���̈�ԉ��̍��W

	float cave_rad = 0.0f;																		//���A���Ȃ���p�x
	int cave_Cnt = 0;																			//���A�̒[�����������ɂ���J�E���g

	//���_�����J��Ԃ�
	for(long nCnt = 0;nCnt < CAVE_MESH_VTX_NUM;nCnt++)
	{
		//�ŏ��ɑ��
		pVtx[nCnt].pos = D3DXVECTOR3(VtxCntx,VtxCnty,VtxCntz);


		//-----���A�̒[�𒼐��ɂ���-----------
		cave_Cnt++;
		//�K��l�͈͓̔��ł̂݁A�w����ω������ē��A�̒[�𒼐��I�ɂ���
		if(cave_Cnt > CAVE_TYOKUSEN && cave_Cnt <= CAVE_MESH_TEXTURE_TYOKKEI - CAVE_TYOKUSEN)
		{	
			//X���ɍ��ɃV�t�g
			VtxCntx -= CAVE_MESH_TYOKKEI / CAVE_MESH_TEXTURE_TYOKKEI;
		}

		//Y���̊p�x��ς���
		cave_rad += D3DX_PI / (CAVE_MESH_TEXTURE_TYOKKEI);

		//y����ς���
		VtxCnty = sinf(cave_rad) * (CAVE_MESH_TYOKKEI/2);
		
		ChangeCntZ++;

		//nCnt�����[�̐��l�ɒB������X�����[�̐��l�ɖ߂��āAZ������ɂ��낷�B
		if(ChangeCntZ > CAVE_MESH_TEXTURE_TYOKKEI)
		{
			VtxCntx = (CAVE_MESH_TYOKKEI / 2) - (CAVE_MESH_POYGON_LENGTH * CAVE_TYOKUSEN);
			VtxCnty = 0;
			VtxCntz -= CAVE_MESH_POYGON_LENGTH;
			ChangeCntZ = 0;
			cave_Cnt = 0;
			cave_rad = 0.0f;
		}
	}



		//�@���̐ݒ�̊J�n

	D3DXVECTOR3 Vec0;
	D3DXVECTOR3 Vec1;
	D3DXVECTOR3 normal;

	int VtxX = 0;		//X���_�p

	//���������p�̎O�p�`�A�E�オ���p�̎O�p�`�̏��Ō��݂ɂ���Ă���

	for(int nCntY = 0;nCntY < CAVE_MESH_TEXTURE_NUM_OKULONG;nCntY++)
	{	//Y���̒��_�����J��Ԃ�

		for(int nCntX = 0;nCntX < CAVE_MESH_TEXTURE_TYOKKEI * 2;nCntX++)
		{	//X���̒��_�����J��Ԃ�
			if(nCntX % 2 == 0)
			{
				//���������p�̎O�p�`
				Vec0 = pVtx[(nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1)) + VtxX + (CAVE_MESH_TEXTURE_TYOKKEI + 1)].pos - pVtx[(nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1)) + VtxX].pos;
				Vec1 = pVtx[(nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1)) + VtxX].pos - pVtx[(nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1)) + VtxX + (CAVE_MESH_TEXTURE_TYOKKEI + 1) + 1].pos;
			}
			else if(nCntX % 2 == 1)
			{
				//�E�オ���p�̎O�p�`
				Vec0 = pVtx[(nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1)) + VtxX + 1].pos - pVtx[(nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1)) + VtxX].pos;
				Vec1 = pVtx[(nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1)) + VtxX + (CAVE_MESH_TEXTURE_TYOKKEI + 1) + 1].pos - pVtx[(nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1)) + VtxX].pos;

				VtxX++;
			}

			//�@�������߂Đ��K������
			D3DXVec3Cross(&normal,&Vec0,&Vec1);
			D3DXVec3Normalize(&normal,&normal);

			pVtx[nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1) + VtxX].nor = normal;

			if(nCntY == (CAVE_MESH_TEXTURE_TYOKKEI - 1))
			{	//�Ō�̂x���W�ł͈�ԉ��̌v�Z������Ȃ��̂ň��̖@�����Ԃ�����
				pVtx[nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1) + VtxX + (CAVE_MESH_TEXTURE_TYOKKEI + 1)].nor = normal;
			}
		}

		VtxX = 0;
	}


	//****�����̐ݒ�*****
	for(int nCnt = 0;nCnt < CAVE_MESH_VTX_NUM;nCnt++)
	{
//		pVtx[nCnt].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	}



	//****�J���[�̐ݒ�****
	for(int nCnt = 0;nCnt < CAVE_MESH_VTX_NUM;nCnt++)
	{
		pVtx[nCnt].col = D3DCOLOR_RGBA(255,255,255,55);
	}

	//****tex�̐ݒ�****
	float TexCntx = 0.0f;	//tex�ł̂ݎg��
	float TexCnty = 0.0f;	//tex�ł̂ݎg��

	for(int nCnt = 0;nCnt < CAVE_MESH_VTX_NUM;nCnt++)
	{
		pVtx[nCnt].tex = D3DXVECTOR2(TexCntx,TexCnty);
		TexCntx += 1.0f;

		if(TexCntx > CAVE_MESH_TEXTURE_TYOKKEI)
		{
			TexCntx = 0.0f;
			TexCnty += 1.0f;
		}
	}

	//============���_�o�b�t�@�f�[�^�̃��b�N����============
	g_pVtxBuffMeshCave->Unlock();
	
	//============�C���f�b�N�X����ݒ�====================
	g_pIdxBuffMeshCave -> Lock(0,0,(void**)&pIdx,0);

	//****pIdx�ւ̒i������****
	int IdxNum = -1;
	int IdxdansuuCnt = 1;
	for(int nCnt = 0;nCnt < CAVE_MESH_INDEX_NUM;nCnt++)
	{
		if(nCnt % 2 == 0)
		{
			IdxNum += (2 + CAVE_MESH_TEXTURE_TYOKKEI);
		}
		else
		{
			IdxNum -= (1 + CAVE_MESH_TEXTURE_TYOKKEI);
		}

		//�d�˂�|���S���������狭���Ƀ_�u�点�� IdxdansuuCnt�� 2,5,
		//���AIdxNum�����_���ȏ�ɂȂ�����ʂ��Ȃ��B�����Ă��܂��ƃu���[�N�|�C���g����������
		//�����C���f�b�N�X�����K��l��蒴���Ă��܂��ƁA�u���[�N�|�C���g���������Ă��܂�
		if(IdxNum == CAVE_MESH_TEXTURE_TYOKKEI * IdxdansuuCnt + IdxdansuuCnt -1 && IdxdansuuCnt < CAVE_MESH_TEXTURE_NUM_OKULONG)
		{
			//�܂���̒��_�𓯂��Ƃ���ɃZ�b�g����
			pIdx[nCnt] = IdxNum;
			pIdx[nCnt + 1] = IdxNum;
			//�����̂Ƃ���Ɉړ����Ă���Z�b�g����B
			IdxNum += (2 + CAVE_MESH_TEXTURE_TYOKKEI);
			pIdx[nCnt + 2] = IdxNum;

			//�O���������̂�3�𑫂��@����pIdx[nCnt] = IdxNum�Ō��ʓI�ɓ����Ƃ���̐��l��������
			nCnt += 3;

			//Z�������ɃV�t�g����
			IdxdansuuCnt++;
		}

		pIdx[nCnt] = IdxNum;
	}

	//============�C���f�b�N�X�o�b�t�@�̃��b�N����============
	g_pIdxBuffMeshCave -> Unlock();
}

//��---------------------------------��
//���b�V���J�[�u�I������
//��---------------------------------��
void UninitMeshCave(void)
{
	//****�e�탊���[�X����****
	if(g_pVtxBuffMeshCave != NULL)
	{
		g_pVtxBuffMeshCave -> Release();
		g_pVtxBuffMeshCave = NULL;
	}
	
	//�e�N�X�`���̏���
	if(g_pTextureMeshCave != NULL)
	{
		g_pTextureMeshCave->Release();
		g_pTextureMeshCave = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̃����[�X
	if(g_pIdxBuffMeshCave != NULL)
	{
		g_pIdxBuffMeshCave->Release();
		g_pIdxBuffMeshCave = NULL;
	}
}
//��---------------------------------��
//���b�V���J�[�u�̍X�V����
//��---------------------------------��
void UpdateMeshCave(void)
{
	//���f���̈ʒu�����̈ʒu���傫���Ȃ�����|���S���̑傫������������O�i������
	//����ŏ����i���ɑ����悤�ɂȂ�
	while(Getg_posModel().z > g_posMeshCave.z)
	{
		g_posMeshCave.z += CAVE_MESH_POYGON_LENGTH;
	}
}

//��---------------------------------��
//���b�V���J�[�u�̕`�揈��
//��---------------------------------��
void DrawMeshCave(void)
{
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	//****���[���h�̐ݒ�****
	D3DXMatrixIdentity(&g_mtxWorldMeshCave);
	D3DXMatrixScaling(&mtxScl,g_sclMeshCave.x,
								g_sclMeshCave.y,
								g_sclMeshCave.z);			//�X�P�[���𔽉f

	D3DXMatrixMultiply(&g_mtxWorldMeshCave,&g_mtxWorldMeshCave,&mtxScl);

	//****���̑��̐ݒ�****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotMeshCave.y,
									g_rotMeshCave.x,
									g_rotMeshCave.z);		//���|�@�s�b�`�@���[��

	D3DXMatrixMultiply(&g_mtxWorldMeshCave,&g_mtxWorldMeshCave,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,g_posMeshCave.x,g_posMeshCave.y,g_posMeshCave.z);	//�ʒu�𔽉f
	D3DXMatrixMultiply(&g_mtxWorldMeshCave,&g_mtxWorldMeshCave,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldMeshCave);	//�ݒ�

	//-----------------------3D�|���S���̕`��-------------
	//���_�o�b�t�@���o�C���h
	pDevice->SetStreamSource(0,g_pVtxBuffMeshCave,0,sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���o�C���h
	pDevice -> SetIndices(g_pIdxBuffMeshCave);		//�C���f�b�N�X�o�b�t�@���o�C���h
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,g_pTextureMeshCave);
	//�|���S���̕`��
	pDevice -> DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,CAVE_MESH_VTX_NUM,0,CAVE_MESH_POLYGON_NUM);
	//----------------------------------------------------
}
