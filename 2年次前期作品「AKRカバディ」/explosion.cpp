//��-------------------------------------------------------------------------��
//
//	����cpp�t�@�C��[explosion.cpp]
//	AT12A271�@�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "explosion.h"
#include "enemy.h"
//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 x_eTexturePolygon[ENEMY_NUM];		//�G�̐����������̐�������
LPDIRECT3DVERTEXBUFFER9 x_eVtxBuffPolygon[ENEMY_NUM];	//
VERTEX_2D *x_eVtx;						//�摜�̍��W�̃|�C���^

float x_eLengthPolygon;					//�Ίp���̒���
float x_eAnglePolygon;					//�Ίp���̊p�x
bool Explosion_Judge[ENEMY_NUM];		//�������邩�ǂ���
D3DXVECTOR3 x_eposPolygon[ENEMY_NUM];	//���S�̍��W
D3DXVECTOR3 x_erotPolygon[ENEMY_NUM];	//��]�̈ړ���

//��-------------------------------------------------------------------------��
//��������������
//��-------------------------------------------------------------------------��
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	for(int nCnt = 0; nCnt < ENEMY_NUM;nCnt++)
	{
		x_eTexturePolygon[nCnt] = NULL;
		x_eVtxBuffPolygon[nCnt] = NULL;

		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*ENEMY_TYOUTEN_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&x_eVtxBuffPolygon[nCnt],NULL);
		
		//�G�l�~�[�̏��o�^�E���b�N
		x_eVtxBuffPolygon[nCnt]->Lock(0,0,(void**)&x_eVtx,0);

		//���_���̐ݒ�

		x_eVtx[0 + (nCnt * 4)].rhw = 1.0f;
		x_eVtx[1 + (nCnt * 4)].rhw = 1.0f;
		x_eVtx[2 + (nCnt * 4)].rhw = 1.0f;
		x_eVtx[3 + (nCnt * 4)].rhw = 1.0f;

		x_eVtx[0 + (nCnt * 4)].col = D3DCOLOR_RGBA(255,255,255,200);
		x_eVtx[1 + (nCnt * 4)].col = D3DCOLOR_RGBA(255,255,255,200);
		x_eVtx[2 + (nCnt * 4)].col = D3DCOLOR_RGBA(255,255,255,200);
		x_eVtx[3 + (nCnt * 4)].col = D3DCOLOR_RGBA(255,255,255,200);

		x_eVtx[0 + (nCnt * 4)].tex = D3DXVECTOR2(0.0,0.0);
		x_eVtx[1 + (nCnt * 4)].tex = D3DXVECTOR2(1.0,0.0);
		x_eVtx[2 + (nCnt * 4)].tex = D3DXVECTOR2(0.0,0.5);
		x_eVtx[3 + (nCnt * 4)].tex = D3DXVECTOR2(1.0,0.5);

		D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/explosion.png",&x_eTexturePolygon[nCnt]);

		//���b�N�̉���
		x_eVtxBuffPolygon[nCnt]->Unlock();
		
		//���낢��ȏ�����
		Explosion_Judge[nCnt] = true;
		
		x_eposPolygon[nCnt].x = 0;
		x_eposPolygon[nCnt].y = 0;

		x_erotPolygon[nCnt].x = 0;
		x_erotPolygon[nCnt].y = 0;
		x_erotPolygon[nCnt].z = 0;
	}

	x_eLengthPolygon = sqrtf((EXPLOSION_HANKEI / 2)  * (EXPLOSION_HANKEI / 2) + (EXPLOSION_HANKEI / 2) * (EXPLOSION_HANKEI / 2));
	x_eAnglePolygon = atan2f(EXPLOSION_HANKEI,EXPLOSION_HANKEI);
}

