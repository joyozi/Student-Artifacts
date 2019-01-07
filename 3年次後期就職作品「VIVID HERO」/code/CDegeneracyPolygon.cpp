//��-------------------------------------------------------------------------��
//
//	File:CDegeneracyPolygon�̃t�@�C��[CDegeneracyPolygon.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CDegeneracyPolygon.h"
#include "CManager.h"
#include "CItemList.h"
#include "CTextureManager.h"
#include "CCamera.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CDegeneracyPolygon�̃R���X�g���N�^
//��-----------------------------------��
CDegeneracyPolygon::CDegeneracyPolygon(int nPriority) : CMeshBasisClass(nPriority)
{
	m_Type = CTYPE_DEGENERACYPOLYGON;

	m_DegeneracyPolygon_Max = DEGENERACYPOLYGON_MAX;

	m_DegeneracyPolygonNum = 0;

	m_pLength = NULL;
	m_pAngle = NULL;
	m_pDegeneracyPolygonPos = NULL;
	m_pPolygonExistJudge = NULL;
	m_pDegeneracyPolygonRot = NULL;
	m_BillboardJudge = true;
	m_AlphaBlendJudge = true;
	m_SortJudge = true;
	m_LoopJudge = true;
	m_pPolygonUninitFlag = NULL;
}

//��-----------------------------------��
//CDegeneracyPolygon�̃f�X�g���N�^
//��-----------------------------------��
CDegeneracyPolygon::~CDegeneracyPolygon()
{

}

