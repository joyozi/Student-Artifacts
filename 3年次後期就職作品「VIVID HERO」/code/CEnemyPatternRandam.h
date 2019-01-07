//��-------------------------------------------------------------------------��
//
//	File:CEnemyPatternRandam�̃w�b�_�[�t�@�C��[CEnemyPatternRandam.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CENEMYPATTERNRANDAM_H_
#define _CENEMYPATTERNRANDAM_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CEnemyPattern.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CEnemyPatternRandam : public CEnemyPattern
{
public:
	CEnemyPatternRandam();
	virtual ~CEnemyPatternRandam();

	virtual void Update(CScene *pEnemy)override;

private:
	D3DXVECTOR3 m_Angle;
	D3DXVECTOR3 m_OldPos;

	int m_MoveCnt;
	int m_MoveCntMax;
};


#endif
