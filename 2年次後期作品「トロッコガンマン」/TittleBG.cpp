//◇-------------------------------------------------------------------------◇
//
//	タイトル背景cppファイル[TittleBG.cpp]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include"main.h"
#include"TittleBG.h"
//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 t_bgTexturePolygon = NULL;
LPDIRECT3DVERTEXBUFFER9 t_bgVtxBuffPolygon = NULL;
VERTEX_2D *t_pVtxBG;		//画像の座標のポインタ

//◇-------------------------------------------------------------------------◇
//タイトル背景の初期化処理
//◇-------------------------------------------------------------------------◇
void InitTittleBG(void)
{
	LPDIRECT3DDEVICE9 bgDevice;
	bgDevice = GetDevice();
	bgDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&t_bgVtxBuffPolygon,NULL);

	//背景画像の情報登録
	t_bgVtxBuffPolygon->Lock(0,0,(void**)&t_pVtxBG,0);

	//頂点情報の設定
	t_pVtxBG[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	t_pVtxBG[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
	t_pVtxBG[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
	t_pVtxBG[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);

	t_pVtxBG[0].rhw = 1.0f;
	t_pVtxBG[1].rhw = 1.0f;
	t_pVtxBG[2].rhw = 1.0f;
	t_pVtxBG[3].rhw = 1.0f;

	t_pVtxBG[0].col = D3DCOLOR_RGBA(255,255,255,255);
	t_pVtxBG[1].col = D3DCOLOR_RGBA(255,255,255,255);
	t_pVtxBG[2].col = D3DCOLOR_RGBA(255,255,255,255);
	t_pVtxBG[3].col = D3DCOLOR_RGBA(255,255,255,255);

	t_pVtxBG[0].tex = D3DXVECTOR2(0.0,0.0);
	t_pVtxBG[1].tex = D3DXVECTOR2(1.0,0.0);
	t_pVtxBG[2].tex = D3DXVECTOR2(0.0,1.0);
	t_pVtxBG[3].tex = D3DXVECTOR2(1.0,1.0);
			
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/torokko_001.jpg",&t_bgTexturePolygon);

	t_bgVtxBuffPolygon->Unlock();
}
//-------------------------------------
//タイトル背景終了処理
//-------------------------------------
void UninitTittleBG(void)
{
	//バッファの処理
	
	if(t_bgVtxBuffPolygon != NULL)
	{
		t_bgVtxBuffPolygon->Release();
		t_bgVtxBuffPolygon = NULL;
	}
	
		//テクスチャの処理
	if(t_bgTexturePolygon != NULL)
	{
		t_bgTexturePolygon->Release();
		t_bgTexturePolygon = NULL;
	}
}
//-------------------------------------
//タイトル背景の更新処理
//-------------------------------------
void UpdateTittleBG(void)
{

}
//-------------------------------------
//タイトル背景の描画処理
//-------------------------------------
void DrawTittleBG(void)
{
	//背景の描画
	GetDevice()->SetStreamSource(0,t_bgVtxBuffPolygon,0,sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	GetDevice()->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	GetDevice()->SetTexture(0,t_bgTexturePolygon);
	//ポリゴンの描画
	GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	
}