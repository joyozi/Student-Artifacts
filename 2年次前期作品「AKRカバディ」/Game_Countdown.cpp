//◇-------------------------------------------------------------------------◇
//
//	ゲームカウントダウンcppファイル[game_countdown.cpp]
//	AT12A271　当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "Game_Countdown.h"
#include "fade.h"
//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
PDIRECT3DTEXTURE9 c_pTextureScore = NULL;
LPDIRECT3DVERTEXBUFFER9 c_pVtxBuffScore[MAX_CNTDOWN_KETA] = {NULL,NULL,NULL};
VERTEX_2D *cVtx;			//画像の座標のポインタ
int g_nTime;				//点数
//◇-------------------------------------------------------------------------◇
//初期化処理
//◇-------------------------------------------------------------------------◇
void InitCountdown(void)
{
	LPDIRECT3DDEVICE9 cDevice;
	cDevice = GetDevice();
	int CountdownIreko[MAX_CNTDOWN_KETA];			//0から順に最上桁目を入れる
	int keta = 0;									//マイナスする桁を入れる変数
	int ketaCnt = 0;								//スコアの計算に使う変数。桁がマイナスされていく

	//スコアの初期化
	g_nTime = COUNTDOWN_TIME;

	//====================================
	//カウントダウンの一番最初の表示の計算
	//====================================
	//CountIrekoに0を代入
	for(int nCnt = 0;nCnt < MAX_CNTDOWN_KETA;nCnt++)
	{
		CountdownIreko[nCnt] = 0;
	}

	//桁ごとの代入
	ketaCnt = g_nTime;

	for(int CountdownCnt = 0;CountdownCnt < MAX_CNTDOWN_KETA;CountdownCnt++)
	{
		keta = powf(10, MAX_CNTDOWN_KETA - CountdownCnt - 1);
			
		while(ketaCnt >= keta)
		{
			CountdownIreko[MAX_CNTDOWN_KETA - CountdownCnt-1]++;
			ketaCnt -= keta;
		}
	}

	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/number000.png",&c_pTextureScore);

	for(int CountdownCnt = 0; CountdownCnt < MAX_CNTDOWN_KETA;CountdownCnt++)
	{
		cDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*TYOUTEN_CNTDOWN_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&c_pVtxBuffScore[CountdownCnt],NULL);

		//スコアの情報登録・ロック
		c_pVtxBuffScore[CountdownCnt]->Lock(0,0,(void**)&cVtx,0);

		//頂点情報の設定
		cVtx[0 + CountdownCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawCountdownPosWidth * (CountdownCnt + 1)),DrawCountdownPosHeight,0.0f);
		cVtx[1 + CountdownCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawCountdownPosWidth * CountdownCnt),DrawCountdownPosHeight,0.0f);
		cVtx[2 + CountdownCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawCountdownPosWidth * (CountdownCnt + 1)),DrawCountdownHeightW+DrawCountdownPosHeight,0.0f);
		cVtx[3 + CountdownCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawCountdownPosWidth * CountdownCnt),DrawCountdownHeightW + DrawCountdownPosHeight,0.0f);

		cVtx[0 + CountdownCnt * 4].rhw = 1.0f;
		cVtx[1 + CountdownCnt * 4].rhw = 1.0f;
		cVtx[2 + CountdownCnt * 4].rhw = 1.0f;
		cVtx[3 + CountdownCnt * 4].rhw = 1.0f;

		cVtx[0 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
		cVtx[1 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
		cVtx[2 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
		cVtx[3 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);

		cVtx[0 + CountdownCnt * 4].tex = D3DXVECTOR2(CountdownIreko[CountdownCnt] * 0.1,0.0);
		cVtx[1 + CountdownCnt * 4].tex = D3DXVECTOR2((CountdownIreko[CountdownCnt] * 0.1 + 0.1),0.0);
		cVtx[2 + CountdownCnt * 4].tex = D3DXVECTOR2(CountdownIreko[CountdownCnt] * 0.1,1.0);
		cVtx[3 + CountdownCnt * 4].tex = D3DXVECTOR2((CountdownIreko[CountdownCnt] * 0.1 + 0.1),1.0);
	
		//ロックの解除
		c_pVtxBuffScore[CountdownCnt]->Unlock();
	}
}

//◇---------------------------------◇
//終了処理
//◇---------------------------------◇
void UninitCountdown(void)
{
	for(int CountdownCnt = 0; CountdownCnt < MAX_CNTDOWN_KETA;CountdownCnt++)
	{
		//バッファの処理
		if(c_pVtxBuffScore[CountdownCnt] != NULL)
		{
			c_pVtxBuffScore[CountdownCnt]->Release();
			c_pVtxBuffScore[CountdownCnt] = NULL;
		}
	}
	if(c_pTextureScore != NULL)
	{
		c_pTextureScore->Release();
		c_pTextureScore = NULL;
	}
}
//◇---------------------------------◇
//の更新処理
//◇---------------------------------◇
void UpdateCountdown(void)
{
	int CountdownIreko[MAX_CNTDOWN_KETA];			//0から順に最上桁目を入れる
	int keta = 0;									//マイナスする桁を入れる変数
	int ketaCnt = 0;								//スコアの計算に使う変数。桁がマイナスされていく
	static int timeCnt;

	//60秒ごとにゼロになる。1秒を計測してもらう
	timeCnt++;

	//CountIrekoに0を代入
	for(int nCnt = 0;nCnt < MAX_CNTDOWN_KETA;nCnt++)
	{
		CountdownIreko[nCnt] = 0;
	}

	//秒読み 一秒たったら桁の代入とかをする
	if(timeCnt > 60)
	{
		g_nTime--;
		timeCnt = 0;
	}

	if(g_nTime <= 0)
	{
		SetFade(FADE_OUT);
	}

	//得点の桁ごとの代入
	ketaCnt = g_nTime;

	for(int CountdownCnt = 0;CountdownCnt < MAX_CNTDOWN_KETA;CountdownCnt++)
	{
		keta = powf(10, MAX_CNTDOWN_KETA - CountdownCnt - 1);
			
		while(ketaCnt >= keta)
		{
			CountdownIreko[MAX_CNTDOWN_KETA - CountdownCnt-1]++;
			ketaCnt -= keta;
		}
	}

	//表示する座標と文字の計算、設定 +色
	for(int CountdownCnt = 0; CountdownCnt < MAX_CNTDOWN_KETA;CountdownCnt++)
	{
		//スコアの情報登録・ロック
		c_pVtxBuffScore[CountdownCnt]->Lock(0,0,(void**)&cVtx,0);

		//頂点情報の設定
		cVtx[0 + CountdownCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawCountdownPosWidth * (CountdownCnt + 1)),DrawCountdownPosHeight,0.0f);
		cVtx[1 + CountdownCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawCountdownPosWidth * CountdownCnt),DrawCountdownPosHeight,0.0f);
		cVtx[2 + CountdownCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawCountdownPosWidth * (CountdownCnt + 1)),DrawCountdownHeightW+DrawCountdownPosHeight,0.0f);
		cVtx[3 + CountdownCnt * 4].pos = D3DXVECTOR3(SCREEN_WIDTH - (DrawCountdownPosWidth * CountdownCnt),DrawCountdownHeightW + DrawCountdownPosHeight,0.0f);

		cVtx[0 + CountdownCnt * 4].tex = D3DXVECTOR2(CountdownIreko[CountdownCnt] * 0.1f,0.0f);
		cVtx[1 + CountdownCnt * 4].tex = D3DXVECTOR2((CountdownIreko[CountdownCnt] * 0.1f + 0.1f),0.0f);
		cVtx[2 + CountdownCnt * 4].tex = D3DXVECTOR2(CountdownIreko[CountdownCnt] * 0.1f,1.0f);
		cVtx[3 + CountdownCnt * 4].tex = D3DXVECTOR2((CountdownIreko[CountdownCnt] * 0.1f + 0.1f),1.0f);

		//得点ごとの色の設定
		if(g_nTime > CountdownChangeColor)
		{
			cVtx[0 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
			cVtx[1 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
			cVtx[2 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
			cVtx[3 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,255,255,255);
		}
		else
		{
			cVtx[0 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,0,0,255);
			cVtx[1 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,0,0,255);
			cVtx[2 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,0,0,255);
			cVtx[3 + CountdownCnt * 4].col = D3DCOLOR_RGBA(255,0,0,255);
		}
		//ロックの解除
		c_pVtxBuffScore[CountdownCnt]->Unlock();
		
	}

}

//◇---------------------------------◇
//の描画処理
//◇---------------------------------◇
void DrawCountdown(void)
{
		for(int CountdownCnt = 0; CountdownCnt < MAX_CNTDOWN_KETA;CountdownCnt++)
	{
		//スコアの描画
		GetDevice()->SetStreamSource(0,c_pVtxBuffScore[CountdownCnt],0,sizeof(VERTEX_2D));
		//頂点フォーマットの設定
		GetDevice()->SetFVF(FVF_VERTEX_2D);	
		//テクスチャの設定
		GetDevice()->SetTexture(0,c_pTextureScore);
		//ポリゴンの描画
		GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,POLYGON_CNTDOWN_NUM);	//真ん中の0は開始する頂点インデックス
	}
}