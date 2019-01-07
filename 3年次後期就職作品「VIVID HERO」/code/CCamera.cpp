//◇-------------------------------------------------------------------------◇
//
//	File:カメラ処理ファイル[CCamera.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CCamera.h"
#include "CManager.h"
#include "input.h"

//◇---------------------------------◇
//コンストラクタ
//◇---------------------------------◇
CCamera::CCamera()
{
	//***カメラの初期化***
	m_posCamera = D3DXVECTOR3(0.0f,0.0f,0.0f);				//位置
	m_rotCamera = D3DXVECTOR3(0.0f,0.0f,0.0f);				//向き
	m_sclCamera = D3DXVECTOR3(0.0f,0.0f,0.0f);				//大きさ（基本変えない）

	m_posCameraP = D3DXVECTOR3(0.0f,0.0f,0.0f);				//カメラの視点
	m_posCameraR = D3DXVECTOR3(0.0f,0.0f,0.0f);				//カメラの注視点
	m_posCameraU = D3DXVECTOR3(0.0f,1.0f,0.0f);				//カメラの上方向ベクトル

	m_CameraVec = D3DXVECTOR3(0.0f,0.0f,0.0f);
}

//◇---------------------------------◇
//デストラクタ
//◇---------------------------------◇
CCamera::~CCamera()
{

}
//◇---------------------------------◇
//カメラ初期化処理
//◇---------------------------------◇
HRESULT CCamera::Init(void)
{
	//****デバイス取得****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;	//

	//****プロジェクションの設定****  この設定はcamera.cppにしかいらないらしい！by toshiyama
	D3DXMatrixIdentity(&m_mtxProjection);									//初期化
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,							//作成
								D3DX_PI / 4,								//視野角(画角)
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//アスペクト比（画面比率）
								10,											//Near値
								1000000);									//Far値		遠くの物体が見えなくなる境界線の値

	pDevice -> SetTransform(D3DTS_PROJECTION,&m_mtxProjection);

	//****ビューの設定****
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixLookAtLH(&m_mtxView,
						&m_posCameraP,
						&m_posCameraR,
						&m_posCameraU);

	pDevice -> SetTransform(D3DTS_VIEW,&m_mtxView);

	//****ワールドの設定****
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&mtxScl,m_sclCamera.x,
								m_sclCamera.y,
								m_sclCamera.z);			//スケールを反映

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

	//****その他の設定****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rotCamera.y,
									m_rotCamera.x,
									m_rotCamera.z);		//ヨ－　ピッチ　ロール

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,m_posCamera.x,m_posCamera.y,m_posCamera.z);	//位置を反映
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&m_mtxWorld);	//設定

	return S_OK;
}

//◇---------------------------------◇
//カメラ終了処理
//◇---------------------------------◇
void CCamera::Uninit(void)
{

}

//◇---------------------------------◇
//カメラ更新処理
//◇---------------------------------◇
void CCamera::Update(void)
{

}

//◇---------------------------------◇
//カメラセット処理
//◇---------------------------------◇
void CCamera::Set(void)
{
	//****デバイス取得****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;	//

	//****プロジェクションの設定****  この設定はcamera.cppにしかいらないらしい！by toshiyama
	D3DXMatrixIdentity(&m_mtxProjection);									//初期化
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,							//作成
								D3DX_PI / 4,								//視野角(画角)
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//アスペクト比（画面比率）
								10,											//Near値
								1000000);									//Far値		遠くの物体が見えなくなる境界線の値
								
	pDevice -> SetTransform(D3DTS_PROJECTION,&m_mtxProjection);

	//****ビューの設定****
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixLookAtLH(&m_mtxView,
						&m_posCameraP,
						&m_posCameraR,
						&m_posCameraU);

	pDevice -> SetTransform(D3DTS_VIEW,&m_mtxView);

	//****ワールドの設定****
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&mtxScl,m_sclCamera.x,
								m_sclCamera.y,
								m_sclCamera.z);			//スケールを反映

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

	//****その他の設定****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rotCamera.y,
									m_rotCamera.x,
									m_rotCamera.z);		//ヨ－　ピッチ　ロール

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,m_posCamera.x,m_posCamera.y,m_posCamera.z);	//位置を反映
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	
	pDevice -> SetTransform(D3DTS_WORLD,&m_mtxWorld);	//設定
}

//◇---------------------------------◇
//ゲットマトリックス処理
//◇---------------------------------◇
D3DXMATRIX CCamera::GetMtxView(void)
{
	return m_mtxView;
}
//◇---------------------------------◇
//視点処理　プラス
//◇---------------------------------◇
void CCamera::CameraMovePPlus(D3DXVECTOR3 PlusPos)
{
	m_posCameraP += PlusPos;
}

//◇---------------------------------◇
//視点処理　プラス その2
//◇---------------------------------◇
void CCamera::CameraMovePPlus(float x,float y,float z)
{
	m_posCameraP.x += x;
	m_posCameraP.y += y;
	m_posCameraP.z += z;
}

//◇---------------------------------◇
//視点処理　セット
//◇---------------------------------◇
void CCamera::CameraMovePSet(D3DXVECTOR3 SetPos)
{
	m_posCameraP = SetPos;
}

//◇---------------------------------◇
//視点処理	セット　その２
//◇---------------------------------◇
void CCamera::CameraMovePSet(float x,float y,float z)
{
	m_posCameraP.x = x;
	m_posCameraP.y = y;
	m_posCameraP.z = z;
}

//◇---------------------------------◇
//注視点処理　プラス
//◇---------------------------------◇
void CCamera::CameraMoveRPlus(D3DXVECTOR3 PlusPos)
{
	m_posCameraR += PlusPos;
}

//◇---------------------------------◇
//注視点セット　追加移動 その２
//◇---------------------------------◇
void CCamera::CameraMoveRPlus(float x,float y,float z)
{
	m_posCameraR.x += x;
	m_posCameraR.y += y;
	m_posCameraR.z += z;
}

//◇---------------------------------◇
//注視点処理　セット
//◇---------------------------------◇
void CCamera::CameraMoveRSet(D3DXVECTOR3 SetPos)
{
	m_posCameraR = SetPos;
}

//◇---------------------------------◇
//注視点移動処理　その２
//◇---------------------------------◇
void CCamera::CameraMoveRSet(float x,float y,float z)
{
	m_posCameraR.x = x;
	m_posCameraR.y = y;
	m_posCameraR.z = z;
}

//◇---------------------------------◇
//視点ゲット処理
//◇---------------------------------◇
D3DXVECTOR3 CCamera::GetCameraP(void)
{
	return m_posCameraP;
}

//◇---------------------------------◇
//注視点ゲット処理
//◇---------------------------------◇
D3DXVECTOR3 CCamera::GetCameraR(void)
{
	return m_posCameraR;
}

//◇---------------------------------◇
//カメラのベクトルゲット処理処理
//◇---------------------------------◇
D3DXVECTOR3 CCamera::GetCameraVector(void)
{
	m_CameraVec = m_posCameraR - m_posCameraP;

	//使いやすいよう正規化
	D3DXVec3Normalize(&m_CameraVec,&m_CameraVec);

	return m_CameraVec;
}



