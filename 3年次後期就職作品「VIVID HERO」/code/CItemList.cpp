//��---------------------------- ---------------------------------------------��
//
//	File:CItemList�̃t�@�C��[CItemList.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CItemList.h"
#include "CHitCheck.h"
#include "input.h"
#include "CCamera.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//�q�x�N�g������e�x�N�g���̈ʒu�����ɖ߂��݂�����
//��-----------------------------------��
D3DXVECTOR3 CItemList::MatrixTruePos(int num,...)
{
	D3DXVECTOR3		 ans				 = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3		 Vector3list		 = D3DXVECTOR3(0.0f,0.0f,0.0f);
	va_list			 list;

	va_start(list,num);

	for(int i = 0;i < num;i++)
	{
		ans += va_arg(list,D3DXVECTOR3);
	}

	va_end(list);

	return ans;
}

//��-----------------------------------��
//�����[�v
//��-----------------------------------��
float CItemList::lerp(float FromA,float ToB,float Time)
{
	return (ToB - FromA) * Time + FromA;
}

//��-----------------------------------��
//D3DXVECTOR3�̃����[�v
//��-----------------------------------��
D3DXVECTOR3 CItemList::Vec3lerp(D3DXVECTOR3 FromA,D3DXVECTOR3 ToB,float Time)
{
	return D3DXVECTOR3(
	CItemList::lerp(FromA.x,ToB.x,Time),
	CItemList::lerp(FromA.y,ToB.y,Time),
	CItemList::lerp(FromA.z,ToB.z,Time));
}

//��-----------------------------------��
//�Q�̃x�N�g��AB�̂Ȃ��p�x�Ƃ����߂�
//��-----------------------------------��
float CItemList::AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B )
{
	//�x�N�g��A��B�̒������v�Z����
	float length_A = D3DXVec3Length(&A);
	float length_B = D3DXVec3Length(&B);

	//���ςƃx�N�g���������g����cos�Ƃ����߂�
	float cos_sita = CHitCheck::dotProduct(A,B) / ( length_A * length_B );

	//cos�Ƃ���Ƃ����߂�
	float sita = acos( cos_sita );	

	return sita;
}


//��-----------------------------------��
//�p�x�̒���
//��-----------------------------------��
float CItemList::RotationOptisitacion(float Rot)
{
	if(Rot < -D3DX_PI)
	{
		Rot += D3DX_PI * 2;
	}
	else if(Rot > D3DX_PI)
	{
		Rot += -D3DX_PI * 2;
	}

	return Rot;
}

//��-----------------------------------��
//�p�x�̒�������2
//��-----------------------------------��
float CItemList::RotationOptisitacion(float ChangeRot,float Rot)
{
	float Diffse = ChangeRot - Rot;

	if(Diffse < -D3DX_PI)
	{
		ChangeRot += D3DX_PI * 2;
	}
	else if(Diffse > D3DX_PI)
	{
		ChangeRot += -D3DX_PI * 2;
	}

	return ChangeRot;
}

//��-----------------------------------��
//�p�x�̒ǉ��̌v�Z
//��-----------------------------------��
void CItemList::AddPosition(D3DXVECTOR3 &vec3Pos, D3DXVECTOR3 vec3Move, CCamera* pCamera)
{
	// ���s�ړ�
	float fSinParam = sinf(pCamera->GetRotationP().y + (D3DX_PI / 2));
	float fCosParam = cosf(pCamera->GetRotationP().y + (D3DX_PI / 2));
	D3DXVECTOR3 vecTempMove = D3DXVECTOR3(0.0f, vec3Move.y, 0.0f);
	vecTempMove.x = (vec3Move.x * fCosParam) - (vec3Move.z * fSinParam);
	vecTempMove.z = (vec3Move.x * fSinParam) + (vec3Move.z * fCosParam);

	vec3Pos = vec3Pos + vecTempMove;
};

