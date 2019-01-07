//◇-------------------------------------------------------------------------◇
//
//	真っ暗ウィンドウ[main.h]
//	AT12A271　当摩好弘
//
//◇-------------------------------------------------------------------------◇

#define DIRECTINPUT_VERSION (0x0800)	//エラー回避のため

#ifndef _MAIN_H_
#define _MAIN_H_
#include<windows.h>

#include "d3dx9.h"	//描画処理に必要

#include"dinput.h"
#include<windows.h>
#include "d3dx9.h"		//描画処理に必要
#include "xaudio2.h"	//XAudio2関連のファイル→サウンド再生に必要
#include <time.h>
#include <stdlib.h>

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")			//描画処理に必要
#pragma comment(lib,"d3dx9.lib")		//上記の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")		//DirectXコンポーネントに必要
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")

#define SCREEN_WIDTH (1200)				//画面の幅
#define SCREEN_HEIGHT (760)				//画面の高さ
#define RESULT_END_TIME	(300)			//リザルト画面の制限時間

#define SCREEN_CHANGE (TRUE)			//ウィンドウ、フルスクリーンのチェンジ

LPDIRECT3DDEVICE9 GetDevice(void);

//*** 2Dの処理 ***
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//テクステャのパースペクティブコレクト用
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
}VERTEX_2D;


/*** 3D処理の追加 ***/
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR    col;
	D3DXVECTOR2 tex;
}VERTEX_3D;

//===================モードの設定=======================
typedef enum
{
	MODE_TITTLE = 0,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
}MODE;

void SetMode(MODE mode);
MODE GetMode(void);
//======================================================

//プレイヤーの状態を保存する構造体
typedef struct
{
	D3DXVECTOR3 MOTO_pos;		//バレットを発射した時のプレイヤーの位置。あたり判定のときに使う
	bool Jump_Judge;			//ジャンプしてるか否かの判定
	int LR_Judge;				//左右に傾いてるかの判定　1が左　2が真ん中　3が右に傾いてる
	int GUN_under;				//腕の状態を保存する 1で腕を上にあげている状態　2で腕を下におろしている状態　3で
	bool Thing_exist;			//物体が存在するかどうか。 trueで表示する
	int Model_Muteki;			//モデルの無敵状態について　1、通常状態　２、ダメージを受けてひるんでる状態　３、無敵状態　弾を撃てる
	int Enemy_Damage;			//てきのHP。0になると消滅する
}PLAYER_MODE;


#endif 	//勝手に追加