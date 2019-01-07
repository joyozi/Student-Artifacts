//��-------------------------------------------------------------------------��
//
//	�Q�[���J�E���g�_�E��cpp�t�@�C��[game_countdown.cpp]
//	AT12A271�@�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "Game_Countdown.h"
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
PDIRECT3DTEXTURE9 c_pTextureScore = NULL;
LPDIRECT3DVERTEXBUFFER9 c_pVtxBuffScore[MAX_CNTDOWN_KETA] = {NULL,NULL,NULL};
VERTEX_2D *cVtx;			//�摜�̍��W�̃|�C���^
int g_nTime;				//�_��
//��-------------------------------------------------------------------------��
//����������
//��-------------------------------------------------------------------------��
void InitCountdown(void)
{
	LPDIRECT3DDEVICE9 cDevice;
	cDevice = GetDevice();
	int CountdownIreko[MAX_CNTDOWN_KETA];			//0���珇�ɍŏ㌅�ڂ�����
	int keta = 0;									//�}�C�i�X���錅������ϐ�
	int ketaCnt = 0;								//�X�R�A�̌v�Z�Ɏg���ϐ��B�����}�C�i�X����Ă���

	//�X�R�A�̏�����
	g_nTime = COUNTDOWN_TIME;

	//====================================
	//�J�E���g�_�E���̈�ԍŏ��̕\���̌v�Z
	//====================================
	//CountIreko��0����
	for(int nCnt = 0;nCnt < MAX_CNTDOWN_KETA;nCnt++)
	{
		CountdownIreko[nCnt] = 0;
	}

	//�����Ƃ̑��
	ketaCnt = g_nTime;

	for(int CountdownCnt = 0;CountdownCnt < MAX_CNTDOWN_KETA;CountdownCnt++)
	{
		keta = powf(10, MAX_CNTDOWN_KETA - CountdownCnt - 1);
			
		while(ketaCnt >= keta)
		{
			CountdownIreko[MAX_CNTDOWN_KETA - CountdownCnt-1]++;
			ketaCnt -= keta;
		}
	}

	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/number000.png",&c_pTextureScore);

	for(int CountdownCnt = 0; CountdownCnt < MAX_CNTDOWN_KETA;CountdownCnt++)
	{
		cDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*TYOUTEN_CNTDOWN_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&c_pVtxBuffScore[CountdownCnt],NULL);

		//�X�R�A�̏��o�^�E���b�N
		c_pVtxBuffScore[CountdownCnt]->Lock(0,0,(void**)&cVtx,0);

		//���_���̐ݒ�
		cVtx[0 + CountdownCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawCountdownPosWidth * (CountdownCnt + 1)),DrawCountdownPosHeight,0.0f);
		cVtx[1 + CountdownCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawCountdownPosWidth * CountdownCnt),DrawCountdownPosHeight,0.0f);
		cVtx[2 + CountdownCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawCountdownPosWidth * (CountdownCnt + 1)),DrawCountdownHeightW+DrawCountdownPosHeight,0.0f);
		cVtx[3 + CountdownCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawCountdownPosWidth * CountdownCnt),DrawCountdownHeightW + DrawCountdownPosHeight,0.0f);

		cVtx[0 + CountdownCnt * 4].rhw = 1.0f;
		cVtx[1 + CountdownCnt * 4].rhw = 1.0f;
		cVtx[2 + CountdownCnt * 4].rhw = 1.0f;
		cVtx[3 + CountdownCnt * 4].rhw = 1.0f;

		cVtx[0 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
		cVtx[1 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
		cVtx[2 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
		cVtx[3 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);

		cVtx[0 + CountdownCnt * 4].tex = D3DXVECTOR2(CountdownIreko[CountdownCnt] * 0.1,0.0);
		cVtx[1 + CountdownCnt * 4].tex = D3DXVECTOR2((CountdownIreko[CountdownCnt] * 0.1 + 0.1),0.0);
		cVtx[2 + CountdownCnt * 4].tex = D3DXVECTOR2(CountdownIreko[CountdownCnt] * 0.1,1.0);
		cVtx[3 + CountdownCnt * 4].tex = D3DXVECTOR2((CountdownIreko[CountdownCnt] * 0.1 + 0.1),1.0);
	
		//���b�N�̉���
		c_pVtxBuffScore[CountdownCnt]->Unlock();
	}
}

//��---------------------------------��
//�I������
//��---------------------------------��
void UninitCountdown(void)
{
	for(int CountdownCnt = 0; CountdownCnt < MAX_CNTDOWN_KETA;CountdownCnt++)
	{
		//�o�b�t�@�̏���
		if(c_pVtxBuffScore[CountdownCnt] != NULL)
		{
			c_pVtxBuffScore[CountdownCnt]->Release();
			c_pVtxBuffScore[CountdownCnt] = NULL;
		}
	}
	if(c_pTextureScore != NULL)
	{
		c_pTextureScore->Release();
		c_pTextureScore = NULL;
	}
}
//��---------------------------------��
//�̍X�V����
//��---------------------------------��
void UpdateCountdown(void)
{
	int CountdownIreko[MAX_CNTDOWN_KETA];			//0���珇�ɍŏ㌅�ڂ�����
	int keta = 0;									//�}�C�i�X���錅������ϐ�
	int ketaCnt = 0;								//�X�R�A�̌v�Z�Ɏg���ϐ��B�����}�C�i�X����Ă���
	static int timeCnt;

	//60�b���ƂɃ[���ɂȂ�B1�b���v�����Ă��炤
	timeCnt++;

	//CountIreko��0����
	for(int nCnt = 0;nCnt < MAX_CNTDOWN_KETA;nCnt++)
	{
		CountdownIreko[nCnt] = 0;
	}

	//�b�ǂ� ��b�������猅�̑���Ƃ�������
	if(timeCnt > 60)
	{
		g_nTime--;
		timeCnt = 0;
	}

	if(g_nTime <= 0)
	{
		SetFade(FADE_OUT);
	}

	//���_�̌����Ƃ̑��
	ketaCnt = g_nTime;

	for(int CountdownCnt = 0;CountdownCnt < MAX_CNTDOWN_KETA;CountdownCnt++)
	{
		keta = powf(10, MAX_CNTDOWN_KETA - CountdownCnt - 1);
			
		while(ketaCnt >= keta)
		{
			CountdownIreko[MAX_CNTDOWN_KETA - CountdownCnt-1]++;
			ketaCnt -= keta;
		}
	}

	//�\��������W�ƕ����̌v�Z�A�ݒ� +�F
	for(int CountdownCnt = 0; CountdownCnt < MAX_CNTDOWN_KETA;CountdownCnt++)
	{
		//�X�R�A�̏��o�^�E���b�N
		c_pVtxBuffScore[CountdownCnt]->Lock(0,0,(void**)&cVtx,0);

		//���_���̐ݒ�
		cVtx[0 + CountdownCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawCountdownPosWidth * (CountdownCnt + 1)),DrawCountdownPosHeight,0.0f);
		cVtx[1 + CountdownCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawCountdownPosWidth * CountdownCnt),DrawCountdownPosHeight,0.0f);
		cVtx[2 + CountdownCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawCountdownPosWidth * (CountdownCnt + 1)),DrawCountdownHeightW+DrawCountdownPosHeight,0.0f);
		cVtx[3 + CountdownCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawCountdownPosWidth * CountdownCnt),DrawCountdownHeightW + DrawCountdownPosHeight,0.0f);

		cVtx[0 + CountdownCnt * 4].tex = D3DXVECTOR2(CountdownIreko[CountdownCnt] * 0.1f,0.0f);
		cVtx[1 + CountdownCnt * 4].tex = D3DXVECTOR2((CountdownIreko[CountdownCnt] * 0.1f + 0.1f),0.0f);
		cVtx[2 + CountdownCnt * 4].tex = D3DXVECTOR2(CountdownIreko[CountdownCnt] * 0.1f,1.0f);
		cVtx[3 + CountdownCnt * 4].tex = D3DXVECTOR2((CountdownIreko[CountdownCnt] * 0.1f + 0.1f),1.0f);

		//���_���Ƃ̐F�̐ݒ�
		if(g_nTime > CountdownChangeColor)
		{
			cVtx[0 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
			cVtx[1 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
			cVtx[2 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
			cVtx[3 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
		}
		else
		{
			cVtx[0 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,0,0,255);
			cVtx[1 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,0,0,255);
			cVtx[2 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,0,0,255);
			cVtx[3 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,0,0,255);
		}
		//���b�N�̉���
		c_pVtxBuffScore[CountdownCnt]->Unlock();
		
	}

}

//��---------------------------------��
//�̕`�揈��
//��---------------------------------��
void DrawCountdown(void)
{
		for(int CountdownCnt = 0; CountdownCnt < MAX_CNTDOWN_KETA;CountdownCnt++)
	{
		//�X�R�A�̕`��
		GetDevice()->SetStreamSource(0,c_pVtxBuffScore[CountdownCnt],0,sizeof(VERTEX_2D));
		//���_�t�H�[�}�b�g�̐ݒ�
		GetDevice()->SetFVF(FVF_VERTEX_2D);	
		//�e�N�X�`���̐ݒ�
		GetDevice()->SetTexture(0,c_pTextureScore);
		//�|���S���̕`��
		GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,POLYGON_CNTDOWN_NUM);	//�^�񒆂�0�͊J�n���钸�_�C���f�b�N�X
	}
}