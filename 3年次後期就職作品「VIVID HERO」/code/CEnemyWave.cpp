//��-------------------------------------------------------------------------��
//
//	File:CEnemyWave�̃t�@�C��[CEnemyWave.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CEnemyWave.h"
#include "CEnemy001.h"
#include "CEnemyPattern000.h"
#include "CBulletPatternEnemy000.h"
#include "CBulletPatternEnemy001.h"
#include "CEnemyPatternStop.h"
#include "CEnemyPatternRandam.h"
#include "CManager.h"
#include "CPhaseChange.h"
#include "CPhaseResult.h"
#include "CPhase.h"
#include "sound.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CEnemyWave�̃R���X�g���N�^
//��-----------------------------------��
CEnemyWave::CEnemyWave(int nPriority) : CScene2D(nPriority)
{
	m_WaveChangeJudge = 0;

	for(int i = 0;i < ENEMYWAVE_MAX;i++)
	{
		m_pEnemyCounter[i] = NULL;
	}
}

//��-----------------------------------��
//CEnemyWave�̃f�X�g���N�^
//��-----------------------------------��
CEnemyWave::~CEnemyWave()
{

}

//��-----------------------------------��
//CEnemyWave�̏���������
//��-----------------------------------��
HRESULT CEnemyWave::Init(void)
{
	EnemyWave_First(2);

	return S_OK;
}

//��-----------------------------------��
//CEnemyWave�̏I������
//��-----------------------------------��
void CEnemyWave::Uninit(void)
{
	for(int i = 0;i < ENEMYWAVE_MAX;i++)
	{

	}
}

//��-----------------------------------��
//CEnemyWave�̍X�V����
//��-----------------------------------��
void CEnemyWave::Update(void)
{
	CScene *pEnemyPointer[ENEMYWAVE_MAX] = {NULL};

	CScene::SearchLinkList(pEnemyPointer,CTYPE_ENEMY);

	//�T���Ă��N�����Ȃ�������X�C�b�`�I
	if(pEnemyPointer[0] == NULL)
	{
		if(m_WaveChangeJudge < 5)
		{
			PlaySound(SOUND_LABEL_EnemyPop00);
			EnemyWave_Second(m_WaveChangeJudge + 2);
			m_WaveChangeJudge++;
		}
		else
		{
			CManager::GetPhaseChangePointer()->PhaseChange(new CPhaseResult(PHASE_RESULT,RESULT_CLEAR));
		}
	}

}

//��-----------------------------------��
//CEnemyWave�̉������Ȃ��h���E
//��-----------------------------------��
void CEnemyWave::Draw(void)
{

}

//��-----------------------------------��
//CEnemyWave�̃E�F�[�u
//��-----------------------------------��
CEnemyWave *CEnemyWave::Create()
{
	CEnemyWave *pEnemyWave;
	pEnemyWave = new CEnemyWave;

	pEnemyWave->Init();

	return pEnemyWave;

}

//��-----------------------------------��
//CEnemyWave�̃E�F�[�u���̂P
//��-----------------------------------��
void CEnemyWave::EnemyWave_First(int Num)
{
	m_pEnemyCounter[0] = CEnemy001::Create("./data/MODEL/Enemy/Enemy002.x",D3DXVECTOR3(0.0f,0.0f,0.500f),new CBulletPatternEnemy001,new CEnemyPatternRandam);
	m_pEnemyCounter[1] = CEnemy001::Create("./data/MODEL/Enemy/Enemy002.x",D3DXVECTOR3(3000.0f,0.0f,0.0f),new CBulletPatternEnemy001,new CEnemyPatternRandam);
	m_pEnemyCounter[2] = CEnemy001::Create("./data/MODEL/Enemy/Enemy002.x",D3DXVECTOR3(-3000.0f,0.0f,500.0f),new CBulletPatternEnemy001,new CEnemyPatternRandam);
}

//��-----------------------------------��
//CEnemyWave�̃E�F�[�u���̂Q
//��-----------------------------------��
void CEnemyWave::EnemyWave_Second(int Num)
{

	for(int i = 0;i < Num;i++)
	{
		D3DXVECTOR3 Pos;
		
		Pos.x = (float)(rand()%6000) - 3000.0f;
		Pos.y = (float)(rand()%3000) - 1500.0f;
		Pos.z = (float)(rand()%6000) - 3000.0f;
		m_pEnemyCounter[i] = CEnemy001::Create("./data/MODEL/Enemy/Enemy002.x",Pos,new CBulletPatternEnemy001,new CEnemyPatternRandam);
	}
}