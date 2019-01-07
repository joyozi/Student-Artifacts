//��-------------------------------------------------------------------------��
//
//	File:CParticleSystem�̃t�@�C��[CParticleSystem.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CParticleSystem.h"
#include "CItemList.h"
#include "input.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CParticleSystem�̃R���X�g���N�^
//��-----------------------------------��
CParticleSystem::CParticleSystem(int nPriority) : CDegeneracyPolygon(nPriority)
{
	m_Type = CTYPE_PARTICLESYSTEM;

	m_DegeneracyPolygon_Max = PARTICLESYSTEM_MAX;

	m_ParticleType = PARTICLE_SPHERE;
	m_ParticleRenderMode = P_REN_BILLBOARD;

	//int�^
	m_PopTimeCnt = 0;

	m_LifeTime = 5;
	m_StartDelay = 0;
	m_PopRate = 60;

	//float�^
	m_GravityModifier = 0.0f;
	m_Speed = 10.0f;
	m_ConeAngle = 0.0f;
	m_ConeRadius = 10.0f;
	m_SphereRadius = 0.0f;

	m_GravityJudge = false;

	m_VecForce = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_pParticleInfo = new PARTICLE_INFO[m_DegeneracyPolygon_Max];

	for(int i = 0;i < m_DegeneracyPolygon_Max;i++)
	{
		m_pParticleInfo[i].Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_pParticleInfo[i].Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_pParticleInfo[i].StartPopPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_pParticleInfo[i].MoveRot = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_pParticleInfo[i].PopRot = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_pParticleInfo[i].MoveVec = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_pParticleInfo[i].LifeCnt = 0;

		m_pParticleInfo[i].EngineTimeCnt = 0;
	}

	m_BillboardJudge = true;
	m_AlphaBlendJudge = true;
	m_LoopJudge = true;
}

//��-----------------------------------��
//CParticleSystem�̃f�X�g���N�^
//��-----------------------------------��
CParticleSystem::~CParticleSystem()
{

}

//��-----------------------------------��
//CParticleSystem�̏I������
//��-----------------------------------��
void CParticleSystem::Uninit(void)
{
	Release();

	SAFE_RELEASE(m_VtxBuffer);
	SAFE_RELEASE(m_IdxBuffer);

	SAFE_DELETE_ARRY(m_pAngle);
	SAFE_DELETE_ARRY(m_pLength);
	SAFE_DELETE_ARRY(m_pDegeneracyPolygonPos);
	SAFE_DELETE_ARRY(m_pPolygonExistJudge);
	SAFE_DELETE_ARRY(m_pDegeneracyPolygonRot);
	SAFE_DELETE_ARRY(m_pParticleInfo);
	SAFE_DELETE_ARRY(m_VtxBox);
	SAFE_DELETE_ARRY(m_pPolygonUninitFlag);
}

