//◇-------------------------------------------------------------------------◇
//
//	File:CMiniMapのヘッダーファイル[CMiniMap.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CMINIMAP_H_
#define _CMINIMAP_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CScene2D.h"
#include "CEnemy001.h"

class CEnemyIcon;
class CScore;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CMiniMap : public CScene2D
{
public:
	CMiniMap(int nPriority = 10);
	virtual ~CMiniMap();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CMiniMap *Create();

	static void MiniMapEnemySet(CEnemy001 *pEnemy);
	static void MiniMapEnemyRemove(CEnemy001 *pEnemy);

private:
	static const int				ENEMYICON_MAX = 16;
	static const int				ENEMY_MAXNUM = 23;

	static int						m_StaticEnemyNum;
	static std::vector<CEnemy001*>	m_pEnemyBucket;

	D3DXVECTOR3						m_MiniMapPos;
	D3DXVECTOR3						m_MiniMapSize;
	CScene2D*						m_pPlayerTex;
	CEnemyIcon*						m_pEnemyIcon[16];
	CScore*							m_pScorePointer;

};


#endif
