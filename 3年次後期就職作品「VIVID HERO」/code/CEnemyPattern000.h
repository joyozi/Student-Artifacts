//��-------------------------------------------------------------------------��
//
//	File:CEnemyPattern000�̃w�b�_�[�t�@�C��[CEnemyPattern000.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CEnemyPattern000_H_
#define _CEnemyPattern000_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CEnemyPattern.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CEnemyPattern000 : public CEnemyPattern
{
public:
	CEnemyPattern000();
	virtual ~CEnemyPattern000();

	virtual void Update(CScene *pEnemy)override;

private:
	float m_Angle;

};


#endif
