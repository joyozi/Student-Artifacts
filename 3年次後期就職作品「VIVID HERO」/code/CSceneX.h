//◇-------------------------------------------------------------------------◇
//
//	File:CXFileManagerのヘッダーファイル[CXFileManager.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CSCENEX_H_
#define _CSCENEX_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CScene.h"
#include "CXFileManager.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CSceneX : public CScene
{
public:
	CSceneX(int nPriority = 14);
	virtual ~CSceneX();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual void MatrixUpdate();

	virtual void  SetPosition(float x,float y,float z);
	virtual void  SetPosition(D3DXVECTOR3 pos);
	virtual D3DXVECTOR3 GetPosition(void);

	virtual void SetRotation(float x,float y,float z);
	virtual void SetRotation(D3DXVECTOR3 pos);
	virtual D3DXVECTOR3 GetRotation(void);

	virtual void SetType(int nType);

	static CSceneX *Create(LPCTSTR XfileName,D3DXVECTOR3 Pos);

protected:
	XFILE_INFO			m_XFile_Info;
	LPDIRECT3DTEXTURE9	m_Texture;
	
	D3DXVECTOR3			m_Pos;
	D3DXVECTOR3			m_Rot;
	D3DXVECTOR3			m_Scl;
	
	D3DXMATRIX			m_mtxProjection;					//プロジェクションマトリックス
	D3DXMATRIX			m_mtxView;						//ビューマトリックス
	D3DXMATRIX			m_mtxWorld;						//ワールドマトリックス

	LPCTSTR				m_XfileName;
	LPCTSTR				m_TextureName;
};




#endif