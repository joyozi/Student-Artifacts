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
#include "model.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "meshfield.h"
#include "gameUI.h"
#include "obstacle.h"
#include "enemy_01.h"
#include "barricade.h"
#include "sound.h"
#include "fade.h"
#include "result.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 g_pTextureModel[MODEL_NUM];		//
LPD3DXMESH g_pMeshModel[MODEL_NUM];					//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatModel[MODEL_NUM];			//マテリアル情報へのポインタ

DWORD g_numMatModel[MODEL_NUM];						//マテリアルの数
D3DXVECTOR3 g_posModel[MODEL_NUM];					//モデルの位置
D3DXVECTOR3 g_rotModel[MODEL_NUM];					//モデルの向き
D3DXVECTOR3 g_sclModel[MODEL_NUM];					//モデルの大きさ

D3DXMATRIX g_mtxWorldModel[MODEL_NUM];				//ワールドマトリックス

D3DXMATRIX g_mtxWorldPlayer[MODEL_NUM];				//プレイヤーマトリックス	5番がモデルだったらg_mtxWorldPlayer[5]に親の位置を保存しておく

D3DXMATRIX p_GetTranslate[MODEL_NUM];				//モデルの位置情報のみを保存する関数　銃の発射位置に用いる

int model_jump;										//ジャンプの判定　0で接地中　1でジャンプ飛び上がり中　2で落下中

float Model_SpeedUP;								//本体のスピードアップ用の変数

