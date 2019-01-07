//◇-------------------------------------------------------------------------◇
//
//	爆発cppファイル[explosion.cpp]
//	AT12A271　当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "explosion.h"
#include "enemy.h"
//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 x_eTexturePolygon[ENEMY_NUM];		//敵の数だけ爆発の数がある
LPDIRECT3DVERTEXBUFFER9 x_eVtxBuffPolygon[ENEMY_NUM];	//
VERTEX_2D *x_eVtx;						//画像の座標のポインタ

float x_eLengthPolygon;					//対角線の長さ
float x_eAnglePolygon;					//対角線の角度
bool Explosion_Judge[ENEMY_NUM];		//爆発するかどうか
D3DXVECTOR3 x_eposPolygon[ENEMY_NUM];	//中心の座標
D3DXVECTOR3 x_erotPolygon[ENEMY_NUM];	//回転の移動量

//◇-------------------------------------------------------------------------◇
//爆発初期化処理
//◇-------------------------------------------------------------------------◇
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	for(int nCnt = 0; nCnt < ENEMY_NUM;nCnt++)
	{
		x_eTexturePolygon[nCnt] = NULL;
		x_eVtxBuffPolygon[nCnt] = NULL;

		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*ENEMY_TYOUTEN_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&x_eVtxBuffPolygon[nCnt],NULL);
		
		//エネミーの情報登録・ロック
		x_eVtxBuffPolygon[nCnt]->Lock(0,0,(void**)&x_eVtx,0);

		//頂点情報の設定

		x_eVtx[0 + (nCnt * 4)].rhw = 1.0f;
		x_eVtx[1 + (nCnt * 4)].rhw = 1.0f;
		x_eVtx[2 + (nCnt * 4)].rhw = 1.0f;
		x_eVtx[3 + (nCnt * 4)].rhw = 1.0f;

		x_eVtx[0 + (nCnt * 4)].col = D3DCOLOR_RGBA(255,255,255,200);
		x_eVtx[1 + (nCnt * 4)].col = D3DCOLOR_RGBA(255,255,255,200);
		x_eVtx[2 + (nCnt * 4)].col = D3DCOLOR_RGBA(255,255,255,200);
		x_eVtx[3 + (nCnt * 4)].col = D3DCOLOR_RGBA(255,255,255,200);

		x_eVtx[0 + (nCnt * 4)].tex = D3DXVECTOR2(0.0,0.0);
		x_eVtx[1 + (nCnt * 4)].tex = D3DXVECTOR2(1.0,0.0);
		x_eVtx[2 + (nCnt * 4)].tex = D3DXVECTOR2(0.0,0.5);
		x_eVtx[3 + (nCnt * 4)].tex = D3DXVECTOR2(1.0,0.5);

		D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/explosion.png",&x_eTexturePolygon[nCnt]);

		//ロックの解除
		x_eVtxBuffPolygon[nCnt]->Unlock();
		
		//いろいろな初期化
		Explosion_Judge[nCnt] = true;
		
		x_eposPolygon[nCnt].x = 0;
		x_eposPolygon[nCnt].y = 0;

		x_erotPolygon[nCnt].x = 0;
		x_erotPolygon[nCnt].y = 0;
		x_erotPolygon[nCnt].z = 0;
	}

	x_eLengthPolygon = sqrtf((EXPLOSION_HANKEI / 2)  * (EXPLOSION_HANKEI / 2) + (EXPLOSION_HANKEI / 2) * (EXPLOSION_HANKEI / 2));
	x_eAnglePolygon = atan2f(EXPLOSION_HANKEI,EXPLOSION_HANKEI);
}

