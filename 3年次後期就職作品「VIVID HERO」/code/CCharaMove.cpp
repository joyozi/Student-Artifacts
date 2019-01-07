//��-------------------------------------------------------------------------��
//
//	File:CCharaMove�̃t�@�C��[CCharaMove.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CCharaMove.h"
#include "input.h"
#include "joystick.h"
#include "CItemList.h"
#include "CItemList.h"
#include "CPlayerModel.h"

#include "CDebugProc.h"
#include "CManager.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CCharaMove�̃R���X�g���N�^
//��-----------------------------------��
CCharaMove::CCharaMove()
{

}

//��-----------------------------------��
//CCharaMove�̃f�X�g���N�^
//��-----------------------------------��
CCharaMove::~CCharaMove()
{

}

//��-----------------------------------��
//CCharaMove�̉F���퓬���{�b�g��p�ړ��֐�
//��-----------------------------------��
void CCharaMove::CharaMoveRobo(CPlayerModel *pPlayer,float CameraRad,float MaxSpeed)
{
	float LeapSpeed			 = 0.3f;		//���`��Ԃ̃X�s�[�h

	D3DXVECTOR3 MovePos		 = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 MoveRot		 = D3DXVECTOR3(0.0f,pPlayer->GetRotation().y,0.0f);

#ifdef JOYSTIKON

	D3DXVECTOR3 JoyStickNum = D3DXVECTOR3(GetJoysticklX(),GetJoysticklY(),0.0f);
	//�X�e�B�b�N�p�x�擾
	float StickRotL = CItemList::VecAngle_2DSimple(D3DXVECTOR3(JoyStickNum.x,0.0f,-JoyStickNum.y));

	//�p�x�̃Z�b�g
	D3DXVECTOR3 PlayerRot = D3DXVECTOR3(0.0f,
										CItemList::RotationOptisitacion(StickRotL + CameraRad + D3DX_PI),
										0.0f);

	PlayerRot.y = CItemList::lerp(pPlayer->GetRotation().y,PlayerRot.y,0.3f);
	pPlayer->SetRotation(PlayerRot);
	
	//�X�e�B�b�N�����삳��Ă��瓮��
	if(JoyStickNum.x >= 200 || JoyStickNum.x <= -200
	|| JoyStickNum.y >= 200 || JoyStickNum.y <= -200)
	{
		MovePos.x = Speed * sinf(+PlayerRot.y + D3DX_PI);
		MovePos.z = Speed * cosf(+PlayerRot.y + D3DX_PI);
	}

	if(GetJoystickPress(JS_LB))		MovePos.y -= MaxSpeed;
	if(GetJoystickPress(JS_RB))		MovePos.y += MaxSpeed;

	float MoveRot = atan2f(abs(MovePos.y),abs(MovePos.x) + abs(MovePos.z));

	MovePos.x = MovePos.x * cosf(MoveRot);
	MovePos.y = MovePos.y * sinf(MoveRot);
	MovePos.z = MovePos.z * cosf(MoveRot);

#else
	//�v���C���p�x�̌v�Z
	SimpleMovePosition(&MovePos,&MoveRot,CameraRad,MaxSpeed);
	MoveRot.y = CItemList::RotationOptisitacion(MoveRot.y,pPlayer->GetRotation().y);

	if(CInput::GetKeyboardPress(DIK_Q)) MovePos.y = -MaxSpeed;
	if(CInput::GetKeyboardPress(DIK_E)) MovePos.y = MaxSpeed;

#endif
	MoveRot = CItemList::Vec3lerp(pPlayer->GetRotation(),MoveRot,0.05f);

	MoveRot.y = CItemList::RotationOptisitacion(MoveRot.y);
	pPlayer->SetRotation(D3DXVECTOR3(MoveRot.x,MoveRot.y,MoveRot.z));


	
	float MoveAngle = atan2f(abs(MovePos.y),abs(MovePos.x) + abs(MovePos.z));

	MovePos.x = MovePos.x * cos(MoveAngle);
	MovePos.y = MovePos.y * sinf(MoveAngle);
	MovePos.z = MovePos.z * cos(MoveAngle);

	MovePos = CItemList::Vec3lerp(pPlayer->GetPlayerSpeed(),MovePos,0.05f);
	pPlayer->SetPlayerSpeed(MovePos);
	pPlayer->SetPosition(pPlayer->GetPosition()+ 
							D3DXVECTOR3(MovePos.x,
							MovePos.y,
							MovePos.z));

	CDebugProc::Print("�v���C���X�s�[�h : %f \n",CItemList::GetLengthSimple(MovePos));
}

