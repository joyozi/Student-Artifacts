//��-------------------------------------------------------------------------��
//
//	���U���g�|���S��cpp�t�@�C��[polygon.cpp]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include"main.h"
#include"ResultPolygon.h"
#include"input.h"
//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 r_pTexturePolygon = NULL;
LPDIRECT3DVERTEXBUFFER9 r_pVtxBuffPolygon = NULL;
VERTEX_2D *r_pVtx;			//�摜�̍��W�̃|�C���^

//��-------------------------------------------------------------------------��
//���U���g�|���S���̏���������
//��-------------------------------------------------------------------------��
void InitResultPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*TYOUTEN_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&r_pVtxBuffPolygon,NULL);

	//�Q�[���I�[�o�[�̏��o�^�E���b�N
	r_pVtxBuffPolygon->Lock(0,0,(void**)&r_pVtx,0);
/*
	//���_���̐ݒ�
	r_pVtx[0].pos = D3DXVECTOR3(450.0f,350.0f,0.0f);
	r_pVtx[1].pos = D3DXVECTOR3(850.0f,350.0f,0.0f);
	r_pVtx[2].pos = D3DXVECTOR3(450.0f,500.0f,0.0f);
	r_pVtx[3].pos = D3DXVECTOR3(850.0f,500.0f,0.0f);

	r_pVtx[0].rhw = 1.0f;
	r_pVtx[1].rhw = 1.0f;
	r_pVtx[2].rhw = 1.0f;
	r_pVtx[3].rhw = 1.0f;

	r_pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	r_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	r_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	r_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	r_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);
*/			
//	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/result_logo.png",&r_pTexturePolygon);
	
	//���b�N�̉���
	r_pVtxBuffPolygon->Unlock();
}
//-------------------------------------
//���U���g�|���S���I������
//-------------------------------------
void UninitResultPolygon(void)
{
	//�o�b�t�@�̏���
	if(r_pVtxBuffPolygon != NULL)
	{
		r_pVtxBuffPolygon->Release();
		r_pVtxBuffPolygon = NULL;
	}

		//�e�N�X�`���̏���
	if(r_pTexturePolygon != NULL)
	{
		r_pTexturePolygon->Release();
		r_pTexturePolygon = NULL;
	}
}
//-------------------------------------
//���U���g�|���S���̍X�V����
//-------------------------------------
void UpdateResultPolygon(void)
{
}
//-------------------------------------
//���U���g�|���S���̕`�揈��
//-------------------------------------
void DrawResultPolygon(void)
{
	//�����j���O�}���̕`��
	GetDevice()->SetStreamSource(0,r_pVtxBuffPolygon,0,sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	GetDevice()->SetFVF(FVF_VERTEX_2D);	
	//�e�N�X�`���̐ݒ�
	GetDevice()->SetTexture(0,r_pTexturePolygon);
	//�|���S���̕`��
	GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,RESULT_POLYGON_NUM);	//�^�񒆂�0�͊J�n���钸�_�C���f�b�N�X
}