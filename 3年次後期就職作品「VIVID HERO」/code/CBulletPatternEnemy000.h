//��-------------------------------------------------------------------------��
//
//	File:CBulletPatternEnemy000�̃w�b�_�[�t�@�C��[CBulletPatternEnemy000.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CBulletPatternEnemy000_H_
#define _CBulletPatternEnemy000_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CBulletPattern.h"

class Cscene;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CBulletPatternEnemy000 : public CBulletPattern
{
public:
	CBulletPatternEnemy000();
	virtual ~CBulletPatternEnemy000();

	virtual void Update_Enemy000(CEnemy000 *Shooter)override;
};

#endif
