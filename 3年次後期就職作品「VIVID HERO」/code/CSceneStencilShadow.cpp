//��-------------------------------------------------------------------------��
//
//	File	:CSceneStencilShadow�t�@�C��[CSceneStencilShadow.cpp]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CSceneStencilShadow.h"
#include "CManager.h"
#include "CTextureManager.h"

//��----------------------------------��
//�R���X�g���N�^
//��----------------------------------��
CSceneStencilShadow::CSceneStencilShadow(int nPriority) : CScene(nPriority)
{
	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	m_Texture = NULL;

	m_TextureName = NULL;
	m_XfileName = NULL;

	m_Type = CTYPE_SCENESTENCILSHADOW;
}

//��----------------------------------��
//�f�X�g���N�^
//��----------------------------------��
CSceneStencilShadow::~CSceneStencilShadow()
{

}

//��----------------------------------��
//CSceneStencilShadow�̏���������
//��----------------------------------��
HRESULT CSceneStencilShadow::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//***�e�N�X�e���̓ǂݍ���***
	if(m_TextureName != NULL)
	{
		m_Texture = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_TextureName));
	}

	//���f���̃��[�h
	m_XFile_Info = CManager::GetXFileManagerPointer()->GetXFile(CManager::GetXFileManagerPointer()->Load(m_XfileName));

	//���_���̓o�^
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&m_VtxBuffer,NULL);
	
	//�w�i�摜�̏��o�^
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	//���_���̐ݒ�
	m_pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
	m_pVtx[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
	m_pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);

	m_pVtx[0].rhw = 1.0f;
	m_pVtx[1].rhw = 1.0f;
	m_pVtx[2].rhw = 1.0f;
	m_pVtx[3].rhw = 1.0f;

	m_pVtx[0].col = D3DXCOLOR(1.0,1.0,1.0,1.0);
	m_pVtx[1].col = D3DXCOLOR(1.0,1.0,1.0,1.0);
	m_pVtx[2].col = D3DXCOLOR(1.0,1.0,1.0,1.0);
	m_pVtx[3].col = D3DXCOLOR(1.0,1.0,1.0,1.0);

	m_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	m_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	m_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	m_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);

	m_VtxBuffer->Unlock();

	return S_OK;
}

//��----------------------------------��
//CSceneStencilShadow�̏I������
//��----------------------------------��
void CSceneStencilShadow::Uninit(void)
{
	Release();
}

//��----------------------------------��
//CSceneStencilShadow�̍X�V����
//��----------------------------------��
void CSceneStencilShadow::Update(void)
{

}

//��----------------------------------��
//CSceneStencilShadow�̕`�揈��
//��----------------------------------��
void CSceneStencilShadow::Draw(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�X�e���V���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE,TRUE);
	//Z�o�b�t�@�ւ̏������ݖ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
	//�J���[�o�b�t�@�ւ̏������ݖ���
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,0);

	//�X�e���V���ݒ�P
	//�X�e���V���Q�ƒl�̐ݒ�

	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_ALWAYS);	//�S�č��i������(�X�e���V���e�X�g)

	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_ZERO);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_INCR);
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_ZERO);

	//�J�����O���t(�N���b�Y���C�Y)�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);
	DrawXModel();

	//�X�e���V���ݒ�2

	//�X�e���V���Q�ƒl�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILREF,1);

	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_GREATEREQUAL);	//�Q�ƒl�ȏ�ō��i������

	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_INCR);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_ZERO);
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_ZERO);

	//�J�����O����(�J�E���^�[�N���b�N���C�Y)�ɖ߂�
	pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	DrawXModel();

	//�X�e���V���ݒ�3
	//�X�e���V���Q�ƒl�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILREF,2);

	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_EQUAL);			//���l�ō��i������

	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_KEEP);

	//�J���[�o�b�t�@�ւ̏������ݗL��
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,0xf);		//�����L���Ƃ��Ă݂�

	//�QD�|���S���̕`��
	//�w�i�̕`��
	pDevice->SetStreamSource(0,m_VtxBuffer,0,sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,NULL);
	//�e�N�X�`���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//Z�o�b�t�@�ւ̏������ݗL��
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	//�X�e���V���e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE,FALSE);
}

//��----------------------------------��
//CSceneStencilShadow�̂R�����f���`��
//��----------------------------------��
void CSceneStencilShadow::DrawXModel(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//�}�b�g�̃f�t�H���g

	//****���[���h�̐ݒ�****
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&mtxScl,m_Scl.x,
								m_Scl.y,
								m_Scl.z);	//�X�P�[���𔽉f

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

	//****���̑��̐ݒ�****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_Rot.y,
									m_Rot.x,
									m_Rot.z);		//���|�@�s�b�`�@���[��

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);

	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);		//�ʒu�𔽉f
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&m_mtxWorld);	//�ݒ�

	//���f���̕`��
	pDevice -> GetMaterial(&matDef);
	pMat = (D3DXMATERIAL*)m_XFile_Info.BuffMat->GetBufferPointer();

	for(int nCntMat = 0;nCntMat < (int)m_XFile_Info.numMat;nCntMat++)
	{
		pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
		pDevice -> SetTexture(0,m_Texture);
		m_XFile_Info.Mesh -> DrawSubset(nCntMat);
	}
	pDevice -> SetMaterial(&matDef);

}

//��----------------------------------��
//CSceneStencilShadow�̃Z�b�g�|�W�V�������̂P
//��----------------------------------��
void CSceneStencilShadow::SetPosition(float x,float y,float z)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}

//��----------------------------------��
//CSceneStencilShadow�̃Z�b�g�|�W�V�������̂Q
//��----------------------------------��
void CSceneStencilShadow::SetPosition(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//��----------------------------------��
//CSceneStencilShadow�̃Q�b�g�|�W�V����
//��----------------------------------��
D3DXVECTOR3 CSceneStencilShadow::GetPosition(void)
{
	return m_Pos;
}

//��----------------------------------��
//CSceneStencilShadow�̃Z�b�g���[�e�[�V�������̂P
//��----------------------------------��
void CSceneStencilShadow::SetRotation(float x,float y,float z)
{
	m_Rot.x = x;
	m_Rot.y = y;
	m_Rot.z = z;
}

//��----------------------------------��
//CSceneStencilShadow�̃Z�b�g���[�e�[�V��������2
//��----------------------------------��
void CSceneStencilShadow::SetRotation(D3DXVECTOR3 rot)
{
	m_Rot.x = rot.x;
	m_Rot.y = rot.y;
	m_Rot.z = rot.z;
}

//��----------------------------------��
//CSceneStencilShadow�̃Q�b�g���[�e�[�V����
//��----------------------------------��
D3DXVECTOR3 CSceneStencilShadow::GetRotation(void)
{
	return m_Rot;
}

//��----------------------------------��
//CSceneStencilShadow�̃Z�b�g�^�C�v
//��----------------------------------��
void CSceneStencilShadow::SetType(int nType)
{
//	m_Type = CTYPE_SCENEX;
}


//��----------------------------------��
//CSceneStencilShadowD��	�N���G�C�g(�����t)
//TextureName:�e�N�X�`���̖��O
//PosX,PosY,PosZ:�e�N�X�`���̍��W
//��----------------------------------��
CSceneStencilShadow *CSceneStencilShadow::Create(LPCTSTR XfileName,D3DXVECTOR3 Pos)
{
	CSceneStencilShadow *pSceneX;
	pSceneX = new CSceneStencilShadow;

	pSceneX->m_XfileName = XfileName;
	pSceneX->m_Pos = Pos;
	
	pSceneX->Init();

	return pSceneX;
}
