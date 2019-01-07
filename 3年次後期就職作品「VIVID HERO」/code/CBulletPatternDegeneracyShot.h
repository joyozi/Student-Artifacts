//◇-------------------------------------------------------------------------◇
//
//	File:CBulletPatternDegeneracyShotのヘッダーファイル[CBulletPatternDegeneracyShot.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CBulletPatternDegeneracyShot_H_
#define _CBulletPatternDegeneracyShot_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CBulletPattern.h"

class CBullet001;
class Cscene;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CBulletPatternDegeneracyShot : public CBulletPattern
{
public:
	CBulletPatternDegeneracyShot();

	virtual ~CBulletPatternDegeneracyShot();

	virtual void Update_Player(CPlayerModel *Shooter)override;

private:
	static const int DEGENERACYSIMPLEINFO_MAX = 256;

	CBullet001 *m_pBulletPointer;
	int m_ShotCnt;

protected:
	DEGENERACYINFO_SIMPLE m_DegeneracySimpleInfo[DEGENERACYSIMPLEINFO_MAX];
	int m_SimpleInfoCnt;
};

#endif
