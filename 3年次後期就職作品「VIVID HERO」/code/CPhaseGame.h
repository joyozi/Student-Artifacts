//◇-------------------------------------------------------------------------◇
//
//	File:CPhaseGameのヘッダーファイル[CPhaseGame.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPHASEGAME_H_
#define _CPHASEGAME_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CPhase.h"

class CPause;
class CCamera;
class CExplosion000;
class CPlayerModel;
class CEnemyBullet001;
class CGameStart;

typedef enum{
	EX_00 = 0,
	EX_01,
	EX_02_SMOG,
	EX_03_BIGBANG,
	EX_04_MAZZLEFLASH,
	EX_05_NORMALEX,

	EX_MAX
}EXPLOSION_TYPE;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPhaseGame : public CPhase
{
public:
	CPhaseGame(PHASE Phase = PHASE_GAME);
	virtual ~CPhaseGame();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CPhaseGame *GetPhaseGamePointer(void){return m_pPhaseGame;}
	static CExplosion000 *GetExplosionPointer(int ExplosionNum){return m_pExplosionPointer[ExplosionNum];}
	static CEnemyBullet001 *GetEnemyBullet001Pointer(){return m_pEnemyBullet001Pointer;}

private:
	CCamera*				m_pCameraGame;
	CPause*					m_pPause;
	bool					m_PauseJudge;
	CPlayerModel*			m_pPlayerModel;
	static CPhaseGame*		m_pPhaseGame;
	static CExplosion000*	m_pExplosionPointer[EX_MAX];
	static CEnemyBullet001*	m_pEnemyBullet001Pointer;

	CGameStart*				m_pGameStartPointer;
};


#endif
