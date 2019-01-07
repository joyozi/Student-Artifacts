//��-------------------------------------------------------------------------��
//
//	File	:�t�B�[���h�����t�@�C��[field.cpp]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "field.h"
#include "camera.h"
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
LPDIRECT3DTEXTURE9 g_pTextureField;			//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField;	//

//��-------------------------------------------------------------------------��
//field�̏���������
//��-------------------------------------------------------------------------��
void InitField(void)
{	
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	VERTEX_3D *pVtx;

	//***�e�N�X�e���̓ǂݍ���***
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/Cocoontower.png",&g_pTextureField);

	//***���_���̐ݒ�***

	//****���_�o�b�t�@�̐ݒ�****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffField,NULL);

	//***���_�f�[�^�����b�N***
	g_pVtxBuffField->Lock(0,0,(void**)&pVtx,0);

	//****���_�̈ʒu�̐ݒ�****
	pVtx[0].pos = D3DXVECTOR3(-50,0,50);
	pVtx[1].pos = D3DXVECTOR3(50,0,50);
	pVtx[2].pos = D3DXVECTOR3(-50,0,-50);
	pVtx[3].pos = D3DXVECTOR3(50,0,-50);

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
	g_pVtxBuffField->Unlock();
}
//��-------------------------------------------------------------------------��
//field�̏I������
//��-------------------------------------------------------------------------��
void UninitField(void)
{
	if(g_pVtxBuffField != NULL)
	{
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
	
		//�e�N�X�`���̏���
	if(g_pTextureField != NULL)
	{
		g_pTextureField->Release();
		g_pTextureField = NULL;
	}
}
//��-------------------------------------------------------------------------��
//field�̍X�V����
//��-------------------------------------------------------------------------��
void UpdateField(void)
{

}
//��-------------------------------------------------------------------------��
//field�̕`�揈��
//��-------------------------------------------------------------------------��
void DrawField(void)
{
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//3D�|���S���̕`��
	pDevice->SetStreamSource(0,g_pVtxBuffField,0,sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,g_pTextureField);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}
