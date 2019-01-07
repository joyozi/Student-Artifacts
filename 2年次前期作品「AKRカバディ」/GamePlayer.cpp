//◇-------------------------------------------------------------------------◇
//
//	ゲームポリゴンcppファイル[polygon.cpp]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "GamePlayer.h"
#include "input.h"
#include "hitjudge.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 g_pTexturePolygon[GamePlayer_texturenum];
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon[GamePlayer_texturenum];
int g_nCounterAnim = 0;
int g_nPatternAnim = 0;
int g_nPatternAnimTATE = 0;
VERTEX_2D *g_pVtx;				//画像の座標のポインタ
D3DXVECTOR3 g_posPolygon;		//中心の座標
D3DXVECTOR3 g_rotPolygon;		//回転の移動量
float g_fLengthPolygon;			//対角線の長さ
float g_fAnglePolygon;			//対角線の角度
float g_fNobiPolygon;			//先生の中心からの距離
D3DXVECTOR3 g_posrotPolygon;	//先生の画像の回転している角度
//◇-------------------------------------------------------------------------◇
//ゲームポリゴンの初期化処理
//◇-------------------------------------------------------------------------◇
void InitGamePolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	for(int Cnt = 0;Cnt < GamePlayer_texturenum;Cnt++)
	{
		g_pVtxBuffPolygon[Cnt] = NULL;
		g_pTexturePolygon[Cnt] = NULL;

		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*TYOUTEN_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffPolygon[Cnt],NULL);
	}

	//ランニングマンの情報登録・ロック
	g_pVtxBuffPolygon[0]->Lock(0,0,(void**)&g_pVtx,0);

	//頂点情報の設定
	g_pVtx[0].pos = D3DXVECTOR3(260.0f,200.0f,0.0f);
	g_pVtx[1].pos = D3DXVECTOR3(360.0f,200.0f,0.0f);
	g_pVtx[2].pos = D3DXVECTOR3(260.0f,300.0f,0.0f);
	g_pVtx[3].pos = D3DXVECTOR3(360.0f,300.0f,0.0f);

	g_pVtx[0].rhw = 1.0f;
	g_pVtx[1].rhw = 1.0f;
	g_pVtx[2].rhw = 1.0f;
	g_pVtx[3].rhw = 1.0f;

	g_pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	g_pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	g_pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	g_pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	g_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	g_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	g_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	g_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);
			
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/akira000.png",&g_pTexturePolygon[0]);
	
	//ロックの解除
	g_pVtxBuffPolygon[0]->Unlock();

	g_posPolygon.x = (SCREEN_WIDTH / 2);
	g_posPolygon.y = (SCREEN_HEIGHT / 2 - POLYGON_HANKEI);
	g_rotPolygon.x = 0;
	g_rotPolygon.y = 0;
	g_rotPolygon.z = 0;
	g_fLengthPolygon = sqrtf((POLYGON_YOKOLONG / 2)  * (POLYGON_YOKOLONG / 2) + (POLYGON_TATELONG / 2) * (POLYGON_TATELONG / 2));
	g_fAnglePolygon = atan2f(POLYGON_YOKOLONG,POLYGON_TATELONG);
	g_posrotPolygon.x = D3DX_PI;
	g_posrotPolygon.y = D3DX_PI;
	g_fNobiPolygon = POLYGON_HANKEI;

	//本体の座標位置をバレットとあたり判定に教える
	SetHitJudge_Player(g_posPolygon,g_rotPolygon);
}
//-------------------------------------
//ゲームポリゴン終了処理
//-------------------------------------
void UninitGamePolygon(void)
{
	for(int Cnt = 0;Cnt < GamePlayer_texturenum;Cnt++)
	{
		//バッファの処理
		if(g_pVtxBuffPolygon[Cnt] != NULL)
		{
			g_pVtxBuffPolygon[Cnt]->Release();
			g_pVtxBuffPolygon[Cnt] = NULL;
		}

		//テクスチャの処理
		if(g_pTexturePolygon[Cnt] != NULL)
		{
			g_pTexturePolygon[Cnt]->Release();
			g_pTexturePolygon[Cnt] = NULL;
		}
	}
}
//-------------------------------------
//ゲームポリゴンの更新処理
//-------------------------------------
void UpdateGamePolygon(void)
{
	D3DXVECTOR3 g_posPolygonOld;	//ひとつ前の座標 バレット用

	g_posPolygonOld.x = g_posPolygon.x;
	g_posPolygonOld.y = g_posPolygon.y;

	//先生の横移動
	if(GetKeyboardPress(DIK_A) == true)
	{
		//先生の画像の回転
		g_rotPolygon.x = g_rotPolygon.x + (D3DX_PI / GAMEPLAYER_SPEED);
		g_rotPolygon.y = g_rotPolygon.y + (D3DX_PI / GAMEPLAYER_SPEED);
		//先生の位置の回転
		g_posrotPolygon.x = g_posrotPolygon.x + (D3DX_PI / GAMEPLAYER_SPEED);
		g_posrotPolygon.y = g_posrotPolygon.y + (D3DX_PI / GAMEPLAYER_SPEED);
	}

	if(GetKeyboardPress(DIK_D) == true)
	{
		//先生の画像の回転
		g_rotPolygon.x = g_rotPolygon.x - (D3DX_PI / GAMEPLAYER_SPEED);
		g_rotPolygon.y = g_rotPolygon.y - (D3DX_PI / GAMEPLAYER_SPEED);
		//先生の位置の回転
		g_posrotPolygon.x = g_posrotPolygon.x - (D3DX_PI / GAMEPLAYER_SPEED);
		g_posrotPolygon.y = g_posrotPolygon.y - (D3DX_PI / GAMEPLAYER_SPEED);
	}

	if(GetKeyboardPress(DIK_W) == true)
	{
		g_fNobiPolygon += GAMEPLAYER_TATE_SPEED;
		//もし画面外に行こうとしたらひとつ前に戻る
		if(g_fNobiPolygon > SCREEN_WIDTH / 2)
		{
			g_fNobiPolygon -= GAMEPLAYER_TATE_SPEED;
		}
	}

	if(GetKeyboardPress(DIK_S) == true)
	{
		g_fNobiPolygon -= GAMEPLAYER_TATE_SPEED;
		//もし中心よりも下がったらひとつ前の位置に戻る
		if(g_fNobiPolygon < 80)
		{
			g_fNobiPolygon += GAMEPLAYER_TATE_SPEED;
		}
	}

	//先生の座標の計算
	g_posPolygon.x = POLYGON_YOKO + sinf(g_posrotPolygon.x) * g_fNobiPolygon;
	g_posPolygon.y = POLYGON_TATE + cosf(g_posrotPolygon.y) * g_fNobiPolygon;

	//座標とかのロック・アンロック

	g_pVtxBuffPolygon[0]->Lock(0,0,(void**)&g_pVtx,0);
	
	g_pVtx[0].pos.x = g_posPolygon.x + sinf(g_rotPolygon.x + g_fAnglePolygon) * g_fLengthPolygon;
	g_pVtx[0].pos.y = g_posPolygon.y + cosf(g_rotPolygon.y + g_fAnglePolygon) * g_fLengthPolygon;
	g_pVtx[0].pos.z = 0.0f;

	g_pVtx[1].pos.x = g_posPolygon.x + sinf(g_rotPolygon.x - g_fAnglePolygon) * g_fLengthPolygon;
	g_pVtx[1].pos.y = g_posPolygon.y + cosf(g_rotPolygon.y - g_fAnglePolygon) * g_fLengthPolygon;
	g_pVtx[1].pos.z = 0.0f;

	g_pVtx[2].pos.x = g_posPolygon.x + sinf(g_rotPolygon.x - g_fAnglePolygon + (D3DX_PI)) * g_fLengthPolygon;
	g_pVtx[2].pos.y = g_posPolygon.y + cosf(g_rotPolygon.y - g_fAnglePolygon + (D3DX_PI)) * g_fLengthPolygon;
	g_pVtx[2].pos.z = 0.0f;

	g_pVtx[3].pos.x = g_posPolygon.x + sinf(g_rotPolygon.x + g_fAnglePolygon + (D3DX_PI)) * g_fLengthPolygon;
	g_pVtx[3].pos.y = g_posPolygon.y + cosf(g_rotPolygon.y + g_fAnglePolygon + (D3DX_PI)) * g_fLengthPolygon;
	g_pVtx[3].pos.z = 0.0f;

	g_pVtxBuffPolygon[0]->Unlock();

	//本体の座標位置をバレットとあたり判定に教える
	SetHitJudge_Player(g_posPolygon,g_rotPolygon);
}
//-------------------------------------
//ゲームポリゴンの描画処理
//-------------------------------------
void DrawGamePolygon(void)
{
	for(int Cnt = 0;Cnt < GamePlayer_texturenum;Cnt++)
	{
		//ゲームポリゴンの描画
		GetDevice()->SetStreamSource(0,g_pVtxBuffPolygon[Cnt],0,sizeof(VERTEX_2D));
		//頂点フォーマットの設定
		GetDevice()->SetFVF(FVF_VERTEX_2D);	
		//テクスチャの設定
		GetDevice()->SetTexture(0,g_pTexturePolygon[Cnt]);
		//ポリゴンの描画
		GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,POLYGON_NUM);	//真ん中の0は開始する頂点インデックス
	}
}