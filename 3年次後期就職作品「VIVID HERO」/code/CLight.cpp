//��-------------------------------------------------------------------------��
//
//	File:�t�B�[���h�����t�@�C��[CLight.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CLight.h"
//#include "CManager.h"

const float CLight::DEFFUSE_R = 1.0f;
const float CLight::DEFFUSE_G = 1.0f;
const float CLight::DEFFUSE_B = 1.0f;
const float CLight::DEFFUSE_A = 1.0f;

const float CLight::LIGHT_RANGE = 10000.0f;
const float CLight::LIGHT_ATTENUATION = 1.0f;		//���Ԃ񃉃C�g�̌����̎d��

#define LIGHT_DIRECTIONAL
//#define LIGHT_POINT

//��---------------------------------��
//�R���X�g���N�^
//��---------------------------------��
CLight::CLight()
{
	m_PosLight_Point = D3DXVECTOR3(0.0f,200.0f,0.0f);

	m_RotLight_Directrical = D3DXVECTOR3(0.0f,-1.0f,0.0f);
}
//��---------------------------------��
//�f�X�g���N�^
//��---------------------------------��
CLight::~CLight()
{

}
//��---------------------------------��
//����������
//��---------------------------------��
void CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	
	//****���C�g�̏�����****
	D3DXVECTOR3 VecDir[3];

#ifdef LIGHT_DIRECTIONAL

	for(int i = 0;i < 3;i++)
	{
		switch(i)
		{
		case 0:
			m_RotLight_Directrical = D3DXVECTOR3(0.0f,-1.0f,0.0f);
			break;
		case 1:
			m_RotLight_Directrical = D3DXVECTOR3(0.0f,1.0f,0.0f);
			break;
		case 2:
			m_RotLight_Directrical = D3DXVECTOR3(0.0f,0.0f,1.0f);
			break;
		case 3:
			m_RotLight_Directrical = D3DXVECTOR3(0.0f,0.0f,-1.0f);
			break;
		}

		//****���C�g1****
		//======================
		ZeroMemory(&m_Light[i],sizeof(D3DLIGHT9));
		m_Light[i].Type = D3DLIGHT_DIRECTIONAL;										//���C�g�̎��
		m_Light[i].Diffuse = D3DXCOLOR(DEFFUSE_R, DEFFUSE_G, DEFFUSE_B, DEFFUSE_A);	//���C�g�̐F
		VecDir[i] = D3DXVECTOR3(m_RotLight_Directrical.x,m_RotLight_Directrical.y,m_RotLight_Directrical.z);	//���C�g�̕���

		D3DXVec3Normalize((D3DXVECTOR3*)&m_Light[i].Direction,&VecDir[i]);

		pDevice -> SetLight(i,&m_Light[i]);	//���C�g��ݒ�
		pDevice -> LightEnable(i,TRUE);			//���C�g��L���ɂ���
	}

#else if LIGHT_POINT

	//****���C�g1****
	//======================
	ZeroMemory(&m_Light[0],sizeof(D3DLIGHT9));
	m_Light[0].Type = D3DLIGHT_POINT;													//���C�g�̎��
	m_Light[0].Diffuse = D3DXCOLOR(DEFFUSE_R, DEFFUSE_G, DEFFUSE_B, DEFFUSE_A);			//���C�g�̐F

	m_Light[0].Position = D3DXVECTOR3(m_PosLight_Point.x,m_PosLight_Point.y,m_PosLight_Point.z);

	m_Light[0].Attenuation0 = LIGHT_ATTENUATION;
	m_Light[0].Range = LIGHT_RANGE;

	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light[0].Direction,&VecDir[0]);

	pDevice -> SetLight(0,&m_Light[0]);		//���C�g��ݒ�
	pDevice -> LightEnable(0,TRUE);			//���C�g��L���ɂ���

	//***���C�g2***
	//========================
	ZeroMemory(&m_Light[1],sizeof(D3DLIGHT9));
	m_Light[1].Type = D3DLIGHT_POINT;												//���C�g�̎��
	m_Light[1].Diffuse = D3DXCOLOR(DEFFUSE_R, DEFFUSE_G, DEFFUSE_B, DEFFUSE_A);		//���C�g�̐F

	m_Light[1].Position = D3DXVECTOR3(m_PosLight_Point.x,m_PosLight_Point.y,m_PosLight_Point.z);

	m_Light[1].Attenuation0 = LIGHT_ATTENUATION;
	m_Light[1].Range = LIGHT_RANGE;

	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light[1].Direction,&VecDir[1]);

	pDevice->SetLight(1,&m_Light[1]);		//���C�g��ݒ�
	pDevice->LightEnable(1,TRUE);			//���C�g��L���ɂ���

	//***���C�g3***
	//========================
	ZeroMemory(&m_Light[2],sizeof(D3DLIGHT9));
	m_Light[2].Type = D3DLIGHT_POINT;											//���C�g�̎��
	m_Light[2].Diffuse = D3DXCOLOR(DEFFUSE_R, DEFFUSE_G, DEFFUSE_B, DEFFUSE_A);	//���C�g�̐F

	m_Light[2].Position = D3DXVECTOR3(m_PosLight_Point.x,m_PosLight_Point.y,m_PosLight_Point.z);

	m_Light[2].Attenuation0 = LIGHT_ATTENUATION;
	m_Light[2].Range = LIGHT_RANGE;

	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light[2].Direction,&VecDir[2]);

	//****���C�g�̐ݒ�****
	pDevice -> SetLight(2,&m_Light[2]);		//���C�g��ݒ�
	pDevice -> LightEnable(2,TRUE);			//���C�g��L���ɂ���

#endif
}

//��---------------------------------��
//�I������
//��---------------------------------��
void CLight::Uninit(void)
{

}

//��---------------------------------��
//�X�V����
//��---------------------------------��
void CLight::Update(void)
{

}

//��---------------------------------��
//�`�揈��
//��---------------------------------��
void CLight::Draw(void)
{

}

//��---------------------------------��
//�Z�b�g�J�����ʒu
//��---------------------------------��
void CLight::SetLight_Point(float x,float y,float z)
{
	m_PosLight_Point = D3DXVECTOR3(x,y,z);
}

//��---------------------------------��
//�Z�b�g���C�g�ʒu
//��---------------------------------��
void CLight::SetLight_Point(D3DXVECTOR3 pos)
{
	m_PosLight_Point = pos;
}

//��---------------------------------��
//�Q�b�g���C�g�ʒu
//��---------------------------------��
D3DXVECTOR3 CLight::GetLight_Point(void)
{
	return m_PosLight_Point;
}







