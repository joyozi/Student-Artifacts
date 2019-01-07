//◇-------------------------------------------------------------------------◇
//
//	File:CBulletPatternEnemy001のヘッダーファイル[CBulletPatternEnemy001.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CBulletPatternEnemy001_H_
#define _CBulletPatternEnemy001_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CBulletPattern.h"

class CEnemy001;
class Cscene;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CBulletPatternEnemy001 : public CBulletPattern
{
public:
	CBulletPatternEnemy001();
	virtual ~CBulletPatternEnemy001();

	virtual void Update_Enemy001(CEnemy001 *Shooter)override;

private:
	static const int DEGENERACYSIMPLEINFO_MAX = 64;

	int m_MuzzleCnt;
	int m_ShotCnt;
	
protected:
	DEGENERACYINFO_SIMPLE m_DegeneracySimpleInfo[DEGENERACYSIMPLEINFO_MAX];
	int m_SimpleInfoCnt;
};

#endif
