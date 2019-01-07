//◇-------------------------------------------------------------------------◇
//
//	File:CDegeneracyAnimationのヘッダーファイル[CDegeneracyAnimation.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CDEGENERACYANIMATION_H_
#define _CDEGENERACYANIMATION_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CDegeneracyPolygon.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CDegeneracyAnimation : public CDegeneracyPolygon
{
public:
	CDegeneracyAnimation(int nPriority = 52);
	virtual ~CDegeneracyAnimation();

	virtual HRESULT Init(void);
	virtual void SetOnlyInit(void);
	virtual void Uninit(void);
	virtual void Update(void);
	
	static CDegeneracyAnimation *Create(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,int DivideNumX,int DivideNumY,int AnimTime);
	
private:
	static const int DEGENERACYANIMATION_MAX = 1000;
	
protected:
	int m_Anim_TexDivide_NumX;		//テクスチャを何分割するか
	int m_Anim_TexDivide_NumY;

	int m_AnimTime;					//何秒かけてアニメーションするか
	int *m_pAnimTimeCnt;			//縮退ポリゴンそれぞれのカウント


	bool m_AnimationLoopJudge;
};


#endif
