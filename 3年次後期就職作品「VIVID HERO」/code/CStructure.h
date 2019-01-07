//◇-------------------------------------------------------------------------◇
//
//	File:CStructureのファイル[CStructure.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
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
	int			 hitNum;								//あたり判定の球の数
	bool		 Judge;									//当たるかどうか
	
	float		 Radius[COLLISIONNUM_MAX];				//半径
	D3DXVECTOR3	 CenterPos[COLLISIONNUM_MAX];			//あたり判定の中心点
	bool		 PartsHitJudge[COLLISIONNUM_MAX];		//個別の部位が当たるかどうか

	bool		 HitObject[CTYPE_MAX];

}COLLISION_INFO;


#endif




