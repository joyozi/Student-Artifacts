//��-------------------------------------------------------------------------��
//
//	File:CMeshSky�̃t�@�C��[CMeshSky.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "CMeshSky.h"
#include "CManager.h"
#include "CTextureManager.h"

//��-----------------------------------��
//CMeshSky�̃R���X�g���N�^
//��-----------------------------------��
CMeshSky::CMeshSky(int nPriority) : CMeshBasisClass(nPriority)
{
	m_Type = CTYPE_MESHSKY;

	m_PolygonNum = (2 * (MESHSKY_BUNKATSU * MESHSKY_DANSUU) + (MESHSKY_DANSUU - 1) * 4);
	m_IndexNum = (m_PolygonNum + 2);
	m_VtxNum = ((MESHSKY_BUNKATSU + 1) * (MESHSKY_DANSUU + 1));
}

//��-----------------------------------��
//CMeshSky�̃f�X�g���N�^
//��-----------------------------------��
CMeshSky::~CMeshSky()
{

}

//��-----------------------------------��
//CMeshSky�̏���������
//��-----------------------------------��
HRESULT CMeshSky::Init(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	
	//***�e�N�X�e���̓ǂݍ���***
	m_Texture = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_TexName));

	//****�C���f�b�N�X�o�b�t�@�̊m��****
	pDevice -> CreateIndexBuffer(sizeof(WORD) * m_IndexNum,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&m_IdxBuffer,NULL);

	//***���_���̐ݒ�***
	//****���_�o�b�t�@�̐ݒ�****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D)) * m_VtxNum,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_VtxBuffer,NULL);

	//===================���_�o�b�t�@�f�[�^�����b�N==========================
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	float radX = 0.0f;									//�p�x�����߂郉�W�A��X�p
	float radY = D3DX_PI / 2;							//�p�x�����߂郉�W�A��Y�p
	float VtxX = 0.0f,VtxY = 0.0f,VtxZ = 0.0f;			//���W�����߂�p�̕ϐ�
	float hankei = 0.0f;								//�X�J�C�̔��a(�Œ�)
	float hankei_num = 0.0f;							//�X�J�C�̔��a(�v�Z�p)

	//���a�����߂�
	hankei = (MESHSKY_PELYGON_WIDTH/2) / sinf(D3DX_PI*2 / MESHSKY_BUNKATSU / 2);
	
	//Y���̍��������߂�
	VtxY = 0.0f;
	for(int i = 0;i < MESHSKY_DANSUU;i++)
	{
		//Y���̊p�x�����ɉ����� �p�x��ς��Ă��炶��Ȃ��ƍŏ��̈ړ���0�ɂ̂܂�
		radY -= (D3DX_PI / 2) / MESHSKY_DANSUU;
		VtxY += MESHSKY_POLYGON_HEIGHT * cosf(radY);

	}

	//�l�����ɖ߂�
	radY = D3DX_PI / 2;

	//�c�̒i�����J��Ԃ�
	for(int CntY = 0;CntY < MESHSKY_DANSUU + 1;CntY++)
	{
		//���̒i�����J��Ԃ�
		for(int CntX = 0;CntX < MESHSKY_BUNKATSU + 1;CntX++)
		{
			VtxX = sinf(radX) * hankei_num;
			VtxZ = cosf(radX) * hankei_num;

			//���_�̑��
			m_pVtx[CntY * (MESHSKY_BUNKATSU + 1) + CntX].pos = D3DXVECTOR3(VtxX,VtxY,VtxZ);

			//X,Z���̊p�x�����߂�
			radX += (D3DX_PI * 2) / MESHSKY_BUNKATSU;
		}

		radX = 0.0f;
		
		//Y���̊p�x�����ɂ����AY�������߂�
		radY -= (D3DX_PI / 2) / MESHSKY_DANSUU;
		VtxY -= MESHSKY_POLYGON_HEIGHT * cosf(radY);

		//���a��傫������
		hankei_num -= hankei * sinf(radY);
	}



	//****�����ƃJ���[�̐ݒ�*****
	for(int nCnt = 0;nCnt < m_VtxNum;nCnt++)
	{
		m_pVtx[nCnt].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
		m_pVtx[nCnt].col = D3DCOLOR_RGBA(255,255,255,55);
	}

	//****tex�̐ݒ�****
	float TexCntX = 0.0f;	//tex�ł̂ݎg��
	float TexCntY = 0.0f;	//tex�ł̂ݎg��

	//�c�̒i�� + 1�J��Ԃ�		1�i�Ȃ�Y����2���_���邩��
	for(int CntY = 0;CntY < MESHSKY_DANSUU+1;CntY++)
	{
		//���̒i�����J��Ԃ�
		for(int CntX = 0;CntX < MESHSKY_BUNKATSU + 1;CntX++)
		{
			m_pVtx[CntY * (MESHSKY_BUNKATSU+1) + CntX].tex = D3DXVECTOR2(TexCntX,TexCntY);
			
			TexCntX += 1.0f / MESHSKY_BUNKATSU;


		}
		TexCntX = 0.0f;

		TexCntY += 1.0f / MESHSKY_DANSUU;
	}

	//============���_�o�b�t�@�f�[�^�̃��b�N����============
	m_VtxBuffer->Unlock();
	
	//============�C���f�b�N�X����ݒ�====================
	m_IdxBuffer -> Lock(0,0,(void**)&m_pIdx,0);

	//****m_pIdx�ւ̒i������****
	int IdxNum = -1;
	int IdxdansuuCnt = 1;


	//�i�����J��Ԃ�
	for(int nCnt = 0;nCnt < m_IndexNum;nCnt++)
	{
		if(nCnt % 2 == 0)
		{
			IdxNum += (2 + MESHSKY_BUNKATSU);
		}
		else
		{
			IdxNum -= (1 + MESHSKY_BUNKATSU);
		}

		//�d�˂�|���S���������狭���Ƀ_�u�点��@�Ō�ȊO
		if(IdxNum == MESHSKY_BUNKATSU * IdxdansuuCnt + IdxdansuuCnt -1 && nCnt != m_IndexNum - 1)
		{
			//�܂���̒��_�𓯂��Ƃ���ɃZ�b�g����
			m_pIdx[nCnt] = IdxNum;
			m_pIdx[nCnt + 1] = IdxNum;
			//�����̂Ƃ���Ɉړ����Ă���Z�b�g����B
			IdxNum += (2 + MESHSKY_BUNKATSU);
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

	return S_OK;
}

//��-----------------------------------��
//CMeshSky�̍X�V����
//��-----------------------------------��
void CMeshSky::Update(void)
{
	m_Rot.y += 0.0001f;
}

//��-----------------------------------��
//���b�V���X�J�C�̃N���G�C�g
//��-----------------------------------��
CMeshSky *CMeshSky::Create(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot)
{
	CMeshSky *pMeshSky;
	pMeshSky = new CMeshSky;

	pMeshSky->m_TexName = TexName;
	pMeshSky->m_Pos = Pos;
	pMeshSky->m_Rot = Rot;

	pMeshSky->Init();

	return pMeshSky;
}

