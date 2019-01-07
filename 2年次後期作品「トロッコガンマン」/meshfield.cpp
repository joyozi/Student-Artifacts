//◇-------------------------------------------------------------------------◇
//
//	File	:ファイル[meshfield.cpp]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "meshfield.h"
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
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;				//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;		//

LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;			//

D3DXVECTOR3 g_posMeshfield;						//モデルの位置
D3DXVECTOR3 g_rotMeshfield;						//モデルの向き
D3DXVECTOR3 g_sclMeshfield;						//モデルの大きさ

D3DXMATRIX g_mtxProjectionMeshfield;			//プロジェクションマトリックス
D3DXMATRIX g_mtxViewMeshfield;					//ビューマトリックス
D3DXMATRIX g_mtxWorldMeshfield;					//ワールドマトリックス

D3DXVECTOR3 g_posMeshfieldP;					//カメラの視点
D3DXVECTOR3 g_posMeshfieldR;					//カメラの注視点
D3DXVECTOR3 g_posMeshfieldU;					//カメラの上方向ベクトル

float cavelong_back;							//洞窟の一番後ろの座標

//◇-------------------------------------------------------------------------◇
//初期化処理
//◇-------------------------------------------------------------------------◇
void InitMeshfield(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	VERTEX_3D *pVtx;
	WORD *pIdx;
	
	//****位置、角度、スケールの初期化****
	g_posMeshfield = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_rotMeshfield = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclMeshfield = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//***カメラの初期化***
	g_posMeshfieldP = D3DXVECTOR3(0.0f,0.0f,0.0f);		//カメラの視点
	g_posMeshfieldR = D3DXVECTOR3(0.0f,0.0f,0.0f);		//カメラの注視点
	g_posMeshfieldU = D3DXVECTOR3(0.0f,1.0f,0.0f);		//カメラの上方向ベクトル


	//***頂点情報の設定***
	//****頂点バッファの設定****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*MESH_VTX_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffMeshField,NULL);

	//****インデックスバッファの確保****
	pDevice -> CreateIndexBuffer(sizeof(WORD) * MESH_INDEX_NUM,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&g_pIdxBuffMeshField,NULL);

	//***テクステャの読み込み***
	D3DXCreateTextureFromFile(pDevice,"./data/TEXTURE/wall_002.jpg",&g_pTextureMeshField);

	//===================頂点バッファデータをロック==========================
	g_pVtxBuffMeshField->Lock(0,0,(void**)&pVtx,0);
	
	//****頂点の位置の設定****
	int ChangeCntX = 1;										//縦軸の切り替えのときに使用する変数
	int ChangeCntZ = 0;
	int VtxCntx = -(MESH_LENGTH_YOKO / 2);					//X軸の一番左の座標
	int VtxCnty = 0;										//Y軸
	int VtxCntz = MESH_LENGTH_OKU / 2;						//Z軸の一番奥の座標

	//頂点数分繰り返す
	for(int nCnt = 0;nCnt < MESH_VTX_NUM;nCnt++)
	{
		//最初に代入
		pVtx[nCnt].pos = D3DXVECTOR3(VtxCntx,VtxCnty,VtxCntz);

		//X軸に左にシフト
		VtxCntx += MESH_POYGON_LENGTH;

		ChangeCntZ++;

		//nCntが左端の数値に達したらXを左端の数値に戻して、Zを一つ下におろす。
		if(ChangeCntZ > MESH_TEXTURE_YOKONUM)
		{
			VtxCntx = -(MESH_LENGTH_YOKO / 2);
			VtxCntz -= MESH_LENGTH_OKU / MESH_TEXTURE_OKUNUM;
			ChangeCntZ = 0;
		}
	}

	//****何かの設定*****
	for(int nCnt = 0;nCnt < MESH_VTX_NUM;nCnt++)
	{
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	}
	//****カラーの設定****
	for(int nCnt = 0;nCnt < MESH_VTX_NUM;nCnt++)
	{
		pVtx[nCnt].col = D3DCOLOR_RGBA(255,255,255,55);
	}

	//****texの設定****
	float TexCntx = 0.0f;	//texでのみ使う
	float TexCnty = 0.0f;	//texでのみ使う

	for(int nCnt = 0;nCnt < MESH_VTX_NUM;nCnt++)
	{
		pVtx[nCnt].tex = D3DXVECTOR2(TexCntx,TexCnty);
		TexCntx += 1.0f;

		if(TexCntx >= MESH_TEXTURE_YOKONUM + 1)
		{
			TexCntx = 0.0f;
			TexCnty += 1.0f;
		}
	}

	//============頂点バッファデータのロック解除============
	g_pVtxBuffMeshField->Unlock();
	
	//============インデックス情報を設定====================
	g_pIdxBuffMeshField -> Lock(0,0,(void**)&pIdx,0);

	//****pIdxへの段数入力****
	int IdxNum = -1;
	int IdxdansuuCnt = 1;		//Ｚ軸へのシフトのカウント
	for(int nCnt = 0;nCnt < MESH_INDEX_NUM;nCnt++)
	{
		if(nCnt % 2 == 0)
		{
			IdxNum += (2 + MESH_TEXTURE_YOKONUM);
		}
		else
		{
			IdxNum -= (1 + MESH_TEXTURE_YOKONUM);
		}

		//重ねるポリゴンが来たら強引にダブらせる IdxdansuuCntは 2,5,
		//かつ、IdxdansuuCntが段数以上になったら通さない。超えてしまうとブレークポイントが発生する
		//もしインデックス数が規定値より超えてしまうと、ブレークポイントが発生してしまう
		if(IdxNum == MESH_TEXTURE_YOKONUM * IdxdansuuCnt + IdxdansuuCnt -1 && IdxdansuuCnt < MESH_TEXTURE_OKUNUM)
		{
			//まず二つの頂点を同じところにセットする
			pIdx[nCnt] = IdxNum;
			pIdx[nCnt + 1] = IdxNum;
			//左下のところに移動してからセットする。
			IdxNum += (2 + MESH_TEXTURE_YOKONUM);
			pIdx[nCnt + 2] = IdxNum;

			//三回代入したので3を足す　下のpIdx[nCnt] = IdxNumで結果的に同じところの数値を入れられる
			nCnt += 3;

			//Z軸方向にシフトする
			IdxdansuuCnt++;
		}

		pIdx[nCnt] = IdxNum;
	}

	//============インデックスバッファのロック解除============
	g_pIdxBuffMeshField -> Unlock();
}

