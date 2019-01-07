//��-------------------------------------------------------------------------��
//
//	File:CEnemyBullet001�̃t�@�C��[CEnemyBullet001.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CEnemyBullet001.h"
#include "CPhaseGame.h"
#include "CExplosion000.h"


//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CEnemyBullet001�̃R���X�g���N�^
//��-----------------------------------��
CEnemyBullet001::CEnemyBullet001()
{
	m_Type					= CTYPE_ENEMYBULLET001;
	m_DegeneracyPolygon_Max	= ENEMYBULLET001_MAX;

	m_Pos				= D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_TexName			= "./data/TEXTURE/Game/shadow000.jpg";

	BulletNumCounter	= 0;
	m_TexSize			= 50.0f;
	m_TexLength			= 20.0f;
	m_AlphaBlendJudge	= true;
	m_Speed				= 100.0f;

	m_ShotTexNum		= ENEMYBULLET001_TEXNUM;
	m_ShotNumMax		= ENEMYBULLET001_NUMMAX;
	m_BulletMax			= ENEMYBULLET001_MAX;
}

//��-----------------------------------��
//CEnemyBullet001�̃f�X�g���N�^
//��-----------------------------------��
CEnemyBullet001::~CEnemyBullet001()
{

}

//��-----------------------------------��
//CEnemyBullet001�̍X�V����
//��-----------------------------------��
void CEnemyBullet001::Update(void)
{
	int BulletNum = 0;

	for(int i = 0;i < m_ShotNumMax;i++)
	{
		if(m_pBulletInfo[i].ExistJudge)
		{
			m_pBulletInfo[i].Pos += m_pBulletInfo[i].GoVec * m_pBulletInfo[i].Speed;
			
			for(int i_2 = 0;i_2 < ENEMYBULLET001_TEXNUM;i_2++)
			{
				ParticleSetPosition( m_pBulletInfo[i].PolygonNum[i_2],m_pBulletInfo[i].Pos - m_pBulletInfo[i].GoVec * (i_2 * m_TexLength));
			}
			
			m_pBulletInfo[i].Life++;

			if(m_pBulletInfo[i].Life >= ENEMYBULLET001_LIFEMAX)
			{
				Bullet001ShotUninit(i);
			}
			else
			{
				//�����Ă���
				BulletNum++;
			}
		}
	}

	SetCollisionHitNum(BulletNum);
}


//��-----------------------------------��
//CBullet001�̃A�N�V����
//��-----------------------------------��
void CEnemyBullet001::CollisionAction(CLASS_TYPE Type,int Num)
{
	int a = 0;

	for(int i = 0;i < m_ShotNumMax;i++)
	{
		if(m_pBulletInfo[i].ExistJudge)
		{
			if(a == Num)
			{
				CPhaseGame::GetExplosionPointer(0)->ExplosionSet3Set(m_pBulletInfo[i].Pos);

				Bullet001ShotUninit(i);
			}
			a++;
		}
	}
}

//��-----------------------------------��
//CEnemyBullet001�̂����蔻��̃`�F�b�N�V�[�g
//��-----------------------------------��
bool CEnemyBullet001::CollisionTargetSheet(CLASS_TYPE Type)
{
	switch(Type)
	{
	case CTYPE_PLAYERMODEL:	return true;break;

	default:			return false;break;
	}
}

//��-----------------------------------��
//CEnemyBullet001�̃N���G�C�g
//��-----------------------------------��
CEnemyBullet001 *CEnemyBullet001::Create()
{
	CEnemyBullet001 *pBullet001;
	pBullet001 = new CEnemyBullet001;

	pBullet001->Init();

	return pBullet001;
}
