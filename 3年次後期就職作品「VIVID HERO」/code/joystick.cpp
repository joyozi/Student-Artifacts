//◇-------------------------------------------------------------------------◇
//
//	File	:	ジョイスティック入力処理プログラム[joystick.cpp]
//	Auther	:	Ikezawa Shintaro
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
///	インクルードファイル
//◇-------------------------------------------------------------------------◇
#include"joystick.h"
#include"main.h"

//◇-------------------------------------------------------------------------◇
//	マクロ定義
//◇-------------------------------------------------------------------------◇
#define REPEAT_INTERVAL		(200)	// リピート間隔時間[ms]
#define REPEAT_START_TIME	(400)	// リピート開始までの待ち時間[ms]

//◇-------------------------------------------------------------------------◇
//	プロトタイプ宣言
//◇-------------------------------------------------------------------------◇
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);

//◇-------------------------------------------------------------------------◇
//	グローバル変数宣言
//◇-------------------------------------------------------------------------◇
LPDIRECTINPUT8 g_pDInputJoystick = NULL;	// インプットオブジェクト
LPDIRECTINPUTDEVICE8 g_pDIDevJoystick = NULL;	// インプットデバイス(キーボード)
DIDEVCAPS             g_diDevCaps;          // ジョイスティックの能力

BYTE g_aJoystickButton[128];		// プレス状態
BYTE g_aJoystickButtonTrigger[128];	// トリガー状態
BYTE g_aJoystickButtonRelease[128];	// リリース状態	
BYTE g_aJoystickButtonRepeatTrigger[128];	// リピートトリガー状態
BYTE g_aJoystickButtonRepeatPress[128];	// リピートプレス状態
unsigned int g_aJoystickButtonRepeatCount[128];	// リピート制御用

BYTE g_aJoystickCross[JCK_MAX];
BYTE g_aJoystickCrossTrigger[JCK_MAX];	// トリガー状態
BYTE g_aJoystickCrossRelease[JCK_MAX];	// リリース状態	
BYTE g_aJoystickCrossRepeatTrigger[JCK_MAX];	// リピートトリガー状態
BYTE g_aJoystickCrossRepeatPress[JCK_MAX];	// リピートプレス状態
unsigned int g_aJoystickCrossRepeatCount[JCK_MAX];	// リピート制御用

DIJOYSTATE2 g_JoyState;

BYTE g_aJoystickCrossKeyPov[JCKP_MAX];

//◇----------------------------------◇
//	キーボード入力の初期化関数
//◇----------------------------------◇
HRESULT InitJoystick(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;	// エラー確認用

	if(g_pDInputJoystick == NULL)	// まだ、作られていないなら作る
	{
		// DirectInputオブジェクト生成
		hr = DirectInput8Create( hInstance,
								DIRECTINPUT_VERSION,
								IID_IDirectInput8,
								(void**)&g_pDInputJoystick,
								NULL);
		// エラーチェック
		if(FAILED(hr))
		{
			MessageBox(hWnd,"DirectInput8の生成に失敗しました。","エラー通知", MB_OK);
			return hr;
		}

	}

	// デバイスを列挙して作成(InputDeviceの作成)
	hr = g_pDInputJoystick->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback,
										NULL, DIEDFL_ATTACHEDONLY);
	
	// エラーチェック
	if(FAILED(hr))
	{
		MessageBox(hWnd,"ジョイスティックの生成に失敗しました。","エラー通知", MB_OK);
		return hr;
	}

	if(g_pDIDevJoystick == NULL)
	{
		return E_FAIL;
	}

	// データフォーマット指定
	hr = g_pDIDevJoystick->SetDataFormat(&c_dfDIJoystick2);

	// エラーチェック
	if(FAILED(hr))
	{
		MessageBox(hWnd,"データフォーマット指定(ジョイスティック)に失敗しました。","エラー通知", MB_OK);
		return hr;
	}

	// セットコーオペレイティブレベル指定( 協調モードを設定（フォアグラウンド＆非排他モード）)
	hr = g_pDIDevJoystick->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	// エラーチェック
	if(FAILED(hr))
	{
		MessageBox(hWnd,"セットコーオペレイティブレベル指定(ジョイスティック)に失敗しました。","エラー通知", MB_OK);
		return hr;
	}

	 // コールバック関数を使って各軸のモードを設定
	hr = g_pDIDevJoystick->EnumObjects(EnumAxesCallback, NULL, DIDFT_AXIS);
	if (FAILED(hr))
	{
		MessageBox(NULL,"軸モードの設定に失敗","Direct Input Error",MB_OK);
		return hr;
	}

	g_pDIDevJoystick->Acquire();	// ジョイスティックへのアクセス権の獲得(入力制御開始)

	return S_OK;
}

