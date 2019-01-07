//◇-------------------------------------------------------------------------◇
//
//	File:CScene2Dcppファイル[CScene2D.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#include "CScene2D.h"
#include "CManager.h"
#include "CTextureManager.h"

//◇----------------------------------◇
//コンストラクタ
//◇----------------------------------◇
CScene2D::CScene2D(int nPriority):CScene(nPriority)		//<-const char *pNone?
{
	m_Type = CTYPE_SCENE2D;

	m_Texture = NULL;
	m_VtxBuffer = NULL;
	m_TextureName = NULL;

	//****位置、角度の初期化****
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);

	TextureWidth = 0.0f;
	TextureHeight = 0.0f;
	m_Color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_TextureName= NULL;
}

//◇----------------------------------◇
//デストラクタ
//◇----------------------------------◇
CScene2D::~CScene2D()
{

}

//◇----------------------------------◇
//CScene2Dの初期化処理
//◇----------------------------------◇
HRESULT CScene2D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//テクスチャのロード
	if(m_TextureName != NULL)
	{
		m_Texture = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer()->Load(m_TextureName));
	}

	//頂点情報の登録
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&m_VtxBuffer,NULL);
	
	//背景画像の情報登録
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	//頂点情報の設定
	m_pVtx[0].pos = D3DXVECTOR3(m_Pos.x - TextureWidth/2,m_Pos.y - TextureHeight/2,0.0f);
	m_pVtx[1].pos = D3DXVECTOR3(m_Pos.x + TextureWidth/2,m_Pos.y - TextureHeight/2,0.0f);
	m_pVtx[2].pos = D3DXVECTOR3(m_Pos.x - TextureWidth/2,m_Pos.y + TextureHeight/2,0.0f);
	m_pVtx[3].pos = D3DXVECTOR3(m_Pos.x + TextureWidth/2,m_Pos.y + TextureHeight/2,0.0f);

	m_pVtx[0].rhw = 1.0f;
	m_pVtx[1].rhw = 1.0f;
	m_pVtx[2].rhw = 1.0f;
	m_pVtx[3].rhw = 1.0f;

	m_pVtx[0].col = m_Color;
	m_pVtx[1].col = m_Color;
	m_pVtx[2].col = m_Color;
	m_pVtx[3].col = m_Color;

	m_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	m_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	m_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	m_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);

	m_VtxBuffer->Unlock();

	return S_OK;
}

//◇----------------------------------◇
//CScene2Dの終了処理
//◇----------------------------------◇
void CScene2D::Uninit(void)
{
	Release();

	//バッファの処理
	if(m_VtxBuffer != NULL)
	{
		m_VtxBuffer->Release();
		m_VtxBuffer = NULL;
	}
}

//◇----------------------------------◇
//CScene2Dの更新処理
//◇----------------------------------◇
void CScene2D::Update(void)
{

}

//◇----------------------------------◇
//CScene2Dの描画処理
//◇----------------------------------◇
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//背景の描画
	pDevice->SetStreamSource(0,m_VtxBuffer,0,sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0,m_Texture);
	//テクスチャの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}

//◇----------------------------------◇
//CScene2Dのセットポジションその１
//◇----------------------------------◇
void  CScene2D::SetPosition(float x,float y,float z)
{
	m_Pos = D3DXVECTOR3(x,y,z);
}

//◇----------------------------------◇
//CScene2Dのセットポジションその２
//◇----------------------------------◇
void  CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//◇----------------------------------◇
//CScene2Dのゲットポジション
//◇----------------------------------◇
D3DXVECTOR3  CScene2D::GetPosition(void)
{
	return m_Pos;
}

//◇----------------------------------◇
//CScene2Dのセットローテーションその１
//◇----------------------------------◇
void CScene2D::SetRotation(float x,float y,float z)
{
	m_Rot = D3DXVECTOR3(x,y,z);
}

//◇----------------------------------◇
//CScene2Dのセットローテーションその2
//◇----------------------------------◇
void CScene2D::SetRotation(D3DXVECTOR3 rot)
{
	m_Rot = rot;
}

//◇----------------------------------◇
//CScene2Dのゲットローテーション
//◇----------------------------------◇
D3DXVECTOR3 CScene2D::GetRotation(void)
{
	return m_Rot;
}

//◇----------------------------------◇
//CScene2Dのセットタイプ
//◇----------------------------------◇
void CScene2D::SetPosition_Re(D3DXVECTOR3 pos)
{
	m_Pos = pos;

	float Angle = atan2f(TextureWidth,TextureHeight);
	float Length = sqrtf((TextureHeight * TextureHeight) + (TextureWidth * TextureWidth)) / 2;

	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	//頂点情報の設定
	m_pVtx[0].pos = D3DXVECTOR3(pos.x + Length * sinf(m_Rot.y + Angle)			,pos.y + Length * cosf(m_Rot.y + Angle)			,0.0f);
	m_pVtx[1].pos = D3DXVECTOR3(pos.x + Length * sinf(m_Rot.y - Angle)			,pos.y + Length * cosf(m_Rot.y - Angle)			,0.0f);
	m_pVtx[2].pos = D3DXVECTOR3(pos.x + Length * sinf(m_Rot.y - Angle + D3DX_PI),pos.y + Length * cosf(m_Rot.y - Angle + D3DX_PI)			,0.0f);
	m_pVtx[3].pos = D3DXVECTOR3(pos.x + Length * sinf(m_Rot.y + Angle + D3DX_PI),pos.y + Length * cosf(m_Rot.y + Angle + D3DX_PI)			,0.0f);

	m_VtxBuffer->Unlock();

}