//��----------------------------------��
// ��_�Ԃ̋��������߂�
//��----------------------------------��
float CItemList::GetLength(D3DXVECTOR3 vec3A, D3DXVECTOR3 vec3B)
{
	return powf((vec3B.x - vec3A.x)*(vec3B.x - vec3A.x) + (vec3B.y - vec3A.y)*(vec3B.y - vec3A.y) + (vec3B.z - vec3A.z)*(vec3B.z - vec3A.z), 0.5f);
};

//��----------------------------------��
//��̃x�N�g���̒��������߂�
//��----------------------------------��
float CItemList::GetLengthSimple(D3DXVECTOR3 vec3)
{
	return powf(( vec3.x * vec3.x ) + ( vec3.y * vec3.y ) + ( vec3.z * vec3.z ), 0.5f );
}

//��----------------------------------��
// �g������
//��----------------------------------��
float CItemList::WaveHeight(D3DXVECTOR3 vecBeginWavePos, D3DXVECTOR3& vecPos, float fFrame, float fFrequency, float fDisstanceColl, float fAmplitude)
{
	float fLen = sqrtf(((vecPos.x - vecBeginWavePos.x) * (vecPos.x - vecBeginWavePos.x))
						+((vecPos.z - vecBeginWavePos.z) * (vecPos.z - vecBeginWavePos.z)));

	vecPos.y = sinf(-fFrame * fFrequency + fLen * fDisstanceColl) * fAmplitude;

	return vecPos.y;
}

//��-----------------------------------��
//���W�A������p�x�ɕϊ�
//��-----------------------------------��
float CItemList::ConvDegree(float fRad)
{
	return fRad * 180 / D3DX_PI;
}

//��-----------------------------------��
//�p�x���烉�W�A���ɕϊ�
//��-----------------------------------��
float CItemList::ConvRadian(float fDeg)
{
	return fDeg * D3DX_PI / 180;
}

//��-----------------------------------��
//�\�[�g�֐�
//��-----------------------------------��
void CItemList::SortNumber(float *pSub,int Kazu)
{
	float *pCmpPos = new float[Kazu];
	int *CmpNumber = new int[Kazu];

	int MinNum;
	float Temp;

	for(int i = 0;i < Kazu;i++)
	{
		MinNum = i;

		for(int j = i + 1;j < Kazu;j++)
		{
			if(pSub[MinNum] > pSub[j])MinNum = j;
		}

		Temp = pSub[MinNum]; //�ŏ��Y��min �ƓY��i �̔z��n[ ] �̒l����������
		pSub[MinNum] = pSub[i];
		pSub[i] = Temp;
	}
}

//��-----------------------------------��
//2�̃x�N�g���̊p�x�����߂�v�Z�B3D�΂�
//��-----------------------------------��
float CItemList::VecAngle_3D(D3DXVECTOR3 VecA,D3DXVECTOR3 VecB)
{
	//�x�N�g��A��B�̒������v�Z����
	float length_A = GetLengthSimple(VecA);
	float length_B = GetLengthSimple(VecB);

	//���ςƃx�N�g���������g����cos�Ƃ����߂�
	float cos_sita;

	if(length_A == 0.0f)
		cos_sita = CHitCheck::dotProduct(VecA,VecB) / ( length_B );

	else if(length_B == 0.0f)
		cos_sita = CHitCheck::dotProduct(VecA,VecB) / ( length_A );

	else
		cos_sita = CHitCheck::dotProduct(VecA,VecB) / ( length_A * length_B );


	//cos�Ƃ���Ƃ����߂�
	float sita = acosf( cos_sita );

	return sita;
}

//��-----------------------------------��
//2�̃x�N�g���̊p�x�����߂�v�Z�B2D�΂�
//��-----------------------------------��
float CItemList::VecAngle_2D(D3DXVECTOR3 VecA,D3DXVECTOR3 VecB)
{
	//�x�N�g��A��B�̒������v�Z����
	float length_A = GetLengthSimple(VecA);
	float length_B = GetLengthSimple(VecB);

	//���ςƃx�N�g���������g����cos�Ƃ����߂�
	float cos_sita = CHitCheck::dotProduct(VecA,VecB) / ( length_A * length_B );

	float a = CHitCheck::dotProduct(VecA,VecB);

	//cos�Ƃ���Ƃ����߂�
	float sita = acosf( cos_sita );

	return sita;
}

