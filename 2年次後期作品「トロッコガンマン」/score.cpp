//��-------------------------------------------------------------------------��
//
//	�X�R�Acpp�t�@�C��[score.cpp]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include"main.h"
#include"input.h"
#include"score.h"
#include <math.h>

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 g_pTextureScore[MAX_SCORE_KETA];
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore[MAX_SCORE_KETA];
VERTEX_2D *sVtx;			//�摜�̍��W�̃|�C���^
int g_nScore;				//�_��
//��-------------------------------------------------------------------------��
//�X�R�A�̏���������
//��-------------------------------------------------------------------------��
void InitScore(void)
{
	LPDIRECT3DDEVICE9 sDevice;
	sDevice = GetDevice();
	
	g_nScore = 0;

	for(int ScoreCnt = 0; ScoreCnt < MAX_SCORE_KETA;ScoreCnt++)
	{
		g_pTextureScore[ScoreCnt] = NULL;
		g_pVtxBuffScore[ScoreCnt] = NULL;

		sDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*TYOUTEN_sNUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffScore[ScoreCnt],NULL);

		//�X�R�A�̏��o�^�E���b�N
		g_pVtxBuffScore[ScoreCnt]->Lock(0,0,(void**)&sVtx,0);

		//���_���̐ݒ�
		sVtx[0 + ScoreCnt * 4].pos = D3DXVECTOR3(DrawScorePosRight - (DrawScorePosWidth * (ScoreCnt + 1)),0.0f,0.0f);
		sVtx[1 + ScoreCnt * 4].pos = D3DXVECTOR3(DrawScorePosRight - (DrawScorePosWidth * ScoreCnt),0.0f,0.0f);
		sVtx[2 + ScoreCnt * 4].pos = D3DXVECTOR3(DrawScorePosRight - (DrawScorePosWidth * (ScoreCnt + 1)),DrawScorePosHeight,0.0f);
		sVtx[3 + ScoreCnt * 4].pos = D3DXVECTOR3(DrawScorePosRight - (DrawScorePosWidth * ScoreCnt),DrawScorePosHeight,0.0f);

		sVtx[0 + ScoreCnt * 4].rhw = 1.0f;
		sVtx[1 + ScoreCnt * 4].rhw = 1.0f;
		sVtx[2 + ScoreCnt * 4].rhw = 1.0f;
		sVtx[3 + ScoreCnt * 4].rhw = 1.0f;

		sVtx[0 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
		sVtx[1 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
		sVtx[2 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
		sVtx[3 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);

		sVtx[0 + ScoreCnt * 4].tex = D3DXVECTOR2(0.0,0.0);
		sVtx[1 + ScoreCnt * 4].tex = D3DXVECTOR2((1.0 / 10),0.0);
		sVtx[2 + ScoreCnt * 4].tex = D3DXVECTOR2(0.0,1.0);
		sVtx[3 + ScoreCnt * 4].tex = D3DXVECTOR2((1.0 / 10),1.0);

		D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/number000.png",&g_pTextureScore[ScoreCnt]);
	
		//���b�N�̉���
		g_pVtxBuffScore[ScoreCnt]->Unlock();
	}
}

//��---------------------------------��
//�X�R�A�̏I������
//��---------------------------------��
void UninitScore(void)
{
	for(int ScoreCnt = 0; ScoreCnt < MAX_SCORE_KETA;ScoreCnt++)
	{
		//�o�b�t�@�̏���
		if(g_pVtxBuffScore[ScoreCnt] != NULL)
		{
			g_pVtxBuffScore[ScoreCnt]->Release();
			g_pVtxBuffScore[ScoreCnt] = NULL;
		}
		//�e�N�X�`���̏���
		if(g_pTextureScore[ScoreCnt] != NULL)
		{
			g_pTextureScore[ScoreCnt]->Release();
			g_pTextureScore[ScoreCnt] = NULL;
		}
	}
}
//��---------------------------------��
//�X�R�A�̍X�V����
//��---------------------------------��
void UpdateScore(void)
{
	int ScoreIreko[MAX_SCORE_KETA];					//0���珇�ɍŏ㌅�ڂ�����
	int keta;										//�}�C�i�X���錅������ϐ�
	int ketaCnt = 0;								//�X�R�A�̌v�Z�Ɏg���ϐ��B�����}�C�i�X����Ă���
	int kakkonum = 0;								//
	bool hantei = true;

	for(int nCnt = 0;nCnt < MAX_SCORE_KETA;nCnt++)
	{
		ScoreIreko[nCnt] = NULL;
	}

	//���_�̉��Z
	if(GetKeyboardTrigger(DIK_RIGHT) == true)
	{
		g_nScore +=100;
	}

	ketaCnt = g_nScore;

	//���_�̌����Ƃ̑��
	for(int ScoreCnt = 0;ScoreCnt < MAX_SCORE_KETA;ScoreCnt++)
	{
		keta = powf(10, MAX_SCORE_KETA - ScoreCnt-1);
			
		while(ketaCnt >= keta)
		{
			ScoreIreko[ MAX_SCORE_KETA - ScoreCnt-1]++;
			ketaCnt -= keta;
		}
	}

	//�\��������W�ƕ����̌v�Z�A�ݒ�
	for(int ScoreCnt = 0; ScoreCnt < MAX_SCORE_KETA;ScoreCnt++)
	{
		//�X�R�A�̏��o�^�E���b�N
		g_pVtxBuffScore[ScoreCnt]->Lock(0,0,(void**)&sVtx,0);

		//���_���̐ݒ�
		sVtx[0 + ScoreCnt * 4].pos = D3DXVECTOR3(DrawScorePosRight - (DrawScorePosWidth * (ScoreCnt + 1)),0.0f,0.0f);
		sVtx[1 + ScoreCnt * 4].pos = D3DXVECTOR3(DrawScorePosRight - (DrawScorePosWidth * ScoreCnt),0.0f,0.0f);
		sVtx[2 + ScoreCnt * 4].pos = D3DXVECTOR3(DrawScorePosRight - (DrawScorePosWidth * (ScoreCnt + 1)),DrawScorePosHeight,0.0f);
		sVtx[3 + ScoreCnt * 4].pos = D3DXVECTOR3(DrawScorePosRight - (DrawScorePosWidth * ScoreCnt),DrawScorePosHeight,0.0f);

		sVtx[0 + ScoreCnt * 4].tex = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1,0.0);
		sVtx[1 + ScoreCnt * 4].tex = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1 + 0.1,0.0);
		sVtx[2 + ScoreCnt * 4].tex = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1,1.0);
		sVtx[3 + ScoreCnt * 4].tex = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1 + 0.1,1.0);
	
		//���b�N�̉���
		g_pVtxBuffScore[ScoreCnt]->Unlock();
	}
}
//��---------------------------------��
//�X�R�A�̕`�揈��
//��---------------------------------��
void DrawScore(void)
{
	for(int ScoreCnt = 0; ScoreCnt < MAX_SCORE_KETA;ScoreCnt++)
	{
		//�X�R�A�̕`��
		GetDevice()->SetStreamSource(0,g_pVtxBuffScore[ScoreCnt],0,sizeof(VERTEX_2D));
		//���_�t�H�[�}�b�g�̐ݒ�
		GetDevice()->SetFVF(FVF_VERTEX_2D);	
		//�e�N�X�`���̐ݒ�
		GetDevice()->SetTexture(0,g_pTextureScore[ScoreCnt]);
		//�|���S���̕`��
		GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,ScoreCnt*4,2);	//�^�񒆂�0�͊J�n���钸�_�C���f�b�N�X
	}
}

void PlusScore(int score)
{
	g_nScore += score;
}