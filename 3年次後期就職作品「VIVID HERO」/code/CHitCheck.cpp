//��-------------------------------------------------------------------------��
//
//	File	:	hitCheck�t�@�C��[hitcheck.cpp]
//	Author	:	touma yoshihiro
//
//��-------------------------------------------------------------------------��
#include "main.h"
#include "CHitCheck.h"

//��-------------------------------------------------------------------------��
// ����
// Contents : 2�����ł̓��ς̌v�Z
//��-------------------------------------------------------------------------��
float CHitCheck::dotProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr)
{
	float ans = 0;					//�����̂����ϐ�

	//vr�̂ق��̒�ӂ����߂�
#if 1
	ans = vl.x * vr.x + vl.y * vr.y + vl.z * vr.z;

#else
	ans = D3DXVec3Dot(&vl,&vr);

#endif

	//������Ԃ�
	return(ans);


}


//��-------------------------------------------------------------------------��
// �O��
// Contents : 3D�̊O�όv�Z�B�|���S���̌���(�@���x�N�g��)�����߂�
//��-------------------------------------------------------------------------��
D3DXVECTOR3 CHitCheck::crossProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr )
{
	D3DXVECTOR3 ret;

#if 1
	ret.x = vl.y * vr.z - vl.z * vr.y;
	ret.y = vl.z * vr.x - vl.x * vr.z;
	ret.z = vl.x * vr.y - vl.y * vr.x;

#else
	D3DXVec3Cross(&ret,&vl,&vr);

#endif

	//���߂��x�N�g���@����Ԃ�
	return(ret);
}


//��-------------------------------------------------------------------------��
// �|���S���Ɛ����Ƃ̓����蔻��i�K�`�Łj
// p0  :�|���S���̒��_1
// p1  :�|���S���̒��_2
// p2  :�|���S���̒��_3
// pos0:�����̎n�_�i�ړ��O���W�j
// pos1:�����̏I�_�i�ړ�����W�j
//��-------------------------------------------------------------------------��
int CHitCheck::HitCheck( D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1 )
{
	D3DXVECTOR3 nor;								// �|���S���̖@��

	{
		D3DXVECTOR3 vec01 = p1 - p0;
		D3DXVECTOR3 vec02 = p2 - p0;

		// �|���S���̊O�ς��Ƃ��Ė@�������߂Ă���
		nor = crossProduct(vec01,vec02);


		//�@���x�N�g���̐��K��
		D3DXVec3Normalize(&nor,&nor);
	}


	{	// �@���ʂƐ����̓��ς��Ƃ��ďՓ˂��Ă���\���𒲂ׂ�
		// ���߂��@���ƃx�N�g���Q�i�����̗��[�ƃ|���S����̔C�ӂ̓_�j��
		// ���ς��Ƃ��ďՓ˂��Ă���\���𒲂ׂ�

		D3DXVECTOR3 vec1 = pos0 - p0;
		D3DXVECTOR3 vec2 = pos1 - p0;

		float a = dotProduct(vec1,nor);
		float b = dotProduct(vec2,nor);

		if((a * b) > 0)
		{	// ���ʓ������Ă��Ȃ�������I��
		
			// �������Ă���\���͖���
			return(0);
		}
	}

	{	// �A�|���S���Ɛ����̌�_�����߂�
		D3DXVECTOR3 vec1 = pos0 - p0;
		D3DXVECTOR3 vec2 = pos1 - p0;

		//�����������߂�
		float comp_d1 = fabs(dotProduct(nor,vec1));
		float comp_d2 = fabs(dotProduct(nor,vec2));

		float comp_a = comp_d1 / (comp_d1 + comp_d2);

#if 1
		D3DXVECTOR3 vec3 = (1- comp_a) * vec1 + comp_a * vec2;
		D3DXVECTOR3 p3 = p0 + vec3;

#else
		D3DXVECTOR3 vec3 = pos1 - pos0;
		D3DXVECTOR3 p3 = pos0 + (vec3 * comp_a);
#endif

		D3DXVECTOR3 v1 = p1 - p0;
		D3DXVECTOR3 v2 = p2 - p1;
		D3DXVECTOR3 v3 = p0 - p2;
		D3DXVECTOR3 v4 = p3 - p1;
		D3DXVECTOR3 v5 = p3 - p2;
		D3DXVECTOR3 v6 = p3 - p0;

		D3DXVECTOR3 n1 = crossProduct(v1,v4);
		D3DXVECTOR3 n2 = crossProduct(v2,v5);
		D3DXVECTOR3 n3 = crossProduct(v3,v6);

#if 1
		if(dotProduct(n1,nor) < 0) return (0);
		if(dotProduct(n2,nor) < 0) return (0);
		if(dotProduct(n3,nor) < 0) return (0);

#else
		if(dotProduct(n1,n2) < 0) return (0);
		if(dotProduct(n2,n3) < 0) return (0);

#endif

	}
	
	// ���ׂĂɊY�����Ă��Ȃ������瓖�����Ă�̂�1��Ԃ�
	return(1);
}

