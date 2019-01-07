//◇-------------------------------------------------------------------------◇
//
//	File:CBulletPatternEnemy000のファイル[CBulletPatternEnemy000.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CBulletPatternEnemy000.h"
#include "CEnemyBullet000.h"
#include "input.h"
#include "CManager.h"
#include "CEnemy000.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CBulletPatternEnemy000のコンストラクタ
//◇-----------------------------------◇
CBulletPatternEnemy000::CBulletPatternEnemy000()
{

}

//◇-----------------------------------◇
//CBulletPatternEnemy000のデストラクタ
//◇-----------------------------------◇
CBulletPatternEnemy000::~CBulletPatternEnemy000()
{

}

//◇-----------------------------------◇
//CBulletPatternEnemy000の更新処理
//◇-----------------------------------◇
void CBulletPatternEnemy000::Update_Enemy000(CEnemy000 *Shooter)
{
	CScene *irekoScene = NULL;
	CScene::SearchLinkList(&irekoScene,CTYPE_PLAYERMODEL);

	if(irekoScene != NULL && rand()%180 == 0)
	{
		CEnemyBullet000::Create(Shooter->GetPosition(),irekoScene->GetPosition() );
	}
}
