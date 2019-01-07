//◇-------------------------------------------------------------------------◇
//
//	タイトルポリゴンcppファイル[TittlePolygon.cpp]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "TittlePolygon.h"
#include "input.h"
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
LPDIRECT3DTEXTURE9 t_pTexturePolygon = NULL;
LPDIRECT3DVERTEXBUFFER9 t_pVtxBuffPolygon = NULL;
int t_nCounterAnim = 0;
int t_nPatternAnim = 0;
int t_nPatternAnimTATE = 0;
VERTEX_2D *t_pVtx;			//画像の座標のポインタ
D3DXVECTOR3 t_posPolygon;	//左上の座標？
D3DXVECTOR3 t_rotPolygon;	//回転の移動量
float t_fLengthPolygon;		//対角線の長さ
float t_fAnglePolygon;		//対角線の角度
bool Tenmetu;				//プレスエンターの点滅の変数
int TenmetuCnt;				//プレスエンターの点滅の時間計測変数　毎回初期化するためにここに記述
//◇-------------------------------------------------------------------------◇
//タイトルポリゴンの初期化処理
//◇-------------------------------------------------------------------------◇
void InitTittlePolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*TITTLE_TYOUTEN_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&t_pVtxBuffPolygon,NULL);

	//プレスエンターの点滅時間の初期化
	TenmetuCnt = 0;

	//点滅を繰り返すと記載shから表示させる処理
	Tenmetu = true;

	//ランニングマンの情報登録・ロック
	t_pVtxBuffPolygon->Lock(0,0,(void**)&t_pVtx,0);

	//頂点情報の設定
	t_pVtx[0].pos = D3DXVECTOR3(150.0f,500.0f,0.0f);
	t_pVtx[1].pos = D3DXVECTOR3(600.0f,500.0f,0.0f);
	t_pVtx[2].pos = D3DXVECTOR3(150.0f,650.0f,0.0f);
	t_pVtx[3].pos = D3DXVECTOR3(600.0f,650.0f,0.0f);

	t_pVtx[0].rhw = 1.0f;
	t_pVtx[1].rhw = 1.0f;
	t_pVtx[2].rhw = 1.0f;
	t_pVtx[3].rhw = 1.0f;

	t_pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	t_pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	t_pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	t_pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	t_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	t_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	t_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	t_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);
			
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/press_enter.png",&t_pTexturePolygon);
	
	//ロックの解除
	t_pVtxBuffPolygon->Unlock();
}
//-------------------------------------
//タイトルポリゴン終了処理
//-------------------------------------
void UninitTittlePolygon(void)
{
	//バッファの処理
	if(t_pVtxBuffPolygon != NULL)
	{
		t_pVtxBuffPolygon->Release();
		t_pVtxBuffPolygon = NULL;
	}

	//テクスチャの処理
	if(t_pTexturePolygon != NULL)
	{
		t_pTexturePolygon->Release();
		t_pTexturePolygon = NULL;
	}
}
//-------------------------------------
//タイトルポリゴンの更新処理
//-------------------------------------
void UpdateTittlePolygon(void)
{
	//フェイドノンだと点滅をする。フェイドアウトだと点滅が早くなる
	switch(GetFade())
	{
		case FADE_NONE:
			//プレスエンターの点滅の計算
			TenmetuCnt++;

			if(TenmetuCnt <= TENMETU_TIME)
			{
				Tenmetu = true;		
			}
			else
			{
				Tenmetu = false;
			}

			if(TenmetuCnt >= TENMETU_TIME * 2)
			{
				TenmetuCnt = 0;
			}
			break;

		case FADE_OUT:
			//プレスエンターの点滅の計算
			TenmetuCnt++;
		
			if(TenmetuCnt <= TENMETU_TIME_FADEOUT)
			{
				Tenmetu = true;		
			}
			else
			{
				Tenmetu = false;
			}

			if(TenmetuCnt >= TENMETU_TIME_FADEOUT * 2)
			{
				TenmetuCnt = 0;
			}
			break;

		default:
			break;
	}

}
//-------------------------------------
//タイトルポリゴンの描画処理
//-------------------------------------
void DrawTittlePolygon(void)
{

	//ランニングマンの描画
	GetDevice()->SetStreamSource(0,t_pVtxBuffPolygon,0,sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	GetDevice()->SetFVF(FVF_VERTEX_2D);	

	if(Tenmetu == true)
	{
		//テクスチャの設定
		GetDevice()->SetTexture(0,t_pTexturePolygon);
		//ポリゴンの描画
		GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,TITTLE_POLYGON_NUM);	//真ん中の0は開始する頂点インデックス
	}
}