//◇-------------------------------------------------------------------------◇
//
//	File	:ライト処理ファイル[light.cpp]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "light.h"
#include "model.h"
#include "input.h"
#include "taimatsu.h"
#include "camera.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇
#define DEFFUSE_R (0.3f)			//ライトの色。赤
#define DEFFUSE_G (0.3f)			//ライトの色。緑
#define DEFFUSE_B (0.3f)			//ライトの色。青
#define DEFFUSE_A (1.0f)			//ライトの色。アルファ

#define LIGHT_NUM ((int)(CAMERA_LONG * 2 / TAIMATSU_KANKAKU))		//ライトの数
#define LIGHTJOUHOU_NUM		(LIGHT_NUM * 3)						//ライト情報の[]内の数 (使えてない)
#define LIGHT_RANGE			(1000.0f)
#define LIGHT_ATTENUATION	(0.8f)
//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
D3DLIGHT9 g_aLight[LIGHTJOUHOU_NUM];		//ライト情報		[]内にはライトの数＊3を入れる

float light_POSZ;							//ライトの一番後ろの位置
bool Light_sayuu;							//松明を左右のどっちに設置するかのジャッジ

bool kisuu_LightOPSION;						//一番後ろの松明が左右どちらにあるかを入れる。松明の数が奇数にするなら使う

//◇-------------------------------------------------------------------------◇
//ライト初期化処理
//◇-------------------------------------------------------------------------◇
void InitLight(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
//	VERTEX_3D *pVtx;
	
	//松明の左右の位置と前後の位置の初期化
	Light_sayuu = true;
	kisuu_LightOPSION = Light_sayuu;	//松明の一番後ろの位置の初期化
	light_POSZ = -CAMERA_LONG;

	//****ライトの初期化****
	D3DXVECTOR3 VecDir[3];
	for(int nCnt = 0;nCnt < LIGHT_NUM;nCnt++)
	{
		//****ライト1****
		//======================
		ZeroMemory(&g_aLight[0 + (nCnt * 3)],sizeof(D3DLIGHT9));
		g_aLight[0 + (nCnt * 3)].Type = D3DLIGHT_POINT;													//ライトの種類
		g_aLight[0 + (nCnt * 3)].Diffuse = D3DXCOLOR(DEFFUSE_R, DEFFUSE_G, DEFFUSE_B, DEFFUSE_A);		//ライトの色

		g_aLight[0 + (nCnt * 3)].Position = D3DXVECTOR3(Getpostaimatsu().x,Getpostaimatsu().y,Getpostaimatsu().z);

		g_aLight[0 + (nCnt * 3)].Attenuation0 =LIGHT_ATTENUATION;
		g_aLight[0 + (nCnt * 3)].Range = LIGHT_RANGE;

		D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0 + (nCnt * 3)].Direction,&VecDir[0 + (nCnt * 3)]);

		pDevice -> SetLight(0 + (nCnt * 3),&g_aLight[0 + (nCnt * 3)]);	//ライトを設定
		pDevice -> LightEnable(0 + (nCnt * 3),TRUE);			//ライトを有効にする

		//***ライト2***
		//========================
		ZeroMemory(&g_aLight[1 + (nCnt * 3)],sizeof(D3DLIGHT9));
		g_aLight[1 + (nCnt * 3)].Type = D3DLIGHT_POINT;						//ライトの種類
		g_aLight[1 + (nCnt * 3)].Diffuse = D3DXCOLOR(DEFFUSE_R, DEFFUSE_G, DEFFUSE_B, DEFFUSE_A);		//ライトの色

		g_aLight[1 + (nCnt * 3)].Position = D3DXVECTOR3(Getpostaimatsu().x,Getpostaimatsu().y,Getpostaimatsu().z);

		g_aLight[1 + (nCnt * 3)].Attenuation0 =LIGHT_ATTENUATION;
		g_aLight[1 + (nCnt * 3)].Range = LIGHT_RANGE;

		D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[1 + (nCnt * 3)].Direction,&VecDir[1 + (nCnt * 3)]);

		pDevice -> SetLight(1 + (nCnt * 3),&g_aLight[1 + (nCnt * 3)]);	//ライトを設定
		pDevice -> LightEnable(1 + (nCnt * 3),TRUE);			//ライトを有効にする

		//***ライト3***
		//========================
		ZeroMemory(&g_aLight[2 + (nCnt * 3)],sizeof(D3DLIGHT9));
		g_aLight[2 + (nCnt * 3)].Type = D3DLIGHT_POINT;						//ライトの種類
		g_aLight[2 + (nCnt * 3)].Diffuse = D3DXCOLOR(DEFFUSE_R, DEFFUSE_G, DEFFUSE_B, DEFFUSE_A);		//ライトの色

		g_aLight[2 + (nCnt * 3)].Position = D3DXVECTOR3(Getpostaimatsu().x,Getpostaimatsu().y,Getpostaimatsu().z);

		g_aLight[2 + (nCnt * 3)].Attenuation0 =LIGHT_ATTENUATION;
		g_aLight[2 + (nCnt * 3)].Range = LIGHT_RANGE;

		D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[2 + (nCnt * 3)].Direction,&VecDir[2 + (nCnt * 3)]);

		//****ライトの設定****
		pDevice -> SetLight(2 + (nCnt * 3),&g_aLight[2 + (nCnt * 3)]);	//ライトを設定
		pDevice -> LightEnable(2,TRUE);			//ライトを有効にする
	}
}

