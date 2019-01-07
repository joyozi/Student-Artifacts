//◇-------------------------------------------------------------------------◇
//
//	File	:CSceneStencilShadowファイル[CSceneStencilShadow.cpp]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CSceneStencilShadow.h"
#include "CManager.h"
#include "CTextureManager.h"

//◇----------------------------------◇
//コンストラクタ
//◇----------------------------------◇
CSceneStencilShadow::CSceneStencilShadow(int nPriority) : CScene(nPriority)
{
	//****位置、角度、スケールの初期化****
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	m_Texture = NULL;

	m_TextureName = NULL;
	m_XfileName = NULL;

	m_Type = CTYPE_SCENESTENCILSHADOW;
}

//◇----------------------------------◇
//デストラクタ
//◇----------------------------------◇
CSceneStencilShadow::~CSceneStencilShadow()
{

}

//◇----------------------------------◇
//CSceneStencilShadowの初期化処理
//◇----------------------------------◇
HRESULT CSceneStencilShadow::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//***テクステャの読み込み***
	if(m_TextureName != NULL)
	{
		m_Texture = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_TextureName));
	}

	//モデルのロード
	m_XFile_Info = CManager::GetXFileManagerPointer()->GetXFile(CManager::GetXFileManagerPointer()->Load(m_XfileName));

	//頂点情報の登録
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&m_VtxBuffer,NULL);
	
	//背景画像の情報登録
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	//頂点情報の設定
	m_pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
	m_pVtx[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
	m_pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);

	m_pVtx[0].rhw = 1.0f;
	m_pVtx[1].rhw = 1.0f;
	m_pVtx[2].rhw = 1.0f;
	m_pVtx[3].rhw = 1.0f;

	m_pVtx[0].col = D3DXCOLOR(1.0,1.0,1.0,1.0);
	m_pVtx[1].col = D3DXCOLOR(1.0,1.0,1.0,1.0);
	m_pVtx[2].col = D3DXCOLOR(1.0,1.0,1.0,1.0);
	m_pVtx[3].col = D3DXCOLOR(1.0,1.0,1.0,1.0);

	m_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	m_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	m_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	m_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);

	m_VtxBuffer->Unlock();

	return S_OK;
}

//◇----------------------------------◇
//CSceneStencilShadowの終了処理
//◇----------------------------------◇
void CSceneStencilShadow::Uninit(void)
{
	Release();
}

//◇----------------------------------◇
//CSceneStencilShadowの更新処理
//◇----------------------------------◇
void CSceneStencilShadow::Update(void)
{

}

//◇----------------------------------◇
//CSceneStencilShadowの描画処理
//◇----------------------------------◇
void CSceneStencilShadow::Draw(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//ステンシルテストを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE,TRUE);
	//Zバッファへの書き込み無効
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
	//カラーバッファへの書き込み無効
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,0);

	//ステンシル設定１
	//ステンシル参照値の設定

	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_ALWAYS);	//全て合格させる(ステンシルテスト)

	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_ZERO);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_INCR);
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_ZERO);

	//カリングを逆(クロッズワイズ)にする
	pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);
	DrawXModel();

	//ステンシル設定2

	//ステンシル参照値の設定
	pDevice->SetRenderState(D3DRS_STENCILREF,1);

	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_GREATEREQUAL);	//参照値以上で合格させる

	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_INCR);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_ZERO);
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_ZERO);

	//カリングを元(カウンタークロックワイズ)に戻す
	pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	DrawXModel();

	//ステンシル設定3
	//ステンシル参照値の設定
	pDevice->SetRenderState(D3DRS_STENCILREF,2);

	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_EQUAL);			//同値で合格させる

	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_KEEP);

	//カラーバッファへの書き込み有効
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,0xf);		//これを有効としてみる

	//２Dポリゴンの描画
	//背景の描画
	pDevice->SetStreamSource(0,m_VtxBuffer,0,sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0,NULL);
	//テクスチャの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//Zバッファへの書き込み有効
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	//ステンシルテストを無効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE,FALSE);
}

//◇----------------------------------◇
//CSceneStencilShadowの３ｄモデル描画
//◇----------------------------------◇
void CSceneStencilShadow::DrawXModel(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//マットのデフォルト

	//****ワールドの設定****
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&mtxScl,m_Scl.x,
								m_Scl.y,
								m_Scl.z);	//スケールを反映

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

	//****その他の設定****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_Rot.y,
									m_Rot.x,
									m_Rot.z);		//ヨ－　ピッチ　ロール

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);

	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);		//位置を反映
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&m_mtxWorld);	//設定

	//モデルの描画
	pDevice -> GetMaterial(&matDef);
	pMat = (D3DXMATERIAL*)m_XFile_Info.BuffMat->GetBufferPointer();

	for(int nCntMat = 0;nCntMat < (int)m_XFile_Info.numMat;nCntMat++)
	{
		pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
		pDevice -> SetTexture(0,m_Texture);
		m_XFile_Info.Mesh -> DrawSubset(nCntMat);
	}
	pDevice -> SetMaterial(&matDef);

}

//◇----------------------------------◇
//CSceneStencilShadowのセットポジションその１
//◇----------------------------------◇
void CSceneStencilShadow::SetPosition(float x,float y,float z)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}

//◇----------------------------------◇
//CSceneStencilShadowのセットポジションその２
//◇----------------------------------◇
void CSceneStencilShadow::SetPosition(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//◇----------------------------------◇
//CSceneStencilShadowのゲットポジション
//◇----------------------------------◇
D3DXVECTOR3 CSceneStencilShadow::GetPosition(void)
{
	return m_Pos;
}

//◇----------------------------------◇
//CSceneStencilShadowのセットローテーションその１
//◇----------------------------------◇
void CSceneStencilShadow::SetRotation(float x,float y,float z)
{
	m_Rot.x = x;
	m_Rot.y = y;
	m_Rot.z = z;
}

//◇----------------------------------◇
//CSceneStencilShadowのセットローテーションその2
//◇----------------------------------◇
void CSceneStencilShadow::SetRotation(D3DXVECTOR3 rot)
{
	m_Rot.x = rot.x;
	m_Rot.y = rot.y;
	m_Rot.z = rot.z;
}

//◇----------------------------------◇
//CSceneStencilShadowのゲットローテーション
//◇----------------------------------◇
D3DXVECTOR3 CSceneStencilShadow::GetRotation(void)
{
	return m_Rot;
}

//◇----------------------------------◇
//CSceneStencilShadowのセットタイプ
//◇----------------------------------◇
void CSceneStencilShadow::SetType(int nType)
{
//	m_Type = CTYPE_SCENEX;
}


//◇----------------------------------◇
//CSceneStencilShadowDの	クリエイト(引数付)
//TextureName:テクスチャの名前
//PosX,PosY,PosZ:テクスチャの座標
//◇----------------------------------◇
CSceneStencilShadow *CSceneStencilShadow::Create(LPCTSTR XfileName,D3DXVECTOR3 Pos)
{
	CSceneStencilShadow *pSceneX;
	pSceneX = new CSceneStencilShadow;

	pSceneX->m_XfileName = XfileName;
	pSceneX->m_Pos = Pos;
	
	pSceneX->Init();

	return pSceneX;
}
