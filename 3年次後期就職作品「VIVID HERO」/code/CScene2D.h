//◇-------------------------------------------------------------------------◇
//
//	File:CFadeのヘッダーファイル[CFade.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CSCENE2D_H_
#define _CSCENE2D_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CScene.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = 7);		//<-const char *pNone?
	virtual ~CScene2D();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual void  SetPosition(float x,float y,float z);
	virtual void  SetPosition(D3DXVECTOR3 pos);

	virtual D3DXVECTOR3 GetPosition(void);

	virtual void SetRotation(float x,float y,float z);
	virtual void SetRotation(D3DXVECTOR3 pos);

	virtual D3DXVECTOR3 GetRotation(void);

	virtual void SetPosition_Re(D3DXVECTOR3 pos);
	virtual void SetSize(D3DXVECTOR3 Size);

	virtual void SetType(int nType);

	static CScene2D *Create(LPCTSTR TextureName,D3DXVECTOR3 Pos,D3DXVECTOR3 Size);
	static CScene2D *Create(int Priority,LPCTSTR TextureName,D3DXVECTOR3 Pos,D3DXVECTOR3 Size);
	
	virtual void SetVertex_Tex(D3DXVECTOR2 Vtx[]);
	virtual void SetVertex_Col(D3DXCOLOR Col[]);
	virtual void SetVertex_Col(D3DXCOLOR Col);

protected:
	VERTEX_2D*					m_pVtx;		//画像の座標のポインタ

	LPDIRECT3DTEXTURE9			m_Texture;
	LPDIRECT3DVERTEXBUFFER9		m_VtxBuffer;
	D3DXVECTOR3					m_Pos;
	D3DXVECTOR3					m_Rot;

	float						TextureWidth;
	float						TextureHeight;
	D3DXCOLOR					m_Color;
	LPCTSTR						m_TextureName;
};

#endif