//◇-------------------------------------------------------------------------◇
//
//	File	:モデル処理ファイル[rail.cpp]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "input.h"
#include "taimatsu.h"
#include "model.h"
#include "camera.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 g_pTextureTaimatsu;		//
LPD3DXMESH g_pMeshTaimatsu;					//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatTaimatsu;			//マテリアル情報へのポインタ

DWORD g_numMatTaimatsu;						//マテリアルの数
D3DXVECTOR3 g_posTaimatsu;					//モデルの位置
D3DXVECTOR3 g_rotTaimatsu;					//モデルの向き
D3DXVECTOR3 g_sclTaimatsu;					//モデルの大きさ

D3DXMATRIX g_mtxWorldTaimatsu;				//ワールドマトリックス

float Taimatsu_POSZ;

bool taimatu_sayuu;						//松明の左右の判定
bool kisuu_taimatuOPSION;				//一番後ろの松明が左右どちらにあるかを入れる。松明の数が奇数にするなら使う

//◇-------------------------------------------------------------------------◇
//モデルの初期化処理
//◇-------------------------------------------------------------------------◇
void InitTaimatsu(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	taimatu_sayuu = true;				//松明の左右位置の初期化
	kisuu_taimatuOPSION = taimatu_sayuu;//一番後ろの松明の位置の代入
	Taimatsu_POSZ = -CAMERA_LONG;		//松明の位置の初期化

	//****モデルの情報セット****
	D3DXLoadMeshFromX("./data/MODEL/taimatsu_001.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatTaimatsu,
					NULL,
					&g_numMatTaimatsu,
					&g_pMeshTaimatsu);

	//****位置、角度、スケールの初期化****
	g_posTaimatsu = D3DXVECTOR3(70.0f,120.0f,Taimatsu_POSZ);
	g_rotTaimatsu = D3DXVECTOR3(0.0f,0.0f,0.5f);
	g_sclTaimatsu = D3DXVECTOR3(1.0f,1.0f,1.0f);
}
//◇-------------------------------------------------------------------------◇
//モデルの終了処理
//◇-------------------------------------------------------------------------◇
void UninitTaimatsu(void)
{
	//メッシュモデルのリリース
	//==============================
	if(g_pMeshTaimatsu != NULL)
	{
		g_pMeshTaimatsu -> Release();
		g_pMeshTaimatsu = NULL;
	}
	
	//バッファマットのリリース
	//=============================
	if(g_pBuffMatTaimatsu != NULL)
	{
		g_pBuffMatTaimatsu -> Release();
		g_pBuffMatTaimatsu = NULL;
	}

	//テクステャのリリース
	//=============================
	if(g_pTextureTaimatsu != NULL)
	{
		g_pTextureTaimatsu -> Release();
		g_pTextureTaimatsu = NULL;

	}
}
//◇-------------------------------------------------------------------------◇
//モデルの更新処理
//◇-------------------------------------------------------------------------◇
void UpdateTaimatsu(void)
{

}
//◇-------------------------------------------------------------------------◇
//モデルの描画処理
//◇-------------------------------------------------------------------------◇
void DrawTaimatsu(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//kisuu_taimatuOPSIONから最初にしないと、松明の位置がおかしくなったりする
	taimatu_sayuu = kisuu_taimatuOPSION;
	

	//松明を左右のどっちに設置するかのジャッジ
	//本体の位置より遠ざかったらプラスマイナスする
	//松明の情報を保存しないでその場のノリでやってるので、数値の変換をするとたまに位置がおかしくなる
	while(Getg_posModel().z - CAMERA_LONG >= Taimatsu_POSZ)
	{
		Taimatsu_POSZ += TAIMATSU_KANKAKU;

		//左右移動
		if(taimatu_sayuu == true)
			taimatu_sayuu = false;
		else
			taimatu_sayuu = true;

		//一番後ろの松明の左右位置の判定
		if(kisuu_taimatuOPSION == true)
			kisuu_taimatuOPSION = false;
		else
			kisuu_taimatuOPSION = true;
	}

	while(Getg_posModel().z + CAMERA_LONG < Taimatsu_POSZ + CAMERA_LONG * 2)
	{
		Taimatsu_POSZ -= TAIMATSU_KANKAKU;

		//左右移動
		if(taimatu_sayuu == true)
			taimatu_sayuu = false;
		else
			taimatu_sayuu = true;

		//一番後ろの松明の左右位置の判定
		if(kisuu_taimatuOPSION == true)
			kisuu_taimatuOPSION = false;
		else
			kisuu_taimatuOPSION = true;

	}

	g_posTaimatsu.z = Taimatsu_POSZ;

	while(g_posTaimatsu.z < Taimatsu_POSZ + CAMERA_LONG * 2)
	{
		//松明の位置を一番後ろに設定
		g_posTaimatsu.z += TAIMATSU_KANKAKU;

		if(taimatu_sayuu == true)
		{
			//もし正だったら左側に松明を表示する
			g_posTaimatsu.x = TAIMATSU_POSX;
			g_rotTaimatsu.y = 0.0f;
			taimatu_sayuu = false;
		}
		else
		{
			g_posTaimatsu.x = -TAIMATSU_POSX;
			g_rotTaimatsu.y = D3DX_PI;
			taimatu_sayuu = true;
		}

		D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
		D3DXMATERIAL *pMat;
		D3DMATERIAL9 matDef;		//マットのデフォルト

		//****ワールドの設定****
		D3DXMatrixIdentity(&g_mtxWorldTaimatsu);
		D3DXMatrixScaling(&mtxScl,g_sclTaimatsu.x,
									g_sclTaimatsu.y,
									g_sclTaimatsu.z);			//スケールを反映

		D3DXMatrixMultiply(&g_mtxWorldTaimatsu,&g_mtxWorldTaimatsu,&mtxScl);

		//****その他の設定****
		D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotTaimatsu.y,
										g_rotTaimatsu.x,
										g_rotTaimatsu.z);		//ヨ－　ピッチ　ロール

		D3DXMatrixMultiply(&g_mtxWorldTaimatsu,&g_mtxWorldTaimatsu,&mtxRot);
		D3DXMatrixTranslation(&mtxTranslate,g_posTaimatsu.x,g_posTaimatsu.y,g_posTaimatsu.z);	//位置を反映
		D3DXMatrixMultiply(&g_mtxWorldTaimatsu,&g_mtxWorldTaimatsu,&mtxTranslate);
	
		pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldTaimatsu);	//設定

		//=========マテリアルなどの取得=========
		//======================================
		pDevice -> GetMaterial(&matDef);
		pMat = (D3DXMATERIAL*)g_pBuffMatTaimatsu -> GetBufferPointer();

		for(int nCntMat = 0;nCntMat < (int)g_numMatTaimatsu;nCntMat++)
		{
			pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
			pDevice -> SetTexture(0,NULL);
			g_pMeshTaimatsu -> DrawSubset(nCntMat);
		}

		pDevice -> SetMaterial(&matDef);
	}

	//終わったら松明の明りのために位置を一番後ろに戻す
	g_posTaimatsu.z = Taimatsu_POSZ;

}

//松明の位置情報の関数
D3DXVECTOR3 Getpostaimatsu(void)
{
	return g_posTaimatsu;
}