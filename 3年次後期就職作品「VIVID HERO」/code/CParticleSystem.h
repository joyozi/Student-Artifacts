//◇-------------------------------------------------------------------------◇
//
//	File:CParticleSystemのヘッダーファイル[CParticleSystem.h]
//	Author:当摩好弘
//
//	同じポリゴンを繰り返し使うタイプのパーティクル。
//	最大量が決まってるから普通と少し違うかも。縮退ポリゴン製
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPARTICLESYSTEM_H_
#define _CPARTICLESYSTEM_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CDegeneracyPolygon.h"

//◇-----------------------------------◇
//enum
//◇-----------------------------------◇
//パーティクルの発生する向きの型
typedef enum{
	PARTICLE_CONE,
	PARTICLE_SPHERE,
	PARTICLE_EDGE,
	PARTICLE_ENGINE,
	PARTICLE_MAX
}PARTICLE_TYPE;

//ビルボードのテクスチャの向き。どの向きのビルボードか
typedef enum{
	P_REN_BILLBOARD,
	P_REN_HORIZONAL,
	P_REN_VERTICAL,
	P_REN_STRETCHIED,
	P_REN_MAX
}PARTICLE_RENDERERMODE;

typedef struct{
	D3DXVECTOR3		Pos;
	D3DXVECTOR3		Rot;
	D3DXVECTOR3		StartPopPos;
	D3DXVECTOR3		MoveRot;			//範囲内のどこから出現したかの角度
	D3DXVECTOR3		PopRot;				//出現した時の全体の角度
	D3DXVECTOR3		MoveVec;			//球で使う
	int				LifeCnt;
	int				EngineTimeCnt;
}PARTICLE_INFO;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CParticleSystem : public CDegeneracyPolygon
{
public:
	CParticleSystem(int nPriority = 60);
	virtual ~CParticleSystem();
	
	virtual void Uninit();
	virtual void Update(void);
	
	virtual void SetParticleChangeRotation(D3DXVECTOR3 Rot);

	static CParticleSystem *CreateCone(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 PopRot,float Width,float Height,
		int LifeTime,int StartDelay,float PopRate,D3DXVECTOR3 VecForce,float Speed,bool Loop,float ConeAngle,float ConeRadius);

	static CParticleSystem *CreateSphere(LPCTSTR TexName,D3DXVECTOR3 Pos,float Width,float Height,
		int LifeTime,int StartDelay,float PopRate,D3DXVECTOR3 VecForce,float Speed,bool Loop,float SphereRadius);


private:
	static const int		PARTICLESYSTEM_MAX = 100;

protected:
	PARTICLE_TYPE			m_ParticleType;
	PARTICLE_RENDERERMODE	m_ParticleRenderMode;

	float					m_PopTimeCnt;
	int						m_LifeTime;				//パーティクル一個の生命期限
	int						m_StartDelay;			//パーティクルの出始める時間
	float					m_PopRate;			//1秒間に何個パーティクルが発生するか
	float					m_GravityModifier;	//重力にどれくらい反抗するか
	D3DXVECTOR3				m_VecForce;		//むきにかかる力
	float					m_Speed;
	bool					m_GravityJudge;		//重力の影響を受けるか否か
	PARTICLE_INFO*			m_pParticleInfo;

	//CONE時の数値
	float					m_ConeAngle;			//発生のむき
	float					m_ConeRadius;			//発生源の大きさ
	D3DXVECTOR3				m_PopRot;		//発生していく角度

	//スフィアのサイズ
	float					m_SphereRadius;
};



#endif
