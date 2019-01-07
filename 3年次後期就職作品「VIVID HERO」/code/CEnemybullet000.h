//��-------------------------------------------------------------------------��
//
//	File:CEnemyBullet000�̃w�b�_�[�t�@�C��[CEnemyBullet000.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CEnemyBullet000_H_
#define _CEnemyBullet000_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CSceneBillboard.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CEnemyBullet000 : public CSceneBillboard
{
public:
	CEnemyBullet000(int nPriority = /*9*/50);
	virtual ~CEnemyBullet000();

	virtual void Update(void);

	float GetCollisionRadius(int Num)override;
	virtual void CollisionAction(CLASS_TYPE Type,int Num)override;

	static CEnemyBullet000 *Create(D3DXVECTOR3 ShotPos,D3DXVECTOR3 TargetPos);

private:

	float m_Speed;

	D3DXVECTOR3 m_ShotVec;
};


#endif
