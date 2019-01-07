//��-------------------------------------------------------------------------��
//
//	File:CBulletPattern�̃w�b�_�[�t�@�C��[CBulletPattern.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CBULLETPATTERN_H_
#define _CBULLETPATTERN_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "main.h"

class CEnemy000;
class CEnemy001;
class CPlayerModel;
class CEnemy;


typedef struct{
	int PolygonNum;
	bool ExistJudge;
	int MuzzleNum;
}DEGENERACYINFO_SIMPLE;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CBulletPattern
{
public:
	CBulletPattern(){}
	virtual ~CBulletPattern() = 0{}

	virtual void Update_Enemy000(CEnemy000 *Shooter){}
	virtual void Update_Enemy001(CEnemy001 *Shooter){}
	virtual void Update_Player(CPlayerModel *Shooter){}


};


#endif
