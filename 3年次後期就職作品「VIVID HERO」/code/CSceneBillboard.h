//◇-------------------------------------------------------------------------◇
//
//	File:CScene3Dのヘッダーファイル[CScene3D.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CSCENEBILLBOARD_H_
#define _CSCENEBILLBOARD_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CScene.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CSceneBillboard : public CScene
{
public:
	CSceneBillboard(int nPriority = /*9*/50);
	virtual ~CSceneBillboard();

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

	virtual void SetType(int nType);

	static CSceneBillboard *Create(void);
	static CSceneBillboard *CSceneBillboard::Create(LPCTSTR TextureName,float PosX,float PosY,float PosZ,float TexWidth,float TexHeight);

	virtual void SetColor(D3DXCOLOR Color);

protected:
	LPDIRECT3DTEXTURE9			m_Texture;
	LPDIRECT3DVERTEXBUFFER9		m_VtxBuffer;

	D3DXVECTOR3					m_Pos;
	D3DXVECTOR3					m_Rot;
	D3DXVECTOR3					m_Scl;

	VERTEX_3D*					m_pVtx;						//画像の座標のポインタ
	
	D3DXMATRIX					m_mtxProjection;				//プロジェクションマトリックス
	D3DXMATRIX					m_mtxView;						//ビューマトリックス
	D3DXMATRIX					m_mtxWorld;					//ワールドマトリックス
	D3DXMATRIX					m_mtxViewreturn;				//逆行列用のビューマトリックス

	float						TextureWidth;
	float						TextureHeight;
	LPCTSTR						m_TextureName;
};


#endif