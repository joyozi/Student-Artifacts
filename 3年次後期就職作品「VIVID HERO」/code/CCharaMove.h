//��-------------------------------------------------------------------------��
//
//	File:CCharaMove�̃w�b�_�[�t�@�C��[CCharaMove.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CCHARAMOVE_H_
#define _CCHARAMOVE_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "main.h"

class CPlayerModel;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
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