//��-----------------------------------��
//2�̃x�N�g���̊p�x�����߂�v�Z�B2D�΂񂻂̂Q
//��-----------------------------------��
float CItemList::VecAngle_2D(float VecA_X,float VecA_Y,float VecB_X,float VecB_Y)
{
	//�@���x�N�g���̒�����0���Ɠ������o�܂���̂Œ��ӂ��Ă��������B

	D3DXVECTOR3 PosA = D3DXVECTOR3(VecA_X,0.0f,VecA_Y);
	D3DXVECTOR3 PosB = D3DXVECTOR3(VecB_X,0.0f,VecB_Y);

	//�x�N�g��A��B�̒������v�Z����
	float length_A = GetLengthSimple(PosA);
	float length_B = GetLengthSimple(PosB);

	//���ςƃx�N�g���������g����cos�Ƃ����߂�
	float cos_sita = CHitCheck::dotProduct(PosA,PosB) / ( length_A * length_B );

	//cos�Ƃ���Ƃ����߂�
	float sita = acosf( cos_sita );

	return sita;
}

//��-----------------------------------��
//�x�N�g���̂x���̊p�x�̌v�Z�p�֐�
//D3DXVECTOR3(0.0f,0.0f,1.0f);����ɂ��Ċp�x�����߂�
//3D�Q�[���Ƃ���XZ���Ŋp�x�����߂邩��D3DXVECTOR3�ɂ��������ɓ���Ȃ��Ƃ����Ȃ�
//��-----------------------------------��
float CItemList::VecAngle_2DSimple(D3DXVECTOR3 Vec)
{
	D3DXVECTOR3 PosA = D3DXVECTOR3(Vec.x,0.0f,Vec.z);
	D3DXVECTOR3 PosB = D3DXVECTOR3(0.0f,0.0f,1.0f);

	//�x�N�g��A��B�̒������v�Z����
	float length_A = GetLengthSimple(PosA);
	float length_B = 1.0f;

	//�G���[���p
	if(PosA == PosB || length_A == 0.0f)
		return 0.0f;

	if(Vec.x == 0.0f)
	{
		if(Vec.z >= 0.0f)
			return 0.0f;
		else
			return D3DX_PI;
	}

	//���ςƃx�N�g���������g����cos�Ƃ����߂�
	float cos_sita = CHitCheck::dotProduct(PosA,PosB) / ( length_A * length_B );

	//cos�Ƃ���Ƃ����߂�
	float sita = acosf( cos_sita );

	if(Vec.x >= 0.0f)
		return sita;
	else
		return -sita;

	return 0.0f;
}

//��-----------------------------------��
//�x�N�g����X�p�x��Y�p�x�̌v�Z�֐�
//��-----------------------------------��
D3DXVECTOR3 CItemList::VecAngle_3D_D3DX(D3DXVECTOR3 Vec)
{
	D3DXVECTOR3 Answer = D3DXVECTOR3(0.0f,0.0f,Vec.z);

	D3DXVECTOR3 VecA;
	D3DXVECTOR3 VecB;
	
	float length_A;
	float length_B;
	
	float cos_sita;

	//�G���[����̂���
	if(Vec.y <= -0.0001f || Vec.y >= 0.0001f)
	{
		VecA = D3DXVECTOR3(0.0f,Vec.y,0.0f);
		VecB = D3DXVECTOR3(Vec.x,0.0f,Vec.z);



		length_A = GetLengthSimple(VecA);
		length_B = GetLengthSimple(VecB);

		cos_sita = atan2f(length_A,length_B);

		if(Vec.y >= 0.0f)
			Answer.x = cos_sita;//acosf( cos_sita );
		else
			Answer.x = -cos_sita;//acosf( cos_sita );
	}
	else
	{
		Answer.x = 0.0f;
	}

	//Y���̊p�x
	VecA = D3DXVECTOR3(Vec.x,0.0f,Vec.z);
	VecB = D3DXVECTOR3(0.0f,0.0f,1.0f);

	Answer.y = VecAngle_2DSimple(VecA);

	return Answer;
}
