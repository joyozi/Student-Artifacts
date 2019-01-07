
//◇-------------------------------------------------------------------------◇
//
//	File:デバッグロックのファイル[CDebugProc.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CDebugProc.h"
#include<vector>

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇
LPD3DXFONT CDebugProc::m_D3DXFont = NULL;
char CDebugProc::m_aStr[] = {NULL};

std::string g_strMoji;

//◇-----------------------------------◇
//デバッグロックのコンストラクタ
//◇-----------------------------------◇
CDebugProc::CDebugProc()
{

}

//◇-----------------------------------◇
//デバッグロックのデストラクタ
//◇-----------------------------------◇
CDebugProc::~CDebugProc()
{

}

//◇-----------------------------------◇
//デバッグロックの初期化処理
//◇-----------------------------------◇
HRESULT CDebugProc::Init(void)
{
#ifndef _DEBUG_

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	
	D3DXCreateFont(pDevice,18,0,FW_ULTRALIGHT,NULL,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"Terminal",&m_D3DXFont);
	
#endif
	return S_OK;
}

//◇-----------------------------------◇
//デバッグロックの終了処理
//◇-----------------------------------◇
void CDebugProc::Uninit(void)
{
	if(m_D3DXFont != NULL)
	{
		m_D3DXFont -> Release();
		m_D3DXFont = NULL;
	}
}

//◇-----------------------------------◇
//デバッグロックの更新処理
//◇-----------------------------------◇
void CDebugProc::Update(void)
{

}

//◇-----------------------------------◇
//デバッグロックの描画処理
//◇-----------------------------------◇
void CDebugProc::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

#ifdef _DEBUG
	RECT rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

	//テキストの描画
	m_D3DXFont->DrawText(NULL,g_strMoji.c_str(),-1,&rect,DT_LEFT,D3DCOLOR_RGBA(255,255,255,255));
#endif

	std::string a;
	g_strMoji = a;
}

//◇-----------------------------------◇
//デバッグロックのプリント処理
//
//fmt : 表示したい文字、変換文字など
//%dで数値は9桁までしか表示できません
//
//◇-----------------------------------◇
void CDebugProc::Print(const char *fmt,...)
{
#ifdef _DEBUG

	//リストの開始
	va_list list;

	int i;
	char *cp;			//fmtを入れる

	double x_float;
	int x_int;
	char *c_char;

	char c[256];		//256文字までなら何とかできる

	va_start(list,fmt);

	//fmtの数分間をあける
	for(cp = (char *)fmt,i = 0;*cp != '\0';cp++,i++)
	{
		if(*cp == '%')
		{
			switch(*(cp + 1))
			{
			case 's':
				c_char = va_arg(list,char*);	//可変引数の文字を入れる
				g_strMoji += c_char;

				break;

			case 'd':
				x_int = va_arg(list,int);
				_itoa(x_int,c,10);

				g_strMoji += c;
				cp++;

				break;

			case 'f':
				x_float = va_arg(list,double);
				_gcvt(x_float,6,c);

				g_strMoji += c;
				cp++;

				break;
			}
		}
		else
		{
			g_strMoji += *cp;
		}
	}




	va_end(list);

#endif
}




