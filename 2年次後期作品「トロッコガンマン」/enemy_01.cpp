//◇-------------------------------------------------------------------------◇
//
//	File	:敵01処理ファイル[Enemy01.cpp]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "enemy_01.h"
#include "obstacle.h"
#include "sound.h"
#include "model.h"
#include "camera.h"
#include "score.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 g_pTextureEnemy01;		//
LPD3DXMESH g_pMeshEnemy01;					//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatEnemy01;				//マテリアル情報へのポインタ

DWORD g_numMatEnemy01;						//マテリアルの数
D3DXVECTOR3 g_posEnemy01;					//モデルの位置
D3DXVECTOR3 g_rotEnemy01;					//モデルの向き
D3DXVECTOR3 g_sclEnemy01;					//モデルの大きさ

D3DXMATRIX g_mtxWorldEnemy01;				//ワールドマトリックス

PLAYER_MODE Enemy01_info[ENEMY01_NUM];		//敵01の障害物の入れ子

//◇-------------------------------------------------------------------------◇
//モデルの初期化処理
//◇-------------------------------------------------------------------------◇
void InitEnemy01(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//障害物の座標を入れる　Ｘ軸
	int Enemy01_posX_ORIGINAL[ENEMY01_NUM] = {0,0,0,0,0,0,0,0,0,0,2,1,0,0,3,0,1,2,0,1,		//0~19
											2,0,1,3,0,0,0,0,3,0,1,0,0,0,1,2,3,1,3,0,		//20~39
											2,0,3,1,2,1,3,0,1,2,							//40~49
											2,0,1,2,0,1,2,3,0,0,							//50~59
											3,2,1,1,3,0,0,3,2,1,
											0,3,0,0,3,0,2,2,0,0,
											2,3,1,1,3,0,2,0,0,1,
											0,0,0,0,0,0,0,0,0,0};
	//障害物の座標　改変しない　Ｚ軸
	float Enemy01_posZ_ORIGINAL[ENEMY01_NUM] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,				//0~19
												0,0,600,0,0,0,0,0,0,0,0,600,0,-600,0,0,0,0,-600,0,		//20~39
												0,0,0,0,-600,0,0,0,0,-600,								//40~49
												0,0,0,0,0,600,0,-600,0,0,								//50~59
												0,0,0,0,-600,0,0,0,600,0,
												0,0,0,0,0,0,0,0,0,0,
												0,0,0,600,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,0};

	for(int nCnt = 0;nCnt < ENEMY01_NUM;nCnt++)
	{
		//障害物の位置を入れる
		Enemy01_info[nCnt].LR_Judge = Enemy01_posX_ORIGINAL[nCnt];
		Enemy01_info[nCnt].MOTO_pos.z = Enemy01_posZ_ORIGINAL[nCnt];

		//障害物の表示判定を入れる
//		Enemy01_info[nCnt].Thing_exist = Enemy01_Exist_ORIGINAL[nCnt];

		if(Enemy01_posX_ORIGINAL[nCnt] != 0)
		{
			Enemy01_info[nCnt].Thing_exist = true;
		}
		else
		{
			Enemy01_info[nCnt].Thing_exist = false;
		}

		//数値の簡略化　障害物設置開始位置をプラス,間隔をあけていく
		Enemy01_info[nCnt].MOTO_pos.z = Enemy01_info[nCnt].MOTO_pos.z + OBSTACLE_SETTI_LINE + nCnt * 600;

		//敵01のHPを入れる
		Enemy01_info[nCnt].Enemy_Damage = 4;
	}
	
	//****モデルの情報セット****
	D3DXLoadMeshFromX("./data/MODEL/obake_000.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatEnemy01,
					NULL,
					&g_numMatEnemy01,
					&g_pMeshEnemy01);

	//****位置、角度、スケールの初期化****
	g_posEnemy01 = D3DXVECTOR3(40.0f,20.0f,OBSTACLE_SETTI_LINE+500.0f);
	g_rotEnemy01 = D3DXVECTOR3(0.0f,D3DX_PI,0.0f);
	g_sclEnemy01 = D3DXVECTOR3(1.0f,1.0f,1.0f);
}
//◇-------------------------------------------------------------------------◇
//モデルの終了処理
//◇-------------------------------------------------------------------------◇
void UninitEnemy01(void)
{
	//メッシュモデルのリリース
	//==============================
	if(g_pMeshEnemy01 != NULL)
	{
		g_pMeshEnemy01 -> Release();
		g_pMeshEnemy01 = NULL;
	}
	
	//バッファマットのリリース
	//=============================
	if(g_pBuffMatEnemy01 != NULL)
	{
		g_pBuffMatEnemy01 -> Release();
		g_pBuffMatEnemy01 = NULL;
	}

	//テクステャのリリース
	//=============================
	if(g_pTextureEnemy01 != NULL)
	{
		g_pTextureEnemy01 -> Release();
		g_pTextureEnemy01 = NULL;

	}
}
//◇-------------------------------------------------------------------------◇
//モデルの更新処理
//◇-------------------------------------------------------------------------◇
void UpdateEnemy01(void)
{
	//ダメージ処理
	for(int nCnt = 0;nCnt < ENEMY01_NUM;nCnt++)
	{
		//体力が0以下になるかどうか
		if(Enemy01_info[nCnt].Enemy_Damage <= 0)
		{
//			PlaySound(SOUND_LABEL_SE_SHOT);
			//敵01の表示を消す
			Enemy01_info[nCnt].Thing_exist = false;

			PlusScore(1000);


			Enemy01_info[nCnt].Enemy_Damage = 4;
		}
	}	
}
//◇-------------------------------------------------------------------------◇
//モデルの描画処理
//◇-------------------------------------------------------------------------◇
void DrawEnemy01(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//マットのデフォルト
	//障害物の数だけ繰り返す
	for(int nCnt = 0;nCnt < ENEMY01_NUM;nCnt++)
	{
		if(Enemy01_info[nCnt].Thing_exist == true)
		{
			//見える位置のみ表示するために、表示の範囲内だったら描画するようにする
			if(Getg_posModel().z - CAMERA_LONG < Enemy01_info[nCnt].MOTO_pos.z && Getg_posModel().z + CAMERA_LONG > Enemy01_info[nCnt].MOTO_pos.z)
			{
				g_posEnemy01.z = Enemy01_info[nCnt].MOTO_pos.z;

				switch(Enemy01_info[nCnt].LR_Judge)
				{
				case 1:
					g_posEnemy01.x = -60.0f;
					break;
				case 2:
					g_posEnemy01.x = 0.0f;
					break;
				case 3:
					g_posEnemy01.x = 60.0f;		
					break;
				}

				//****ワールドの設定****
				D3DXMatrixIdentity(&g_mtxWorldEnemy01);
				D3DXMatrixScaling(&mtxScl,g_sclEnemy01.x,
											g_sclEnemy01.y,
											g_sclEnemy01.z);			//スケールを反映

				D3DXMatrixMultiply(&g_mtxWorldEnemy01,&g_mtxWorldEnemy01,&mtxScl);

				//****その他の設定****
				D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotEnemy01.y,
												g_rotEnemy01.x,
												g_rotEnemy01.z);		//ヨ－　ピッチ　ロール

				D3DXMatrixMultiply(&g_mtxWorldEnemy01,&g_mtxWorldEnemy01,&mtxRot);
				D3DXMatrixTranslation(&mtxTranslate,g_posEnemy01.x,g_posEnemy01.y,g_posEnemy01.z);	//位置を反映
				D3DXMatrixMultiply(&g_mtxWorldEnemy01,&g_mtxWorldEnemy01,&mtxTranslate);
	
				pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldEnemy01);	//設定

				//=========マテリアルなどの取得=========
				//======================================
				pDevice -> GetMaterial(&matDef);
				pMat = (D3DXMATERIAL*)g_pBuffMatEnemy01 -> GetBufferPointer();

				for(int nCntMat = 0;nCntMat < (int)g_numMatEnemy01;nCntMat++)
				{
					pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
					pDevice -> SetTexture(0,NULL);
					g_pMeshEnemy01 -> DrawSubset(nCntMat);
				}

				pDevice -> SetMaterial(&matDef);
			}
		}
	}
}
//======================================
//敵01の基準情報の受け渡し関数
//======================================
PLAYER_MODE GetEnemy01_info(int num)
{
	return Enemy01_info[num];
}

//敵01のダメージ処理。これを使うと体力が1減る
void Enemy01_DamageCnt(int num)
{
	Enemy01_info[num].Enemy_Damage--;
}