//◇-------------------------------------------------------------------------◇
//
//	File:CDegeneracyPolygonのファイル[CDegeneracyPolygon.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CDegeneracyPolygon.h"
#include "CManager.h"
#include "CItemList.h"
#include "CTextureManager.h"
#include "CCamera.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CDegeneracyPolygonのコンストラクタ
//◇-----------------------------------◇
CDegeneracyPolygon::CDegeneracyPolygon(int nPriority) : CMeshBasisClass(nPriority)
{
	m_Type = CTYPE_DEGENERACYPOLYGON;

	m_DegeneracyPolygon_Max = DEGENERACYPOLYGON_MAX;

	m_DegeneracyPolygonNum = 0;

	m_pLength = NULL;
	m_pAngle = NULL;
	m_pDegeneracyPolygonPos = NULL;
	m_pPolygonExistJudge = NULL;
	m_pDegeneracyPolygonRot = NULL;
	m_BillboardJudge = true;
	m_AlphaBlendJudge = true;
	m_SortJudge = true;
	m_LoopJudge = true;
	m_pPolygonUninitFlag = NULL;
}

//◇-----------------------------------◇
//CDegeneracyPolygonのデストラクタ
//◇-----------------------------------◇
CDegeneracyPolygon::~CDegeneracyPolygon()
{

}

