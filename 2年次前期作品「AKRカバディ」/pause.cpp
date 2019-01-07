//◇-------------------------------------------------------------------------◇
//
//	pauseファイル[pause.cpp]
//	AT12A271　当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "pause.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include"score.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 p_pTexturePolygon[PAUSE_TEXTURE_NUM];
LPDIRECT3DVERTEXBUFFER9 p_pVtxBuffPolygon[PAUSE_TEXTURE_NUM];
int p_nCounterAnim = 0;
int p_nPatternAnim = 0;
int p_nPatternAnimTATE = 0;
VERTEX_2D *p_pVtx;				//画像の座標のポインタ
D3DXVECTOR3 p_posPolygon;		//中心の座標

PAUSE_MENU g_selectMenu = PAUSE_MENU_CONTINUE;

//◇-------------------------------------------------------------------------◇
//ポーズ初期化処理
//◇-------------------------------------------------------------------------◇
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	g_selectMenu = PAUSE_MENU_CONTINUE;

	for(int Cnt = 0;Cnt < PAUSE_TEXTURE_NUM;Cnt++)
	{
		p_pVtxBuffPolygon[Cnt] = NULL;
		p_pTexturePolygon[Cnt] = NULL;

		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*PAUSE_TYOUTEN_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&p_pVtxBuffPolygon[Cnt],NULL);
	}

	//ポーズの情報登録・ロック
	p_pVtxBuffPolygon[0]->Lock(0,0,(void**)&p_pVtx,0);

	//頂点情報の設定
	p_pVtx[0].pos = D3DXVECTOR3(0,0,0.0f);
	p_pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0,0.0f);
	p_pVtx[2].pos = D3DXVECTOR3(0,SCREEN_WIDTH,0.0f);
	p_pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_WIDTH,0.0f);

	p_pVtx[0].rhw = 1.0f;
	p_pVtx[1].rhw = 1.0f;
	p_pVtx[2].rhw = 1.0f;
	p_pVtx[3].rhw = 1.0f;

	p_pVtx[0].col = D3DCOLOR_RGBA(255,255,255,100);
	p_pVtx[1].col = D3DCOLOR_RGBA(255,255,255,100);
	p_pVtx[2].col = D3DCOLOR_RGBA(255,255,255,100);
	p_pVtx[3].col = D3DCOLOR_RGBA(255,255,255,100);

	p_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	p_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	p_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	p_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);

	//ロックの解除
	p_pVtxBuffPolygon[0]->Unlock();
	
	//選択肢の情報登録・ロック
	p_pVtxBuffPolygon[1]->Lock(0,0,(void**)&p_pVtx,0);

	//頂点情報の設定
	p_pVtx[0].pos = D3DXVECTOR3(250,350,0.0f);
	p_pVtx[1].pos = D3DXVECTOR3(500,350,0.0f);
	p_pVtx[2].pos = D3DXVECTOR3(250,450,0.0f);
	p_pVtx[3].pos = D3DXVECTOR3(500,450,0.0f);

	p_pVtx[0].rhw = 1.0f;
	p_pVtx[1].rhw = 1.0f;
	p_pVtx[2].rhw = 1.0f;
	p_pVtx[3].rhw = 1.0f;

	p_pVtx[0].col = D3DCOLOR_RGBA(255,255,0,100);
	p_pVtx[1].col = D3DCOLOR_RGBA(255,255,0,100);
	p_pVtx[2].col = D3DCOLOR_RGBA(255,255,0,100);
	p_pVtx[3].col = D3DCOLOR_RGBA(255,255,0,100);

	p_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	p_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	p_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	p_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);

//	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/explosion.png",&p_pTexturePolygon[1]);

	//ロックの解除
	p_pVtxBuffPolygon[1]->Unlock();

	//ポーズの情報登録・ロック
	p_pVtxBuffPolygon[2]->Lock(0,0,(void**)&p_pVtx,0);

	//頂点情報の設定
	p_pVtx[0].pos = D3DXVECTOR3(150,150,0.0f);
	p_pVtx[1].pos = D3DXVECTOR3(600,150,0.0f);
	p_pVtx[2].pos = D3DXVECTOR3(150,350,0.0f);
	p_pVtx[3].pos = D3DXVECTOR3(600,350,0.0f);

	p_pVtx[0].rhw = 1.0f;
	p_pVtx[1].rhw = 1.0f;
	p_pVtx[2].rhw = 1.0f;
	p_pVtx[3].rhw = 1.0f;

	p_pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	p_pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	p_pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	p_pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	p_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	p_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	p_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	p_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);

	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/PAUSE.png",&p_pTexturePolygon[2]);

	//ロックの解除
	p_pVtxBuffPolygon[2]->Unlock();

	//CONTINUEの情報登録・ロック
	p_pVtxBuffPolygon[3]->Lock(0,0,(void**)&p_pVtx,0);

	//頂点情報の設定
	p_pVtx[0].pos = D3DXVECTOR3(250,350,0.0f);
	p_pVtx[1].pos = D3DXVECTOR3(500,350,0.0f);
	p_pVtx[2].pos = D3DXVECTOR3(250,450,0.0f);
	p_pVtx[3].pos = D3DXVECTOR3(500,450,0.0f);

	p_pVtx[0].rhw = 1.0f;
	p_pVtx[1].rhw = 1.0f;
	p_pVtx[2].rhw = 1.0f;
	p_pVtx[3].rhw = 1.0f;

	p_pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	p_pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	p_pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	p_pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	p_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	p_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	p_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	p_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);

	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/CONTINUE.png",&p_pTexturePolygon[3]);
		//ロックの解除
	p_pVtxBuffPolygon[3]->Unlock();

	//RETRYの情報登録・ロック
	p_pVtxBuffPolygon[4]->Lock(0,0,(void**)&p_pVtx,0);

	//頂点情報の設定
	p_pVtx[0].pos = D3DXVECTOR3(250,450,0.0f);
	p_pVtx[1].pos = D3DXVECTOR3(500,450,0.0f);
	p_pVtx[2].pos = D3DXVECTOR3(250,550,0.0f);
	p_pVtx[3].pos = D3DXVECTOR3(500,550,0.0f);

	p_pVtx[0].rhw = 1.0f;
	p_pVtx[1].rhw = 1.0f;
	p_pVtx[2].rhw = 1.0f;
	p_pVtx[3].rhw = 1.0f;

	p_pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	p_pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	p_pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	p_pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	p_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	p_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	p_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	p_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);

	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/RETRY.png",&p_pTexturePolygon[4]);
		//ロックの解除
	p_pVtxBuffPolygon[4]->Unlock();

	//QUITの情報登録・ロック
	p_pVtxBuffPolygon[5]->Lock(0,0,(void**)&p_pVtx,0);

	//頂点情報の設定
	p_pVtx[0].pos = D3DXVECTOR3(250,550,0.0f);
	p_pVtx[1].pos = D3DXVECTOR3(500,550,0.0f);
	p_pVtx[2].pos = D3DXVECTOR3(250,650,0.0f);
	p_pVtx[3].pos = D3DXVECTOR3(500,650,0.0f);

	p_pVtx[0].rhw = 1.0f;
	p_pVtx[1].rhw = 1.0f;
	p_pVtx[2].rhw = 1.0f;
	p_pVtx[3].rhw = 1.0f;

	p_pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	p_pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	p_pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	p_pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	p_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	p_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	p_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	p_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);

	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/QUIT.png",&p_pTexturePolygon[5]);
	//ロックの解除
	p_pVtxBuffPolygon[5]->Unlock();

}

