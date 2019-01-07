//◇-------------------------------------------------------------------------◇
//
//	File	:モデル処理ファイル[model.cpp]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "obstacle.h"
#include "model.h"
#include "gameUI.h"
#include "camera.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇
#define MODEL_OBSTACLE_DATA	("./data/MODEL/rock_001.x")	//モデルのデータの位置と名前

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 g_pTextureObstacle;		//
LPD3DXMESH g_pMeshObstacle;					//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatObstacle;			//マテリアル情報へのポインタ

DWORD g_numMatObstacle;						//マテリアルの数
D3DXVECTOR3 g_posObstacle;					//モデルの位置
D3DXVECTOR3 g_rotObstacle[OBSTACLE_NUM];	//モデルの向き	岩の向きを変えるために配列にする
D3DXVECTOR3 g_sclObstacle;					//モデルの大きさ

D3DXMATRIX g_mtxWorldObstacle;				//ワールドマトリックス

PLAYER_MODE Obstacle_info[OBSTACLE_NUM];	//障害物の情報の入れ子

//◇-------------------------------------------------------------------------◇
//モデルの初期化処理
//◇-------------------------------------------------------------------------◇
void InitObstacle(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//障害物の座標を入れる　Ｘ軸
	int Obstacle_posX_ORIGINAL[OBSTACLE_NUM] = {2,0,0,3,0,2,1,3,0,2,0,0,0,0,0,0,0,0,2,0,				//0～19
												1,3,0,0,0,3,1,3,0,0,1,0,0,3,2,1,0,0,0,0,				//20～39
												1,3,0,3,0,0,0,3,0,0,									//４０～４９
												0,0,3,0,2,0,0,1,3,0,									//５０～５９
												0,0,2,0,0,3,2,0,3,0,									//60~69
												1,2,0,0,0,1,3,0,0,0,									//70~79
												0,0,2,2,0,0,1,3,2,0,									//80~89
												0,0,0,0,0,0,0,0,0,0};

	//障害物の座標　改変しない　Ｚ軸
	float Obstacle_posZ_ORIGINAL[OBSTACLE_NUM] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
												0,-600,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
												0,-600,0,0,0,0,0,0,0,0,									//40~49
												0,0,0,0,0,0,0,0,0,0,									//50~59
												0,0,0,0,0,0,0,0,0,0,									//60~69
												600,0,0,0,0,600,0,0,0,0,								//70~79
												0,0,0,0,0,0,0,0,0,0,									//80~89
												0,0,0,0,0,0,0,0,0,0};

	for(int nCnt = 0;nCnt < OBSTACLE_NUM;nCnt++)
	{
		//障害物の位置を入れる
		Obstacle_info[nCnt].LR_Judge = Obstacle_posX_ORIGINAL[nCnt];
		Obstacle_info[nCnt].MOTO_pos.z = Obstacle_posZ_ORIGINAL[nCnt];

		//障害物の表示判定を入れる
		if(Obstacle_posX_ORIGINAL[nCnt] != 0)
		{
			Obstacle_info[nCnt].Thing_exist = true;
		}
		else
		{
			Obstacle_info[nCnt].Thing_exist = false;
		}

		//数値の簡略化　障害物設置開始位置をプラス,間隔をあけていく
		Obstacle_info[nCnt].MOTO_pos.z = Obstacle_info[nCnt].MOTO_pos.z + OBSTACLE_SETTI_LINE + nCnt * 600;
	}

	//****モデルの情報セット****
	D3DXLoadMeshFromX(MODEL_OBSTACLE_DATA,
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatObstacle,
					NULL,
					&g_numMatObstacle,
					&g_pMeshObstacle);

	//****位置、角度、スケールの初期化****
	g_posObstacle = D3DXVECTOR3(40.0f,0.0f,0.0f);
	g_sclObstacle = D3DXVECTOR3(1.0f,1.0f,1.0f);

	for(int nCnt = 0;nCnt < OBSTACLE_NUM;nCnt++)
	{
		g_rotObstacle[nCnt] = D3DXVECTOR3(0.0f,0.0f,0.0f);

		switch(nCnt % 4)
		{
		case 0:
			g_rotObstacle[nCnt].y = 0.0f;
			break;
		case 1:
			g_rotObstacle[nCnt].y = D3DX_PI / 2;
			break;
		case 2:
			g_rotObstacle[nCnt].y = D3DX_PI;
			break;
		case 3:
			g_rotObstacle[nCnt].y = -D3DX_PI / 2;
			break;

		}
	}
}
//◇-------------------------------------------------------------------------◇
//モデルの終了処理
//◇-------------------------------------------------------------------------◇
void UninitObstacle(void)
{
	//メッシュモデルのリリース
	//==============================
	if(g_pMeshObstacle != NULL)
	{
		g_pMeshObstacle -> Release();
		g_pMeshObstacle = NULL;
	}
	
	//バッファマットのリリース
	//=============================
	if(g_pBuffMatObstacle != NULL)
	{
		g_pBuffMatObstacle -> Release();
		g_pBuffMatObstacle = NULL;
	}

	//テクステャのリリース
	//=============================
	if(g_pTextureObstacle != NULL)
	{
		g_pTextureObstacle -> Release();
		g_pTextureObstacle = NULL;

	}
}
//◇-------------------------------------------------------------------------◇
//モデルの更新処理
//◇-------------------------------------------------------------------------◇
void UpdateObstacle(void)
{

}
//◇-------------------------------------------------------------------------◇
//モデルの描画処理
//◇-------------------------------------------------------------------------◇
void DrawObstacle(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//マットのデフォルト

	//障害物の数だけ繰り返す
	for(int nCnt = 0;nCnt < OBSTACLE_NUM;nCnt++)
	{
		//表示させるか否かの判定
		if(Obstacle_info[nCnt].Thing_exist == true)
		{
			//見える位置のみ表示するために、表示の範囲内だったら描画するようにする
			if(Getg_posModel().z - CAMERA_LONG < Obstacle_info[nCnt].MOTO_pos.z && Getg_posModel().z + CAMERA_LONG > Obstacle_info[nCnt].MOTO_pos.z)
			{
				//用意しておいた位置情報を一つのg_posObstacleにいれる
				g_posObstacle.z = Obstacle_info[nCnt].MOTO_pos.z;

				switch(Obstacle_info[nCnt].LR_Judge)
				{
				case 1:
					g_posObstacle.x = -60.0f;
					break;
				case 2:
					g_posObstacle.x = 0.0f;
					break;
				case 3:
					g_posObstacle.x = 60.0f;		
					break;
				}

				//****ワールドの設定****
				D3DXMatrixIdentity(&g_mtxWorldObstacle);
				D3DXMatrixScaling(&mtxScl,g_sclObstacle.x,
											g_sclObstacle.y,
											g_sclObstacle.z);			//スケールを反映

				D3DXMatrixMultiply(&g_mtxWorldObstacle,&g_mtxWorldObstacle,&mtxScl);

				//****その他の設定****
				D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotObstacle[nCnt].y,
												g_rotObstacle[nCnt].x,
												g_rotObstacle[nCnt].z);		//ヨ－　ピッチ　ロール

				D3DXMatrixMultiply(&g_mtxWorldObstacle,&g_mtxWorldObstacle,&mtxRot);
				D3DXMatrixTranslation(&mtxTranslate,g_posObstacle.x,g_posObstacle.y,g_posObstacle.z);	//位置を反映
				D3DXMatrixMultiply(&g_mtxWorldObstacle,&g_mtxWorldObstacle,&mtxTranslate);
	
				pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldObstacle);	//設定

				//=========マテリアルなどの取得=========
				//======================================
				pDevice -> GetMaterial(&matDef);
				pMat = (D3DXMATERIAL*)g_pBuffMatObstacle -> GetBufferPointer();

				for(int nCntMat = 0;nCntMat < (int)g_numMatObstacle;nCntMat++)
				{
					pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
					pDevice -> SetTexture(0,NULL);
					g_pMeshObstacle -> DrawSubset(nCntMat);
				}

				pDevice -> SetMaterial(&matDef);
			}
		}
	}
}

//================================
//位置と角度の取得関数
//================================

PLAYER_MODE GetObstacle_info(int num)
{
	return Obstacle_info[num];
}