//◇-----------------------------------◇
//CDegeneracyPolygonの初期化処理
//◇-----------------------------------◇
HRESULT CDegeneracyPolygon::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	
	//***テクステャの読み込み***
	m_Texture = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_TexName));



	int Index_Max = m_DegeneracyPolygon_Max * 4 + ((m_DegeneracyPolygon_Max - 1) * 2);
	int Vtx_Max = m_DegeneracyPolygon_Max * 4;

	m_pLength = new float[m_DegeneracyPolygon_Max];
	m_pAngle = new float[m_DegeneracyPolygon_Max];
	m_pDegeneracyPolygonPos = new D3DXVECTOR3[m_DegeneracyPolygon_Max];
	m_pPolygonExistJudge = new bool[m_DegeneracyPolygon_Max];
	m_pDegeneracyPolygonRot = new D3DXVECTOR3[m_DegeneracyPolygon_Max];
	m_pPolygonUninitFlag = new bool[m_DegeneracyPolygon_Max];

	m_VtxBox = new VERTEX_3D[Vtx_Max];

	for(int i = 0;i < m_DegeneracyPolygon_Max;i++)
	{
		m_pPolygonExistJudge[i] = false;
		m_pLength[i] = 0.0f;
		m_pAngle[i] = 0.0f;
		m_pDegeneracyPolygonPos[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_pDegeneracyPolygonRot[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_pPolygonUninitFlag[i] = false;
	}



	//****インデックスバッファの確保****
	pDevice->CreateIndexBuffer(sizeof(WORD) * Index_Max,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&m_IdxBuffer,NULL);

	//***頂点情報の設定***
	//****頂点バッファの設定****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*Vtx_Max,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_VtxBuffer,NULL);



	//頂点数分繰り返す
	for(int nCnt = 0;nCnt < Vtx_Max;nCnt++)
	{
		//最初に代入
		m_VtxBox[nCnt].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_VtxBox[nCnt].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		m_VtxBox[nCnt].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	}

	//****texの設定****
	float TexCntx = 0.0f;	//texでのみ使う
	float TexCnty = 0.0f;	//texでのみ使う

	for(int nCnt = 0;nCnt < Vtx_Max;nCnt++)
	{
		m_VtxBox[nCnt].tex = D3DXVECTOR2(TexCntx,TexCnty);
		TexCntx += 1.0f;

		//右側になったらみたいな
		if(nCnt % 2 == 1)
		{
			TexCntx = 0.0f;
			if(TexCnty == 0.0f)
				TexCnty += 1.0f;
			else
				TexCnty = 0.0f;
		}
	}

	//============インデックス情報を設定====================
	m_IdxBuffer -> Lock(0,0,(void**)&m_pIdx,0);

	//****m_pIdxへの段数入力****
	int IdxNum = -1;
	int IdxdansuuCnt = 1;

	int PolygonNumX = 1;		//横のポリゴンの数

	for(int nCnt = 0;nCnt < Index_Max;nCnt++)
	{
		if(nCnt % 2 == 0)
		{
			IdxNum += (2 + PolygonNumX);
		}
		else
		{
			IdxNum -= (1 + PolygonNumX);
		}

		//1 5 9 13
		if(IdxNum == (IdxdansuuCnt - 1) * 4 + 1 && IdxNum != (m_DegeneracyPolygon_Max - 1) * 4 + 1)
		{
			//まず二つの頂点を同じところにセットする
			m_pIdx[nCnt] = IdxNum;
			m_pIdx[nCnt + 1] = IdxNum;
			//左下のところに移動してからセットする。
			IdxNum += (4 + PolygonNumX);
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
	
	SetOnlyInit();

	return S_OK;
}

//◇-----------------------------------◇
//CDegeneracyPolygonのセットする専用のInit
//◇-----------------------------------◇
void CDegeneracyPolygon::SetOnlyInit(void)
{

}

//◇-----------------------------------◇
//CDegeneracyPolygonの終了処理
//◇-----------------------------------◇
void CDegeneracyPolygon::Uninit(void)
{
	Release();

	SAFE_RELEASE(m_VtxBuffer);
	SAFE_RELEASE(m_IdxBuffer);

	SAFE_DELETE_ARRY(m_pAngle);
	SAFE_DELETE_ARRY(m_pLength);
	SAFE_DELETE_ARRY(m_pDegeneracyPolygonPos);
	SAFE_DELETE_ARRY(m_pPolygonExistJudge);
	SAFE_DELETE_ARRY(m_pDegeneracyPolygonRot);
	SAFE_DELETE_ARRY(m_VtxBox);
	SAFE_DELETE_ARRY(m_pPolygonUninitFlag);

}

//◇-----------------------------------◇
//CDegeneracyPolygonの描画処理
//◇-----------------------------------◇
void CDegeneracyPolygon::Draw(void)
{
	//****デバイス取得****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;



	//ビルボードにするかどうか
	if(m_BillboardJudge)
	{
		D3DXMATRIX Matrix;
		D3DXVECTOR3 KariPos[4] = {D3DXVECTOR3(0.0f,0.0f,0.0f)};
		D3DXMATRIX mtxRot;

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&Matrix);

		//逆行列を求める
		D3DXMatrixInverse(&Matrix,NULL,&CManager::GetCameraPointer()->GetMtxView());
		Matrix._41 = 0.0f;
		Matrix._42 = 0.0f;
		Matrix._43 = 0.0f;

		for(int i = 0;i < m_DegeneracyPolygon_Max;i++)
		{
			if(m_pPolygonExistJudge[i])
			{
				KariPos[0].x = m_pLength[i] * sinf(m_pAngle[i] + D3DX_PI);
				KariPos[1].x = m_pLength[i] * sinf(m_pAngle[i]);
				KariPos[2].x = KariPos[0].x;
				KariPos[3].x = KariPos[1].x;

				KariPos[0].y = m_pLength[i] * cosf(m_pAngle[i]);
				KariPos[1].y = KariPos[0].y;
				KariPos[2].y = m_pLength[i] * cosf(m_pAngle[i] + D3DX_PI);
				KariPos[3].y = KariPos[2].y;

				KariPos[0].z = 0.0f;
				KariPos[1].z = 0.0f;
				KariPos[2].z = 0.0f;
				KariPos[3].z = 0.0f;
				
				for(int i_2 = 0;i_2 < 4;i_2++)
				{
					D3DXVec3TransformCoord(&KariPos[i_2],&KariPos[i_2],&Matrix);

					KariPos[i_2].x += m_pDegeneracyPolygonPos[i].x;
					KariPos[i_2].y += m_pDegeneracyPolygonPos[i].y;
					KariPos[i_2].z += m_pDegeneracyPolygonPos[i].z;
				}

				m_VtxBox[(i * 4) + 0].pos = KariPos[0];
				m_VtxBox[(i * 4) + 1].pos = KariPos[1];
				m_VtxBox[(i * 4) + 2].pos = KariPos[2];
				m_VtxBox[(i * 4) + 3].pos = KariPos[3];
			}
		}
	}



	//===================頂点バッファデータをロック==========================
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	int PolygonCnt = 0;

	for(int i = 0;i < m_DegeneracyPolygonNum;i++)
	{
		if(m_pPolygonExistJudge[i])
		{
			m_pVtx[(PolygonCnt * 4) + 0] = m_VtxBox[(i * 4) + 0];
			m_pVtx[(PolygonCnt * 4) + 1] = m_VtxBox[(i * 4) + 1];
			m_pVtx[(PolygonCnt * 4) + 2] = m_VtxBox[(i * 4) + 2];
			m_pVtx[(PolygonCnt * 4) + 3] = m_VtxBox[(i * 4) + 3];

			if(m_pPolygonUninitFlag[PolygonCnt])
			{
				m_pPolygonExistJudge[PolygonCnt] = false;
				m_pPolygonUninitFlag[PolygonCnt] = false;
			}

			PolygonCnt++;
		}
	}
	
	m_PolygonNum = 0;
	//描画時に必要なポリゴン数の設定
	for(int i = 0;i < PolygonCnt;i++)
	{
		if(i == 0)
			m_PolygonNum += 2;
		else
			m_PolygonNum += 6;
	}

	//===================頂点バッファデータのロック解除======================
	m_VtxBuffer->Unlock();



	//****ワールドの設定****
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&mtxScl,m_Scl.x,
								m_Scl.y,
								m_Scl.z);								//スケールを反映

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

	//****その他の設定****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_Rot.y,m_Rot.x,m_Rot.z);	//ヨ－　ピッチ　ロール
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);

	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);		//位置を反映
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&m_mtxWorld);	//設定
	
	if(m_AlphaBlendJudge)
	{
		//エフェクト処理　光る処理
		pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE ,FALSE);
	}

	//3Dポリゴンの描画
	pDevice->SetStreamSource(0,m_VtxBuffer,0,sizeof(VERTEX_3D));
	//頂点バッファをバインド
	pDevice -> SetIndices(m_IdxBuffer);		//インデックスバッファをバインド
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0,m_Texture);
	//ドロウプリミティブ
	pDevice -> DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_VtxNum,0,m_PolygonNum);

	if(m_AlphaBlendJudge)
	{
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE ,TRUE);
		pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	}
}


