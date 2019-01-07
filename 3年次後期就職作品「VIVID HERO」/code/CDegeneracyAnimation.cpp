//◇-------------------------------------------------------------------------◇
//
//	File:CDegeneracyAnimationのファイル[CDegeneracyAnimation.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CDegeneracyAnimation.h"
#include "CScene3D.h"
#include "CManager.h"
#include "CTextureManager.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CDegeneracyAnimationのコンストラクタ
//◇-----------------------------------◇
CDegeneracyAnimation::CDegeneracyAnimation(int nPriority) : CDegeneracyPolygon(nPriority)
{
	m_DegeneracyPolygon_Max = DEGENERACYANIMATION_MAX;

	m_Anim_TexDivide_NumX = 10;
	m_Anim_TexDivide_NumY = 1;
	m_AnimTime = 60;

	m_LoopJudge = true;
	m_AnimationLoopJudge = true;
}

//◇-----------------------------------◇
//CDegeneracyAnimationのデストラクタ
//◇-----------------------------------◇
CDegeneracyAnimation::~CDegeneracyAnimation()
{

}


//◇-----------------------------------◇
//CDegeneracyAnimationの初期化処理
//◇-----------------------------------◇
HRESULT CDegeneracyAnimation::Init(void)
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

	//アニメーション用の処理
	m_pAnimTimeCnt = new int[m_DegeneracyPolygon_Max];

	for(int i = 0;i < m_DegeneracyPolygon_Max;i++)
	{
		m_pAnimTimeCnt[i] = 0;
	}

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
		TexCntx += (1.0f / m_Anim_TexDivide_NumX);

		//右側になったらみたいな
		if(nCnt % 2 == 1)
		{
			TexCntx = 0.0f;
			if(TexCnty == 0.0f)
				TexCnty += (1.0f / m_Anim_TexDivide_NumY);
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
//CDegeneracyAnimationのせっとおんりーとか
//◇-----------------------------------◇
void CDegeneracyAnimation::SetOnlyInit()
{

}

//◇-----------------------------------◇
//CDegeneracyAnimationの終了処理
//◇-----------------------------------◇
void CDegeneracyAnimation::Uninit(void)
{
	Release();

	SAFE_RELEASE(m_VtxBuffer);
	SAFE_RELEASE(m_IdxBuffer);

	SAFE_DELETE_ARRY(m_pAngle);
	SAFE_DELETE_ARRY(m_pLength);
	SAFE_DELETE_ARRY(m_pDegeneracyPolygonPos);
	SAFE_DELETE_ARRY(m_pPolygonExistJudge);
	SAFE_DELETE_ARRY(m_pDegeneracyPolygonRot);
	SAFE_DELETE_ARRY(m_pAnimTimeCnt);
	SAFE_DELETE_ARRY(m_VtxBox);
	SAFE_DELETE_ARRY(m_pPolygonUninitFlag);
}


//◇-----------------------------------◇
//CDegeneracyAnimationの更新処理
//◇-----------------------------------◇
void CDegeneracyAnimation::Update(void)
{
	int KetaCntX,KetaCntY;

	for(int i = 0;i < m_DegeneracyPolygonNum;i++)
	{
		if(m_pPolygonExistJudge[i])
		{
			KetaCntX = 0;
			KetaCntY = 0;

			//何番目の分割番号か

			int j = m_pAnimTimeCnt[i] / (m_AnimTime / (m_Anim_TexDivide_NumX * m_Anim_TexDivide_NumY));

			KetaCntY = j / m_Anim_TexDivide_NumX;
			KetaCntX = j % m_Anim_TexDivide_NumX;



			m_VtxBox[(i * 4) + 0].tex = D3DXVECTOR2((float)((1.0f / m_Anim_TexDivide_NumX) * KetaCntX),		(float)((1.0f / m_Anim_TexDivide_NumY) * KetaCntY));
			m_VtxBox[(i * 4) + 1].tex = D3DXVECTOR2((float)((1.0f / m_Anim_TexDivide_NumX) * (KetaCntX + 1)),	(float)((1.0f / m_Anim_TexDivide_NumY) * KetaCntY));
			m_VtxBox[(i * 4) + 2].tex = D3DXVECTOR2((float)((1.0f / m_Anim_TexDivide_NumX) * KetaCntX),		(float)((1.0f / m_Anim_TexDivide_NumY) * (KetaCntY + 1)));
			m_VtxBox[(i * 4) + 3].tex = D3DXVECTOR2((float)((1.0f / m_Anim_TexDivide_NumX) * (KetaCntX + 1)),	(float)((1.0f / m_Anim_TexDivide_NumY) * (KetaCntY + 1)));
			
			m_pAnimTimeCnt[i] += 1;
			
			if(m_pAnimTimeCnt[i] > m_AnimTime)
			{
				if(m_AnimationLoopJudge)
				{
					m_pAnimTimeCnt[i] = 0;
				}
				else
				{
					m_pAnimTimeCnt[i] = 0;

					ParticleUninitPosition(i);
				}
			}
		}
		else
		{
			m_pAnimTimeCnt[i] = 0;
		}
	}
}

//◇-----------------------------------◇
//CDegeneracyAnimationのクリエイト
//◇-----------------------------------◇
CDegeneracyAnimation *CDegeneracyAnimation::Create(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,int DivideNumX,int DivideNumY,int AnimTime)
{
	CDegeneracyAnimation *pDegeneracyAnim;
	pDegeneracyAnim = new CDegeneracyAnimation;

	pDegeneracyAnim->m_TexName = TexName;
	pDegeneracyAnim->m_Pos = Pos;
	pDegeneracyAnim->m_Rot = Rot;
	pDegeneracyAnim->m_Anim_TexDivide_NumX = DivideNumX;
	pDegeneracyAnim->m_Anim_TexDivide_NumY = DivideNumY;

	pDegeneracyAnim->m_AnimTime = AnimTime;

	pDegeneracyAnim->Init();

	return pDegeneracyAnim;
}


