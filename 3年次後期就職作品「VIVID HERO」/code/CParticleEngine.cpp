//◇-------------------------------------------------------------------------◇
//
//	File:CParticleEngineのファイル[CParticleEngine.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CParticleEngine.h"
#include "CItemList.h"
#include "input.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CParticleEngineのコンストラクタ
//◇-----------------------------------◇
CParticleEngine::CParticleEngine(int nPriority) : CParticleSystem(nPriority)
{
	m_Type = CTYPE_PARTICLESYSTEM;

	m_DegeneracyPolygon_Max = PARTICLEENGINE_MAX;
}

//◇-----------------------------------◇
//CParticleEngineのデストラクタ
//◇-----------------------------------◇
CParticleEngine::~CParticleEngine()
{

}

//◇-----------------------------------◇
//CParticleEngineの更新処理
//◇-----------------------------------◇
void CParticleEngine::Update(void)
{
	float MoveRot,MoveCenterToLength;				//何度かと中心からどれくらいの距離か
	D3DXVECTOR3 PopPos = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_PopTimeCnt += m_PopRate;

	//先に現在の回転行列を計算
	D3DXMATRIX mtxRot_Sphere;
	D3DXMatrixRotationYawPitchRoll(&mtxRot_Sphere,m_PopRot.y,m_PopRot.x,m_PopRot.z);		//ヨ－　ピッチ　ロール

	
	
	//それぞれの位置の移動
	for(int i = 0;i < m_DegeneracyPolygon_Max;i++)
	{
		if(m_pPolygonExistJudge[i])
		{
			m_pParticleInfo[i].Pos += m_Speed * m_pParticleInfo[i].MoveVec;
		}
	}



	//何秒に1っこ生成するか
	for(;m_PopTimeCnt >= 1.0f;m_PopTimeCnt--)
	{
		//位置のランダム生成
		MoveRot = CItemList::ConvRadian((float)(rand()%360));

		if(m_ConeRadius != 0.0f){
			MoveCenterToLength = (float)(rand()%(int)(m_ConeRadius));

			PopPos.x = MoveCenterToLength * cosf(MoveRot);
			PopPos.z = MoveCenterToLength * sinf(MoveRot);
		}
		else
		{
			PopPos.x = 0.0f;
			PopPos.z = 0.0f;
		}




		D3DXVECTOR3 KariPos = PopPos;

		//発生位置の座標変換
		D3DXVec3TransformCoord(&PopPos,&PopPos,&mtxRot_Sphere);

		//ポリゴンセット&番号の取得
		int a = SetPolygon(PopPos + m_Pos,D3DXVECTOR3(0.0f,0.0f,0.0f),m_TexWidth,m_TexHeight);

		//ポリゴンを作成可能だったら
		if(a != -1)
		{
			m_OriginalTexLength[a] = m_pLength[a];

			//後で使えるように保存
			m_pParticleInfo[a].Pos = KariPos;
			m_pParticleInfo[a].PopRot = m_PopRot;

			//==========動いてく角度の設定===========
			//Posからの距離
			float VecLength = CItemList::GetLength(KariPos,D3DXVECTOR3(0.0f,0.0f,0.0f));

			m_pParticleInfo[a].MoveRot.x = MoveRot;
			m_pParticleInfo[a].MoveRot.y = m_ConeAngle * (VecLength / m_ConeRadius);
			m_pParticleInfo[a].MoveRot.z = MoveRot;

			m_pParticleInfo[a].MoveVec.x = +1.0f * sinf(m_pParticleInfo[a].MoveRot.y) * cosf(m_pParticleInfo[a].MoveRot.x);
			m_pParticleInfo[a].MoveVec.y = +1.0f * cosf(m_pParticleInfo[a].MoveRot.y);
			m_pParticleInfo[a].MoveVec.z = +1.0f * sinf(m_pParticleInfo[a].MoveRot.y) * sinf(m_pParticleInfo[a].MoveRot.x);



			D3DXVec3Normalize(&m_pParticleInfo[a].MoveVec,&m_pParticleInfo[a].MoveVec);
		}
	}



	for(int i = 0;i < m_DegeneracyPolygon_Max;i++)
	{
		if(m_pPolygonExistJudge[i])
		{
			D3DXVECTOR3 TransPos = m_pParticleInfo[i].Pos;

		//発生位置の座標変換
			D3DXMATRIX mtxRot;
			D3DXMatrixRotationYawPitchRoll(&mtxRot,m_pParticleInfo[i].PopRot.y,m_pParticleInfo[i].PopRot.x,m_pParticleInfo[i].PopRot.z);
			D3DXVec3TransformCoord(&TransPos,&TransPos,&mtxRot);

			ParticleSetPosition(i,TransPos);
			

			
			//サイズの調整
			m_pLength[i] -= m_OriginalTexLength[i] / (float)(m_LifeTime*4);
			


			//ライフの計算
			m_pParticleInfo[i].LifeCnt++;

			if(m_pParticleInfo[i].LifeCnt >= m_LifeTime)
			{
				m_pParticleInfo[i].LifeCnt = 0;

				ParticleUninitPosition(i);

				//最後のが消えたら殺す
				if(i == m_DegeneracyPolygon_Max - 1 && m_LoopJudge == false)
				{
					Uninit();
				}
			}
		}
	}
}

//◇-----------------------------------◇
//CParticleEngineのクリエイト
//◇-----------------------------------◇
CParticleEngine *CParticleEngine::Create(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 PopRot,float Width,float Height,
		int LifeTime,int StartDelay,float PopRate,D3DXVECTOR3 VecForce,float Speed,bool Loop,
		float ConeAngle,float ConeRadius)
{
	CParticleEngine *pParticleSystem;
	pParticleSystem = new CParticleEngine;

	pParticleSystem->m_TexName = TexName;
	pParticleSystem->m_Pos = Pos;
	pParticleSystem->m_PopRot = PopRot;
	pParticleSystem->m_TexWidth = Width;
	pParticleSystem->m_TexHeight = Height;
	pParticleSystem->m_LifeTime = LifeTime;
	pParticleSystem->m_StartDelay = StartDelay;

	pParticleSystem->m_PopRate = PopRate / 60.0f;

	pParticleSystem->m_VecForce = VecForce;
	pParticleSystem->m_Speed = Speed;
	pParticleSystem->m_LoopJudge = Loop;
	pParticleSystem->m_ConeAngle = ConeAngle;
	pParticleSystem->m_ConeRadius = ConeRadius;

	pParticleSystem->m_ParticleRenderMode = P_REN_BILLBOARD;
	pParticleSystem->m_ParticleType = PARTICLE_CONE;

	pParticleSystem->Init();

	return pParticleSystem;
}

