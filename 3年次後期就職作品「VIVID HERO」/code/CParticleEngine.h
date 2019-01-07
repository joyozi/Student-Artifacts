//◇-------------------------------------------------------------------------◇
//
//	File:CParticleEngineのヘッダーファイル[CParticleEngine.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPARTICLEENGINE_H_
#define _CPARTICLEENGINE_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CParticleSystem.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CParticleEngine : public CParticleSystem
{
public:
	CParticleEngine(int nPriority = 60);
	virtual ~CParticleEngine();
	
	virtual void Update(void);
	
	virtual void SetEngineSpeedUp(float Speed){m_Speed = Speed;}
	virtual float GetEngineSpeedUp(){return m_Speed;}

	static CParticleEngine *Create(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 PopRot,float Width,float Height,
		int LifeTime,int StartDelay,float PopRate,D3DXVECTOR3 VecForce,float Speed,bool Loop,float ConeAngle,float ConeRadius);

private:
	static const int PARTICLEENGINE_MAX = 100;

	float m_OriginalTexLength[PARTICLEENGINE_MAX];

};



#endif
