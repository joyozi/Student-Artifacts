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
#include "meshsky.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��		
#define MESHSKY_TEXTURE_FILE	("./data/TEXTURE/kirisuto_000.jpg")

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 g_pTextureMeshsky;			//

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshsky;		//
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshsky;		//

D3DXVECTOR3 g_posMeshsky;						//���f���̈ʒu
D3DXVECTOR3 g_rotMeshsky;						//���f���̌���
D3DXVECTOR3 g_sclMeshsky;						//���f���̑傫��

D3DXMATRIX g_mtxProjectionMeshsky;				//�v���W�F�N�V�����}�g���b�N�X
D3DXMATRIX g_mtxViewMeshsky;					//�r���[�}�g���b�N�X
D3DXMATRIX g_mtxWorldMeshsky;					//���[���h�}�g���b�N�X

//��-------------------------------------------------------------------------��
//���b�V���X�J�C����������
//��-------------------------------------------------------------------------��
void InitMeshsky(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	VERTEX_3D *pVtx;
	WORD *pIdx;	
	
	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posMeshsky = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_rotMeshsky = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclMeshsky = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//***�e�N�X�e���̓ǂݍ���***
	D3DXCreateTextureFromFile(pDevice,MESHSKY_TEXTURE_FILE,&g_pTextureMeshsky);

	//***���_���̐ݒ�***
	//****���_�o�b�t�@�̐ݒ�****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*MESHSKY_VTX_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffMeshsky,NULL);

	//****�C���f�b�N�X�o�b�t�@�̊m��****
	pDevice -> CreateIndexBuffer(sizeof(WORD) * MESHSKY_INDEX_NUM,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&g_pIdxBuffMeshsky,NULL);

	//===================���_�o�b�t�@�f�[�^�����b�N==========================
	g_pVtxBuffMeshsky->Lock(0,0,(void**)&pVtx,0);
	
	//****���_�̈ʒu�̐ݒ�****
	int ChangeCntX = 0;				//�c���̐؂�ւ��̂Ƃ��Ɏg�p����ϐ�
	int ChangeCntY = 0;
	int ChangeCntZ = 0;
	
	float sky_rad = 0;				//XZ���̉摜�̉�]�̂��˂�
	
	float sky_radY = 0.0f;			//�c�̔��X�~�̊p�x�̕ϐ�

	//-------���W�̏����l�v�Z------------
	
	float VtxCntx = -cosf(sky_rad) * (MESHSKY_DIAMETER);	//X���̈�ԍ��̍��W
	float VtxCnty = MESHSKY_HEIGHT;							//Y���̈�ԏ�
	float VtxCntz = sinf(sky_rad) * (MESHSKY_DIAMETER);		//Z���̈�ԉ��̍��W �O�p�֐��~���a
	
	//----------------------------------

	//���_�����J��Ԃ�
	for(int nCnt = 0;nCnt < MESHSKY_VTX_NUM;nCnt++)
	{		
		//X���ɉE�ɃV�t�g
		VtxCntx = -cosf(sky_rad) * (MESHSKY_DIAMETER) * sinf(sky_radY);
		//Z���̈ʒu���~��ɕς��� 
		VtxCntz = sinf(sky_rad) * (MESHSKY_DIAMETER) * sinf(sky_radY);

		//�ŏ��ɑ��
		pVtx[nCnt].pos = D3DXVECTOR3(VtxCntx,VtxCnty,VtxCntz);

		//�p�x��ς���
		sky_rad += ((D3DX_PI * 2) / MESHSKY_YOKO_VTX);
		
		//�����̉摜��\��������AY���Ɉ�i�����邽�߂̃J�E���g
		ChangeCntX++;

		//nCnt�����[�̐��l�ɒB������X�����[�̐��l�ɖ߂��āAZ������ɂ��낷�B
		if(ChangeCntX > MESHSKY_YOKO_VTX)
		{
			sky_radY += D3DX_PI / 2 / MESHSKY_TATE_VTX;

			//�J�E���g���Z�b�g
			ChangeCntX = 0;
			sky_rad = 0;

			//�ʒu�̃��Z�b�g
			VtxCntx = -cosf(sky_rad) * (MESHSKY_DIAMETER);
			VtxCnty -= MESHSKY_POYGON_HEIGHT;
			VtxCntz = sinf(sky_rad) * (MESHSKY_DIAMETER);
		}
	}

	//****�����̐ݒ�*****
	for(int nCnt = 0;nCnt < MESHSKY_VTX_NUM;nCnt++)
	{
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	}
	//****�J���[�̐ݒ�****
	for(int nCnt = 0;nCnt < MESHSKY_VTX_NUM;nCnt++)
	{
		pVtx[nCnt].col = D3DCOLOR_RGBA(255,255,255,55);
	}

	//****tex�̐ݒ�****
	float TexCntx = 0.0f;	//tex�ł̂ݎg��
	float TexCnty = 0.0f;	//tex�ł̂ݎg��

	for(int nCnt = 0;nCnt < MESHSKY_VTX_NUM;nCnt++)
	{
		pVtx[nCnt].tex = D3DXVECTOR2(TexCntx,TexCnty);
		TexCntx += 1.0f;

		if(TexCntx >= MESHSKY_YOKO_VTX + 1)
		{
			TexCntx = 0.0f;
			TexCnty += 1.0f;
		}
	}

	//============���_�o�b�t�@�f�[�^�̃��b�N����============
	g_pVtxBuffMeshsky->Unlock();
	
	//============�C���f�b�N�X����ݒ�====================
	g_pIdxBuffMeshsky -> Lock(0,0,(void**)&pIdx,0);

	//****pIdx�ւ̒i������****
	int IdxNum = -1;									//
	int IdxdansuuCnt = 1;								//

	for(int nCnt = 0;nCnt < MESHSKY_INDEX_NUM;nCnt++)	//�C���f�b�N�X�̐������J��Ԃ�
	{

		if(nCnt % 2 == 0)
		{
			IdxNum += (2 + MESHSKY_YOKO_VTX);
		}
		else
		{
			IdxNum -= (1 + MESHSKY_YOKO_VTX);
		}

		//�d�˂�|���S���������狭���Ƀ_�u�点�� IdxdansuuCnt�� 2,5,
		//���AIdxNum�����_���ȏ�ɂȂ�����ʂ��Ȃ��B�����Ă��܂��ƃu���[�N�|�C���g����������
		//�����C���f�b�N�X�����K��l��蒴���Ă��܂��ƁA�u���[�N�|�C���g���������Ă��܂�
		if(IdxNum == MESHSKY_YOKO_VTX * IdxdansuuCnt + IdxdansuuCnt -1 && IdxdansuuCnt < MESHSKY_TATE_VTX)
		{
			//�܂���̒��_�𓯂��Ƃ���ɃZ�b�g����
			pIdx[nCnt] = IdxNum;
			pIdx[nCnt + 1] = IdxNum;
			//�����̂Ƃ���Ɉړ����Ă���Z�b�g����B
			IdxNum += (2 + MESHSKY_YOKO_VTX);
			pIdx[nCnt + 2] = IdxNum;

			//�O���������̂�3�𑫂��@����pIdx[nCnt] = IdxNum�Ō��ʓI�ɓ����Ƃ���̐��l��������
			nCnt += 3;

			//Y�������ɃV�t�g����
			IdxdansuuCnt++;
		}

		pIdx[nCnt] = IdxNum;
	}

	//============�C���f�b�N�X�o�b�t�@�̃��b�N����============
	g_pIdxBuffMeshsky -> Unlock();
}

