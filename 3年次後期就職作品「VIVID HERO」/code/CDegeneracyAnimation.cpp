//��-------------------------------------------------------------------------��
//
//	File:CDegeneracyAnimation�̃t�@�C��[CDegeneracyAnimation.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CDegeneracyAnimation.h"
#include "CScene3D.h"
#include "CManager.h"
#include "CTextureManager.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CDegeneracyAnimation�̃R���X�g���N�^
//��-----------------------------------��
CDegeneracyAnimation::CDegeneracyAnimation(int nPriority) : CDegeneracyPolygon(nPriority)
{
	m_DegeneracyPolygon_Max = DEGENERACYANIMATION_MAX;

	m_Anim_TexDivide_NumX = 10;
	m_Anim_TexDivide_NumY = 1;
	m_AnimTime = 60;

	m_LoopJudge = true;
	m_AnimationLoopJudge = true;
}

//��-----------------------------------��
//CDegeneracyAnimation�̃f�X�g���N�^
//��-----------------------------------��
CDegeneracyAnimation::~CDegeneracyAnimation()
{

}


//��-----------------------------------��
//CDegeneracyAnimation�̏���������
//��-----------------------------------��
HRESULT CDegeneracyAnimation::Init(void)
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

	//�A�j���[�V�����p�̏���
	m_pAnimTimeCnt = new int[m_DegeneracyPolygon_Max];

	for(int i = 0;i < m_DegeneracyPolygon_Max;i++)
	{
		m_pAnimTimeCnt[i] = 0;
	}

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
		TexCntx += (1.0f / m_Anim_TexDivide_NumX);

		//�E���ɂȂ�����݂�����
		if(nCnt % 2 == 1)
		{
			TexCntx = 0.0f;
			if(TexCnty == 0.0f)
				TexCnty += (1.0f / m_Anim_TexDivide_NumY);
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
//CDegeneracyAnimation�̂����Ƃ����[�Ƃ�
//��-----------------------------------��
void CDegeneracyAnimation::SetOnlyInit()
{

}

//��-----------------------------------��
//CDegeneracyAnimation�̏I������
//��-----------------------------------��
void CDegeneracyAnimation::Uninit(void)
{
	Release();

	SAFE_RELEASE(m_VtxBuffer);
	SAFE_RELEASE(m_IdxBuffer);

	SAFE_DELETE_ARRY(m_pAngle);
	SAFE_DELETE_ARRY(m_pLength);
	SAFE_DELETE_ARRY(m_pDegeneracyPolygonPos);
	SAFE_DELETE_ARRY(m_pPolygonExistJudge);
	SAFE_DELETE_ARRY(m_pDegeneracyPolygonRot);
	SAFE_DELETE_ARRY(m_pAnimTimeCnt);
	SAFE_DELETE_ARRY(m_VtxBox);
	SAFE_DELETE_ARRY(m_pPolygonUninitFlag);
}


//��-----------------------------------��
//CDegeneracyAnimation�̍X�V����
//��-----------------------------------��
void CDegeneracyAnimation::Update(void)
{
	int KetaCntX,KetaCntY;

	for(int i = 0;i < m_DegeneracyPolygonNum;i++)
	{
		if(m_pPolygonExistJudge[i])
		{
			KetaCntX = 0;
			KetaCntY = 0;

			//���Ԗڂ̕����ԍ���

			int j = m_pAnimTimeCnt[i] / (m_AnimTime / (m_Anim_TexDivide_NumX * m_Anim_TexDivide_NumY));

			KetaCntY = j / m_Anim_TexDivide_NumX;
			KetaCntX = j % m_Anim_TexDivide_NumX;



			m_VtxBox[(i * 4) + 0].tex = D3DXVECTOR2((float)((1.0f / m_Anim_TexDivide_NumX) * KetaCntX),		(float)((1.0f / m_Anim_TexDivide_NumY) * KetaCntY));
			m_VtxBox[(i * 4) + 1].tex = D3DXVECTOR2((float)((1.0f / m_Anim_TexDivide_NumX) * (KetaCntX + 1)),	(float)((1.0f / m_Anim_TexDivide_NumY) * KetaCntY));
			m_VtxBox[(i * 4) + 2].tex = D3DXVECTOR2((float)((1.0f / m_Anim_TexDivide_NumX) * KetaCntX),		(float)((1.0f / m_Anim_TexDivide_NumY) * (KetaCntY + 1)));
			m_VtxBox[(i * 4) + 3].tex = D3DXVECTOR2((float)((1.0f / m_Anim_TexDivide_NumX) * (KetaCntX + 1)),	(float)((1.0f / m_Anim_TexDivide_NumY) * (KetaCntY + 1)));
			
			m_pAnimTimeCnt[i] += 1;
			
			if(m_pAnimTimeCnt[i] > m_AnimTime)
			{
				if(m_AnimationLoopJudge)
				{
					m_pAnimTimeCnt[i] = 0;
				}
				else
				{
					m_pAnimTimeCnt[i] = 0;

					ParticleUninitPosition(i);
				}
			}
		}
		else
		{
			m_pAnimTimeCnt[i] = 0;
		}
	}
}

//��-----------------------------------��
//CDegeneracyAnimation�̃N���G�C�g
//��-----------------------------------��
CDegeneracyAnimation *CDegeneracyAnimation::Create(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,int DivideNumX,int DivideNumY,int AnimTime)
{
	CDegeneracyAnimation *pDegeneracyAnim;
	pDegeneracyAnim = new CDegeneracyAnimation;

	pDegeneracyAnim->m_TexName = TexName;
	pDegeneracyAnim->m_Pos = Pos;
	pDegeneracyAnim->m_Rot = Rot;
	pDegeneracyAnim->m_Anim_TexDivide_NumX = DivideNumX;
	pDegeneracyAnim->m_Anim_TexDivide_NumY = DivideNumY;

	pDegeneracyAnim->m_AnimTime = AnimTime;

	pDegeneracyAnim->Init();

	return pDegeneracyAnim;
}


