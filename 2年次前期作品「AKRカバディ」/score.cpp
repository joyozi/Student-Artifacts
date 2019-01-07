//◇-------------------------------------------------------------------------◇
//
//	スコアcppファイル[score.cpp]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include"main.h"
#include"input.h"
#include"score.h"
#include "fade.h"
#include <math.h>
//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 g_pTextureScore;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore[MAX_SCORE_KETA];
VERTEX_2D *sVtx;			//画像の座標のポインタ
int g_nScore;				//点数
//◇-------------------------------------------------------------------------◇
//スコアの初期化処理
//◇-------------------------------------------------------------------------◇
void InitScore(void)
{
	LPDIRECT3DDEVICE9 sDevice;
	sDevice = GetDevice();
	
	//スコアの初期化
	g_nScore = 0;

	g_pTextureScore = NULL;
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/number000.png",&g_pTextureScore);

	for(int ScoreCnt = 0; ScoreCnt < MAX_SCORE_KETA;ScoreCnt++)
	{
		g_pVtxBuffScore[ScoreCnt] = NULL;

		sDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*TYOUTEN_sNUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffScore[ScoreCnt],NULL);

		//スコアの情報登録・ロック
		g_pVtxBuffScore[ScoreCnt]->Lock(0,0,(void**)&sVtx,0);

		//頂点情報の設定
		sVtx[0 + ScoreCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawScorePosWidth * (float)((ScoreCnt + 1))),0.0f,0.0f);
		sVtx[1 + ScoreCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawScorePosWidth * (float)(ScoreCnt)),0.0f,0.0f);
		sVtx[2 + ScoreCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawScorePosWidth * (float)((ScoreCnt + 1))),DrawScorePosHeight,0.0f);
		sVtx[3 + ScoreCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawScorePosWidth * (float)(ScoreCnt)),DrawScorePosHeight,0.0f);

		sVtx[0 + ScoreCnt * 4].rhw = 1.0f;
		sVtx[1 + ScoreCnt * 4].rhw = 1.0f;
		sVtx[2 + ScoreCnt * 4].rhw = 1.0f;
		sVtx[3 + ScoreCnt * 4].rhw = 1.0f;

		sVtx[0 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
		sVtx[1 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
		sVtx[2 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
		sVtx[3 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);

		sVtx[0 + ScoreCnt * 4].tex = D3DXVECTOR2(0.0f,0.0f);
		sVtx[1 + ScoreCnt * 4].tex = D3DXVECTOR2((1.0f / 10.0f),0.0f);
		sVtx[2 + ScoreCnt * 4].tex = D3DXVECTOR2(0.0f,1.0f);
		sVtx[3 + ScoreCnt * 4].tex = D3DXVECTOR2((1.0f / 10.0f),1.0f);
	
		//ロックの解除
		g_pVtxBuffScore[ScoreCnt]->Unlock();
	}
}

//◇---------------------------------◇
//スコアの終了処理
//◇---------------------------------◇
void UninitScore(void)
{
	for(int ScoreCnt = 0; ScoreCnt < MAX_SCORE_KETA;ScoreCnt++)
	{
		//バッファの処理
		if(g_pVtxBuffScore[ScoreCnt] != NULL)
		{
			g_pVtxBuffScore[ScoreCnt]->Release();
			g_pVtxBuffScore[ScoreCnt] = NULL;
		}
	}
	//バッファの処理
	if(g_pTextureScore != NULL)
	{
		//テクスチャの処理
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
}
//◇---------------------------------◇
//スコアの更新処理
//◇---------------------------------◇
void UpdateScore(void)
{
	int ScoreIreko[MAX_SCORE_KETA] = {0,0,0};	//0から順に最上桁目を入れる
	int keta;										//マイナスする桁を入れる変数
	int ketaCnt = 0;								//スコアの計算に使う変数。桁がマイナスされていく

	//得点の桁ごとの代入
	ketaCnt = g_nScore;

	for(int ScoreCnt = 0;ScoreCnt < MAX_SCORE_KETA;ScoreCnt++)
	{
		keta = powf(10,MAX_SCORE_KETA - ScoreCnt - 1);
			
		while(ketaCnt >= keta)
		{
			ScoreIreko[ MAX_SCORE_KETA - ScoreCnt-1]++;
			ketaCnt -= keta;
		}
	}



		switch(GetMode())
		{
		case MODE_GAME:
		//表示する座標と文字の計算、設定 +色
		for(int ScoreCnt = 0; ScoreCnt < MAX_SCORE_KETA;ScoreCnt++)
		{

			//スコアの情報登録・ロック
			g_pVtxBuffScore[ScoreCnt]->Lock(0,0,(void**)&sVtx,0);

			//頂点情報の設定
			sVtx[0 + ScoreCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawScorePosWidth * (ScoreCnt + 1)),0.0f,0.0f);
			sVtx[1 + ScoreCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawScorePosWidth * ScoreCnt),0.0f,0.0f);
			sVtx[2 + ScoreCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawScorePosWidth * (ScoreCnt + 1)),DrawScorePosHeight,0.0f);
			sVtx[3 + ScoreCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawScorePosWidth * ScoreCnt),DrawScorePosHeight,0.0f);

			sVtx[0 + ScoreCnt * 4].tex = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1f,0.0f);
			sVtx[1 + ScoreCnt * 4].tex = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1f + 0.1f,0.0f);
			sVtx[2 + ScoreCnt * 4].tex = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1f,1.0f);
			sVtx[3 + ScoreCnt * 4].tex = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1f + 0.1f,1.0f);
	
			//得点ごとの色の設定
			if(g_nScore < ScoreChangeColor)
			{
				sVtx[0 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
				sVtx[1 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
				sVtx[2 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
				sVtx[3 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
			}
			else
			{
				sVtx[0 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,0,0,255);
				sVtx[1 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,0,0,255);
				sVtx[2 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,0,0,255);
				sVtx[3 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,0,0,255);
			}

			//ロックの解除
			g_pVtxBuffScore[ScoreCnt]->Unlock();
		}

		break;

		case MODE_RESULT:
			for(int ScoreCnt = 0; ScoreCnt < MAX_SCORE_KETA;ScoreCnt++)
		{

			//スコアの情報登録・ロック
			g_pVtxBuffScore[ScoreCnt]->Lock(0,0,(void**)&sVtx,0);

			//頂点情報の設定
			sVtx[0 + ScoreCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (DrawScorePosWidth * (ScoreCnt + 1)),150,0.0f);
			sVtx[1 + ScoreCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (DrawScorePosWidth * ScoreCnt),150,0.0f);
			sVtx[2 + ScoreCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH / 2  - (DrawScorePosWidth * (ScoreCnt + 1)),150 + DrawScorePosHeight,0.0f);
			sVtx[3 + ScoreCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (DrawScorePosWidth * ScoreCnt),150 + DrawScorePosHeight,0.0f);

			sVtx[0 + ScoreCnt * 4].tex = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1f,0.0f);
			sVtx[1 + ScoreCnt * 4].tex = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1f + 0.1f,0.0f);
			sVtx[2 + ScoreCnt * 4].tex = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1f,1.0f);
			sVtx[3 + ScoreCnt * 4].tex = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1f + 0.1f,1.0f);
	
			//得点ごとの色の設定
			if(g_nScore < ScoreChangeColor)
			{
				sVtx[0 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
				sVtx[1 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
				sVtx[2 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
				sVtx[3 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
			}
			else
			{
				sVtx[0 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,0,0,255);
				sVtx[1 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,0,0,255);
				sVtx[2 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,0,0,255);
				sVtx[3 + ScoreCnt * 4].col = D3DCOLOR_RGBA(255,0,0,255);
			}

			//ロックの解除
			g_pVtxBuffScore[ScoreCnt]->Unlock();
		}
			break;

		}
}
//◇---------------------------------◇
//スコアの描画処理
//◇---------------------------------◇
void DrawScore(void)
{
	for(int ScoreCnt = 0; ScoreCnt < MAX_SCORE_KETA;ScoreCnt++)
	{
		//スコアの描画
		GetDevice()->SetStreamSource(0,g_pVtxBuffScore[ScoreCnt],0,sizeof(VERTEX_2D));
		//頂点フォーマットの設定
		GetDevice()->SetFVF(FVF_VERTEX_2D);	
		//テクスチャの設定
		GetDevice()->SetTexture(0,g_pTextureScore);
		//ポリゴンの描画
		GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,POLYGON_sNUM);	//真ん中の0は開始する頂点インデックス
	}
}

void GetScore(void)
{
	g_nScore++;
}