//◇-----------------------------------◇
//CDegeneracyPolygonのクリエイト
//◇-----------------------------------◇
CDegeneracyPolygon *CDegeneracyPolygon::Create(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot)
{
	CDegeneracyPolygon *pDegeneracyPolygon;
	pDegeneracyPolygon = new CDegeneracyPolygon;

	pDegeneracyPolygon->m_TexName = TexName;
	pDegeneracyPolygon->m_Pos = Pos;
	pDegeneracyPolygon->m_Rot = Rot;

	pDegeneracyPolygon->Init();

	return pDegeneracyPolygon;
}



//◇-----------------------------------◇
//CDegeneracyPolygonのセットポリゴン
//◇-----------------------------------◇
int CDegeneracyPolygon::SetPolygon(D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,float Width,float Height)
{
	//今の数値をもらう 右のだけだと繰り返すときに数値が変わってきてしまうから
	int PolygonNumNow = m_DegeneracyPolygonNum;		//今回どこの番号に入れるかと、全体に表示されてるポリゴン数

	//もしセットできるポリゴンを超えてたら
	if(PolygonNumNow >= m_DegeneracyPolygon_Max && m_LoopJudge)
	{
		//最大数まで行ったら繰り返せるかを見る
		for(int i = 0;i < m_DegeneracyPolygon_Max;i++)
		{
			if(m_pPolygonExistJudge[i] == false)
			{
				PolygonNumNow = i;
				break;
			}
		}
	}

	if(PolygonNumNow >= m_DegeneracyPolygon_Max)
	{
		//なかったら終わり
		return -1;
	}

	m_pPolygonExistJudge[PolygonNumNow] = true;



	//他しか割り算とかって遅いような気がしたから
	float Width_Harh = Width / 2;
	float Height_Harh = Height / 2;

	//平方根？を求める?
	m_pLength[PolygonNumNow] = sqrtf((Width_Harh * Width_Harh) + (Height_Harh * Height_Harh));
	//角度を求める
	m_pAngle[PolygonNumNow] = atan2f(Width_Harh,Height_Harh);
	//位置を保存
	m_pDegeneracyPolygonPos[PolygonNumNow] = Pos;

	D3DXVECTOR3 KariPos[4];

	m_VtxBox[(PolygonNumNow * 4) + 0].pos.x = Pos.x + m_pLength[PolygonNumNow] * sinf(m_pAngle[PolygonNumNow] + D3DX_PI);
	m_VtxBox[(PolygonNumNow * 4) + 1].pos.x = Pos.x + m_pLength[PolygonNumNow] * sinf(m_pAngle[PolygonNumNow]);
	m_VtxBox[(PolygonNumNow * 4) + 2].pos.x = Pos.x + m_pLength[PolygonNumNow] * sinf(m_pAngle[PolygonNumNow] + D3DX_PI);
	m_VtxBox[(PolygonNumNow * 4) + 3].pos.x = Pos.x + m_pLength[PolygonNumNow] * sinf(m_pAngle[PolygonNumNow]);

	m_VtxBox[(PolygonNumNow * 4) + 0].pos.y = Pos.y + m_pLength[PolygonNumNow] * cosf(m_pAngle[PolygonNumNow]);
	m_VtxBox[(PolygonNumNow * 4) + 1].pos.y = Pos.y + m_pLength[PolygonNumNow] * cosf(m_pAngle[PolygonNumNow]);
	m_VtxBox[(PolygonNumNow * 4) + 2].pos.y = Pos.y + m_pLength[PolygonNumNow] * cosf(m_pAngle[PolygonNumNow] + D3DX_PI);
	m_VtxBox[(PolygonNumNow * 4) + 3].pos.y = Pos.y + m_pLength[PolygonNumNow] * cosf(m_pAngle[PolygonNumNow] + D3DX_PI);

	m_VtxBox[(PolygonNumNow * 4) + 0].pos.z = Pos.z + 0.0f;
	m_VtxBox[(PolygonNumNow * 4) + 1].pos.z = Pos.z + 0.0f;
	m_VtxBox[(PolygonNumNow * 4) + 2].pos.z = Pos.z + 0.0f;
	m_VtxBox[(PolygonNumNow * 4) + 3].pos.z = Pos.z + 0.0f;

	if(m_DegeneracyPolygonNum < m_DegeneracyPolygon_Max)
		m_DegeneracyPolygonNum++;


	return PolygonNumNow;
}

