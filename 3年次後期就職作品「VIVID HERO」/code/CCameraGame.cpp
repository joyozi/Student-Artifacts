//◇-------------------------------------------------------------------------◇
//
//	File:ゲーム用のカメラ処理ファイル[CCameraGame.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CCameraGame.h"
#include "CManager.h"

#include "CScene.h"
#include "input.h"
#include "CItemList.h"
#include "CItemList.h"
#include "CDebugProc.h"

//◇---------------------------------◇
//コンストラクタ
//◇---------------------------------◇
CCameraGame::CCameraGame()
{
	//***カメラの初期化***
	m_posCameraP		= D3DXVECTOR3(0.0f,0.0f,-500.0f);		//カメラの視点
	m_posCameraR		= D3DXVECTOR3(0.0f,0.0f,0.0f);		//カメラの注視点
	m_posCameraU		= D3DXVECTOR3(0.0f,1.0f,0.0f);		//カメラの上方向ベクトル

	m_AdjustmentPos		= D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_AdjustmentNowPos	= D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_Viewport.X		= 0;
	m_Viewport.Y		= 0;
	m_Viewport.Width	= SCREEN_WIDTH / 2;
	m_Viewport.Height	= SCREEN_HEIGHT;
	m_Viewport.MinZ		= 0.0f;
	m_Viewport.MaxZ		= 1.0f;
}

//◇---------------------------------◇
//カメラ更新処理
//◇---------------------------------◇
void CCameraGame::Update(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	CScene *irekoScene = NULL;
	CScene::SearchLinkList(&irekoScene,CTYPE_PLAYERMODEL);

	if(irekoScene != NULL)
	{
		D3DXVECTOR3 Length = D3DXVECTOR3(0.0f,0.0f,0.0f);
		float CameraRadius = 1000.0f;

		D3DXVECTOR3 CameraLength = m_posCameraR - irekoScene->GetPosition();
		D3DXVECTOR3 CameraRotRP = D3DXVECTOR3(0.0f,0.0f,0.0f);
		CameraRotRP = CItemList::VecAngle_3D_D3DX(CameraLength);
		
		Length.x = -(CameraRadius) * cosf(CameraRotRP.x) * sinf(CameraRotRP.y);
		Length.y = -(CameraRadius) * sinf(CameraRotRP.x) + 500.0f;
		Length.z = -(CameraRadius) * cosf(CameraRotRP.x) * cosf(CameraRotRP.y);

		//最終調整も加える
		m_AdjustmentNowPos = CItemList::Vec3lerp(m_AdjustmentNowPos,m_AdjustmentPos,0.5f);
		m_posCameraP = irekoScene->GetPosition() + Length + m_AdjustmentNowPos;

		CDebugProc::Print("カメラのX軸角度 : %d\n",(int)CameraRotRP.x);
		CDebugProc::Print("カメラのY軸角度 : %d\n",(int)CameraRotRP.y);
	}

#ifdef _DEBUG
	if(CInput::GetKeyboardPress(DIK_UP))	{m_posCameraR=D3DXVECTOR3(0.0f,0.0f,0.0f);m_posCameraP=D3DXVECTOR3(1.0f,3000.0f,0.0f);}
	if(CInput::GetKeyboardPress(DIK_DOWN))	{m_posCameraR=D3DXVECTOR3(0.0f,0.0f,0.0f);m_posCameraP=D3DXVECTOR3(1.0f,-3000.0f,0.0f);}
	if(CInput::GetKeyboardPress(DIK_LEFT))	{m_posCameraR=D3DXVECTOR3(0.0f,0.0f,0.0f);m_posCameraP=D3DXVECTOR3(-3000.0f,0.0f,0.0f);}
	if(CInput::GetKeyboardPress(DIK_RIGHT))	{m_posCameraR=D3DXVECTOR3(0.0f,0.0f,0.0f);m_posCameraP=D3DXVECTOR3(3000.0f,0.0f,0.0f);}
#endif
}


