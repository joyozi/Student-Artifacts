//��-------------------------------------------------------------------------��
//
//	File:CEnemyPattern�̃w�b�_�[�t�@�C��[CEnemyPattern.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CENEMYPATTERN_H_
#define _CENEMYPATTERN_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "main.h"
#include "CScene.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CEnemyPattern
{
public:
	CEnemyPattern(){}
	virtual ~CEnemyPattern() = 0{}

	virtual void Update(CScene *pEnemy) = 0;
};


#endif
