//��-------------------------------------------------------------------------��
//
//	File	:�r���{�[�h�t�@�C��[billboard.cpp]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "billboard.h"
#include "camera.h"
#include "input.h"
#include "light.h"
//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 g_pTextureBillboard;			//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard;	//

D3DXMATRIX g_mtxProjectionBillboard;				//�v���W�F�N�V�����}�g���b�N�X
D3DXMATRIX g_mtxViewBillboard;						//�r���[�}�g���b�N�X
D3DXMATRIX g_mtxWorldBillboard;						//���[���h�}�g���b�N�X

D3DXVECTOR3 g_posBillboard;						//�ʒu
D3DXVECTOR3 g_rotBillboard;						//����
D3DXVECTOR3 g_sclBillboard;						//�傫���i��{�ς��Ȃ��j
D3DXVECTOR3 g_posBillboardP;					//�J�����̎��_
D3DXVECTOR3 g_posBillboardR;					//�J�����̒����_
D3DXVECTOR3 g_posBillboardU;					//�J�����̏�����x�N�g��

//��-------------------------------------------------------------------------��
//����������
//��-------------------------------------------------------------------------��
void InitBillboard(void)
{
	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	g_posBillboard = D3DXVECTOR3(0.0f,100.0f,200.0f);
	g_rotBillboard = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclBillboard = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//***�J�����̏�����***
	g_posBillboardP = D3DXVECTOR3(0.0f,100.0f,-150.0f);		//�J�����̎��_
	g_posBillboardR = D3DXVECTOR3(0.0f,0.0f,0.0f);			//�J�����̒����_
	g_posBillboardU = D3DXVECTOR3(0.0f,1.0f,0.0f);			//�J�����̏�����x�N�g��

	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	VERTEX_3D *pVtx;

	//***�e�N�X�e���̓ǂݍ���***
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/oumu.png",&g_pTextureBillboard);

	//***���_���̐ݒ�***

	//****���_�o�b�t�@�̐ݒ�****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffBillboard,NULL);

	//***���_�f�[�^�����b�N***
	g_pVtxBuffBillboard->Lock(0,0,(void**)&pVtx,0);

	//****���_�̈ʒu�̐ݒ�****
	pVtx[0].pos = D3DXVECTOR3(-30,20,0);
	pVtx[1].pos = D3DXVECTOR3(30,20,0);
	pVtx[2].pos = D3DXVECTOR3(-30,-20,0);
	pVtx[3].pos = D3DXVECTOR3(30,-20,0);

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
	pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0,1.0);


	//****���_�f�[�^�̃��b�N����
	g_pVtxBuffBillboard->Unlock();
}

//��---------------------------------��
//�I������
//��---------------------------------��
void UninitBillboard(void)
{
	if(g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
	
		//�e�N�X�`���̏���
	if(g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
}
//��---------------------------------��
//�̍X�V����
//��---------------------------------��
void UpdateBillboard(void)
{
	static D3DXVECTOR3 RotBillboard;

/*
	//****************************�J�����̑���*************************************
	//===�J�����̑O�ړ�=============
	//==============================
	if(GetKeyboardPress(DIK_UP) == true)
	{
		g_posBillboard.x += sinf(GetRotCamera().y) * BILLBOARD_MOVE;
		g_posBillboard.z += cosf(GetRotCamera().y) * BILLBOARD_MOVE;
	}
	
	//===�J�����̌��ړ�===========
	//==============================
	if(GetKeyboardPress(DIK_DOWN) == true)
	{
		g_posBillboard.x -= sinf(GetRotCamera().y) * BILLBOARD_MOVE;
		g_posBillboard.z -= cosf(GetRotCamera().y) * BILLBOARD_MOVE;
	}


	//===�J�����̍��ړ�=============
	//==============================
	if(GetKeyboardPress(DIK_LEFT) == true)
	{
		g_posBillboard.x -= cosf(GetRotCamera().y) * BILLBOARD_MOVE;
		g_posBillboard.z += sinf(GetRotCamera().y) * BILLBOARD_MOVE;
	}
	//===�J�����̉E�ړ�=============
	//==============================
	if(GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_posBillboard.x += cosf(GetRotCamera().y) * BILLBOARD_MOVE;
		g_posBillboard.z -= sinf(GetRotCamera().y) * BILLBOARD_MOVE;
	}
*/

}

//��---------------------------------��
//�̕`�揈��
//��---------------------------------��
void DrawBillboard(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;	
	D3DXMATRIX mtxView;				//�r���[�}�g���b�N�X
	
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	mtxView = GetMtxView();

	//------���[���h�}�g���b�N�X�Ƃ��̐ݒ�--------------------------------------------------------------

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldBillboard);

	//�t�s������߂�
	D3DXMatrixInverse(&g_mtxWorldBillboard,NULL,&mtxView);

	g_mtxWorldBillboard._41 = 0.0f;
	g_mtxWorldBillboard._42 = 0.0f;
	g_mtxWorldBillboard._43 = 0.0f;

	//****���[���h�̐ݒ�****
	D3DXMatrixScaling(&mtxScl,g_sclBillboard.x,g_sclBillboard.y,g_sclBillboard.z);			//�X�P�[���𔽉f
	D3DXMatrixMultiply(&g_mtxWorldBillboard,&g_mtxWorldBillboard,&mtxScl);

/*	�����ɕt����������ォ��g���邯�Ǎ��͎g���Ȃ����ۂ��N����
	//�t�s������ɖ߂�
	D3DXMatrixInverse(&g_mtxWorldBillboard,NULL,&mtxView);
*/

	//****���̑��̐ݒ�****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotBillboard.y,g_rotBillboard.x,g_rotBillboard.z);		//���|�@�s�b�`�@���[��

	D3DXMatrixMultiply(&g_mtxWorldBillboard,&g_mtxWorldBillboard,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,g_posBillboard.x,g_posBillboard.y,g_posBillboard.z);	//�ʒu�𔽉f
	D3DXMatrixMultiply(&g_mtxWorldBillboard,&g_mtxWorldBillboard,&mtxTranslate);

	pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldBillboard);	//�ݒ�
	

	//------------------------------------------------------------------------------------------

	//****���e�X�g�̊J�n****
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

/*

D3DCMP_NEVER�@�łȂ��Ȃ����Ⴄ
D3DCMP_LESS�@���u�����h�̕������o�Ă���
D3DCMP_EQUAL�@�����l��������o�Ă���
D3DCMP_LESSEQUAL�@�����l���Əo��B����ȊO���ƃ��u�����h�̕������o��H
D3DCMP_GREATER�@�l�ȏゾ�Əo�Ă���
D3DCMP_NOTEQUAL�@�����l���Əo�Ă��Ȃ�
D3DCMP_GREATEREQUAL �l�ȏゾ�Əo�Ă���H
D3DCMP_ALWAYS �S���o�Ă���


*/
	//----------------3D�|���S���̕`��----------------------------------------------------------

	//���_�o�b�t�@���o�C���h
	pDevice->SetStreamSource(0,g_pVtxBuffBillboard,0,sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,g_pTextureBillboard);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//------------------------------------------------------------------------------------------

	//****���e�X�g�̏I��****
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
}

D3DXVECTOR3 GetPosBillboard(void)
{
	return g_posBillboard;
}