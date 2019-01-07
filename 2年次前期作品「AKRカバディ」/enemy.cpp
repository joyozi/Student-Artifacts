//◇-------------------------------------------------------------------------◇
//
//	エネミーcppファイル[enemy.cpp]
//	AT12A271　当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "enemy.h"
#include "explosion.h"
#include "hitjudge.h"
#include "score.h"
#include "sound.h"
#include "gakutyou.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 e_pTexturePolygon[3];
LPDIRECT3DVERTEXBUFFER9 e_pVtxBuffPolygon[ENEMY_NUM];

VERTEX_2D *e_pVtx;						//画像の座標のポインタ
D3DXVECTOR3 e_fposPolygon[ENEMY_NUM];	//中心の座標
D3DXVECTOR3 e_frotPolygon[ENEMY_NUM];	//回転の移動量
float e_fLengthPolygon;					//対角線の長さ
float e_fAnglePolygon;					//対角線の角度
bool startPopjudge[ENEMY_NUM];			//一番最初に敵の出てくるタイミングずらし　それと敵の出現
int timeCnt;							//最初だけのカウント
int startPopCnt;						//
int SecondtimeCnt;						//車の出現カウントをちゃんと初期化処理で０にする 同じ配列の番号の車が再び出てくるようにする
bool explosion_hikisuu[ENEMY_NUM];		//trueのときに爆発処理に命令する

int WhatCar[ENEMY_NUM];					//車の種類を決める

//◇-------------------------------------------------------------------------◇
//初期化処理
//◇-------------------------------------------------------------------------◇
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	srand((unsigned)time(NULL));		//車の出現位置と車の種類をランダムに決定するためにランダム

	for(int nCnt = 0; nCnt < ENEMY_NUM;nCnt++)
	{
		startPopjudge[nCnt] = false;
		explosion_hikisuu[nCnt] = false;

		//車の種類を決める
		WhatCar[nCnt] = rand()%3;

		e_pVtxBuffPolygon[nCnt] = NULL;
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*ENEMY_TYOUTEN_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&e_pVtxBuffPolygon[nCnt],NULL);
		
		//エネミーの情報登録・ロック
		e_pVtxBuffPolygon[nCnt]->Lock(0,0,(void**)&e_pVtx,0);
		
		//頂点情報の設定
		e_pVtx[nCnt * 4].pos = D3DXVECTOR3(460.0f,250.0f,0.0f);
		e_pVtx[1 + (nCnt * 4)].pos = D3DXVECTOR3(510.0f,250.0f,0.0f);
		e_pVtx[2 + (nCnt * 4)].pos = D3DXVECTOR3(460.0f,350.0f,0.0f);
		e_pVtx[3 + (nCnt * 4)].pos = D3DXVECTOR3(510.0f,350.0f,0.0f);

		e_pVtx[0 + (nCnt * 4)].rhw = 1.0f;
		e_pVtx[1 + (nCnt * 4)].rhw = 1.0f;
		e_pVtx[2 + (nCnt * 4)].rhw = 1.0f;
		e_pVtx[3 + (nCnt * 4)].rhw = 1.0f;

		e_pVtx[0 + (nCnt * 4)].col = D3DCOLOR_RGBA(255,255,255,255);
		e_pVtx[1 + (nCnt * 4)].col = D3DCOLOR_RGBA(255,255,255,255);
		e_pVtx[2 + (nCnt * 4)].col = D3DCOLOR_RGBA(255,255,255,255);
		e_pVtx[3 + (nCnt * 4)].col = D3DCOLOR_RGBA(255,255,255,255);

		e_pVtx[0 + (nCnt * 4)].tex = D3DXVECTOR2(0.0,0.0);
		e_pVtx[1 + (nCnt * 4)].tex = D3DXVECTOR2(1.0,0.0);
		e_pVtx[2 + (nCnt * 4)].tex = D3DXVECTOR2(0.0,1.0);
		e_pVtx[3 + (nCnt * 4)].tex = D3DXVECTOR2(1.0,1.0);
		//ロックの解除
		e_pVtxBuffPolygon[nCnt]->Unlock();
	}

	for(int i = 0;i < 3;i++)
	{
		e_pTexturePolygon[i] = NULL;
	}

	//車の車種をランダムに決める
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/car000.png",&e_pTexturePolygon[0]);
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/car001.png",&e_pTexturePolygon[1]);
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/car002.png",&e_pTexturePolygon[2]);

	e_fLengthPolygon = sqrtf((ENEMY_WIDTH / 2)  * (ENEMY_WIDTH / 2) + (ENEMY_HEIGHT / 2) * (ENEMY_HEIGHT / 2));
	e_fAnglePolygon = atan2f(ENEMY_WIDTH,ENEMY_HEIGHT);
	
	timeCnt = -180;
	startPopCnt = 0;
}

