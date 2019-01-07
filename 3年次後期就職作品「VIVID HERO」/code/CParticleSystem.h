//��-------------------------------------------------------------------------��
//
//	File:CParticleSystem�̃w�b�_�[�t�@�C��[CParticleSystem.h]
//	Author:�����D�O
//
//	�����|���S�����J��Ԃ��g���^�C�v�̃p�[�e�B�N���B
//	�ő�ʂ����܂��Ă邩�畁�ʂƏ����Ⴄ�����B�k�ރ|���S����
//
//��-------------------------------------------------------------------------��
#ifndef _CPARTICLESYSTEM_H_
#define _CPARTICLESYSTEM_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CDegeneracyPolygon.h"

//��-----------------------------------��
//enum
//��-----------------------------------��
//�p�[�e�B�N���̔�����������̌^
typedef enum{
	PARTICLE_CONE,
	PARTICLE_SPHERE,
	PARTICLE_EDGE,
	PARTICLE_ENGINE,
	PARTICLE_MAX
}PARTICLE_TYPE;

//�r���{�[�h�̃e�N�X�`���̌����B�ǂ̌����̃r���{�[�h��
typedef enum{
	P_REN_BILLBOARD,
	P_REN_HORIZONAL,
	P_REN_VERTICAL,
	P_REN_STRETCHIED,
	P_REN_MAX
}PARTICLE_RENDERERMODE;

typedef struct{
	D3DXVECTOR3		Pos;
	D3DXVECTOR3		Rot;
	D3DXVECTOR3		StartPopPos;
	D3DXVECTOR3		MoveRot;			//�͈͓��̂ǂ�����o���������̊p�x
	D3DXVECTOR3		PopRot;				//�o���������̑S�̂̊p�x
	D3DXVECTOR3		MoveVec;			//���Ŏg��
	int				LifeCnt;
	int				EngineTimeCnt;
}PARTICLE_INFO;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CParticleSystem : public CDegeneracyPolygon
{
public:
	CParticleSystem(int nPriority = 60);
	virtual ~CParticleSystem();
	
	virtual void Uninit();
	virtual void Update(void);
	
	virtual void SetParticleChangeRotation(D3DXVECTOR3 Rot);

	static CParticleSystem *CreateCone(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 PopRot,float Width,float Height,
		int LifeTime,int StartDelay,float PopRate,D3DXVECTOR3 VecForce,float Speed,bool Loop,float ConeAngle,float ConeRadius);

	static CParticleSystem *CreateSphere(LPCTSTR TexName,D3DXVECTOR3 Pos,float Width,float Height,
		int LifeTime,int StartDelay,float PopRate,D3DXVECTOR3 VecForce,float Speed,bool Loop,float SphereRadius);


private:
	static const int		PARTICLESYSTEM_MAX = 100;

protected:
	PARTICLE_TYPE			m_ParticleType;
	PARTICLE_RENDERERMODE	m_ParticleRenderMode;

	float					m_PopTimeCnt;
	int						m_LifeTime;				//�p�[�e�B�N����̐�������
	int						m_StartDelay;			//�p�[�e�B�N���̏o�n�߂鎞��
	float					m_PopRate;			//1�b�Ԃɉ��p�[�e�B�N�����������邩
	float					m_GravityModifier;	//�d�͂ɂǂꂭ�炢���R���邩
	D3DXVECTOR3				m_VecForce;		//�ނ��ɂ������
	float					m_Speed;
	bool					m_GravityJudge;		//�d�͂̉e�����󂯂邩�ۂ�
	PARTICLE_INFO*			m_pParticleInfo;

	//CONE���̐��l
	float					m_ConeAngle;			//�����̂ނ�
	float					m_ConeRadius;			//�������̑傫��
	D3DXVECTOR3				m_PopRot;		//�������Ă����p�x

	//�X�t�B�A�̃T�C�Y
	float					m_SphereRadius;
};



#endif
