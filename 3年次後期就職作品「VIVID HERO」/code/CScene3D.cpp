//��-------------------------------------------------------------------------��
//
//	File:CScene3Dcpp�t�@�C��[CScene3D.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CScene3D.h"
#include "CManager.h"

#include "CTextureManager.h"

//��----------------------------------��
//�R���X�g���N�^
//��----------------------------------��
CScene3D::CScene3D(int nPriority) : CScene(nPriority)
{
	m_Type = CTYPE_SCENE3D;

	m_Texture = NULL;
	m_VtxBuffer = NULL;

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	m_TexWidth = 0.0f;
	m_TexHeight = 0.0f;
}

//��----------------------------------��
//�f�X�g���N�^
//��----------------------------------��
CScene3D::~CScene3D()
{

}

//��----------------------------------��
//CScene3D�̏���������
//��----------------------------------��
HRESULT CScene3D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//***�e�N�X�e���̓ǂݍ���***
	m_Texture = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_TexName));

	//***���_���̐ݒ�***
	//****���_�o�b�t�@�̐ݒ�****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_VtxBuffer,NULL);
	
	//�w�i�摜�̏��o�^
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	//���_���̐ݒ�
	m_pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_TexWidth/2,m_Pos.y + m_TexHeight/2,0.0f);
	m_pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_TexWidth/2,m_Pos.y + m_TexHeight/2,0.0f);
	m_pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_TexWidth/2,m_Pos.y - m_TexHeight/2,0.0f);
	m_pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_TexWidth/2,m_Pos.y - m_TexHeight/2,0.0f);

	//****����@���I�@���I���̐ݒ�*****
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
//CScene3D�̏I������
//��----------------------------------��
void CScene3D::Uninit(void)
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
//CScene3D�̍X�V����
//��----------------------------------��
void CScene3D::Update(void)
{

}

//��----------------------------------��
//CScene3D�̕`�揈��
//��----------------------------------��
void CScene3D::Draw(void)
{
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;	//

	//****���[���h�̐ݒ�****
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&mtxScl,m_Scl.x,
								m_Scl.y,
								m_Scl.z);			//�X�P�[���𔽉f

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

	//****���̑��̐ݒ�****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_Rot.y,
									m_Rot.x,
									m_Rot.z);		//���|�@�s�b�`�@���[��

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);		//�ʒu�𔽉f
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&m_mtxWorld);	//�ݒ�

	//3D�|���S���̕`��
	pDevice->SetStreamSource(0,m_VtxBuffer,0,sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,m_Texture);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}

//��----------------------------------��
//CScene3D�̃Z�b�g�|�W�V�������̂P
//��----------------------------------��
void  CScene3D::SetPosition(float x,float y,float z)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}

//��----------------------------------��
//CScene3D�̃Z�b�g�|�W�V�������̂Q
//��----------------------------------��
void  CScene3D::SetPosition(D3DXVECTOR3 pos)
{	
	m_Pos.x = pos.x;
	m_Pos.y = pos.y;
	m_Pos.z = pos.z;
}

//��----------------------------------��
//CScene3D�̃Q�b�g�|�W�V����
//��----------------------------------��
D3DXVECTOR3  CScene3D::GetPosition(void)
{
	return m_Pos;
}

//��----------------------------------��
//CScene3D�̃Z�b�g���[�e�[�V�������̂P
//��----------------------------------��
void CScene3D::SetRotation(float x,float y,float z)
{
	m_Rot.x = x;
	m_Rot.y = y;
	m_Rot.z = z;
}

//��----------------------------------��
//CScene3D�̃Z�b�g���[�e�[�V��������2
//��----------------------------------��
void CScene3D::SetRotation(D3DXVECTOR3 rot)
{
	m_Rot.x = rot.x;
	m_Rot.y = rot.y;
	m_Rot.z = rot.z;
}

//��----------------------------------��
//CScene3D�̃Q�b�g���[�e�[�V����
//��----------------------------------��
D3DXVECTOR3 CScene3D::GetRotation(void)
{
	return m_Rot;
}

//��----------------------------------��
//CScene3D�̃Z�b�g�^�C�v
//��----------------------------------��
void CScene3D::SetType(int nType)
{

}

//��----------------------------------��
//CScene3D��	�N���G�C�g(�����t)
//TextureName:�e�N�X�`���̖��O
//Pos:�e�N�X�`���̍��W
//Rot:�e�N�X�e���̊p�x
//m_TexWidth,m_TexHeight:�e�N�X�`���̃^�e���R�̒���
//��----------------------------------��
CScene3D *CScene3D::Create(LPCTSTR TextureName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,float TexWidth,float TexHeight)
{
	CScene3D *pScene3D;
	pScene3D = new CScene3D;

	pScene3D->m_TexName = TextureName;
	pScene3D->m_Pos = Pos;
	pScene3D->m_Rot = Rot;

	pScene3D->m_TexWidth = TexWidth;
	pScene3D->m_TexHeight = TexHeight;
	pScene3D->Init();

	return pScene3D;
}

//��----------------------------------��
//CScene3D��	�N���G�C�g
//��----------------------------------��
CScene3D *CScene3D::Create(int Priority,LPCTSTR TextureName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,float m_TexWidth,float m_TexHeight)
{
	CScene3D *pScene3D;
	pScene3D = new CScene3D(Priority);

	pScene3D->m_TexName		 = TextureName;
	pScene3D->m_Pos			 = Pos;
	pScene3D->m_Rot			 = Rot;

	pScene3D->m_TexWidth	 = m_TexWidth;
	pScene3D->m_TexHeight	 = m_TexHeight;
	pScene3D->Init();

	return pScene3D;
}

//��----------------------------------��
//�|���S���̍��W���Q�b�g����֐�
//��----------------------------------��
VERTEX_3D CScene3D::GetVERTEXPos(int num)
{
	return m_pVtx[num];
}


//��----------------------------------��
//�|���S���̐F�ύX�֐�
//��----------------------------------��
void CScene3D::SetColor(D3DXCOLOR Color)
{
	//�w�i�摜�̏��o�^
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	m_pVtx[0].col = Color;
	m_pVtx[1].col = Color;
	m_pVtx[2].col = Color;
	m_pVtx[3].col = Color;

	m_VtxBuffer->Unlock();
}