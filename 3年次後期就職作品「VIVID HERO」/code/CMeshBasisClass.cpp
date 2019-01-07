//��-------------------------------------------------------------------------��
//
//	File:CMeshBasisClass�̃t�@�C��[CMeshBasisClass.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CMeshBasisClass.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CMeshBasisClass�̃R���X�g���N�^
//��-----------------------------------��
CMeshBasisClass::CMeshBasisClass(int nPriority) : CScene3D(nPriority)
{
	m_Type = CTYPE_MESHBESISCLASS;

	m_IdxBuffer = NULL;

	m_VtxNum = 0;
	m_IndexNum = 0;
	m_PolygonNum = 0;
}

//��-----------------------------------��
//CMeshBasisClass�̃f�X�g���N�^
//��-----------------------------------��
CMeshBasisClass::~CMeshBasisClass()
{

}

//��-----------------------------------��
//CMeshBasisClass�̏I������
//��-----------------------------------��
void CMeshBasisClass::Uninit(void)
{
	Release();

	//�o�b�t�@�̏���
	if(m_VtxBuffer != NULL)
	{
		m_VtxBuffer->Release();
		m_VtxBuffer = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̃����[�X
	if(m_IdxBuffer != NULL)
	{
		m_IdxBuffer->Release();
		m_IdxBuffer = NULL;
	}
}

//��-----------------------------------��
//CMeshBasisClass�̕`�揈��
//��-----------------------------------��
void CMeshBasisClass::Draw(void)
{
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

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


