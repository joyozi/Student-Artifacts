//◇-------------------------------------------------------------------------◇
//
//	File:CScene3Dcppファイル[CScene3D.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CScene3D.h"
#include "CManager.h"

#include "CTextureManager.h"

//◇----------------------------------◇
//コンストラクタ
//◇----------------------------------◇
CScene3D::CScene3D(int nPriority) : CScene(nPriority)
{
	m_Type = CTYPE_SCENE3D;

	m_Texture = NULL;
	m_VtxBuffer = NULL;

	//****位置、角度、スケールの初期化****
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	m_TexWidth = 0.0f;
	m_TexHeight = 0.0f;
}

//◇----------------------------------◇
//デストラクタ
//◇----------------------------------◇
CScene3D::~CScene3D()
{

}

//◇----------------------------------◇
//CScene3Dの初期化処理
//◇----------------------------------◇
HRESULT CScene3D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//***テクステャの読み込み***
	m_Texture = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_TexName));

	//***頂点情報の設定***
	//****頂点バッファの設定****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_VtxBuffer,NULL);
	
	//背景画像の情報登録
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	//頂点情報の設定
	m_pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_TexWidth/2,m_Pos.y + m_TexHeight/2,0.0f);
	m_pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_TexWidth/2,m_Pos.y + m_TexHeight/2,0.0f);
	m_pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_TexWidth/2,m_Pos.y - m_TexHeight/2,0.0f);
	m_pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_TexWidth/2,m_Pos.y - m_TexHeight/2,0.0f);

	//****これ法線！法線！ｓの設定*****
	m_pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	m_pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	m_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	m_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	m_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	m_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);

	m_VtxBuffer->Unlock();

	return S_OK;
}

//◇----------------------------------◇
//CScene3Dの終了処理
//◇----------------------------------◇
void CScene3D::Uninit(void)
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
//CScene3Dの更新処理
//◇----------------------------------◇
void CScene3D::Update(void)
{

}

//◇----------------------------------◇
//CScene3Dの描画処理
//◇----------------------------------◇
void CScene3D::Draw(void)
{
	//****デバイス取得****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;	//

	//****ワールドの設定****
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&mtxScl,m_Scl.x,
								m_Scl.y,
								m_Scl.z);			//スケールを反映

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

	//****その他の設定****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_Rot.y,
									m_Rot.x,
									m_Rot.z);		//ヨ－　ピッチ　ロール

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);		//位置を反映
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&m_mtxWorld);	//設定

	//3Dポリゴンの描画
	pDevice->SetStreamSource(0,m_VtxBuffer,0,sizeof(VERTEX_3D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0,m_Texture);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}

//◇----------------------------------◇
//CScene3Dのセットポジションその１
//◇----------------------------------◇
void  CScene3D::SetPosition(float x,float y,float z)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}

//◇----------------------------------◇
//CScene3Dのセットポジションその２
//◇----------------------------------◇
void  CScene3D::SetPosition(D3DXVECTOR3 pos)
{	
	m_Pos.x = pos.x;
	m_Pos.y = pos.y;
	m_Pos.z = pos.z;
}

//◇----------------------------------◇
//CScene3Dのゲットポジション
//◇----------------------------------◇
D3DXVECTOR3  CScene3D::GetPosition(void)
{
	return m_Pos;
}

//◇----------------------------------◇
//CScene3Dのセットローテーションその１
//◇----------------------------------◇
void CScene3D::SetRotation(float x,float y,float z)
{
	m_Rot.x = x;
	m_Rot.y = y;
	m_Rot.z = z;
}

//◇----------------------------------◇
//CScene3Dのセットローテーションその2
//◇----------------------------------◇
void CScene3D::SetRotation(D3DXVECTOR3 rot)
{
	m_Rot.x = rot.x;
	m_Rot.y = rot.y;
	m_Rot.z = rot.z;
}

//◇----------------------------------◇
//CScene3Dのゲットローテーション
//◇----------------------------------◇
D3DXVECTOR3 CScene3D::GetRotation(void)
{
	return m_Rot;
}

//◇----------------------------------◇
//CScene3Dのセットタイプ
//◇----------------------------------◇
void CScene3D::SetType(int nType)
{

}

//◇----------------------------------◇
//CScene3Dの	クリエイト(引数付)
//TextureName:テクスチャの名前
//Pos:テクスチャの座標
//Rot:テクステャの角度
//m_TexWidth,m_TexHeight:テクスチャのタテヨコの長さ
//◇----------------------------------◇
CScene3D *CScene3D::Create(LPCTSTR TextureName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,float TexWidth,float TexHeight)
{
	CScene3D *pScene3D;
	pScene3D = new CScene3D;

	pScene3D->m_TexName = TextureName;
	pScene3D->m_Pos = Pos;
	pScene3D->m_Rot = Rot;

	pScene3D->m_TexWidth = TexWidth;
	pScene3D->m_TexHeight = TexHeight;
	pScene3D->Init();

	return pScene3D;
}

//◇----------------------------------◇
//CScene3Dの	クリエイト
//◇----------------------------------◇
CScene3D *CScene3D::Create(int Priority,LPCTSTR TextureName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,float m_TexWidth,float m_TexHeight)
{
	CScene3D *pScene3D;
	pScene3D = new CScene3D(Priority);

	pScene3D->m_TexName		 = TextureName;
	pScene3D->m_Pos			 = Pos;
	pScene3D->m_Rot			 = Rot;

	pScene3D->m_TexWidth	 = m_TexWidth;
	pScene3D->m_TexHeight	 = m_TexHeight;
	pScene3D->Init();

	return pScene3D;
}

//◇----------------------------------◇
//ポリゴンの座標をゲットする関数
//◇----------------------------------◇
VERTEX_3D CScene3D::GetVERTEXPos(int num)
{
	return m_pVtx[num];
}


//◇----------------------------------◇
//ポリゴンの色変更関数
//◇----------------------------------◇
void CScene3D::SetColor(D3DXCOLOR Color)
{
	//背景画像の情報登録
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	m_pVtx[0].col = Color;
	m_pVtx[1].col = Color;
	m_pVtx[2].col = Color;
	m_pVtx[3].col = Color;

	m_VtxBuffer->Unlock();
}