//◇-------------------------------------------------------------------------◇
//
//	File:CExplosionのヘッダーファイル[CExplosion.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CEXPLOSION_H_
#define _CEXPLOSION_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CSceneBillboard.h"
#include "CManager.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CExplosion : public CSceneBillboard
{
public:
	CExplosion(int nPriority = 22);

	HRESULT Init(void);
	void Update(void);
	
	static CExplosion *Create(LPCTSTR TextureName,float PosX,float PosY,float PosZ,float TexWidth,float TexHeight);

private:
	static const int	EXPLOSION_SEPARATE_NUM = 7;	//爆発アニメーションのテクスチャを何分割するか
	static const int	EXPLOSION_COUNT = 5;			//何秒でアニメを切り替えるか
	int					m_CounterAnim;								//アニメが変わっていくカウント
	int					m_PatternAnim;								//何番目のアニメか
};

#endif
