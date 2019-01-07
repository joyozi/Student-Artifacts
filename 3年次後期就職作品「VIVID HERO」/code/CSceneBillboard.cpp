//◇-------------------------------------------------------------------------◇
//
//	File:CSceneBillboardcppファイル[CSceneBillboard.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CSceneBillboard.h"
#include "CManager.h"
#include "CTextureManager.h"
#include "CCamera.h"

//◇----------------------------------◇
//コンストラクタ
//◇----------------------------------◇
CSceneBillboard::CSceneBillboard(int nPriority) : CScene(nPriority)
{
	m_Type = CTYPE_SCENEBILLBOARD;

	m_Texture = NULL;
	m_VtxBuffer = NULL;

	//****位置、角度、スケールの初期化****
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	TextureWidth = 30.0f;
	TextureHeight = 50.0f;

	m_TextureName = NULL;
}

//◇----------------------------------◇
//デストラクタ
//◇----------------------------------◇
CSceneBillboard::~CSceneBillboard()
{

}

//◇----------------------------------◇
//CSceneBillboardの初期化処理
//◇----------------------------------◇
HRESULT CSceneBillboard::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//***テクステャの読み込み***
	m_Texture = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_TextureName));

	//***頂点情報の設定***
	//****頂点バッファの設定****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_VtxBuffer,NULL);

	//背景画像の情報登録
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	//頂点情報の設定
	m_pVtx[0].pos = D3DXVECTOR3( - TextureWidth / 2, + TextureHeight / 2,0.0f);
	m_pVtx[1].pos = D3DXVECTOR3( + TextureWidth / 2, + TextureHeight / 2,0.0f);
	m_pVtx[2].pos = D3DXVECTOR3( - TextureWidth / 2, - TextureHeight / 2,0.0f);
	m_pVtx[3].pos = D3DXVECTOR3( + TextureWidth / 2, - TextureHeight / 2,0.0f);

	//****何かの設定*****
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
//CSceneBillboardの終了処理
//◇----------------------------------◇
void CSceneBillboard::Uninit(void)
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
//CSceneBillboardの更新処理
//◇----------------------------------◇
void CSceneBillboard::Update(void)
{

}

//◇----------------------------------◇
//CSceneBillboardの描画処理
//◇----------------------------------◇
void CSceneBillboard::Draw(void)
{
	//****デバイス取得****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATRIX mtxView;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスの取得
	mtxView = CManager::GetCameraPointer()->GetMtxView();

	//逆行列を求める
	D3DXMatrixInverse(&m_mtxWorld,NULL,&mtxView);

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//****ワールドの設定****
	D3DXMatrixScaling(&mtxScl,m_Scl.x,m_Scl.y,m_Scl.z);					//スケールを反映
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

	//****位置の設定****
	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);		//位置を反映
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);

	pDevice -> SetTransform(D3DTS_WORLD,&m_mtxWorld);	//設定



	//これでライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);

	//3Dポリゴンの描画
	pDevice->SetStreamSource(0,m_VtxBuffer,0,sizeof(VERTEX_3D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0,m_Texture);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//元に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);
}

//◇----------------------------------◇
//CSceneBillboardのセットポジションその１
//◇----------------------------------◇
void  CSceneBillboard::SetPosition(float x,float y,float z)
{
	m_Pos = D3DXVECTOR3(x,y,z);
}

//◇----------------------------------◇
//CSceneBillboardのセットポジションその２
//◇----------------------------------◇
void  CSceneBillboard::SetPosition(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//◇----------------------------------◇
//CSceneBillboardのゲットポジション
//◇----------------------------------◇
D3DXVECTOR3  CSceneBillboard::GetPosition(void)
{
	return m_Pos;
}

//◇----------------------------------◇
//CSceneBillboardのセットローテーションその１
//◇----------------------------------◇
void CSceneBillboard::SetRotation(float x,float y,float z)
{
	m_Rot = D3DXVECTOR3(x,y,z);
}

//◇----------------------------------◇
//CSceneBillboardのセットローテーションその2
//◇----------------------------------◇
void CSceneBillboard::SetRotation(D3DXVECTOR3 rot)
{
	m_Rot = rot;
}

//◇----------------------------------◇
//CSceneBillboardのゲットローテーション
//◇----------------------------------◇
D3DXVECTOR3 CSceneBillboard::GetRotation(void)
{
	return m_Rot;
}

//◇----------------------------------◇
//CSceneBillboardのセットタイプ
//◇----------------------------------◇
void CSceneBillboard::SetType(int nType)
{

}

//◇----------------------------------◇
//CSceneBillboardのクリエイト
//◇----------------------------------◇
CSceneBillboard *CSceneBillboard::Create(void)
{
	CSceneBillboard *pSceneBillboard;
	pSceneBillboard = new CSceneBillboard;
	pSceneBillboard->Init();

	return pSceneBillboard;
}

//◇----------------------------------◇
//CSceneBillboardのクリエイト(引数付)
//TextureName:テクスチャの名前
//PosX,PosY,PosZ:テクスチャの座標
//TexWidth,TexHeight:テクスチャのタテヨコの長さ
//◇----------------------------------◇
CSceneBillboard *CSceneBillboard::Create(LPCTSTR TextureName,float PosX,float PosY,float PosZ,float TexWidth,float TexHeight)
{
	CSceneBillboard *pSceneBillboard;
	pSceneBillboard = new CSceneBillboard;

	pSceneBillboard->m_TextureName	 = TextureName;
	pSceneBillboard->m_Pos			 = D3DXVECTOR3(PosX,PosY,PosZ);
	pSceneBillboard->TextureWidth	 = TexWidth;
	pSceneBillboard->TextureHeight	 = TexHeight;
	
	pSceneBillboard->Init();

	return pSceneBillboard;
}

//◇----------------------------------◇
//CSceneBillboardの色変え
//◇----------------------------------◇
void CSceneBillboard::SetColor(D3DXCOLOR Color)
{
	//情報登録
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	m_pVtx[0].col = D3DXCOLOR(Color.r * Color.a,Color.g * Color.a,Color.b * Color.a,Color.a);
	m_pVtx[1].col = D3DXCOLOR(Color.r * Color.a,Color.g * Color.a,Color.b * Color.a,Color.a);
	m_pVtx[2].col = D3DXCOLOR(Color.r * Color.a,Color.g * Color.a,Color.b * Color.a,Color.a);
	m_pVtx[3].col = D3DXCOLOR(Color.r * Color.a,Color.g * Color.a,Color.b * Color.a,Color.a);

	m_VtxBuffer->Unlock();
}
