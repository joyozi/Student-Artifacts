//◇-------------------------------------------------------------------------◇
//
//	File	:フィールド処理ファイル[field.cpp]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "field.h"
#include "camera.h"
#include "light.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 g_pTextureField;			//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField;	//

//◇-------------------------------------------------------------------------◇
//fieldの初期化処理
//◇-------------------------------------------------------------------------◇
void InitField(void)
{	
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	VERTEX_3D *pVtx;

	//***テクステャの読み込み***
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/Cocoontower.png",&g_pTextureField);

	//***頂点情報の設定***

	//****頂点バッファの設定****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffField,NULL);

	//***頂点データをロック***
	g_pVtxBuffField->Lock(0,0,(void**)&pVtx,0);

	//****頂点の位置の設定****
	pVtx[0].pos = D3DXVECTOR3(-50,0,50);
	pVtx[1].pos = D3DXVECTOR3(50,0,50);
	pVtx[2].pos = D3DXVECTOR3(-50,0,-50);
	pVtx[3].pos = D3DXVECTOR3(50,0,-50);

	//****何かの設定*****
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	//****カラーの設定****
	pVtx[0].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtx[1].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtx[2].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtx[3].col = D3DCOLOR_RGBA(255,255,255,55);

	//****texの設定****
	pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0,1.0);


	//****頂点データのロック解除
	g_pVtxBuffField->Unlock();
}
//◇-------------------------------------------------------------------------◇
//fieldの終了処理
//◇-------------------------------------------------------------------------◇
void UninitField(void)
{
	if(g_pVtxBuffField != NULL)
	{
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
	
		//テクスチャの処理
	if(g_pTextureField != NULL)
	{
		g_pTextureField->Release();
		g_pTextureField = NULL;
	}
}
//◇-------------------------------------------------------------------------◇
//fieldの更新処理
//◇-------------------------------------------------------------------------◇
void UpdateField(void)
{

}
//◇-------------------------------------------------------------------------◇
//fieldの描画処理
//◇-------------------------------------------------------------------------◇
void DrawField(void)
{
	//****デバイス取得****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//3Dポリゴンの描画
	pDevice->SetStreamSource(0,g_pVtxBuffField,0,sizeof(VERTEX_3D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0,g_pTextureField);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}