//��-------------------------------------------------------------------------��
// �|���S���Ɛ����Ƃ̌�_
// p0  :�|���S���̒��_1
// p1  :�|���S���̒��_2
// p2  :�|���S���̒��_3
// pos0:�����̎n�_�i�ړ��O���W�j
// pos1:�����̏I�_�i�ړ�����W�j
//��-------------------------------------------------------------------------��
D3DXVECTOR3 CHitCheck::HitIntersection( D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1 )
{
	D3DXVECTOR3 nor;								// �|���S���̖@��

	{
		D3DXVECTOR3 vec01 = p1 - p0;
		D3DXVECTOR3 vec02 = p2 - p0;

		// �|���S���̊O�ς��Ƃ��Ė@�������߂Ă���
		nor = crossProduct(vec01,vec02);


		//�@���x�N�g���̐��K��
		D3DXVec3Normalize(&nor,&nor);
	}


	{	// �@���ʂƐ����̓��ς��Ƃ��ďՓ˂��Ă���\���𒲂ׂ�
		// ���߂��@���ƃx�N�g���Q�i�����̗��[�ƃ|���S����̔C�ӂ̓_�j��
		// ���ς��Ƃ��ďՓ˂��Ă���\���𒲂ׂ�

		D3DXVECTOR3 vec1 = pos0 - p0;
		D3DXVECTOR3 vec2 = pos1 - p0;

		float a = dotProduct(vec1,nor);
		float b = dotProduct(vec2,nor);

		if((a * b) > 0)
		{	// ���ʓ������Ă��Ȃ�������I��
		
			// �������Ă���\���͖���
			return D3DXVECTOR3(0.0f,0.0f,0.0f);
		}
	}

	{	// �A�|���S���Ɛ����̌�_�����߂�
		D3DXVECTOR3 vec1 = pos0 - p0;
		D3DXVECTOR3 vec2 = pos1 - p0;

		//�����������߂�
		float comp_d1 = fabs(dotProduct(nor,vec1));
		float comp_d2 = fabs(dotProduct(nor,vec2));

		float comp_a = comp_d1 / (comp_d1 + comp_d2);

#if 1
		D3DXVECTOR3 vec3 = (1- comp_a) * vec1 + comp_a * vec2;
		D3DXVECTOR3 p3 = p0 + vec3;

#else
		D3DXVECTOR3 vec3 = pos1 - pos0;
		D3DXVECTOR3 p3 = pos0 + (vec3 * comp_a);
#endif

		D3DXVECTOR3 v1 = p1 - p0;
		D3DXVECTOR3 v2 = p2 - p1;
		D3DXVECTOR3 v3 = p0 - p2;
		D3DXVECTOR3 v4 = p3 - p1;
		D3DXVECTOR3 v5 = p3 - p2;
		D3DXVECTOR3 v6 = p3 - p0;

		D3DXVECTOR3 n1 = crossProduct(v1,v4);
		D3DXVECTOR3 n2 = crossProduct(v2,v5);
		D3DXVECTOR3 n3 = crossProduct(v3,v6);

#if 1
		if(dotProduct(n1,nor) < 0) return (p3);
		if(dotProduct(n2,nor) < 0) return (p3);
		if(dotProduct(n3,nor) < 0) return (p3);

#else
		if(dotProduct(n1,n2) < 0) return (0);
		if(dotProduct(n2,n3) < 0) return (0);

#endif

	}
	
	// ���ׂĂɊY�����Ă��Ȃ������瓖�����Ă�̂�1��Ԃ�
	return D3DXVECTOR3(0.0f,0.0f,0.0f);
}

//��-------------------------------------------------------------------------��
// �|���S���ƕ��̂̐ݒu���Ă���Ƃ���Y��
//Player_Pos	: �v���C���[�Ƃ��̈ʒu
//Polygon_Pos0	: �v�Z�������|���S���̂R���_�̂����̂ǂꂩ���
//Polygon_Nor	: �|���S���̖@���B�����
//��-------------------------------------------------------------------------��
float CHitCheck::ConnectYVertex(const D3DXVECTOR3 Player_Pos,const D3DXVECTOR3 Polygon_Pos0,const D3DXVECTOR3 Polygon_Nor)
{
	float VtxY;

	VtxY = (- (Player_Pos.x - Polygon_Pos0.x) * Polygon_Nor.x
			- (Player_Pos.z - Polygon_Pos0.z) * Polygon_Nor.z)
			/ Polygon_Nor.y + Polygon_Pos0.y;


	return VtxY;
}

//��-------------------------------------------------------------------------��
// �|���S���ƕ��̂̐ݒu���Ă���Ƃ���Y���@���̂Q
//Player_Pos		: �v���C���[�Ƃ��̈ʒu
//Polygon_Pos0,1,2	: �v�Z�������|���S���̂R���_
//��-------------------------------------------------------------------------��
float CHitCheck::ConnectYVertex(const D3DXVECTOR3 Player_Pos,const D3DXVECTOR3 Polygon_Pos0,const D3DXVECTOR3 Polygon_Pos1,const D3DXVECTOR3 Polygon_Pos2)
{
	float VtxY;

	D3DXVECTOR3 Vec01 = Polygon_Pos1 - Polygon_Pos0;
	D3DXVECTOR3 Vec02 = Polygon_Pos2 - Polygon_Pos0;

	// �|���S���̊O�ς��Ƃ��Ė@�������߂Ă���
	D3DXVECTOR3 Nor = crossProduct(Vec01,Vec02);


	VtxY = (- (Player_Pos.x - Polygon_Pos0.x) * Nor.x
			- (Player_Pos.z - Polygon_Pos0.z) * Nor.z)
			/ Nor.y + Polygon_Pos0.y;


	return VtxY;
}
