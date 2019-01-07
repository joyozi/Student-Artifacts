//��-------------------------------------------------------------------------��
//
//	File:CStructure�̃t�@�C��[CStructure.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CSTRUCTURE_H_
#define _CSTRUCTURE_H_

#include "main.h"

typedef struct{
	int Life;
	float Speed;
}BULLET_INFO;


#define DEGENERACY_BULLETPOLYGON_MAX (128)

typedef struct{
	int			 Life;
	float		 Speed;
	D3DXVECTOR3	 Pos;
	D3DXVECTOR3	 StartPos;
	D3DXVECTOR3	 GoVec;
	bool		 ExistJudge;

	int			 PolygonNum[DEGENERACY_BULLETPOLYGON_MAX];

}DEGENERACY_BULLET;


#define COLLISIONNUM_MAX (16)

typedef struct{
	int			 hitNum;								//�����蔻��̋��̐�
	bool		 Judge;									//�����邩�ǂ���
	
	float		 Radius[COLLISIONNUM_MAX];				//���a
	D3DXVECTOR3	 CenterPos[COLLISIONNUM_MAX];			//�����蔻��̒��S�_
	bool		 PartsHitJudge[COLLISIONNUM_MAX];		//�ʂ̕��ʂ������邩�ǂ���

	bool		 HitObject[CTYPE_MAX];

}COLLISION_INFO;


#endif




