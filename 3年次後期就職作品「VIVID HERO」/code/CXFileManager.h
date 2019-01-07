//◇-------------------------------------------------------------------------◇
//
//	File:CXFileManagerのヘッダーファイル[CXFileManager.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CXFileManager_H_
#define _CXFileManager_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "main.h"

//◇-----------------------------------◇
//構造体定義
//◇-----------------------------------◇
typedef struct
{
	LPDIRECT3DTEXTURE9			XFile;
	LPDIRECT3DVERTEXBUFFER9		VtxBuffer;
	LPD3DXMESH					Mesh;			//メッシュ情報へのポインタ
	LPD3DXBUFFER				BuffMat;		//マテリアル情報へのポインタ
	DWORD						numMat;			//マテリアルの数
}XFILE_INFO;

//structの場合は、publicとかをつけなかった場合は、publicになる
struct XFileData
{
	XFILE_INFO			XFile_Info;
	static const int	XFILE_FILENAME_MAX = 256;
	char				XFileName[XFILE_FILENAME_MAX];
};

class CXFileManager;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CXFileManager
{
public:
	CXFileManager();
	virtual ~CXFileManager();

	int Load(const char* pXFileName);

	void Init(int nMax);
	void Uninit(void);

	XFILE_INFO GetXFile(int nId);

private:
	LPDIRECT3DTEXTURE9		m_XFile;
	int						m_nXFileMax;
	int						m_nXFileCount;
	XFileData*				m_pXFileData;
};


#endif