//��-------------------------------------------------------------------------��
//
//	����cpp�t�@�C��[explosion.cpp]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include"main.h"
#include"explosion.h"
#include "camera.h"
#include "bullet.h"
//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 r_bgTextureExplosion;
LPDIRECT3DVERTEXBUFFER9 r_bgVtxBuffExplosion;

D3DXMATRIX g_mtxProjectionExplosion[BULLET_MAX];				//�v���W�F�N�V�����}�g���b�N�X
D3DXMATRIX g_mtxViewExplosion[BULLET_MAX];						//�r���[�}�g���b�N�X
D3DXMATRIX g_mtxWorldExplosion[BULLET_MAX];						//���[���h�}�g���b�N�X

D3DXVECTOR3 g_posExplosion[BULLET_MAX];							//�ʒu
D3DXVECTOR3 g_rotExplosion[BULLET_MAX];							//����
D3DXVECTOR3 g_sclExplosion[BULLET_MAX];							//�傫���i��{�ς��Ȃ��j

bool ExplosionJudge[BULLET_MAX];								//�\���̐���

VERTEX_3D *pVtx;												//�摜�̍��W�̃|�C���^

int g_nCounterAnim[BULLET_MAX];
int g_nPatternAnim[BULLET_MAX];

//��-------------------------------------------------------------------------��
//�����̏���������
//��-------------------------------------------------------------------------��
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 bgDevice;
	bgDevice = GetDevice();

	for(int nCnt = 0;nCnt < BULLET_MAX;nCnt++)
	{
		//****�ʒu�A�p�x�A�X�P�[���̏�����****
		g_posExplosion[nCnt] = D3DXVECTOR3(0.0f,50.0f,0.0f);
		g_rotExplosion[nCnt] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_sclExplosion[nCnt] = D3DXVECTOR3(1.0f,1.0f,1.0f);

		//�\���̏�����
		ExplosionJudge[nCnt] = false;
		g_nPatternAnim[nCnt] = 0;
		g_nCounterAnim[nCnt] = 0;
	}


	r_bgVtxBuffExplosion = NULL;
	r_bgTextureExplosion = NULL;

	//�e�N�X�`���o�b�t�@
	D3DXCreateTextureFromFile(bgDevice,"./data/TEXTURE/explosion_000.png",&r_bgTextureExplosion);

	//���_�o�b�t�@
	bgDevice -> CreateVertexBuffer(sizeof(VERTEX_3D)*4*BULLET_MAX,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&r_bgVtxBuffExplosion,NULL);

	//�摜�̏��o�^
	r_bgVtxBuffExplosion->Lock(0,0,(void**)&pVtx,0);

	//****���_�̈ʒu�̐ݒ�****
	pVtx[0].pos = D3DXVECTOR3(-30,30,0);
	pVtx[1].pos = D3DXVECTOR3(30,30,0);
	pVtx[2].pos = D3DXVECTOR3(-30,-30,0);
	pVtx[3].pos = D3DXVECTOR3(30,-30,0);

	//****�����̐ݒ�*****
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	//****�J���[�̐ݒ�****
	pVtx[0].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtx[1].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtx[2].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtx[3].col = D3DCOLOR_RGBA(255,255,255,55);

	//****tex�̐ݒ�****
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.14f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.14f,1.0f);

	r_bgVtxBuffExplosion->Unlock();
}
//-------------------------------------
//��������
//-------------------------------------
void UninitExplosion(void)
{
	//�o�b�t�@�̏���
	if(r_bgVtxBuffExplosion != NULL)
	{
		r_bgVtxBuffExplosion -> Release();
		r_bgVtxBuffExplosion = NULL;
	}

	//�e�N�X�`���̏���
	if(r_bgTextureExplosion != NULL)
	{
		r_bgTextureExplosion->Release();
		r_bgTextureExplosion = NULL;
	}
}
//-------------------------------------
//�����̃Z�b�g����
//-------------------------------------
void UpdateExplosion(void)
{

}
//-------------------------------------
//�����̕`�揈��
//-------------------------------------
void DrawExplosion(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;	
	D3DXMATRIX mtxView;						//�r���[�}�g���b�N�X
	
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	mtxView = GetMtxView();

	//�ʒu�̏�����
	for(int nCnt = 0;nCnt < BULLET_MAX;nCnt++)
	{
		//�L���Ȃ�\������
		if(ExplosionJudge[nCnt] == true)
		{
			//�����̔ԍ����Ƃ̎��Ԃ̌v�Z������
			g_nCounterAnim[nCnt]++;

			//���W�̐ݒ菈��
			r_bgVtxBuffExplosion->Lock(0,0,(void**)&pVtx,0);

			pVtx[0].tex = D3DXVECTOR2(g_nPatternAnim[nCnt]*0.14f,0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_nPatternAnim[nCnt]*0.14f)+0.14f,0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_nPatternAnim[nCnt]*0.14f,1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_nPatternAnim[nCnt]*0.14f)+0.14f,1.0f);
		
			r_bgVtxBuffExplosion->Unlock();
			
			//�E�ӈȏ�ɂȂ����玟�̃R�}�Ɉڂ�
			if(g_nCounterAnim[nCnt] > 3)
			{		
				//���̏��ԂɈڂ�
				g_nPatternAnim[nCnt]++;
				//�ŏ�����J�E���g����
				g_nCounterAnim[nCnt] = 0;
			}

			//�Ō�܂ŕ\��������I���ɂ���
			if(g_nPatternAnim[nCnt] >= 7)
			{
				g_nPatternAnim[nCnt] = 0;
				g_nCounterAnim[nCnt] = 0;
				ExplosionJudge[nCnt] = false;
			}					
		

			//------���[���h�}�g���b�N�X�Ƃ��̐ݒ�--------------------------------------------------------------

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldExplosion[nCnt]);

			//�t�s������߂�
			D3DXMatrixInverse(&g_mtxWorldExplosion[nCnt],NULL,&mtxView);

			g_mtxWorldExplosion[nCnt]._41 = 0.0f;
			g_mtxWorldExplosion[nCnt]._42 = 0.0f;
			g_mtxWorldExplosion[nCnt]._43 = 0.0f;

			//****���[���h�̐ݒ�****
			D3DXMatrixScaling(&mtxScl,g_sclExplosion[nCnt].x,g_sclExplosion[nCnt].y,g_sclExplosion[nCnt].z);				//�X�P�[���𔽉f
			D3DXMatrixMultiply(&g_mtxWorldExplosion[nCnt],&g_mtxWorldExplosion[nCnt],&mtxScl);

			//****���̑��̐ݒ�****
			D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotExplosion[nCnt].y,g_rotExplosion[nCnt].x,g_rotExplosion[nCnt].z);	//���|�@�s�b�`�@���[��

			D3DXMatrixMultiply(&g_mtxWorldExplosion[nCnt],&g_mtxWorldExplosion[nCnt],&mtxRot);
			D3DXMatrixTranslation(&mtxTranslate,g_posExplosion[nCnt].x,g_posExplosion[nCnt].y,g_posExplosion[nCnt].z);		//�ʒu�𔽉f

			D3DXMatrixMultiply(&g_mtxWorldExplosion[nCnt],&g_mtxWorldExplosion[nCnt],&mtxTranslate);

			pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldExplosion[nCnt]);	//�ݒ�
	
			//------------------------------------------------------------------------------------------

			//�G�t�F�N�g�����@���鏈��
			pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

			//****���e�X�g�̊J�n****
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF,100);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

			//----------------3D�|���S���̕`��----------------------------------------------------------

			//���_�o�b�t�@���o�C���h
			pDevice->SetStreamSource(0,r_bgVtxBuffExplosion,0,sizeof(VERTEX_3D));
			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0,r_bgTextureExplosion);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

			//------------------------------------------------------------------------------------------

			//****���e�X�g�̏I��****
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);

			//�G�t�F�N�g�����ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
		}
	}
}

//-------------------------------------
//�����̃Z�b�g����
//-------------------------------------
void SetExplosion(D3DXVECTOR3 Explosion_Pos,int BULLETNUM,bool JUDGE,int LRJudge)
{
	g_posExplosion[BULLETNUM] = Explosion_Pos;
	ExplosionJudge[BULLETNUM] = JUDGE;

	//���ꂼ��̂�����ۂ��ʒu�ւ̒���
	switch(LRJudge)
	{
	case 1:
		g_posExplosion[BULLETNUM].x -= 50.0f;
		break;
	case 2:
		g_posExplosion[BULLETNUM].y += 30.0f;
		break;
	case 3:
		g_posExplosion[BULLETNUM].x += 50.0f;
		break;

	}
}
