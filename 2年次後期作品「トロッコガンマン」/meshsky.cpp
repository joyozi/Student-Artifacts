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
#include "meshsky.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇		
#define MESHSKY_TEXTURE_FILE	("./data/TEXTURE/kirisuto_000.jpg")

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 g_pTextureMeshsky;			//

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshsky;		//
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshsky;		//

D3DXVECTOR3 g_posMeshsky;						//モデルの位置
D3DXVECTOR3 g_rotMeshsky;						//モデルの向き
D3DXVECTOR3 g_sclMeshsky;						//モデルの大きさ

D3DXMATRIX g_mtxProjectionMeshsky;				//プロジェクションマトリックス
D3DXMATRIX g_mtxViewMeshsky;					//ビューマトリックス
D3DXMATRIX g_mtxWorldMeshsky;					//ワールドマトリックス

//◇-------------------------------------------------------------------------◇
//メッシュスカイ初期化処理
//◇-------------------------------------------------------------------------◇
void InitMeshsky(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	VERTEX_3D *pVtx;
	WORD *pIdx;	
	
	//****位置、角度、スケールの初期化****
	g_posMeshsky = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_rotMeshsky = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclMeshsky = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//***テクステャの読み込み***
	D3DXCreateTextureFromFile(pDevice,MESHSKY_TEXTURE_FILE,&g_pTextureMeshsky);

	//***頂点情報の設定***
	//****頂点バッファの設定****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*MESHSKY_VTX_NUM,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffMeshsky,NULL);

	//****インデックスバッファの確保****
	pDevice -> CreateIndexBuffer(sizeof(WORD) * MESHSKY_INDEX_NUM,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&g_pIdxBuffMeshsky,NULL);

	//===================頂点バッファデータをロック==========================
	g_pVtxBuffMeshsky->Lock(0,0,(void**)&pVtx,0);
	
	//****頂点の位置の設定****
	int ChangeCntX = 0;				//縦軸の切り替えのときに使用する変数
	int ChangeCntY = 0;
	int ChangeCntZ = 0;
	
	float sky_rad = 0;				//XZ軸の画像の回転のうねり
	
	float sky_radY = 0.0f;			//縦の半々円の角度の変数

	//-------座標の初期値計算------------
	
	float VtxCntx = -cosf(sky_rad) * (MESHSKY_DIAMETER);	//X軸の一番左の座標
	float VtxCnty = MESHSKY_HEIGHT;							//Y軸の一番上
	float VtxCntz = sinf(sky_rad) * (MESHSKY_DIAMETER);		//Z軸の一番奥の座標 三角関数×直径
	
	//----------------------------------

	//頂点数分繰り返す
	for(int nCnt = 0;nCnt < MESHSKY_VTX_NUM;nCnt++)
	{		
		//X軸に右にシフト
		VtxCntx = -cosf(sky_rad) * (MESHSKY_DIAMETER) * sinf(sky_radY);
		//Z軸の位置を円状に変える 
		VtxCntz = sinf(sky_rad) * (MESHSKY_DIAMETER) * sinf(sky_radY);

		//最初に代入
		pVtx[nCnt].pos = D3DXVECTOR3(VtxCntx,VtxCnty,VtxCntz);

		//角度を変える
		sky_rad += ((D3DX_PI * 2) / MESHSKY_YOKO_VTX);
		
		//横一列の画像を表示したら、Y軸に一段下がるためのカウント
		ChangeCntX++;

		//nCntが左端の数値に達したらXを左端の数値に戻して、Zを一つ下におろす。
		if(ChangeCntX > MESHSKY_YOKO_VTX)
		{
			sky_radY += D3DX_PI / 2 / MESHSKY_TATE_VTX;

			//カウントリセット
			ChangeCntX = 0;
			sky_rad = 0;

			//位置のリセット
			VtxCntx = -cosf(sky_rad) * (MESHSKY_DIAMETER);
			VtxCnty -= MESHSKY_POYGON_HEIGHT;
			VtxCntz = sinf(sky_rad) * (MESHSKY_DIAMETER);
		}
	}

	//****何かの設定*****
	for(int nCnt = 0;nCnt < MESHSKY_VTX_NUM;nCnt++)
	{
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	}
	//****カラーの設定****
	for(int nCnt = 0;nCnt < MESHSKY_VTX_NUM;nCnt++)
	{
		pVtx[nCnt].col = D3DCOLOR_RGBA(255,255,255,55);
	}

	//****texの設定****
	float TexCntx = 0.0f;	//texでのみ使う
	float TexCnty = 0.0f;	//texでのみ使う

	for(int nCnt = 0;nCnt < MESHSKY_VTX_NUM;nCnt++)
	{
		pVtx[nCnt].tex = D3DXVECTOR2(TexCntx,TexCnty);
		TexCntx += 1.0f;

		if(TexCntx >= MESHSKY_YOKO_VTX + 1)
		{
			TexCntx = 0.0f;
			TexCnty += 1.0f;
		}
	}

	//============頂点バッファデータのロック解除============
	g_pVtxBuffMeshsky->Unlock();
	
	//============インデックス情報を設定====================
	g_pIdxBuffMeshsky -> Lock(0,0,(void**)&pIdx,0);

	//****pIdxへの段数入力****
	int IdxNum = -1;									//
	int IdxdansuuCnt = 1;								//

	for(int nCnt = 0;nCnt < MESHSKY_INDEX_NUM;nCnt++)	//インデックスの数だけ繰り返す
	{

		if(nCnt % 2 == 0)
		{
			IdxNum += (2 + MESHSKY_YOKO_VTX);
		}
		else
		{
			IdxNum -= (1 + MESHSKY_YOKO_VTX);
		}

		//重ねるポリゴンが来たら強引にダブらせる IdxdansuuCntは 2,5,
		//かつ、IdxNumが頂点数以上になったら通さない。超えてしまうとブレークポイントが発生する
		//もしインデックス数が規定値より超えてしまうと、ブレークポイントが発生してしまう
		if(IdxNum == MESHSKY_YOKO_VTX * IdxdansuuCnt + IdxdansuuCnt -1 && IdxdansuuCnt < MESHSKY_TATE_VTX)
		{
			//まず二つの頂点を同じところにセットする
			pIdx[nCnt] = IdxNum;
			pIdx[nCnt + 1] = IdxNum;
			//左下のところに移動してからセットする。
			IdxNum += (2 + MESHSKY_YOKO_VTX);
			pIdx[nCnt + 2] = IdxNum;

			//三回代入したので3を足す　下のpIdx[nCnt] = IdxNumで結果的に同じところの数値を入れられる
			nCnt += 3;

			//Y軸方向にシフトする
			IdxdansuuCnt++;
		}

		pIdx[nCnt] = IdxNum;
	}

	//============インデックスバッファのロック解除============
	g_pIdxBuffMeshsky -> Unlock();
}