PLAYER_MODE p_Model_Original;						//モデルのオリジナルの情報
//◇-------------------------------------------------------------------------◇
//モデルの初期化処理
//◇-------------------------------------------------------------------------◇
void InitModel(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//ジャンプ状態の初期化
	model_jump = 0;

	//スピードアップの初期化
	Model_SpeedUP = 0.0f;

	//PLAYER_MODEの初期化
	p_Model_Original.Jump_Judge = false;	//ジャンプしていない
	p_Model_Original.LR_Judge = 2;			//中心にいる

	p_Model_Original.Model_Muteki = 1;		//モデルは通常状態である

	//****モデルの情報セット****

	//トロッコのモデル設置	親である
	D3DXLoadMeshFromX("./data/MODEL/000_torokko.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[0],
					NULL,
					&g_numMatModel[0],
					&g_pMeshModel[0]);

	//****位置、角度、スケールの初期化****
	g_posModel[0] = D3DXVECTOR3(0.0f,8.0f,0.0f);
	g_rotModel[0] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclModel[0] = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//胴体、頭のモデル設置	親はトロッコ
	D3DXLoadMeshFromX("./data/MODEL/001_body.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[1],
					NULL,
					&g_numMatModel[1],
					&g_pMeshModel[1]);

	//****位置、角度、スケールの初期化****
	g_posModel[1] = D3DXVECTOR3(0.0f,15.0f,0.0f);
	g_rotModel[1] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclModel[1] = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//前輪のモデル設置	親はトロッコ
	D3DXLoadMeshFromX("./data/MODEL/002_zenrin.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[2],
					NULL,
					&g_numMatModel[2],
					&g_pMeshModel[2]);

	//****位置、角度、スケールの初期化****
	g_posModel[2] = D3DXVECTOR3(0.0f,3.0f,13.0f);
	g_rotModel[2] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclModel[2] = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//後輪のモデル設置	親はトロッコ
	D3DXLoadMeshFromX("./data/MODEL/003_kourin.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[3],
					NULL,
					&g_numMatModel[3],
					&g_pMeshModel[3]);

	//****位置、角度、スケールの初期化****
	g_posModel[3] = D3DXVECTOR3(0.0f,3.0f,-13.0f);
	g_rotModel[3] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclModel[3] = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//左二の腕のモデル設置	親は胴体
	D3DXLoadMeshFromX("./data/MODEL/004_ninoudeL.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[4],
					NULL,
					&g_numMatModel[4],
					&g_pMeshModel[4]);

	//****位置、角度、スケールの初期化****
	g_posModel[4] = D3DXVECTOR3(-3.0f,20.0f,0.0f);
	g_rotModel[4] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclModel[4] = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//右二の腕のモデル設置	親は胴体
	D3DXLoadMeshFromX("./data/MODEL/005_ninoudeR.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[5],
					NULL,
					&g_numMatModel[5],
					&g_pMeshModel[5]);

	//****位置、角度、スケールの初期化****
	g_posModel[5] = D3DXVECTOR3(3.0f,20.0f,0.0f);
	g_rotModel[5] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclModel[5] = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//左手の銃のモデル設置	親は左二の腕
	D3DXLoadMeshFromX("./data/MODEL/006_juuL.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[6],
					NULL,
					&g_numMatModel[6],
					&g_pMeshModel[6]);

	//****位置、角度、スケールの初期化****
	g_posModel[6] = D3DXVECTOR3(-12.0f,1.6f,8.3f);
	g_rotModel[6] = D3DXVECTOR3(-D3DX_PI / 2,0.0f,0.0f);
	g_sclModel[6] = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//右手の銃のモデル設置	親は右二の腕
	D3DXLoadMeshFromX("./data/MODEL/007_juuR.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[7],
					NULL,
					&g_numMatModel[7],
					&g_pMeshModel[7]);

	//****位置、角度、スケールの初期化****
	g_posModel[7] = D3DXVECTOR3(12.0f,1.6f,8.3f);
	g_rotModel[7] = D3DXVECTOR3(-D3DX_PI / 2,0.0f,0.0f);
	g_sclModel[7] = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//右手の銃のモデル設置	親は右二の腕
	D3DXLoadMeshFromX("./data/MODEL/008_head.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel[8],
					NULL,
					&g_numMatModel[8],
					&g_pMeshModel[8]);

	//****位置、角度、スケールの初期化****
	g_posModel[8] = D3DXVECTOR3(0.0f,25.0f,0.0f);
	g_rotModel[8] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclModel[8] = D3DXVECTOR3(1.0f,1.0f,1.0f);

}
//◇-------------------------------------------------------------------------◇
//モデルの終了処理
//◇-------------------------------------------------------------------------◇
void UninitModel(void)
{
	for(int nCnt = 0;nCnt < MODEL_NUM;nCnt++)
	{
		//メッシュモデルのリリース
		//==============================
		if(g_pMeshModel[nCnt] != NULL)
		{
			g_pMeshModel[nCnt] -> Release();
			g_pMeshModel[nCnt] = NULL;
		}
	
		//バッファマットのリリース
		//=============================
		if(g_pBuffMatModel[nCnt] != NULL)
		{
			g_pBuffMatModel[nCnt] -> Release();
			g_pBuffMatModel[nCnt] = NULL;
		}

		//テクステャのリリース
		//=============================
		if(g_pTextureModel[nCnt] != NULL)
		{
			g_pTextureModel[nCnt] -> Release();
			g_pTextureModel[nCnt] = NULL;
		}
	}
}
//◇-------------------------------------------------------------------------◇
//モデルの更新処理
//◇-------------------------------------------------------------------------◇
void UpdateModel(void)
{
	static float jump = 0.0f;	//ジャンプの慣性移動の計算用

	static int SpeedupCnt;

	//強引に初期化
	if(g_posModel[0].z <= OBSTACLE_SETTI_LINE)
	{
		SpeedupCnt = 1;
	}


	//ゴールの判定
	if(g_posModel[0].z >= MODEL_GOAL)
	{
		//ファンファーレ
		PlaySound(SOUND_LABEL_FANFALE);

		SetResultJudge(true);
		SetFade(FADE_OUT);
	}

	//スピードアップ
	if(g_posModel[0].z >= OBSTACLE_SETTI_LINE + (600 * 20 * SpeedupCnt))
	{
		Model_SpeedUP +=0.5f;
		SpeedupCnt++;
	}

#ifdef _DEBUG	//デバッグのときはキー入力で移動
	if(GetKeyboardPress(DIK_W) == true)
#endif

	{
		//前進する
		g_posModel[0].z += MODEL_MOVE + Model_SpeedUP;
	}
#ifdef _DEBUG	//デバッグのときはキー入力で移動
	if(GetKeyboardPress(DIK_S) == true)
	{
		//前進する
		g_posModel[0].z -= MODEL_MOVE + Model_SpeedUP;
	}
#endif

	//タイヤを回す
	g_rotModel[2].x += MODE_WHEEL_ROT;
	g_rotModel[3].x += MODE_WHEEL_ROT;

	if(model_jump == 0)
	{
		//左に傾ける
		if(GetKeyboardPress(DIK_A) == true)
		{
			//左に傾けていると教える
			p_Model_Original.LR_Judge = 1;
		
			//トロッコを斜めにする
			g_posModel[0].x = -15.0f;
			g_posModel[0].y = 33.0f;
			g_rotModel[0].z = 1.2f;

			//身体の位置をずらす
			g_posModel[1].x = 0.0f;
			g_posModel[1].y = 25.0f;
			g_rotModel[1].z = -0.7f;

			//二の腕、頭の角度を変える
			g_rotModel[4].z = -0.4f;
			g_rotModel[5].z = -0.15f;
			g_rotModel[8].z = -0.4f;
		}

		else if(GetKeyboardPress(DIK_D) == true)
		{
			//右に傾けていると教える
			p_Model_Original.LR_Judge = 3;

			//トロッコを斜めにする
			g_posModel[0].x = 15.0f;
			g_posModel[0].y = 33.0f;
			g_rotModel[0].z = -1.2f;

			//身体の位置をずらす
			g_posModel[1].x = 0.0f;
			g_posModel[1].y = 25.0f;
			g_rotModel[1].z = 0.7f;

			//二の腕、頭の角度を変える
			g_rotModel[4].z = 0.15f;
			g_rotModel[5].z = 0.4f;
			g_rotModel[8].z = 0.4f;
		}
		else
		{
			//傾いていないと教える
			p_Model_Original.LR_Judge = 2;

			//トロッコの位置を元に戻す
			g_posModel[0].x = 0.0f;
			g_posModel[0].y = 8.0f;
			g_rotModel[0].z = 0.0f;

			//本体を元に戻す
			g_posModel[1].x = 0.0f;
			g_posModel[1].y = 15.0f;
			g_rotModel[1].z = 0.0f;

			//二の腕、頭の角度を元に戻す
			g_rotModel[4].z = 0.0f;
			g_rotModel[5].z = 0.0f;
			g_rotModel[8].z = 0.0f;

			//無敵状態の設定から元に戻す
			g_rotModel[0].x =0.0f;

		}
	}

	//腕の上下移動
	if(GetKeyboardPress(DIK_RETURN) == true)
	{
		if(g_rotModel[6].x < 0.0f)
		{
			g_rotModel[6].x += D3DX_PI / 6;
		}

		if(g_rotModel[7].x < 0.0f)
		{
			g_rotModel[7].x += D3DX_PI / 6;
		}
	}
	else
	{
		if(g_rotModel[6].x > -D3DX_PI / 2)
		{
			g_rotModel[6].x -= D3DX_PI / 6;
		}

		if(g_rotModel[7].x > -D3DX_PI / 2)
		{
			g_rotModel[7].x -= D3DX_PI / 6;
		}
	}

	if(p_Model_Original.Jump_Judge == true)
	{
		//ジャンプしているときは、左右に位置をずらせない
		//ジャンプしていると教える
		p_Model_Original.Jump_Judge = true;
	}

	//ジャンプモーション
	if(model_jump == 0)
	{
		if(GetKeyboardTrigger(DIK_SPACE) == true)
		{
			//傾いていないと教える
			p_Model_Original.LR_Judge = 2;

			//*********中心でしかジャンプできない************
			//トロッコの位置を元に戻す
			g_posModel[0].x = 0.0f;
			g_posModel[0].y = 8.0f;
			g_rotModel[0].z = 0.0f;

			//本体を元に戻す
			g_posModel[1].x = 0.0f;
			g_posModel[1].y = 15.0f;
			g_rotModel[1].z = 0.0f;

			//二の腕、頭の角度を元に戻す
			g_rotModel[4].z = 0.0f;
			g_rotModel[5].z = 0.0f;
			g_rotModel[8].z = 0.0f;

			model_jump = 1;
			//ジャンプの初速を入れる
			jump = 12.0f;
		}
	}
	else if(model_jump == 1)	//ジャンプ上昇中
	{
		//ジャンプの重力によるジャンプ速度を上げる
		jump = jump * 0.9f;
		g_posModel[0].y += jump;
		
		if(g_posModel[0].y >= 60.0f)
		{
			model_jump = 2;

			//落下を始める
			jump = 0.05f;
		}
	}
	else if(model_jump == 2)	//ジャンプ落下中
	{
		//落下速度を上げていく
		jump = jump * 1.15f;
		g_posModel[0].y -= jump;

		if(g_posModel[0].y <= 0.0f)
		{
			//ちょっと埋まるので修正する
			g_posModel[0].y= 0;
			model_jump = 0;

			//ジャンプが終わったと教える
			p_Model_Original.Jump_Judge = false;
		}
	}
//=======================================================
//無敵についての処理
//=======================================================

	static int MutekiCnt;	//無敵時間をカウントする変数	

	MutekiCnt++;			//ここでカウントする　どうせ通常時に0にするからいい

	switch(p_Model_Original.Model_Muteki)
	{
	case 1:		//通常状態はMutekiCntをゼロにする
		MutekiCnt = 0;
		break;
	case 2:		//無敵、怯み状態

		//右辺の分だけ時間がたったら怯みから抜ける
		if(MutekiCnt >= 50)
		{
			p_Model_Original.Model_Muteki = 3;
			MutekiCnt = 0;
		}

		if(model_jump == 0)
		{	//接地中だったら真ん中である程度の硬直をする
			//-------------------------------------
			//トロッコの位置を元に戻す
			g_posModel[0].x = 0.0f;
			g_rotModel[0].z = 0.0f;

			//本体を元に戻す
			g_posModel[1].x = 0.0f;
			g_posModel[1].y = 15.0f;
			g_rotModel[1].z = 0.0f;

			//二の腕、頭の角度を元に戻す
			g_rotModel[4].z = 0.0f;
			g_rotModel[5].z = 0.0f;
			g_rotModel[8].z = 0.0f;

			g_posModel[0].y = 20.0f;
			g_rotModel[0].x = -0.5f;
			g_rotModel[6].x = -D3DX_PI / 2;
			g_rotModel[7].x = -D3DX_PI / 2;
			//--------------------------------------

		}
		else	//その他のジャンプ中だったらその位置でななめる
		{
			g_rotModel[0].x = -0.5f;
			g_rotModel[6].x = -D3DX_PI / 2;
			g_rotModel[7].x = -D3DX_PI / 2;
		}
		break;
	case 3:

		//無敵状態の設定から元に戻す
		g_rotModel[0].x =0.0f;

		//右辺の分だけ時間がたったら無敵時間を終える
		if(MutekiCnt >= 100)
		{
			p_Model_Original.Model_Muteki = 1;
		}
		break;
	}

	//最終的なモデルの位置を保存しておく
	p_Model_Original.MOTO_pos = g_posModel[0];
}
//◇-------------------------------------------------------------------------◇
//モデルの描画処理
//◇-------------------------------------------------------------------------◇
void DrawModel(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	static int p_Playernum = 0;		//プレイヤーの原点の代入されている番号。 g_mtxWorldPlayer[num]のこと

	D3DXMATRIX Player_mtxScl,Player_mtxRot,Player_mtxTranslate;		//原点のマトリックス用の変数
	
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//マットのデフォルト
	
	for(int nCnt = 0;nCnt < MODEL_NUM;nCnt++)
	{
		//****ワールドの設定****

		//==========マトリックスの初期化==========
		D3DXMatrixIdentity(&g_mtxWorldModel[nCnt]);

		//==========スケールの反映================
		D3DXMatrixScaling(&mtxScl,g_sclModel[nCnt].x,g_sclModel[nCnt].y,g_sclModel[nCnt].z);
		D3DXMatrixMultiply(&g_mtxWorldModel[nCnt],&g_mtxWorldModel[nCnt],&mtxScl);

		//==========角度の反映====================
		D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotModel[nCnt].y,g_rotModel[nCnt].x,g_rotModel[nCnt].z);		//ヨ－　ピッチ　ロール
		D3DXMatrixMultiply(&g_mtxWorldModel[nCnt],&g_mtxWorldModel[nCnt],&mtxRot);

		//=========位置の反映=====================
		D3DXMatrixTranslation(&mtxTranslate,g_posModel[nCnt].x,g_posModel[nCnt].y,g_posModel[nCnt].z);	//位置を反映
		D3DXMatrixMultiply(&g_mtxWorldModel[nCnt],&g_mtxWorldModel[nCnt],&mtxTranslate);

		//親のマトリックス　×　このマトリックスを行う。そうすることで原点についていくようになる
		//トロッコは原点(MDでいうNULL)だから反映させない!
		//トロッコが原点のとき
		if(nCnt == 1 || nCnt == 2 || nCnt == 3)
		{
			D3DXMatrixMultiply(&g_mtxWorldModel[nCnt],&g_mtxWorldModel[nCnt],&g_mtxWorldPlayer[0]);
		}

		//胴体が原点のとき
		else if(nCnt == 4 || nCnt == 5 || nCnt == 8)
		{
			D3DXMatrixMultiply(&g_mtxWorldModel[nCnt],&g_mtxWorldModel[nCnt],&g_mtxWorldPlayer[1]);
		}

		//左二の腕が原点のとき
		else if(nCnt == 6)
		{
			D3DXMatrixMultiply(&g_mtxWorldModel[nCnt],&g_mtxWorldModel[nCnt],&g_mtxWorldPlayer[4]);
		}
		
		//右二の腕が原点のとき
		else if(nCnt == 7)
		{
			D3DXMatrixMultiply(&g_mtxWorldModel[nCnt],&g_mtxWorldModel[nCnt],&g_mtxWorldPlayer[5]);
		}
		
		//原点のコピーを取っておく 左右の銃は、弾発射のための位置の保存
		if(nCnt == 0 /*親はトロッコ*/|| nCnt == 1/*身体*/ || nCnt == 4/*左二の腕*/ || nCnt == 5/*右二の腕*/ || nCnt == 6/*左二の腕*/ || nCnt == 7/*右二の腕*/)
		{
			//親の原点をコピーしておく
			g_mtxWorldPlayer[nCnt] = g_mtxWorldModel[nCnt];
		}

		//BULLET処理のために
		//左銃と右銃の位置情報を保存する
		if(nCnt == 6)
		{
			D3DXMatrixMultiply(&mtxTranslate,&mtxTranslate,&g_mtxWorldPlayer[4]);
			p_GetTranslate[6] = mtxTranslate;
		}
		//右銃の保存
		if(nCnt == 7)
		{
			D3DXMatrixMultiply(&mtxTranslate,&mtxTranslate,&g_mtxWorldPlayer[5]);
			p_GetTranslate[7] = mtxTranslate;
		}


		//=========情報のセット===================
		pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldModel[nCnt]);	//設定


		//無敵状態のときは点滅させる
		static int Muteki_DisplayCnt;			//点滅のカウント
		if(p_Model_Original.Model_Muteki == 1)
		{
			Muteki_DisplayCnt = 0;

			//=========マテリアルなどの取得=========
			//======================================
			pDevice -> GetMaterial(&matDef);
			pMat = (D3DXMATERIAL*)g_pBuffMatModel[nCnt] -> GetBufferPointer();

			for(int nCntMat = 0;nCntMat < (int)g_numMatModel[nCnt];nCntMat++)
			{
				pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
				pDevice -> SetTexture(0,NULL);
				g_pMeshModel[nCnt] -> DrawSubset(nCntMat);
			}

			pDevice -> SetMaterial(&matDef);

		}
		else if(p_Model_Original.Model_Muteki != 1)
		{
			Muteki_DisplayCnt++;

			if(Muteki_DisplayCnt % 120 >= 60)
			{
				//=========マテリアルなどの取得=========
				//======================================
				pDevice -> GetMaterial(&matDef);
				pMat = (D3DXMATERIAL*)g_pBuffMatModel[nCnt] -> GetBufferPointer();

				for(int nCntMat = 0;nCntMat < (int)g_numMatModel[nCnt];nCntMat++)
				{
					pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
					pDevice -> SetTexture(0,NULL);
					g_pMeshModel[nCnt] -> DrawSubset(nCntMat);
				}

				pDevice -> SetMaterial(&matDef);
			}
		}
	}
}

