//◇-------------------------------------------------------------------------◇
//
//	File:CBulletPatternNoneのヘッダーファイル[CBulletPatternNone.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CBulletPatternNone_H_
#define _CBulletPatternNone_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CBulletPattern.h"

class Cscene;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CBulletPatternNone : public CBulletPattern
{
public:
	CBulletPatternNone(){}
	virtual ~CBulletPatternNone(){}

	
	virtual void Update_Enemy000(CEnemy000 *Shooter) override{}
	virtual void Update_Enemy001(CEnemy001 *Shooter) override{}
	virtual void Update_Player(CPlayerModel *Shooter) override{}
};


#endif
