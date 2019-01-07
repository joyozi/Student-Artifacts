//��-------------------------------------------------------------------------��
//
//	File	:�V���h�E�t�@�C��[shadow.cpp]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "input.h"
#include "shadow.h"
#include "billboard.h"
#include "camera.h"
#include "model.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 g_pTextureShadow;			//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow;	//

D3DXVECTOR3 g_posShadow;		//���f���̈ʒu
D3DXVECTOR3 g_rotShadow;		//���f���̌���
D3DXVECTOR3 g_sclShadow;		//���f���̑傫��

D3DXMATRIX g_mtxProjectionShadow;					//�v���W�F�N�V�����}�g���b�N�X
D3DXMATRIX g_mtxViewShadow;						//�r���[�}�g���b�N�X
D3DXMATRIX g_mtxWorldShadow;						//���[���h�}�g���b�N�X

D3DXVECTOR3 g_posShadowP;					//�J�����̎��_
D3DXVECTOR3 g_posShadowR;					//�J�����̒����_
D3DXVECTOR3 g_posShadowU;					//�J�����̏�����x�N�g��

VERTEX_3D *pVtxShadow;

//��-------------------------------------------------------------------------��
//����������
//��-------------------------------------------------------------------------��
void InitShadow(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posShadow = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_rotShadow = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclShadow = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//***�J�����̏�����***
	g_posShadowP = D3DXVECTOR3(0.0f,100.0f,-150.0f);
	g_posShadowR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_posShadowU = D3DXVECTOR3(0.0f,1.0f,0.0f);

	//***�e�N�X�e���̓ǂݍ���***
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/shadow000.jpg",&g_pTextureShadow);

	//***���_���̐ݒ�***

	//****���_�o�b�t�@�̐ݒ�****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffShadow,NULL);

	//***���_�f�[�^�����b�N***
	g_pVtxBuffShadow->Lock(0,0,(void**)&pVtxShadow,0);

	//****���_�̈ʒu�̐ݒ�****
	pVtxShadow[0].pos = D3DXVECTOR3(-30,1,30);
	pVtxShadow[1].pos = D3DXVECTOR3(30,1,30);
	pVtxShadow[2].pos = D3DXVECTOR3(-30,1,-30);
	pVtxShadow[3].pos = D3DXVECTOR3(30,1,-30);

	//****�����̐ݒ�*****
	pVtxShadow[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtxShadow[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtxShadow[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtxShadow[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	//****�J���[�̐ݒ�****
	pVtxShadow[0].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtxShadow[1].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtxShadow[2].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtxShadow[3].col = D3DCOLOR_RGBA(255,255,255,55);

	//****tex�̐ݒ�****
	pVtxShadow[0].tex = D3DXVECTOR2(0.0,0.0);
	pVtxShadow[1].tex = D3DXVECTOR2(1.0,0.0);
	pVtxShadow[2].tex = D3DXVECTOR2(0.0,1.0);
	pVtxShadow[3].tex = D3DXVECTOR2(1.0,1.0);


	//****���_�f�[�^�̃��b�N����
	g_pVtxBuffShadow->Unlock();
}

//��---------------------------------��
//�I������
//��---------------------------------��
void UninitShadow(void)
{
	if(g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow ->Release();
		g_pVtxBuffShadow = NULL;
	}
	
		//�e�N�X�`���̏���
	if(g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}
//��---------------------------------��
//�̍X�V����
//��---------------------------------��
void UpdateShadow(void)
{
	static D3DXVECTOR3 RotShadow;

	//�r���{�[�h�̈ʒu���擾
	RotShadow = Getg_posModel();

	//�r���{�[�h�̈ʒu���e�Ɉڂ�
	g_posShadow.x = RotShadow.x;
	g_posShadow.z = RotShadow.z;
}

//��---------------------------------��
//�̕`�揈��
//��---------------------------------��
void DrawShadow(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//****���[���h�̐ݒ�****
	D3DXMatrixIdentity(&g_mtxWorldShadow);
	D3DXMatrixScaling(&mtxScl,g_sclShadow.x,
								g_sclShadow.y,
								g_sclShadow.z);			//�X�P�[���𔽉f

	D3DXMatrixMultiply(&g_mtxWorldShadow,&g_mtxWorldShadow,&mtxScl);

	//****���̑��̐ݒ�****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotShadow.y,
									g_rotShadow.x,
									g_rotShadow.z);		//���|�@�s�b�`�@���[��

	D3DXMatrixMultiply(&g_mtxWorldShadow,&g_mtxWorldShadow,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,g_posShadow.x,g_posShadow.y,g_posShadow.z);	//�ʒu�𔽉f
	D3DXMatrixMultiply(&g_mtxWorldShadow,&g_mtxWorldShadow,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldShadow);	//�ݒ�

	//���Z�����Ƃ����낢��
	pDevice -> SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_REVSUBTRACT);
	pDevice -> SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice -> SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);


	//3D�|���S���̕`��
	pDevice->SetStreamSource(0,g_pVtxBuffShadow,0,sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,g_pTextureShadow);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//���Z���������ɖ߂�
	pDevice -> SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_SUBTRACT);
	pDevice -> SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice -> SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
}
