//��-------------------------------------------------------------------------��
//
//	File:CXFileManager�̃t�@�C��[CXFileManager.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CXFileManager.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CXFileManager�̃R���X�g���N�^
//��-----------------------------------��
CXFileManager::CXFileManager()
{

}

//��-----------------------------------��
//CXFileManager�̃f�X�g���N�^
//��-----------------------------------��
CXFileManager::~CXFileManager()
{

}

//��-----------------------------------��
//CXFileManager�̃��[�h
//��-----------------------------------��
int CXFileManager::Load(const char* pXFileName)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`�����������ς��łȂ���
	if(m_nXFileCount >= m_nXFileMax)
	{
		return -1;
	}

	for(int i = 0;i < m_nXFileCount;i++)
	{
		if(strcmp(pXFileName,m_pXFileData[i].XFileName) == 0)
		{
			return i;
		}
	}

	if(FAILED(D3DXLoadMeshFromX(pXFileName,D3DXMESH_SYSTEMMEM,pDevice,NULL,&m_pXFileData[m_nXFileCount].XFile_Info.BuffMat,NULL,&m_pXFileData[m_nXFileCount].XFile_Info.numMat,&m_pXFileData[m_nXFileCount].XFile_Info.Mesh)))
	{
		char PopComment[255];
		wsprintf(PopComment,"%s��XFile�ǂݍ��߂Ă�H",pXFileName);

		MessageBox(NULL,
							PopComment,
							"from�e�N�X�`���}�l�[�W��",
							MB_ICONEXCLAMATION | MB_OK);
	}

	strcpy_s(m_pXFileData[m_nXFileCount].XFileName,pXFileName);

	//���̐��l��Ԃ�
	return m_nXFileCount++;
}

//��-----------------------------------��
//CXFileManager�̏���������
//��-----------------------------------��
void CXFileManager::Init(int nMax)
{
	m_pXFileData = new XFileData[nMax];
	
	m_nXFileMax = nMax;
	m_nXFileCount = 0;
}

//��-----------------------------------��
//CXFileManager�̏I������
//��-----------------------------------��
void CXFileManager::Uninit(void)
{
	if(m_pXFileData != NULL)
	{
		for(int i = 0;i < m_nXFileCount;i++)
		{
			m_pXFileData[i].XFile_Info.Mesh->Release();
			m_pXFileData[i].XFile_Info.Mesh = NULL;

			m_pXFileData[i].XFile_Info.BuffMat->Release();
			m_pXFileData[i].XFile_Info.BuffMat = NULL;
		}

		delete[] m_pXFileData;
	}

	m_nXFileMax = 0;
	m_nXFileCount = 0;
}

//��-----------------------------------��
//CXFileManager�̃f�[�^�Q�b�g����
//��-----------------------------------��
XFILE_INFO CXFileManager::GetXFile(int nId)
{
	return m_pXFileData[nId].XFile_Info;
}
