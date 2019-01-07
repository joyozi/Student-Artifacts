//◇-------------------------------------------------------------------------◇
//
//	File:CSceneMeshOrbitのファイル[CSceneMeshOrbit.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CSceneMeshOrbit.h"
#include "CManager.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CSceneMeshOrbitのコンストラクタ
//◇-----------------------------------◇
CSceneMeshOrbit::CSceneMeshOrbit(int nPriority) : CScene3D(nPriority)
{
	m_Type = CTYPE_SCENEMESHORBIT;

	D3DXMatrixIdentity(&m_TargetMatrix);
	m_VtxBuffer = NULL;

	m_StopJudge = false;

	m_PolygonNumCnt = 0;
}

//◇-----------------------------------◇
//CSceneMeshOrbitのデストラクタ
//◇-----------------------------------◇
CSceneMeshOrbit::~CSceneMeshOrbit()
{

}

//◇-----------------------------------◇
//CSceneMeshOrbitの初期化処理
//◇-----------------------------------◇
HRESULT CSceneMeshOrbit::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//***頂点情報の設定***
	//****頂点バッファの設定****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D)) * (NUM_ORBIT * 2 + 2),D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_VtxBuffer,NULL);
	
	//===================頂点バッファデータをロック==========================
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);
		
	for(int i = 0;i < NUM_ORBIT * 2 + 2;i++)
	{
		m_aPosRecorder[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_aPosColor[i] = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
		
		m_pVtx[i].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_pVtx[i].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
		m_pVtx[i].col = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);

		if(i%2 == 0){
			m_pVtx[i].tex = D3DXVECTOR2(1.0f/((NUM_ORBIT * 2 + 1) - i),1.0f);
		}
		else{
			m_pVtx[i].tex = D3DXVECTOR2(1.0f/((NUM_ORBIT * 2 + 1) - i),1.0f);
		}
	}

	//============頂点バッファデータのロック解除============
	m_VtxBuffer->Unlock();
	
	return S_OK;
}

//◇-----------------------------------◇
//CSceneMeshOrbitの終了処理
//◇-----------------------------------◇
void CSceneMeshOrbit::Uninit(void)
{
	Release();

	//****各種リリース処理****
	if(m_VtxBuffer != NULL)
	{
		m_VtxBuffer -> Release();
		m_VtxBuffer = NULL;
	}
}

//◇-----------------------------------◇
//CSceneMeshOrbitの更新処理
//◇-----------------------------------◇
void CSceneMeshOrbit::Update(void)
{	
	//===================頂点バッファデータをロック==========================
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	for(int i = 0;i < NUM_ORBIT * 2 + 2;i++)
	{
		m_aPosColor[i].a -= 0.05f;
		if(m_aPosColor[i].a < 0.0f)
		{
			m_aPosColor[i].a = 0.0f;
		}

		m_pVtx[i].col = m_aPosColor[i];
		m_pVtx[i].pos = m_aPosRecorder[i];
	}

	//============頂点バッファデータのロック解除============
	m_VtxBuffer->Unlock();

	D3DXVECTOR3 PosOrbit[2] = {D3DXVECTOR3(0.0f,0.0f,0.0f)};
	D3DXCOLOR ColOrbit[2] = {D3DXCOLOR(0.0f,0.0f,0.0f,0.0f)};

	ColOrbit[0] = m_aPosColor[0];
	ColOrbit[1] = m_aPosColor[1];
	
	//座標変換
	D3DXVec3TransformCoord(&PosOrbit[0],&m_PointPosA,&m_TargetMatrix);
	D3DXVec3TransformCoord(&PosOrbit[1],&m_PointPosB,&m_TargetMatrix);

	for(int i = 0;i < NUM_ORBIT;i++)
	{
		m_aPosRecorder[i * 2] = m_aPosRecorder[(i + 1) * 2];
		m_aPosRecorder[i * 2 + 1] = m_aPosRecorder[(i + 1) * 2 + 1];

		m_aPosColor[i * 2] = m_aPosColor[(i + 1) * 2];
		m_aPosColor[i * 2 + 1] = m_aPosColor[(i + 1) * 2 + 1];
	}

	m_aPosRecorder[NUM_ORBIT * 2] = PosOrbit[0];
	m_aPosRecorder[NUM_ORBIT * 2 + 1] = PosOrbit[1];

	m_aPosColor[NUM_ORBIT * 2] = m_PointColA;
	m_aPosColor[NUM_ORBIT * 2 + 1] = m_PointColB;

	if(m_StopJudge)
	{
		m_PolygonNumCnt += 2;

		if(m_PolygonNumCnt >= NUM_ORBIT * 2)
			m_PolygonNumCnt = NUM_ORBIT * 2;

	}
	else
	{
		m_PolygonNumCnt -= 6;

		if(m_PolygonNumCnt <= 0)
			m_PolygonNumCnt = 0;
	}
}

//◇-----------------------------------◇
//CSceneMeshOrbitの描画処理
//◇-----------------------------------◇
void CSceneMeshOrbit::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

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
	pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);	//設定
	
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE ,FALSE);

	//3Dポリゴンの描画
	pDevice->SetStreamSource(0,m_VtxBuffer,0,sizeof(VERTEX_3D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0,m_Texture);

	//消え方で数値が変わってくるので
	if(m_StopJudge)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,NUM_ORBIT * 2 - m_PolygonNumCnt,m_PolygonNumCnt);
	}
	else
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,m_PolygonNumCnt);
	}

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE ,TRUE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//◇-----------------------------------◇
//CSceneMeshOrbitのクリエイト
//◇-----------------------------------◇
CSceneMeshOrbit *CSceneMeshOrbit::Create(D3DXVECTOR3 PosA,D3DXVECTOR3 PosB,D3DXCOLOR ColorA,D3DXCOLOR ColorB)
{
	CSceneMeshOrbit *pSceneMeshOrbit;
	pSceneMeshOrbit = new CSceneMeshOrbit;

	pSceneMeshOrbit->m_PointPosA = PosA;
	pSceneMeshOrbit->m_PointPosB = PosB;

	pSceneMeshOrbit->m_PointColA = ColorA;
	pSceneMeshOrbit->m_PointColB = ColorB;

	pSceneMeshOrbit->Init();

	return pSceneMeshOrbit;
}

//◇-----------------------------------◇
//CSceneMeshOrbitのマトリクスのセット
//◇-----------------------------------◇
void CSceneMeshOrbit::SetOrbitMatrix(D3DXMATRIX matrix)
{
	m_TargetMatrix = matrix;
}

//◇-----------------------------------◇
//CSceneMeshOrbitのポジションのセット
//◇-----------------------------------◇
void CSceneMeshOrbit::SetOrbitPosition(D3DXVECTOR3 Pos)
{
	m_TargetPos = Pos;
}
