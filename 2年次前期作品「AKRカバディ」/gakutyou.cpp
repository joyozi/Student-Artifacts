//��-------------------------------------------------------------------------��
//
//	�t�@�C��[.]
//	AT12A271�@�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "gakutyou.h"
#include "input.h"
#include "sound.h"
//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 g_gTexturePolygon[2] = {NULL};
LPDIRECT3DVERTEXBUFFER9 g_gVtxBuffPolygon[GAKUTYOU_TEXTURE_NUM];

VERTEX_2D *g_gVtx;											//�摜�̍��W�̃|�C���^
D3DXVECTOR3 g_gposPolygon[GAKUTYOU_TEXTURE_NUM];			//���S�̍��W
D3DXVECTOR3 g_grotPolygon[GAKUTYOU_TEXTURE_NUM];			//��]�̈ړ���

float g_gLengthPolygon;										//�Ίp���̒���
float g_gAnglePolygon;										//�Ίp���̊p�x

int BEAM_TIME;												//�r�[���̎��Ԍv�Z
int BEAM_NUM;												//�r�[���̐� �ʒu����n�߂�
bool BEAM_JUDGE[GAKUTYOU_TEXTURE_NUM];						//�r�[���̏o������ true�ŏo��
int BEAM_PHAZE;												//�w���搶�̃r�[���̒i�K 0���ˊJ�n�@�P�`���[�W�@�Q�L�΂��@�R�񂷁@�S�����@�T������

D3DXVECTOR3 g_gposrotPolygon[GAKUTYOU_TEXTURE_NUM];			//�r�[���̉�]�ʒu�̌v�Z�p
D3DXVECTOR3 g_gposPolygon_PHAZE3[GAKUTYOU_TEXTURE_NUM];		//PHAZE3�Ŏg���B���W�ʒu���Œ肷��

int BEAM_START;
bool BOOMBOOMBOOM;
bool BOOMBOOMBOOMEnemy;		//�G�l�~�[��ʔ����p

//��-------------------------------------------------------------------------��
//����������
//��-------------------------------------------------------------------------��
void InitMasaru(void)
{	
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	for(int Cnt = 0;Cnt < GAKUTYOU_TEXTURE_NUM;Cnt++)
	{
		BEAM_JUDGE[Cnt] = false;
		g_gVtxBuffPolygon[Cnt] = NULL;
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*GAKUTYOU_TYOUTEN_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_gVtxBuffPolygon[Cnt],NULL);
	}

	//�e�N�X�`���ݒ�
	g_gTexturePolygon[0] = NULL;
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/genki_041123_3.png",&g_gTexturePolygon[0]);
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/effect000.jpg",&g_gTexturePolygon[1]);

	//�w���搶�̏��o�^�E���b�N
	g_gVtxBuffPolygon[0]->Lock(0,0,(void**)&g_gVtx,0);

	//���_���̐ݒ�
	g_gVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - GAKUTYOU_POLYGON_YOKOLONG,SCREEN_HEIGHT / 2 - GAKUTYOU_POLYGON_TATELONG,0.0f);
	g_gVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + GAKUTYOU_POLYGON_YOKOLONG,SCREEN_HEIGHT / 2 - GAKUTYOU_POLYGON_TATELONG,0.0f);
	g_gVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - GAKUTYOU_POLYGON_YOKOLONG,SCREEN_HEIGHT / 2 + GAKUTYOU_POLYGON_TATELONG,0.0f);
	g_gVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + GAKUTYOU_POLYGON_YOKOLONG,SCREEN_HEIGHT / 2 + GAKUTYOU_POLYGON_TATELONG,0.0f);

	g_gVtx[0].rhw = 1.0f;
	g_gVtx[1].rhw = 1.0f;
	g_gVtx[2].rhw = 1.0f;
	g_gVtx[3].rhw = 1.0f;

	g_gVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	g_gVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	g_gVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	g_gVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	g_gVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	g_gVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	g_gVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	g_gVtx[3].tex = D3DXVECTOR2(1.0,1.0);
	
	//���b�N�̉���
	g_gVtxBuffPolygon[0]->Unlock();

	//�r�[���w���̏�����
	for(int nCnt= 1;nCnt < GAKUTYOU_TEXTURE_NUM;nCnt++)
	{
		//�w���搶�̏��o�^�E���b�N
		g_gVtxBuffPolygon[nCnt]->Lock(0,0,(void**)&g_gVtx,0);

		g_gVtx[0].rhw = 1.0f;
		g_gVtx[1].rhw = 1.0f;
		g_gVtx[2].rhw = 1.0f;
		g_gVtx[3].rhw = 1.0f;

		g_gVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
		g_gVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
		g_gVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
		g_gVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

		g_gVtx[0].tex = D3DXVECTOR2(0.0,0.0);
		g_gVtx[1].tex = D3DXVECTOR2(1.0,0.0);
		g_gVtx[2].tex = D3DXVECTOR2(0.0,1.0);
		g_gVtx[3].tex = D3DXVECTOR2(1.0,1.0);
				
		//���b�N�̉���
		g_gVtxBuffPolygon[nCnt]->Unlock();

		g_gposPolygon[nCnt].x = (SCREEN_WIDTH / 2);
		g_gposPolygon[nCnt].y = (SCREEN_HEIGHT / 2) - GAKUTYOU_POLYGON_TATELONG;
		g_grotPolygon[nCnt].z = D3DX_PI;
		g_gposrotPolygon[nCnt].z = D3DX_PI;
	}
		
	g_gLengthPolygon = sqrtf(GAKUTYOU_POLYGON_YOKOLONG * GAKUTYOU_POLYGON_YOKOLONG);
	g_gAnglePolygon = atan2f(GAKUTYOU_POLYGON_YOKOLONG,GAKUTYOU_POLYGON_TATELONG);

	BEAM_NUM = 1;
	BEAM_TIME = 0;
	BEAM_PHAZE = 0;
	BEAM_START = 0;
	BOOMBOOMBOOM = false;
	BOOMBOOMBOOMEnemy = false;
}

