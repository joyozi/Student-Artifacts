//◇-------------------------------------------------------------------------◇
//
//	File:CScoreのファイル[CScore.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CScore.h"
#include "CManager.h"

class CScene2D;

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CScoreのコンストラクタ
//◇-----------------------------------◇
CScore::CScore(int nPriority):CScene(nPriority)
{
	m_Type = CTYPE_SCORE;

	//****位置、角度の初期化****
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_Score = 0;
	m_NowScore = 0;
}

//◇-----------------------------------◇
//CScoreのデストラクタ
//◇-----------------------------------◇
CScore::~CScore()
{

}

//◇-----------------------------------◇
//classnameの初期化処理
//◇-----------------------------------◇
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

//◇-----------------------------------◇
//classnameの終了処理
//◇-----------------------------------◇
void CScore::Uninit(void)
{

}


//◇-----------------------------------◇
//CScoreの更新処理
//◇-----------------------------------◇
void CScore::Update(void)
{
	int ScoreIreko[SCORE_KETA_MAX];						//0から順に最上桁目を入れる
	int keta;											//マイナスする桁を入れる変数
	int ketaCnt				= 0;						//スコアの計算に使う変数。桁がマイナスされていく
	int kakkonum			= 0;						//
	bool hantei				= true;

	//スコアが変化予定値と現在値の差がどれくらいあるかで１フレームで変わる値を変える
	const int ChangeLine[]			= {1,	15	,30,	50,	100,	150};
	const int LineNum				= sizeof(ChangeLine) / sizeof(int);			//ChangeLineの数
	const int ChangeNum[LineNum]	= {1,	2	,3,		5,	10,		30};		//ChangeLineと同じ数入れる

	//カンストの設定
	if(m_Score >= powl(10,SCORE_KETA_NUM))
	{
		m_Score = (int)powl(10,SCORE_KETA_NUM) - 1;
	}

	//スコアの加減算
	int ScoreDifference = m_Score - m_NowScore;

	if(ScoreDifference != 0)						//0値以外だったら
	{
		ScoreDifference = abs(ScoreDifference);		//計算しやすいように
		for(int i = LineNum - 1;i >= 0;i--)
		{
			if(ScoreDifference >= ChangeLine[i])	//定数以上だったらそれに属した値で加減算
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

	//得点の桁ごとの代入
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

	//表示する座標と文字の計算、設定
	for(int ScoreCnt = 0; ScoreCnt < SCORE_KETA_NUM;ScoreCnt++)
	{
		VtxTexture[0] = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1f,0.0f);
		VtxTexture[1] = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1f + 0.1f,0.0f);
		VtxTexture[2] = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1f,1.0f);
		VtxTexture[3] = D3DXVECTOR2(ScoreIreko[ScoreCnt] * 0.1f + 0.1f,1.0f);

		m_pNumber[ScoreCnt]->SetVertex_Tex(VtxTexture);
	}
}

//◇-----------------------------------◇
//classnameの描画処理
//◇-----------------------------------◇
void CScore::Draw(void)
{

}

//◇----------------------------------◇
//CScoreのセットポジションその１
//◇----------------------------------◇
void  CScore::SetPosition(float x,float y,float z)
{
	m_Pos = D3DXVECTOR3(x,y,z);
}

//◇----------------------------------◇
//CScoreのセットポジションその２
//◇----------------------------------◇
void  CScore::SetPosition(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//◇----------------------------------◇
//CScoreのゲットポジション
//◇----------------------------------◇
D3DXVECTOR3  CScore::GetPosition(void)
{
	return m_Pos;
}

//◇----------------------------------◇
//CScoreのセットローテーションその１
//◇----------------------------------◇
void CScore::SetRotation(float x,float y,float z)
{
	m_Rot = D3DXVECTOR3(x,y,z);
}

//◇----------------------------------◇
//CScoreのセットローテーションその2
//◇----------------------------------◇
void CScore::SetRotation(D3DXVECTOR3 rot)
{
	m_Rot = rot;
}

//◇----------------------------------◇
//CScoreのゲットローテーション
//◇----------------------------------◇
D3DXVECTOR3 CScore::GetRotation(void)
{
	return m_Rot;
}

//◇----------------------------------◇
//セットタイプ
//◇----------------------------------◇
void CScore::SetType(int nType)
{

}

//◇----------------------------------◇
//CScoreの	クリエイト(引数付)
//
//はじっこに設置しやすい作りです。とくにみぎうえ
//
//TextureName		 : テクスチャの名前
//KeTaNum			 : 桁数
//Pos_Up			 : スコアの一番上の位置
//Pos_Right			 : スコアの一番右の位置
//TexWidth,TexHeight : テクスチャのタテヨコの長さ 多分１文字のサイズのこと
//◇----------------------------------◇
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

//◇----------------------------------◇
//ポイントを加減算していく関数
//◇----------------------------------◇
void CScore::PlusScore(int score)
{
	m_Score += score;
}

//◇----------------------------------◇
//ポイントをリセットする
//◇----------------------------------◇
void CScore::ResetScore(int score)
{
	m_Score = score;
	m_NowScore = score;
}

