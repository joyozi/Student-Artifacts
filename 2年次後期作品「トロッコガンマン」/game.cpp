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
#include "input.h"
#include "fade.h"
#include "pause.h"
#include "box.h"

#include "field.h"
#include "model.h"
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "billboard.h"
#include "shadow.h"
#include "meshsky.h"
#include "meshcave.h"
#include "obstacle.h"
#include "model_rail.h"
#include "bullet.h"
#include "gameUI.h"
#include "explosion.h"
#include "taimatsu.h"
#include "enemy_01.h"
#include "barricade.h"

#include "sound.h"
#include "score.h"
#include "UI_modelpos.h"

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

//◇-------------------------------------------------------------------------◇
//ゲーム初期化処理
//◇-------------------------------------------------------------------------◇
void InitGame(void)
{
	PlaySound(SOUND_LABEL_GAMEBGM);

	g_bPause = false;

	InitLight();
	InitCamera();
	InitPause();

	InitObstacle();

	InitModel();
	InitRail();
	InitTaimatsu();
	InitEnemy01();

	InitBullet();
	InitExplosion();

	InitBarricade();

	InitMeshfield();
	InitMeshCave();
	InitBox();

	InitGameUI();
	InitUI_modelpos();
	InitScore();
}

//◇---------------------------------◇
//ゲームの終了処理
//◇---------------------------------◇
void UninitGame(void)
{
	//QUITで終了したらポーズメニューを終了させる
	g_bPause = false;


	UninitLight();
	UninitCamera();
	UninitPause();

	UninitObstacle();

	UninitModel();
	UninitRail();
	UninitTaimatsu();
	UninitEnemy01();

	UninitBullet();	
	UninitExplosion();

	UninitBarricade();

	UninitMeshfield();
	UninitMeshCave();
	UninitBox();
	
	UninitGameUI();
	UninitUI_modelpos();
	UninitScore();

	StopSound(SOUND_LABEL_GAMEBGM);
}
//◇---------------------------------◇
//ゲームの更新処理
//◇---------------------------------◇
void UpdateGame(void)
{
	if(GetFade() == FADE_NONE)
	{
		//ポーズ処理
		if(GetKeyboardTrigger(DIK_P) == true)
		{
			g_bPause = g_bPause?false : true;
			//ポーズメニューの選択肢を元に戻す
		}
	}

	if(g_bPause == true)
	{
		UpdatePause();
	}
	else
	{
		UpdateLight();
		UpdateCamera();

		UpdateObstacle();

		UpdateModel();
		UpdateRail();
		UpdateTaimatsu();
		UpdateEnemy01();

		UpdateBullet();
		UpdateExplosion();

		UpdateBarricade();
		UpdateBox();

		UpdateMeshfield();
		UpdateMeshCave();

		BULLET_HITJUDGE();
		ModelHITJUDGE();

		UpdateGameUI();
		UpdateUI_modelpos();
		UpdateScore();
	}

}

//◇---------------------------------◇
//ゲームの描画処理
//◇---------------------------------◇
void DrawGame(void)
{
	DrawLight();
	SetCamera();

	DrawObstacle();
	DrawModel();
	DrawRail();
	DrawTaimatsu();
	DrawEnemy01();

	DrawBullet();
	DrawExplosion();
	
	DrawBarricade();

	DrawMeshfield();
	DrawMeshCave();
//	DrawBox();

	DrawGameUI();
	DrawUI_modelpos();
	DrawScore();

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