//��-----------------------------------��
//�ʒu�̈ړ�
//��-----------------------------------��
void CCharaMove::AddPositionRe(D3DXVECTOR3 *Pos,D3DXVECTOR3 *Rot,D3DXVECTOR3 CameraRot,float MoveSpeed)
{
	float Speed		 = MoveSpeed;
	float LeapSpeed	 = 0.3f;

	if(CInput::GetKeyboardPress(DIK_V))
	{
		Speed = MoveSpeed * 3.0f;
	}

	if(CInput::GetKeyboardPress(DIK_W))
	{
		float GoRot = CameraRot.y + D3DX_PI;

		GoRot		 = CItemList::RotationOptisitacion(GoRot,Rot->y);
		Rot->y		 = CItemList::lerp(Rot->y,GoRot,LeapSpeed);

		Pos->x		 += Speed * sinf(CameraRot.y);
		Pos->z		 += Speed * cosf(CameraRot.y);
	}

	if(CInput::GetKeyboardPress(DIK_S))
	{
		float GoRot = CameraRot.y;

		GoRot		 = CItemList::RotationOptisitacion(GoRot,Rot->y);
		Rot->y		 = CItemList::lerp(Rot->y,GoRot,LeapSpeed);

		Pos->x		 += Speed * sinf(CameraRot.y + D3DX_PI);
		Pos->z		 += Speed * cosf(CameraRot.y + D3DX_PI);
	}

	if(CInput::GetKeyboardPress(DIK_A))
	{
		float GoRot	 = CameraRot.y + D3DX_PI / 2;

		GoRot		 = CItemList::RotationOptisitacion(GoRot,Rot->y);
		Rot->y		 = CItemList::lerp(Rot->y,GoRot,LeapSpeed);

		Pos->x		 += Speed * sinf(CameraRot.y - D3DX_PI / 2);
		Pos->z		 += Speed * cosf(CameraRot.y - D3DX_PI / 2);
	}

	if(CInput::GetKeyboardPress(DIK_D))
	{
		float GoRot = CameraRot.y - D3DX_PI / 2;

		GoRot		 = CItemList::RotationOptisitacion(GoRot,Rot->y);
		Rot->y		 = CItemList::lerp(Rot->y,GoRot,LeapSpeed);

		Pos->x		 += Speed * sinf(CameraRot.y + D3DX_PI / 2);
		Pos->z		 += Speed * cosf(CameraRot.y + D3DX_PI / 2);
	}

	if(CInput::GetKeyboardPress(DIK_E))
	{
		Pos->y += Speed;
	}

	if(CInput::GetKeyboardPress(DIK_Q))
	{
		Pos->y -= Speed;
	}

	Rot->y = CItemList::RotationOptisitacion(Rot->y);
}


//��-----------------------------------��
//�L�����̈ړ�
//��-----------------------------------��
void CCharaMove::InputMove(D3DXVECTOR3 *Pos,D3DXVECTOR3 *Rot,float MoveSpeed)
{
	float Rot_Hikae				 = Rot->y;
	float GoRot					 = 0.0f;
	const float RotMoveSpeed	 = 0.1f;

	//===�v���C���[�̑O�ړ�=============
	//==================================
	if(CInput::GetKeyboardPress(DIK_W))
	{
		GoRot			 = D3DX_PI;
		float diffRotY	 = GoRot - Rot->y;

		GoRot = CItemList::RotationOptisitacion(diffRotY);
		if(diffRotY < -D3DX_PI)
		{
			GoRot += D3DX_PI * 2;
		}
		else if(diffRotY > D3DX_PI)
		{
			GoRot += -D3DX_PI * 2;
		}
		
		Rot->y = CItemList::lerp(Rot->y,GoRot,RotMoveSpeed);

		Pos->x -= sinf(GoRot) * MoveSpeed;
		Pos->z -= cosf(GoRot) * MoveSpeed;
	}
	
	//===�v���C���[�̌��ړ�============
	//===================================
	if(CInput::GetKeyboardPress(DIK_S))
	{
		GoRot				 = 0.0f;
		float diffRotY		 = GoRot - Rot->y;

		if(diffRotY < -D3DX_PI)
		{
			GoRot += D3DX_PI * 2;
		}
		else if(diffRotY > D3DX_PI)
		{
			GoRot += -D3DX_PI * 2;
		}

		Rot->y = CItemList::lerp(Rot->y,GoRot,RotMoveSpeed);

		Pos->x -= sinf(GoRot) * MoveSpeed;
		Pos->z -= cosf(GoRot) * MoveSpeed;
	}

	//===�v���C���[�̍��ړ�=============
	//==================================
	if(CInput::GetKeyboardPress(DIK_A))
	{
		GoRot			 = D3DX_PI /2;
		float diffRotY	 = GoRot - Rot->y;

		if(diffRotY < -D3DX_PI)
		{
			GoRot += D3DX_PI * 2;
		}
		else if(diffRotY > D3DX_PI)
		{
			GoRot += -D3DX_PI * 2;
		}

		Rot->y = CItemList::lerp(Rot->y,GoRot,RotMoveSpeed);

		Pos->x -= sinf(GoRot) * MoveSpeed;
		Pos->z -= cosf(GoRot) * MoveSpeed;
	}

	//===�v���C���[�̉E�ړ�=============
	//==================================
	if(CInput::GetKeyboardPress(DIK_D))
	{
		GoRot			 = -D3DX_PI /2;
		float diffRotY	 = GoRot - Rot->y;

		if(diffRotY < -D3DX_PI)
		{
			GoRot += D3DX_PI * 2;
		}
		else if(diffRotY > D3DX_PI)
		{
			GoRot += -D3DX_PI * 2;
		}

		Rot->y = CItemList::lerp(Rot->y,GoRot,RotMoveSpeed);

		Pos->x -= sinf(GoRot) * MoveSpeed;
		Pos->z -= cosf(GoRot) * MoveSpeed;
	}

	//===�v���C���[�̏㏸=============
	//================================
	if(CInput::GetKeyboardPress(DIK_E))
	{
		Pos->y += MoveSpeed;
	}

	//===�v���C���[�̉��~=============
	//================================
	if(CInput::GetKeyboardPress(DIK_Q))
	{
		Pos->y -= MoveSpeed;
	}
	
	if(Rot->y < -D3DX_PI)
	{
		Rot->y += D3DX_PI * 2;
	}
	else if(Rot->y > D3DX_PI)
	{
		Rot->y += -D3DX_PI * 2;
	}
}

