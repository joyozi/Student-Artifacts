//��-------------------------------------------------------------------------��
//
//	File:CDegeneracyStar�̃t�@�C��[CDegeneracyStar.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CDegeneracyStar.h"
#include "CManager.h"
#include "CPlayerModel.h"
#include "CCamera.h"
#include "CHitCheck.h"
#include "CItemList.h"
#include "CItemList.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CDegeneracyStar�̃R���X�g���N�^
//��-----------------------------------��
CDegeneracyStar::CDegeneracyStar(int nPriority) : CDegeneracyPolygon(nPriority)
{
	m_Type = CTYPE_DEGENERACYSTAR;

	m_DegeneracyPolygon_Max = DEGENERACYSTAR_MAX;

	for(int i = 0;i < DEGENERACYSTAR_MAX;i++)
	{
		m_PolygonColorJudge[i] = false;

		m_PolygonColor[i] = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	}

	m_BillboardJudge = true;
	m_AlphaBlendJudge = true;
	m_SortJudge = false;
}

//��-----------------------------------��
//CDegeneracyStar�̃f�X�g���N�^
//��-----------------------------------��
CDegeneracyStar::~CDegeneracyStar()
{

}

//��-----------------------------------��
//CDegeneracyStar�̃Z�b�g�����p��Init
//��-----------------------------------��
void CDegeneracyStar::SetOnlyInit(void)
{
	int MinLength = 5000;
	float Size;
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 KariRot;



	for(int i = 0;i < m_DegeneracyPolygon_Max;i++)
	{
		//�����p�ł������ʊp
		KariRot.x = D3DX_PI / 180 * (float)(rand()%360);
		KariRot.y = D3DX_PI / 180 * (float)(rand()%360);
		KariRot.z = 0.0f;

		Pos.x = -MinLength * cosf(KariRot.x) * cosf(KariRot.y);
		Pos.y = +MinLength * sinf(KariRot.x);
		Pos.z = +MinLength * cosf(KariRot.x) * sinf(KariRot.y);

		Size = (float)(rand()%50) + 50.0f;
		SetPolygon(Pos,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);



		if(rand()%2 == 0)
			m_PolygonColorJudge[i] = true;

		//�F�̃����_��
		switch(rand()%4)
		{
		case 0:		//���傢��
			m_PolygonColor[i] = D3DXCOLOR(0.2f,1.0f,1.0f,1.0f);
			break;
		case 1:		//��
			m_PolygonColor[i] = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			break;
		case 2:		//���F
			m_PolygonColor[i] = D3DXCOLOR(1.0f,0.0f,1.0f,1.0f);
			break;
		case 3:		//��
			m_PolygonColor[i] = D3DXCOLOR(1.0f,0.0f,1.0f,1.0f);
			break;
		default:
			break;
		}
	
		m_PolygonColor[i].a = 0.1f * (float)(rand()%10);
		ParticleSetColor(i,m_PolygonColor[i]);
	}



	D3DXMATRIX Matrix;
	D3DXVECTOR3 KariPos[4];
	D3DXMATRIX mtxRot;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&Matrix);

	//�t�s������߂�
	D3DXMatrixInverse(&Matrix,NULL,&CManager::GetCameraPointer()->GetMtxView());
	Matrix._41 = 0.0f;
	Matrix._42 = 0.0f;
	Matrix._43 = 0.0f;

	//===================���_�o�b�t�@�f�[�^�����b�N==========================
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	for(int i = 0;i < m_DegeneracyPolygon_Max;i++)
	{
		if(m_pPolygonExistJudge[i])
		{
			KariPos[0].x = m_pLength[i] * sinf(m_pAngle[i] + D3DX_PI);
			KariPos[1].x = m_pLength[i] * sinf(m_pAngle[i]);
			KariPos[2].x = m_pLength[i] * sinf(m_pAngle[i] + D3DX_PI);
			KariPos[3].x = m_pLength[i] * sinf(m_pAngle[i]);

			KariPos[0].y = m_pLength[i] * cosf(m_pAngle[i]);
			KariPos[1].y = m_pLength[i] * cosf(m_pAngle[i]);
			KariPos[2].y = m_pLength[i] * cosf(m_pAngle[i] + D3DX_PI);
			KariPos[3].y = m_pLength[i] * cosf(m_pAngle[i] + D3DX_PI);

			KariPos[0].z = 0.0f;
			KariPos[1].z = 0.0f;
			KariPos[2].z = 0.0f;
			KariPos[3].z = 0.0f;

			for(int i_2 = 0;i_2 < 4;i_2++)
			{
				D3DXVec3TransformCoord(&KariPos[i_2],&KariPos[i_2],&Matrix);

				KariPos[i_2].x += m_pDegeneracyPolygonPos[i].x;
				KariPos[i_2].y += m_pDegeneracyPolygonPos[i].y;
				KariPos[i_2].z += m_pDegeneracyPolygonPos[i].z;
			}

			m_pVtx[(i * 4) + 0].pos = KariPos[0];
			m_pVtx[(i * 4) + 1].pos = KariPos[1];
			m_pVtx[(i * 4) + 2].pos = KariPos[2];
			m_pVtx[(i * 4) + 3].pos = KariPos[3];
		}
	}

	//===================���_�o�b�t�@�f�[�^�̃��b�N����======================
	m_VtxBuffer->Unlock();

	m_PolygonNum = 0;

	//�`�掞�ɕK�v�ȃ|���S�����̐ݒ�
	for(int i = 0;i < m_DegeneracyPolygon_Max;i++)
	{
		if(i == 0)
			m_PolygonNum += 2;
		else
			m_PolygonNum += 6;
	}

}