//◇---------------------------------◇
//終了処理
//◇---------------------------------◇
void UninitMeshfield(void)
{
	//****各種リリース処理****
	if(g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField -> Release();
		g_pVtxBuffMeshField = NULL;
	}

	//インデックスバッファのリリース
	if(g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField -> Release();
		g_pIdxBuffMeshField = NULL;
	}

	//テクスチャの処理
	if(g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

}
//◇---------------------------------◇
//の更新処理
//◇---------------------------------◇
void UpdateMeshfield(void)
{
	//モデルの位置が床の位置より大きくなったらポリゴンの大きさ分だけ床を前進させる
	//これで床が永遠に続くようになる
	while(Getg_posModel().z > g_posMeshfield.z)
	{
		g_posMeshfield.z += MESH_POYGON_LENGTH;
	}

}

//◇---------------------------------◇
//の描画処理
//◇---------------------------------◇
void DrawMeshfield(void)
{
	//****デバイス取得****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	//****ワールドの設定****
	D3DXMatrixIdentity(&g_mtxWorldMeshfield);
	D3DXMatrixScaling(&mtxScl,g_sclMeshfield.x,
								g_sclMeshfield.y,
								g_sclMeshfield.z);			//スケールを反映

	D3DXMatrixMultiply(&g_mtxWorldMeshfield,&g_mtxWorldMeshfield,&mtxScl);

	//****その他の設定****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotMeshfield.y,
									g_rotMeshfield.x,
									g_rotMeshfield.z);		//ヨ－　ピッチ　ロール

	D3DXMatrixMultiply(&g_mtxWorldMeshfield,&g_mtxWorldMeshfield,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,g_posMeshfield.x,g_posMeshfield.y,g_posMeshfield.z);	//位置を反映
	D3DXMatrixMultiply(&g_mtxWorldMeshfield,&g_mtxWorldMeshfield,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldMeshfield);	//設定

//----------------------3Dポリゴンの描画--------------------------

	//頂点バッファのバインド
	pDevice->SetStreamSource(0,g_pVtxBuffMeshField,0,sizeof(VERTEX_3D));
	//インデックスバッファをバインド
	pDevice -> SetIndices(g_pIdxBuffMeshField);		//インデックスバッファをバインド
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0,g_pTextureMeshField);
	//ポリゴンの描画
	pDevice -> DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,MESH_VTX_NUM,0,MESH_POLYGON_NUM);

//-----------------------------------------------------------------
}
