//��-------------------------------------------------------------------------��
//
//	File:CSceneBillboardcpp�t�@�C��[CSceneBillboard.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CSceneBillboard.h"
#include "CManager.h"
#include "CTextureManager.h"
#include "CCamera.h"

//��----------------------------------��
//�R���X�g���N�^
//��----------------------------------��
CSceneBillboard::CSceneBillboard(int nPriority) : CScene(nPriority)
{
	m_Type = CTYPE_SCENEBILLBOARD;

	m_Texture = NULL;
	m_VtxBuffer = NULL;

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	TextureWidth = 30.0f;
	TextureHeight = 50.0f;

	m_TextureName = NULL;
}

//��----------------------------------��
//�f�X�g���N�^
//��----------------------------------��
CSceneBillboard::~CSceneBillboard()
{

}

//��----------------------------------��
//CSceneBillboard�̏���������
//��----------------------------------��
HRESULT CSceneBillboard::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//***�e�N�X�e���̓ǂݍ���***
	m_Texture = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_TextureName));

	//***���_���̐ݒ�***
	//****���_�o�b�t�@�̐ݒ�****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_VtxBuffer,NULL);

	//�w�i�摜�̏��o�^
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	//���_���̐ݒ�
	m_pVtx[0].pos = D3DXVECTOR3( - TextureWidth / 2, + TextureHeight / 2,0.0f);
	m_pVtx[1].pos = D3DXVECTOR3( + TextureWidth / 2, + TextureHeight / 2,0.0f);
	m_pVtx[2].pos = D3DXVECTOR3( - TextureWidth / 2, - TextureHeight / 2,0.0f);
	m_pVtx[3].pos = D3DXVECTOR3( + TextureWidth / 2, - TextureHeight / 2,0.0f);

	//****�����̐ݒ�*****
	m_pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	m_pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	m_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	m_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	m_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	m_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);

	m_VtxBuffer->Unlock();

	return S_OK;
}

//��----------------------------------��
//CSceneBillboard�̏I������
//��----------------------------------��
void CSceneBillboard::Uninit(void)
{
	Release();

	//�o�b�t�@�̏���
	if(m_VtxBuffer != NULL)
	{
		m_VtxBuffer->Release();
		m_VtxBuffer = NULL;
	}
}

//��----------------------------------��
//CSceneBillboard�̍X�V����
//��----------------------------------��
void CSceneBillboard::Update(void)
{

}

//��----------------------------------��
//CSceneBillboard�̕`�揈��
//��----------------------------------��
void CSceneBillboard::Draw(void)
{
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATRIX mtxView;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X�̎擾
	mtxView = CManager::GetCameraPointer()->GetMtxView();

	//�t�s������߂�
	D3DXMatrixInverse(&m_mtxWorld,NULL,&mtxView);

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//****���[���h�̐ݒ�****
	D3DXMatrixScaling(&mtxScl,m_Scl.x,m_Scl.y,m_Scl.z);					//�X�P�[���𔽉f
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

	//****�ʒu�̐ݒ�****
	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);		//�ʒu�𔽉f
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);

	pDevice -> SetTransform(D3DTS_WORLD,&m_mtxWorld);	//�ݒ�



	//����Ń��C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);

	//3D�|���S���̕`��
	pDevice->SetStreamSource(0,m_VtxBuffer,0,sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,m_Texture);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);
}

//��----------------------------------��
//CSceneBillboard�̃Z�b�g�|�W�V�������̂P
//��----------------------------------��
void  CSceneBillboard::SetPosition(float x,float y,float z)
{
	m_Pos = D3DXVECTOR3(x,y,z);
}

//��----------------------------------��
//CSceneBillboard�̃Z�b�g�|�W�V�������̂Q
//��----------------------------------��
void  CSceneBillboard::SetPosition(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//��----------------------------------��
//CSceneBillboard�̃Q�b�g�|�W�V����
//��----------------------------------��
D3DXVECTOR3  CSceneBillboard::GetPosition(void)
{
	return m_Pos;
}

//��----------------------------------��
//CSceneBillboard�̃Z�b�g���[�e�[�V�������̂P
//��----------------------------------��
void CSceneBillboard::SetRotation(float x,float y,float z)
{
	m_Rot = D3DXVECTOR3(x,y,z);
}

//��----------------------------------��
//CSceneBillboard�̃Z�b�g���[�e�[�V��������2
//��----------------------------------��
void CSceneBillboard::SetRotation(D3DXVECTOR3 rot)
{
	m_Rot = rot;
}

//��----------------------------------��
//CSceneBillboard�̃Q�b�g���[�e�[�V����
//��----------------------------------��
D3DXVECTOR3 CSceneBillboard::GetRotation(void)
{
	return m_Rot;
}

//��----------------------------------��
//CSceneBillboard�̃Z�b�g�^�C�v
//��----------------------------------��
void CSceneBillboard::SetType(int nType)
{

}

//��----------------------------------��
//CSceneBillboard�̃N���G�C�g
//��----------------------------------��
CSceneBillboard *CSceneBillboard::Create(void)
{
	CSceneBillboard *pSceneBillboard;
	pSceneBillboard = new CSceneBillboard;
	pSceneBillboard->Init();

	return pSceneBillboard;
}

//��----------------------------------��
//CSceneBillboard�̃N���G�C�g(�����t)
//TextureName:�e�N�X�`���̖��O
//PosX,PosY,PosZ:�e�N�X�`���̍��W
//TexWidth,TexHeight:�e�N�X�`���̃^�e���R�̒���
//��----------------------------------��
CSceneBillboard *CSceneBillboard::Create(LPCTSTR TextureName,float PosX,float PosY,float PosZ,float TexWidth,float TexHeight)
{
	CSceneBillboard *pSceneBillboard;
	pSceneBillboard = new CSceneBillboard;

	pSceneBillboard->m_TextureName	 = TextureName;
	pSceneBillboard->m_Pos			 = D3DXVECTOR3(PosX,PosY,PosZ);
	pSceneBillboard->TextureWidth	 = TexWidth;
	pSceneBillboard->TextureHeight	 = TexHeight;
	
	pSceneBillboard->Init();

	return pSceneBillboard;
}

//��----------------------------------��
//CSceneBillboard�̐F�ς�
//��----------------------------------��
void CSceneBillboard::SetColor(D3DXCOLOR Color)
{
	//���o�^
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	m_pVtx[0].col = D3DXCOLOR(Color.r * Color.a,Color.g * Color.a,Color.b * Color.a,Color.a);
	m_pVtx[1].col = D3DXCOLOR(Color.r * Color.a,Color.g * Color.a,Color.b * Color.a,Color.a);
	m_pVtx[2].col = D3DXCOLOR(Color.r * Color.a,Color.g * Color.a,Color.b * Color.a,Color.a);
	m_pVtx[3].col = D3DXCOLOR(Color.r * Color.a,Color.g * Color.a,Color.b * Color.a,Color.a);

	m_VtxBuffer->Unlock();
}