//◇---------------------------------◇
//メッシュスカイ終了処理
//◇---------------------------------◇
void UninitMeshsky(void)
{
	//****各種リリース処理****
	if(g_pVtxBuffMeshsky != NULL)
	{
		g_pVtxBuffMeshsky -> Release();
		g_pVtxBuffMeshsky = NULL;
	}
	
	//テクスチャの処理
	if(g_pTextureMeshsky != NULL)
	{
		g_pTextureMeshsky->Release();
		g_pTextureMeshsky = NULL;
	}

	//インデックスバッファのリリース
	if(g_pIdxBuffMeshsky != NULL)
	{
		g_pIdxBuffMeshsky -> Release();
		g_pIdxBuffMeshsky = NULL;
	}
}
//◇---------------------------------◇
//メッシュスカイの更新処理
//◇---------------------------------◇
void UpdateMeshsky(void)
{

}

//◇---------------------------------◇
//メッシュスカイの描画処理
//◇---------------------------------◇
void DrawMeshsky(void)
{
	//****デバイス取得****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	//****ワールドの設定****
	D3DXMatrixIdentity(&g_mtxWorldMeshsky);
	D3DXMatrixScaling(&mtxScl,g_sclMeshsky.x,
								g_sclMeshsky.y,
								g_sclMeshsky.z);			//スケールを反映

	D3DXMatrixMultiply(&g_mtxWorldMeshsky,&g_mtxWorldMeshsky,&mtxScl);

	//****その他の設定****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotMeshsky.y,
									g_rotMeshsky.x,
									g_rotMeshsky.z);		//ヨ－　ピッチ　ロール

	D3DXMatrixMultiply(&g_mtxWorldMeshsky,&g_mtxWorldMeshsky,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,g_posMeshsky.x,g_posMeshsky.y,g_posMeshsky.z);	//位置を反映
	D3DXMatrixMultiply(&g_mtxWorldMeshsky,&g_mtxWorldMeshsky,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldMeshsky);	//設定

	//---------------------3Dポリゴンの描画------------------------------
	//頂点バッファをバインド
	pDevice->SetStreamSource(0,g_pVtxBuffMeshsky,0,sizeof(VERTEX_3D));

	//インデックスバッファをバインド
	pDevice -> SetIndices(g_pIdxBuffMeshsky);		//インデックスバッファをバインド

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0,g_pTextureMeshsky);
	//ポリゴンの描画
	pDevice -> DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,MESHSKY_VTX_NUM,0,MESHSKY_POLYGON_NUM);
	//------------------------------------------------------------------
}
