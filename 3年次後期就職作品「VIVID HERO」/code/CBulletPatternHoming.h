//��-------------------------------------------------------------------------��
//
//	File:CBulletPatternHoming�̃w�b�_�[�t�@�C��[CBulletPatternHoming.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CBulletPatternHoming_H_
#define _CBulletPatternHoming_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CBulletPattern.h"
#include "CBullet000.h"
#include "input.h"
#include "CManager.h"
#include "CPlayerModel.h"
#include "CCamera.h"
#include "CBulletHoming.h"

class Cscene;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CBulletPatternHoming : public CBulletPattern
{
public:
	CBulletPatternHoming(){}
	virtual ~CBulletPatternHoming(){}

	virtual void Update_Player(CPlayerModel *Shooter)override
	{
		if(CInput::GetKeyboardTrigger(DIK_B))
		{
//			CBulletHoming::Create(Shooter->GetPosition(), CManager::GetCameraPointer()->GetCameraR());
		}
	}
};

#endif
