//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionChangerのファイル[CPlayerMotionChanger.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CPlayerMotionChanger.h"

#include "CPlayerModel.h"
#include "CSceneModelMotion.h"
#include "CPlayerMotionPattern.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CPlayerMotionChangerのコンストラクタ
//◇-----------------------------------◇
CPlayerMotionChanger::CPlayerMotionChanger(CPlayerMotionPattern *pPattern) : m_pPatternNow(pPattern)
{

}

//◇-----------------------------------◇
//CPlayerMotionChangerのデストラクタ
//◇-----------------------------------◇
CPlayerMotionChanger::~CPlayerMotionChanger()
{
	delete m_pPatternNow;
}

//◇-----------------------------------◇
//CPlayerMotionChangerの更新処理
//◇-----------------------------------◇
void CPlayerMotionChanger::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	m_pPatternNow->Update(pPlayer,pModelMotion);
}

//◇-----------------------------------◇
//CPlayerMotionChangerのパターン変更
//◇-----------------------------------◇
void CPlayerMotionChanger::ChangedPattern(CPlayerMotionPattern *pPattern)
{
	if(m_pPatternNow != pPattern)
	{
		CPlayerMotionPattern *pChangePattern = m_pPatternNow;

		delete pChangePattern;
		pChangePattern = NULL;

		m_pPatternNow = pPattern;
	}
}


