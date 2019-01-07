//◇-------------------------------------------------------------------------◇
//
//	File:テクスチャマネージャのファイル[CTextureManager.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CTextureManager.h"

//◇-----------------------------------◇
//テクスチャマネージャのコンストラクタ
//◇-----------------------------------◇
CTextureManager::CTextureManager()
{

}

//◇-----------------------------------◇
//テクスチャマネージャのデストラクタ
//◇-----------------------------------◇
CTextureManager::~CTextureManager()
{

}

//◇-----------------------------------◇
//テクスチャマネージャのロード処理
//◇-----------------------------------◇
int CTextureManager::Load(const char* pTextureFileName)
{
	//テクスチャ数がいっぱいでないか
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
		wsprintf(PopComment,"%sのテクスチャ読み込めてる？",pTextureFileName);

		MessageBox(NULL,
							PopComment,
							"fromテクスチャマネージャ",
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

	//次の数値を返す
	return m_nTextureCount  ++;
}
	
//◇-----------------------------------◇
//テクスチャマネージャの初期化処理
//◇-----------------------------------◇
void CTextureManager::Init(int nMax)
{
	m_pTextureData = new TextureData[nMax];
	m_nTextureMax = nMax;
	m_nTextureCount = 0;
}

//◇-----------------------------------◇
//テクスチャマネージャの終了処理
//◇-----------------------------------◇
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
//◇-----------------------------------◇
//テクスチャマネージャのゲット処理
//◇-----------------------------------◇
LPDIRECT3DTEXTURE9 CTextureManager::GetTexture(int nId)
{
	return m_pTextureData[nId].pTexture;
}
