//◇-------------------------------------------------------------------------◇
//
//	爆発cppファイル[explosion.cpp]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include"main.h"
#include"explosion.h"
#include "camera.h"
#include "bullet.h"
//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 r_bgTextureExplosion;
LPDIRECT3DVERTEXBUFFER9 r_bgVtxBuffExplosion;

D3DXMATRIX g_mtxProjectionExplosion[BULLET_MAX];				//プロジェクションマトリックス
D3DXMATRIX g_mtxViewExplosion[BULLET_MAX];						//ビューマトリックス
D3DXMATRIX g_mtxWorldExplosion[BULLET_MAX];						//ワールドマトリックス

D3DXVECTOR3 g_posExplosion[BULLET_MAX];							//位置
D3DXVECTOR3 g_rotExplosion[BULLET_MAX];							//向き
D3DXVECTOR3 g_sclExplosion[BULLET_MAX];							//大きさ（基本変えない）

bool ExplosionJudge[BULLET_MAX];								//表示の正否

VERTEX_3D *pVtx;												//画像の座標のポインタ

int g_nCounterAnim[BULLET_MAX];
int g_nPatternAnim[BULLET_MAX];

//◇-------------------------------------------------------------------------◇
//爆発の初期化処理
//◇-------------------------------------------------------------------------◇
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 bgDevice;
	bgDevice = GetDevice();

	for(int nCnt = 0;nCnt < BULLET_MAX;nCnt++)
	{
		//****位置、角度、スケールの初期化****
		g_posExplosion[nCnt] = D3DXVECTOR3(0.0f,50.0f,0.0f);
		g_rotExplosion[nCnt] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_sclExplosion[nCnt] = D3DXVECTOR3(1.0f,1.0f,1.0f);

		//表示の初期化
		ExplosionJudge[nCnt] = false;
		g_nPatternAnim[nCnt] = 0;
		g_nCounterAnim[nCnt] = 0;
	}


	r_bgVtxBuffExplosion = NULL;
	r_bgTextureExplosion = NULL;

	//テクスチャバッファ
	D3DXCreateTextureFromFile(bgDevice,"./data/TEXTURE/explosion_000.png",&r_bgTextureExplosion);

	//頂点バッファ
	bgDevice -> CreateVertexBuffer(sizeof(VERTEX_3D)*4*BULLET_MAX,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&r_bgVtxBuffExplosion,NULL);

	//画像の情報登録
	r_bgVtxBuffExplosion->Lock(0,0,(void**)&pVtx,0);

	//****頂点の位置の設定****
	pVtx[0].pos = D3DXVECTOR3(-30,30,0);
	pVtx[1].pos = D3DXVECTOR3(30,30,0);
	pVtx[2].pos = D3DXVECTOR3(-30,-30,0);
	pVtx[3].pos = D3DXVECTOR3(30,-30,0);

	//****何かの設定*****
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	//****カラーの設定****
	pVtx[0].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtx[1].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtx[2].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtx[3].col = D3DCOLOR_RGBA(255,255,255,55);

	//****texの設定****
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.14f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.14f,1.0f);

	r_bgVtxBuffExplosion->Unlock();
}
//-------------------------------------
//爆発処理
//-------------------------------------
void UninitExplosion(void)
{
	//バッファの処理
	if(r_bgVtxBuffExplosion != NULL)
	{
		r_bgVtxBuffExplosion -> Release();
		r_bgVtxBuffExplosion = NULL;
	}

	//テクスチャの処理
	if(r_bgTextureExplosion != NULL)
	{
		r_bgTextureExplosion->Release();
		r_bgTextureExplosion = NULL;
	}
}
//-------------------------------------
//爆発のセット処理
//-------------------------------------
void UpdateExplosion(void)
{

}
//-------------------------------------
//爆発の描画処理
//-------------------------------------
void DrawExplosion(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;	
	D3DXMATRIX mtxView;						//ビューマトリックス
	
	//****デバイス取得****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	mtxView = GetMtxView();

	//位置の初期化
	for(int nCnt = 0;nCnt < BULLET_MAX;nCnt++)
	{
		//有効なら表示する
		if(ExplosionJudge[nCnt] == true)
		{
			//爆発の番号ごとの時間の計算をする
			g_nCounterAnim[nCnt]++;

			//座標の設定処理
			r_bgVtxBuffExplosion->Lock(0,0,(void**)&pVtx,0);

			pVtx[0].tex = D3DXVECTOR2(g_nPatternAnim[nCnt]*0.14f,0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_nPatternAnim[nCnt]*0.14f)+0.14f,0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_nPatternAnim[nCnt]*0.14f,1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_nPatternAnim[nCnt]*0.14f)+0.14f,1.0f);
		
			r_bgVtxBuffExplosion->Unlock();
			
			//右辺以上になったら次のコマに移る
			if(g_nCounterAnim[nCnt] > 3)
			{		
				//次の小間に移る
				g_nPatternAnim[nCnt]++;
				//最初からカウントする
				g_nCounterAnim[nCnt] = 0;
			}

			//最後まで表示したら終わりにする
			if(g_nPatternAnim[nCnt] >= 7)
			{
				g_nPatternAnim[nCnt] = 0;
				g_nCounterAnim[nCnt] = 0;
				ExplosionJudge[nCnt] = false;
			}					
		

			//------ワールドマトリックスとかの設定--------------------------------------------------------------

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldExplosion[nCnt]);

			//逆行列を求める
			D3DXMatrixInverse(&g_mtxWorldExplosion[nCnt],NULL,&mtxView);

			g_mtxWorldExplosion[nCnt]._41 = 0.0f;
			g_mtxWorldExplosion[nCnt]._42 = 0.0f;
			g_mtxWorldExplosion[nCnt]._43 = 0.0f;

			//****ワールドの設定****
			D3DXMatrixScaling(&mtxScl,g_sclExplosion[nCnt].x,g_sclExplosion[nCnt].y,g_sclExplosion[nCnt].z);				//スケールを反映
			D3DXMatrixMultiply(&g_mtxWorldExplosion[nCnt],&g_mtxWorldExplosion[nCnt],&mtxScl);

			//****その他の設定****
			D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotExplosion[nCnt].y,g_rotExplosion[nCnt].x,g_rotExplosion[nCnt].z);	//ヨ－　ピッチ　ロール

			D3DXMatrixMultiply(&g_mtxWorldExplosion[nCnt],&g_mtxWorldExplosion[nCnt],&mtxRot);
			D3DXMatrixTranslation(&mtxTranslate,g_posExplosion[nCnt].x,g_posExplosion[nCnt].y,g_posExplosion[nCnt].z);		//位置を反映

			D3DXMatrixMultiply(&g_mtxWorldExplosion[nCnt],&g_mtxWorldExplosion[nCnt],&mtxTranslate);

			pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldExplosion[nCnt]);	//設定
	
			//------------------------------------------------------------------------------------------

			//エフェクト処理　光る処理
			pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

			//****αテストの開始****
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF,100);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

			//----------------3Dポリゴンの描画----------------------------------------------------------

			//頂点バッファをバインド
			pDevice->SetStreamSource(0,r_bgVtxBuffExplosion,0,sizeof(VERTEX_3D));
			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);
			//テクスチャの設定
			pDevice->SetTexture(0,r_bgTextureExplosion);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

			//------------------------------------------------------------------------------------------

			//****αテストの終了****
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);

			//エフェクトを元に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
		}
	}
}

//-------------------------------------
//爆発のセット処理
//-------------------------------------
void SetExplosion(D3DXVECTOR3 Explosion_Pos,int BULLETNUM,bool JUDGE,int LRJudge)
{
	g_posExplosion[BULLETNUM] = Explosion_Pos;
	ExplosionJudge[BULLETNUM] = JUDGE;

	//それぞれのそれっぽい位置への調整
	switch(LRJudge)
	{
	case 1:
		g_posExplosion[BULLETNUM].x -= 50.0f;
		break;
	case 2:
		g_posExplosion[BULLETNUM].y += 30.0f;
		break;
	case 3:
		g_posExplosion[BULLETNUM].x += 50.0f;
		break;

	}
}
