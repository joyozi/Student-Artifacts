//��-------------------------------------------------------------------------��
//
//	�G�l�~�[cpp�t�@�C��[enemy.cpp]
//	AT12A271�@�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "enemy.h"
#include "explosion.h"
#include "hitjudge.h"
#include "score.h"
#include "sound.h"
#include "gakutyou.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 e_pTexturePolygon[3];
LPDIRECT3DVERTEXBUFFER9 e_pVtxBuffPolygon[ENEMY_NUM];

VERTEX_2D *e_pVtx;						//�摜�̍��W�̃|�C���^
D3DXVECTOR3 e_fposPolygon[ENEMY_NUM];	//���S�̍��W
D3DXVECTOR3 e_frotPolygon[ENEMY_NUM];	//��]�̈ړ���
float e_fLengthPolygon;					//�Ίp���̒���
float e_fAnglePolygon;					//�Ίp���̊p�x
bool startPopjudge[ENEMY_NUM];			//��ԍŏ��ɓG�̏o�Ă���^�C�~���O���炵�@����ƓG�̏o��
int timeCnt;							//�ŏ������̃J�E���g
int startPopCnt;						//
int SecondtimeCnt;						//�Ԃ̏o���J�E���g�������Ə����������łO�ɂ��� �����z��̔ԍ��̎Ԃ��Ăяo�Ă���悤�ɂ���
bool explosion_hikisuu[ENEMY_NUM];		//true�̂Ƃ��ɔ��������ɖ��߂���

int WhatCar[ENEMY_NUM];					//�Ԃ̎�ނ����߂�

//��-------------------------------------------------------------------------��
//����������
//��-------------------------------------------------------------------------��
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	srand((unsigned)time(NULL));		//�Ԃ̏o���ʒu�ƎԂ̎�ނ������_���Ɍ��肷�邽�߂Ƀ����_��

	for(int nCnt = 0; nCnt < ENEMY_NUM;nCnt++)
	{
		startPopjudge[nCnt] = false;
		explosion_hikisuu[nCnt] = false;

		//�Ԃ̎�ނ����߂�
		WhatCar[nCnt] = rand()%3;

		e_pVtxBuffPolygon[nCnt] = NULL;
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*ENEMY_TYOUTEN_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&e_pVtxBuffPolygon[nCnt],NULL);
		
		//�G�l�~�[�̏��o�^�E���b�N
		e_pVtxBuffPolygon[nCnt]->Lock(0,0,(void**)&e_pVtx,0);
		
		//���_���̐ݒ�
		e_pVtx[nCnt * 4].pos = D3DXVECTOR3(460.0f,250.0f,0.0f);
		e_pVtx[1 + (nCnt * 4)].pos = D3DXVECTOR3(510.0f,250.0f,0.0f);
		e_pVtx[2 + (nCnt * 4)].pos = D3DXVECTOR3(460.0f,350.0f,0.0f);
		e_pVtx[3 + (nCnt * 4)].pos = D3DXVECTOR3(510.0f,350.0f,0.0f);

		e_pVtx[0 + (nCnt * 4)].rhw = 1.0f;
		e_pVtx[1 + (nCnt * 4)].rhw = 1.0f;
		e_pVtx[2 + (nCnt * 4)].rhw = 1.0f;
		e_pVtx[3 + (nCnt * 4)].rhw = 1.0f;

		e_pVtx[0 + (nCnt * 4)].col = D3DCOLOR_RGBA(255,255,255,255);
		e_pVtx[1 + (nCnt * 4)].col = D3DCOLOR_RGBA(255,255,255,255);
		e_pVtx[2 + (nCnt * 4)].col = D3DCOLOR_RGBA(255,255,255,255);
		e_pVtx[3 + (nCnt * 4)].col = D3DCOLOR_RGBA(255,255,255,255);

		e_pVtx[0 + (nCnt * 4)].tex = D3DXVECTOR2(0.0,0.0);
		e_pVtx[1 + (nCnt * 4)].tex = D3DXVECTOR2(1.0,0.0);
		e_pVtx[2 + (nCnt * 4)].tex = D3DXVECTOR2(0.0,1.0);
		e_pVtx[3 + (nCnt * 4)].tex = D3DXVECTOR2(1.0,1.0);
		//���b�N�̉���
		e_pVtxBuffPolygon[nCnt]->Unlock();
	}

	for(int i = 0;i < 3;i++)
	{
		e_pTexturePolygon[i] = NULL;
	}

	//�Ԃ̎Ԏ�������_���Ɍ��߂�
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/car000.png",&e_pTexturePolygon[0]);
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/car001.png",&e_pTexturePolygon[1]);
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/car002.png",&e_pTexturePolygon[2]);

	e_fLengthPolygon = sqrtf((ENEMY_WIDTH / 2)  * (ENEMY_WIDTH / 2) + (ENEMY_HEIGHT / 2) * (ENEMY_HEIGHT / 2));
	e_fAnglePolygon = atan2f(ENEMY_WIDTH,ENEMY_HEIGHT);
	
	timeCnt = -180;
	startPopCnt = 0;
}

