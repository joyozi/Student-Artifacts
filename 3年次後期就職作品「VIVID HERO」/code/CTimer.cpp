//��-------------------------------------------------------------------------��
//
//	File:CTimer�̃t�@�C��[CTimer.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CTimer.h"
#include "CManager.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��
int CTimer::m_Time = 0;

//��-----------------------------------��
//CTimer�̃R���X�g���N�^
//��-----------------------------------��
CTimer::CTimer(int nPriority) : CScore(nPriority)
{
	m_Type = CTYPE_TIMER;

	m_Time = 0;
	m_TimeCnt = 0;
}

//��-----------------------------------��
//CTimer�̃f�X�g���N�^
//��-----------------------------------��
CTimer::~CTimer()
{

}


//��-----------------------------------��
//CTimer�̍X�V����
//��-----------------------------------��
void CTimer::Update(void)
{

	//���Ԃ̌o�߂̌v�Z
	m_TimeCnt++;

	if(m_TimeCnt >= 60)
	{
		m_Time--;
		m_TimeCnt = 0;
	}



	int ScoreIreko[SCORE_KETA_MAX];					//0���珇�ɍŏ㌅�ڂ�����
	int keta;										//�}�C�i�X���錅������ϐ�
	int ketaCnt = 0;								//�X�R�A�̌v�Z�Ɏg���ϐ��B�����}�C�i�X����Ă���
	int kakkonum = 0;								//
	bool hantei = true;

	for(int nCnt = 0;nCnt < SCORE_KETA_NUM;nCnt++)
	{
		ScoreIreko[nCnt] = NULL;
	}

	ketaCnt = m_Time;

	//���_�̌����Ƃ̑��
	for(int ScoreCnt = 0;ScoreCnt < SCORE_KETA_NUM;ScoreCnt++)
	{
		keta = (int)(powl(10.0, SCORE_KETA_NUM - ScoreCnt-1));
			
		while(ketaCnt >= keta)
		{
			ScoreIreko[ SCORE_KETA_NUM - ScoreCnt-1]++;
			ketaCnt -= keta;
		}
	}



	D3DXVECTOR2 VtxTexture[4];

	//�\��������W�ƕ����̌v�Z�A�ݒ�
	for(int ScoreCnt = 0; ScoreCnt < SCORE_KETA_NUM;ScoreCnt++)
	{
		VtxTexture[0] = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1f,0.0f);
		VtxTexture[1] = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1f + 0.1f,0.0f);
		VtxTexture[2] = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1f,1.0f);
		VtxTexture[3] = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1f + 0.1f,1.0f);

		m_pNumber[ScoreCnt]->SetVertex_Tex(VtxTexture);
	}
}

//��----------------------------------��
//CTimer�̃N���G�C�g(�����t)
//TextureName:�e�N�X�`���̖��O
//SetTime : �Z�b�g���鎞��
//KeTaNum : ����
//Pos_Right : �X�R�A�̈�ԉE�̈ʒu
//TexWidth,TexHeight:�e�N�X�`���̃^�e���R�̒���
//��----------------------------------��
CTimer *CTimer::Create(LPCTSTR TextureName,int SetTime,int KetaNum,float Pos_Right,float TexWidth,float TexHeight)
{
	CTimer *pTimer;
	pTimer = new CTimer;

	pTimer->m_ScoreTextureName = TextureName;
	pTimer->m_Time = SetTime;

	pTimer->SCORE_KETA_NUM = KetaNum;
	pTimer->SCORE_POS_RIGHT = Pos_Right;
	pTimer->SCORE_POS_WIDTH = TexWidth;
	pTimer->SCORE_POS_HEIGHT = TexHeight;

	pTimer->Init();

	return pTimer;
}


//��----------------------------------��
//���Ԃ������Z���Ă����֐�
//��----------------------------------��
void CTimer::PlusTime(int time)
{
	m_Time += time;
}



