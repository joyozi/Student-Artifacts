//��-------------------------------------------------------------------------��
//
//	File:CBulletPatternEnemy001�̃t�@�C��[CBulletPatternEnemy001.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CBulletPatternEnemy001.h"
#include "CManager.h"
#include "CEnemy001.h"
#include "CEnemyBullet001.h"
#include "CCamera.h"
#include "CPhaseGame.h"
#include "CExplosion000.h"
#include "CPhaseGame.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CBulletPatternEnemy001�̃R���X�g���N�^
//��-----------------------------------��
CBulletPatternEnemy001::CBulletPatternEnemy001()
{
	m_MuzzleCnt = rand()%3;
	m_ShotCnt = rand()%30;
	

	for(int i = 0;i < DEGENERACYSIMPLEINFO_MAX;i++)
	{
		m_DegeneracySimpleInfo[i].PolygonNum = -1;
		m_DegeneracySimpleInfo[i].ExistJudge = false;
		m_DegeneracySimpleInfo[i].MuzzleNum = 0;
	}

	m_SimpleInfoCnt = 0;
}

//��-----------------------------------��
//CBulletPatternEnemy001�̃f�X�g���N�^
//��-----------------------------------��
CBulletPatternEnemy001::~CBulletPatternEnemy001()
{

}

//��-----------------------------------��
//CBulletPatternEnemy001�̍X�V����
//��-----------------------------------��
void CBulletPatternEnemy001::Update_Enemy001(CEnemy001 *Shooter)
{
	if(m_ShotCnt % 60 == 0)
	{
		CScene *pPlayer = NULL;

		CScene::SearchLinkList(&pPlayer,CTYPE_PLAYERMODEL);

		if(pPlayer != NULL)
		{
			CPhaseGame::GetExplosionPointer(EX_04_MAZZLEFLASH)->ExplosionMuzzleFlash(Shooter->GetMuzzlePos(m_MuzzleCnt));

			//�ڕW���R���W�����Z���^�[�|�X�ɂ���
			CPhaseGame::GetEnemyBullet001Pointer()->Bullet001Shot(Shooter->GetMuzzlePos(m_MuzzleCnt),pPlayer->GetCollisionCenterPos(0));



			m_MuzzleCnt++;
			if(m_MuzzleCnt >= Shooter->GetMuzzleNum())
			{
				m_MuzzleCnt = 0;
			}
		}
	}

	m_ShotCnt++;
}