//��-----------------------------------��
//CDegeneracyStar�̍X�V����
//��-----------------------------------��
void CDegeneracyStar::Update(void)
{
	for(int i = 0;i < m_DegeneracyPolygon_Max;i++)
	{
		if(m_PolygonColorJudge[i])
		{
			m_PolygonColor[i].a += 0.01f;
		}
		else
		{
			m_PolygonColor[i].a -= 0.01f;
		}

		if(m_PolygonColor[i].a > 1.0f)
		{
			m_PolygonColor[i].a = 1.0f;
			m_PolygonColorJudge[i] = false;
		}
		else if(m_PolygonColor[i].a <= 0.0f)
		{
			m_PolygonColor[i].a = 0.0f;
			m_PolygonColorJudge[i] = true;
		}

		ParticleSetColor(i,m_PolygonColor[i]);
	}

	CScene *pPlayer = NULL;
	CScene::SearchLinkList(&pPlayer,CTYPE_PLAYERMODEL);

	if(pPlayer)
		m_Pos = pPlayer->GetPosition();
}


//��-----------------------------------��
//CDegeneracyStar�̕`�揈��
//��-----------------------------------��
void CDegeneracyStar::Draw(void)
{
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	D3DXMATRIX Matrix;
	D3DXVECTOR3 KariPos[4];

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&Matrix);

	//�t�s������߂�
	D3DXMatrixInverse(&Matrix,NULL,&CManager::GetCameraPointer()->GetMtxView());
	Matrix._41 = 0.0f;
	Matrix._42 = 0.0f;
	Matrix._43 = 0.0f;

	for(int i = 0;i < m_DegeneracyPolygon_Max;i++)
	{
		KariPos[0].x = m_pLength[i] * sinf(m_pAngle[i] + D3DX_PI);
		KariPos[1].x = m_pLength[i] * sinf(m_pAngle[i]);
		KariPos[2].x = m_pLength[i] * sinf(m_pAngle[i] + D3DX_PI);
		KariPos[3].x = m_pLength[i] * sinf(m_pAngle[i]);

		KariPos[0].y = m_pLength[i] * cosf(m_pAngle[i]);
		KariPos[1].y = m_pLength[i] * cosf(m_pAngle[i]);
		KariPos[2].y = m_pLength[i] * cosf(m_pAngle[i] + D3DX_PI);
		KariPos[3].y = m_pLength[i] * cosf(m_pAngle[i] + D3DX_PI);

		KariPos[0].z = 0.0f;
		KariPos[1].z = 0.0f;
		KariPos[2].z = 0.0f;
		KariPos[3].z = 0.0f;

		for(int i_2 = 0;i_2 < 4;i_2++)
		{
			D3DXVec3TransformCoord(&KariPos[i_2],&KariPos[i_2],&Matrix);

			KariPos[i_2].x += m_pDegeneracyPolygonPos[i].x;
			KariPos[i_2].y += m_pDegeneracyPolygonPos[i].y;
			KariPos[i_2].z += m_pDegeneracyPolygonPos[i].z;
		}

		m_VtxBox[(i * 4) + 0].pos = KariPos[0];
		m_VtxBox[(i * 4) + 1].pos = KariPos[1];
		m_VtxBox[(i * 4) + 2].pos = KariPos[2];
		m_VtxBox[(i * 4) + 3].pos = KariPos[3];
	}

	//===================���_�o�b�t�@�f�[�^�����b�N==========================
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	for(int i = 0;i < m_DegeneracyPolygonNum;i++)
	{
		m_pVtx[(i * 4) + 0] = m_VtxBox[(i * 4) + 0];
		m_pVtx[(i * 4) + 1] = m_VtxBox[(i * 4) + 1];
		m_pVtx[(i * 4) + 2] = m_VtxBox[(i * 4) + 2];
		m_pVtx[(i * 4) + 3] = m_VtxBox[(i * 4) + 3];
	}

	//===================���_�o�b�t�@�f�[�^�̃��b�N����======================
	m_VtxBuffer->Unlock();



	//****���[���h�̐ݒ�****
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&mtxScl,m_Scl.x,
								m_Scl.y,
								m_Scl.z);								//�X�P�[���𔽉f

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

	//****���̑��̐ݒ�****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_Rot.y,m_Rot.x,m_Rot.z);	//���|�@�s�b�`�@���[��
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);

	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);		//�ʒu�𔽉f
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&m_mtxWorld);	//�ݒ�
	
	//�G�t�F�N�g�����@���鏈��
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
	//�[�b�g���o�b�t�@�̖���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE ,FALSE);

	//3D�|���S���̕`��
	pDevice->SetStreamSource(0,m_VtxBuffer,0,sizeof(VERTEX_3D));
	//���_�o�b�t�@���o�C���h
	pDevice -> SetIndices(m_IdxBuffer);		//�C���f�b�N�X�o�b�t�@���o�C���h
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,m_Texture);
	//�h���E�v���~�e�B�u
	pDevice -> DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_VtxNum,0,m_PolygonNum);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE ,TRUE);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
}

//��-----------------------------------��
//CDegeneracyStar�̃N���G�C�g
//��-----------------------------------��
CDegeneracyStar *CDegeneracyStar::Create(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot)
{
	CDegeneracyStar *pDegeneracyStar;
	pDegeneracyStar = new CDegeneracyStar;

	pDegeneracyStar->m_TexName = TexName;
	pDegeneracyStar->m_Pos = Pos;
	pDegeneracyStar->m_Rot = Rot;

	pDegeneracyStar->Init();

	return pDegeneracyStar;
}
