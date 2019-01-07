//��-------------------------------------------------------------------------��
//
//	File:CBulletPatternDegeneracyShot�̃w�b�_�[�t�@�C��[CBulletPatternDegeneracyShot.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CBulletPatternDegeneracyShot_H_
#define _CBulletPatternDegeneracyShot_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CBulletPattern.h"

class CBullet001;
class Cscene;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CBulletPatternDegeneracyShot : public CBulletPattern
{
public:
	CBulletPatternDegeneracyShot();

	virtual ~CBulletPatternDegeneracyShot();

	virtual void Update_Player(CPlayerModel *Shooter)override;

private:
	static const int DEGENERACYSIMPLEINFO_MAX = 256;

	CBullet001 *m_pBulletPointer;
	int m_ShotCnt;

protected:
	DEGENERACYINFO_SIMPLE m_DegeneracySimpleInfo[DEGENERACYSIMPLEINFO_MAX];
	int m_SimpleInfoCnt;
};

#endif
