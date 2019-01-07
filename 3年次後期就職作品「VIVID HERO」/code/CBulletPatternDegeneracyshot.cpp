//��-------------------------------------------------------------------------��
//
//	File:CBulletPatternDegeneracyShot�̃t�@�C��[CBulletPatternDegeneracyShot.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CBulletPatternDegeneracyShot.h"
#include "CBullet001.h"
#include "input.h"
#include "CManager.h"
#include "CPlayerModel.h"
#include "CCamera.h"
#include "joystick.h"
#include "CPhaseGame.h"
#include "CExplosion000.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CBulletPatternDegeneracyShot�̃R���X�g���N�^
//��-----------------------------------��
CBulletPatternDegeneracyShot::CBulletPatternDegeneracyShot()
{
	m_pBulletPointer = CBullet001::Create();
	m_ShotCnt = 0;

	for(int i = 0;i < DEGENERACYSIMPLEINFO_MAX;i++)
	{
		m_DegeneracySimpleInfo[i].PolygonNum = -1;
		m_DegeneracySimpleInfo[i].ExistJudge = false;
	}

	m_SimpleInfoCnt = 0;
}

//��-----------------------------------��
//CBulletPatternDegeneracyShot�̃f�X�g���N�^
//��-----------------------------------��
CBulletPatternDegeneracyShot::~CBulletPatternDegeneracyShot()
{
	m_pBulletPointer->Uninit();
}

//��-----------------------------------��
//CBulletPatternDegeneracyShot�̍X�V����
//��-----------------------------------��
void CBulletPatternDegeneracyShot::Update_Player(CPlayerModel *Shooter)
{
	//��ɂ܂����̈ʒu��ݒ肵�Ă���
	D3DXVECTOR3 PartsPos = D3DXVECTOR3(0.0f,-120.0f,-5.0f);
	D3DXMATRIX PlayerMtx = Shooter->GetPlayerPartsMatrix(8);

	D3DXVec3TransformCoord(&PartsPos,&PartsPos,&Shooter->GetPlayerPartsMatrix(8));

	if(CInput::GetKeyboardPress(DIK_J))
	{
		if(m_ShotCnt == 0 && Shooter->GetBulletTrigger())
		{
			//�������Ȃ�t���[���Ɉꔭ���̐��l
			m_ShotCnt = 10;
			m_pBulletPointer->Bullet001Shot(PartsPos,CManager::GetCameraPointer()->GetCameraR());

			CPhaseGame::GetExplosionPointer(EX_04_MAZZLEFLASH)->ExplosionMuzzleFlash(PartsPos);
		}
		else
		{
			m_ShotCnt--;
			if(m_ShotCnt < 0)
			{
				m_ShotCnt = 0;
			}
		}
	}
	else
	{
		m_ShotCnt--;
		if(m_ShotCnt < 0)
			m_ShotCnt = 0;
	}
}
