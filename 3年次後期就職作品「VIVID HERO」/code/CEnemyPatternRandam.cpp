//��-------------------------------------------------------------------------��
//
//	File:CEnemyPatternRandam�̃t�@�C��[CEnemyPatternRandam.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CEnemyPatternRandam.h"
#include "CItemList.h"
#include "CPlayerModel.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CEnemyPatternRandam�̃R���X�g���N�^
//��-----------------------------------��
CEnemyPatternRandam::CEnemyPatternRandam()
{
	m_Angle.x = CItemList::ConvRadian((float)(rand()%360));
	m_Angle.y = CItemList::ConvRadian((float)(rand()%360));

	m_MoveCntMax = rand()%300 + 120;
	m_MoveCnt = 0;
}

//��-----------------------------------��
//CEnemyPatternRandam�̃f�X�g���N�^
//��-----------------------------------��
CEnemyPatternRandam::~CEnemyPatternRandam()
{

}

//��-----------------------------------��
//CEnemyPatternRandam�̍X�V����
//��-----------------------------------��
void CEnemyPatternRandam::Update(CScene *pEnemy)
{
	D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);

	Pos = pEnemy->GetPosition();

	float Speed = 6.0f;
	Pos.x += -(Speed) * cosf(m_Angle.x) * cosf(m_Angle.y);
	Pos.y += (Speed) * sinf(m_Angle.x);
	Pos.z += (Speed) * cosf(m_Angle.x) * sinf(m_Angle.y);

	//�����~�b�V�������O�ɏo����
	if(Pos.x < -STAGE_LENGTH_X || Pos.x > STAGE_LENGTH_X)	Pos.x = m_OldPos.x;
	if(Pos.y < -STAGE_LENGTH_Y || Pos.y > STAGE_LENGTH_Y)	Pos.y = m_OldPos.y;
	if(Pos.z < -STAGE_LENGTH_Z || Pos.z > STAGE_LENGTH_Z)	Pos.z = m_OldPos.z;

	pEnemy->SetPosition(Pos);



	//��莞�Ԃ�����������]��
	m_MoveCnt++;
	if(m_MoveCnt >= m_MoveCntMax)
	{
		m_Angle.x = CItemList::ConvRadian((float)(rand()%360));
		m_Angle.y = CItemList::ConvRadian((float)(rand()%360));
			
		m_MoveCntMax = rand()%300 + 120;
		m_MoveCnt = 0;
	}

	m_OldPos = Pos;
}
