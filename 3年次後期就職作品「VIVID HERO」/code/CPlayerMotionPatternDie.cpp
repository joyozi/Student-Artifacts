//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPatternDie�̃t�@�C��[CPlayerMotionPatternDie.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CPlayerMotionPatternDie.h"

#include "CPlayerModel.h"
#include "CManager.h"
#include "CItemList.h"
#include "CPhaseGame.h"
#include "CExplosion000.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CPlayerMotionPatternDie�̃R���X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternDie::CPlayerMotionPatternDie(CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_DAMAGE);
}

//��-----------------------------------��
//CPlayerMotionPatternDie�̃f�X�g���N�^
//��-----------------------------------��
CPlayerMotionPatternDie::~CPlayerMotionPatternDie()
{

}

//��-----------------------------------��
//CPlayerMotionPatternDie�̍X�V����
//��-----------------------------------��
void CPlayerMotionPatternDie::Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion)
{
	pModelMotion->SetActCommand(PMOVE_DAMAGE);

	//���܂ɉ����v�X�v�X������
	if(rand()%10 == 0)
	{
		D3DXVECTOR3 SmogAngle;
		D3DXVECTOR3 SmogPos;
		float Radius = (float)(rand()%300);

		SmogAngle.x = CItemList::ConvRadian((float)(rand()%360));
		SmogAngle.y = CItemList::ConvRadian((float)(rand()%360));

		SmogPos.x = -(Radius) * cosf(SmogAngle.x) * cosf(SmogAngle.y);
		SmogPos.y = (Radius) * sinf(SmogAngle.x);
		SmogPos.z = (Radius) * cosf(SmogAngle.x) * sinf(SmogAngle.y);



		CPhaseGame::GetExplosionPointer(EX_05_NORMALEX)->ExplosionSet1Set(pPlayer->GetPosition() + SmogPos,200.0f,200.0f);
	}
}