//◇---------------------------------◇
//終了処理
//◇---------------------------------◇
void UninitEnemy(void)
{
	for(int nCnt = 0; nCnt < ENEMY_NUM;nCnt++)
	{
		//バッファの処理
		if(e_pVtxBuffPolygon[nCnt] != NULL)
		{
			e_pVtxBuffPolygon[nCnt]->Release();
			e_pVtxBuffPolygon[nCnt] = NULL;
		}
	}
	
	for(int nCnt = 0; nCnt < 3;nCnt++)
	{
		//テクスチャの処理
		if(e_pTexturePolygon[nCnt] != NULL)
		{
			e_pTexturePolygon[nCnt]->Release();
			e_pTexturePolygon[nCnt] = NULL;
		}
	}
}
//◇---------------------------------◇
//の更新処理
//◇---------------------------------◇
void UpdateEnemy(void)
{
	timeCnt++;
	//ENEMY_POP_TIME秒ごとに敵を出現させる
	if(timeCnt > ENEMY_POP_TIME)
	{
		startPopjudge[startPopCnt] = true;
		explosion_hikisuu[startPopCnt] = false;
		e_frotPolygon[startPopCnt].z = D3DX_PI * ((rand()%200) * 0.01f);
		e_fposPolygon[startPopCnt].x = (SCREEN_WIDTH / 2) - (SCREEN_WIDTH / 2) * sinf(e_frotPolygon[startPopCnt].z);
		e_fposPolygon[startPopCnt].y = (SCREEN_WIDTH / 2) - (SCREEN_WIDTH / 2) * cosf(e_frotPolygon[startPopCnt].z);
		
		//カウントのクリア
		timeCnt = 0;

		//次の配列の処理に入る
		startPopCnt++;
		//もし配列が最後まで行ったら最初に戻る
		if(startPopCnt >= ENEMY_NUM)
		{
			startPopCnt = 0;
		}
	}
	
	//車の移動処理＆あたり判定
	for(int nCnt = 0;nCnt < ENEMY_NUM; nCnt++)
	{
		if(startPopjudge[nCnt] == true)
		{
			e_fposPolygon[nCnt].x += ENEMY_SPEED * sinf(e_frotPolygon[nCnt].z);
			e_fposPolygon[nCnt].y += ENEMY_SPEED * cosf(e_frotPolygon[nCnt].z);

			//あたり判定
			SetHitJudge_Enemy(e_fposPolygon[nCnt],e_frotPolygon[nCnt],nCnt);
			//あたり判定の計算
			UpdateHitJudge();
			//判定の戻り値受け取り
			startPopjudge[nCnt] = GetHitJudge();

			//学長砲の効果適用
			if(GetBeam() == true)
			{
				for(int gakutyouCnt = 0;gakutyouCnt < ENEMY_NUM; gakutyouCnt++)
				{
					if(startPopjudge[gakutyouCnt] == true)
					{
						startPopjudge[gakutyouCnt] = false;
						SetExplosion(startPopjudge[gakutyouCnt],e_fposPolygon[gakutyouCnt],gakutyouCnt);

						
						
						GetScore();
						
						

						PlaySound(SOUND_LABEL_SE_sen_ge_bom18);
					}
				}
				SetBeam(false);
			}

			//破壊できたら特典
			if(GetHitJudge() == false)
			{
				PlaySound(SOUND_LABEL_SE_bomb000);
				GetScore();
			}
			


			//学長に近づきすぎたら消える処理
			if((SCREEN_WIDTH / 2) - ENEMY_DEADLINE < e_fposPolygon[nCnt].x && (SCREEN_WIDTH / 2) + ENEMY_DEADLINE > e_fposPolygon[nCnt].x)
			{
				if((SCREEN_HEIGHT / 2) - ENEMY_DEADLINE < e_fposPolygon[nCnt].y && (SCREEN_HEIGHT / 2) + ENEMY_DEADLINE > e_fposPolygon[nCnt].y)
				{
					//
					startPopjudge[nCnt] = false;
				}
			}
			//敵が消失したら爆発の命令
			if(startPopjudge[nCnt] == false)
			{
				//車の位置と爆発したという判定と配列の位置を教える
				SetExplosion(startPopjudge[nCnt],e_fposPolygon[nCnt],nCnt);
				PlaySound(SOUND_LABEL_SE_bomb000);
			}
		}
	}

	for(int nCnt = 0;nCnt < ENEMY_NUM; nCnt++)
	{
		//エネミーの情報登録・ロック
		e_pVtxBuffPolygon[nCnt]->Lock(0,0,(void**)&e_pVtx,0);

		e_pVtx[0 + (nCnt * 4)].pos.x = e_fposPolygon[nCnt].x + sinf(e_frotPolygon[nCnt].z + e_fAnglePolygon) * e_fLengthPolygon;
		e_pVtx[0 + (nCnt * 4)].pos.y = e_fposPolygon[nCnt].y + cosf(e_frotPolygon[nCnt].z + e_fAnglePolygon) * e_fLengthPolygon;
		e_pVtx[0 + (nCnt * 4)].pos.z = 0.0f;

		e_pVtx[1 + (nCnt * 4)].pos.x = e_fposPolygon[nCnt].x + sinf(e_frotPolygon[nCnt].z - e_fAnglePolygon) * e_fLengthPolygon;
		e_pVtx[1 + (nCnt * 4)].pos.y = e_fposPolygon[nCnt].y + cosf(e_frotPolygon[nCnt].z - e_fAnglePolygon) * e_fLengthPolygon;
		e_pVtx[1 + (nCnt * 4)].pos.z = 0.0f;

		e_pVtx[2 + (nCnt * 4)].pos.x = e_fposPolygon[nCnt].x + sinf(e_frotPolygon[nCnt].z - e_fAnglePolygon + (D3DX_PI)) * e_fLengthPolygon;
		e_pVtx[2 + (nCnt * 4)].pos.y = e_fposPolygon[nCnt].y + cosf(e_frotPolygon[nCnt].z - e_fAnglePolygon + (D3DX_PI)) * e_fLengthPolygon;
		e_pVtx[2 + (nCnt * 4)].pos.z = 0.0f;

		e_pVtx[3 + (nCnt * 4)].pos.x = e_fposPolygon[nCnt].x + sinf(e_frotPolygon[nCnt].z + e_fAnglePolygon + (D3DX_PI)) * e_fLengthPolygon;
		e_pVtx[3 + (nCnt * 4)].pos.y = e_fposPolygon[nCnt].y + cosf(e_frotPolygon[nCnt].z + e_fAnglePolygon + (D3DX_PI)) * e_fLengthPolygon;
		e_pVtx[3 + (nCnt * 4)].pos.z = 0.0f;
		
		//ロックの解除
		e_pVtxBuffPolygon[nCnt]->Unlock();
	}
}

//◇---------------------------------◇
//の描画処理
//◇---------------------------------◇
void DrawEnemy(void)
{
	for(int nCnt = 0;nCnt < ENEMY_NUM;nCnt++)
	{
		if(startPopjudge[nCnt] == true)
		{
			//背景の描画
			GetDevice()->SetStreamSource(0,e_pVtxBuffPolygon[nCnt],0,sizeof(VERTEX_2D));
			//頂点フォーマットの設定
			GetDevice()->SetFVF(FVF_VERTEX_2D);
			//テクスチャの設定
			GetDevice()->SetTexture(0,e_pTexturePolygon[WhatCar[nCnt]]);
			//ポリゴンの描画
			GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,ENEMY_POLYGON_NUM);
		}
	}
}
