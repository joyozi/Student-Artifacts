//◇-------------------------------------------------------------------------◇
//
//	スコアhファイル[score.h]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇
#ifndef _SCORE_H_
#define _SCORE_H_

#define POLYGON_sNUM	(MAX_SCORE_KETA * 4)	//表示する三角形ポリゴンの数
#define TYOUTEN_sNUM	(MAX_SCORE_KETA * 4)	//スコアの頂点の個数
#define DrawScorePosRight (1200)					//スコアの左端の位置
#define DrawScorePosHeight (70)					//スコアの縦幅
#define DrawScorePosWidth  (30)					//一つのスコアの横幅
#define MAX_SCORE_KETA	   (5)					//スコアの最大桁数

void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void PlusScore(int score);

#endif _SCORE_H_