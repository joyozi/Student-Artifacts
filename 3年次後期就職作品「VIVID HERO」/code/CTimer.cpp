//◇-------------------------------------------------------------------------◇
//
//	File:CTimerのファイル[CTimer.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CTimer.h"
#include "CManager.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇
int CTimer::m_Time = 0;

//◇-----------------------------------◇
//CTimerのコンストラクタ
//◇-----------------------------------◇
CTimer::CTimer(int nPriority) : CScore(nPriority)
{
	m_Type = CTYPE_TIMER;

	m_Time = 0;
	m_TimeCnt = 0;
}

//◇-----------------------------------◇
//CTimerのデストラクタ
//◇-----------------------------------◇
CTimer::~CTimer()
{

}


//◇-----------------------------------◇
//CTimerの更新処理
//◇-----------------------------------◇
void CTimer::Update(void)
{

	//時間の経過の計算
	m_TimeCnt++;

	if(m_TimeCnt >= 60)
	{
		m_Time--;
		m_TimeCnt = 0;
	}



	int ScoreIreko[SCORE_KETA_MAX];					//0から順に最上桁目を入れる
	int keta;										//マイナスする桁を入れる変数
	int ketaCnt = 0;								//スコアの計算に使う変数。桁がマイナスされていく
	int kakkonum = 0;								//
	bool hantei = true;

	for(int nCnt = 0;nCnt < SCORE_KETA_NUM;nCnt++)
	{
		ScoreIreko[nCnt] = NULL;
	}

	ketaCnt = m_Time;

	//得点の桁ごとの代入
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

//◇----------------------------------◇
//CTimerのクリエイト(引数付)
//TextureName:テクスチャの名前
//SetTime : セットする時間
//KeTaNum : 桁数
//Pos_Right : スコアの一番右の位置
//TexWidth,TexHeight:テクスチャのタテヨコの長さ
//◇----------------------------------◇
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


//◇----------------------------------◇
//時間を加減算していく関数
//◇----------------------------------◇
void CTimer::PlusTime(int time)
{
	m_Time += time;
}