//◇----------------------------------◇
//	キーボード入力の終了関数
//◇----------------------------------◇
void UninitJoystick(void)
{
	if(g_pDIDevJoystick != NULL)
	{
		g_pDIDevJoystick->Unacquire();	// キーボードへのアクセス権を破棄(入力制御終了)
	}


	// 入力デバイス(キーボードの破棄)
	if(g_pDIDevJoystick != NULL)
	{
		g_pDIDevJoystick->Release();	// 解放処理

		g_pDIDevJoystick = NULL;		// NULLで初期化
	}

	// InputDeviceの破棄
	if(g_pDInputJoystick != NULL)
	{
		g_pDInputJoystick->Release();	// 解放処理

		g_pDInputJoystick = NULL;		// NULLで初期化
	}

}

//◇----------------------------------◇
//	ジョイスティックを列挙する CALLBACK 関数
// 使用するデバイスが見つかれば g_pDIDev に設定して、DIENUM_STOP をリターン
//◇----------------------------------◇
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	HRESULT hr;

	// 列挙されたジョイスティックへのインターフェイスを取得する。
	hr = g_pDInputJoystick->CreateDevice(pdidInstance->guidInstance, &g_pDIDevJoystick, NULL);
	if (FAILED(hr))     return DIENUM_CONTINUE;
	// ジョイスティックの能力を調べる
	g_diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hr = g_pDIDevJoystick->GetCapabilities(&g_diDevCaps);
	if (FAILED(hr))
	{// ジョイスティック能力の取得に失敗
		SAFE_RELEASE(g_pDIDevJoystick);
		return DIENUM_CONTINUE;
	}

	return DIENUM_STOP;
}

//◇----------------------------------◇
//	ジョイスティックの軸を列挙する CALLBACK 関数
//◇----------------------------------◇
// 最小値を -1000 に、最大値を +1000 に設定
BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	HRESULT hr;

	// 軸の値の範囲を設定（-1000～1000）
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize       = sizeof(diprg); 
	diprg.diph.dwHeaderSize = sizeof(diprg.diph); 
	diprg.diph.dwObj        = lpddoi->dwType;
	diprg.diph.dwHow        = DIPH_BYID;
	diprg.lMin  = -1000;
	diprg.lMax  = +1000;
	hr = g_pDIDevJoystick->SetProperty(DIPROP_RANGE, &diprg.diph);
	if (FAILED(hr))     return DIENUM_STOP;
	return DIENUM_CONTINUE;
}