//��-----------------------------------��
//�ȒP�ȃL�[���͂ɂ��ړ��l�̃Q�b�g
//��-----------------------------------��
void CCharaMove::SimpleMovePosition(D3DXVECTOR3 *Pos,D3DXVECTOR3 *Rot,float CameraRadY,float MoveSpeed)
{
	D3DXVECTOR3 MovePos	 = D3DXVECTOR3(0.0f,0.0f,0.0f);
	float MoveRot		 = Rot->y;

	if(CInput::GetKeyboardPress(DIK_W) && CInput::GetKeyboardPress(DIK_A))
	{
		MoveRot		 = CameraRadY - D3DX_PI / 4 + D3DX_PI;
		MovePos.x	 = -MoveSpeed * sinf(MoveRot);
		MovePos.z	 = -MoveSpeed * cosf(MoveRot);
	}
	else if(CInput::GetKeyboardPress(DIK_W) && CInput::GetKeyboardPress(DIK_D))
	{
		MoveRot		 = CameraRadY + D3DX_PI / 4 + D3DX_PI;
		MovePos.x	 = -MoveSpeed * sinf(MoveRot);
		MovePos.z	 = -MoveSpeed * cosf(MoveRot);
	}
	else if(CInput::GetKeyboardPress(DIK_S) && CInput::GetKeyboardPress(DIK_A))
	{
		MoveRot		 = CameraRadY + D3DX_PI / 4;
		MovePos.x	 = -MoveSpeed * sinf(MoveRot);
		MovePos.z	 = -MoveSpeed * cosf(MoveRot);
	}
	else if(CInput::GetKeyboardPress(DIK_S) && CInput::GetKeyboardPress(DIK_D))
	{
		MoveRot		 = CameraRadY - D3DX_PI / 4;
		MovePos.x	 = -MoveSpeed * sinf(MoveRot);
		MovePos.z	 = -MoveSpeed * cosf(MoveRot);
	}
	else if(CInput::GetKeyboardPress(DIK_W))
	{
		MoveRot		 = D3DX_PI + CameraRadY;
		MovePos.x	 = +MoveSpeed * sinf(CameraRadY);
		MovePos.z	 = +MoveSpeed * cosf(CameraRadY);
	}
	else if(CInput::GetKeyboardPress(DIK_A)){
		MoveRot		 = D3DX_PI/2 + CameraRadY;
		MovePos.x	 = -MoveSpeed * cosf(CameraRadY);
		MovePos.z	 = +MoveSpeed * sinf(CameraRadY);
	}
	else if(CInput::GetKeyboardPress(DIK_S)){
		MoveRot		 = 0.0f + CameraRadY;
		MovePos.x	 = -MoveSpeed * sinf(CameraRadY);
		MovePos.z	 = -MoveSpeed * cosf(CameraRadY);
	}
	else if(CInput::GetKeyboardPress(DIK_D)){
		MoveRot		 = -D3DX_PI/2 + CameraRadY;
		MovePos.x	 = +MoveSpeed * cosf(CameraRadY);
		MovePos.z	 = -MoveSpeed * sinf(CameraRadY);
	}

	*Pos		 += MovePos;
	Rot->y		 = MoveRot;
}
