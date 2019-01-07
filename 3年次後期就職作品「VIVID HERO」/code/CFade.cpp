//◇-------------------------------------------------------------------------◇
//
//	File:CFadeのファイル[CFade.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CFade.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CFadeのコンストラクタ
//◇-----------------------------------◇
CFade::CFade(int nPriority) : CScene2D(nPriority)
{
	m_Type			 = CTYPE_FADE;
	m_FadeTime		 = 0;
	m_Color			 = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
	m_FadeType		 = FADE_NONE;
}

//◇-----------------------------------◇
//CFadeの更新処理
//◇-----------------------------------◇
void CFade::Update(void)
{
	//色情報のセット
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	//頂点情報の設定
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

//◇-----------------------------------◇
//ゲットフェイド処理
//◇-----------------------------------◇
FADE CFade::GetFade(void)
{
	return m_FadeType;
}

//◇-----------------------------------◇
//フェイドクリエイト処理
//col : 何色でのフェイドか
//FadeTime : 60で1秒。フェイドを何秒間するか
//◇-----------------------------------◇
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