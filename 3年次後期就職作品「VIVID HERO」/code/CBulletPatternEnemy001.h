//��-------------------------------------------------------------------------��
//
//	File:CBulletPatternEnemy001�̃w�b�_�[�t�@�C��[CBulletPatternEnemy001.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CBulletPatternEnemy001_H_
#define _CBulletPatternEnemy001_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CBulletPattern.h"

class CEnemy001;
class Cscene;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CBulletPatternEnemy001 : public CBulletPattern
{
public:
	CBulletPatternEnemy001();
	virtual ~CBulletPatternEnemy001();

	virtual void Update_Enemy001(CEnemy001 *Shooter)override;

private:
	static const int DEGENERACYSIMPLEINFO_MAX = 64;

	int m_MuzzleCnt;
	int m_ShotCnt;
	
protected:
	DEGENERACYINFO_SIMPLE m_DegeneracySimpleInfo[DEGENERACYSIMPLEINFO_MAX];
	int m_SimpleInfoCnt;
};

#endif