//��---------------------------------��
//�����I������
//��---------------------------------��
void UninitExplosion(void)
{
	for(int nCnt = 0; nCnt < ENEMY_NUM;nCnt++)
	{
		//�o�b�t�@�̏���
		if(x_eVtxBuffPolygon[nCnt] != NULL)
		{
			x_eVtxBuffPolygon[nCnt]->Release();
			x_eVtxBuffPolygon[nCnt] = NULL;
		}

		//�e�N�X�`���̏���
		if(x_eTexturePolygon[nCnt] != NULL)
		{
			x_eTexturePolygon[nCnt]->Release();
			x_eTexturePolygon[nCnt] = NULL;
		}
	}
}
//��---------------------------------��
//�����̍X�V����
//��---------------------------------��
void UpdateExplosion(void)
{
	static int explosion_cnt[ENEMY_NUM];

	for(int nCnt = 0;nCnt < ENEMY_NUM;nCnt++)
	{
		if(Explosion_Judge[nCnt] == false)
		{
			explosion_cnt[nCnt]++;
			
			//�G�l�~�[�̏��o�^�E���b�N
			x_eVtxBuffPolygon[nCnt]->Lock(0,0,(void**)&x_eVtx,0);

			x_eVtx[nCnt * 4].pos.x = x_eposPolygon[nCnt].x + sinf(x_erotPolygon[nCnt].z + x_eAnglePolygon) * x_eLengthPolygon;
			x_eVtx[nCnt * 4].pos.y = x_eposPolygon[nCnt].y + cosf(x_erotPolygon[nCnt].z + x_eAnglePolygon) * x_eLengthPolygon;
			x_eVtx[nCnt * 4].pos.z = 0.0f;

			x_eVtx[1 + (nCnt * 4)].pos.x = x_eposPolygon[nCnt].x + sinf(x_erotPolygon[nCnt].z - x_eAnglePolygon) * x_eLengthPolygon;
			x_eVtx[1 + (nCnt * 4)].pos.y = x_eposPolygon[nCnt].y + cosf(x_erotPolygon[nCnt].z - x_eAnglePolygon) * x_eLengthPolygon;
			x_eVtx[1 + (nCnt * 4)].pos.z = 0.0f;

			x_eVtx[2 + (nCnt * 4)].pos.x = x_eposPolygon[nCnt].x + sinf(x_erotPolygon[nCnt].z - x_eAnglePolygon + (D3DX_PI)) * x_eLengthPolygon;
			x_eVtx[2 + (nCnt * 4)].pos.y = x_eposPolygon[nCnt].y + cosf(x_erotPolygon[nCnt].z - x_eAnglePolygon + (D3DX_PI)) * x_eLengthPolygon;
			x_eVtx[2 + (nCnt * 4)].pos.z = 0.0f;

			x_eVtx[3 + (nCnt * 4)].pos.x = x_eposPolygon[nCnt].x + sinf(x_erotPolygon[nCnt].z + x_eAnglePolygon + (D3DX_PI)) * x_eLengthPolygon;
			x_eVtx[3 + (nCnt * 4)].pos.y = x_eposPolygon[nCnt].y + cosf(x_erotPolygon[nCnt].z + x_eAnglePolygon + (D3DX_PI)) * x_eLengthPolygon;
			x_eVtx[3 + (nCnt * 4)].pos.z = 0.0f;

			//���b�N�̉���
			x_eVtxBuffPolygon[nCnt]->Unlock();
		
			//���b��������I���
			if(explosion_cnt[nCnt] >= EXPLOSION_TIME)
			{
				Explosion_Judge[nCnt] = true;
				explosion_cnt[nCnt] = 0;
			}		
		}
	}
}

//��---------------------------------��
//�����̕`�揈��
//��---------------------------------��
void DrawExplosion(void)
{
	for(int nCnt = 0;nCnt < ENEMY_NUM;nCnt++)
	{
		if(Explosion_Judge[nCnt] == false)
		{
			//�w�i�̕`��
			GetDevice()->SetStreamSource(0,x_eVtxBuffPolygon[nCnt],0,sizeof(VERTEX_2D));
			//���_�t�H�[�}�b�g�̐ݒ�
			GetDevice()->SetFVF(FVF_VERTEX_2D);
			//�e�N�X�`���̐ݒ�
			GetDevice()->SetTexture(0,x_eTexturePolygon[nCnt]);
			//�|���S���̕`��
			GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,ENEMY_POLYGON_NUM);
		}
	}
}

//��---------------------------------��
//�����̎擾����
//��---------------------------------��
void SetExplosion(bool enemy_Judge,D3DXVECTOR3 pos,int RendouCnt)	//�Ԃ�enemy�̒��ŉ��Ԗڂ��𓯊�����
{
	x_eposPolygon[RendouCnt].x = pos.x;
	x_eposPolygon[RendouCnt].y = pos.y;
	Explosion_Judge[RendouCnt] = enemy_Judge;	//false�������甚��
}