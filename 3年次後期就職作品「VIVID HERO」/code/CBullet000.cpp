//��-------------------------------------------------------------------------��
//
//	File:CBullet000�̃t�@�C��[CBullet000.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CBullet000.h"
#include "CItemList.h"
#include "CExplosion000.h"
#include "CPhaseGame.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CBullet000�̃R���X�g���N�^
//��-----------------------------------��
CBullet000::CBullet000(int nPriority) : CSceneBillboard(nPriority)
{
	m_Type = CTYPE_BULLET000;

	TextureWidth = 30.0f;
	TextureHeight = 30.0f;
	m_TextureName = "./data/TEXTURE/Game/shadow000.jpg";

	m_Speed = 50.0f;

	SetCollisionHitNum(1);
}

//��-----------------------------------��
//CBullet000�̃f�X�g���N�^
//��-----------------------------------��
CBullet000::~CBullet000()
{

}

//��-----------------------------------��
//CBullet000�̍X�V����
//��-----------------------------------��
void CBullet000::Update(void)
{
	if(m_CollisionHitJudge)
	{
		CPhaseGame::GetExplosionPointer(0)->ExplosionSet3Set(m_Pos);

		Uninit();
	}

	m_Pos += m_ShotVec * m_Speed;
}


//��-----------------------------------��
//CBullet000�̂����蔻��֐�
//��-----------------------------------��
float CBullet000::GetCollisionRadius(int Num)
{
	return 5.0f;
}

void CBullet000::CollisionAction(CLASS_TYPE Type,int Num)
{
	m_CollisionHitJudge = true;
}

//��-----------------------------------��
//CBullet000�̍X�V����
//��-----------------------------------��
CBullet000 *CBullet000::Create(D3DXVECTOR3 ShotPos,D3DXVECTOR3 TargetPos)
{
	CBullet000 *pBullet000;
	pBullet000 = new CBullet000;

	pBullet000->m_Pos = ShotPos;
	pBullet000->m_ShotVec = TargetPos - ShotPos;
	D3DXVec3Normalize(&pBullet000->m_ShotVec,&pBullet000->m_ShotVec);

	pBullet000->Init();

	return pBullet000;
}


