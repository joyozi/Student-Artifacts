//��-------------------------------------------------------------------------��
//
//	�Q�[����UIcpp�t�@�C��[gameUI.cpp]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include"main.h"
#include"gameUI.h"
#include"input.h"
#include"fade.h"
#include"Result.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��
#define HITPOINT (5)	//�̗͂̐�

#define HP_WIDTH (60)	//�̗͕\���̉��̒���
#define HP_HEIGHT (30)	//�̗͕\���̏c�̒���

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 r_bgTextureGameUI;
LPDIRECT3DVERTEXBUFFER9 r_bgVtxBuffGameUI[HITPOINT];

int p_HitPointNum;

//��-------------------------------------------------------------------------��
//UI�̏���������
//��-------------------------------------------------------------------------��
void InitGameUI(void)
{
	LPDIRECT3DDEVICE9 bgDevice;
	bgDevice = GetDevice();

	VERTEX_2D *r_pVtxBG;		//�摜�̍��W�̃|�C���^

	p_HitPointNum = HITPOINT;

	r_bgTextureGameUI = NULL;
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/heart.png",&r_bgTextureGameUI);

	for(int nCnt = 0;nCnt < HITPOINT;nCnt++)
	{	
		r_bgVtxBuffGameUI[nCnt] = NULL;

		bgDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4*HITPOINT,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&r_bgVtxBuffGameUI[nCnt],NULL);

		//�w�i�摜�̏��o�^
		r_bgVtxBuffGameUI[nCnt]->Lock(0,0,(void**)&r_pVtxBG,0);

		//���_���̐ݒ�
		r_pVtxBG[0 + nCnt*4].pos = D3DXVECTOR3(0.0f + nCnt*HP_WIDTH	,0.0f,0.0f);
		r_pVtxBG[1 + nCnt*4].pos = D3DXVECTOR3(HP_WIDTH + nCnt*HP_WIDTH,0.0f,0.0f);
		r_pVtxBG[2 + nCnt*4].pos = D3DXVECTOR3(0.0f + nCnt*HP_WIDTH	,HP_WIDTH,0.0f);
		r_pVtxBG[3 + nCnt*4].pos = D3DXVECTOR3(HP_WIDTH + nCnt*HP_WIDTH,HP_WIDTH,0.0f);

		r_pVtxBG[0 + nCnt*4].rhw = 1.0f;
		r_pVtxBG[1 + nCnt*4].rhw = 1.0f;
		r_pVtxBG[2 + nCnt*4].rhw = 1.0f;
		r_pVtxBG[3 + nCnt*4].rhw = 1.0f;

		r_pVtxBG[0 + nCnt*4].col = D3DCOLOR_RGBA(255,255,255,255);
		r_pVtxBG[1 + nCnt*4].col = D3DCOLOR_RGBA(255,255,255,255);
		r_pVtxBG[2 + nCnt*4].col = D3DCOLOR_RGBA(255,255,255,255);
		r_pVtxBG[3 + nCnt*4].col = D3DCOLOR_RGBA(255,255,255,255);

		r_pVtxBG[0 + nCnt*4].tex = D3DXVECTOR2(0.0,0.0);
		r_pVtxBG[1 + nCnt*4].tex = D3DXVECTOR2(1.0,0.0);
		r_pVtxBG[2 + nCnt*4].tex = D3DXVECTOR2(0.0,1.0);
		r_pVtxBG[3 + nCnt*4].tex = D3DXVECTOR2(1.0,1.0);

		r_bgVtxBuffGameUI[nCnt]->Unlock();
	}
}
//-------------------------------------
//UI�I������
//-------------------------------------
void UninitGameUI(void)
{
	for(int nCnt = 0;nCnt < HITPOINT;nCnt++)
	{
		//�o�b�t�@�̏���
		if(r_bgVtxBuffGameUI[nCnt] != NULL)
		{
			r_bgVtxBuffGameUI[nCnt]->Release();
			r_bgVtxBuffGameUI[nCnt] = NULL;
		}
	}
	//�e�N�X�`���̏���
	if(r_bgTextureGameUI != NULL)
	{
		r_bgTextureGameUI->Release();
		r_bgTextureGameUI= NULL;
	}	
}
//-------------------------------------
//UI�̍X�V����
//-------------------------------------
void UpdateGameUI(void)
{
	if(p_HitPointNum <= 0)
	{
		SetResultJudge(false);
		SetFade(FADE_OUT);
	}
}
//-------------------------------------
//UI�̕`�揈��
//-------------------------------------
void DrawGameUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	for(int nCnt = 0;nCnt < p_HitPointNum;nCnt++)
	{
		//�w�i�̕`��
		pDevice->SetStreamSource(0,r_bgVtxBuffGameUI[nCnt],0,sizeof(VERTEX_2D));
		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0,r_bgTextureGameUI);
		//�e�N�X�`���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCnt * 4,2);
	}
}

//������g���Ƒ̗͂�����B��Q���ɓ����������Ȃǂ悤��
void HitPointCNT(void)
{
	p_HitPointNum--;
}