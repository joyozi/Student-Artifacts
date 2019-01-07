//��-------------------------------------------------------------------------��
//
//	���U���g�w�icpp�t�@�C��[ResultBG.cpp]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include"main.h"
#include"ResultBG.h"
//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 r_bgTexturePolygon = NULL;
LPDIRECT3DVERTEXBUFFER9 r_bgVtxBuffPolygon = NULL;
VERTEX_2D *r_pVtxBG;		//�摜�̍��W�̃|�C���^

//��-------------------------------------------------------------------------��
//���U���g�w�i�̏���������
//��-------------------------------------------------------------------------��
void InitResultBG(bool Judge)
{
	LPDIRECT3DDEVICE9 bgDevice;
	bgDevice = GetDevice();
	bgDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&r_bgVtxBuffPolygon,NULL);

	//�w�i�摜�̏��o�^
	r_bgVtxBuffPolygon->Lock(0,0,(void**)&r_pVtxBG,0);

	//���_���̐ݒ�
	r_pVtxBG[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	r_pVtxBG[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
	r_pVtxBG[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
	r_pVtxBG[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);

	r_pVtxBG[0].rhw = 1.0f;
	r_pVtxBG[1].rhw = 1.0f;
	r_pVtxBG[2].rhw = 1.0f;
	r_pVtxBG[3].rhw = 1.0f;

	r_pVtxBG[0].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtxBG[1].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtxBG[2].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtxBG[3].col = D3DCOLOR_RGBA(255,255,255,255);

	r_pVtxBG[0].tex = D3DXVECTOR2(0.0,0.0);
	r_pVtxBG[1].tex = D3DXVECTOR2(1.0,0.0);
	r_pVtxBG[2].tex = D3DXVECTOR2(0.0,1.0);
	r_pVtxBG[3].tex = D3DXVECTOR2(1.0,1.0);
	
	if(Judge)
	{
		D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/result_takara.jpg",&r_bgTexturePolygon);
	}
	else
	{
		D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/GameOver00.jpg",&r_bgTexturePolygon);
	}

	r_bgVtxBuffPolygon->Unlock();
}
//-------------------------------------
//���U���g�w�i�I������
//-------------------------------------
void UninitResultBG(void)
{
	//�o�b�t�@�̏���
	
	if(r_bgVtxBuffPolygon != NULL)
	{
		r_bgVtxBuffPolygon->Release();
		r_bgVtxBuffPolygon = NULL;
	}
	
		//�e�N�X�`���̏���
	if(r_bgTexturePolygon != NULL)
	{
		r_bgTexturePolygon->Release();
		r_bgTexturePolygon = NULL;
	}
}
//-------------------------------------
//���U���g�w�i�̍X�V����
//-------------------------------------
void UpdateResultBG(void)
{

}
//-------------------------------------
//���U���g�w�i�̕`�揈��
//-------------------------------------
void DrawResultBG(void)
{
	//�w�i�̕`��
	GetDevice()->SetStreamSource(0,r_bgVtxBuffPolygon,0,sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	GetDevice()->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	GetDevice()->SetTexture(0,r_bgTexturePolygon);
	GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	
}