//◇-----------------------------------◇
//CDegeneracyPolygonのセットカラー
//◇-----------------------------------◇
int CDegeneracyPolygon::ParticleSetColor(int Num,D3DXCOLOR Col)
{
	//もしセットできるポリゴンを超えてたら
	if(Num >= m_DegeneracyPolygon_Max || Num < 0 || m_pPolygonExistJudge[Num] == false)
	{
		return -1;
	}

	D3DXCOLOR a = D3DXCOLOR(Col.r * Col.a,Col.g * Col.a,Col.b * Col.a,Col.a);

	m_VtxBox[(Num * 4) + 0].col = a;
	m_VtxBox[(Num * 4) + 1].col = a;
	m_VtxBox[(Num * 4) + 2].col = a;
	m_VtxBox[(Num * 4) + 3].col = a;

	return Num;
}

//◇-----------------------------------◇
//CDegeneracyPolygonの移動
//◇-----------------------------------◇
int CDegeneracyPolygon::ParticleSetPosition(int Num,D3DXVECTOR3 Pos)
{
	//もしセットできるポリゴンを超えてたら
	if(Num >= m_DegeneracyPolygon_Max || Num < 0 || m_pPolygonExistJudge[Num] == false)
	{
		return -1;
	}

	m_pDegeneracyPolygonPos[Num] = Pos;

	D3DXVECTOR3 KariPos[4];

	m_VtxBox[(Num * 4) + 0].pos.x = Pos.x + m_pLength[Num] * sinf(m_pAngle[Num] + D3DX_PI);
	m_VtxBox[(Num * 4) + 1].pos.x = Pos.x + m_pLength[Num] * sinf(m_pAngle[Num]);
	m_VtxBox[(Num * 4) + 2].pos.x = Pos.x + m_pLength[Num] * sinf(m_pAngle[Num] + D3DX_PI);
	m_VtxBox[(Num * 4) + 3].pos.x = Pos.x + m_pLength[Num] * sinf(m_pAngle[Num]);

	m_VtxBox[(Num * 4) + 0].pos.y = Pos.y + m_pLength[Num] * cosf(m_pAngle[Num]);
	m_VtxBox[(Num * 4) + 1].pos.y = Pos.y + m_pLength[Num] * cosf(m_pAngle[Num]);
	m_VtxBox[(Num * 4) + 2].pos.y = Pos.y + m_pLength[Num] * cosf(m_pAngle[Num] + D3DX_PI);
	m_VtxBox[(Num * 4) + 3].pos.y = Pos.y + m_pLength[Num] * cosf(m_pAngle[Num] + D3DX_PI);

	m_VtxBox[(Num * 4) + 0].pos.z = Pos.z + 0.0f;
	m_VtxBox[(Num * 4) + 1].pos.z = Pos.z + 0.0f;
	m_VtxBox[(Num * 4) + 2].pos.z = Pos.z + 0.0f;
	m_VtxBox[(Num * 4) + 3].pos.z = Pos.z + 0.0f;

	return Num;
}


//◇-----------------------------------◇
//CDegeneracyPolygonの消去
//◇-----------------------------------◇
int CDegeneracyPolygon::ParticleUninitPosition(int Num)
{
	//もしセットできるポリゴンを超えてたら
	if(Num >= m_DegeneracyPolygon_Max || Num < 0 || m_pPolygonExistJudge[Num] == false)
	{
		return Num;
	}

	m_pDegeneracyPolygonPos[Num] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_pDegeneracyPolygonRot[Num] = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_pLength[Num] = 0.0f;
	m_pAngle[Num] = 0.0f;

	m_VtxBox[(Num * 4) + 0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_VtxBox[(Num * 4) + 1].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_VtxBox[(Num * 4) + 2].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_VtxBox[(Num * 4) + 3].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_pPolygonUninitFlag[Num] = true;

	return -1;
}

