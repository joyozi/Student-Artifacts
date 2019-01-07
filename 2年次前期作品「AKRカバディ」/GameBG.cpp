//��-------------------------------------------------------------------------��
//
//	�Q�[���w�icpp�t�@�C��[polygon.cpp]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include"main.h"
#include"GameBG.h"
//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 g_bgTexturePolygon[BG_NUM];
LPDIRECT3DVERTEXBUFFER9 g_bgVtxBuffPolygon[BG_NUM];
VERTEX_2D *g_pVtxBG;						//�摜�̍��W�̃|�C���^

//��-------------------------------------------------------------------------��
//�Q�[���w�i�̏���������
//��-------------------------------------------------------------------------��
void InitGameBG(void)
{
	LPDIRECT3DDEVICE9 bgDevice;
	bgDevice = GetDevice();

	for(int nCnt = 0;nCnt < BG_NUM;nCnt++)
	{
		g_bgTexturePolygon[nCnt] = NULL;
		g_bgVtxBuffPolygon[nCnt] = NULL;

		bgDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_bgVtxBuffPolygon[nCnt],NULL);
	}
	//�w�i�摜�̏��o�^
	g_bgVtxBuffPolygon[0]->Lock(0,0,(void**)&g_pVtxBG,0);

	//���_���̐ݒ�
	g_pVtxBG[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_pVtxBG[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
	g_pVtxBG[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
	g_pVtxBG[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);

	g_pVtxBG[0].rhw = 1.0f;
	g_pVtxBG[1].rhw = 1.0f;
	g_pVtxBG[2].rhw = 1.0f;
	g_pVtxBG[3].rhw = 1.0f;

	g_pVtxBG[0].col = D3DCOLOR_RGBA(255,255,255,255);
	g_pVtxBG[1].col = D3DCOLOR_RGBA(255,255,255,255);
	g_pVtxBG[2].col = D3DCOLOR_RGBA(255,255,255,255);
	g_pVtxBG[3].col = D3DCOLOR_RGBA(255,255,255,255);

	g_pVtxBG[0].tex = D3DXVECTOR2(0.0,0.0);
	g_pVtxBG[1].tex = D3DXVECTOR2(1.0,0.0);
	g_pVtxBG[2].tex = D3DXVECTOR2(0.0,1.0);
	g_pVtxBG[3].tex = D3DXVECTOR2(1.0,1.0);
			
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/game_BG02.jpg",&g_bgTexturePolygon[0]);

	g_bgVtxBuffPolygon[0]->Unlock();
	
}
//-------------------------------------
//�Q�[���w�i�I������
//-------------------------------------
void UninitGameBG(void)
{
	for(int nCnt = 0;nCnt < BG_NUM;nCnt++)
	{
		//�o�b�t�@�̏���	
		if(g_bgVtxBuffPolygon[nCnt] != NULL)
		{
			g_bgVtxBuffPolygon[nCnt]->Release();
			g_bgVtxBuffPolygon[nCnt] = NULL;
		}
	
			//�e�N�X�`���̏���
		if(g_bgTexturePolygon[nCnt] != NULL)
		{
			g_bgTexturePolygon[nCnt]->Release();
			g_bgTexturePolygon[nCnt] = NULL;
		}
	}
}
//-------------------------------------
//�Q�[���w�i�̍X�V����
//-------------------------------------
void UpdateGameBG(void)
{

}
//-------------------------------------
//�Q�[���w�i�̕`�揈��
//-------------------------------------
void DrawGameBG(void)
{
	for(int nCnt = 0;nCnt < BG_NUM;nCnt++)
	{
		//�w�i�̕`��
		GetDevice()->SetStreamSource(0,g_bgVtxBuffPolygon[nCnt],0,sizeof(VERTEX_2D));
		//���_�t�H�[�}�b�g�̐ݒ�
		GetDevice()->SetFVF(FVF_VERTEX_2D);
		//�e�N�X�`���̐ݒ�
		GetDevice()->SetTexture(0,g_bgTexturePolygon[nCnt]);
		//�|���S���̕`��
		GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	}
}