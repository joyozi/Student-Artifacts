//◇-------------------------------------------------------------------------◇
//
//	File:CBulletHomingのファイル[CBulletHoming.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CBulletHoming.h"
#include "CItemList.h"
#include "CExplosion000.h"
#include "CPhaseGame.h"
#include "CHitCheck.h"
#include "CItemList.h"
#include "sound.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CBulletHomingのコンストラクタ
//◇-----------------------------------◇
CBulletHoming::CBulletHoming(int nPriority) : CSceneX(nPriority)
{
	m_Type = CTYPE_BULLETHOMING;

	m_XfileName = "./data/MODEL/Missile001.x";

	m_Speed = 2.0f;

	m_Scl *= 10.0f;

	m_ShotPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_TargetPos = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_OldPos = D3DXVECTOR3(0.0f,0.0f,0.0f);

	int HomingLength = 5000;

	ControlVector0.x = (float)(rand() % HomingLength - HomingLength / 2);
	ControlVector0.y = (float)(rand() % HomingLength + HomingLength / 2);
	ControlVector0.z = (float)(rand() % HomingLength - HomingLength / 2);

	if(ControlVector0.x >= 0.0f)
		ControlVector0.x += HomingLength / 2;
	else
		ControlVector0.x -= HomingLength / 2;

	if(ControlVector0.z >= 0.0f)
		ControlVector0.z += HomingLength / 2;
	else
		ControlVector0.z -= HomingLength / 2;

	ControlVector1.x = 0;//(float)(rand() % HomingLength - HomingLength);
	ControlVector1.y = 0;//(float)(rand() % HomingLength + HomingLength);
	ControlVector1.z = 0;//(float)(rand() % HomingLength - HomingLength);

	m_ShotTime = 0.0f;

	m_Life = 0;

	SetCollisionHitNum(1);
}

//◇-----------------------------------◇
//CBulletHomingのデストラクタ
//◇-----------------------------------◇
CBulletHoming::~CBulletHoming()
{

}

//◇-----------------------------------◇
//CBulletHomingの更新処理
//◇-----------------------------------◇
void CBulletHoming::Update(void)
{
	//数フレームにいっこ煙を出す
	if(m_Life % 2 == 0)
		CPhaseGame::GetExplosionPointer(EX_02_SMOG)->ExplosionSet1Set(m_OldPos,70.0f,70.0f);

	m_Life++;
	m_ShotTime += 1.0f / (float)HOMING_LIFETIME;
	m_Rot.z += 1.2f;

	float h00, h01, h10, h11;

	h00 = (m_ShotTime - 1.0f) * (m_ShotTime - 1.0f) * (2.0f * m_ShotTime + 1.0f);
	h01 = m_ShotTime * m_ShotTime * (3.0f - 2.0f * m_ShotTime);
	h10 = (1.0f - m_ShotTime) * (1.0f - m_ShotTime) * m_ShotTime;
	h11 = m_ShotTime * m_ShotTime * (m_ShotTime - 1.0f);

	m_Pos.x = h00 * m_ShotPos.x +
			  h01 * m_TargetPos.x +
			  h10 * ControlVector0.x +
			  h11 * ControlVector1.x;

	m_Pos.y = h00 * m_ShotPos.y +
			  h01 * m_TargetPos.y +
			  h10 * ControlVector0.y +
			  h11 * ControlVector1.y;

	m_Pos.z = h00 * m_ShotPos.z +
			  h01 * m_TargetPos.z +
			  h10 * ControlVector0.z +
			  h11 * ControlVector1.z;

	D3DXVECTOR3 BasicRot = CItemList::VecAngle_3D_D3DX(m_Pos - m_OldPos);
	m_Rot = D3DXVECTOR3(-BasicRot.x,BasicRot.y,BasicRot.z);

	m_OldPos = m_Pos;
	
	MatrixUpdate();

	//エ無理の軌道が少し残るため微調整
	if(m_CollisionHitJudge || m_Life >= HOMING_LIFETIME - 10)
	{
		CPhaseGame::GetExplosionPointer(EX_04_MAZZLEFLASH)->ExplosionPlayerBulletHit(m_Pos);
		PlaySound(SOUND_LABEL_Missle_Explosion);
		Uninit();
	}
}

//◇-----------------------------------◇
//CBulletHomingのあたり判定のチェックシート
//◇-----------------------------------◇
bool CBulletHoming::CollisionTargetSheet(CLASS_TYPE Type)
{
	switch(Type)
	{
	case CTYPE_ENEMY:	return true;break;

	default:			return false;break;
	}
}

//◇-----------------------------------◇
//CBulletHomingのあたり判定関数
//◇-----------------------------------◇
float CBulletHoming::GetCollisionRadius(int Num)
{
	return 60.0f;
}

//◇-----------------------------------◇
//CBulletHomingのアクション	
//◇-----------------------------------◇
void CBulletHoming::CollisionAction(CLASS_TYPE Type,int Num)
{
	m_CollisionHitJudge = true;
}

//◇-----------------------------------◇
//CBulletHomingのクリエイト
//◇-----------------------------------◇
CBulletHoming *CBulletHoming::Create(D3DXVECTOR3 ShotPos,D3DXVECTOR3 TargetPos)
{
	CBulletHoming *pBulletHoming;
	pBulletHoming = new CBulletHoming;

	pBulletHoming->m_Pos = ShotPos;
	pBulletHoming->m_ShotPos = ShotPos;
	pBulletHoming->m_OldPos = ShotPos;
	pBulletHoming->m_TargetPos = TargetPos;

	float Gosa = (float)(rand()%1500);
	D3DXVECTOR3 m_Angle;

	m_Angle.x = CItemList::ConvRadian((float)(rand()%360));
	m_Angle.y = CItemList::ConvRadian((float)(rand()%360));

	D3DXVECTOR3 GosaPos;

	GosaPos.x = -(Gosa) * cosf(m_Angle.x) * cosf(m_Angle.y);
	GosaPos.y = (Gosa) * sinf(m_Angle.x);
	GosaPos.z = (Gosa) * cosf(m_Angle.x) * sinf(m_Angle.y);

	pBulletHoming->m_TargetPos += GosaPos;

	pBulletHoming->ControlVector0 += ShotPos;
	pBulletHoming->ControlVector1 += ShotPos;

	pBulletHoming->Init();

	return pBulletHoming;
}


