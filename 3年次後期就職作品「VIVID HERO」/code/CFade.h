//◇-------------------------------------------------------------------------◇
//
//	File:CFadeのヘッダーファイル[CFade.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CFADE_H_
#define _CFADE_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CScene2D.h"
#include "input.h"

//◇-----------------------------------◇
//
//◇-----------------------------------◇
typedef enum
{
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX
}FADE;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CFade : public CScene2D
{
public:
	CFade(int nPriority = PRIORITY_NUM - 1);
	virtual void Update(void);
	FADE GetFade(void);

	static CFade *Create(FADE Fade,D3DXCOLOR col,int FadeTime);

private:
	FADE	m_FadeType;
	int		m_FadeTime;
};



#endif