//◇---------------------------------◇
//ライト終了処理
//◇---------------------------------◇
void UninitLight(void)
{

}
//◇---------------------------------◇
//ライトの更新処理
//◇---------------------------------◇
void UpdateLight(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXVECTOR3 LightIti;			//松明の位置を受け取る変数

	//松明の位置をここで受け取る
	LightIti = Getpostaimatsu();

	//偶数だったらtrueから最初にしないと、松明の位置がおかしくなったりする
//	if((int)(CAMERA_LONG / TAIMATSU_KANKAKU) % 2 == 0)
	{
		Light_sayuu = kisuu_LightOPSION;
	}

	//本体の位置より遠ざかったらプラスマイナスする
	while(Getg_posModel().z - CAMERA_LONG >= light_POSZ)
	{
		light_POSZ += TAIMATSU_KANKAKU;

		//左右移動
		if(Light_sayuu == true)
			Light_sayuu = false;
		else
			Light_sayuu = true;

		//一番後ろの松明の左右位置の判定
		if(kisuu_LightOPSION == true)
			kisuu_LightOPSION = false;
		else
			kisuu_LightOPSION = true;

	}

	//松明のcppと同じ処理を行う
	while(Getg_posModel().z + CAMERA_LONG < light_POSZ + CAMERA_LONG * 2)
	{
		light_POSZ -= TAIMATSU_KANKAKU;

		//左右移動
		if(Light_sayuu == true)
			Light_sayuu = false;
		else
			Light_sayuu = true;

		//一番後ろの松明の左右位置の判定
		if(kisuu_LightOPSION == true)
			kisuu_LightOPSION = false;
		else
			kisuu_LightOPSION = true;
	}
	//松明の位置を一番後ろに設定
	LightIti.z = light_POSZ;

	int num = 0;

	for(int nCnt = 0;nCnt < LIGHT_NUM;nCnt++)
	{
		LightIti.z += TAIMATSU_KANKAKU;

		if(Light_sayuu == true)
		{
			//もし正だったら左側に松明を表示する
			LightIti.x = TAIMATSU_POSX;
			Light_sayuu = false;
		}
		else
		{
			LightIti.x = -TAIMATSU_POSX;
			Light_sayuu = true;
		}

		g_aLight[0 + (nCnt*3)].Position = D3DXVECTOR3(LightIti.x,LightIti.y,LightIti.z);
		g_aLight[1 + (nCnt*3)].Position = D3DXVECTOR3(LightIti.x,LightIti.y,LightIti.z);
		g_aLight[2 + (nCnt*3)].Position = D3DXVECTOR3(LightIti.x,LightIti.y,LightIti.z);

		pDevice -> SetLight(0 + (nCnt*3),&g_aLight[0 + (nCnt*3)]);	//ライトを設定
		pDevice -> SetLight(1 + (nCnt*3),&g_aLight[1 + (nCnt*3)]);	//ライトを設定
		pDevice -> SetLight(2 + (nCnt*3),&g_aLight[2 + (nCnt*3)]);	//ライトを設定
	}


	static bool judge = true;

	if(GetKeyboardTrigger(DIK_0) == true)
	{
		if(judge == true)
			judge =false;
		else
			judge =true;
	

		if(judge == true)
		{
			g_aLight[0].Type = D3DLIGHT_POINT;						//ライトの種類
			g_aLight[1].Type = D3DLIGHT_POINT;						//ライトの種類
			g_aLight[2].Type = D3DLIGHT_POINT;						//ライトの種類
		}
		else
		{
			g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;						//ライトの種類
			g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;						//ライトの種類
			g_aLight[2].Type = D3DLIGHT_DIRECTIONAL;						//ライトの種類
		}
	}
}

//◇---------------------------------◇
//ライトの描画処理
//◇---------------------------------◇
void DrawLight(void)
{

}
