//◇-------------------------------------------------------------------------◇
//
//	File	:バリケード処理ファイル[Barricade.cpp]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "barricade.h"
#include "obstacle.h"
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
LPDIRECT3DTEXTURE9 g_pTextureBarricade;			//
LPD3DXMESH g_pMeshBarricade;					//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatBarricade;				//マテリアル情報へのポインタ

DWORD g_numMatBarricade;						//マテリアルの数
D3DXVECTOR3 g_posBarricade;						//モデルの位置
D3DXVECTOR3 g_rotBarricade;						//モデルの向き
D3DXVECTOR3 g_sclBarricade;						//モデルの大きさ

D3DXMATRIX g_mtxWorldBarricade;					//ワールドマトリックス

PLAYER_MODE Barricade_info[BARRICADE_NUM];		//敵01の障害物の入れ子

//◇-------------------------------------------------------------------------◇
//モデルの初期化処理
//◇-------------------------------------------------------------------------◇
void InitBarricade(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//障害物の座標を入れる　Ｘ軸
	int Barricade_posX_ORIGINAL[BARRICADE_NUM] = {2,1};
	//障害物の座標　改変しない　Ｚ軸
	float Barricade_posZ_ORIGINAL[BARRICADE_NUM] = {0,0,0,0,0,0,0,0,0,0,600,600,0,0,600,0,0,0,0,0};

	//障害物を表示させるかどうかの正否
	bool Barricade_Exist_ORIGINAL[BARRICADE_NUM] = {false,false,true,false,false,true,false,true,true ,true ,
													true ,true ,false,false,true ,true ,false,false,false,false};

	for(int nCnt = 0;nCnt < BARRICADE_NUM;nCnt++)
	{
		//障害物の位置を入れる
//		Barricade_info[nCnt].LR_Judge = Barricade_posX_ORIGINAL[nCnt];
		Barricade_info[nCnt].LR_Judge = 0;										//左右関係ないので0を入れる
		Barricade_info[nCnt].MOTO_pos.z = Barricade_posZ_ORIGINAL[nCnt];

		//障害物の表示判定を入れる
		Barricade_info[nCnt].Thing_exist = Barricade_Exist_ORIGINAL[nCnt];

		//数値の簡略化　障害物設置開始位置をプラス,間隔をあけていく
		Barricade_info[nCnt].MOTO_pos.z = Barricade_info[nCnt].MOTO_pos.z + OBSTACLE_SETTI_LINE + nCnt * 3000 + 600;
	}
	
	//****モデルの情報セット****
	D3DXLoadMeshFromX("./data/MODEL/barricade_000.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatBarricade,
					NULL,
					&g_numMatBarricade,
					&g_pMeshBarricade);

	//****位置、角度、スケールの初期化****
	g_posBarricade = D3DXVECTOR3(0.0f,0.0f,500.0f);
	g_rotBarricade = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclBarricade = D3DXVECTOR3(1.0f,1.0f,1.0f);
}
//◇-------------------------------------------------------------------------◇
//モデルの終了処理
//◇-------------------------------------------------------------------------◇
void UninitBarricade(void)
{
	//メッシュモデルのリリース
	//==============================
	if(g_pMeshBarricade != NULL)
	{
		g_pMeshBarricade -> Release();
		g_pMeshBarricade = NULL;
	}
	
	//バッファマットのリリース
	//=============================
	if(g_pBuffMatBarricade != NULL)
	{
		g_pBuffMatBarricade -> Release();
		g_pBuffMatBarricade = NULL;
	}

	//テクステャのリリース
	//=============================
	if(g_pTextureBarricade != NULL)
	{
		g_pTextureBarricade -> Release();
		g_pTextureBarricade = NULL;

	}
}
//◇-------------------------------------------------------------------------◇
//モデルの更新処理
//◇-------------------------------------------------------------------------◇
void UpdateBarricade(void)
{
	
}
//◇-------------------------------------------------------------------------◇
//モデルの描画処理
//◇-------------------------------------------------------------------------◇
void DrawBarricade(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//マットのデフォルト
	
	//障害物の数だけ繰り返す
	for(int nCnt = 0;nCnt < BARRICADE_NUM;nCnt++)
	{
		if(Barricade_info[nCnt].Thing_exist == true)
		{
			//見える位置のみ表示するために、表示の範囲内だったら描画するようにする
			if(Getg_posModel().z - CAMERA_LONG < Barricade_info[nCnt].MOTO_pos.z && Getg_posModel().z + CAMERA_LONG > Barricade_info[nCnt].MOTO_pos.z)
			{
				g_posBarricade.z = Barricade_info[nCnt].MOTO_pos.z;
			
				//****ワールドの設定****
				D3DXMatrixIdentity(&g_mtxWorldBarricade);
				D3DXMatrixScaling(&mtxScl,g_sclBarricade.x,	g_sclBarricade.y,g_sclBarricade.z);			//スケールを反映

				D3DXMatrixMultiply(&g_mtxWorldBarricade,&g_mtxWorldBarricade,&mtxScl);

				//****その他の設定****
				D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotBarricade.y,g_rotBarricade.x,g_rotBarricade.z);		//ヨ－　ピッチ　ロール

				D3DXMatrixMultiply(&g_mtxWorldBarricade,&g_mtxWorldBarricade,&mtxRot);
				D3DXMatrixTranslation(&mtxTranslate,g_posBarricade.x,g_posBarricade.y,g_posBarricade.z);	//位置を反映
				D3DXMatrixMultiply(&g_mtxWorldBarricade,&g_mtxWorldBarricade,&mtxTranslate);
	
				pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldBarricade);	//設定

				//=========マテリアルなどの取得=========
				//======================================
				pDevice -> GetMaterial(&matDef);
 				pMat = (D3DXMATERIAL*)g_pBuffMatBarricade -> GetBufferPointer();

				for(int nCntMat = 0;nCntMat < (int)g_numMatBarricade;nCntMat++)
				{
					pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
					pDevice -> SetTexture(0,NULL);
					g_pMeshBarricade -> DrawSubset(nCntMat);
				}

				pDevice -> SetMaterial(&matDef);
			}
		}
	}
}
//======================================
//敵01の基準情報の受け渡し関数
//======================================
PLAYER_MODE GetBarricade_info(int num)
{
	return Barricade_info[num];
}
