//◇-------------------------------------------------------------------------◇
//
//	File:CBulletPatternEnemy000のヘッダーファイル[CBulletPatternEnemy000.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CBulletPatternEnemy000_H_
#define _CBulletPatternEnemy000_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CBulletPattern.h"

class Cscene;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CBulletPatternEnemy000 : public CBulletPattern
{
public:
	CBulletPatternEnemy000();
	virtual ~CBulletPatternEnemy000();

	virtual void Update_Enemy000(CEnemy000 *Shooter)override;
};

#endif
