//◇-------------------------------------------------------------------------◇
//
//	File	:	joystickヘッダープログラム[joystick.h]
//	Auther	:	Ikezawa Shintaro
//
//◇-------------------------------------------------------------------------◇
#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include<Windows.h>
#include"d3dx9.h"

#define FPS_DIRECTX (60)

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

enum JoystickCrossKeyPov
{
	JCKP_UP = 0,
	JCKP_RIGHT_UP,
	JCKP_RIGHT,
	JCKP_RIGHT_DOWN,
	JCKP_DOWN,
	JCKP_LEFT_DOWN,
	JCKP_LEFT,
	JCKP_LEFT_UP,
	JCKP_MAX
};


enum JoystickCrossKey
{
	JCK_UP = 0,
	JCK_RIGHT_UP,
	JCK_RIGHT,
	JCK_RIGHT_DOWN,
	JCK_DOWN,
	JCK_LEFT_DOWN,
	JCK_LEFT,
	JCK_LEFT_UP,
	JCK_RUP,
	JCK_RRIGHT_UP,
	JCK_RRIGHT,
	JCK_RRIGHT_DOWN,
	JCK_RDOWN,
	JCK_RLEFT_DOWN,
	JCK_RLEFT,
	JCK_RLEFT_UP,
	JCK_MAX
};

enum JoyStickKey
{
	JS_X = 0,
	JS_A,
	JS_B,
	JS_Y,
	JS_LB,
	JS_RB,
	JS_LT,
	JS_RT,
	JS_BACK,
	JS_START,
	JS_L3,
	JS_R3,
	JS_MAX
};

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇
HRESULT InitJoystick(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
void UninitJoystick(void);	// 終了処理
void UpdateJoystick(void);	// 更新処理
bool GetJoystickPress(int nKey);	// プレス取得(0~127)
bool GetJoystickTrigger(int nKey);	// トリガー取得(0~127)
bool GetJoystickRelease(int nKey);	// リリース取得
bool GetJoystickRepeatTrigger(int nKey);	// リピートトリガー取得
bool GetJoystickRepeatPress(int nKey);		// リピートプレス取得

bool GetJoystickCrossPov(JoystickCrossKeyPov nKey);

bool GetJoystickCrossPress(JoystickCrossKey nKey);
bool GetJoystickCrossTrigger(JoystickCrossKey nKey);	// トリガー取得(0~127)
bool GetJoystickCrossRelease(JoystickCrossKey nKey);	// リリース取得
bool GetJoystickCrossRepeatTrigger(JoystickCrossKey nKey);	// リピートトリガー取得
bool GetJoystickCrossRepeatPress(JoystickCrossKey nKey);		// リピートプレス取得

float GetJoysticklX();
float GetJoysticklY();
float GetJoysticklZ();
float GetJoysticklRx();
float GetJoysticklRy();
float GetJoysticklRz();
float GetJoysticklARx();
float GetJoysticklARy();
float GetJoysticklARz();

float GetJoysticklFX();
float GetJoysticklFY();
float GetJoysticklFZ();

float GetJoysticklFRx();
float GetJoysticklFRy();
float GetJoysticklFRz();

#endif
//EOF