//��-----------------------------------��
//CParticleSystem�̍X�V����
//��-----------------------------------��
void CParticleSystem::Update(void)
{
	float MoveRot,MoveCenterToLength;				//���x���ƒ��S����ǂꂭ�炢�̋�����
	D3DXVECTOR3 PopPos = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_PopTimeCnt += m_PopRate;
		

	//��Ɍ��݂̉�]�s����v�Z
	D3DXMATRIX mtxRot_Sphere;
	D3DXMatrixRotationYawPitchRoll(&mtxRot_Sphere,m_PopRot.y,m_PopRot.x,m_PopRot.z);		//���|�@�s�b�`�@���[��


	switch(m_ParticleType)
	{
	case PARTICLE_CONE:
		//���b��1�����������邩
		for(;m_PopTimeCnt >= 1.0f;m_PopTimeCnt--)
		{
			//�ʒu�̃����_������
			MoveRot = CItemList::ConvRadian((float)(rand()%360));

//			MoveCenterToLength = (float)rand()%(int)(m_ConeRadius * 10) / 10.0f;
			MoveCenterToLength = (float)(rand()%(int)(m_ConeRadius));

			PopPos.x = MoveCenterToLength * cosf(MoveRot);
			PopPos.z = MoveCenterToLength * sinf(MoveRot);

			//�����ʒu�̍��W�ϊ�
			D3DXVec3TransformCoord(&PopPos,&PopPos,&mtxRot_Sphere);

			//�|���S���Z�b�g&�ԍ��̎擾
			int a = SetPolygon(PopPos + m_Pos,D3DXVECTOR3(0.0f,0.0f,0.0f),m_TexWidth,m_TexHeight);

			//�|���S�����쐬�\��������
			if(a != -1)
			{
				//��Ŏg����悤�ɕۑ�
				m_pParticleInfo[a].Pos = PopPos;
				m_pParticleInfo[a].StartPopPos = m_Pos;
				m_pParticleInfo[a].PopRot = m_PopRot;

				//==========�����Ă��p�x�̐ݒ�===========
				//Pos����̋���
				float VecLength = CItemList::GetLength(PopPos,D3DXVECTOR3(0.0f,0.0f,0.0f));

				m_pParticleInfo[a].MoveRot.x = MoveRot;
				m_pParticleInfo[a].MoveRot.y = m_ConeAngle * (VecLength / m_ConeRadius);
				m_pParticleInfo[a].MoveRot.z = MoveRot;

				m_pParticleInfo[a].MoveVec.x = +1.0f * sinf(m_pParticleInfo[a].MoveRot.y) * cosf(m_pParticleInfo[a].MoveRot.x);
				m_pParticleInfo[a].MoveVec.y = +1.0f * cosf(m_pParticleInfo[a].MoveRot.y);
				m_pParticleInfo[a].MoveVec.z = -1.0f * sinf(m_pParticleInfo[a].MoveRot.y) * sinf(m_pParticleInfo[a].MoveRot.x);

			}
		}

		for(int i = 0;i < PARTICLESYSTEM_MAX;i++)
		{
			if(m_pPolygonExistJudge[i])
			{
				m_pParticleInfo[i].Pos += m_Speed * m_pParticleInfo[i].MoveVec;
			}
		}



		break;
	case PARTICLE_SPHERE:
		//���b��1�����������邩
		for(;m_PopTimeCnt >= 1.0f;m_PopTimeCnt--)
		{
			D3DXVECTOR3 Pos;
			D3DXVECTOR3 KariRot;

			//�����p�ł������ʊp
			KariRot.x = D3DX_PI / 180 * (float)(rand()%360);
			KariRot.y = D3DX_PI / 180 * (float)(rand()%360);
			KariRot.z = 0.0f;

			Pos.x = -m_SphereRadius * cosf(KariRot.x) * cosf(KariRot.y);
			Pos.y = +m_SphereRadius * sinf(KariRot.x);
			Pos.z = +m_SphereRadius * cosf(KariRot.x) * sinf(KariRot.y);
			
			Pos += m_Pos;

			int a = SetPolygon(Pos,D3DXVECTOR3(0.0f,0.0f,0.0f),m_TexWidth,m_TexHeight);

			//�|���S�����쐬�\��������
			if(a != -1)
			{
				//��Ŏg����悤�ɕۑ�
				m_pParticleInfo[a].Pos = Pos - m_Pos;
				m_pParticleInfo[a].StartPopPos = m_Pos;

				m_pParticleInfo[a].MoveVec.x = -1.0f * cosf(KariRot.x) * cosf(KariRot.y);
				m_pParticleInfo[a].MoveVec.y = +1.0f * sinf(KariRot.x);
				m_pParticleInfo[a].MoveVec.z = +1.0f * cosf(KariRot.x) * sinf(KariRot.y);

				D3DXVec3Normalize(&m_pParticleInfo[a].MoveVec,&m_pParticleInfo[a].MoveVec);
			}
		}

		for(int i = 0;i < PARTICLESYSTEM_MAX;i++)
		{
			if(m_pPolygonExistJudge[i])
			{
				m_pParticleInfo[i].Pos += m_Speed * m_pParticleInfo[i].MoveVec;
			}
		}
		break;

	case PARTICLE_EDGE:
		break;

	case PARTICLE_ENGINE:
		break;

	default:
		break;
	}

	for(int i = 0;i < PARTICLESYSTEM_MAX;i++)
	{
		D3DXVECTOR3 TransPos = m_pParticleInfo[i].Pos;

		if(m_pPolygonExistJudge[i])
		{
			//�����ʒu�̍��W�ϊ�
			D3DXMATRIX mtxRot;
			D3DXMatrixRotationYawPitchRoll(&mtxRot,m_pParticleInfo[i].PopRot.y,m_pParticleInfo[i].PopRot.x,m_pParticleInfo[i].PopRot.z);
			D3DXVec3TransformCoord(&TransPos,&TransPos,&mtxRot);

			D3DXVECTOR3 Kari = (m_pParticleInfo[i].StartPopPos - m_Pos);
			TransPos += (m_pParticleInfo[i].StartPopPos - m_Pos);

			ParticleSetPosition(i,TransPos);
			
			//���C�t�̌v�Z
			m_pParticleInfo[i].LifeCnt++;

			if(m_pParticleInfo[i].LifeCnt >= m_LifeTime)
			{
				m_pParticleInfo[i].LifeCnt = 0;

				ParticleUninitPosition(i);

				//�Ō�̂���������E��
				if(i == PARTICLESYSTEM_MAX - 1 && m_LoopJudge == false)
				{
					Uninit();
				}
			}
		}
	}
}

