//◇-------------------------------------------------------------------------◇
//
//	ゲームカウントダウンヘッダーファイル[game_countdown.h]
//	AT12A271　当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _GAMECOUNTDOWN_H_
#define _GAMECOUNTDOWN_H_

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇
#define MAX_CNTDOWN_KETA		(3)						//スコアの最大桁数　これを増やしたらscore.cppの UpdateScoreのしたのScoreIrekoの０も増やしてください
#define POLYGON_CNTDOWN_NUM		(MAX_CNTDOWN_KETA * 4)	//表示する三角形ポリゴンの数
#define TYOUTEN_CNTDOWN_NUM		(MAX_CNTDOWN_KETA * 4)	//スコアの頂点の個数
#define DrawCountdownPosRight	(780)					//スコアの右端の位置
#define DrawCountdownPosHeight	(100)					//カウントダウンの縦の位置
#define DrawCountdownHeightW	(70)					//スコアの縦幅
#define DrawCountdownPosWidth	(30)					//一つのスコアの横幅
#define COUNTDOWN_TIME			(60)					//制限時間
#define CountdownChangeColor	(30)					//スコアがこの数値以上になると赤くなります
//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇
void InitCountdown(void);
void UninitCountdown(void);
void UpdateCountdown(void);
void DrawCountdown(void);

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇



#endif