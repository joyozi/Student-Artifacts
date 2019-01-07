//��-------------------------------------------------------------------------��
//
//	File:CExplosion�̃t�@�C��[CExplosion.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CExplosion.h"
#include "CTextureManager.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CExplosion�̃R���X�g���N�^
//��-----------------------------------��
CExplosion::CExplosion(int nPriority) : CSceneBillboard(nPriority)
{
	m_Type = CTYPE_EXPLOSION;

	m_CounterAnim = 0;
	m_PatternAnim = 0;

	m_Texture = NULL;
	m_VtxBuffer = NULL;
}

//��-----------------------------------��
//CExplosion�̏���������
//�������tex�̊֌W�ň����p���Ȃ�
//��-----------------------------------��
HRESULT CExplosion::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	m_Texture = NULL;
	m_VtxBuffer = NULL;

	//***�e�N�X�e���̓ǂݍ���***
	m_Texture = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_TextureName));

	//***���_���̐ݒ�***
	//****���_�o�b�t�@�̐ݒ�****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_VtxBuffer,NULL);

	//�w�i�摜�̏��o�^
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	//���_���̐ݒ�
	m_pVtx[0].pos = D3DXVECTOR3(-TextureWidth / 2,TextureHeight / 2,0.0f);
	m_pVtx[1].pos = D3DXVECTOR3(TextureWidth / 2,TextureHeight / 2,0.0f);
	m_pVtx[2].pos = D3DXVECTOR3(-TextureWidth / 2,-TextureHeight / 2,0.0f);
	m_pVtx[3].pos = D3DXVECTOR3(TextureWidth / 2,-TextureHeight / 2,0.0f);

	//****�����̐ݒ�*****
	m_pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	m_pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	m_pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	m_pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	m_pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	m_pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	m_pVtx[1].tex = D3DXVECTOR2((1.0f / EXPLOSION_SEPARATE_NUM),0.0f);
	m_pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	m_pVtx[3].tex = D3DXVECTOR2((1.0f / EXPLOSION_SEPARATE_NUM),1.0f);

	m_VtxBuffer->Unlock();

	return S_OK;

}

//��-----------------------------------��
//CExplosion�̍X�V����
//��-----------------------------------��
void CExplosion::Update(void)
{
	//�����̔ԍ����Ƃ̎��Ԃ̌v�Z������
	m_CounterAnim++;

	//�E�ӈȏ�ɂȂ����玟�̃R�}�Ɉڂ�
	if(m_CounterAnim >= EXPLOSION_COUNT)
	{
		//���̏��ԂɈڂ�
		m_PatternAnim++;
		//�ŏ�����J�E���g����
		m_CounterAnim = 0;

		//�w�i�摜�̏��o�^
		m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

		//���_���̐ݒ�
		m_pVtx[0].tex = D3DXVECTOR2((1.0f / EXPLOSION_SEPARATE_NUM) * m_PatternAnim,0.0f);
		m_pVtx[1].tex = D3DXVECTOR2((1.0f / EXPLOSION_SEPARATE_NUM) * (m_PatternAnim + 1),0.0f);
		m_pVtx[2].tex = D3DXVECTOR2((1.0f / EXPLOSION_SEPARATE_NUM) * m_PatternAnim,1.0f);
		m_pVtx[3].tex = D3DXVECTOR2((1.0f / EXPLOSION_SEPARATE_NUM) * (m_PatternAnim + 1),1.0f);

		m_VtxBuffer->Unlock();

		//�Ō�܂ŕ\��������I���ɂ���
		if(m_PatternAnim >= EXPLOSION_SEPARATE_NUM)
		{
			Uninit();
		}

	}
}

//��----------------------------------��
//CSceneBillboard��	�N���G�C�g(�����t)
//TextureName:�e�N�X�`���̖��O
//PosX,PosY,PosZ:�e�N�X�`���̍��W
//TexWidth,TexHeight:�e�N�X�`���̃^�e���R�̒���
//��----------------------------------��
CExplosion *CExplosion::Create(LPCTSTR TextureName,float PosX,float PosY,float PosZ,float TexWidth,float TexHeight)
{
	CExplosion *pExplosion;
	pExplosion = new CExplosion;

	pExplosion->m_TextureName	 = TextureName;
	pExplosion->m_Pos			 = D3DXVECTOR3(PosX,PosY,PosZ);
	pExplosion->TextureWidth	 = TexWidth;
	pExplosion->TextureHeight	 = TexHeight;
	
	pExplosion->Init();

	return pExplosion;
}