//◇---------------------------------◇
//ポーズ終了処理
//◇---------------------------------◇
void UninitPause(void)
{
	
	for(int Cnt = 0;Cnt < PAUSE_TEXTURE_NUM;Cnt++)
	{
		//バッファの処理
		if(p_pVtxBuffPolygon[Cnt] != NULL)
		{
			p_pVtxBuffPolygon[Cnt]->Release();
			p_pVtxBuffPolygon[Cnt] = NULL;
		}

		//テクスチャの処理
		if(p_pTexturePolygon[Cnt] != NULL)
		{
			p_pTexturePolygon[Cnt]->Release();
			p_pTexturePolygon[Cnt] = NULL;
		}
	}
}
//◇---------------------------------◇
//ポーズの更新処理
//◇---------------------------------◇
void UpdatePause(void)
{
	//RETRYのときに下を押すとQUIT　上を押すとCONTINUE
	if(g_selectMenu == PAUSE_MENU_RETRY)
	{
		if(GetKeyboardTrigger(DIK_S) == true)
		{
			g_selectMenu = PAUSE_MENU_QUIT;
		}
		if(GetKeyboardTrigger(DIK_W) == true)
		{
			g_selectMenu = PAUSE_MENU_CONTINUE;
		}
	}

	//CONTINUEのときに下を押すとRETRY
	else if(g_selectMenu == PAUSE_MENU_CONTINUE)
	{
		if(GetKeyboardTrigger(DIK_S) == true)
		{
			UninitScore();
			InitScore();
			
			g_selectMenu = PAUSE_MENU_RETRY;

		}
	}
	
	//QUITのときに上を押すとRETRY
	else if(g_selectMenu == PAUSE_MENU_QUIT)
	{
		if(GetKeyboardTrigger(DIK_W) == true)
		{
			g_selectMenu = PAUSE_MENU_RETRY;
		}
	}
	
	//決定する
	if(GetKeyboardTrigger(DIK_RETURN) == true)
	{
		switch(g_selectMenu)
		{
		case PAUSE_MENU_CONTINUE:
			SetEnablePause(false);
			break;

		case PAUSE_MENU_RETRY:
			SetFade_2(FADE_OUT,MODE_TITTLE);
			break;

		case PAUSE_MENU_QUIT:
			SetFade_2(FADE_OUT,MODE_RESULT);
			break;
		}
	}
	//選択肢の情報登録・ロック
	p_pVtxBuffPolygon[1]->Lock(0,0,(void**)&p_pVtx,0);

	//頂点情報の設定
	p_pVtx[0].pos = D3DXVECTOR3(250,350 + (g_selectMenu * 100),0.0f);
	p_pVtx[1].pos = D3DXVECTOR3(500,350 + (g_selectMenu * 100),0.0f);
	p_pVtx[2].pos = D3DXVECTOR3(250,450 + (g_selectMenu * 100),0.0f);
	p_pVtx[3].pos = D3DXVECTOR3(500,450 + (g_selectMenu * 100),0.0f);

	//ロックの解除
	p_pVtxBuffPolygon[1]->Unlock();
}

//◇---------------------------------◇
//ポーズの描画処理
//◇---------------------------------◇
void DrawPause(void)
{
	for(int Cnt = 0;Cnt < PAUSE_TEXTURE_NUM;Cnt++)
	{
		//ゲームポリゴンの描画
		GetDevice()->SetStreamSource(0,p_pVtxBuffPolygon[Cnt],0,sizeof(VERTEX_2D));
		//頂点フォーマットの設定
		GetDevice()->SetFVF(FVF_VERTEX_2D);
		//テクスチャの設定
		GetDevice()->SetTexture(0,p_pTexturePolygon[Cnt]);
		//ポリゴンの描画
		GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,PAUSE_POLYGON_NUM);	//真ん中の0は開始する頂点インデックス
	}
}

void ResetPauseMenu(void)
{

}