//◇----------------------------------◇
//キーボード入力の更新関数
//◇----------------------------------◇
void UpdateJoystick(void)
{
	//BYTE aKeyState[256];
	 DIJOYSTATE2 dijs;

	// ジョイスティックからデータを取得
	if(SUCCEEDED(g_pDIDevJoystick->GetDeviceState(sizeof(DIJOYSTATE2), &dijs)))
	{
		// ﾎﾞﾀﾝ状態を判別
		for(int nKey = 0; nKey < 128; nKey++)
		{

			g_aJoystickButtonTrigger[nKey] = ~g_aJoystickButton[nKey] & dijs.rgbButtons[nKey];	// トリガー

			g_aJoystickButtonRelease[nKey] = g_aJoystickButton[nKey] & ~dijs.rgbButtons[nKey];	// リリース

			g_aJoystickButton[nKey] = dijs.rgbButtons[nKey];	// プレス(連続入力)


			//---- リピート処理 ----
			if(GetJoystickTrigger(nKey))	// ボタンを押したとき(リピート開始時)
			{
				g_aJoystickButtonRepeatCount[nKey] = 0;		// カウント初期化
				// ON(押した瞬間は、１回受付)
				g_aJoystickButtonRepeatTrigger[nKey] = 0x80;	// リピートトリガー	
				g_aJoystickButtonRepeatPress[nKey] = 0x80;	// リピートプレス
			}
			else if(GetJoystickPress(nKey))	// 押し続けているとき(リピート中)
			{
				
				g_aJoystickButtonRepeatCount[nKey] += 1;	// カウントアップ

				if(g_aJoystickButtonRepeatCount[nKey] > 30000) g_aJoystickButtonRepeatCount[nKey] = 0;	// オーバーフロー対策

				if(g_aJoystickButtonRepeatCount[nKey] > (float)FPS_DIRECTX * ((float)REPEAT_START_TIME / 1000.0f))		// リピータを開始する時間を設定
				{
					// リピートトリガーは、ON/OFFを繰り返す
					if((g_aJoystickButtonRepeatCount[nKey] % (int)(FPS_DIRECTX * REPEAT_INTERVAL / 1000)) == 0)	// 繰り返し間隔
					{
						g_aJoystickButtonRepeatTrigger[nKey] = 0x80;	// フラグON
					}
					else
					{
						g_aJoystickButtonRepeatTrigger[nKey] = 0x00;	// フラグOFF
					}

					g_aJoystickButtonRepeatPress[nKey] = 0x80;	// 常にフラグON(リピートプレス)
				}
				else
				{
					// OFF（最初の１回受付後、一旦OFFにするため）
					g_aJoystickButtonRepeatTrigger[nKey]	= 0x00;	// リピートトリガー	
					g_aJoystickButtonRepeatPress[nKey]	= 0x00;	// リピートプレス
				}
			}
			else if(GetJoystickRelease(nKey))	// ボタンを離したとき(リピート終了時)
			{
				g_aJoystickButtonRepeatCount[nKey] = 0;		// カウント初期化
				// OFF（ボタン入力終了時）
				g_aJoystickButtonRepeatTrigger[nKey] = 0x00;	// リピートトリガー	
				g_aJoystickButtonRepeatPress[nKey]	= 0x00;	// リピートプレス
			}
			//---- リピート処理ここまで ----
		}
		//---- ボタン状態を判別(for文)ここまで ----

		//とりあえずこれらを調整
		if(dijs.lX >= -100 &&  dijs.lX <= 100)		dijs.lX = 0;
		if(dijs.lY >= -100 &&  dijs.lY <= 100)		dijs.lY = 0;
		if(dijs.lZ >= -100 &&  dijs.lZ <= 100)		dijs.lZ = 0;
		if(dijs.lRx >= -100 && dijs.lRx <= 100)		dijs.lRx = 0;
		if(dijs.lRy >= -100 && dijs.lRy <= 100)		dijs.lRy = 0;
		if(dijs.lRz >= -100 && dijs.lRz <= 100)		dijs.lRz = 0;
		if(dijs.lARx >= -100 && dijs.lARx <= 100)	dijs.lARx = 0;
		if(dijs.lARy >= -100 && dijs.lARy <= 100)	dijs.lARy = 0;
		if(dijs.lARz >= -100 && dijs.lARz <= 100)	dijs.lARz = 0;

		g_JoyState = dijs;



		//========= ANALOG消灯時 ==========================

		BYTE g_aTempJoystickCross[JCK_MAX];
		// 一旦リセット
		for(int nKey = 0; nKey < JCK_MAX; nKey++)
		{
			g_aTempJoystickCross[nKey] = 0x00;
		}


		// 取得

		if(dijs.lX == +1000 && dijs.lY == -1000)
		{
			g_aTempJoystickCross[JCK_RIGHT_UP] = 0x80;
		}
		else if(dijs.lX == +1000 && dijs.lY == +1000)
		{
			g_aTempJoystickCross[JCK_RIGHT_DOWN] = 0x80;
		}
		else if(dijs.lX == -1000 && dijs.lY == +1000)
		{
			g_aTempJoystickCross[JCK_LEFT_DOWN] = 0x80;
		}
		else if(dijs.lX == -1000 && dijs.lY == -1000)
		{
			g_aTempJoystickCross[JCK_LEFT_UP] = 0x80;
		}
		else if(dijs.lY == -1000 )
		{
			g_aTempJoystickCross[JCK_UP] = 0x80;
		}
		else if(dijs.lY == +1000)
		{
			g_aTempJoystickCross[JCK_DOWN] = 0x80;
		}
		else if(dijs.lX == +1000)
		{
			g_aTempJoystickCross[JCK_RIGHT] = 0x80;
		}
		else if(dijs.lX == -1000)
		{
			g_aTempJoystickCross[JCK_LEFT] = 0x80;
		}



		if(dijs.lRz == +1000 && dijs.lZ == -1000)
		{
			g_aTempJoystickCross[JCK_RRIGHT_UP] = 0x80;
		}
		else if(dijs.lRz == +1000 && dijs.lZ == +1000)
		{
			g_aTempJoystickCross[JCK_RRIGHT_DOWN] = 0x80;
		}
		else if(dijs.lRz == -1000 && dijs.lZ == +1000)
		{
			g_aTempJoystickCross[JCK_RLEFT_DOWN] = 0x80;
		}
		else if(dijs.lRz == -1000 && dijs.lZ == -1000)
		{
			g_aTempJoystickCross[JCK_RLEFT_UP] = 0x80;
		}
		else if(dijs.lZ == -1000 )
		{
			g_aTempJoystickCross[JCK_RUP] = 0x80;
		}
		else if(dijs.lZ == +1000)
		{
			g_aTempJoystickCross[JCK_RDOWN] = 0x80;
		}
		else if(dijs.lRx == +1000)
		{
			g_aTempJoystickCross[JCK_RRIGHT] = 0x80;
		}
		else if(dijs.lRx == -1000)
		{
			g_aTempJoystickCross[JCK_RLEFT] = 0x80;
		}


		// 処理
		for(int nKey = 0; nKey < JCK_MAX; nKey++)
		{

			
			g_aJoystickCrossTrigger[nKey] = ~g_aJoystickCross[nKey] & g_aTempJoystickCross[nKey];	// トリガー

			g_aJoystickCrossRelease[nKey] = g_aJoystickCross[nKey] & ~g_aTempJoystickCross[nKey];	// リリース

			g_aJoystickCross[nKey] = g_aTempJoystickCross[nKey];	// プレス


			//---- リピート処理 ----
			if(GetJoystickCrossTrigger((JoystickCrossKey)nKey))	// ボタンを押したとき(リピート開始時)
			{
				g_aJoystickCrossRepeatCount[nKey] = 0;		// カウント初期化
				// ON(押した瞬間は、１回受付)
				g_aJoystickCrossRepeatTrigger[nKey] = 0x80;	// リピートトリガー	
				g_aJoystickCrossRepeatPress[nKey] = 0x80;	// リピートプレス
			}
			else if(GetJoystickCrossPress((JoystickCrossKey)nKey))	// 押し続けているとき(リピート中)
			{
				
				g_aJoystickCrossRepeatCount[nKey] += 1;	// カウントアップ

				if(g_aJoystickCrossRepeatCount[nKey] > 30000) g_aJoystickCrossRepeatCount[nKey] = 0;	// オーバーフロー対策

				if(g_aJoystickCrossRepeatCount[nKey] > (float)FPS_DIRECTX * ((float)REPEAT_START_TIME / 1000.0f))		// リピータを開始する時間を設定
				{
					// リピートトリガーは、ON/OFFを繰り返す
					if((g_aJoystickCrossRepeatCount[nKey] % (int)(FPS_DIRECTX * REPEAT_INTERVAL / 1000)) == 0)	// 繰り返し間隔
					{
						g_aJoystickCrossRepeatTrigger[nKey] = 0x80;	// フラグON
					}
					else
					{
						g_aJoystickCrossRepeatTrigger[nKey] = 0x00;	// フラグOFF
					}

					g_aJoystickCrossRepeatPress[nKey] = 0x80;	// 常にフラグON(リピートプレス)
				}
				else
				{
					// OFF（最初の１回受付後、一旦OFFにするため）
					g_aJoystickCrossRepeatTrigger[nKey]	= 0x00;	// リピートトリガー	
					g_aJoystickCrossRepeatPress[nKey]	= 0x00;	// リピートプレス
				}
			}
			else if(GetJoystickCrossRelease((JoystickCrossKey)nKey))	// ボタンを離したとき(リピート終了時)
			{
				g_aJoystickCrossRepeatCount[nKey] = 0;		// カウント初期化
				// OFF（ボタン入力終了時）
				g_aJoystickCrossRepeatTrigger[nKey] = 0x00;	// リピートトリガー	
				g_aJoystickCrossRepeatPress[nKey]	= 0x00;	// リピートプレス
			}
			//---- リピート処理ここまで ----
			
		}



		//========= ANALOG点灯時 ==========================
		// これは、気にするな

		// 一旦リセット
		for(int nNumCrossKey = 0; nNumCrossKey < JCKP_MAX; nNumCrossKey++)
		{
			g_aJoystickCrossKeyPov[nNumCrossKey] = 0x00;
		}




		//---- 十字キー状態処理(同時押しで競合がないので、ループしなくて良い) ----
		// ８方向で上から右回り
		switch(dijs.rgdwPOV[0])
		{
		case 0:
			g_aJoystickCrossKeyPov[JCKP_UP] = 0x80; 
			break;
		case 4500:
			g_aJoystickCrossKeyPov[JCKP_RIGHT_UP] = 0x80; 
			break;
		case 9000:
			g_aJoystickCrossKeyPov[JCKP_RIGHT] = 0x80; 
			break;
		case 13500:
			g_aJoystickCrossKeyPov[JCKP_RIGHT_DOWN] = 0x80; 
			break;
		case 18000:
			g_aJoystickCrossKeyPov[JCKP_DOWN] = 0x80; 
			break;
		case 22500:
			g_aJoystickCrossKeyPov[JCKP_LEFT_DOWN] = 0x80;
			break;
		case 27000:
			g_aJoystickCrossKeyPov[JCKP_LEFT] = 0x80; 
			break;
		case 31500:
			g_aJoystickCrossKeyPov[JCKP_LEFT_UP] = 0x80; 
			break;
		default:
			break;
		}
	}
	else
	{
		g_pDIDevJoystick->Acquire();	// 予期せぬ時に、キーボードのアクセス権を再取得
	}
}