//��---------------------------------��
//�I������
//��---------------------------------��
void UninitMasaru(void)
{
	for(int Cnt = 0;Cnt < GAKUTYOU_TEXTURE_NUM;Cnt++)
	{
		//�o�b�t�@�̏���
		if(g_gVtxBuffPolygon[Cnt] != NULL)
		{
			g_gVtxBuffPolygon[Cnt]->Release();
			g_gVtxBuffPolygon[Cnt] = NULL;
		}
	}

	//�e�N�X�`���̏���
	for(int i = 0;i < 2;i++)
	{
		if(g_gTexturePolygon[i] != NULL)
		{
			g_gTexturePolygon[i]->Release();
			g_gTexturePolygon[i] = NULL;
		}
	}
}
//��---------------------------------��
//�̍X�V����
//��---------------------------------��
void UpdateMasaru(void)
{
	
	BEAM_START++;

	if(BEAM_START >= 480)
	{
		BEAM_PHAZE = 0;
		for(int nCnt = 1;nCnt < GAKUTYOU_TEXTURE_NUM;nCnt++)
		{
			g_gposPolygon[nCnt].x = (SCREEN_WIDTH / 2);
			g_gposPolygon[nCnt].y = (SCREEN_HEIGHT / 2) - GAKUTYOU_POLYGON_TATELONG;
			g_grotPolygon[nCnt].z = D3DX_PI;
			g_gposrotPolygon[nCnt].z = D3DX_PI;
		}
		//�w���搶�̏��o�^�E���b�N
		g_gVtxBuffPolygon[0]->Lock(0,0,(void**)&g_gVtx,0);

		g_gVtx[0].col = D3DCOLOR_RGBA(200,25,25,255);
		g_gVtx[1].col = D3DCOLOR_RGBA(200,25,25,255);
		g_gVtx[2].col = D3DCOLOR_RGBA(200,25,25,255);
		g_gVtx[3].col = D3DCOLOR_RGBA(200,25,25,255);

		//���b�N�̉���
		g_gVtxBuffPolygon[0]->Unlock();

		if(GetKeyboardTrigger(DIK_SPACE) == true)
		{
			PlaySound(SOUND_LABEL_SE_gakutyou_beam_05);

			//PHAZE 0 ������
			if(BEAM_PHAZE == 0)
			{
				BEAM_PHAZE++;
				BEAM_START = 0;
				BEAM_TIME = 0;
				g_gVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
				g_gVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
				g_gVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
				g_gVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);
			}	
		}
	}
	
	

	//PHAZE 1 �r�[�������߂�
	if(BEAM_PHAZE == 1)
	{
		//�\���̂�������
		BEAM_TIME++;

		if(BEAM_NUM < GAKUTYOU_TEXTURE_NUM)
		{
			if(BEAM_TIME >= GAKUTYOU_BEAM_TAME_TIME / GAKUTYOU_TEXTURE_NUM)
			{
				BEAM_JUDGE[BEAM_NUM] = true;

				//�w���搶�̏��o�^�E���b�N
				g_gVtxBuffPolygon[BEAM_NUM]->Lock(0,0,(void**)&g_gVtx,0);

				//���_���̐ݒ�
				g_gVtx[0].pos.x = g_gposPolygon[BEAM_NUM].x + sinf(g_grotPolygon[BEAM_NUM].z + g_gAnglePolygon) * g_gLengthPolygon;
				g_gVtx[0].pos.y = g_gposPolygon[BEAM_NUM].y + cosf(g_grotPolygon[BEAM_NUM].z + g_gAnglePolygon) * g_gLengthPolygon;
				g_gVtx[0].pos.z = 0;

				g_gVtx[1].pos.x = g_gposPolygon[BEAM_NUM].x + sinf(g_grotPolygon[BEAM_NUM].z - g_gAnglePolygon) * g_gLengthPolygon;
				g_gVtx[1].pos.y = g_gposPolygon[BEAM_NUM].y + cosf(g_grotPolygon[BEAM_NUM].z - g_gAnglePolygon) * g_gLengthPolygon;
				g_gVtx[1].pos.z = 0;

				g_gVtx[2].pos.x = g_gposPolygon[BEAM_NUM].x + sinf(g_grotPolygon[BEAM_NUM].z - g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
				g_gVtx[2].pos.y = g_gposPolygon[BEAM_NUM].y + cosf(g_grotPolygon[BEAM_NUM].z - g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
				g_gVtx[2].pos.z = 0;

				g_gVtx[3].pos.x = g_gposPolygon[BEAM_NUM].x + sinf(g_grotPolygon[BEAM_NUM].z + g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
				g_gVtx[3].pos.y = g_gposPolygon[BEAM_NUM].y + cosf(g_grotPolygon[BEAM_NUM].z + g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
				g_gVtx[3].pos.z = 0;
	
				//���b�N�̉���
				g_gVtxBuffPolygon[BEAM_NUM]->Unlock();

				BEAM_NUM++;
				BEAM_TIME = 0;
				//�ŏ������w���̊���̂�������B�ŏ��̈ꖇ�摜���������\������
				if(BEAM_NUM == 2)
				{
					BEAM_TIME = -GAKUTYOU_BEAM_TAME_TIME;
				}
			}
		}
		else	//�S���\�������玟�̒i�K��
		{
			BEAM_PHAZE++;
			BEAM_NUM = 1;
			BEAM_TIME = 0;
		}
	}

	//PHAZE 2�@�L�΂�
	if(BEAM_PHAZE == 2)
	{
		for(int nCnt = 1;nCnt < GAKUTYOU_TEXTURE_NUM;nCnt++)
		{
			//�P��������X�N���[���̔������炢���i�e�N�X�`�����[�P�j�����i�ށB�@nCnt���P�̃e�N�X�`���͈�ԋ߂��Ŏ~�܂�
			if(g_gposPolygon[nCnt].y > GAKUTYOU_BEAM_LONG - (GAKUTYOU_BEAM_LONG / GAKUTYOU_TEXTURE_NUM * nCnt))
			{
				g_gposPolygon[nCnt].y -= GAKUTYOU_BEAM_NOBI_SPEED;

				//�w���搶�̏��o�^�E���b�N
				g_gVtxBuffPolygon[nCnt]->Lock(0,0,(void**)&g_gVtx,0);

				//���_���̐ݒ�
				g_gVtx[0].pos.x = g_gposPolygon[nCnt].x + sinf(g_grotPolygon[nCnt].z + g_gAnglePolygon) * g_gLengthPolygon;
				g_gVtx[0].pos.y = g_gposPolygon[nCnt].y + cosf(g_grotPolygon[nCnt].z + g_gAnglePolygon) * g_gLengthPolygon;
				g_gVtx[0].pos.z = 0;

				g_gVtx[1].pos.x = g_gposPolygon[nCnt].x + sinf(g_grotPolygon[nCnt].z - g_gAnglePolygon) * g_gLengthPolygon;
				g_gVtx[1].pos.y = g_gposPolygon[nCnt].y + cosf(g_grotPolygon[nCnt].z - g_gAnglePolygon) * g_gLengthPolygon;
				g_gVtx[1].pos.z = 0;

				g_gVtx[2].pos.x = g_gposPolygon[nCnt].x + sinf(g_grotPolygon[nCnt].z - g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
				g_gVtx[2].pos.y = g_gposPolygon[nCnt].y + cosf(g_grotPolygon[nCnt].z - g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
				g_gVtx[2].pos.z = 0;

				g_gVtx[3].pos.x = g_gposPolygon[nCnt].x + sinf(g_grotPolygon[nCnt].z + g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
				g_gVtx[3].pos.y = g_gposPolygon[nCnt].y + cosf(g_grotPolygon[nCnt].z + g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
				g_gVtx[3].pos.z = 0;
	
				//���b�N�̉���
				g_gVtxBuffPolygon[nCnt]->Unlock();
			}

			//�r�[���̐�[���ő�܂ł̂т���PHAZE�ڍs
			if(g_gposPolygon[nCnt].y <= 100)
			{
				BEAM_TIME++;
				if(BEAM_TIME >= 60)
				{
					BEAM_PHAZE++;
					BEAM_TIME = 0;
					for(int Junbi_Cnt = 1;Junbi_Cnt < GAKUTYOU_TEXTURE_NUM;Junbi_Cnt++)
					{
						g_gposPolygon_PHAZE3[Junbi_Cnt].x = g_gposPolygon[Junbi_Cnt].x;
						g_gposPolygon_PHAZE3[Junbi_Cnt].y = g_gposPolygon[Junbi_Cnt].y;
					}
				}
			}
		}
	}

	//PHAZE 3 �ガ����
	if(BEAM_PHAZE == 3)
	{
		for(int nCnt = 1;nCnt < GAKUTYOU_TEXTURE_NUM;nCnt++)
		{
			g_grotPolygon[nCnt].z += g_gposrotPolygon[nCnt].z + (D3DX_PI / GAKUTYOU_BEAM_ROLL_SPEED);
			g_gposrotPolygon[nCnt].z = g_gposrotPolygon[nCnt].z + (D3DX_PI / GAKUTYOU_BEAM_ROLL_SPEED);

			//�r�[���̍��W�̌v�Z
			g_gposPolygon[nCnt].x = SCREEN_WIDTH / 2 + sinf(g_gposrotPolygon[nCnt].z) * (g_gposPolygon_PHAZE3[nCnt].y + GAKUTYOU_POLYGON_TATELONG);
			g_gposPolygon[nCnt].y = SCREEN_HEIGHT / 2 + cosf(g_gposrotPolygon[nCnt].z) * (g_gposPolygon_PHAZE3[nCnt].y + GAKUTYOU_POLYGON_TATELONG);

			//�w���搶�̏��o�^�E���b�N
			g_gVtxBuffPolygon[nCnt]->Lock(0,0,(void**)&g_gVtx,0);

			//���_���̐ݒ�
			g_gVtx[0].pos.x = g_gposPolygon[nCnt].x + sinf(g_grotPolygon[nCnt].z + g_gAnglePolygon) * g_gLengthPolygon;
			g_gVtx[0].pos.y = g_gposPolygon[nCnt].y + cosf(g_grotPolygon[nCnt].z + g_gAnglePolygon) * g_gLengthPolygon;
			g_gVtx[0].pos.z = 0;

			g_gVtx[1].pos.x = g_gposPolygon[nCnt].x + sinf(g_grotPolygon[nCnt].z - g_gAnglePolygon) * g_gLengthPolygon;
			g_gVtx[1].pos.y = g_gposPolygon[nCnt].y + cosf(g_grotPolygon[nCnt].z - g_gAnglePolygon) * g_gLengthPolygon;
			g_gVtx[1].pos.z = 0;

			g_gVtx[2].pos.x = g_gposPolygon[nCnt].x + sinf(g_grotPolygon[nCnt].z - g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
			g_gVtx[2].pos.y = g_gposPolygon[nCnt].y + cosf(g_grotPolygon[nCnt].z - g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
			g_gVtx[2].pos.z = 0;

			g_gVtx[3].pos.x = g_gposPolygon[nCnt].x + sinf(g_grotPolygon[nCnt].z + g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
			g_gVtx[3].pos.y = g_gposPolygon[nCnt].y + cosf(g_grotPolygon[nCnt].z + g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
			g_gVtx[3].pos.z = 0;
	
			//���b�N�̉���
			g_gVtxBuffPolygon[nCnt]->Unlock();
		}

		if(g_grotPolygon[1].z >= D3DX_PI * 41)
		{
			BEAM_PHAZE++;
			BEAM_TIME = -60;
			BOOMBOOMBOOM = true;
		}
	}

	//PHAZE 4 ����
	if(BEAM_PHAZE == 4)
	{
		BEAM_TIME++;

		for(int nCnt = 1;nCnt < GAKUTYOU_TEXTURE_NUM;nCnt++)
		{
			if(BEAM_TIME >= 0.5f * (GAKUTYOU_TEXTURE_NUM - nCnt))
			{
				//�w���搶�̏��o�^�E���b�N
				g_gVtxBuffPolygon[nCnt]->Lock(0,0,(void**)&g_gVtx,0);

				g_gVtx[0].pos = D3DXVECTOR3(-400,-400,0.0f);
				g_gVtx[1].pos = D3DXVECTOR3(-400,-400,0.0f);
				g_gVtx[2].pos = D3DXVECTOR3(-400,-400,0.0f);
				g_gVtx[3].pos = D3DXVECTOR3(-400,-400,0.0f);
		
				//���b�N�̉���
				g_gVtxBuffPolygon[nCnt]->Unlock();
			}
		}
		
		if(BEAM_TIME >= 20 * (GAKUTYOU_TEXTURE_NUM - 1))
		{
			BEAM_PHAZE++;
			BEAM_PHAZE = 0;
			BEAM_START = 0;
			BEAM_TIME = 0;

			
		}
	}

	//PHAZE 5 ������
	if(BEAM_PHAZE == 5)
	{
		for(int nCnt = 1;nCnt < GAKUTYOU_TEXTURE_NUM;nCnt++)
		{
			

			
		}
		BEAM_PHAZE = 0;
		BEAM_START = 0;
		BEAM_TIME = 0;
	}
}

//��---------------------------------��
//�̕`�揈��
//��---------------------------------��
void DrawMasaru(void)
{
	//���S�̊w���̕`��
	//�Q�[���|���S���̕`��
	GetDevice()->SetStreamSource(0,g_gVtxBuffPolygon[0],0,sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	GetDevice()->SetFVF(FVF_VERTEX_2D);	
	//�e�N�X�`���̐ݒ�
	GetDevice()->SetTexture(0,g_gTexturePolygon[0]);
	//�|���S���̕`��
	GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,GAKUTYOU_POLYGON_NUM);	//�^�񒆂�0�͊J�n���钸�_�C���f�b�N�X

	//�G�t�F�N�g�����@���鏈��
	GetDevice()->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	GetDevice()->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	GetDevice()->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
	

	if(BEAM_PHAZE > 0)
	{
		//�ŏ��̃I���W�i���w���ȊO�̕`��
		for(int Cnt = 1;Cnt < GAKUTYOU_TEXTURE_NUM;Cnt++)
		{
			//�Q�[���|���S���̕`��
			GetDevice()->SetStreamSource(0,g_gVtxBuffPolygon[Cnt],0,sizeof(VERTEX_2D));
			//���_�t�H�[�}�b�g�̐ݒ�
			GetDevice()->SetFVF(FVF_VERTEX_2D);	
			//�e�N�X�`���̐ݒ�
			GetDevice()->SetTexture(0,g_gTexturePolygon[0]);
			//�|���S���̕`��
			GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);	//�^�񒆂�0�͊J�n���钸�_�C���f�b�N�X
		}
	}

	//�G�t�F�N�g�����ɖ߂�
	GetDevice()->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	GetDevice()->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	GetDevice()->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

}


void SetBeam(bool gakutyouJudge)
{
	BOOMBOOMBOOM = gakutyouJudge;
}

bool GetBeam(void)
{
	return BOOMBOOMBOOM;
}

void SetBeamEnemy(bool gakutyouJudgeEnemy)
{
	BOOMBOOMBOOMEnemy = gakutyouJudgeEnemy;
}

bool GetBeamEnemy(void)
{
	return BOOMBOOMBOOMEnemy;
}