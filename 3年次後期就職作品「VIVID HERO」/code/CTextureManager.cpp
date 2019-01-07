//��-------------------------------------------------------------------------��
//
//	File:�e�N�X�`���}�l�[�W���̃t�@�C��[CTextureManager.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CTextureManager.h"

//��-----------------------------------��
//�e�N�X�`���}�l�[�W���̃R���X�g���N�^
//��-----------------------------------��
CTextureManager::CTextureManager()
{

}

//��-----------------------------------��
//�e�N�X�`���}�l�[�W���̃f�X�g���N�^
//��-----------------------------------��
CTextureManager::~CTextureManager()
{

}

//��-----------------------------------��
//�e�N�X�`���}�l�[�W���̃��[�h����
//��-----------------------------------��
int CTextureManager::Load(const char* pTextureFileName)
{
	//�e�N�X�`�����������ς��łȂ���
	if(m_nTextureCount >= m_nTextureMax)
	{
		return -1;
	}

	for(int i = 0;i < m_nTextureCount;i++)
	{
		if(strcmp(pTextureFileName,m_pTextureData[i].m_fileName) == 0)
		{
			return i;
		}
	}

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	if(FAILED(D3DXCreateTextureFromFile(pDevice, pTextureFileName, &m_pTextureData[m_nTextureCount].pTexture)))
	{
		char PopComment[256];
		wsprintf(PopComment,"%s�̃e�N�X�`���ǂݍ��߂Ă�H",pTextureFileName);

		MessageBox(NULL,
							PopComment,
							"from�e�N�X�`���}�l�[�W��",
							MB_ICONEXCLAMATION | MB_OK);
	}else
	{
		pDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);

		D3DXCreateTextureFromFileEx(pDevice, pTextureFileName, D3DX_DEFAULT,D3DX_DEFAULT,
#if 0
				1,
#elseif 1
				3,
#else
				1,
#endif
				0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,
				0,NULL,NULL,&m_pTextureData[m_nTextureCount].pTexture
			);
	}

	strcpy_s(m_pTextureData[m_nTextureCount].m_fileName,pTextureFileName);

	//���̐��l��Ԃ�
	return m_nTextureCount  ++;
}
	
//��-----------------------------------��
//�e�N�X�`���}�l�[�W���̏���������
//��-----------------------------------��
void CTextureManager::Init(int nMax)
{
	m_pTextureData = new TextureData[nMax];
	m_nTextureMax = nMax;
	m_nTextureCount = 0;
}

//��-----------------------------------��
//�e�N�X�`���}�l�[�W���̏I������
//��-----------------------------------��
void CTextureManager::Uninit(void)
{
	if(m_pTextureData != NULL)
	{
		for(int i = 0;i < m_nTextureCount;i++)
		{
			m_pTextureData[i].pTexture->Release();
			m_pTextureData[i].pTexture = NULL;
		}

		delete[] m_pTextureData;
	}

	m_nTextureMax = 0;
	m_nTextureCount = 0;
}
//��-----------------------------------��
//�e�N�X�`���}�l�[�W���̃Q�b�g����
//��-----------------------------------��
LPDIRECT3DTEXTURE9 CTextureManager::GetTexture(int nId)
{
	return m_pTextureData[nId].pTexture;
}