//��---------------------------------��
//�I������
//��---------------------------------��
void UninitEnemy(void)
{
	for(int nCnt = 0; nCnt < ENEMY_NUM;nCnt++)
	{
		//�o�b�t�@�̏���
		if(e_pVtxBuffPolygon[nCnt] != NULL)
		{
			e_pVtxBuffPolygon[nCnt]->Release();
			e_pVtxBuffPolygon[nCnt] = NULL;
		}
	}
	
	for(int nCnt = 0; nCnt < 3;nCnt++)
	{
		//�e�N�X�`���̏���
		if(e_pTexturePolygon[nCnt] != NULL)
		{
			e_pTexturePolygon[nCnt]->Release();
			e_pTexturePolygon[nCnt] = NULL;
		}
	}
}
//��---------------------------------��
//�̍X�V����
//��---------------------------------��
void UpdateEnemy(void)
{
	timeCnt++;
	//ENEMY_POP_TIME�b���ƂɓG���o��������
	if(timeCnt > ENEMY_POP_TIME)
	{
		startPopjudge[startPopCnt] = true;
		explosion_hikisuu[startPopCnt] = false;
		e_frotPolygon[startPopCnt].z = D3DX_PI * ((rand()%200) * 0.01f);
		e_fposPolygon[startPopCnt].x = (SCREEN_WIDTH / 2) - (SCREEN_WIDTH / 2) * sinf(e_frotPolygon[startPopCnt].z);
		e_fposPolygon[startPopCnt].y = (SCREEN_WIDTH / 2) - (SCREEN_WIDTH / 2) * cosf(e_frotPolygon[startPopCnt].z);
		
		//�J�E���g�̃N���A
		timeCnt = 0;

		//���̔z��̏����ɓ���
		startPopCnt++;
		//�����z�񂪍Ō�܂ōs������ŏ��ɖ߂�
		if(startPopCnt >= ENEMY_NUM)
		{
			startPopCnt = 0;
		}
	}
	
	//�Ԃ̈ړ������������蔻��
	for(int nCnt = 0;nCnt < ENEMY_NUM; nCnt++)
	{
		if(startPopjudge[nCnt] == true)
		{
			e_fposPolygon[nCnt].x += ENEMY_SPEED * sinf(e_frotPolygon[nCnt].z);
			e_fposPolygon[nCnt].y += ENEMY_SPEED * cosf(e_frotPolygon[nCnt].z);

			//�����蔻��
			SetHitJudge_Enemy(e_fposPolygon[nCnt],e_frotPolygon[nCnt],nCnt);
			//�����蔻��̌v�Z
			UpdateHitJudge();
			//����̖߂�l�󂯎��
			startPopjudge[nCnt] = GetHitJudge();

			//�w���C�̌��ʓK�p
			if(GetBeam() == true)
			{
				for(int gakutyouCnt = 0;gakutyouCnt < ENEMY_NUM; gakutyouCnt++)
				{
					if(startPopjudge[gakutyouCnt] == true)
					{
						startPopjudge[gakutyouCnt] = false;
						SetExplosion(startPopjudge[gakutyouCnt],e_fposPolygon[gakutyouCnt],gakutyouCnt);

						
						
						GetScore();
						
						

						PlaySound(SOUND_LABEL_SE_sen_ge_bom18);
					}
				}
				SetBeam(false);
			}

			//�j��ł�������T
			if(GetHitJudge() == false)
			{
				PlaySound(SOUND_LABEL_SE_bomb000);
				GetScore();
			}
			


			//�w���ɋ߂Â�������������鏈��
			if((SCREEN_WIDTH / 2) - ENEMY_DEADLINE < e_fposPolygon[nCnt].x && (SCREEN_WIDTH / 2) + ENEMY_DEADLINE > e_fposPolygon[nCnt].x)
			{
				if((SCREEN_HEIGHT / 2) - ENEMY_DEADLINE < e_fposPolygon[nCnt].y && (SCREEN_HEIGHT / 2) + ENEMY_DEADLINE > e_fposPolygon[nCnt].y)
				{
					//
					startPopjudge[nCnt] = false;
				}
			}
			//�G�����������甚���̖���
			if(startPopjudge[nCnt] == false)
			{
				//�Ԃ̈ʒu�Ɣ��������Ƃ�������Ɣz��̈ʒu��������
				SetExplosion(startPopjudge[nCnt],e_fposPolygon[nCnt],nCnt);
				PlaySound(SOUND_LABEL_SE_bomb000);
			}
		}
	}

	for(int nCnt = 0;nCnt < ENEMY_NUM; nCnt++)
	{
		//�G�l�~�[�̏��o�^�E���b�N
		e_pVtxBuffPolygon[nCnt]->Lock(0,0,(void**)&e_pVtx,0);

		e_pVtx[0 + (nCnt * 4)].pos.x = e_fposPolygon[nCnt].x + sinf(e_frotPolygon[nCnt].z + e_fAnglePolygon) * e_fLengthPolygon;
		e_pVtx[0 + (nCnt * 4)].pos.y = e_fposPolygon[nCnt].y + cosf(e_frotPolygon[nCnt].z + e_fAnglePolygon) * e_fLengthPolygon;
		e_pVtx[0 + (nCnt * 4)].pos.z = 0.0f;

		e_pVtx[1 + (nCnt * 4)].pos.x = e_fposPolygon[nCnt].x + sinf(e_frotPolygon[nCnt].z - e_fAnglePolygon) * e_fLengthPolygon;
		e_pVtx[1 + (nCnt * 4)].pos.y = e_fposPolygon[nCnt].y + cosf(e_frotPolygon[nCnt].z - e_fAnglePolygon) * e_fLengthPolygon;
		e_pVtx[1 + (nCnt * 4)].pos.z = 0.0f;

		e_pVtx[2 + (nCnt * 4)].pos.x = e_fposPolygon[nCnt].x + sinf(e_frotPolygon[nCnt].z - e_fAnglePolygon + (D3DX_PI)) * e_fLengthPolygon;
		e_pVtx[2 + (nCnt * 4)].pos.y = e_fposPolygon[nCnt].y + cosf(e_frotPolygon[nCnt].z - e_fAnglePolygon + (D3DX_PI)) * e_fLengthPolygon;
		e_pVtx[2 + (nCnt * 4)].pos.z = 0.0f;

		e_pVtx[3 + (nCnt * 4)].pos.x = e_fposPolygon[nCnt].x + sinf(e_frotPolygon[nCnt].z + e_fAnglePolygon + (D3DX_PI)) * e_fLengthPolygon;
		e_pVtx[3 + (nCnt * 4)].pos.y = e_fposPolygon[nCnt].y + cosf(e_frotPolygon[nCnt].z + e_fAnglePolygon + (D3DX_PI)) * e_fLengthPolygon;
		e_pVtx[3 + (nCnt * 4)].pos.z = 0.0f;
		
		//���b�N�̉���
		e_pVtxBuffPolygon[nCnt]->Unlock();
	}
}

//��---------------------------------��
//�̕`�揈��
//��---------------------------------��
void DrawEnemy(void)
{
	for(int nCnt = 0;nCnt < ENEMY_NUM;nCnt++)
	{
		if(startPopjudge[nCnt] == true)
		{
			//�w�i�̕`��
			GetDevice()->SetStreamSource(0,e_pVtxBuffPolygon[nCnt],0,sizeof(VERTEX_2D));
			//���_�t�H�[�}�b�g�̐ݒ�
			GetDevice()->SetFVF(FVF_VERTEX_2D);
			//�e�N�X�`���̐ݒ�
			GetDevice()->SetTexture(0,e_pTexturePolygon[WhatCar[nCnt]]);
			//�|���S���̕`��
			GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,ENEMY_POLYGON_NUM);
		}
	}
}
