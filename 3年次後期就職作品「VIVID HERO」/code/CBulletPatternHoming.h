//◇-------------------------------------------------------------------------◇
//
//	File:CBulletPatternHomingのヘッダーファイル[CBulletPatternHoming.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CBulletPatternHoming_H_
#define _CBulletPatternHoming_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CBulletPattern.h"
#include "CBullet000.h"
#include "input.h"
#include "CManager.h"
#include "CPlayerModel.h"
#include "CCamera.h"
#include "CBulletHoming.h"

class Cscene;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CBulletPatternHoming : public CBulletPattern
{
public:
	CBulletPatternHoming(){}
	virtual ~CBulletPatternHoming(){}

	virtual void Update_Player(CPlayerModel *Shooter)override
	{
		if(CInput::GetKeyboardTrigger(DIK_B))
		{
//			CBulletHoming::Create(Shooter->GetPosition(), CManager::GetCameraPointer()->GetCameraR());
		}
	}
};

#endif
