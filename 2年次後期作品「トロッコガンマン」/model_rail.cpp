//◇-------------------------------------------------------------------------◇
//
//	File	:モデル処理ファイル[rail.cpp]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "input.h"
#include "model_rail.h"
#include "model.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇
#define MODEL_RAIL_DATA	("./data/MODEL/rail_002.x")	//モデルのデータの位置と名前

#define MODEL_RAILLONG	(6000)								//レールの長さ

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 g_pTextureRail;		//
LPD3DXMESH g_pMeshRail;					//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatRail;			//マテリアル情報へのポインタ

DWORD g_numMatRail;						//マテリアルの数
D3DXVECTOR3 g_posRail;					//モデルの位置
D3DXVECTOR3 g_rotRail;					//モデルの向き
D3DXVECTOR3 g_sclRail;					//モデルの大きさ

D3DXMATRIX g_mtxWorldRail;				//ワールドマトリックス

float railLong;		//レールの一番後ろの座標

//◇-------------------------------------------------------------------------◇
//モデルの初期化処理
//◇-------------------------------------------------------------------------◇
void InitRail(void)
{
	//レール位置の初期化しないとね
	railLong = -MODEL_RAILLONG / 2;

	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//****モデルの情報セット****
	D3DXLoadMeshFromX(MODEL_RAIL_DATA,
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatRail,
					NULL,
					&g_numMatRail,
					&g_pMeshRail);

	//****位置、角度、スケールの初期化****
	g_posRail = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_rotRail = D3DXVECTOR3(0.0f,D3DX_PI,0.0f);
	g_sclRail = D3DXVECTOR3(1.0f,1.0f,1.0f);
}
//◇-------------------------------------------------------------------------◇
//モデルの終了処理
//◇-------------------------------------------------------------------------◇
void UninitRail(void)
{
	//メッシュモデルのリリース
	//==============================
	if(g_pMeshRail != NULL)
	{
		g_pMeshRail -> Release();
		g_pMeshRail = NULL;
	}
	
	//バッファマットのリリース
	//=============================
	if(g_pBuffMatRail != NULL)
	{
		g_pBuffMatRail -> Release();
		g_pBuffMatRail = NULL;
	}

	//テクステャのリリース
	//=============================
	if(g_pTextureRail != NULL)
	{
		g_pTextureRail -> Release();
		g_pTextureRail = NULL;

	}
}
//◇-------------------------------------------------------------------------◇
//モデルの更新処理
//◇-------------------------------------------------------------------------◇
void UpdateRail(void)
{

}
//◇-------------------------------------------------------------------------◇
//モデルの描画処理
//◇-------------------------------------------------------------------------◇
void DrawRail(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//マットのデフォルト

	while(Getg_posModel().z - MODEL_RAILLONG / 2 >= railLong)
	{
		railLong += 98;
	}

	while(Getg_posModel().z + MODEL_RAILLONG / 2 < railLong + MODEL_RAILLONG)
	{
		railLong -= 98;
	}

	g_posRail.z = railLong;//Getg_posModel().z - 2000;

	while(g_posRail.z < railLong + MODEL_RAILLONG)
	{
		g_posRail.z += 98; 

		//****ワールドの設定****
		D3DXMatrixIdentity(&g_mtxWorldRail);
		D3DXMatrixScaling(&mtxScl,g_sclRail.x,
									g_sclRail.y,
									g_sclRail.z);			//スケールを反映

		D3DXMatrixMultiply(&g_mtxWorldRail,&g_mtxWorldRail,&mtxScl);

		//****その他の設定****
		D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotRail.y,
										g_rotRail.x,
										g_rotRail.z);		//ヨ－　ピッチ　ロール

		D3DXMatrixMultiply(&g_mtxWorldRail,&g_mtxWorldRail,&mtxRot);
		D3DXMatrixTranslation(&mtxTranslate,g_posRail.x,g_posRail.y,g_posRail.z);	//位置を反映
		D3DXMatrixMultiply(&g_mtxWorldRail,&g_mtxWorldRail,&mtxTranslate);
	
		pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldRail);	//設定

		//=========マテリアルなどの取得=========
		//======================================
		pDevice -> GetMaterial(&matDef);
		pMat = (D3DXMATERIAL*)g_pBuffMatRail -> GetBufferPointer();

		for(int nCntMat = 0;nCntMat < (int)g_numMatRail;nCntMat++)
		{
			pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
			pDevice -> SetTexture(0,NULL);
			g_pMeshRail -> DrawSubset(nCntMat);
		}

		pDevice -> SetMaterial(&matDef);
	}
}

//================================
//位置と角度の取得関数
//================================
D3DXVECTOR3 Getg_posRail(void)
{
	return g_posRail;
}

D3DXVECTOR3 Getg_rotRail(void)
{
	return g_rotRail;
}