//��-----------------------------------��
//CParticleSystem�̃N���G�C�g�@�R�[��
//��-----------------------------------��
CParticleSystem *CParticleSystem::CreateCone(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 PopRot,float Width,float Height,
		int LifeTime,int StartDelay,float PopRate,D3DXVECTOR3 VecForce,float Speed,bool Loop,
		float ConeAngle,float ConeRadius)
{
	CParticleSystem *pParticleSystem;
	pParticleSystem = new CParticleSystem;

	pParticleSystem->m_TexName = TexName;
	pParticleSystem->m_Pos = Pos;
	pParticleSystem->m_PopRot = PopRot;
	pParticleSystem->m_TexWidth = Width;
	pParticleSystem->m_TexHeight = Height;
	pParticleSystem->m_LifeTime = LifeTime;
	pParticleSystem->m_StartDelay = StartDelay;

	pParticleSystem->m_PopRate = PopRate / 60.0f;

	pParticleSystem->m_VecForce = VecForce;
	pParticleSystem->m_Speed = Speed;
	pParticleSystem->m_LoopJudge = Loop;
	pParticleSystem->m_ConeAngle = ConeAngle;
	pParticleSystem->m_ConeRadius = ConeRadius;

	pParticleSystem->m_ParticleRenderMode = P_REN_BILLBOARD;
	pParticleSystem->m_ParticleType = PARTICLE_CONE;

	pParticleSystem->Init();

	return pParticleSystem;
}


//��-----------------------------------��
//CParticleSystem�̃N���G�C�g�@���܌^
//��-----------------------------------��
CParticleSystem *CParticleSystem::CreateSphere(LPCTSTR TexName,D3DXVECTOR3 Pos,float Width,float Height,
	int LifeTime,int StartDelay,float PopRate,D3DXVECTOR3 VecForce,float Speed,bool Loop,float SphereRadius)
{
	CParticleSystem *pParticleSystem;
	pParticleSystem = new CParticleSystem;

	pParticleSystem->m_TexName = TexName;
	pParticleSystem->m_Pos = Pos;
	pParticleSystem->m_TexWidth = Width;
	pParticleSystem->m_TexHeight = Height;
	pParticleSystem->m_LifeTime = LifeTime;
	pParticleSystem->m_StartDelay = StartDelay;

	pParticleSystem->m_PopRate = PopRate / 60.0f;

	pParticleSystem->m_VecForce = VecForce;
	pParticleSystem->m_Speed = Speed;
	pParticleSystem->m_LoopJudge = Loop;

	pParticleSystem->m_SphereRadius = SphereRadius;

	pParticleSystem->m_ParticleRenderMode = P_REN_BILLBOARD;
	pParticleSystem->m_ParticleType = PARTICLE_SPHERE;

	pParticleSystem->Init();

	return pParticleSystem;
}

//��-----------------------------------��
//CParticleSystem�̃N���G�C�g�@���܌^
//��-----------------------------------��
void CParticleSystem::SetParticleChangeRotation(D3DXVECTOR3 Rot)
{
	m_PopRot = Rot;
}


