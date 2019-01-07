//��-------------------------------------------------------------------------��
//
//	File:CEnemyWave�̃w�b�_�[�t�@�C��[CEnemyWave.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CENEMYWAVE_H_
#define _CENEMYWAVE_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "Cscene2D.h"

class CEnemy001;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CEnemyWave : public CScene2D
{
public:
	CEnemyWave(int nPriority = 20);
	virtual ~CEnemyWave();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);		//�`�揈�������Ȃ����߂ɕK�v

	virtual void EnemyWave_First(int Num);
	virtual void EnemyWave_Second(int Num);

	static CEnemyWave *Create();

private:
	static const int ENEMYWAVE_MAX = 32;
	int m_WaveChangeJudge;

	CEnemy001 *m_pEnemyCounter[ENEMYWAVE_MAX];
};



#endif
