//��-------------------------------------------------------------------------��
//
//	File:CMeshHitCheckBall�̃t�@�C��[CMeshHitCheckBall.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CMeshHitCheckBall.h"
#include "CManager.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CMeshHitCheckBall�̃R���X�g���N�^
//��-----------------------------------��
CMeshHitCheckBall::CMeshHitCheckBall(int nPriority) : CMeshBasisClass(nPriority)
{
	m_BallRadius = 0.0f;
}

//��-----------------------------------��
//CMeshHitCheckBall�̃f�X�g���N�^
//��-----------------------------------��
CMeshHitCheckBall::~CMeshHitCheckBall()
{

}

//��-----------------------------------��
//CMeshHitCheckBall�̏���������
//��-----------------------------------��
HRESULT CMeshHitCheckBall::Init(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	
	//***�e�N�X�e���̓ǂݍ���***
//	m_Texture = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_TexName));

	int dansuu = 3;

//	m_PolygonNum = (CHECKBALL_VTXNUM - 2)*2;
//	m_IndexNum = (m_PolygonNum + 2)*3;		//���������K��
//	m_VtxNum = CHECKBALL_VTXNUM;

	m_PolygonNum = (2 * (CHECLBALL_ONEVTX * CHECLBALL_ONEVTX) + (CHECKBALL_DANSUU - 1) * 4);
	m_IndexNum = (m_PolygonNum + 2);
	m_VtxNum = ((CHECLBALL_ONEVTX + 1) * (CHECKBALL_DANSUU + 1));

	//****�C���f�b�N�X�o�b�t�@�̊m��****
	pDevice -> CreateIndexBuffer(sizeof(WORD) * m_IndexNum,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&m_IdxBuffer,NULL);

	//***���_���̐ݒ�***
	//****���_�o�b�t�@�̐ݒ�****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D)) * m_VtxNum,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_VtxBuffer,NULL);

	//===================���_�o�b�t�@�f�[�^�����b�N==========================
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);
	


	float AngleX = 0.0f;
	float AngleY = 0.0f;

	for(int nCntY = 0;nCntY < CHECKBALL_DANSUU;nCntY++)
	{
		for(int nCntX = 0;nCntX < CHECLBALL_ONEVTX;nCntX++)
		{
			D3DXVECTOR3 Pos;

			Pos.x = sinf(AngleX) * sinf(AngleY);
			Pos.y = cosf(AngleY);
			Pos.z = cosf(AngleX) * sinf(AngleY);

			m_BallVtxVec[nCntX + nCntY * CHECLBALL_ONEVTX] = Pos;
			m_pVtx[nCntX + nCntY * CHECLBALL_ONEVTX].pos = Pos * m_BallRadius;

			AngleX += D3DX_PI*2 / (float)CHECLBALL_ONEVTX;
		}

		AngleX = 0.0f;

		AngleY += D3DX_PI / (CHECKBALL_DANSUU - 1);
	}



	//****�J���[�Ɩ@���̐ݒ�*****
	for(int nCnt = 0;nCnt < m_VtxNum;nCnt++)
	{
		m_pVtx[nCnt].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
		m_pVtx[nCnt].col = D3DCOLOR_RGBA(55,0,255,55);
	}

	//****tex�̐ݒ�****
	float TexCntX = 0.0f;	//tex�ł̂ݎg��
	float TexCntY = 0.0f;	//tex�ł̂ݎg��

	for(int CntX = 0;CntX < m_VtxNum;CntX++)
	{
		m_pVtx[CntX].tex = D3DXVECTOR2(0.0f,0.0f);
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
			IdxNum += (2 + CHECKBALL_DANSUU);
		}
		else
		{
			IdxNum -= (1 + CHECKBALL_DANSUU);
		}

		//�d�˂�|���S���������狭���Ƀ_�u�点��@�Ō�ȊO
		if(IdxNum == CHECKBALL_DANSUU * IdxdansuuCnt + IdxdansuuCnt -1 && nCnt != m_IndexNum - 1)
		{
			//�܂���̒��_�𓯂��Ƃ���ɃZ�b�g����
			m_pIdx[nCnt] = IdxNum;
			m_pIdx[nCnt + 1] = IdxNum;
			//�����̂Ƃ���Ɉړ����Ă���Z�b�g����B
			IdxNum += (2 + CHECKBALL_DANSUU);
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
//CMeshHitCheckBall�̕`�揈��
//��-----------------------------------��
void CMeshHitCheckBall::Draw(void)
{
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);

	CScene *pIrekoScene[512] = {NULL};

	for(int i = 0;i < PRIORITY_NUM;i++)
	{
		CScene::SearchLinkList(pIrekoScene,i);

		for(int i_2 = 0;pIrekoScene[i_2] != NULL;i_2++)
		{

			//�����蔻��̂��鐔�������
			for(int i_3 = 0;i_3 < pIrekoScene[i_2]->GetCollisionHitNum();i_3++)
			{
				//===================���_�o�b�t�@�f�[�^�����b�N==========================
				m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

				SetBallRadius(pIrekoScene[i_2]->GetCollisionRadius(i_3));

				//============���_�o�b�t�@�f�[�^�̃��b�N����============
				m_VtxBuffer->Unlock();
			
				SetPosition(pIrekoScene[i_2]->GetCollisionCenterPos(i_3));



				//****���[���h�̐ݒ�****
				D3DXMatrixIdentity(&m_mtxWorld);
				D3DXMatrixScaling(&mtxScl,m_Scl.x,
											m_Scl.y,
											m_Scl.z);			//�X�P�[���𔽉f

				D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

				//****���̑��̐ݒ�****
				D3DXMatrixRotationYawPitchRoll(&mtxRot,m_Rot.y,
												m_Rot.x,
												m_Rot.z);		//���|�@�s�b�`�@���[��

				D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
				D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);		//�ʒu�𔽉f
				D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	
				pDevice -> SetTransform(D3DTS_WORLD,&m_mtxWorld);	//�ݒ�



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



			}
		}

		//����̂��߂ɑS���Ƀk��������
		for(int i_4 = 0;pIrekoScene[i_4] != NULL;i_4++)
		{
			pIrekoScene[i_4] = NULL;
		}
		
	}
	pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//��-----------------------------------��
//CMeshHitCheckBall�̔��a�̐ݒ�
//��-----------------------------------��
void CMeshHitCheckBall::SetBallRadius(float Radius)
{
	for(int i = 0;i < CHECKBALL_VTXNUM;i++)
	{
		m_pVtx[i].pos = m_BallVtxVec[i] * Radius;
	}
}

//��-----------------------------------��
//CMeshHitCheckBall�̃N���G�C�g
//��-----------------------------------��
CMeshHitCheckBall *CMeshHitCheckBall::Create()
{
	CMeshHitCheckBall *pCheckBall;
	pCheckBall = new CMeshHitCheckBall;

	pCheckBall->Init();

	return pCheckBall;
}