//◇----------------------------------◇
//ジョイスティック入力のプレス取得関数
//◇----------------------------------◇
bool GetJoystickPress(int nKey)
{
	return (g_aJoystickButton[nKey] & 0x80) ? true : false;
}

//◇----------------------------------◇
//ジョイスティック入力のトリガー取得関数
//◇----------------------------------◇
bool GetJoystickTrigger(int nKey)
{
	return (g_aJoystickButtonTrigger[nKey] & 0x80) ? true : false;
}

//◇----------------------------------◇
//ジョイスティック入力のリリース取得関数
//◇----------------------------------◇
bool GetJoystickRelease(int nKey)
{
	return (g_aJoystickButtonRelease[nKey] & 0x80) ? true : false;
}

//◇----------------------------------◇
//ジョイスティック入力のリピートトリガー取得関数
//◇----------------------------------◇
bool GetJoystickRepeatTrigger(int nKey)
{
	return (g_aJoystickButtonRepeatTrigger[nKey] & 0x80) ? true : false;
}

//◇----------------------------------◇
//ジョイスティック入力のリピート取得関数
//◇----------------------------------◇
bool GetJoystickRepeatPress(int nKey)
{
	return (g_aJoystickButtonRepeatPress[nKey] & 0x80) ? true : false;
}

