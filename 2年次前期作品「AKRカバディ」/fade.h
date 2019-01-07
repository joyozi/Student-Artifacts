//◇-------------------------------------------------------------------------◇
//
//	フェイドヘッダーファイル[fade.h]
//	AT12A271　当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _FADE_H_
#define _FADE_H_

typedef enum
{
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX
}FADE;


void InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(FADE fade);
FADE GetFade(void);
void SetFade_2(FADE fade,MODE modeNext);	//0924に作成　かぶったから_2

#define FADE_TIME	(0.01f)	//フェイドインフェイドアウトの時間

#endif