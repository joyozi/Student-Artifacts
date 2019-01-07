//◇-------------------------------------------------------------------------◇
//
//	File:CEnemyBullet001のヘッダーファイル[CEnemyBullet001.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CENEMYBULLET001_H_
#define _CENEMYBULLET001_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CBullet001.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CEnemyBullet001 : public CBullet001
{
public:
	CEnemyBullet001();
	virtual ~CEnemyBullet001();

	virtual void Update(void);
	virtual void CollisionAction(CLASS_TYPE Type,int Num)override;
	bool CollisionTargetSheet(CLASS_TYPE Type);

	static CEnemyBullet001 *Create();

private:
	static const int ENEMYBULLET001_TEXNUM = 30;
	static const int ENEMYBULLET001_NUMMAX = 40;
	static const int ENEMYBULLET001_MAX = ENEMYBULLET001_TEXNUM * ENEMYBULLET001_NUMMAX;
	static const int ENEMYBULLET001_LIFEMAX = 120;
};


#endif