//��-----------------------------------��
//CDegeneracyPolygon�̏���������
//��-----------------------------------��
HRESULT CDegeneracyPolygon::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	
	//***�e�N�X�e���̓ǂݍ���***
	m_Texture = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_TexName));



	int Index_Max = m_DegeneracyPolygon_Max * 4 + ((m_DegeneracyPolygon_Max - 1) * 2);
	int Vtx_Max = m_DegeneracyPolygon_Max * 4;

	m_pLength = new float[m_DegeneracyPolygon_Max];
	m_pAngle = new float[m_DegeneracyPolygon_Max];
	m_pDegeneracyPolygonPos = new D3DXVECTOR3[m_DegeneracyPolygon_Max];
	m_pPolygonExistJudge = new bool[m_DegeneracyPolygon_Max];
	m_pDegeneracyPolygonRot = new D3DXVECTOR3[m_DegeneracyPolygon_Max];
	m_pPolygonUninitFlag = new bool[m_DegeneracyPolygon_Max];

	m_VtxBox = new VERTEX_3D[Vtx_Max];

	for(int i = 0;i < m_DegeneracyPolygon_Max;i++)
	{
		m_pPolygonExistJudge[i] = false;
		m_pLength[i] = 0.0f;
		m_pAngle[i] = 0.0f;
		m_pDegeneracyPolygonPos[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_pDegeneracyPolygonRot[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_pPolygonUninitFlag[i] = false;
	}



	//****�C���f�b�N�X�o�b�t�@�̊m��****
	pDevice->CreateIndexBuffer(sizeof(WORD) * Index_Max,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&m_IdxBuffer,NULL);

	//***���_���̐ݒ�***
	//****���_�o�b�t�@�̐ݒ�****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*Vtx_Max,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_VtxBuffer,NULL);



	//���_�����J��Ԃ�
	for(int nCnt = 0;nCnt < Vtx_Max;nCnt++)
	{
		//�ŏ��ɑ��
		m_VtxBox[nCnt].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_VtxBox[nCnt].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		m_VtxBox[nCnt].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	}

	//****tex�̐ݒ�****
	float TexCntx = 0.0f;	//tex�ł̂ݎg��
	float TexCnty = 0.0f;	//tex�ł̂ݎg��

	for(int nCnt = 0;nCnt < Vtx_Max;nCnt++)
	{
		m_VtxBox[nCnt].tex = D3DXVECTOR2(TexCntx,TexCnty);
		TexCntx += 1.0f;

		//�E���ɂȂ�����݂�����
		if(nCnt % 2 == 1)
		{
			TexCntx = 0.0f;
			if(TexCnty == 0.0f)
				TexCnty += 1.0f;
			else
				TexCnty = 0.0f;
		}
	}

	//============�C���f�b�N�X����ݒ�====================
	m_IdxBuffer -> Lock(0,0,(void**)&m_pIdx,0);

	//****m_pIdx�ւ̒i������****
	int IdxNum = -1;
	int IdxdansuuCnt = 1;

	int PolygonNumX = 1;		//���̃|���S���̐�

	for(int nCnt = 0;nCnt < Index_Max;nCnt++)
	{
		if(nCnt % 2 == 0)
		{
			IdxNum += (2 + PolygonNumX);
		}
		else
		{
			IdxNum -= (1 + PolygonNumX);
		}

		//1 5 9 13
		if(IdxNum == (IdxdansuuCnt - 1) * 4 + 1 && IdxNum != (m_DegeneracyPolygon_Max - 1) * 4 + 1)
		{
			//�܂���̒��_�𓯂��Ƃ���ɃZ�b�g����
			m_pIdx[nCnt] = IdxNum;
			m_pIdx[nCnt + 1] = IdxNum;
			//�����̂Ƃ���Ɉړ����Ă���Z�b�g����B
			IdxNum += (4 + PolygonNumX);
			m_pIdx[nCnt + 2] = IdxNum;

			//�O���������̂�3�𑫂��@����m_pIdx[nCnt] = IdxNum�Ō��ʓI�ɓ����Ƃ���̐��l��������
			nCnt += 3;

			//Z�������ɃV�t�g����
			IdxdansuuCnt++;
		}

		m_pIdx[nCnt] = IdxNum;
	}

	//============�C���f�b�N�X�o�b�t�@�̃��b�N����============
	m_IdxBuffer -> Unlock();
	
	SetOnlyInit();

	return S_OK;
}

//��-----------------------------------��
//CDegeneracyPolygon�̃Z�b�g�����p��Init
//��-----------------------------------��
void CDegeneracyPolygon::SetOnlyInit(void)
{

}

//��-----------------------------------��
//CDegeneracyPolygon�̏I������
//��-----------------------------------��
void CDegeneracyPolygon::Uninit(void)
{
	Release();

	SAFE_RELEASE(m_VtxBuffer);
	SAFE_RELEASE(m_IdxBuffer);

	SAFE_DELETE_ARRY(m_pAngle);
	SAFE_DELETE_ARRY(m_pLength);
	SAFE_DELETE_ARRY(m_pDegeneracyPolygonPos);
	SAFE_DELETE_ARRY(m_pPolygonExistJudge);
	SAFE_DELETE_ARRY(m_pDegeneracyPolygonRot);
	SAFE_DELETE_ARRY(m_VtxBox);
	SAFE_DELETE_ARRY(m_pPolygonUninitFlag);

}

//��-----------------------------------��
//CDegeneracyPolygon�̕`�揈��
//��-----------------------------------��
void CDegeneracyPolygon::Draw(void)
{
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;



	//�r���{�[�h�ɂ��邩�ǂ���
	if(m_BillboardJudge)
	{
		D3DXMATRIX Matrix;
		D3DXVECTOR3 KariPos[4] = {D3DXVECTOR3(0.0f,0.0f,0.0f)};
		D3DXMATRIX mtxRot;

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&Matrix);

		//�t�s������߂�
		D3DXMatrixInverse(&Matrix,NULL,&CManager::GetCameraPointer()->GetMtxView());
		Matrix._41 = 0.0f;
		Matrix._42 = 0.0f;
		Matrix._43 = 0.0f;

		for(int i = 0;i < m_DegeneracyPolygon_Max;i++)
		{
			if(m_pPolygonExistJudge[i])
			{
				KariPos[0].x = m_pLength[i] * sinf(m_pAngle[i] + D3DX_PI);
				KariPos[1].x = m_pLength[i] * sinf(m_pAngle[i]);
				KariPos[2].x = KariPos[0].x;
				KariPos[3].x = KariPos[1].x;

				KariPos[0].y = m_pLength[i] * cosf(m_pAngle[i]);
				KariPos[1].y = KariPos[0].y;
				KariPos[2].y = m_pLength[i] * cosf(m_pAngle[i] + D3DX_PI);
				KariPos[3].y = KariPos[2].y;

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
		}
	}



	//===================���_�o�b�t�@�f�[�^�����b�N==========================
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	int PolygonCnt = 0;

	for(int i = 0;i < m_DegeneracyPolygonNum;i++)
	{
		if(m_pPolygonExistJudge[i])
		{
			m_pVtx[(PolygonCnt * 4) + 0] = m_VtxBox[(i * 4) + 0];
			m_pVtx[(PolygonCnt * 4) + 1] = m_VtxBox[(i * 4) + 1];
			m_pVtx[(PolygonCnt * 4) + 2] = m_VtxBox[(i * 4) + 2];
			m_pVtx[(PolygonCnt * 4) + 3] = m_VtxBox[(i * 4) + 3];

			if(m_pPolygonUninitFlag[PolygonCnt])
			{
				m_pPolygonExistJudge[PolygonCnt] = false;
				m_pPolygonUninitFlag[PolygonCnt] = false;
			}

			PolygonCnt++;
		}
	}
	
	m_PolygonNum = 0;
	//�`�掞�ɕK�v�ȃ|���S�����̐ݒ�
	for(int i = 0;i < PolygonCnt;i++)
	{
		if(i == 0)
			m_PolygonNum += 2;
		else
			m_PolygonNum += 6;
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
	
	if(m_AlphaBlendJudge)
	{
		//�G�t�F�N�g�����@���鏈��
		pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE ,FALSE);
	}

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

	if(m_AlphaBlendJudge)
	{
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE ,TRUE);
		pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	}
}


