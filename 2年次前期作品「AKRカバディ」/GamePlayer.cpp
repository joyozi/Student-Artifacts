//��-------------------------------------------------------------------------��
//
//	�Q�[���|���S��cpp�t�@�C��[polygon.cpp]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "GamePlayer.h"
#include "input.h"
#include "hitjudge.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 g_pTexturePolygon[GamePlayer_texturenum];
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon[GamePlayer_texturenum];
int g_nCounterAnim = 0;
int g_nPatternAnim = 0;
int g_nPatternAnimTATE = 0;
VERTEX_2D *g_pVtx;				//�摜�̍��W�̃|�C���^
D3DXVECTOR3 g_posPolygon;		//���S�̍��W
D3DXVECTOR3 g_rotPolygon;		//��]�̈ړ���
float g_fLengthPolygon;			//�Ίp���̒���
float g_fAnglePolygon;			//�Ίp���̊p�x
float g_fNobiPolygon;			//�搶�̒��S����̋���
D3DXVECTOR3 g_posrotPolygon;	//�搶�̉摜�̉�]���Ă���p�x
//��-------------------------------------------------------------------------��
//�Q�[���|���S���̏���������
//��-------------------------------------------------------------------------��
void InitGamePolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	for(int Cnt = 0;Cnt < GamePlayer_texturenum;Cnt++)
	{
		g_pVtxBuffPolygon[Cnt] = NULL;
		g_pTexturePolygon[Cnt] = NULL;

		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*TYOUTEN_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffPolygon[Cnt],NULL);
	}

	//�����j���O�}���̏��o�^�E���b�N
	g_pVtxBuffPolygon[0]->Lock(0,0,(void**)&g_pVtx,0);

	//���_���̐ݒ�
	g_pVtx[0].pos = D3DXVECTOR3(260.0f,200.0f,0.0f);
	g_pVtx[1].pos = D3DXVECTOR3(360.0f,200.0f,0.0f);
	g_pVtx[2].pos = D3DXVECTOR3(260.0f,300.0f,0.0f);
	g_pVtx[3].pos = D3DXVECTOR3(360.0f,300.0f,0.0f);

	g_pVtx[0].rhw = 1.0f;
	g_pVtx[1].rhw = 1.0f;
	g_pVtx[2].rhw = 1.0f;
	g_pVtx[3].rhw = 1.0f;

	g_pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	g_pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	g_pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	g_pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	g_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	g_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	g_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	g_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);
			
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/akira000.png",&g_pTexturePolygon[0]);
	
	//���b�N�̉���
	g_pVtxBuffPolygon[0]->Unlock();

	g_posPolygon.x = (SCREEN_WIDTH / 2);
	g_posPolygon.y = (SCREEN_HEIGHT / 2 - POLYGON_HANKEI);
	g_rotPolygon.x = 0;
	g_rotPolygon.y = 0;
	g_rotPolygon.z = 0;
	g_fLengthPolygon = sqrtf((POLYGON_YOKOLONG / 2)  * (POLYGON_YOKOLONG / 2) + (POLYGON_TATELONG / 2) * (POLYGON_TATELONG / 2));
	g_fAnglePolygon = atan2f(POLYGON_YOKOLONG,POLYGON_TATELONG);
	g_posrotPolygon.x = D3DX_PI;
	g_posrotPolygon.y = D3DX_PI;
	g_fNobiPolygon = POLYGON_HANKEI;

	//�{�̂̍��W�ʒu���o���b�g�Ƃ����蔻��ɋ�����
	SetHitJudge_Player(g_posPolygon,g_rotPolygon);
}
//-------------------------------------
//�Q�[���|���S���I������
//-------------------------------------
void UninitGamePolygon(void)
{
	for(int Cnt = 0;Cnt < GamePlayer_texturenum;Cnt++)
	{
		//�o�b�t�@�̏���
		if(g_pVtxBuffPolygon[Cnt] != NULL)
		{
			g_pVtxBuffPolygon[Cnt]->Release();
			g_pVtxBuffPolygon[Cnt] = NULL;
		}

		//�e�N�X�`���̏���
		if(g_pTexturePolygon[Cnt] != NULL)
		{
			g_pTexturePolygon[Cnt]->Release();
			g_pTexturePolygon[Cnt] = NULL;
		}
	}
}
//-------------------------------------
//�Q�[���|���S���̍X�V����
//-------------------------------------
void UpdateGamePolygon(void)
{
	D3DXVECTOR3 g_posPolygonOld;	//�ЂƂO�̍��W �o���b�g�p

	g_posPolygonOld.x = g_posPolygon.x;
	g_posPolygonOld.y = g_posPolygon.y;

	//�搶�̉��ړ�
	if(GetKeyboardPress(DIK_A) == true)
	{
		//�搶�̉摜�̉�]
		g_rotPolygon.x = g_rotPolygon.x + (D3DX_PI / GAMEPLAYER_SPEED);
		g_rotPolygon.y = g_rotPolygon.y + (D3DX_PI / GAMEPLAYER_SPEED);
		//�搶�̈ʒu�̉�]
		g_posrotPolygon.x = g_posrotPolygon.x + (D3DX_PI / GAMEPLAYER_SPEED);
		g_posrotPolygon.y = g_posrotPolygon.y + (D3DX_PI / GAMEPLAYER_SPEED);
	}

	if(GetKeyboardPress(DIK_D) == true)
	{
		//�搶�̉摜�̉�]
		g_rotPolygon.x = g_rotPolygon.x - (D3DX_PI / GAMEPLAYER_SPEED);
		g_rotPolygon.y = g_rotPolygon.y - (D3DX_PI / GAMEPLAYER_SPEED);
		//�搶�̈ʒu�̉�]
		g_posrotPolygon.x = g_posrotPolygon.x - (D3DX_PI / GAMEPLAYER_SPEED);
		g_posrotPolygon.y = g_posrotPolygon.y - (D3DX_PI / GAMEPLAYER_SPEED);
	}

	if(GetKeyboardPress(DIK_W) == true)
	{
		g_fNobiPolygon += GAMEPLAYER_TATE_SPEED;
		//������ʊO�ɍs�����Ƃ�����ЂƂO�ɖ߂�
		if(g_fNobiPolygon > SCREEN_WIDTH / 2)
		{
			g_fNobiPolygon -= GAMEPLAYER_TATE_SPEED;
		}
	}

	if(GetKeyboardPress(DIK_S) == true)
	{
		g_fNobiPolygon -= GAMEPLAYER_TATE_SPEED;
		//�������S��������������ЂƂO�̈ʒu�ɖ߂�
		if(g_fNobiPolygon < 80)
		{
			g_fNobiPolygon += GAMEPLAYER_TATE_SPEED;
		}
	}

	//�搶�̍��W�̌v�Z
	g_posPolygon.x = POLYGON_YOKO + sinf(g_posrotPolygon.x) * g_fNobiPolygon;
	g_posPolygon.y = POLYGON_TATE + cosf(g_posrotPolygon.y) * g_fNobiPolygon;

	//���W�Ƃ��̃��b�N�E�A�����b�N

	g_pVtxBuffPolygon[0]->Lock(0,0,(void**)&g_pVtx,0);
	
	g_pVtx[0].pos.x = g_posPolygon.x + sinf(g_rotPolygon.x + g_fAnglePolygon) * g_fLengthPolygon;
	g_pVtx[0].pos.y = g_posPolygon.y + cosf(g_rotPolygon.y + g_fAnglePolygon) * g_fLengthPolygon;
	g_pVtx[0].pos.z = 0.0f;

	g_pVtx[1].pos.x = g_posPolygon.x + sinf(g_rotPolygon.x - g_fAnglePolygon) * g_fLengthPolygon;
	g_pVtx[1].pos.y = g_posPolygon.y + cosf(g_rotPolygon.y - g_fAnglePolygon) * g_fLengthPolygon;
	g_pVtx[1].pos.z = 0.0f;

	g_pVtx[2].pos.x = g_posPolygon.x + sinf(g_rotPolygon.x - g_fAnglePolygon + (D3DX_PI)) * g_fLengthPolygon;
	g_pVtx[2].pos.y = g_posPolygon.y + cosf(g_rotPolygon.y - g_fAnglePolygon + (D3DX_PI)) * g_fLengthPolygon;
	g_pVtx[2].pos.z = 0.0f;

	g_pVtx[3].pos.x = g_posPolygon.x + sinf(g_rotPolygon.x + g_fAnglePolygon + (D3DX_PI)) * g_fLengthPolygon;
	g_pVtx[3].pos.y = g_posPolygon.y + cosf(g_rotPolygon.y + g_fAnglePolygon + (D3DX_PI)) * g_fLengthPolygon;
	g_pVtx[3].pos.z = 0.0f;

	g_pVtxBuffPolygon[0]->Unlock();

	//�{�̂̍��W�ʒu���o���b�g�Ƃ����蔻��ɋ�����
	SetHitJudge_Player(g_posPolygon,g_rotPolygon);
}
//-------------------------------------
//�Q�[���|���S���̕`�揈��
//-------------------------------------
void DrawGamePolygon(void)
{
	for(int Cnt = 0;Cnt < GamePlayer_texturenum;Cnt++)
	{
		//�Q�[���|���S���̕`��
		GetDevice()->SetStreamSource(0,g_pVtxBuffPolygon[Cnt],0,sizeof(VERTEX_2D));
		//���_�t�H�[�}�b�g�̐ݒ�
		GetDevice()->SetFVF(FVF_VERTEX_2D);	
		//�e�N�X�`���̐ݒ�
		GetDevice()->SetTexture(0,g_pTexturePolygon[Cnt]);
		//�|���S���̕`��
		GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,POLYGON_NUM);	//�^�񒆂�0�͊J�n���钸�_�C���f�b�N�X
	}
}