//◇----------------------------------◇
//十字キー入力のプレス取得関数
//◇----------------------------------◇
bool GetJoystickCrossPov(JoystickCrossKeyPov nKey)
{
	return (g_aJoystickCrossKeyPov[nKey] & 0x80) ? true : false;
}

//◇----------------------------------◇
//十字キー入力のプレス取得関数
//◇----------------------------------◇
bool GetJoystickCrossPress(JoystickCrossKey nKey)
{
	return (g_aJoystickCross[nKey] & 0x80) ? true : false;
}


//◇----------------------------------◇
//ジョイスティック入力のトリガー取得関数
//◇----------------------------------◇
bool GetJoystickCrossTrigger(JoystickCrossKey nKey)
{
	return (g_aJoystickCrossTrigger[nKey] & 0x80) ? true : false;
}

//◇----------------------------------◇
//十字キー入力のリリース取得関数
//◇----------------------------------◇
bool GetJoystickCrossRelease(JoystickCrossKey nKey)
{
	return (g_aJoystickCrossRelease[nKey] & 0x80) ? true : false;
}


//◇----------------------------------◇
//十字キー入力のリピートトリガー取得関数
//◇----------------------------------◇
bool GetJoystickCrossRepeatTrigger(JoystickCrossKey nKey)
{
	return (g_aJoystickCrossRepeatTrigger[nKey] & 0x80) ? true : false;
}

//◇----------------------------------◇
//十字キー入力のリピート取得関数
//◇----------------------------------◇
bool GetJoystickCrossRepeatPress(JoystickCrossKey nKey)
{
	return (g_aJoystickCrossRepeatPress[nKey] & 0x80) ? true : false;
}

float GetJoysticklX()		{return (float)(g_JoyState.lX);}
float GetJoysticklY()		{return (float)(g_JoyState.lY);}
float GetJoysticklZ()		{return (float)(g_JoyState.lZ);}
float GetJoysticklRx()		{return (float)(g_JoyState.lRx);}
float GetJoysticklRy()		{return (float)(g_JoyState.lRy);}
float GetJoysticklRz()		{return (float)(g_JoyState.lRz);}
float GetJoysticklARx()		{return (float)(g_JoyState.lARx);}
float GetJoysticklARy()		{return (float)(g_JoyState.lARy);}
float GetJoysticklARz()		{return (float)(g_JoyState.lARz);}

float GetJoysticklFX()		{return (float)(g_JoyState.lFX);}
float GetJoysticklFY()		{return (float)(g_JoyState.lFY);}
float GetJoysticklFZ()		{return (float)(g_JoyState.lFZ);}

float GetJoysticklFRx()		{return (float)(g_JoyState.lFRx);}
float GetJoysticklFRy()		{return (float)(g_JoyState.lFRy);}
float GetJoysticklFRz()		{return (float)(g_JoyState.lFRz);}
