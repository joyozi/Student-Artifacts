//◇-------------------------------------------------------------------------◇
//
//	ゲーム背景cppファイル[polygon.cpp]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include"main.h"
#include"GameBG.h"
//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 g_bgTexturePolygon[BG_NUM];
LPDIRECT3DVERTEXBUFFER9 g_bgVtxBuffPolygon[BG_NUM];
VERTEX_2D *g_pVtxBG;						//画像の座標のポインタ

//◇-------------------------------------------------------------------------◇
//ゲーム背景の初期化処理
//◇-------------------------------------------------------------------------◇
void InitGameBG(void)
{
	LPDIRECT3DDEVICE9 bgDevice;
	bgDevice = GetDevice();

	for(int nCnt = 0;nCnt < BG_NUM;nCnt++)
	{
		g_bgTexturePolygon[nCnt] = NULL;
		g_bgVtxBuffPolygon[nCnt] = NULL;

		bgDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_bgVtxBuffPolygon[nCnt],NULL);
	}
	//背景画像の情報登録
	g_bgVtxBuffPolygon[0]->Lock(0,0,(void**)&g_pVtxBG,0);

	//頂点情報の設定
	g_pVtxBG[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_pVtxBG[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
	g_pVtxBG[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
	g_pVtxBG[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);

	g_pVtxBG[0].rhw = 1.0f;
	g_pVtxBG[1].rhw = 1.0f;
	g_pVtxBG[2].rhw = 1.0f;
	g_pVtxBG[3].rhw = 1.0f;

	g_pVtxBG[0].col = D3DCOLOR_RGBA(255,255,255,255);
	g_pVtxBG[1].col = D3DCOLOR_RGBA(255,255,255,255);
	g_pVtxBG[2].col = D3DCOLOR_RGBA(255,255,255,255);
	g_pVtxBG[3].col = D3DCOLOR_RGBA(255,255,255,255);

	g_pVtxBG[0].tex = D3DXVECTOR2(0.0,0.0);
	g_pVtxBG[1].tex = D3DXVECTOR2(1.0,0.0);
	g_pVtxBG[2].tex = D3DXVECTOR2(0.0,1.0);
	g_pVtxBG[3].tex = D3DXVECTOR2(1.0,1.0);
			
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/game_BG02.jpg",&g_bgTexturePolygon[0]);

	g_bgVtxBuffPolygon[0]->Unlock();
	
}
//-------------------------------------
//ゲーム背景終了処理
//-------------------------------------
void UninitGameBG(void)
{
	for(int nCnt = 0;nCnt < BG_NUM;nCnt++)
	{
		//バッファの処理	
		if(g_bgVtxBuffPolygon[nCnt] != NULL)
		{
			g_bgVtxBuffPolygon[nCnt]->Release();
			g_bgVtxBuffPolygon[nCnt] = NULL;
		}
	
			//テクスチャの処理
		if(g_bgTexturePolygon[nCnt] != NULL)
		{
			g_bgTexturePolygon[nCnt]->Release();
			g_bgTexturePolygon[nCnt] = NULL;
		}
	}
}
//-------------------------------------
//ゲーム背景の更新処理
//-------------------------------------
void UpdateGameBG(void)
{

}
//-------------------------------------
//ゲーム背景の描画処理
//-------------------------------------
void DrawGameBG(void)
{
	for(int nCnt = 0;nCnt < BG_NUM;nCnt++)
	{
		//背景の描画
		GetDevice()->SetStreamSource(0,g_bgVtxBuffPolygon[nCnt],0,sizeof(VERTEX_2D));
		//頂点フォーマットの設定
		GetDevice()->SetFVF(FVF_VERTEX_2D);
		//テクスチャの設定
		GetDevice()->SetTexture(0,g_bgTexturePolygon[nCnt]);
		//ポリゴンの描画
		GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	}
}