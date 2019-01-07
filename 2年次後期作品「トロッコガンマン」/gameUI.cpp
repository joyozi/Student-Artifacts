//◇-------------------------------------------------------------------------◇
//
//	ゲームのUIcppファイル[gameUI.cpp]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include"main.h"
#include"gameUI.h"
#include"input.h"
#include"fade.h"
#include"Result.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇
#define HITPOINT (5)	//体力の数

#define HP_WIDTH (60)	//体力表示の横の長さ
#define HP_HEIGHT (30)	//体力表示の縦の長さ

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 r_bgTextureGameUI;
LPDIRECT3DVERTEXBUFFER9 r_bgVtxBuffGameUI[HITPOINT];

int p_HitPointNum;

//◇-------------------------------------------------------------------------◇
//UIの初期化処理
//◇-------------------------------------------------------------------------◇
void InitGameUI(void)
{
	LPDIRECT3DDEVICE9 bgDevice;
	bgDevice = GetDevice();

	VERTEX_2D *r_pVtxBG;		//画像の座標のポインタ

	p_HitPointNum = HITPOINT;

	r_bgTextureGameUI = NULL;
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/heart.png",&r_bgTextureGameUI);

	for(int nCnt = 0;nCnt < HITPOINT;nCnt++)
	{	
		r_bgVtxBuffGameUI[nCnt] = NULL;

		bgDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4*HITPOINT,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&r_bgVtxBuffGameUI[nCnt],NULL);

		//背景画像の情報登録
		r_bgVtxBuffGameUI[nCnt]->Lock(0,0,(void**)&r_pVtxBG,0);

		//頂点情報の設定
		r_pVtxBG[0 + nCnt*4].pos = D3DXVECTOR3(0.0f + nCnt*HP_WIDTH	,0.0f,0.0f);
		r_pVtxBG[1 + nCnt*4].pos = D3DXVECTOR3(HP_WIDTH + nCnt*HP_WIDTH,0.0f,0.0f);
		r_pVtxBG[2 + nCnt*4].pos = D3DXVECTOR3(0.0f + nCnt*HP_WIDTH	,HP_WIDTH,0.0f);
		r_pVtxBG[3 + nCnt*4].pos = D3DXVECTOR3(HP_WIDTH + nCnt*HP_WIDTH,HP_WIDTH,0.0f);

		r_pVtxBG[0 + nCnt*4].rhw = 1.0f;
		r_pVtxBG[1 + nCnt*4].rhw = 1.0f;
		r_pVtxBG[2 + nCnt*4].rhw = 1.0f;
		r_pVtxBG[3 + nCnt*4].rhw = 1.0f;

		r_pVtxBG[0 + nCnt*4].col = D3DCOLOR_RGBA(255,255,255,255);
		r_pVtxBG[1 + nCnt*4].col = D3DCOLOR_RGBA(255,255,255,255);
		r_pVtxBG[2 + nCnt*4].col = D3DCOLOR_RGBA(255,255,255,255);
		r_pVtxBG[3 + nCnt*4].col = D3DCOLOR_RGBA(255,255,255,255);

		r_pVtxBG[0 + nCnt*4].tex = D3DXVECTOR2(0.0,0.0);
		r_pVtxBG[1 + nCnt*4].tex = D3DXVECTOR2(1.0,0.0);
		r_pVtxBG[2 + nCnt*4].tex = D3DXVECTOR2(0.0,1.0);
		r_pVtxBG[3 + nCnt*4].tex = D3DXVECTOR2(1.0,1.0);

		r_bgVtxBuffGameUI[nCnt]->Unlock();
	}
}
//-------------------------------------
//UI終了処理
//-------------------------------------
void UninitGameUI(void)
{
	for(int nCnt = 0;nCnt < HITPOINT;nCnt++)
	{
		//バッファの処理
		if(r_bgVtxBuffGameUI[nCnt] != NULL)
		{
			r_bgVtxBuffGameUI[nCnt]->Release();
			r_bgVtxBuffGameUI[nCnt] = NULL;
		}
	}
	//テクスチャの処理
	if(r_bgTextureGameUI != NULL)
	{
		r_bgTextureGameUI->Release();
		r_bgTextureGameUI= NULL;
	}	
}
//-------------------------------------
//UIの更新処理
//-------------------------------------
void UpdateGameUI(void)
{
	if(p_HitPointNum <= 0)
	{
		SetResultJudge(false);
		SetFade(FADE_OUT);
	}
}
//-------------------------------------
//UIの描画処理
//-------------------------------------
void DrawGameUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	for(int nCnt = 0;nCnt < p_HitPointNum;nCnt++)
	{
		//背景の描画
		pDevice->SetStreamSource(0,r_bgVtxBuffGameUI[nCnt],0,sizeof(VERTEX_2D));
		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		//テクスチャの設定
		pDevice->SetTexture(0,r_bgTextureGameUI);
		//テクスチャの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCnt * 4,2);
	}
}

//これを使うと体力が減る。障害物に当たった時などように
void HitPointCNT(void)
{
	p_HitPointNum--;
}