//��-----------------------------------��
//CDegeneracyPolygon�̃N���G�C�g
//��-----------------------------------��
CDegeneracyPolygon *CDegeneracyPolygon::Create(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot)
{
	CDegeneracyPolygon *pDegeneracyPolygon;
	pDegeneracyPolygon = new CDegeneracyPolygon;

	pDegeneracyPolygon->m_TexName = TexName;
	pDegeneracyPolygon->m_Pos = Pos;
	pDegeneracyPolygon->m_Rot = Rot;

	pDegeneracyPolygon->Init();

	return pDegeneracyPolygon;
}



//��-----------------------------------��
//CDegeneracyPolygon�̃Z�b�g�|���S��
//��-----------------------------------��
int CDegeneracyPolygon::SetPolygon(D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,float Width,float Height)
{
	//���̐��l�����炤 �E�̂������ƌJ��Ԃ��Ƃ��ɐ��l���ς���Ă��Ă��܂�����
	int PolygonNumNow = m_DegeneracyPolygonNum;		//����ǂ��̔ԍ��ɓ���邩�ƁA�S�̂ɕ\������Ă�|���S����

	//�����Z�b�g�ł���|���S���𒴂��Ă���
	if(PolygonNumNow >= m_DegeneracyPolygon_Max && m_LoopJudge)
	{
		//�ő吔�܂ōs������J��Ԃ��邩������
		for(int i = 0;i < m_DegeneracyPolygon_Max;i++)
		{
			if(m_pPolygonExistJudge[i] == false)
			{
				PolygonNumNow = i;
				break;
			}
		}
	}

	if(PolygonNumNow >= m_DegeneracyPolygon_Max)
	{
		//�Ȃ�������I���
		return -1;
	}

	m_pPolygonExistJudge[PolygonNumNow] = true;



	//����������Z�Ƃ����Ēx���悤�ȋC����������
	float Width_Harh = Width / 2;
	float Height_Harh = Height / 2;

	//�������H�����߂�?
	m_pLength[PolygonNumNow] = sqrtf((Width_Harh * Width_Harh) + (Height_Harh * Height_Harh));
	//�p�x�����߂�
	m_pAngle[PolygonNumNow] = atan2f(Width_Harh,Height_Harh);
	//�ʒu��ۑ�
	m_pDegeneracyPolygonPos[PolygonNumNow] = Pos;

	D3DXVECTOR3 KariPos[4];

	m_VtxBox[(PolygonNumNow * 4) + 0].pos.x = Pos.x + m_pLength[PolygonNumNow] * sinf(m_pAngle[PolygonNumNow] + D3DX_PI);
	m_VtxBox[(PolygonNumNow * 4) + 1].pos.x = Pos.x + m_pLength[PolygonNumNow] * sinf(m_pAngle[PolygonNumNow]);
	m_VtxBox[(PolygonNumNow * 4) + 2].pos.x = Pos.x + m_pLength[PolygonNumNow] * sinf(m_pAngle[PolygonNumNow] + D3DX_PI);
	m_VtxBox[(PolygonNumNow * 4) + 3].pos.x = Pos.x + m_pLength[PolygonNumNow] * sinf(m_pAngle[PolygonNumNow]);

	m_VtxBox[(PolygonNumNow * 4) + 0].pos.y = Pos.y + m_pLength[PolygonNumNow] * cosf(m_pAngle[PolygonNumNow]);
	m_VtxBox[(PolygonNumNow * 4) + 1].pos.y = Pos.y + m_pLength[PolygonNumNow] * cosf(m_pAngle[PolygonNumNow]);
	m_VtxBox[(PolygonNumNow * 4) + 2].pos.y = Pos.y + m_pLength[PolygonNumNow] * cosf(m_pAngle[PolygonNumNow] + D3DX_PI);
	m_VtxBox[(PolygonNumNow * 4) + 3].pos.y = Pos.y + m_pLength[PolygonNumNow] * cosf(m_pAngle[PolygonNumNow] + D3DX_PI);

	m_VtxBox[(PolygonNumNow * 4) + 0].pos.z = Pos.z + 0.0f;
	m_VtxBox[(PolygonNumNow * 4) + 1].pos.z = Pos.z + 0.0f;
	m_VtxBox[(PolygonNumNow * 4) + 2].pos.z = Pos.z + 0.0f;
	m_VtxBox[(PolygonNumNow * 4) + 3].pos.z = Pos.z + 0.0f;

	if(m_DegeneracyPolygonNum < m_DegeneracyPolygon_Max)
		m_DegeneracyPolygonNum++;


	return PolygonNumNow;
}

