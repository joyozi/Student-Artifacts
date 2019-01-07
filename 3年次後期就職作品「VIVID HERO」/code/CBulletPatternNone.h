//��-------------------------------------------------------------------------��
//
//	File:CBulletPatternNone�̃w�b�_�[�t�@�C��[CBulletPatternNone.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CBulletPatternNone_H_
#define _CBulletPatternNone_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CBulletPattern.h"

class Cscene;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CBulletPatternNone : public CBulletPattern
{
public:
	CBulletPatternNone(){}
	virtual ~CBulletPatternNone(){}

	
	virtual void Update_Enemy000(CEnemy000 *Shooter) override{}
	virtual void Update_Enemy001(CEnemy001 *Shooter) override{}
	virtual void Update_Player(CPlayerModel *Shooter) override{}
};


#endif
