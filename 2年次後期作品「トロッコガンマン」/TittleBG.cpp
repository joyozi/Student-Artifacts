//��-------------------------------------------------------------------------��
//
//	�^�C�g���w�icpp�t�@�C��[TittleBG.cpp]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include"main.h"
#include"TittleBG.h"
//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 t_bgTexturePolygon = NULL;
LPDIRECT3DVERTEXBUFFER9 t_bgVtxBuffPolygon = NULL;
VERTEX_2D *t_pVtxBG;		//�摜�̍��W�̃|�C���^

//��-------------------------------------------------------------------------��
//�^�C�g���w�i�̏���������
//��-------------------------------------------------------------------------��
void InitTittleBG(void)
{
	LPDIRECT3DDEVICE9 bgDevice;
	bgDevice = GetDevice();
	bgDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&t_bgVtxBuffPolygon,NULL);

	//�w�i�摜�̏��o�^
	t_bgVtxBuffPolygon->Lock(0,0,(void**)&t_pVtxBG,0);

	//���_���̐ݒ�
	t_pVtxBG[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	t_pVtxBG[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
	t_pVtxBG[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
	t_pVtxBG[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);

	t_pVtxBG[0].rhw = 1.0f;
	t_pVtxBG[1].rhw = 1.0f;
	t_pVtxBG[2].rhw = 1.0f;
	t_pVtxBG[3].rhw = 1.0f;

	t_pVtxBG[0].col = D3DCOLOR_RGBA(255,255,255,255);
	t_pVtxBG[1].col = D3DCOLOR_RGBA(255,255,255,255);
	t_pVtxBG[2].col = D3DCOLOR_RGBA(255,255,255,255);
	t_pVtxBG[3].col = D3DCOLOR_RGBA(255,255,255,255);

	t_pVtxBG[0].tex = D3DXVECTOR2(0.0,0.0);
	t_pVtxBG[1].tex = D3DXVECTOR2(1.0,0.0);
	t_pVtxBG[2].tex = D3DXVECTOR2(0.0,1.0);
	t_pVtxBG[3].tex = D3DXVECTOR2(1.0,1.0);
			
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/torokko_001.jpg",&t_bgTexturePolygon);

	t_bgVtxBuffPolygon->Unlock();
}
//-------------------------------------
//�^�C�g���w�i�I������
//-------------------------------------
void UninitTittleBG(void)
{
	//�o�b�t�@�̏���
	
	if(t_bgVtxBuffPolygon != NULL)
	{
		t_bgVtxBuffPolygon->Release();
		t_bgVtxBuffPolygon = NULL;
	}
	
		//�e�N�X�`���̏���
	if(t_bgTexturePolygon != NULL)
	{
		t_bgTexturePolygon->Release();
		t_bgTexturePolygon = NULL;
	}
}
//-------------------------------------
//�^�C�g���w�i�̍X�V����
//-------------------------------------
void UpdateTittleBG(void)
{

}
//-------------------------------------
//�^�C�g���w�i�̕`�揈��
//-------------------------------------
void DrawTittleBG(void)
{
	//�w�i�̕`��
	GetDevice()->SetStreamSource(0,t_bgVtxBuffPolygon,0,sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	GetDevice()->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	GetDevice()->SetTexture(0,t_bgTexturePolygon);
	//�|���S���̕`��
	GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	
}