//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionChangerのヘッダーファイル[CPlayerMotionChanger.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CPLAYERMOTIONCHANGER_H_
#define _CPLAYERMOTIONCHANGER_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include <Windows.h>

class CPlayerMotionPattern;
class CPlayerModel;
class CSceneModelMotion;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CPlayerMotionChanger
{
public:
	CPlayerMotionChanger(CPlayerMotionPattern *pPattern);
	virtual ~CPlayerMotionChanger();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);
	
	virtual void ChangedPattern(CPlayerMotionPattern *pPattern);



private:
	CPlayerMotionPattern *m_pPatternNow;
};


#endif
