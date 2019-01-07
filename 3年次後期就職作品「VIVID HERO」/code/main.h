//◇-------------------------------------------------------------------------◇
//
//	File:真っ暗ウィンドウ[main.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#define DIRECTINPUT_VERSION (0x0800)	//エラー回避のため
#define _CRT_SECURE_NO_WARNINGS 1

//クリエイトテクスチャの中をのぞけるようにするマクロ定義
//覗き方：クリテクの前にブレポイントを置いて実行→のぞける?
#define D3D_DEBUG_INFO

//2重インクルード防止
#ifndef _MAIN_H_
#define _MAIN_H_

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)	{if(p){delete (p);(p) = NULL;}}
#endif

#ifndef SAFE_DELETE_ARRY
#define SAFE_DELETE_ARRY(p)	{if(p){delete[] (p);(p) = NULL;}}
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)	{if(p){(p)->Release();(p) = NULL;}}
#endif

//===================
//メモリリークのファイル
//===================
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include"dinput.h"
#include<windows.h>
#include "d3dx9.h"		//描画処理に必要
#include "xaudio2.h"	//XAudio2関連のファイル→サウンド再生に必要
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")			//描画処理に必要
#pragma comment(lib,"d3dx9.lib")		//上記の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")		//DirectXコンポーネントに必要
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")

//これを入れておいたら、DXTrace(？？？？？);を書くと何かのダイアログが出る
#pragma comment(lib,"dxerr.lib")
#include"dxerr.h"
//#pragma once
//まだ何かある
//◇-----------------------------------◇
//多分メモリリークの処理
//◇-----------------------------------◇
#ifndef _DEBUG_
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

//◇-----------------------------------◇
//マクロ定義
//◇-----------------------------------◇
#define SCREEN_WIDTH (1280)				//画面の幅
#define SCREEN_HEIGHT (720)				//画面の高さ

//◇-----------------------------------◇
//2Dの処理
//◇-----------------------------------◇
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
typedef struct
{
	D3DXVECTOR3		pos;		//頂点座標
	float			rhw;		//テクステャのパースペクティブコレクト用
	D3DCOLOR		col;		//頂点カラー
	D3DXVECTOR2		tex;		//テクスチャ座標
}VERTEX_2D;



//◇-----------------------------------◇
//3D処理の追加
//◇-----------------------------------◇
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

typedef struct
{
	D3DXVECTOR3		pos;
	D3DXVECTOR3		nor;
	D3DCOLOR		col;
	D3DXVECTOR2		tex;
}VERTEX_3D;

//◇-----------------------------------◇
//それぞれの物体のタイプ設定
//◇-----------------------------------◇
enum CLASS_TYPE
{
	CTYPE_NONE =0,
	CTYPE_SCENE,
	CTYPE_SCENE2D,
	CTYPE_SCENE3D,
	CTYPE_SCENEX,
	CTYPE_SCENEBILLBOARD,
	CTYPE_MESHSKY,
	CTYPE_BULLET,
	CTYPE_EXPLOSION,
	CTYPE_SCORE,
	CTYPE_TIMER,
	CTYPE_FADE,
	CTYPE_SCENEMODELMOTION,
	CTYPE_SCENEMODELPARTS,
	CTYPE_SCENESTENCILSHADOW,
	CTYPE_SCENEMESHORBIT,
	CTYPE_MESHBESISCLASS,
	CTYPE_PARTICLESYSTEM,
	CTYPE_DEGENERACYPOLYGON,
	CTYPE_DEGENERACYSTAR,

	CTYPE_PLAYERMODEL,
	CTYPE_BULLET000,
	CTYPE_BULLETHOMING,

	CTYPE_ENEMY,

	CTYPE_ENEMYBULLET000,
	CTYPE_ENEMYBULLET001,
	
	CTYPE_GAMESTART,

	CTYPE_MAX
};

//◇-----------------------------------◇
//デバイスを取得する関数
//◇-----------------------------------◇
LPDIRECT3DDEVICE9 GetDevice(void);

#endif