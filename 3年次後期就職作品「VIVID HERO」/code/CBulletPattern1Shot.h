//��-------------------------------------------------------------------------��
//
//	File:CBulletPattern1Shot�̃w�b�_�[�t�@�C��[CBulletPattern1Shot.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CBULLETPATTERN1SHOT_H_
#define _CBULLETPATTERN1SHOT_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CBulletPattern.h"
#include "CBullet000.h"
#include "input.h"
#include "CManager.h"
#include "CPlayerModel.h"
#include "CCamera.h"

class Cscene;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CBulletPattern1Shot : public CBulletPattern
{
public:
	CBulletPattern1Shot(){}
	virtual ~CBulletPattern1Shot(){}

	virtual void Update_Player(CPlayerModel *Shooter)override{
	
		if(CInput::GetKeyboardTrigger(DIK_SPACE))
		{
			CPlayerModel *pPlayer = (CPlayerModel*)Shooter;
				
			D3DXVECTOR3 PartsPos = D3DXVECTOR3(0.0f,-70.0f,0.0f);
			D3DXMATRIX PlayerMtx = pPlayer->GetPlayerPartsMatrix(8);

			D3DXMATRIX Matrix;

			D3DXMatrixIdentity(&Matrix);
			D3DXMatrixMultiply(&Matrix,&Matrix,&pPlayer->GetPlayerPartsMatrix(8));

			D3DXVec3TransformCoord(&PartsPos,&PartsPos,&Matrix);

			CBullet000::Create(PartsPos, CManager::GetCameraPointer()->GetCameraR());
		}
	}
};

#endif