//◇----------------------------------◇
//CScene2Dのセットタイプ
//◇----------------------------------◇
void CScene2D::SetSize(D3DXVECTOR3 size)
{
	TextureWidth = size.x;
	TextureHeight = size.y;

	float Angle = atan2f(TextureWidth,TextureHeight);
	float Length = sqrtf((TextureHeight * TextureHeight) + (TextureWidth * TextureWidth)) / 2;

	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	//頂点情報の設定
	m_pVtx[0].pos = D3DXVECTOR3(m_Pos.x + Length * sinf(m_Rot.y + Angle + D3DX_PI),m_Pos.y + Length * cosf(m_Rot.y + Angle + D3DX_PI)			,0.0f);
	m_pVtx[1].pos = D3DXVECTOR3(m_Pos.x + Length * sinf(m_Rot.y - Angle + D3DX_PI),m_Pos.y + Length * cosf(m_Rot.y - Angle + D3DX_PI)			,0.0f);
	m_pVtx[2].pos = D3DXVECTOR3(m_Pos.x + Length * sinf(m_Rot.y - Angle)			,m_Pos.y + Length * cosf(m_Rot.y - Angle)			,0.0f);
	m_pVtx[3].pos = D3DXVECTOR3(m_Pos.x + Length * sinf(m_Rot.y + Angle)			,m_Pos.y + Length * cosf(m_Rot.y + Angle)			,0.0f);

	m_VtxBuffer->Unlock();
}

//◇----------------------------------◇
//CScene2Dのセットタイプ
//◇----------------------------------◇
void CScene2D::SetType(int nType)
{

}

//◇----------------------------------◇
//CScene2Dの	クリエイト(引数付)
//TextureName:テクスチャの名前
//PosX,PosY,PosZ:テクスチャの座標
//TexWidth,TexHeight:テクスチャのタテヨコの長さ
//◇----------------------------------◇
CScene2D *CScene2D::Create(LPCTSTR TextureName,D3DXVECTOR3 Pos,D3DXVECTOR3 Size)
{
	CScene2D *pScene2D;
	pScene2D = new CScene2D;

	pScene2D->m_TextureName = TextureName;
	pScene2D->m_Pos = Pos;
	pScene2D->TextureWidth = Size.x;
	pScene2D->TextureHeight = Size.y;
	
	pScene2D->Init();

	return pScene2D;
}

//◇----------------------------------◇
//CScene2Dのクリエイト　プライオリティ付き
//◇----------------------------------◇
CScene2D *CScene2D::Create(int Priority,LPCTSTR TextureName,D3DXVECTOR3 Pos,D3DXVECTOR3 Size)
{
	CScene2D *pScene2D;
	pScene2D = new CScene2D(Priority);

	pScene2D->m_TextureName = TextureName;
	pScene2D->m_Pos = Pos;
	pScene2D->TextureWidth = Size.x;
	pScene2D->TextureHeight = Size.y;
	
	pScene2D->Init();

	return pScene2D;
}


//◇----------------------------------◇
//CScene2Dのテクスチャ頂点のセット
//◇----------------------------------◇
void CScene2D::SetVertex_Tex(D3DXVECTOR2 Vtx[])
{
	//背景画像の情報登録
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	//頂点情報の設定
	m_pVtx[0].tex = Vtx[0];
	m_pVtx[1].tex = Vtx[1];
	m_pVtx[2].tex = Vtx[2];
	m_pVtx[3].tex = Vtx[3];

	m_VtxBuffer->Unlock();
}

//◇----------------------------------◇
//CScene2Dのカラーのセット　頂点ごとにセット可能
//◇----------------------------------◇
void CScene2D::SetVertex_Col(D3DXCOLOR Col[])
{
	//背景画像の情報登録
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	//頂点情報の設定
	m_pVtx[0].col = Col[0];
	m_pVtx[1].col = Col[1];
	m_pVtx[2].col = Col[2];
	m_pVtx[3].col = Col[3];

	m_VtxBuffer->Unlock();
}

//◇----------------------------------◇
//CScene2Dのカラーのセット　一つの色のみセット可能
//◇----------------------------------◇
void CScene2D::SetVertex_Col(D3DXCOLOR Col)
{
	//背景画像の情報登録
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	//頂点情報の設定
	m_pVtx[0].col = Col;
	m_pVtx[1].col = Col;
	m_pVtx[2].col = Col;
	m_pVtx[3].col = Col;

	m_VtxBuffer->Unlock();
}
