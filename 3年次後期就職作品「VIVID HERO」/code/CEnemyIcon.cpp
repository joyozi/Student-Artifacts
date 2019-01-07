//��-------------------------------------------------------------------------��
//
//	File:CEnemyIcon�̃t�@�C��[CEnemyIcon.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CEnemyIcon.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CEnemyIcon�̃R���X�g���N�^
//��-----------------------------------��
CEnemyIcon::CEnemyIcon(int nPriority) : CScene2D(nPriority)
{
	m_DrawJudge = false;
}

//��-----------------------------------��
//CEnemyIcon�̃f�X�g���N�^
//��-----------------------------------��
CEnemyIcon::~CEnemyIcon()
{

}

//��-----------------------------------��
//CEnemyIcon�̕`�揈��
//��-----------------------------------��
void CEnemyIcon::Draw(void)
{
	if(m_DrawJudge)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = GetDevice();

		//�w�i�̕`��
		pDevice->SetStreamSource(0,m_VtxBuffer,0,sizeof(VERTEX_2D));
		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0,m_Texture);
		//�e�N�X�`���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	}
}

CEnemyIcon *CEnemyIcon::Create(LPCTSTR TextureName,D3DXVECTOR3 Pos,D3DXVECTOR3 Size)
{
	CEnemyIcon *pEnemyIcon;
	pEnemyIcon = new CEnemyIcon;

	pEnemyIcon->m_TextureName = TextureName;
	pEnemyIcon->m_Pos = Pos;
	pEnemyIcon->TextureWidth = Size.x;
	pEnemyIcon->TextureHeight = Size.y;
	
	pEnemyIcon->Init();

	return pEnemyIcon;

}
