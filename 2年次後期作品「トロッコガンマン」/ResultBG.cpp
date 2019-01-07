//◇-------------------------------------------------------------------------◇
//
//	リザルト背景cppファイル[ResultBG.cpp]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include"main.h"
#include"ResultBG.h"
//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 r_bgTexturePolygon = NULL;
LPDIRECT3DVERTEXBUFFER9 r_bgVtxBuffPolygon = NULL;
VERTEX_2D *r_pVtxBG;		//画像の座標のポインタ

//◇-------------------------------------------------------------------------◇
//リザルト背景の初期化処理
//◇-------------------------------------------------------------------------◇
void InitResultBG(bool Judge)
{
	LPDIRECT3DDEVICE9 bgDevice;
	bgDevice = GetDevice();
	bgDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&r_bgVtxBuffPolygon,NULL);

	//背景画像の情報登録
	r_bgVtxBuffPolygon->Lock(0,0,(void**)&r_pVtxBG,0);

	//頂点情報の設定
	r_pVtxBG[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	r_pVtxBG[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
	r_pVtxBG[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
	r_pVtxBG[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);

	r_pVtxBG[0].rhw = 1.0f;
	r_pVtxBG[1].rhw = 1.0f;
	r_pVtxBG[2].rhw = 1.0f;
	r_pVtxBG[3].rhw = 1.0f;

	r_pVtxBG[0].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtxBG[1].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtxBG[2].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtxBG[3].col = D3DCOLOR_RGBA(255,255,255,255);

	r_pVtxBG[0].tex = D3DXVECTOR2(0.0,0.0);
	r_pVtxBG[1].tex = D3DXVECTOR2(1.0,0.0);
	r_pVtxBG[2].tex = D3DXVECTOR2(0.0,1.0);
	r_pVtxBG[3].tex = D3DXVECTOR2(1.0,1.0);
	
	if(Judge)
	{
		D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/result_takara.jpg",&r_bgTexturePolygon);
	}
	else
	{
		D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/GameOver00.jpg",&r_bgTexturePolygon);
	}

	r_bgVtxBuffPolygon->Unlock();
}
//-------------------------------------
//リザルト背景終了処理
//-------------------------------------
void UninitResultBG(void)
{
	//バッファの処理
	
	if(r_bgVtxBuffPolygon != NULL)
	{
		r_bgVtxBuffPolygon->Release();
		r_bgVtxBuffPolygon = NULL;
	}
	
		//テクスチャの処理
	if(r_bgTexturePolygon != NULL)
	{
		r_bgTexturePolygon->Release();
		r_bgTexturePolygon = NULL;
	}
}
//-------------------------------------
//リザルト背景の更新処理
//-------------------------------------
void UpdateResultBG(void)
{

}
//-------------------------------------
//リザルト背景の描画処理
//-------------------------------------
void DrawResultBG(void)
{
	//背景の描画
	GetDevice()->SetStreamSource(0,r_bgVtxBuffPolygon,0,sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	GetDevice()->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	GetDevice()->SetTexture(0,r_bgTexturePolygon);
	GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	
}