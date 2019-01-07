//◇-------------------------------------------------------------------------◇
//
//	File	:モデル処理ファイル[model.cpp]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "box.h"
#include "model.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 g_pTextureBox;		//
LPD3DXMESH g_pMeshBox;				//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatBox;			//マテリアル情報へのポインタ

DWORD g_numMatBox;					//マテリアルの数
D3DXVECTOR3 g_posBox;					//モデルの位置
D3DXVECTOR3 g_rotBox;					//モデルの向き
D3DXVECTOR3 g_sclBox;					//モデルの大きさ

D3DXMATRIX g_mtxProjectionBox;		//プロジェクションマトリックス
D3DXMATRIX g_mtxViewBox;				//ビューマトリックス
D3DXMATRIX g_mtxWorldBox;				//ワールドマトリックス

//◇-------------------------------------------------------------------------◇
//モデルの初期化処理
//◇-------------------------------------------------------------------------◇
void InitBox(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	VERTEX_3D *pVtx;

	//****モデルの情報セット****
	D3DXLoadMeshFromX("./data/MODEL/box006.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatBox,
					NULL,
					&g_numMatBox,
					&g_pMeshBox);

	//****位置、角度、スケールの初期化****
	g_posBox = D3DXVECTOR3(0.0f,30.0f,1000);
	g_rotBox = D3DXVECTOR3(0.0f,D3DX_PI,0.0f);
	g_sclBox = D3DXVECTOR3(1.0f,1.0f,1.0f);
}
//◇-------------------------------------------------------------------------◇
//モデルの終了処理
//◇-------------------------------------------------------------------------◇
void UninitBox(void)
{
	//メッシュモデルのリリース
	//==============================
	if(g_pMeshBox != NULL)
	{
		g_pMeshBox->Release();
		g_pMeshBox = NULL;
	}
	
	//バッファマットのリリース
	//=============================
	if(g_pBuffMatBox != NULL)
	{
		g_pBuffMatBox->Release();
		g_pBuffMatBox = NULL;
	}
}
//◇-------------------------------------------------------------------------◇
//モデルの更新処理
//◇-------------------------------------------------------------------------◇
void UpdateBox(void)
{
	g_rotBox.y +=0.05f;
}
//◇-------------------------------------------------------------------------◇
//モデルの描画処理
//◇-------------------------------------------------------------------------◇
void DrawBox(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//マットのデフォルト

	//****ワールドの設定****
	D3DXMatrixIdentity(&g_mtxWorldBox);
	D3DXMatrixScaling(&mtxScl,g_sclBox.x,
								g_sclBox.y,
								g_sclBox.z);			//スケールを反映

	D3DXMatrixMultiply(&g_mtxWorldBox,&g_mtxWorldBox,&mtxScl);

	//****その他の設定****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotBox.y,
									g_rotBox.x,
									g_rotBox.z);		//ヨ－　ピッチ　ロール

	D3DXMatrixMultiply(&g_mtxWorldBox,&g_mtxWorldBox,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,g_posBox.x,g_posBox.y,g_posBox.z);	//位置を反映
	D3DXMatrixMultiply(&g_mtxWorldBox,&g_mtxWorldBox,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldBox);	//設定

	//=========マテリアルなどの取得=========
	//======================================
	pDevice -> GetMaterial(&matDef);
	pMat = (D3DXMATERIAL*)g_pBuffMatBox -> GetBufferPointer();

	for(int nCntMat = 0;nCntMat < (int)g_numMatBox;nCntMat++)
	{
		pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
		pDevice -> SetTexture(0,NULL);
		g_pMeshBox -> DrawSubset(nCntMat);
	}

	pDevice -> SetMaterial(&matDef);
}