//��-----------------------------------��
//CDegeneracyPolygon�̃Z�b�g�J���[
//��-----------------------------------��
int CDegeneracyPolygon::ParticleSetColor(int Num,D3DXCOLOR Col)
{
	//�����Z�b�g�ł���|���S���𒴂��Ă���
	if(Num >= m_DegeneracyPolygon_Max || Num < 0 || m_pPolygonExistJudge[Num] == false)
	{
		return -1;
	}

	D3DXCOLOR a = D3DXCOLOR(Col.r * Col.a,Col.g * Col.a,Col.b * Col.a,Col.a);

	m_VtxBox[(Num * 4) + 0].col = a;
	m_VtxBox[(Num * 4) + 1].col = a;
	m_VtxBox[(Num * 4) + 2].col = a;
	m_VtxBox[(Num * 4) + 3].col = a;

	return Num;
}

//��-----------------------------------��
//CDegeneracyPolygon�̈ړ�
//��-----------------------------------��
int CDegeneracyPolygon::ParticleSetPosition(int Num,D3DXVECTOR3 Pos)
{
	//�����Z�b�g�ł���|���S���𒴂��Ă���
	if(Num >= m_DegeneracyPolygon_Max || Num < 0 || m_pPolygonExistJudge[Num] == false)
	{
		return -1;
	}

	m_pDegeneracyPolygonPos[Num] = Pos;

	D3DXVECTOR3 KariPos[4];

	m_VtxBox[(Num * 4) + 0].pos.x = Pos.x + m_pLength[Num] * sinf(m_pAngle[Num] + D3DX_PI);
	m_VtxBox[(Num * 4) + 1].pos.x = Pos.x + m_pLength[Num] * sinf(m_pAngle[Num]);
	m_VtxBox[(Num * 4) + 2].pos.x = Pos.x + m_pLength[Num] * sinf(m_pAngle[Num] + D3DX_PI);
	m_VtxBox[(Num * 4) + 3].pos.x = Pos.x + m_pLength[Num] * sinf(m_pAngle[Num]);

	m_VtxBox[(Num * 4) + 0].pos.y = Pos.y + m_pLength[Num] * cosf(m_pAngle[Num]);
	m_VtxBox[(Num * 4) + 1].pos.y = Pos.y + m_pLength[Num] * cosf(m_pAngle[Num]);
	m_VtxBox[(Num * 4) + 2].pos.y = Pos.y + m_pLength[Num] * cosf(m_pAngle[Num] + D3DX_PI);
	m_VtxBox[(Num * 4) + 3].pos.y = Pos.y + m_pLength[Num] * cosf(m_pAngle[Num] + D3DX_PI);

	m_VtxBox[(Num * 4) + 0].pos.z = Pos.z + 0.0f;
	m_VtxBox[(Num * 4) + 1].pos.z = Pos.z + 0.0f;
	m_VtxBox[(Num * 4) + 2].pos.z = Pos.z + 0.0f;
	m_VtxBox[(Num * 4) + 3].pos.z = Pos.z + 0.0f;

	return Num;
}


//��-----------------------------------��
//CDegeneracyPolygon�̏���
//��-----------------------------------��
int CDegeneracyPolygon::ParticleUninitPosition(int Num)
{
	//�����Z�b�g�ł���|���S���𒴂��Ă���
	if(Num >= m_DegeneracyPolygon_Max || Num < 0 || m_pPolygonExistJudge[Num] == false)
	{
		return Num;
	}

	m_pDegeneracyPolygonPos[Num] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_pDegeneracyPolygonRot[Num] = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_pLength[Num] = 0.0f;
	m_pAngle[Num] = 0.0f;

	m_VtxBox[(Num * 4) + 0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_VtxBox[(Num * 4) + 1].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_VtxBox[(Num * 4) + 2].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_VtxBox[(Num * 4) + 3].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_pPolygonUninitFlag[Num] = true;

	return -1;
}

