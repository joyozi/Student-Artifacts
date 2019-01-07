//◇-------------------------------------------------------------------------◇
//
//	File:CMeshSkyのファイル[CMeshSky.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "CMeshSky.h"
#include "CManager.h"
#include "CTextureManager.h"

//◇-----------------------------------◇
//CMeshSkyのコンストラクタ
//◇-----------------------------------◇
CMeshSky::CMeshSky(int nPriority) : CMeshBasisClass(nPriority)
{
	m_Type = CTYPE_MESHSKY;

	m_PolygonNum = (2 * (MESHSKY_BUNKATSU * MESHSKY_DANSUU) + (MESHSKY_DANSUU - 1) * 4);
	m_IndexNum = (m_PolygonNum + 2);
	m_VtxNum = ((MESHSKY_BUNKATSU + 1) * (MESHSKY_DANSUU + 1));
}

//◇-----------------------------------◇
//CMeshSkyのデストラクタ
//◇-----------------------------------◇
CMeshSky::~CMeshSky()
{

}

//◇-----------------------------------◇
//CMeshSkyの初期化処理
//◇-----------------------------------◇
HRESULT CMeshSky::Init(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	
	//***テクステャの読み込み***
	m_Texture = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_TexName));

	//****インデックスバッファの確保****
	pDevice -> CreateIndexBuffer(sizeof(WORD) * m_IndexNum,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&m_IdxBuffer,NULL);

	//***頂点情報の設定***
	//****頂点バッファの設定****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D)) * m_VtxNum,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_VtxBuffer,NULL);

	//===================頂点バッファデータをロック==========================
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	float radX = 0.0f;									//角度を決めるラジアンX用
	float radY = D3DX_PI / 2;							//角度を決めるラジアンY用
	float VtxX = 0.0f,VtxY = 0.0f,VtxZ = 0.0f;			//座標を求める用の変数
	float hankei = 0.0f;								//スカイの半径(固定)
	float hankei_num = 0.0f;							//スカイの半径(計算用)

	//半径を求める
	hankei = (MESHSKY_PELYGON_WIDTH/2) / sinf(D3DX_PI*2 / MESHSKY_BUNKATSU / 2);
	
	//Y軸の高さを求める
	VtxY = 0.0f;
	for(int i = 0;i < MESHSKY_DANSUU;i++)
	{
		//Y軸の角度を下に下げる 角度を変えてからじゃないと最初の移動が0にのまま
		radY -= (D3DX_PI / 2) / MESHSKY_DANSUU;
		VtxY += MESHSKY_POLYGON_HEIGHT * cosf(radY);

	}

	//値を元に戻す
	radY = D3DX_PI / 2;

	//縦の段数分繰り返す
	for(int CntY = 0;CntY < MESHSKY_DANSUU + 1;CntY++)
	{
		//横の段数分繰り返す
		for(int CntX = 0;CntX < MESHSKY_BUNKATSU + 1;CntX++)
		{
			VtxX = sinf(radX) * hankei_num;
			VtxZ = cosf(radX) * hankei_num;

			//頂点の代入
			m_pVtx[CntY * (MESHSKY_BUNKATSU + 1) + CntX].pos = D3DXVECTOR3(VtxX,VtxY,VtxZ);

			//X,Z軸の角度を決める
			radX += (D3DX_PI * 2) / MESHSKY_BUNKATSU;
		}

		radX = 0.0f;
		
		//Y軸の角度を下にさげ、Y軸を求める
		radY -= (D3DX_PI / 2) / MESHSKY_DANSUU;
		VtxY -= MESHSKY_POLYGON_HEIGHT * cosf(radY);

		//半径を大きくする
		hankei_num -= hankei * sinf(radY);
	}



	//****何かとカラーの設定*****
	for(int nCnt = 0;nCnt < m_VtxNum;nCnt++)
	{
		m_pVtx[nCnt].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
		m_pVtx[nCnt].col = D3DCOLOR_RGBA(255,255,255,55);
	}

	//****texの設定****
	float TexCntX = 0.0f;	//texでのみ使う
	float TexCntY = 0.0f;	//texでのみ使う

	//縦の段数 + 1繰り返す		1段ならY軸に2頂点あるから
	for(int CntY = 0;CntY < MESHSKY_DANSUU+1;CntY++)
	{
		//横の段数分繰り返す
		for(int CntX = 0;CntX < MESHSKY_BUNKATSU + 1;CntX++)
		{
			m_pVtx[CntY * (MESHSKY_BUNKATSU+1) + CntX].tex = D3DXVECTOR2(TexCntX,TexCntY);
			
			TexCntX += 1.0f / MESHSKY_BUNKATSU;


		}
		TexCntX = 0.0f;

		TexCntY += 1.0f / MESHSKY_DANSUU;
	}

	//============頂点バッファデータのロック解除============
	m_VtxBuffer->Unlock();
	
	//============インデックス情報を設定====================
	m_IdxBuffer -> Lock(0,0,(void**)&m_pIdx,0);

	//****m_pIdxへの段数入力****
	int IdxNum = -1;
	int IdxdansuuCnt = 1;


	//段数分繰り返す
	for(int nCnt = 0;nCnt < m_IndexNum;nCnt++)
	{
		if(nCnt % 2 == 0)
		{
			IdxNum += (2 + MESHSKY_BUNKATSU);
		}
		else
		{
			IdxNum -= (1 + MESHSKY_BUNKATSU);
		}

		//重ねるポリゴンが来たら強引にダブらせる　最後以外
		if(IdxNum == MESHSKY_BUNKATSU * IdxdansuuCnt + IdxdansuuCnt -1 && nCnt != m_IndexNum - 1)
		{
			//まず二つの頂点を同じところにセットする
			m_pIdx[nCnt] = IdxNum;
			m_pIdx[nCnt + 1] = IdxNum;
			//左下のところに移動してからセットする。
			IdxNum += (2 + MESHSKY_BUNKATSU);
			m_pIdx[nCnt + 2] = IdxNum;

			//三回代入したので3を足す　下のm_pIdx[nCnt] = IdxNumで結果的に同じところの数値を入れられる
			nCnt += 3;
			//Z軸方向にシフトする
			IdxdansuuCnt++;
		}

		m_pIdx[nCnt] = IdxNum;

		
	}


	//============インデックスバッファのロック解除============
	m_IdxBuffer -> Unlock();

	return S_OK;
}

//◇-----------------------------------◇
//CMeshSkyの更新処理
//◇-----------------------------------◇
void CMeshSky::Update(void)
{
	m_Rot.y += 0.0001f;
}

//◇-----------------------------------◇
//メッシュスカイのクリエイト
//◇-----------------------------------◇
CMeshSky *CMeshSky::Create(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot)
{
	CMeshSky *pMeshSky;
	pMeshSky = new CMeshSky;

	pMeshSky->m_TexName = TexName;
	pMeshSky->m_Pos = Pos;
	pMeshSky->m_Rot = Rot;

	pMeshSky->Init();

	return pMeshSky;
}

