//◇-------------------------------------------------------------------------◇
//
//	File:CEnemyWaveのヘッダーファイル[CEnemyWave.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CENEMYWAVE_H_
#define _CENEMYWAVE_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "Cscene2D.h"

class CEnemy001;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CEnemyWave : public CScene2D
{
public:
	CEnemyWave(int nPriority = 20);
	virtual ~CEnemyWave();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);		//描画処理をしないために必要

	virtual void EnemyWave_First(int Num);
	virtual void EnemyWave_Second(int Num);

	static CEnemyWave *Create();

private:
	static const int ENEMYWAVE_MAX = 32;
	int m_WaveChangeJudge;

	CEnemy001 *m_pEnemyCounter[ENEMYWAVE_MAX];
};



#endif
