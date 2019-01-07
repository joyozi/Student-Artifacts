//◇-------------------------------------------------------------------------◇
//
//	ゲームcppファイル[game.cpp]
//	AT12A271　当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "game.h"
#include "GameBG.h"
#include "GamePlayer.h"
#include "input.h"
#include "enemy.h"
#include "fade.h"
#include "Game_Countdown.h"
#include "score.h"
#include "pause.h"
#include "gakutyou.h"
#include "explosion.h"
#include "sound.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
bool g_bPause = false;		//trueのときポーズ

float musicTime;

//◇-------------------------------------------------------------------------◇
//ゲーム初期化処理
//◇-------------------------------------------------------------------------◇
void InitGame(void)
{
	g_bPause = false;

	musicTime = 0;

	InitGameBG();			//ゲームの背景の初期化処理
	InitGamePolygon();		//ゲームのポリゴン初期化処理
	InitMasaru();
	InitEnemy();
	InitExplosion();
	InitScore();			//スコアの初期化処理
	InitCountdown();
	InitPause();

	PlaySound(SOUND_LABEL_GAME_MAIN);
}

//◇---------------------------------◇
//ゲームの終了処理
//◇---------------------------------◇
void UninitGame(void)
{
	//QUITで終了したらポーズメニューを終了させる
	g_bPause = false;

	StopSound(SOUND_LABEL_GAME_MAIN);

	UninitGameBG();			//ゲームの背景の終了処理
	UninitGamePolygon();	//ゲームのポリゴン終了処理
	UninitMasaru();
	UninitEnemy();
	UninitExplosion();
//	UninitScore();			//スコアの終了処理  RESULTでするからいらない
	UninitCountdown();
	UninitPause();
}
//◇---------------------------------◇
//ゲームの更新処理
//◇---------------------------------◇
void UpdateGame(void)
{
	//やっつけミュージックループ
	musicTime+=1.0f;
	if(musicTime >= 60.0f*60.3f)
	{
		StopSound(SOUND_LABEL_GAME_MAIN);
		PlaySound(SOUND_LABEL_GAME_MAIN);

		musicTime = 0.0f;
	}


	//ポーズ処理
	if(GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause?false : true;
		//ポーズメニューの選択肢を元に戻す
	}

	if(g_bPause == true)
	{
		UpdatePause();
	}
	else
	{
		//カウントダウンはフェイドインが終了してから始めてもらいます
		if(GetFade() == FADE_NONE)
		{
			UpdateCountdown();	//カウントダウン処理
		}

		UpdateGameBG();			//ゲームの背景の更新処理
		UpdateMasaru();
		UpdateGamePolygon();	//ゲームのポリゴン更新処理
		UpdateEnemy();
		UpdateExplosion();
		UpdateScore();			//スコアアップデート
	
	}
}

//◇---------------------------------◇
//ゲームの描画処理
//◇---------------------------------◇
void DrawGame(void)
{
	DrawGameBG();			//ゲームの背景の描画処理
	DrawCountdown();		//カウントダウンの描画処理
	DrawMasaru();
	DrawGamePolygon();		//ゲームのポリゴン描画処理
	DrawExplosion();
	DrawScore();			//スコアの描画処理
	DrawEnemy();

	if(g_bPause == true)
	{
		DrawPause();
	}
}

//◇---------------------------------◇
//ポーズ処理
//◇---------------------------------◇
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

bool GetPause(void)
{
	return g_bPause;
}