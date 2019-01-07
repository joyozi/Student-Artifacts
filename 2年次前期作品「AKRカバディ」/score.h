//◇-------------------------------------------------------------------------◇
//
//	スコアhファイル[score.h]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇
#ifndef _SCORE_H_
#define _SCORE_H_

#define MAX_SCORE_KETA		(3)						//スコアの最大桁数　これを増やしたらscore.cppの UpdateScoreのしたのScoreIrekoの０も増やしてください
#define POLYGON_sNUM		(MAX_SCORE_KETA * 4)	//表示する三角形ポリゴンの数
#define TYOUTEN_sNUM		(MAX_SCORE_KETA * 4)	//スコアの頂点の個数
#define DrawScorePosRight	(780)					//スコアの左端の位置
#define DrawScorePosHeight	(70)					//スコアの縦幅
#define DrawScorePosWidth	(30)					//一つのスコアの横幅
#define PlusScore			(10)					//加算する量
#define MinusScore			(10)					//減算する量
#define ScoreChangeColor	(500)					//スコアがこの数値以上になると赤くなります

void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void GetScore(void);

#endif _SCORE_H_