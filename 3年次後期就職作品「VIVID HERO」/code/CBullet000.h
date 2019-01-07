//��-------------------------------------------------------------------------��
//
//	File:CBullet000�̃w�b�_�[�t�@�C��[CBullet000.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CBULLET000_H_
#define _CBULLET000_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CSceneBillboard.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CBullet000 : public CSceneBillboard
{
public:
	CBullet000(int nPriority = /*9*/50);
	virtual ~CBullet000();

	virtual void Update(void);

	float GetCollisionRadius(int Num)override;
	virtual void CollisionAction(CLASS_TYPE Type,int Num)override;

	static CBullet000 *Create(D3DXVECTOR3 ShotPos,D3DXVECTOR3 TargetPos);

private:

	float m_Speed;

	D3DXVECTOR3 m_ShotVec;
};


#endif