//=====================================
//本体のあたり判定
//=====================================
void ModelHITJUDGE(void)
{
	PLAYER_MODE Model_JudgeIreko;		//本体のあたり判定に用いる入れ子

	//通常状態のときだけあたり判定を行う
	if(p_Model_Original.Model_Muteki == 1)
	{

		//まず、岩とのあたり判定
		//障害物の数だけ繰り返す
		for(int ObjectCnt = 0;ObjectCnt < OBSTACLE_NUM;ObjectCnt++)
		{
			//障害物の位置情報を入れる
			Model_JudgeIreko = GetObstacle_info(ObjectCnt);

			//正なら判定を行う
			if(Model_JudgeIreko.Thing_exist == true)
			{
				//まず、Z軸のあたり判定  
				if(g_posModel[0].z >= Model_JudgeIreko.MOTO_pos.z - 60 &&
					g_posModel[0].z <= Model_JudgeIreko.MOTO_pos.z + 30)
				{
					//X軸のあたり判定
					if(p_Model_Original.LR_Judge == Model_JudgeIreko.LR_Judge)
					{
						//ここまで来ると当ってるのでその処理をする
						PlaySound(SOUND_LABEL_DAMAGE_SE);
						p_Model_Original.Model_Muteki = 2;			//無敵にする
						HitPointCNT();								//ダメージを食らう
					}
				}
			}
		}

		//敵01とのあたり判定
		//敵01の数だけ繰り返す
		for(int Enemy01Cnt = 0;Enemy01Cnt < ENEMY01_NUM;Enemy01Cnt++)
		{
			//障害物の位置情報を入れる
			Model_JudgeIreko = GetEnemy01_info(Enemy01Cnt);

			//正なら判定を行う
			if(Model_JudgeIreko.Thing_exist == true)
			{
				//まず、Z軸のあたり判定  
				if(g_posModel[0].z >= Model_JudgeIreko.MOTO_pos.z - 60 &&
					g_posModel[0].z <= Model_JudgeIreko.MOTO_pos.z + 30)
				{
					//X軸のあたり判定
					if(p_Model_Original.LR_Judge == Model_JudgeIreko.LR_Judge)
					{
						//ここまで来ると当ってるのでその処理をする
						PlaySound(SOUND_LABEL_DAMAGE_SE);
						p_Model_Original.Model_Muteki = 2;			//無敵にする
						HitPointCNT();								//ダメージを食らう
					}
				}
			}
		}

		//バリケードとのあたり判定。Z軸とY軸を比べる
		for(int BarricadeCnt = 0;BarricadeCnt < BARRICADE_NUM;BarricadeCnt++)
		{
			//障害物の位置情報を入れる
			Model_JudgeIreko = GetBarricade_info(BarricadeCnt);

			//正なら判定を行う
			if(Model_JudgeIreko.Thing_exist == true)
			{
				//まず、Z軸のあたり判定  
				if(g_posModel[0].z >= Model_JudgeIreko.MOTO_pos.z - 20 &&
					g_posModel[0].z <= Model_JudgeIreko.MOTO_pos.z + 20)
				{
					//Y軸のあたり判定　本体が一定の高さ未満だったら当たる
					if(g_posModel[0].y < 45.0f)
					{
						//ここまで来ると当ってるのでその処理をする
						p_Model_Original.Model_Muteki = 2;			//無敵にする
						HitPointCNT();								//ダメージを食らう
					}
				}
			}
		}
	}
}

//================================
//位置と角度の取得関数
//================================
D3DXVECTOR3 Getg_posModel(void)
{
	//親モデルの位置を教える
	return g_posModel[0];
}

D3DXVECTOR3 Getg_rotModel(void)
{
	//親モデルの角度を教える
	return g_rotModel[0];
}

//左の銃の位置の取得関数　基本的にバレットで使う
D3DXMATRIX GetTranslate_juuL(void)
{
	return p_GetTranslate[6];
}

//右の銃の位置の取得関数
D3DXMATRIX GetTranslate_juuR(void)
{
	return p_GetTranslate[7];
}

//あたり判定とかのために位置を教える関数
PLAYER_MODE GetModelOriginal(void)
{
	return p_Model_Original;
}

//バレットに持っていくスピードアップ変数
float GetModel_SpeedUP(void)
{
	return Model_SpeedUP;
}
