//��-------------------------------------------------------------------------��
//
//	File:CEnemy001�̃w�b�_�[�t�@�C��[CEnemy001.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CEnemy001_H_
#define _CEnemy001_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CSceneX.h"

class CBulletPattern;
class CEnemyPattern;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CEnemy001 : public CSceneX
{
public:
	CEnemy001(int nPriority = 20);
	virtual ~CEnemy001();

	virtual void Uninit(void);
	virtual void Update(void);
	
	virtual float GetCollisionRadius(int Num)override;
	virtual void CollisionAction(CLASS_TYPE Type,int Num)override;

	//�e���̐�
	virtual int GetMuzzleNum(void);
	//�e���̈ʒu
	virtual D3DXVECTOR3 GetMuzzlePos(int Num);

	static CEnemy001 *Create(LPCTSTR ModelTxtName,D3DXVECTOR3 Pos,CBulletPattern *pBullet,CEnemyPattern *pEnemy );



private:
	CBulletPattern *m_pBulletPattern;
	CEnemyPattern *m_pEnemyPattern;

	int m_Life;

	int DeathCnt;

};


#endif
