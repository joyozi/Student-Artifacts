//��-------------------------------------------------------------------------��
//
//	File:CEnemyBullet000�̃t�@�C��[CEnemyBullet000.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CEnemyBullet000.h"
#include "CItemList.h"
#include "CExplosion000.h"
#include "CPhaseGame.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CEnemyBullet000�̃R���X�g���N�^
//��-----------------------------------��
CEnemyBullet000::CEnemyBullet000(int nPriority) : CSceneBillboard(nPriority)
{
	m_Type = CTYPE_ENEMYBULLET000;

	TextureWidth = 30.0f;
	TextureHeight = 30.0f;
	m_TextureName = "./data/TEXTURE/Game/bullet000.png";

	m_Speed = 200.0f;

	SetCollisionHitNum(1);
}

//��-----------------------------------��
//CEnemyBullet000�̃f�X�g���N�^
//��-----------------------------------��
CEnemyBullet000::~CEnemyBullet000()
{

}

//��-----------------------------------��
//CEnemyBullet000�̍X�V����
//��-----------------------------------��
void CEnemyBullet000::Update(void)
{
	if(m_CollisionHitJudge)
	{
		CPhaseGame::GetExplosionPointer(0)->ExplosionSet3Set(m_Pos);

		Uninit();
	}

	m_Pos += m_ShotVec * m_Speed;
}

//��-----------------------------------��
//CEnemyBullet000�̂����蔻��֐�
//��-----------------------------------��
float CEnemyBullet000::GetCollisionRadius(int Num)
{
	return 5.0f;
}

void CEnemyBullet000::CollisionAction(CLASS_TYPE Type,int Num)
{
	if(Type == CTYPE_PLAYERMODEL)
		m_CollisionHitJudge = true;
}

//��-----------------------------------��
//CEnemyBullet000�̃N���G�C�g
//��-----------------------------------��
CEnemyBullet000 *CEnemyBullet000::Create(D3DXVECTOR3 ShotPos,D3DXVECTOR3 TargetPos)
{
	CEnemyBullet000 *pBullet000;
	pBullet000 = new CEnemyBullet000;

	pBullet000->m_Pos = ShotPos;
	pBullet000->m_ShotVec = TargetPos - ShotPos;
	D3DXVec3Normalize(&pBullet000->m_ShotVec,&pBullet000->m_ShotVec);

	pBullet000->Init();

	return pBullet000;
}


