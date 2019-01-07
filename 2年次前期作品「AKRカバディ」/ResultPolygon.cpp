//◇-------------------------------------------------------------------------◇
//
//	リザルトポリゴンcppファイル[polygon.cpp]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include"main.h"
#include"ResultPolygon.h"
#include"input.h"
//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 r_pTexturePolygon = NULL;
LPDIRECT3DVERTEXBUFFER9 r_pVtxBuffPolygon = NULL;
VERTEX_2D *r_pVtx;			//画像の座標のポインタ

//◇-------------------------------------------------------------------------◇
//リザルトポリゴンの初期化処理
//◇-------------------------------------------------------------------------◇
void InitResultPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*TYOUTEN_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&r_pVtxBuffPolygon,NULL);

	//ゲームオーバーの情報登録・ロック
	r_pVtxBuffPolygon->Lock(0,0,(void**)&r_pVtx,0);
/*
	//頂点情報の設定
	r_pVtx[0].pos = D3DXVECTOR3(450.0f,350.0f,0.0f);
	r_pVtx[1].pos = D3DXVECTOR3(850.0f,350.0f,0.0f);
	r_pVtx[2].pos = D3DXVECTOR3(450.0f,500.0f,0.0f);
	r_pVtx[3].pos = D3DXVECTOR3(850.0f,500.0f,0.0f);

	r_pVtx[0].rhw = 1.0f;
	r_pVtx[1].rhw = 1.0f;
	r_pVtx[2].rhw = 1.0f;
	r_pVtx[3].rhw = 1.0f;

	r_pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	r_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	r_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	r_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	r_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);
*/			
//	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/result_logo.png",&r_pTexturePolygon);
	
	//ロックの解除
	r_pVtxBuffPolygon->Unlock();
}
//-------------------------------------
//リザルトポリゴン終了処理
//-------------------------------------
void UninitResultPolygon(void)
{
	//バッファの処理
	if(r_pVtxBuffPolygon != NULL)
	{
		r_pVtxBuffPolygon->Release();
		r_pVtxBuffPolygon = NULL;
	}

		//テクスチャの処理
	if(r_pTexturePolygon != NULL)
	{
		r_pTexturePolygon->Release();
		r_pTexturePolygon = NULL;
	}
}
//-------------------------------------
//リザルトポリゴンの更新処理
//-------------------------------------
void UpdateResultPolygon(void)
{
}
//-------------------------------------
//リザルトポリゴンの描画処理
//-------------------------------------
void DrawResultPolygon(void)
{
	//ランニングマンの描画
	GetDevice()->SetStreamSource(0,r_pVtxBuffPolygon,0,sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	GetDevice()->SetFVF(FVF_VERTEX_2D);	
	//テクスチャの設定
	GetDevice()->SetTexture(0,r_pTexturePolygon);
	//ポリゴンの描画
	GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,RESULT_POLYGON_NUM);	//真ん中の0は開始する頂点インデックス
}