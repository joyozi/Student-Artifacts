//◇-------------------------------------------------------------------------◇
//
//	File:CPlayerMotionPatternRapidDownのファイル[CPlayerMotionPatternRapidDown.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CPlayerMotionPatternRapidDown.h"
#include "CPlayerMotionPatternNormal.h"

#include "CPlayerModel.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CPlayerMotionPatternRapidDownのコンストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternRapidDown::CPlayerMotionPatternRapidDown(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_RAPIDDOWN);
	m_MoveDownCnt = 0;
}

//◇-----------------------------------◇
//CPlayerMotionPatternRapidDownのデストラクタ
//◇-----------------------------------◇
CPlayerMotionPatternRapidDown::~CPlayerMotionPatternRapidDown()
{

}

//◇-----------------------------------◇
//CPlayerMotionPatternRapidDownの更新処理
//◇-----------------------------------◇
void CPlayerMotionPatternRapidDown::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	pPlayer->SetPosition(pPlayer->GetPosition() + D3DXVECTOR3(0.0f,-100.0f,0.0f));
	pModelMotion->SetActCommand(PMOVE_RAPIDDOWN);

	m_MoveDownCnt++;

	//こっちはモーションが一個しかないのでタイムで計算してる
	if(m_MoveDownCnt >= 15)
	{
		pPlayer->MotionPatternChange(new CPlayerMotionPatternNormal(pModelMotion));
		pPlayer->SetPlayerSpeed(D3DXVECTOR3(0.0f,-30.0f,0.0f));
	}
	
}