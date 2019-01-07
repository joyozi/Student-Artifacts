//��-------------------------------------------------------------------------��
//
//	File:CBulletHoming�̃w�b�_�[�t�@�C��[CBulletHoming.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CBulletHoming_H_
#define _CBulletHoming_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CSceneX.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CBulletHoming : public CSceneX
{
public:
	CBulletHoming(int nPriority = /*9*/50);
	virtual ~CBulletHoming();

	virtual void Update(void);

	virtual float GetCollisionRadius(int Num)override;
	virtual void CollisionAction(CLASS_TYPE Type,int Num)override;
	virtual bool CollisionTargetSheet(CLASS_TYPE Type);

	static CBulletHoming *Create(D3DXVECTOR3 ShotPos,D3DXVECTOR3 TargetPos);

private:
	static const int HOMING_LIFETIME = 120;

	float m_Speed;

	D3DXVECTOR3 m_ShotPos;
	D3DXVECTOR3 m_TargetPos;

	D3DXVECTOR3 m_OldPos;

	D3DXVECTOR3 ControlVector0;
	D3DXVECTOR3 ControlVector1;

	int m_Life;

	float m_ShotTime;
};


#endif
