//��-------------------------------------------------------------------------��
//
//	File	:�t�@�C��[meshfield.cpp]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "meshfield.h"
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
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;				//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;		//

LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;			//

D3DXVECTOR3 g_posMeshfield;						//���f���̈ʒu
D3DXVECTOR3 g_rotMeshfield;						//���f���̌���
D3DXVECTOR3 g_sclMeshfield;						//���f���̑傫��

D3DXMATRIX g_mtxProjectionMeshfield;			//�v���W�F�N�V�����}�g���b�N�X
D3DXMATRIX g_mtxViewMeshfield;					//�r���[�}�g���b�N�X
D3DXMATRIX g_mtxWorldMeshfield;					//���[���h�}�g���b�N�X

D3DXVECTOR3 g_posMeshfieldP;					//�J�����̎��_
D3DXVECTOR3 g_posMeshfieldR;					//�J�����̒����_
D3DXVECTOR3 g_posMeshfieldU;					//�J�����̏�����x�N�g��

float cavelong_back;							//���A�̈�Ԍ��̍��W

//��-------------------------------------------------------------------------��
//����������
//��-------------------------------------------------------------------------��
void InitMeshfield(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	VERTEX_3D *pVtx;
	WORD *pIdx;
	
	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posMeshfield = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_rotMeshfield = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclMeshfield = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//***�J�����̏�����***
	g_posMeshfieldP = D3DXVECTOR3(0.0f,0.0f,0.0f);		//�J�����̎��_
	g_posMeshfieldR = D3DXVECTOR3(0.0f,0.0f,0.0f);		//�J�����̒����_
	g_posMeshfieldU = D3DXVECTOR3(0.0f,1.0f,0.0f);		//�J�����̏�����x�N�g��


	//***���_���̐ݒ�***
	//****���_�o�b�t�@�̐ݒ�****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*MESH_VTX_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffMeshField,NULL);

	//****�C���f�b�N�X�o�b�t�@�̊m��****
	pDevice -> CreateIndexBuffer(sizeof(WORD) * MESH_INDEX_NUM,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&g_pIdxBuffMeshField,NULL);

	//***�e�N�X�e���̓ǂݍ���***
	D3DXCreateTextureFromFile(pDevice,"./data/TEXTURE/wall_002.jpg",&g_pTextureMeshField);

	//===================���_�o�b�t�@�f�[�^�����b�N==========================
	g_pVtxBuffMeshField->Lock(0,0,(void**)&pVtx,0);
	
	//****���_�̈ʒu�̐ݒ�****
	int ChangeCntX = 1;										//�c���̐؂�ւ��̂Ƃ��Ɏg�p����ϐ�
	int ChangeCntZ = 0;
	int VtxCntx = -(MESH_LENGTH_YOKO / 2);					//X���̈�ԍ��̍��W
	int VtxCnty = 0;										//Y��
	int VtxCntz = MESH_LENGTH_OKU / 2;						//Z���̈�ԉ��̍��W

	//���_�����J��Ԃ�
	for(int nCnt = 0;nCnt < MESH_VTX_NUM;nCnt++)
	{
		//�ŏ��ɑ��
		pVtx[nCnt].pos = D3DXVECTOR3(VtxCntx,VtxCnty,VtxCntz);

		//X���ɍ��ɃV�t�g
		VtxCntx += MESH_POYGON_LENGTH;

		ChangeCntZ++;

		//nCnt�����[�̐��l�ɒB������X�����[�̐��l�ɖ߂��āAZ������ɂ��낷�B
		if(ChangeCntZ > MESH_TEXTURE_YOKONUM)
		{
			VtxCntx = -(MESH_LENGTH_YOKO / 2);
			VtxCntz -= MESH_LENGTH_OKU / MESH_TEXTURE_OKUNUM;
			ChangeCntZ = 0;
		}
	}

	//****�����̐ݒ�*****
	for(int nCnt = 0;nCnt < MESH_VTX_NUM;nCnt++)
	{
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	}
	//****�J���[�̐ݒ�****
	for(int nCnt = 0;nCnt < MESH_VTX_NUM;nCnt++)
	{
		pVtx[nCnt].col = D3DCOLOR_RGBA(255,255,255,55);
	}

	//****tex�̐ݒ�****
	float TexCntx = 0.0f;	//tex�ł̂ݎg��
	float TexCnty = 0.0f;	//tex�ł̂ݎg��

	for(int nCnt = 0;nCnt < MESH_VTX_NUM;nCnt++)
	{
		pVtx[nCnt].tex = D3DXVECTOR2(TexCntx,TexCnty);
		TexCntx += 1.0f;

		if(TexCntx >= MESH_TEXTURE_YOKONUM + 1)
		{
			TexCntx = 0.0f;
			TexCnty += 1.0f;
		}
	}

	//============���_�o�b�t�@�f�[�^�̃��b�N����============
	g_pVtxBuffMeshField->Unlock();
	
	//============�C���f�b�N�X����ݒ�====================
	g_pIdxBuffMeshField -> Lock(0,0,(void**)&pIdx,0);

	//****pIdx�ւ̒i������****
	int IdxNum = -1;
	int IdxdansuuCnt = 1;		//�y���ւ̃V�t�g�̃J�E���g
	for(int nCnt = 0;nCnt < MESH_INDEX_NUM;nCnt++)
	{
		if(nCnt % 2 == 0)
		{
			IdxNum += (2 + MESH_TEXTURE_YOKONUM);
		}
		else
		{
			IdxNum -= (1 + MESH_TEXTURE_YOKONUM);
		}

		//�d�˂�|���S���������狭���Ƀ_�u�点�� IdxdansuuCnt�� 2,5,
		//���AIdxdansuuCnt���i���ȏ�ɂȂ�����ʂ��Ȃ��B�����Ă��܂��ƃu���[�N�|�C���g����������
		//�����C���f�b�N�X�����K��l��蒴���Ă��܂��ƁA�u���[�N�|�C���g���������Ă��܂�
		if(IdxNum == MESH_TEXTURE_YOKONUM * IdxdansuuCnt + IdxdansuuCnt -1 && IdxdansuuCnt < MESH_TEXTURE_OKUNUM)
		{
			//�܂���̒��_�𓯂��Ƃ���ɃZ�b�g����
			pIdx[nCnt] = IdxNum;
			pIdx[nCnt + 1] = IdxNum;
			//�����̂Ƃ���Ɉړ����Ă���Z�b�g����B
			IdxNum += (2 + MESH_TEXTURE_YOKONUM);
			pIdx[nCnt + 2] = IdxNum;

			//�O���������̂�3�𑫂��@����pIdx[nCnt] = IdxNum�Ō��ʓI�ɓ����Ƃ���̐��l��������
			nCnt += 3;

			//Z�������ɃV�t�g����
			IdxdansuuCnt++;
		}

		pIdx[nCnt] = IdxNum;
	}

	//============�C���f�b�N�X�o�b�t�@�̃��b�N����============
	g_pIdxBuffMeshField -> Unlock();
}

