//◇-------------------------------------------------------------------------◇
//
//	ファイル[.]
//	AT12A271　当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "gakutyou.h"
#include "input.h"
#include "sound.h"
//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 g_gTexturePolygon[2] = {NULL};
LPDIRECT3DVERTEXBUFFER9 g_gVtxBuffPolygon[GAKUTYOU_TEXTURE_NUM];

VERTEX_2D *g_gVtx;											//画像の座標のポインタ
D3DXVECTOR3 g_gposPolygon[GAKUTYOU_TEXTURE_NUM];			//中心の座標
D3DXVECTOR3 g_grotPolygon[GAKUTYOU_TEXTURE_NUM];			//回転の移動量

float g_gLengthPolygon;										//対角線の長さ
float g_gAnglePolygon;										//対角線の角度

int BEAM_TIME;												//ビームの時間計算
int BEAM_NUM;												//ビームの数 位置から始める
bool BEAM_JUDGE[GAKUTYOU_TEXTURE_NUM];						//ビームの出現判定 trueで出現
int BEAM_PHAZE;												//学長先生のビームの段階 0発射開始　１チャージ　２伸ばす　３回す　４消す　５初期化

D3DXVECTOR3 g_gposrotPolygon[GAKUTYOU_TEXTURE_NUM];			//ビームの回転位置の計算用
D3DXVECTOR3 g_gposPolygon_PHAZE3[GAKUTYOU_TEXTURE_NUM];		//PHAZE3で使う。座標位置を固定する

int BEAM_START;
bool BOOMBOOMBOOM;
bool BOOMBOOMBOOMEnemy;		//エネミー大量発生用

//◇-------------------------------------------------------------------------◇
//初期化処理
//◇-------------------------------------------------------------------------◇
void InitMasaru(void)
{	
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	for(int Cnt = 0;Cnt < GAKUTYOU_TEXTURE_NUM;Cnt++)
	{
		BEAM_JUDGE[Cnt] = false;
		g_gVtxBuffPolygon[Cnt] = NULL;
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*GAKUTYOU_TYOUTEN_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_gVtxBuffPolygon[Cnt],NULL);
	}

	//テクスチャ設定
	g_gTexturePolygon[0] = NULL;
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/genki_041123_3.png",&g_gTexturePolygon[0]);
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/effect000.jpg",&g_gTexturePolygon[1]);

	//学長先生の情報登録・ロック
	g_gVtxBuffPolygon[0]->Lock(0,0,(void**)&g_gVtx,0);

	//頂点情報の設定
	g_gVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - GAKUTYOU_POLYGON_YOKOLONG,SCREEN_HEIGHT / 2 - GAKUTYOU_POLYGON_TATELONG,0.0f);
	g_gVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + GAKUTYOU_POLYGON_YOKOLONG,SCREEN_HEIGHT / 2 - GAKUTYOU_POLYGON_TATELONG,0.0f);
	g_gVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - GAKUTYOU_POLYGON_YOKOLONG,SCREEN_HEIGHT / 2 + GAKUTYOU_POLYGON_TATELONG,0.0f);
	g_gVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + GAKUTYOU_POLYGON_YOKOLONG,SCREEN_HEIGHT / 2 + GAKUTYOU_POLYGON_TATELONG,0.0f);

	g_gVtx[0].rhw = 1.0f;
	g_gVtx[1].rhw = 1.0f;
	g_gVtx[2].rhw = 1.0f;
	g_gVtx[3].rhw = 1.0f;

	g_gVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	g_gVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	g_gVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	g_gVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	g_gVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	g_gVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	g_gVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	g_gVtx[3].tex = D3DXVECTOR2(1.0,1.0);
	
	//ロックの解除
	g_gVtxBuffPolygon[0]->Unlock();

	//ビーム学長の初期化
	for(int nCnt= 1;nCnt < GAKUTYOU_TEXTURE_NUM;nCnt++)
	{
		//学長先生の情報登録・ロック
		g_gVtxBuffPolygon[nCnt]->Lock(0,0,(void**)&g_gVtx,0);

		g_gVtx[0].rhw = 1.0f;
		g_gVtx[1].rhw = 1.0f;
		g_gVtx[2].rhw = 1.0f;
		g_gVtx[3].rhw = 1.0f;

		g_gVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
		g_gVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
		g_gVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
		g_gVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

		g_gVtx[0].tex = D3DXVECTOR2(0.0,0.0);
		g_gVtx[1].tex = D3DXVECTOR2(1.0,0.0);
		g_gVtx[2].tex = D3DXVECTOR2(0.0,1.0);
		g_gVtx[3].tex = D3DXVECTOR2(1.0,1.0);
				
		//ロックの解除
		g_gVtxBuffPolygon[nCnt]->Unlock();

		g_gposPolygon[nCnt].x = (SCREEN_WIDTH / 2);
		g_gposPolygon[nCnt].y = (SCREEN_HEIGHT / 2) - GAKUTYOU_POLYGON_TATELONG;
		g_grotPolygon[nCnt].z = D3DX_PI;
		g_gposrotPolygon[nCnt].z = D3DX_PI;
	}
		
	g_gLengthPolygon = sqrtf(GAKUTYOU_POLYGON_YOKOLONG * GAKUTYOU_POLYGON_YOKOLONG);
	g_gAnglePolygon = atan2f(GAKUTYOU_POLYGON_YOKOLONG,GAKUTYOU_POLYGON_TATELONG);

	BEAM_NUM = 1;
	BEAM_TIME = 0;
	BEAM_PHAZE = 0;
	BEAM_START = 0;
	BOOMBOOMBOOM = false;
	BOOMBOOMBOOMEnemy = false;
}

