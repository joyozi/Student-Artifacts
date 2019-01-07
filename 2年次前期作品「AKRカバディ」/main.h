//◇-------------------------------------------------------------------------◇
//
//	真っ暗ウィンドウ[main.h]
//	AT12A271　当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇

#define DIRECTINPUT_VERSION (0x0800)	//エラー回避のため

#ifndef _MAIN_H_
#define _MAIN_H_

#include"dinput.h"
#include<windows.h>
#include "d3dx9.h"		//描画処理に必要
#include "xaudio2.h"	//XAudio2関連のファイル→サウンド再生に必要
#include <time.h>
#include <stdlib.h>

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//上記の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	//DirectXコンポーネントに必要
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")

#define SCREEN_WIDTH (800)			//画面の幅
#define SCREEN_HEIGHT (800)			//画面の高さ
#define CLASS_NAME	"表示します"	//(ウィンドウクラスの名前)
#define WINDOW_NAME	"（学長　×　田中先生）　AKRカバディ！"		//(ウィンドウの名前)
//頂点のフォーマット
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define RESULT_END_TIME	(300)			//リザルト画面の制限時間


//上記のフォーマットに合わせた構造体
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//テクステャのパースペクティブコレクト用
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
}VERTEX_2D;

typedef enum
{
	MODE_TITTLE = 0,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
}MODE;

LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif	//勝手に追加