//��---------------------------------��
//�I������
//��---------------------------------��
void UninitMeshfield(void)
{
	//****�e�탊���[�X����****
	if(g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField -> Release();
		g_pVtxBuffMeshField = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̃����[�X
	if(g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField -> Release();
		g_pIdxBuffMeshField = NULL;
	}

	//�e�N�X�`���̏���
	if(g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

}
//��---------------------------------��
//�̍X�V����
//��---------------------------------��
void UpdateMeshfield(void)
{
	//���f���̈ʒu�����̈ʒu���傫���Ȃ�����|���S���̑傫������������O�i������
	//����ŏ����i���ɑ����悤�ɂȂ�
	while(Getg_posModel().z > g_posMeshfield.z)
	{
		g_posMeshfield.z += MESH_POYGON_LENGTH;
	}

}

//��---------------------------------��
//�̕`�揈��
//��---------------------------------��
void DrawMeshfield(void)
{
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	//****���[���h�̐ݒ�****
	D3DXMatrixIdentity(&g_mtxWorldMeshfield);
	D3DXMatrixScaling(&mtxScl,g_sclMeshfield.x,
								g_sclMeshfield.y,
								g_sclMeshfield.z);			//�X�P�[���𔽉f

	D3DXMatrixMultiply(&g_mtxWorldMeshfield,&g_mtxWorldMeshfield,&mtxScl);

	//****���̑��̐ݒ�****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotMeshfield.y,
									g_rotMeshfield.x,
									g_rotMeshfield.z);		//���|�@�s�b�`�@���[��

	D3DXMatrixMultiply(&g_mtxWorldMeshfield,&g_mtxWorldMeshfield,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,g_posMeshfield.x,g_posMeshfield.y,g_posMeshfield.z);	//�ʒu�𔽉f
	D3DXMatrixMultiply(&g_mtxWorldMeshfield,&g_mtxWorldMeshfield,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldMeshfield);	//�ݒ�

//----------------------3D�|���S���̕`��--------------------------

	//���_�o�b�t�@�̃o�C���h
	pDevice->SetStreamSource(0,g_pVtxBuffMeshField,0,sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���o�C���h
	pDevice -> SetIndices(g_pIdxBuffMeshField);		//�C���f�b�N�X�o�b�t�@���o�C���h
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,g_pTextureMeshField);
	//�|���S���̕`��
	pDevice -> DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,MESH_VTX_NUM,0,MESH_POLYGON_NUM);

//-----------------------------------------------------------------
}
