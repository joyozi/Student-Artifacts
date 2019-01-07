//◇-------------------------------------------------------------------------◇
//
//	File	:メッシュカーブファイル[meshcave.cpp]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "meshcave.h"
#include "model.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇		

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 g_pTextureMeshCave;				//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCave;		//

LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCave;			//

D3DXVECTOR3 g_posMeshCave;						//モデルの位置
D3DXVECTOR3 g_rotMeshCave;						//モデルの向き
D3DXVECTOR3 g_sclMeshCave;						//モデルの大きさ

D3DXMATRIX g_mtxProjectionMeshCave;			//プロジェクションマトリックス
D3DXMATRIX g_mtxViewMeshCave;					//ビューマトリックス
D3DXMATRIX g_mtxWorldMeshCave;					//ワールドマトリックス

D3DXVECTOR3 g_posMeshCaveP;					//カメラの視点
D3DXVECTOR3 g_posMeshCaveR;					//カメラの注視点
D3DXVECTOR3 g_posMeshCaveU;					//カメラの上方向ベクトル

//◇-------------------------------------------------------------------------◇
//メッシュカーブ初期化処理
//◇-------------------------------------------------------------------------◇
void InitMeshCave(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	VERTEX_3D *pVtx;

	WORD *pIdx;
	
	//****位置、角度、スケールの初期化****
	g_posMeshCave = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_rotMeshCave = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclMeshCave = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//***カメラの初期化***
	g_posMeshCaveP = D3DXVECTOR3(0.0f,0.0f,0.0f);		//カメラの視点
	g_posMeshCaveR = D3DXVECTOR3(0.0f,0.0f,0.0f);		//カメラの注視点
	g_posMeshCaveU = D3DXVECTOR3(0.0f,1.0f,0.0f);		//カメラの上方向ベクトル


	//***テクステャの読み込み***
	D3DXCreateTextureFromFile(GetDevice(),CAVE_TEXTURE_FILE,&g_pTextureMeshCave);

	//***頂点情報の設定***
	//****頂点バッファの設定****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*CAVE_MESH_VTX_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffMeshCave,NULL);

	//****インデックスバッファの確保****
	pDevice -> CreateIndexBuffer(sizeof(WORD) * CAVE_MESH_INDEX_NUM,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&g_pIdxBuffMeshCave,NULL);

	//===================頂点バッファデータをロック==========================
	g_pVtxBuffMeshCave->Lock(0,0,(void**)&pVtx,0);
	
	//****頂点の位置の設定****
//	int ChangeCntX = 0;																			//縦軸の切り替えのときに使用する変数
	int ChangeCntZ = 0;
	float VtxCntx = (CAVE_MESH_TYOKKEI / 2) - (CAVE_MESH_POYGON_LENGTH * CAVE_TYOKUSEN);		//X軸の一番右の座標
	float VtxCnty = 0;																			//Y軸
	float VtxCntz = (CAVE_MESH_OKU_LONG / 2);													//Z軸の一番奥の座標

	float cave_rad = 0.0f;																		//洞窟を曲げる角度
	int cave_Cnt = 0;																			//洞窟の端を少し直線にするカウント

	//頂点数分繰り返す
	for(long nCnt = 0;nCnt < CAVE_MESH_VTX_NUM;nCnt++)
	{
		//最初に代入
		pVtx[nCnt].pos = D3DXVECTOR3(VtxCntx,VtxCnty,VtxCntz);


		//-----洞窟の端を直線にする-----------
		cave_Cnt++;
		//規定値の範囲内でのみ、Ｘ軸を変化させて洞窟の端を直線的にする
		if(cave_Cnt > CAVE_TYOKUSEN && cave_Cnt <= CAVE_MESH_TEXTURE_TYOKKEI - CAVE_TYOKUSEN)
		{	
			//X軸に左にシフト
			VtxCntx -= CAVE_MESH_TYOKKEI / CAVE_MESH_TEXTURE_TYOKKEI;
		}

		//Y軸の角度を変える
		cave_rad += D3DX_PI / (CAVE_MESH_TEXTURE_TYOKKEI);

		//y軸を変える
		VtxCnty = sinf(cave_rad) * (CAVE_MESH_TYOKKEI/2);
		
		ChangeCntZ++;

		//nCntが左端の数値に達したらXを左端の数値に戻して、Zを一つ下におろす。
		if(ChangeCntZ > CAVE_MESH_TEXTURE_TYOKKEI)
		{
			VtxCntx = (CAVE_MESH_TYOKKEI / 2) - (CAVE_MESH_POYGON_LENGTH * CAVE_TYOKUSEN);
			VtxCnty = 0;
			VtxCntz -= CAVE_MESH_POYGON_LENGTH;
			ChangeCntZ = 0;
			cave_Cnt = 0;
			cave_rad = 0.0f;
		}
	}



		//法線の設定の開始

	D3DXVECTOR3 Vec0;
	D3DXVECTOR3 Vec1;
	D3DXVECTOR3 normal;

	int VtxX = 0;		//X頂点用

	//左下が直角の三角形、右上が直角の三角形の順で交互にやっていく

	for(int nCntY = 0;nCntY < CAVE_MESH_TEXTURE_NUM_OKULONG;nCntY++)
	{	//Y軸の頂点数分繰り返す

		for(int nCntX = 0;nCntX < CAVE_MESH_TEXTURE_TYOKKEI * 2;nCntX++)
		{	//X軸の頂点数分繰り返す
			if(nCntX % 2 == 0)
			{
				//左下が直角の三角形
				Vec0 = pVtx[(nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1)) + VtxX + (CAVE_MESH_TEXTURE_TYOKKEI + 1)].pos - pVtx[(nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1)) + VtxX].pos;
				Vec1 = pVtx[(nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1)) + VtxX].pos - pVtx[(nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1)) + VtxX + (CAVE_MESH_TEXTURE_TYOKKEI + 1) + 1].pos;
			}
			else if(nCntX % 2 == 1)
			{
				//右上が直角の三角形
				Vec0 = pVtx[(nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1)) + VtxX + 1].pos - pVtx[(nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1)) + VtxX].pos;
				Vec1 = pVtx[(nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1)) + VtxX + (CAVE_MESH_TEXTURE_TYOKKEI + 1) + 1].pos - pVtx[(nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1)) + VtxX].pos;

				VtxX++;
			}

			//法線を求めて正規化する
			D3DXVec3Cross(&normal,&Vec0,&Vec1);
			D3DXVec3Normalize(&normal,&normal);

			pVtx[nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1) + VtxX].nor = normal;

			if(nCntY == (CAVE_MESH_TEXTURE_TYOKKEI - 1))
			{	//最後のＹ座標では一番下の計算がされないので一つ上の法線をぶっこむ
				pVtx[nCntY * (CAVE_MESH_TEXTURE_TYOKKEI + 1) + VtxX + (CAVE_MESH_TEXTURE_TYOKKEI + 1)].nor = normal;
			}
		}

		VtxX = 0;
	}


	//****何かの設定*****
	for(int nCnt = 0;nCnt < CAVE_MESH_VTX_NUM;nCnt++)
	{
//		pVtx[nCnt].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	}



	//****カラーの設定****
	for(int nCnt = 0;nCnt < CAVE_MESH_VTX_NUM;nCnt++)
	{
		pVtx[nCnt].col = D3DCOLOR_RGBA(255,255,255,55);
	}

	//****texの設定****
	float TexCntx = 0.0f;	//texでのみ使う
	float TexCnty = 0.0f;	//texでのみ使う

	for(int nCnt = 0;nCnt < CAVE_MESH_VTX_NUM;nCnt++)
	{
		pVtx[nCnt].tex = D3DXVECTOR2(TexCntx,TexCnty);
		TexCntx += 1.0f;

		if(TexCntx > CAVE_MESH_TEXTURE_TYOKKEI)
		{
			TexCntx = 0.0f;
			TexCnty += 1.0f;
		}
	}

	//============頂点バッファデータのロック解除============
	g_pVtxBuffMeshCave->Unlock();
	
	//============インデックス情報を設定====================
	g_pIdxBuffMeshCave -> Lock(0,0,(void**)&pIdx,0);

	//****pIdxへの段数入力****
	int IdxNum = -1;
	int IdxdansuuCnt = 1;
	for(int nCnt = 0;nCnt < CAVE_MESH_INDEX_NUM;nCnt++)
	{
		if(nCnt % 2 == 0)
		{
			IdxNum += (2 + CAVE_MESH_TEXTURE_TYOKKEI);
		}
		else
		{
			IdxNum -= (1 + CAVE_MESH_TEXTURE_TYOKKEI);
		}

		//重ねるポリゴンが来たら強引にダブらせる IdxdansuuCntは 2,5,
		//かつ、IdxNumが頂点数以上になったら通さない。超えてしまうとブレークポイントが発生する
		//もしインデックス数が規定値より超えてしまうと、ブレークポイントが発生してしまう
		if(IdxNum == CAVE_MESH_TEXTURE_TYOKKEI * IdxdansuuCnt + IdxdansuuCnt -1 && IdxdansuuCnt < CAVE_MESH_TEXTURE_NUM_OKULONG)
		{
			//まず二つの頂点を同じところにセットする
			pIdx[nCnt] = IdxNum;
			pIdx[nCnt + 1] = IdxNum;
			//左下のところに移動してからセットする。
			IdxNum += (2 + CAVE_MESH_TEXTURE_TYOKKEI);
			pIdx[nCnt + 2] = IdxNum;

			//三回代入したので3を足す　下のpIdx[nCnt] = IdxNumで結果的に同じところの数値を入れられる
			nCnt += 3;

			//Z軸方向にシフトする
			IdxdansuuCnt++;
		}

		pIdx[nCnt] = IdxNum;
	}

	//============インデックスバッファのロック解除============
	g_pIdxBuffMeshCave -> Unlock();
}

