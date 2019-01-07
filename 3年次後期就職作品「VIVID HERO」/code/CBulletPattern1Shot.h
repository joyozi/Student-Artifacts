//◇-------------------------------------------------------------------------◇
//
//	File:CBulletPattern1Shotのヘッダーファイル[CBulletPattern1Shot.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CBULLETPATTERN1SHOT_H_
#define _CBULLETPATTERN1SHOT_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CBulletPattern.h"
#include "CBullet000.h"
#include "input.h"
#include "CManager.h"
#include "CPlayerModel.h"
#include "CCamera.h"

class Cscene;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CBulletPattern1Shot : public CBulletPattern
{
public:
	CBulletPattern1Shot(){}
	virtual ~CBulletPattern1Shot(){}

	virtual void Update_Player(CPlayerModel *Shooter)override{
	
		if(CInput::GetKeyboardTrigger(DIK_SPACE))
		{
			CPlayerModel *pPlayer = (CPlayerModel*)Shooter;
				
			D3DXVECTOR3 PartsPos = D3DXVECTOR3(0.0f,-70.0f,0.0f);
			D3DXMATRIX PlayerMtx = pPlayer->GetPlayerPartsMatrix(8);

			D3DXMATRIX Matrix;

			D3DXMatrixIdentity(&Matrix);
			D3DXMatrixMultiply(&Matrix,&Matrix,&pPlayer->GetPlayerPartsMatrix(8));

			D3DXVec3TransformCoord(&PartsPos,&PartsPos,&Matrix);

			CBullet000::Create(PartsPos, CManager::GetCameraPointer()->GetCameraR());
		}
	}
};

#endif
