//◇-------------------------------------------------------------------------◇
//
//	File:CMeshBasisClassのファイル[CMeshBasisClass.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CMeshBasisClass.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CMeshBasisClassのコンストラクタ
//◇-----------------------------------◇
CMeshBasisClass::CMeshBasisClass(int nPriority) : CScene3D(nPriority)
{
	m_Type = CTYPE_MESHBESISCLASS;

	m_IdxBuffer = NULL;

	m_VtxNum = 0;
	m_IndexNum = 0;
	m_PolygonNum = 0;
}

//◇-----------------------------------◇
//CMeshBasisClassのデストラクタ
//◇-----------------------------------◇
CMeshBasisClass::~CMeshBasisClass()
{

}

//◇-----------------------------------◇
//CMeshBasisClassの終了処理
//◇-----------------------------------◇
void CMeshBasisClass::Uninit(void)
{
	Release();

	//バッファの処理
	if(m_VtxBuffer != NULL)
	{
		m_VtxBuffer->Release();
		m_VtxBuffer = NULL;
	}

	//インデックスバッファのリリース
	if(m_IdxBuffer != NULL)
	{
		m_IdxBuffer->Release();
		m_IdxBuffer = NULL;
	}
}

//◇-----------------------------------◇
//CMeshBasisClassの描画処理
//◇-----------------------------------◇
void CMeshBasisClass::Draw(void)
{
	//****デバイス取得****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

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
	//頂点バッファをバインド
	pDevice -> SetIndices(m_IdxBuffer);		//インデックスバッファをバインド
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0,m_Texture);
	//ドロウプリミティブ
	pDevice -> DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_VtxNum,0,m_PolygonNum);
}