//◇---------------------------------◇
//メッシュカーブ終了処理
//◇---------------------------------◇
void UninitMeshCave(void)
{
	//****各種リリース処理****
	if(g_pVtxBuffMeshCave != NULL)
	{
		g_pVtxBuffMeshCave -> Release();
		g_pVtxBuffMeshCave = NULL;
	}
	
	//テクスチャの処理
	if(g_pTextureMeshCave != NULL)
	{
		g_pTextureMeshCave->Release();
		g_pTextureMeshCave = NULL;
	}
	//インデックスバッファのリリース
	if(g_pIdxBuffMeshCave != NULL)
	{
		g_pIdxBuffMeshCave->Release();
		g_pIdxBuffMeshCave = NULL;
	}
}
//◇---------------------------------◇
//メッシュカーブの更新処理
//◇---------------------------------◇
void UpdateMeshCave(void)
{
	//モデルの位置が床の位置より大きくなったらポリゴンの大きさ分だけ床を前進させる
	//これで床が永遠に続くようになる
	while(Getg_posModel().z > g_posMeshCave.z)
	{
		g_posMeshCave.z += CAVE_MESH_POYGON_LENGTH;
	}
}

//◇---------------------------------◇
//メッシュカーブの描画処理
//◇---------------------------------◇
void DrawMeshCave(void)
{
	//****デバイス取得****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	//****ワールドの設定****
	D3DXMatrixIdentity(&g_mtxWorldMeshCave);
	D3DXMatrixScaling(&mtxScl,g_sclMeshCave.x,
								g_sclMeshCave.y,
								g_sclMeshCave.z);			//スケールを反映

	D3DXMatrixMultiply(&g_mtxWorldMeshCave,&g_mtxWorldMeshCave,&mtxScl);

	//****その他の設定****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotMeshCave.y,
									g_rotMeshCave.x,
									g_rotMeshCave.z);		//ヨ－　ピッチ　ロール

	D3DXMatrixMultiply(&g_mtxWorldMeshCave,&g_mtxWorldMeshCave,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,g_posMeshCave.x,g_posMeshCave.y,g_posMeshCave.z);	//位置を反映
	D3DXMatrixMultiply(&g_mtxWorldMeshCave,&g_mtxWorldMeshCave,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldMeshCave);	//設定

	//-----------------------3Dポリゴンの描画-------------
	//頂点バッファをバインド
	pDevice->SetStreamSource(0,g_pVtxBuffMeshCave,0,sizeof(VERTEX_3D));
	//インデックスバッファをバインド
	pDevice -> SetIndices(g_pIdxBuffMeshCave);		//インデックスバッファをバインド
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0,g_pTextureMeshCave);
	//ポリゴンの描画
	pDevice -> DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,CAVE_MESH_VTX_NUM,0,CAVE_MESH_POLYGON_NUM);
	//----------------------------------------------------
}
