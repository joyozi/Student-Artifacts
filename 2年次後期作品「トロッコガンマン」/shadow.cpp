//◇-------------------------------------------------------------------------◇
//
//	File	:シャドウファイル[shadow.cpp]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "input.h"
#include "shadow.h"
#include "billboard.h"
#include "camera.h"
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
LPDIRECT3DTEXTURE9 g_pTextureShadow;			//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow;	//

D3DXVECTOR3 g_posShadow;		//モデルの位置
D3DXVECTOR3 g_rotShadow;		//モデルの向き
D3DXVECTOR3 g_sclShadow;		//モデルの大きさ

D3DXMATRIX g_mtxProjectionShadow;					//プロジェクションマトリックス
D3DXMATRIX g_mtxViewShadow;						//ビューマトリックス
D3DXMATRIX g_mtxWorldShadow;						//ワールドマトリックス

D3DXVECTOR3 g_posShadowP;					//カメラの視点
D3DXVECTOR3 g_posShadowR;					//カメラの注視点
D3DXVECTOR3 g_posShadowU;					//カメラの上方向ベクトル

VERTEX_3D *pVtxShadow;

//◇-------------------------------------------------------------------------◇
//初期化処理
//◇-------------------------------------------------------------------------◇
void InitShadow(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//****位置、角度、スケールの初期化****
	g_posShadow = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_rotShadow = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclShadow = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//***カメラの初期化***
	g_posShadowP = D3DXVECTOR3(0.0f,100.0f,-150.0f);
	g_posShadowR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_posShadowU = D3DXVECTOR3(0.0f,1.0f,0.0f);

	//***テクステャの読み込み***
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/shadow000.jpg",&g_pTextureShadow);

	//***頂点情報の設定***

	//****頂点バッファの設定****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffShadow,NULL);

	//***頂点データをロック***
	g_pVtxBuffShadow->Lock(0,0,(void**)&pVtxShadow,0);

	//****頂点の位置の設定****
	pVtxShadow[0].pos = D3DXVECTOR3(-30,1,30);
	pVtxShadow[1].pos = D3DXVECTOR3(30,1,30);
	pVtxShadow[2].pos = D3DXVECTOR3(-30,1,-30);
	pVtxShadow[3].pos = D3DXVECTOR3(30,1,-30);

	//****何かの設定*****
	pVtxShadow[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtxShadow[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtxShadow[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtxShadow[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	//****カラーの設定****
	pVtxShadow[0].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtxShadow[1].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtxShadow[2].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtxShadow[3].col = D3DCOLOR_RGBA(255,255,255,55);

	//****texの設定****
	pVtxShadow[0].tex = D3DXVECTOR2(0.0,0.0);
	pVtxShadow[1].tex = D3DXVECTOR2(1.0,0.0);
	pVtxShadow[2].tex = D3DXVECTOR2(0.0,1.0);
	pVtxShadow[3].tex = D3DXVECTOR2(1.0,1.0);


	//****頂点データのロック解除
	g_pVtxBuffShadow->Unlock();
}

//◇---------------------------------◇
//終了処理
//◇---------------------------------◇
void UninitShadow(void)
{
	if(g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow ->Release();
		g_pVtxBuffShadow = NULL;
	}
	
		//テクスチャの処理
	if(g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}
//◇---------------------------------◇
//の更新処理
//◇---------------------------------◇
void UpdateShadow(void)
{
	static D3DXVECTOR3 RotShadow;

	//ビルボードの位置を取得
	RotShadow = Getg_posModel();

	//ビルボードの位置を影に移す
	g_posShadow.x = RotShadow.x;
	g_posShadow.z = RotShadow.z;
}

//◇---------------------------------◇
//の描画処理
//◇---------------------------------◇
void DrawShadow(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	
	//****デバイス取得****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//****ワールドの設定****
	D3DXMatrixIdentity(&g_mtxWorldShadow);
	D3DXMatrixScaling(&mtxScl,g_sclShadow.x,
								g_sclShadow.y,
								g_sclShadow.z);			//スケールを反映

	D3DXMatrixMultiply(&g_mtxWorldShadow,&g_mtxWorldShadow,&mtxScl);

	//****その他の設定****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotShadow.y,
									g_rotShadow.x,
									g_rotShadow.z);		//ヨ－　ピッチ　ロール

	D3DXMatrixMultiply(&g_mtxWorldShadow,&g_mtxWorldShadow,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,g_posShadow.x,g_posShadow.y,g_posShadow.z);	//位置を反映
	D3DXMatrixMultiply(&g_mtxWorldShadow,&g_mtxWorldShadow,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldShadow);	//設定

	//加算合成とかいろいろ
	pDevice -> SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_REVSUBTRACT);
	pDevice -> SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice -> SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);


	//3Dポリゴンの描画
	pDevice->SetStreamSource(0,g_pVtxBuffShadow,0,sizeof(VERTEX_3D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0,g_pTextureShadow);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//加算合成を元に戻す
	pDevice -> SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_SUBTRACT);
	pDevice -> SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice -> SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
}