//��---------------------------------��
//���b�V���X�J�C�I������
//��---------------------------------��
void UninitMeshsky(void)
{
	//****�e�탊���[�X����****
	if(g_pVtxBuffMeshsky != NULL)
	{
		g_pVtxBuffMeshsky -> Release();
		g_pVtxBuffMeshsky = NULL;
	}
	
	//�e�N�X�`���̏���
	if(g_pTextureMeshsky != NULL)
	{
		g_pTextureMeshsky->Release();
		g_pTextureMeshsky = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̃����[�X
	if(g_pIdxBuffMeshsky != NULL)
	{
		g_pIdxBuffMeshsky -> Release();
		g_pIdxBuffMeshsky = NULL;
	}
}
//��---------------------------------��
//���b�V���X�J�C�̍X�V����
//��---------------------------------��
void UpdateMeshsky(void)
{

}

//��---------------------------------��
//���b�V���X�J�C�̕`�揈��
//��---------------------------------��
void DrawMeshsky(void)
{
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	//****���[���h�̐ݒ�****
	D3DXMatrixIdentity(&g_mtxWorldMeshsky);
	D3DXMatrixScaling(&mtxScl,g_sclMeshsky.x,
								g_sclMeshsky.y,
								g_sclMeshsky.z);			//�X�P�[���𔽉f

	D3DXMatrixMultiply(&g_mtxWorldMeshsky,&g_mtxWorldMeshsky,&mtxScl);

	//****���̑��̐ݒ�****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotMeshsky.y,
									g_rotMeshsky.x,
									g_rotMeshsky.z);		//���|�@�s�b�`�@���[��

	D3DXMatrixMultiply(&g_mtxWorldMeshsky,&g_mtxWorldMeshsky,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,g_posMeshsky.x,g_posMeshsky.y,g_posMeshsky.z);	//�ʒu�𔽉f
	D3DXMatrixMultiply(&g_mtxWorldMeshsky,&g_mtxWorldMeshsky,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldMeshsky);	//�ݒ�

	//---------------------3D�|���S���̕`��------------------------------
	//���_�o�b�t�@���o�C���h
	pDevice->SetStreamSource(0,g_pVtxBuffMeshsky,0,sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���o�C���h
	pDevice -> SetIndices(g_pIdxBuffMeshsky);		//�C���f�b�N�X�o�b�t�@���o�C���h

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,g_pTextureMeshsky);
	//�|���S���̕`��
	pDevice -> DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,MESHSKY_VTX_NUM,0,MESHSKY_POLYGON_NUM);
	//------------------------------------------------------------------
}
