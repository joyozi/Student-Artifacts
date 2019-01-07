//◇-------------------------------------------------------------------------◇
//
//	File	:カメラ処理ファイル[camera.cpp]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "camera.h"
#include "input.h"
#include "model.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇
#define CAMERA_MOVE (0.6f);			//カメラの移動の速さ
#define CAMERA_ROLL (0.05f);		//カメラの回転の速さ

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇
D3DXVECTOR3 GetRotCamera(void);

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
D3DXVECTOR3 g_posCamera;					//位置
D3DXVECTOR3 g_rotCamera;					//向き
D3DXVECTOR3 g_sclCamera;					//大きさ（基本変えない）
D3DXVECTOR3 g_posCameraP;					//カメラの視点
D3DXVECTOR3 g_posCameraR;					//カメラの注視点
D3DXVECTOR3 g_posCameraU;					//カメラの上方向ベクトル

D3DXMATRIX g_mtxProjection;					//プロジェクションマトリックス
D3DXMATRIX g_mtxView;						//ビューマトリックス
D3DXMATRIX g_mtxWorld;						//ワールドマトリックス

float g_fLengthCamera;						//視点と注視点の距離

D3DVIEWPORT9 viewport;

//◇-------------------------------------------------------------------------◇
//カメラ初期化処理
//◇-------------------------------------------------------------------------◇
void InitCamera(void)
{
	//****位置、角度、スケールの初期化****
	g_posCamera = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_rotCamera = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclCamera = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//***カメラの初期化***
	g_posCameraP = D3DXVECTOR3(0.0f,150.0f,120.0f);		//カメラの視点
	g_posCameraR = D3DXVECTOR3(0.0f,60.0f,150.0f);		//カメラの注視点
	g_posCameraU = D3DXVECTOR3(0.0f,1.0f,0.0f);			//カメラの上方向ベクトル

	viewport.X      = 0;
	viewport.Y      = 0;
	viewport.Width  = SCREEN_WIDTH / 2;
	viewport.Height = SCREEN_HEIGHT;
	viewport.MinZ   = 0.0f;
	viewport.MaxZ   = 1.0f;
}

//◇---------------------------------◇
//カメラ終了処理
//◇---------------------------------◇
void UninitCamera(void)
{

}
//◇---------------------------------◇
//カメラの更新処理
//◇---------------------------------◇
void UpdateCamera(void)
{
	static float rad = D3DX_PI;
	static float tyuurad = 0;

	static bool change = true;


	if(change == true)
	{
		//モデルを中心に移動
//		g_posCameraR.x = Getg_posModel().x - sinf(g_rotCamera.y) * 30;
		g_posCameraR.z = Getg_posModel().z - cosf(g_rotCamera.y) + 400;

		g_posCameraP.x = g_posCameraR.x - sinf(g_rotCamera.y) * 700;
		g_posCameraP.z = g_posCameraR.z - cosf(g_rotCamera.y) * 650;

	}
	else
	{	//モデルの進行方向の先を中心に移動
		g_posCameraR.x = Getg_posModel().x;
		g_posCameraR.z = Getg_posModel().z;

		g_posCameraP.x = g_posCameraR.x - sinf(g_rotCamera.y) * 300;
		g_posCameraP.z = g_posCameraR.z - cosf(g_rotCamera.y) * 300;
	}

}

//◇---------------------------------◇
//カメラのセット処理
//◇---------------------------------◇
void SetCamera(void)
{
	//****デバイス取得****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;	//

	//****プロジェクションの設定****  この設定はcamera.cppにしかいらないらしい！by toshiyama
	D3DXMatrixIdentity(&g_mtxProjection);									//初期化
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,							//作成
								D3DX_PI / 4,								//視野角(画角)
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//アスペクト比（画面比率）
								10,											//Near値
								CAMERA_LONG);								//Far値		遠くの物体が見えなくなる境界線の値

	pDevice -> SetTransform(D3DTS_PROJECTION,&g_mtxProjection);

	//****ビューの設定****
	D3DXMatrixIdentity(&g_mtxView);
	D3DXMatrixLookAtLH(&g_mtxView,
						&g_posCameraP,
						&g_posCameraR,
						&g_posCameraU);

	pDevice -> SetTransform(D3DTS_VIEW,&g_mtxView);

	//****ワールドの設定****
	D3DXMatrixIdentity(&g_mtxWorld);
	D3DXMatrixScaling(&mtxScl,g_sclCamera.x,
								g_sclCamera.y,
								g_sclCamera.z);			//スケールを反映

	D3DXMatrixMultiply(&g_mtxWorld,&g_mtxWorld,&mtxScl);

	//****その他の設定****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotCamera.y,
									g_rotCamera.x,
									g_rotCamera.z);		//ヨ－　ピッチ　ロール

	D3DXMatrixMultiply(&g_mtxWorld,&g_mtxWorld,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,g_posCamera.x,g_posCamera.y,g_posCamera.z);	//位置を反映
	D3DXMatrixMultiply(&g_mtxWorld,&g_mtxWorld,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorld);	//設定
}

//*********************************
//いろいろなゲット
//*********************************
D3DXVECTOR3 GetposCamera(void)
{
	return g_posCamera;
}

D3DXVECTOR3 GetRotCamera(void)
{
	return g_rotCamera;
}

D3DXVECTOR3 GetsclCamera(void)
{
	return g_sclCamera;
}

D3DXMATRIX GetMtxView(void)
{
	return g_mtxView;
}