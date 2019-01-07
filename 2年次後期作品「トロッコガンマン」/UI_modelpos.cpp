//◇-------------------------------------------------------------------------◇
//
//	ＵＩのモデルの位置情報をしめす画像表示cppファイル[UI_modelpos.cpp]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include"main.h"
#include"UI_modelpos.h"
#include"model.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇
#define UI_MODELPOS_TEXTURE_NUM	(2)	//ここのテクスチャの数

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 p_gTextureUI_modelpos[UI_MODELPOS_TEXTURE_NUM];
LPDIRECT3DVERTEXBUFFER9 p_gVtxBuffUI_modelpos[UI_MODELPOS_TEXTURE_NUM];

VERTEX_2D *r_pVtxUI_modelpos;		//画像の座標のポインタ

//◇-------------------------------------------------------------------------◇
//UI_modelposの初期化処理
//◇-------------------------------------------------------------------------◇
void InitUI_modelpos(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	

	for(int nCnt = 0;nCnt < UI_MODELPOS_TEXTURE_NUM;nCnt++)
	{
		p_gTextureUI_modelpos[nCnt] = NULL;
		p_gVtxBuffUI_modelpos[nCnt] = NULL;
	}

	//--------トロッコの画像の設定------------------------------------------
	D3DXCreateTextureFromFile(pDevice,"./data/TEXTURE/model_icon.png",&p_gTextureUI_modelpos[0]);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&p_gVtxBuffUI_modelpos[0],NULL);

	//背景画像の情報登録
	p_gVtxBuffUI_modelpos[0]->Lock(0,0,(void**)&r_pVtxUI_modelpos,0);

	//頂点情報の設定
	r_pVtxUI_modelpos[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 90.0f,0.0f,0.0f);
	r_pVtxUI_modelpos[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 20.0f,0.0f,0.0f);
	r_pVtxUI_modelpos[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 90.0f,0.0f,0.0f);
	r_pVtxUI_modelpos[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 20.0f,0.0f,0.0f);

	r_pVtxUI_modelpos[0].rhw = 1.0f;
	r_pVtxUI_modelpos[1].rhw = 1.0f;
	r_pVtxUI_modelpos[2].rhw = 1.0f;
	r_pVtxUI_modelpos[3].rhw = 1.0f;

	r_pVtxUI_modelpos[0].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtxUI_modelpos[1].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtxUI_modelpos[2].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtxUI_modelpos[3].col = D3DCOLOR_RGBA(255,255,255,255);

	r_pVtxUI_modelpos[0].tex = D3DXVECTOR2(0.0,0.0);
	r_pVtxUI_modelpos[1].tex = D3DXVECTOR2(1.0,0.0);
	r_pVtxUI_modelpos[2].tex = D3DXVECTOR2(0.0,1.0);
	r_pVtxUI_modelpos[3].tex = D3DXVECTOR2(1.0,1.0);

	p_gVtxBuffUI_modelpos[0]->Unlock();
	//-----------------------------------------------------

	//--------レールの画像の設定------------------------------------------
	D3DXCreateTextureFromFile(pDevice,"./data/TEXTURE/railmap.png",&p_gTextureUI_modelpos[1]);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&p_gVtxBuffUI_modelpos[1],NULL);

	//背景画像の情報登録
	p_gVtxBuffUI_modelpos[1]->Lock(0,0,(void**)&r_pVtxUI_modelpos,0);

	//頂点情報の設定
	r_pVtxUI_modelpos[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 100.0f,80.0f,0.0f);
	r_pVtxUI_modelpos[1].pos = D3DXVECTOR3(SCREEN_WIDTH,80.0f,0.0f);
	r_pVtxUI_modelpos[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 100.0f,730.0f,0.0f);
	r_pVtxUI_modelpos[3].pos = D3DXVECTOR3(SCREEN_WIDTH,730.0f,0.0f);

	r_pVtxUI_modelpos[0].rhw = 1.0f;
	r_pVtxUI_modelpos[1].rhw = 1.0f;
	r_pVtxUI_modelpos[2].rhw = 1.0f;
	r_pVtxUI_modelpos[3].rhw = 1.0f;

	r_pVtxUI_modelpos[0].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtxUI_modelpos[1].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtxUI_modelpos[2].col = D3DCOLOR_RGBA(255,255,255,255);
	r_pVtxUI_modelpos[3].col = D3DCOLOR_RGBA(255,255,255,255);

	r_pVtxUI_modelpos[0].tex = D3DXVECTOR2(0.0,0.0);
	r_pVtxUI_modelpos[1].tex = D3DXVECTOR2(1.0,0.0);
	r_pVtxUI_modelpos[2].tex = D3DXVECTOR2(0.0,1.0);
	r_pVtxUI_modelpos[3].tex = D3DXVECTOR2(1.0,1.0);

	p_gVtxBuffUI_modelpos[1]->Unlock();
	//-----------------------------------------------------
}
//-------------------------------------
//UI終了処理
//-------------------------------------
void UninitUI_modelpos(void)
{
	for(int nCnt = 0;nCnt < UI_MODELPOS_TEXTURE_NUM;nCnt++)
	{
		//バッファの処理
		if(p_gVtxBuffUI_modelpos[nCnt] != NULL)
		{
			p_gVtxBuffUI_modelpos[nCnt]->Release();
			p_gVtxBuffUI_modelpos[nCnt] = NULL;
		}
	
		//テクスチャの処理
		if(p_gTextureUI_modelpos[nCnt] != NULL)
		{
			p_gTextureUI_modelpos[nCnt] -> Release();
			p_gTextureUI_modelpos[nCnt] = NULL;
		}	
	}
}
//-------------------------------------
//UIの更新処理
//-------------------------------------
void UpdateUI_modelpos(void)
{
	static float tex_pos;

	tex_pos = ((Getg_posModel().z / MODEL_GOAL) * 610.0f);
	
	//ダメージを受けたら赤く点滅とかいいかもしれない byとしやま


	//背景画像の情報登録
	p_gVtxBuffUI_modelpos[0]->Lock(0,0,(void**)&r_pVtxUI_modelpos,0);

	r_pVtxUI_modelpos[0].pos.y = 730.0f - (tex_pos+70.0f);
	r_pVtxUI_modelpos[1].pos.y = 730.0f - (tex_pos+70.0f);
	r_pVtxUI_modelpos[2].pos.y = 730.0f - (tex_pos);
	r_pVtxUI_modelpos[3].pos.y = 730.0f - (tex_pos);

	p_gVtxBuffUI_modelpos[0]->Unlock();

}
//-------------------------------------
//UIの描画処理
//-------------------------------------
void DrawUI_modelpos(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//!!!!!!!!!!テクスチャの表示の順番を反対にするため作業を強制的に行う!!!!!!!!!!!!!!!!!
	for(int nCnt = UI_MODELPOS_TEXTURE_NUM - 1;nCnt >= 0;nCnt--)
	{
		//背景の描画
		pDevice->SetStreamSource(0,p_gVtxBuffUI_modelpos[nCnt],0,sizeof(VERTEX_2D));
		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		//テクスチャの設定
		pDevice->SetTexture(0,p_gTextureUI_modelpos[nCnt]);
		//テクスチャの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	}
}