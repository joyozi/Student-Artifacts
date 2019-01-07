//��-------------------------------------------------------------------------��
//
//	File:CPlayerModel�̃w�b�_�[�t�@�C��[CPlayerModel.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CPLAYERMODEL_H_
#define _CPLAYERMODEL_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CSceneModelParts.h"

class CParticleEngine;
class CBulletPattern;
class CPlayerMotionPattern;
class CScore;
class CPlayerMotionChanger;
class CSceneMeshOrbit;

#define STAGE_LENGTH_X (10000)
#define STAGE_LENGTH_Y (10000)
#define STAGE_LENGTH_Z (10000)

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CPlayerModel : public CSceneModelParts
{
public:
	CPlayerModel(int nPriority = 50);

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);				//�}�g���b�N�X�̓z�����Ȃ�������
	
	virtual float GetCollisionRadius(int Num)override;
	virtual D3DXVECTOR3 GetCollisionCenterPos(int Num)override;
	virtual void CollisionAction(CLASS_TYPE Type,int Num)override;
	virtual bool CollisionTargetSheet(CLASS_TYPE Type);

	virtual D3DXMATRIX GetPlayerPartsMatrix(int PartsNum);

	virtual void MotionPatternChange(CPlayerMotionPattern *pPattern);

	virtual D3DXVECTOR3 GetPlayerSpeed(void){return m_MoveSpeed;}
	virtual void SetPlayerSpeed(D3DXVECTOR3 Speed){m_MoveSpeed = Speed;}

	virtual CScene *GetTargetEnemyPointer(){return m_pTargetEnemyPointer;}
	virtual void SetOrbitDrawStartJudge(bool Judge);

	virtual void SetEngineSpeed(float Speed);
	virtual float GetEngineSpeed();
	
	virtual void SetBulletTrigger(bool Trigger){m_BulletTrigger = Trigger;}
	virtual bool GetBulletTrigger(){return m_BulletTrigger;}


	static CPlayerModel *Create(D3DXVECTOR3 Pos);

private:
	static const int		PLAYER_BULLETNUM = 2;
	static const int		PLAYER_ENGINENUM = 4;
	static const int		PLAYER_DAMAGE = 70;

	D3DXVECTOR3				m_OldPos;
	D3DXVECTOR3				m_OldRot;
	D3DXVECTOR3				m_GoRot;
	
	bool					m_EnemyAimJudge;
	int						m_EnemyAimNum;

	int						m_PlayerLife;

	CParticleEngine*		m_pParticleSystem[PLAYER_ENGINENUM];
	CBulletPattern*			m_pBulletPattern[PLAYER_BULLETNUM];
	CPlayerMotionChanger*	m_pPatternChanger;
	CScore*					m_pPlayerScore;
	CSceneMeshOrbit*		m_pMeshOrbit;

	D3DXVECTOR3				m_CameraRStartPos;

	bool					m_MoveJudge;
	int						m_UpJudge;			//0�Œ�� 1�ŏ㏸ 2�ŉ��~
	float					m_AccelSpeed;
	float					m_UpSeed;
	D3DXVECTOR3				m_MoveSpeed;			//X��XZ���̑��x�AY��Y�����x
	CScene*					m_pTargetEnemyPointer;
	bool					m_BulletTrigger;

	int						m_ResultChangeCnt;

	D3DXVECTOR3				m_CameraRPos;
	int						m_NowTargetNum;
};


#endif