//◇---------------------------------◇
//爆発終了処理
//◇---------------------------------◇
void UninitExplosion(void)
{
	for(int nCnt = 0; nCnt < ENEMY_NUM;nCnt++)
	{
		//バッファの処理
		if(x_eVtxBuffPolygon[nCnt] != NULL)
		{
			x_eVtxBuffPolygon[nCnt]->Release();
			x_eVtxBuffPolygon[nCnt] = NULL;
		}

		//テクスチャの処理
		if(x_eTexturePolygon[nCnt] != NULL)
		{
			x_eTexturePolygon[nCnt]->Release();
			x_eTexturePolygon[nCnt] = NULL;
		}
	}
}
//◇---------------------------------◇
//爆発の更新処理
//◇---------------------------------◇
void UpdateExplosion(void)
{
	static int explosion_cnt[ENEMY_NUM];

	for(int nCnt = 0;nCnt < ENEMY_NUM;nCnt++)
	{
		if(Explosion_Judge[nCnt] == false)
		{
			explosion_cnt[nCnt]++;
			
			//エネミーの情報登録・ロック
			x_eVtxBuffPolygon[nCnt]->Lock(0,0,(void**)&x_eVtx,0);

			x_eVtx[nCnt * 4].pos.x = x_eposPolygon[nCnt].x + sinf(x_erotPolygon[nCnt].z + x_eAnglePolygon) * x_eLengthPolygon;
			x_eVtx[nCnt * 4].pos.y = x_eposPolygon[nCnt].y + cosf(x_erotPolygon[nCnt].z + x_eAnglePolygon) * x_eLengthPolygon;
			x_eVtx[nCnt * 4].pos.z = 0.0f;

			x_eVtx[1 + (nCnt * 4)].pos.x = x_eposPolygon[nCnt].x + sinf(x_erotPolygon[nCnt].z - x_eAnglePolygon) * x_eLengthPolygon;
			x_eVtx[1 + (nCnt * 4)].pos.y = x_eposPolygon[nCnt].y + cosf(x_erotPolygon[nCnt].z - x_eAnglePolygon) * x_eLengthPolygon;
			x_eVtx[1 + (nCnt * 4)].pos.z = 0.0f;

			x_eVtx[2 + (nCnt * 4)].pos.x = x_eposPolygon[nCnt].x + sinf(x_erotPolygon[nCnt].z - x_eAnglePolygon + (D3DX_PI)) * x_eLengthPolygon;
			x_eVtx[2 + (nCnt * 4)].pos.y = x_eposPolygon[nCnt].y + cosf(x_erotPolygon[nCnt].z - x_eAnglePolygon + (D3DX_PI)) * x_eLengthPolygon;
			x_eVtx[2 + (nCnt * 4)].pos.z = 0.0f;

			x_eVtx[3 + (nCnt * 4)].pos.x = x_eposPolygon[nCnt].x + sinf(x_erotPolygon[nCnt].z + x_eAnglePolygon + (D3DX_PI)) * x_eLengthPolygon;
			x_eVtx[3 + (nCnt * 4)].pos.y = x_eposPolygon[nCnt].y + cosf(x_erotPolygon[nCnt].z + x_eAnglePolygon + (D3DX_PI)) * x_eLengthPolygon;
			x_eVtx[3 + (nCnt * 4)].pos.z = 0.0f;

			//ロックの解除
			x_eVtxBuffPolygon[nCnt]->Unlock();
		
			//数秒たったら終わり
			if(explosion_cnt[nCnt] >= EXPLOSION_TIME)
			{
				Explosion_Judge[nCnt] = true;
				explosion_cnt[nCnt] = 0;
			}		
		}
	}
}

//◇---------------------------------◇
//爆発の描画処理
//◇---------------------------------◇
void DrawExplosion(void)
{
	for(int nCnt = 0;nCnt < ENEMY_NUM;nCnt++)
	{
		if(Explosion_Judge[nCnt] == false)
		{
			//背景の描画
			GetDevice()->SetStreamSource(0,x_eVtxBuffPolygon[nCnt],0,sizeof(VERTEX_2D));
			//頂点フォーマットの設定
			GetDevice()->SetFVF(FVF_VERTEX_2D);
			//テクスチャの設定
			GetDevice()->SetTexture(0,x_eTexturePolygon[nCnt]);
			//ポリゴンの描画
			GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,ENEMY_POLYGON_NUM);
		}
	}
}

//◇---------------------------------◇
//爆発の取得処理
//◇---------------------------------◇
void SetExplosion(bool enemy_Judge,D3DXVECTOR3 pos,int RendouCnt)	//車がenemyの中で何番目かを同期する
{
	x_eposPolygon[RendouCnt].x = pos.x;
	x_eposPolygon[RendouCnt].y = pos.y;
	Explosion_Judge[RendouCnt] = enemy_Judge;	//falseだったら爆発
}