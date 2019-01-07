//��-------------------------------------------------------------------------��
//
//	File	:CSceneModelParts�t�@�C��[CSceneModelParts.cpp]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CSceneModelParts.h"
#include "CManager.h"
#include "CTextureManager.h"

//��----------------------------------��
//�R���X�g���N�^
//��----------------------------------��
CSceneModelParts::CSceneModelParts(int nPriority) : CScene(nPriority)
{
	m_Type = CTYPE_SCENEMODELPARTS;

	//****�ʒu�A�p�x�A�X�P�[���̏�����****
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	for(int i = 0;i < 256;i++)
	{
		m_Texture[i] = NULL;
	}

	m_MotionParentPartsRot = D3DXVECTOR3(0.0f,0.0f,0.0f);

}

//��----------------------------------��
//�f�X�g���N�^
//��----------------------------------��
CSceneModelParts::~CSceneModelParts()
{

}

//��----------------------------------��
//CSceneModelParts�̏���������
//��----------------------------------��
HRESULT CSceneModelParts::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	m_pSceneModelMotion = CSceneModelMotion::Create(m_ModelTxtName);
	m_pModelParts = m_pSceneModelMotion->GetPart_Info();

	m_pmtxWorld = new D3DXMATRIX[m_pSceneModelMotion->GetPart_Num()];

	for(int i = 0;i < m_pSceneModelMotion->GetPart_Num();i++)
	{
		//***�e�N�X�e���̓ǂݍ���***
		if(m_pModelParts[i].TexName[0] != NULL && strcmp(m_pModelParts[i].TexName,"NULL") != 0)
		{
			m_Texture[i] = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_pModelParts[i].TexName));
		}

		//���f���̃��[�h
		if(m_pModelParts[i].ModelName != NULL)
		{
			m_XFile_Info[i] = CManager::GetXFileManagerPointer()->GetXFile(CManager::GetXFileManagerPointer()->Load(m_pModelParts[i].ModelName));
		}
	}

	return S_OK;
}

//��----------------------------------��
//CSceneModelParts�̏I������
//��----------------------------------��
void CSceneModelParts::Uninit(void)
{
	Release();

	SAFE_DELETE_ARRY(m_pmtxWorld);
}

//��----------------------------------��
//CSceneModelParts�̍X�V����
//��----------------------------------��
void CSceneModelParts::Update(void)
{

}

//��-----------------------------------��
//CSceneModelParts�̕`�揈��
//��-----------------------------------��
void CSceneModelParts::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//�}�b�g�̃f�t�H���g

	MatrixUpdate();
	for(int i = 0;i < m_pSceneModelMotion->GetPart_Num();i++)
	{
		pDevice -> SetTransform(D3DTS_WORLD,&m_pmtxWorld[i]);	//�ݒ�

		//���f���̕`��
		pDevice -> GetMaterial(&matDef);
		pMat = (D3DXMATERIAL*)m_XFile_Info[i].BuffMat->GetBufferPointer();

		for(int nCntMat = 0;nCntMat < (int)m_XFile_Info[i].numMat;nCntMat++)
		{
			pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
			pDevice -> SetTexture(0,m_Texture[i]);
			m_XFile_Info[i].Mesh->DrawSubset(nCntMat);
		}

		pDevice -> SetMaterial(&matDef);
	}

}

//��----------------------------------��
//CSceneModelParts�̃}�g���b�N�X�̍��W�ړ�
//��----------------------------------��
void CSceneModelParts::MatrixUpdate()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXVECTOR3 Pos,Rot,Scl;

	for(int i = 0;i < m_pSceneModelMotion->GetPart_Num();i++)
	{
		if(m_pModelParts[i].ParentNumber == -1)
		{
			Pos = m_Pos + m_pModelParts[i].Pos;
			Rot = m_Rot + m_pModelParts[i].Rot;
			Scl = m_Scl + m_pModelParts[i].Scl;

			m_MotionParentPartsRot = Rot;
		}
		else
		{
			Pos = m_pModelParts[i].Pos;
			Rot = m_pModelParts[i].Rot;
			Scl = m_pModelParts[i].Scl;
		}

		//****���[���h�̐ݒ�****
		D3DXMatrixIdentity(&m_pmtxWorld[i]);
		D3DXMatrixScaling(&mtxScl,Scl.x,
									Scl.y,
									Scl.z);	//�X�P�[���𔽉f

		D3DXMatrixMultiply(&m_pmtxWorld[i],&m_pmtxWorld[i],&mtxScl);

		//****���̑��̐ݒ�****
		D3DXMatrixRotationYawPitchRoll(&mtxRot,Rot.y,
										Rot.x,
										Rot.z);		//���|�@�s�b�`�@���[��

		D3DXMatrixMultiply(&m_pmtxWorld[i],&m_pmtxWorld[i],&mtxRot);

		D3DXMatrixTranslation(&mtxTranslate,Pos.x,Pos.y,Pos.z);		//�ʒu�𔽉f
		D3DXMatrixMultiply(&m_pmtxWorld[i],&m_pmtxWorld[i],&mtxTranslate);



		if(m_pModelParts[i].ParentNumber != -1)
		{
			D3DXMatrixMultiply(&m_pmtxWorld[i],&m_pmtxWorld[i],&m_pmtxWorld[m_pModelParts[i].ParentNumber]);
		}
	}
}
//��----------------------------------��
//CSceneModelParts�̃Z�b�g�|�W�V�������̂P
//��----------------------------------��
void  CSceneModelParts::SetPosition(float x,float y,float z)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}

//��----------------------------------��
//CSceneModelParts�̃Z�b�g�|�W�V�������̂Q
//��----------------------------------��
void  CSceneModelParts::SetPosition(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//��----------------------------------��
//CSceneModelParts�̃Q�b�g�|�W�V����
//��----------------------------------��
D3DXVECTOR3  CSceneModelParts::GetPosition(void)
{
	return m_Pos;
}

//��----------------------------------��
//CSceneModelParts�̃Z�b�g���[�e�[�V�������̂P
//��----------------------------------��
void CSceneModelParts::SetRotation(float x,float y,float z)
{
	m_Rot.x = x;
	m_Rot.y = y;
	m_Rot.z = z;
}

//��----------------------------------��
//CSceneModelParts�̃Z�b�g���[�e�[�V��������2
//��----------------------------------��
void CSceneModelParts::SetRotation(D3DXVECTOR3 rot)
{
	m_Rot.x = rot.x;
	m_Rot.y = rot.y;
	m_Rot.z = rot.z;
}

//��----------------------------------��
//CSceneModelParts�̃Q�b�g���[�e�[�V����
//��----------------------------------��
D3DXVECTOR3 CSceneModelParts::GetRotation(void)
{
	return m_Rot;
}

//��----------------------------------��
//CSceneModelParts�̃Z�b�g�^�C�v
//��----------------------------------��
void CSceneModelParts::SetType(int nType)
{

}


//��----------------------------------��
//CSceneModelPartsD��	�N���G�C�g(�����t)
//TextureName:�e�N�X�`���̖��O
//PosX,PosY,PosZ:�e�N�X�`���̍��W
//��----------------------------------��
CSceneModelParts *CSceneModelParts::Create(LPCTSTR ModelTxtName,D3DXVECTOR3 Pos)
{
	CSceneModelParts *pCSceneModelParts;
	pCSceneModelParts = new CSceneModelParts;

	pCSceneModelParts->m_ModelTxtName = ModelTxtName;
	pCSceneModelParts->m_Pos = Pos;

	pCSceneModelParts->Init();

	return pCSceneModelParts;
}
