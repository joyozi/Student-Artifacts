//��-------------------------------------------------------------------------��
//
//	File:CEnemyPatternStop�̃w�b�_�[�t�@�C��[CEnemyPatternStop.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CEnemyPatternStop_H_
#define _CEnemyPatternStop_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CEnemyPattern.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CEnemyPatternStop : public CEnemyPattern
{
public:
	CEnemyPatternStop(){}
	virtual ~CEnemyPatternStop(){}

	virtual void Update(CScene *pEnemy)override{}
};


#endif
