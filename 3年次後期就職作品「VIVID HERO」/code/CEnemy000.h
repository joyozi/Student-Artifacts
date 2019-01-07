//��-------------------------------------------------------------------------��
//
//	File:CEnemy000�̃w�b�_�[�t�@�C��[CEnemy000.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CENEMY000_H_
#define _CENEMY000_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CSceneModelParts.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CEnemy000 : public CSceneModelParts
{
public:
	CEnemy000(int nPriority = 50);
	virtual ~CEnemy000();

	virtual void Update(void);
	
	virtual float GetCollisionRadius(void);
	virtual void CollisionAction(void);

	static CEnemy000 *Create(LPCTSTR ModelTxtName,D3DXVECTOR3 Pos);
};


#endif
