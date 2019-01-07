//◇-------------------------------------------------------------------------◇
//
//	File:CXFileManagerのヘッダーファイル[CXFileManager.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CTEXTUREMANAGER_H_
#define _CTEXTUREMANAGER_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "main.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CTextureManager
{
public:
	CTextureManager();
	~CTextureManager();
	
	//管理番号　読み込めなかったらー１
	int Load(const char* pTextureFileName);
	
	void Init(int nMax);
	void Uninit(void);
	LPDIRECT3DTEXTURE9 GetTexture(int nId);

private:
	int m_nTextureMax;
	int m_nTextureCount;


	//structの場合は、publicとかをつけなかった場合は、publicになる
	struct TextureData
	{
		LPDIRECT3DTEXTURE9 pTexture;
		static const int TEXTURE_FILENAME_MAX = 256;
		char m_fileName[TEXTURE_FILENAME_MAX];
	};
	TextureData* m_pTextureData;
};

#endif