//◇---------------------------------◇
//終了処理
//◇---------------------------------◇
void UninitMasaru(void)
{
	for(int Cnt = 0;Cnt < GAKUTYOU_TEXTURE_NUM;Cnt++)
	{
		//バッファの処理
		if(g_gVtxBuffPolygon[Cnt] != NULL)
		{
			g_gVtxBuffPolygon[Cnt]->Release();
			g_gVtxBuffPolygon[Cnt] = NULL;
		}
	}

	//テクスチャの処理
	for(int i = 0;i < 2;i++)
	{
		if(g_gTexturePolygon[i] != NULL)
		{
			g_gTexturePolygon[i]->Release();
			g_gTexturePolygon[i] = NULL;
		}
	}
}
//◇---------------------------------◇
//の更新処理
//◇---------------------------------◇
void UpdateMasaru(void)
{
	
	BEAM_START++;

	if(BEAM_START >= 480)
	{
		BEAM_PHAZE = 0;
		for(int nCnt = 1;nCnt < GAKUTYOU_TEXTURE_NUM;nCnt++)
		{
			g_gposPolygon[nCnt].x = (SCREEN_WIDTH / 2);
			g_gposPolygon[nCnt].y = (SCREEN_HEIGHT / 2) - GAKUTYOU_POLYGON_TATELONG;
			g_grotPolygon[nCnt].z = D3DX_PI;
			g_gposrotPolygon[nCnt].z = D3DX_PI;
		}
		//学長先生の情報登録・ロック
		g_gVtxBuffPolygon[0]->Lock(0,0,(void**)&g_gVtx,0);

		g_gVtx[0].col = D3DCOLOR_RGBA(200,25,25,255);
		g_gVtx[1].col = D3DCOLOR_RGBA(200,25,25,255);
		g_gVtx[2].col = D3DCOLOR_RGBA(200,25,25,255);
		g_gVtx[3].col = D3DCOLOR_RGBA(200,25,25,255);

		//ロックの解除
		g_gVtxBuffPolygon[0]->Unlock();

		if(GetKeyboardTrigger(DIK_SPACE) == true)
		{
			PlaySound(SOUND_LABEL_SE_gakutyou_beam_05);

			//PHAZE 0 初期化
			if(BEAM_PHAZE == 0)
			{
				BEAM_PHAZE++;
				BEAM_START = 0;
				BEAM_TIME = 0;
				g_gVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
				g_gVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
				g_gVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
				g_gVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);
			}	
		}
	}
	
	

	//PHAZE 1 ビームをためる
	if(BEAM_PHAZE == 1)
	{
		//表示のずれを作る
		BEAM_TIME++;

		if(BEAM_NUM < GAKUTYOU_TEXTURE_NUM)
		{
			if(BEAM_TIME >= GAKUTYOU_BEAM_TAME_TIME / GAKUTYOU_TEXTURE_NUM)
			{
				BEAM_JUDGE[BEAM_NUM] = true;

				//学長先生の情報登録・ロック
				g_gVtxBuffPolygon[BEAM_NUM]->Lock(0,0,(void**)&g_gVtx,0);

				//頂点情報の設定
				g_gVtx[0].pos.x = g_gposPolygon[BEAM_NUM].x + sinf(g_grotPolygon[BEAM_NUM].z + g_gAnglePolygon) * g_gLengthPolygon;
				g_gVtx[0].pos.y = g_gposPolygon[BEAM_NUM].y + cosf(g_grotPolygon[BEAM_NUM].z + g_gAnglePolygon) * g_gLengthPolygon;
				g_gVtx[0].pos.z = 0;

				g_gVtx[1].pos.x = g_gposPolygon[BEAM_NUM].x + sinf(g_grotPolygon[BEAM_NUM].z - g_gAnglePolygon) * g_gLengthPolygon;
				g_gVtx[1].pos.y = g_gposPolygon[BEAM_NUM].y + cosf(g_grotPolygon[BEAM_NUM].z - g_gAnglePolygon) * g_gLengthPolygon;
				g_gVtx[1].pos.z = 0;

				g_gVtx[2].pos.x = g_gposPolygon[BEAM_NUM].x + sinf(g_grotPolygon[BEAM_NUM].z - g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
				g_gVtx[2].pos.y = g_gposPolygon[BEAM_NUM].y + cosf(g_grotPolygon[BEAM_NUM].z - g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
				g_gVtx[2].pos.z = 0;

				g_gVtx[3].pos.x = g_gposPolygon[BEAM_NUM].x + sinf(g_grotPolygon[BEAM_NUM].z + g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
				g_gVtx[3].pos.y = g_gposPolygon[BEAM_NUM].y + cosf(g_grotPolygon[BEAM_NUM].z + g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
				g_gVtx[3].pos.z = 0;
	
				//ロックの解除
				g_gVtxBuffPolygon[BEAM_NUM]->Unlock();

				BEAM_NUM++;
				BEAM_TIME = 0;
				//最初だけ学長の顔をのぞかせる。最初の一枚画像だけ長く表示する
				if(BEAM_NUM == 2)
				{
					BEAM_TIME = -GAKUTYOU_BEAM_TAME_TIME;
				}
			}
		}
		else	//全部表示したら次の段階へ
		{
			BEAM_PHAZE++;
			BEAM_NUM = 1;
			BEAM_TIME = 0;
		}
	}

	//PHAZE 2　伸ばす
	if(BEAM_PHAZE == 2)
	{
		for(int nCnt = 1;nCnt < GAKUTYOU_TEXTURE_NUM;nCnt++)
		{
			//１だったらスクリーンの半分くらい÷（テクスチャ数ー１）だけ進む。　nCnt＝１のテクスチャは一番近くで止まる
			if(g_gposPolygon[nCnt].y > GAKUTYOU_BEAM_LONG - (GAKUTYOU_BEAM_LONG / GAKUTYOU_TEXTURE_NUM * nCnt))
			{
				g_gposPolygon[nCnt].y -= GAKUTYOU_BEAM_NOBI_SPEED;

				//学長先生の情報登録・ロック
				g_gVtxBuffPolygon[nCnt]->Lock(0,0,(void**)&g_gVtx,0);

				//頂点情報の設定
				g_gVtx[0].pos.x = g_gposPolygon[nCnt].x + sinf(g_grotPolygon[nCnt].z + g_gAnglePolygon) * g_gLengthPolygon;
				g_gVtx[0].pos.y = g_gposPolygon[nCnt].y + cosf(g_grotPolygon[nCnt].z + g_gAnglePolygon) * g_gLengthPolygon;
				g_gVtx[0].pos.z = 0;

				g_gVtx[1].pos.x = g_gposPolygon[nCnt].x + sinf(g_grotPolygon[nCnt].z - g_gAnglePolygon) * g_gLengthPolygon;
				g_gVtx[1].pos.y = g_gposPolygon[nCnt].y + cosf(g_grotPolygon[nCnt].z - g_gAnglePolygon) * g_gLengthPolygon;
				g_gVtx[1].pos.z = 0;

				g_gVtx[2].pos.x = g_gposPolygon[nCnt].x + sinf(g_grotPolygon[nCnt].z - g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
				g_gVtx[2].pos.y = g_gposPolygon[nCnt].y + cosf(g_grotPolygon[nCnt].z - g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
				g_gVtx[2].pos.z = 0;

				g_gVtx[3].pos.x = g_gposPolygon[nCnt].x + sinf(g_grotPolygon[nCnt].z + g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
				g_gVtx[3].pos.y = g_gposPolygon[nCnt].y + cosf(g_grotPolygon[nCnt].z + g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
				g_gVtx[3].pos.z = 0;
	
				//ロックの解除
				g_gVtxBuffPolygon[nCnt]->Unlock();
			}

			//ビームの先端が最大までのびたらPHAZE移行
			if(g_gposPolygon[nCnt].y <= 100)
			{
				BEAM_TIME++;
				if(BEAM_TIME >= 60)
				{
					BEAM_PHAZE++;
					BEAM_TIME = 0;
					for(int Junbi_Cnt = 1;Junbi_Cnt < GAKUTYOU_TEXTURE_NUM;Junbi_Cnt++)
					{
						g_gposPolygon_PHAZE3[Junbi_Cnt].x = g_gposPolygon[Junbi_Cnt].x;
						g_gposPolygon_PHAZE3[Junbi_Cnt].y = g_gposPolygon[Junbi_Cnt].y;
					}
				}
			}
		}
	}

	//PHAZE 3 薙ぎ払う
	if(BEAM_PHAZE == 3)
	{
		for(int nCnt = 1;nCnt < GAKUTYOU_TEXTURE_NUM;nCnt++)
		{
			g_grotPolygon[nCnt].z += g_gposrotPolygon[nCnt].z + (D3DX_PI / GAKUTYOU_BEAM_ROLL_SPEED);
			g_gposrotPolygon[nCnt].z = g_gposrotPolygon[nCnt].z + (D3DX_PI / GAKUTYOU_BEAM_ROLL_SPEED);

			//ビームの座標の計算
			g_gposPolygon[nCnt].x = SCREEN_WIDTH / 2 + sinf(g_gposrotPolygon[nCnt].z) * (g_gposPolygon_PHAZE3[nCnt].y + GAKUTYOU_POLYGON_TATELONG);
			g_gposPolygon[nCnt].y = SCREEN_HEIGHT / 2 + cosf(g_gposrotPolygon[nCnt].z) * (g_gposPolygon_PHAZE3[nCnt].y + GAKUTYOU_POLYGON_TATELONG);

			//学長先生の情報登録・ロック
			g_gVtxBuffPolygon[nCnt]->Lock(0,0,(void**)&g_gVtx,0);

			//頂点情報の設定
			g_gVtx[0].pos.x = g_gposPolygon[nCnt].x + sinf(g_grotPolygon[nCnt].z + g_gAnglePolygon) * g_gLengthPolygon;
			g_gVtx[0].pos.y = g_gposPolygon[nCnt].y + cosf(g_grotPolygon[nCnt].z + g_gAnglePolygon) * g_gLengthPolygon;
			g_gVtx[0].pos.z = 0;

			g_gVtx[1].pos.x = g_gposPolygon[nCnt].x + sinf(g_grotPolygon[nCnt].z - g_gAnglePolygon) * g_gLengthPolygon;
			g_gVtx[1].pos.y = g_gposPolygon[nCnt].y + cosf(g_grotPolygon[nCnt].z - g_gAnglePolygon) * g_gLengthPolygon;
			g_gVtx[1].pos.z = 0;

			g_gVtx[2].pos.x = g_gposPolygon[nCnt].x + sinf(g_grotPolygon[nCnt].z - g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
			g_gVtx[2].pos.y = g_gposPolygon[nCnt].y + cosf(g_grotPolygon[nCnt].z - g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
			g_gVtx[2].pos.z = 0;

			g_gVtx[3].pos.x = g_gposPolygon[nCnt].x + sinf(g_grotPolygon[nCnt].z + g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
			g_gVtx[3].pos.y = g_gposPolygon[nCnt].y + cosf(g_grotPolygon[nCnt].z + g_gAnglePolygon + (D3DX_PI)) * g_gLengthPolygon;
			g_gVtx[3].pos.z = 0;
	
			//ロックの解除
			g_gVtxBuffPolygon[nCnt]->Unlock();
		}

		if(g_grotPolygon[1].z >= D3DX_PI * 41)
		{
			BEAM_PHAZE++;
			BEAM_TIME = -60;
			BOOMBOOMBOOM = true;
		}
	}

	//PHAZE 4 消失
	if(BEAM_PHAZE == 4)
	{
		BEAM_TIME++;

		for(int nCnt = 1;nCnt < GAKUTYOU_TEXTURE_NUM;nCnt++)
		{
			if(BEAM_TIME >= 0.5f * (GAKUTYOU_TEXTURE_NUM - nCnt))
			{
				//学長先生の情報登録・ロック
				g_gVtxBuffPolygon[nCnt]->Lock(0,0,(void**)&g_gVtx,0);

				g_gVtx[0].pos = D3DXVECTOR3(-400,-400,0.0f);
				g_gVtx[1].pos = D3DXVECTOR3(-400,-400,0.0f);
				g_gVtx[2].pos = D3DXVECTOR3(-400,-400,0.0f);
				g_gVtx[3].pos = D3DXVECTOR3(-400,-400,0.0f);
		
				//ロックの解除
				g_gVtxBuffPolygon[nCnt]->Unlock();
			}
		}
		
		if(BEAM_TIME >= 20 * (GAKUTYOU_TEXTURE_NUM - 1))
		{
			BEAM_PHAZE++;
			BEAM_PHAZE = 0;
			BEAM_START = 0;
			BEAM_TIME = 0;

			
		}
	}

	//PHAZE 5 初期化
	if(BEAM_PHAZE == 5)
	{
		for(int nCnt = 1;nCnt < GAKUTYOU_TEXTURE_NUM;nCnt++)
		{
			

			
		}
		BEAM_PHAZE = 0;
		BEAM_START = 0;
		BEAM_TIME = 0;
	}
}

//◇---------------------------------◇
//の描画処理
//◇---------------------------------◇
void DrawMasaru(void)
{
	//中心の学長の描画
	//ゲームポリゴンの描画
	GetDevice()->SetStreamSource(0,g_gVtxBuffPolygon[0],0,sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	GetDevice()->SetFVF(FVF_VERTEX_2D);	
	//テクスチャの設定
	GetDevice()->SetTexture(0,g_gTexturePolygon[0]);
	//ポリゴンの描画
	GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,GAKUTYOU_POLYGON_NUM);	//真ん中の0は開始する頂点インデックス

	//エフェクト処理　光る処理
	GetDevice()->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	GetDevice()->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	GetDevice()->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
	

	if(BEAM_PHAZE > 0)
	{
		//最初のオリジナル学長以外の描画
		for(int Cnt = 1;Cnt < GAKUTYOU_TEXTURE_NUM;Cnt++)
		{
			//ゲームポリゴンの描画
			GetDevice()->SetStreamSource(0,g_gVtxBuffPolygon[Cnt],0,sizeof(VERTEX_2D));
			//頂点フォーマットの設定
			GetDevice()->SetFVF(FVF_VERTEX_2D);	
			//テクスチャの設定
			GetDevice()->SetTexture(0,g_gTexturePolygon[0]);
			//ポリゴンの描画
			GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);	//真ん中の0は開始する頂点インデックス
		}
	}

	//エフェクトを元に戻す
	GetDevice()->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	GetDevice()->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	GetDevice()->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

}


void SetBeam(bool gakutyouJudge)
{
	BOOMBOOMBOOM = gakutyouJudge;
}

bool GetBeam(void)
{
	return BOOMBOOMBOOM;
}

void SetBeamEnemy(bool gakutyouJudgeEnemy)
{
	BOOMBOOMBOOMEnemy = gakutyouJudgeEnemy;
}

bool GetBeamEnemy(void)
{
	return BOOMBOOMBOOMEnemy;
}