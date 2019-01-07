//◇-------------------------------------------------------------------------◇
//
//	File:CMeshHitCheckBallのファイル[CMeshHitCheckBall.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CMeshHitCheckBall.h"
#include "CManager.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CMeshHitCheckBallのコンストラクタ
//◇-----------------------------------◇
CMeshHitCheckBall::CMeshHitCheckBall(int nPriority) : CMeshBasisClass(nPriority)
{
	m_BallRadius = 0.0f;
}

//◇-----------------------------------◇
//CMeshHitCheckBallのデストラクタ
//◇-----------------------------------◇
CMeshHitCheckBall::~CMeshHitCheckBall()
{

}

//◇-----------------------------------◇
//CMeshHitCheckBallの初期化処理
//◇-----------------------------------◇
HRESULT CMeshHitCheckBall::Init(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	
	//***テクステャの読み込み***
//	m_Texture = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_TexName));

	int dansuu = 3;

//	m_PolygonNum = (CHECKBALL_VTXNUM - 2)*2;
//	m_IndexNum = (m_PolygonNum + 2)*3;		//ここだけ適当
//	m_VtxNum = CHECKBALL_VTXNUM;

	m_PolygonNum = (2 * (CHECLBALL_ONEVTX * CHECLBALL_ONEVTX) + (CHECKBALL_DANSUU - 1) * 4);
	m_IndexNum = (m_PolygonNum + 2);
	m_VtxNum = ((CHECLBALL_ONEVTX + 1) * (CHECKBALL_DANSUU + 1));

	//****インデックスバッファの確保****
	pDevice -> CreateIndexBuffer(sizeof(WORD) * m_IndexNum,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&m_IdxBuffer,NULL);

	//***頂点情報の設定***
	//****頂点バッファの設定****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D)) * m_VtxNum,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_VtxBuffer,NULL);

	//===================頂点バッファデータをロック==========================
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);
	


	float AngleX = 0.0f;
	float AngleY = 0.0f;

	for(int nCntY = 0;nCntY < CHECKBALL_DANSUU;nCntY++)
	{
		for(int nCntX = 0;nCntX < CHECLBALL_ONEVTX;nCntX++)
		{
			D3DXVECTOR3 Pos;

			Pos.x = sinf(AngleX) * sinf(AngleY);
			Pos.y = cosf(AngleY);
			Pos.z = cosf(AngleX) * sinf(AngleY);

			m_BallVtxVec[nCntX + nCntY * CHECLBALL_ONEVTX] = Pos;
			m_pVtx[nCntX + nCntY * CHECLBALL_ONEVTX].pos = Pos * m_BallRadius;

			AngleX += D3DX_PI*2 / (float)CHECLBALL_ONEVTX;
		}

		AngleX = 0.0f;

		AngleY += D3DX_PI / (CHECKBALL_DANSUU - 1);
	}



	//****カラーと法線の設定*****
	for(int nCnt = 0;nCnt < m_VtxNum;nCnt++)
	{
		m_pVtx[nCnt].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
		m_pVtx[nCnt].col = D3DCOLOR_RGBA(55,0,255,55);
	}

	//****texの設定****
	float TexCntX = 0.0f;	//texでのみ使う
	float TexCntY = 0.0f;	//texでのみ使う

	for(int CntX = 0;CntX < m_VtxNum;CntX++)
	{
		m_pVtx[CntX].tex = D3DXVECTOR2(0.0f,0.0f);
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
			IdxNum += (2 + CHECKBALL_DANSUU);
		}
		else
		{
			IdxNum -= (1 + CHECKBALL_DANSUU);
		}

		//重ねるポリゴンが来たら強引にダブらせる　最後以外
		if(IdxNum == CHECKBALL_DANSUU * IdxdansuuCnt + IdxdansuuCnt -1 && nCnt != m_IndexNum - 1)
		{
			//まず二つの頂点を同じところにセットする
			m_pIdx[nCnt] = IdxNum;
			m_pIdx[nCnt + 1] = IdxNum;
			//左下のところに移動してからセットする。
			IdxNum += (2 + CHECKBALL_DANSUU);
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
//CMeshHitCheckBallの描画処理
//◇-----------------------------------◇
void CMeshHitCheckBall::Draw(void)
{
	//****デバイス取得****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);

	CScene *pIrekoScene[512] = {NULL};

	for(int i = 0;i < PRIORITY_NUM;i++)
	{
		CScene::SearchLinkList(pIrekoScene,i);

		for(int i_2 = 0;pIrekoScene[i_2] != NULL;i_2++)
		{

			//あたり判定のある数だけやる
			for(int i_3 = 0;i_3 < pIrekoScene[i_2]->GetCollisionHitNum();i_3++)
			{
				//===================頂点バッファデータをロック==========================
				m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

				SetBallRadius(pIrekoScene[i_2]->GetCollisionRadius(i_3));

				//============頂点バッファデータのロック解除============
				m_VtxBuffer->Unlock();
			
				SetPosition(pIrekoScene[i_2]->GetCollisionCenterPos(i_3));



				//****ワールドの設定****
				D3DXMatrixIdentity(&m_mtxWorld);
				D3DXMatrixScaling(&mtxScl,m_Scl.x,
											m_Scl.y,
											m_Scl.z);			//スケールを反映

				D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

				//****その他の設定****
				D3DXMatrixRotationYawPitchRoll(&mtxRot,m_Rot.y,
												m_Rot.x,
												m_Rot.z);		//ヨ－　ピッチ　ロール

				D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
				D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);		//位置を反映
				D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	
				pDevice -> SetTransform(D3DTS_WORLD,&m_mtxWorld);	//設定



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



			}
		}

		//判定のために全部にヌルを入れる
		for(int i_4 = 0;pIrekoScene[i_4] != NULL;i_4++)
		{
			pIrekoScene[i_4] = NULL;
		}
		
	}
	pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//◇-----------------------------------◇
//CMeshHitCheckBallの半径の設定
//◇-----------------------------------◇
void CMeshHitCheckBall::SetBallRadius(float Radius)
{
	for(int i = 0;i < CHECKBALL_VTXNUM;i++)
	{
		m_pVtx[i].pos = m_BallVtxVec[i] * Radius;
	}
}

//◇-----------------------------------◇
//CMeshHitCheckBallのクリエイト
//◇-----------------------------------◇
CMeshHitCheckBall *CMeshHitCheckBall::Create()
{
	CMeshHitCheckBall *pCheckBall;
	pCheckBall = new CMeshHitCheckBall;

	pCheckBall->Init();

	return pCheckBall;
}
