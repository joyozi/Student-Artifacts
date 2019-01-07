//��-------------------------------------------------------------------------��
//
//	File:CFade�̃t�@�C��[CFade.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CFade.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CFade�̃R���X�g���N�^
//��-----------------------------------��
CFade::CFade(int nPriority) : CScene2D(nPriority)
{
	m_Type			 = CTYPE_FADE;
	m_FadeTime		 = 0;
	m_Color			 = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
	m_FadeType		 = FADE_NONE;
}

//��-----------------------------------��
//CFade�̍X�V����
//��-----------------------------------��
void CFade::Update(void)
{
	//�F���̃Z�b�g
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	//���_���̐ݒ�
	m_pVtx[0].col = D3DXCOLOR(m_Color.r,m_Color.g,m_Color.b,m_Color.a);
	m_pVtx[1].col = D3DXCOLOR(m_Color.r,m_Color.g,m_Color.b,m_Color.a);
	m_pVtx[2].col = D3DXCOLOR(m_Color.r,m_Color.g,m_Color.b,m_Color.a);
	m_pVtx[3].col = D3DXCOLOR(m_Color.r,m_Color.g,m_Color.b,m_Color.a);

	m_VtxBuffer->Unlock();

	switch(m_FadeType)
	{
	case FADE_NONE:
		break;

	case FADE_IN:
		m_Color.a -= 1.0f / m_FadeTime;

		if(m_Color.a <= 0.0f)
		{
			m_FadeType = FADE_NONE;
		}
		break;

	case FADE_OUT:
		m_Color.a += 1.0f / m_FadeTime;

		if(m_Color.a >= 1.0f)
		{
			m_FadeType = FADE_NONE;
		}
		break;
	}
}

//��-----------------------------------��
//�Q�b�g�t�F�C�h����
//��-----------------------------------��
FADE CFade::GetFade(void)
{
	return m_FadeType;
}

//��-----------------------------------��
//�t�F�C�h�N���G�C�g����
//col : ���F�ł̃t�F�C�h��
//FadeTime : 60��1�b�B�t�F�C�h�����b�Ԃ��邩
//��-----------------------------------��
CFade *CFade::Create(FADE Fade,D3DXCOLOR col,int FadeTime)
{
	CFade *pFade;
	pFade = new CFade;

	pFade->m_FadeTime		 = FadeTime;
	pFade->m_Color			 = col;
	pFade->m_FadeType		 = Fade;
	pFade->m_Pos			 = D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f);
	pFade->TextureWidth		 = SCREEN_WIDTH;
	pFade->TextureHeight	 = SCREEN_HEIGHT;

	pFade->Init();

	return pFade;
}