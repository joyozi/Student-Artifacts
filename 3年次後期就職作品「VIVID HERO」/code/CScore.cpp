//��-------------------------------------------------------------------------��
//
//	File:CScore�̃t�@�C��[CScore.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CScore.h"
#include "CManager.h"

class CScene2D;

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CScore�̃R���X�g���N�^
//��-----------------------------------��
CScore::CScore(int nPriority):CScene(nPriority)
{
	m_Type = CTYPE_SCORE;

	//****�ʒu�A�p�x�̏�����****
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_Score = 0;
	m_NowScore = 0;
}

//��-----------------------------------��
//CScore�̃f�X�g���N�^
//��-----------------------------------��
CScore::~CScore()
{

}

//��-----------------------------------��
//classname�̏���������
//��-----------------------------------��
HRESULT CScore::Init(void)
{
	
	for(int i = 0;i < SCORE_KETA_NUM;i++)
	{
		m_pNumber[i] = CScene2D::Create(100,m_ScoreTextureName,
										D3DXVECTOR3(SCORE_POS_RIGHT - (SCORE_POS_WIDTH * i) - (SCORE_POS_WIDTH / 2),
										SCORE_POS_UP + SCORE_POS_HEIGHT / 2,
										0.0f),
										D3DXVECTOR3(SCORE_POS_WIDTH,
										SCORE_POS_HEIGHT,0.0f)
										);
	}

	return S_OK;
}

//��-----------------------------------��
//classname�̏I������
//��-----------------------------------��
void CScore::Uninit(void)
{

}


//��-----------------------------------��
//CScore�̍X�V����
//��-----------------------------------��
void CScore::Update(void)
{
	int ScoreIreko[SCORE_KETA_MAX];						//0���珇�ɍŏ㌅�ڂ�����
	int keta;											//�}�C�i�X���錅������ϐ�
	int ketaCnt				= 0;						//�X�R�A�̌v�Z�Ɏg���ϐ��B�����}�C�i�X����Ă���
	int kakkonum			= 0;						//
	bool hantei				= true;

	//�X�R�A���ω��\��l�ƌ��ݒl�̍����ǂꂭ�炢���邩�łP�t���[���ŕς��l��ς���
	const int ChangeLine[]			= {1,	15	,30,	50,	100,	150};
	const int LineNum				= sizeof(ChangeLine) / sizeof(int);			//ChangeLine�̐�
	const int ChangeNum[LineNum]	= {1,	2	,3,		5,	10,		30};		//ChangeLine�Ɠ����������

	//�J���X�g�̐ݒ�
	if(m_Score >= powl(10,SCORE_KETA_NUM))
	{
		m_Score = (int)powl(10,SCORE_KETA_NUM) - 1;
	}

	//�X�R�A�̉����Z
	int ScoreDifference = m_Score - m_NowScore;

	if(ScoreDifference != 0)						//0�l�ȊO��������
	{
		ScoreDifference = abs(ScoreDifference);		//�v�Z���₷���悤��
		for(int i = LineNum - 1;i >= 0;i--)
		{
			if(ScoreDifference >= ChangeLine[i])	//�萔�ȏゾ�����炻��ɑ������l�ŉ����Z
			{
				if(m_Score - m_NowScore > 0)
				{
					m_NowScore += ChangeNum[i];
				}
				else
				{
					m_NowScore -= ChangeNum[i];
				}
				break;
			}
		}
	}

	for(int nCnt = 0;nCnt < SCORE_KETA_NUM;nCnt++)
	{
		ScoreIreko[nCnt] = 0;
	}
	
	ketaCnt = m_NowScore;

	//���_�̌����Ƃ̑��
	for(int ScoreCnt = 0;ScoreCnt < SCORE_KETA_NUM;ScoreCnt++)
	{
		keta = (int)(powl(10, SCORE_KETA_NUM - ScoreCnt-1));
			
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

//��-----------------------------------��
//classname�̕`�揈��
//��-----------------------------------��
void CScore::Draw(void)
{

}

//��----------------------------------��
//CScore�̃Z�b�g�|�W�V�������̂P
//��----------------------------------��
void  CScore::SetPosition(float x,float y,float z)
{
	m_Pos = D3DXVECTOR3(x,y,z);
}

//��----------------------------------��
//CScore�̃Z�b�g�|�W�V�������̂Q
//��----------------------------------��
void  CScore::SetPosition(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//��----------------------------------��
//CScore�̃Q�b�g�|�W�V����
//��----------------------------------��
D3DXVECTOR3  CScore::GetPosition(void)
{
	return m_Pos;
}

//��----------------------------------��
//CScore�̃Z�b�g���[�e�[�V�������̂P
//��----------------------------------��
void CScore::SetRotation(float x,float y,float z)
{
	m_Rot = D3DXVECTOR3(x,y,z);
}

//��----------------------------------��
//CScore�̃Z�b�g���[�e�[�V��������2
//��----------------------------------��
void CScore::SetRotation(D3DXVECTOR3 rot)
{
	m_Rot = rot;
}

//��----------------------------------��
//CScore�̃Q�b�g���[�e�[�V����
//��----------------------------------��
D3DXVECTOR3 CScore::GetRotation(void)
{
	return m_Rot;
}

//��----------------------------------��
//�Z�b�g�^�C�v
//��----------------------------------��
void CScore::SetType(int nType)
{

}

//��----------------------------------��
//CScore��	�N���G�C�g(�����t)
//
//�͂������ɐݒu���₷�����ł��B�Ƃ��ɂ݂�����
//
//TextureName		 : �e�N�X�`���̖��O
//KeTaNum			 : ����
//Pos_Up			 : �X�R�A�̈�ԏ�̈ʒu
//Pos_Right			 : �X�R�A�̈�ԉE�̈ʒu
//TexWidth,TexHeight : �e�N�X�`���̃^�e���R�̒��� �����P�����̃T�C�Y�̂���
//��----------------------------------��
CScore *CScore::Create(LPCTSTR TextureName,int KetaNum,float Pos_Right,float Pos_Up,float TexWidth,float TexHeight,int StartScore)
{
	CScore *pScore;
	pScore = new CScore;

	pScore->m_ScoreTextureName = TextureName;

	pScore->SCORE_KETA_NUM = KetaNum;
	pScore->SCORE_POS_RIGHT = Pos_Right;
	pScore->SCORE_POS_UP = Pos_Up;

	pScore->SCORE_POS_WIDTH = TexWidth;
	pScore->SCORE_POS_HEIGHT = TexHeight;

	pScore->m_Score = StartScore;
	pScore->m_NowScore = StartScore;

	pScore->Init();

	return pScore;
}

//��----------------------------------��
//�|�C���g�������Z���Ă����֐�
//��----------------------------------��
void CScore::PlusScore(int score)
{
	m_Score += score;
}

//��----------------------------------��
//�|�C���g�����Z�b�g����
//��----------------------------------��
void CScore::ResetScore(int score)
{
	m_Score = score;
	m_NowScore = score;
}

