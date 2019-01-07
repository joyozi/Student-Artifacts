//��-------------------------------------------------------------------------��
//
//	�^�C�g���|���S��cpp�t�@�C��[TittlePolygon.cpp]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "TittlePolygon.h"
#include "input.h"
#include "fade.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 t_pTexturePolygon[2] = {NULL,NULL};
LPDIRECT3DVERTEXBUFFER9 t_pVtxBuffPolygon[2] = {NULL,NULL};
int t_nCounterAnim = 0;
int t_nPatternAnim = 0;
int t_nPatternAnimTATE = 0;
VERTEX_2D *t_pVtx;			//�摜�̍��W�̃|�C���^
D3DXVECTOR3 t_posPolygon;	//����̍��W�H
D3DXVECTOR3 t_rotPolygon;	//��]�̈ړ���
float t_fLengthPolygon;		//�Ίp���̒���
float t_fAnglePolygon;		//�Ίp���̊p�x
bool Tenmetu;				//�v���X�G���^�[�̓_�ł̕ϐ�
int TenmetuCnt;				//�v���X�G���^�[�̓_�ł̎��Ԍv���ϐ��@���񏉊������邽�߂ɂ����ɋL�q
//��-------------------------------------------------------------------------��
//�^�C�g���|���S���̏���������
//��-------------------------------------------------------------------------��
void InitTittlePolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*TITTLE_TYOUTEN_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&t_pVtxBuffPolygon[0],NULL);

	//�v���X�G���^�[�̓_�Ŏ��Ԃ̏�����
	TenmetuCnt = 0;

	//�_�ł��J��Ԃ��ƋL��sh����\�������鏈��
	Tenmetu = true;

	//�����j���O�}���̏��o�^�E���b�N
	t_pVtxBuffPolygon[0]->Lock(0,0,(void**)&t_pVtx,0);

	//���_���̐ݒ�
	t_pVtx[0].pos = D3DXVECTOR3(400.0f,500.0f,0.0f);
	t_pVtx[1].pos = D3DXVECTOR3(700.0f,500.0f,0.0f);
	t_pVtx[2].pos = D3DXVECTOR3(400.0f,600.0f,0.0f);
	t_pVtx[3].pos = D3DXVECTOR3(700.0f,600.0f,0.0f);

	t_pVtx[0].rhw = 1.0f;
	t_pVtx[1].rhw = 1.0f;
	t_pVtx[2].rhw = 1.0f;
	t_pVtx[3].rhw = 1.0f;

	t_pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	t_pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	t_pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	t_pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	t_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	t_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	t_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	t_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);
			
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/pressenter000.png",&t_pTexturePolygon[0]);
	
	//���b�N�̉���
	t_pVtxBuffPolygon[0]->Unlock();

	
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&t_pVtxBuffPolygon[1],NULL);

	//�����j���O�}���̏��o�^�E���b�N
	t_pVtxBuffPolygon[1]->Lock(0,0,(void**)&t_pVtx,0);

	//���_���̐ݒ�
	t_pVtx[0].pos = D3DXVECTOR3(50.0f,20.0f,0.0f);
	t_pVtx[1].pos = D3DXVECTOR3(1000.0f,20.0f,0.0f);
	t_pVtx[2].pos = D3DXVECTOR3(50.0f,250.0f,0.0f);
	t_pVtx[3].pos = D3DXVECTOR3(1000.0f,250.0f,0.0f);

	t_pVtx[0].rhw = 1.0f;
	t_pVtx[1].rhw = 1.0f;
	t_pVtx[2].rhw = 1.0f;
	t_pVtx[3].rhw = 1.0f;

	t_pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	t_pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	t_pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	t_pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	t_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	t_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	t_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	t_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);
			
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/title_004.png",&t_pTexturePolygon[1]);
	
	//���b�N�̉���
	t_pVtxBuffPolygon[0]->Unlock();
}
//-------------------------------------
//�^�C�g���|���S���I������
//-------------------------------------
void UninitTittlePolygon(void)
{
	for(int nCnt = 0;nCnt < 2;nCnt++)
	{
		//�o�b�t�@�̏���
		if(t_pVtxBuffPolygon[nCnt] != NULL)
		{
			t_pVtxBuffPolygon[nCnt]->Release();
			t_pVtxBuffPolygon[nCnt] = NULL;
		}

		//�e�N�X�`���̏���
		if(t_pTexturePolygon[nCnt] != NULL)
		{
			t_pTexturePolygon[nCnt]->Release();
			t_pTexturePolygon[nCnt] = NULL;
		}
	}
}
//-------------------------------------
//�^�C�g���|���S���̍X�V����
//-------------------------------------
void UpdateTittlePolygon(void)
{
	//�t�F�C�h�m�����Ɠ_�ł�����B�t�F�C�h�A�E�g���Ɠ_�ł������Ȃ�
	switch(GetFade())
	{
		case FADE_NONE:
			//�v���X�G���^�[�̓_�ł̌v�Z
			TenmetuCnt++;

			if(TenmetuCnt <= TENMETU_TIME)
			{
				Tenmetu = true;		
			}
			else
			{
				Tenmetu = false;
			}

			if(TenmetuCnt >= TENMETU_TIME * 2)
			{
				TenmetuCnt = 0;
			}
			break;

		case FADE_OUT:
			//�v���X�G���^�[�̓_�ł̌v�Z
			TenmetuCnt++;
		
			if(TenmetuCnt <= TENMETU_TIME_FADEOUT)
			{
				Tenmetu = true;		
			}
			else
			{
				Tenmetu = false;
			}

			if(TenmetuCnt >= TENMETU_TIME_FADEOUT * 2)
			{
				TenmetuCnt = 0;
			}
			break;

		default:
			break;
	}

}
//-------------------------------------
//�^�C�g���|���S���̕`�揈��
//-------------------------------------
void DrawTittlePolygon(void)
{
		//�����j���O�}���̕`��
		GetDevice()->SetStreamSource(0,t_pVtxBuffPolygon[0],0,sizeof(VERTEX_2D));
		//���_�t�H�[�}�b�g�̐ݒ�
		GetDevice()->SetFVF(FVF_VERTEX_2D);	

		if(Tenmetu == true)
		{
			//�e�N�X�`���̐ݒ�
			GetDevice()->SetTexture(0,t_pTexturePolygon[0]);
			//�|���S���̕`��
			GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);	//�^�񒆂�0�͊J�n���钸�_�C���f�b�N�X
		}

				//�����j���O�}���̕`��
		GetDevice()->SetStreamSource(0,t_pVtxBuffPolygon[1],0,sizeof(VERTEX_2D));
		//���_�t�H�[�}�b�g�̐ݒ�
		GetDevice()->SetFVF(FVF_VERTEX_2D);	
		//�e�N�X�`���̐ݒ�
		GetDevice()->SetTexture(0,t_pTexturePolygon[1]);
		//�|���S���̕`��
		GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,4);	//�^�񒆂�0�͊J�n���钸�_�C���f�b�N�X


}