//◇-------------------------------------------------------------------------◇
//
//	File:CCharaMoveのヘッダーファイル[CCharaMove.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CCHARAMOVE_H_
#define _CCHARAMOVE_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "main.h"

class CPlayerModel;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CCharaMove
{
public:
	CCharaMove();
	virtual ~CCharaMove();

	static void CharaMoveRobo(CPlayerModel *pPlayer,float CameraRad,float MaxSpeed);
	static void AddPositionRe(D3DXVECTOR3 *Pos,D3DXVECTOR3 *Rot,D3DXVECTOR3 CameraRot,float MoveSpeed);
	static void InputMove(D3DXVECTOR3 *Pos,D3DXVECTOR3 *Rot,float MoveSpeed);
	static void SimpleMovePosition(D3DXVECTOR3 *Pos,D3DXVECTOR3 *Rot,float CameraRadY,float MoveSpeed);


};


#endif
