//◇-------------------------------------------------------------------------◇
//
//	File:CXFileManagerのファイル[CXFileManager.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CXFileManager.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CXFileManagerのコンストラクタ
//◇-----------------------------------◇
CXFileManager::CXFileManager()
{

}

//◇-----------------------------------◇
//CXFileManagerのデストラクタ
//◇-----------------------------------◇
CXFileManager::~CXFileManager()
{

}

//◇-----------------------------------◇
//CXFileManagerのロード
//◇-----------------------------------◇
int CXFileManager::Load(const char* pXFileName)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//テクスチャ数がいっぱいでないか
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
		wsprintf(PopComment,"%sのXFile読み込めてる？",pXFileName);

		MessageBox(NULL,
							PopComment,
							"fromテクスチャマネージャ",
							MB_ICONEXCLAMATION | MB_OK);
	}

	strcpy_s(m_pXFileData[m_nXFileCount].XFileName,pXFileName);

	//次の数値を返す
	return m_nXFileCount++;
}

//◇-----------------------------------◇
//CXFileManagerの初期化処理
//◇-----------------------------------◇
void CXFileManager::Init(int nMax)
{
	m_pXFileData = new XFileData[nMax];
	
	m_nXFileMax = nMax;
	m_nXFileCount = 0;
}

//◇-----------------------------------◇
//CXFileManagerの終了処理
//◇-----------------------------------◇
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

//◇-----------------------------------◇
//CXFileManagerのデータゲット処理
//◇-----------------------------------◇
XFILE_INFO CXFileManager::GetXFile(int nId)
{
	return m_pXFileData[nId].XFile_Info;
}
