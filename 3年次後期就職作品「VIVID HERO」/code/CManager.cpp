//◇-------------------------------------------------------------------------◇
//
//	File:マネージャのファイル[CManager.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CManager.h"
#include "main.h"
#include "CPhaseTitle.h"
#include "Joystick.h"
#include "CCamera.h"
#include "CLight.h"
#include "CTextureManager.h"
#include "input.h"
#include "CDebugProc.h"
#include "CPhaseChange.h"
#include "CPhaseGame.h"
#include "CXFileManager.h"
#include "sound.h"
#include "joystick.h"
#include "Renderer.h"

//◇-------------------------------------------------------------------------◇
//メンバ変数の初期化
//◇-------------------------------------------------------------------------◇
CRenderer *CManager::m_Renderer = {NULL};
CLight *CManager::m_pLight = {NULL};
CCamera *CManager::m_pCamera = NULL;
CInput *CManager::m_pInput = {NULL};
CTextureManager *CManager::m_pTexManager = {NULL};
CPhaseChange *CManager::m_pPhaseChange = NULL;
CXFileManager *CManager::m_pXFileManager = NULL;

CJoystick *CManager::m_pJoystick = NULL;

//◇-----------------------------------◇
//マネージャのコンストラクタ
//◇-----------------------------------◇
CManager::CManager()
{

}

//◇-----------------------------------◇
//マネージャのデストラクタ
//◇-----------------------------------◇
CManager::~CManager()
{

}

//◇-----------------------------------◇
//マネージャの初期化処理
//◇-----------------------------------◇
HRESULT CManager::Init(HINSTANCE hInstance)
{
	//レンダラの初期化
	m_Renderer = new CRenderer;
	m_Renderer->Init(hInstance);

	//ライト初期化
	m_pLight = new CLight;
	m_pLight -> Init();
	
	//テクスチャマネージャ初期化
	m_pTexManager = new CTextureManager;
	m_pTexManager->Init(256);

	//Xファイルマネージャ初期化
	m_pXFileManager = new CXFileManager;
	m_pXFileManager->Init(256);
	
	//キーボードの初期化
	m_pInput = new CInput;
	m_pInput->InitKeyboard(hInstance,GethWnd());

	//サウンドの初期化
	InitSound(GethWnd());

	//フェイドの初期化 ここで最初のフェイズを決める
	m_pPhaseChange = new CPhaseChange;
	m_pPhaseChange->Init(new CPhaseTitle());

	return S_OK;
}

//◇-----------------------------------◇
//マネージャの終了処理
//◇-----------------------------------◇
void CManager::Uninit(void)
{
	if(m_Renderer != NULL)
	{
		m_Renderer->Uninit();
		delete m_Renderer;
		m_Renderer = NULL;
	}

	if(m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	if(m_pInput != NULL)
	{
		m_pInput->UninitKeyboard();
		delete m_pInput;
		m_pInput = NULL;
	}

	if(m_pTexManager != NULL)
	{
		m_pTexManager->Uninit();
		delete m_pTexManager;
		m_pTexManager = NULL;
	}

	if(m_pXFileManager != NULL)
	{
		m_pXFileManager->Uninit();
		delete m_pXFileManager;
		m_pXFileManager = NULL;
	}

	if(m_pPhaseChange != NULL)
	{
		m_pPhaseChange->Uninit();
		delete m_pPhaseChange;
		m_pPhaseChange = NULL;
	}

	UninitJoystick();

	UninitSound();

	CScene::ReleaseAll();
}

//◇-----------------------------------◇
//マネージャの更新処理
//◇-----------------------------------◇
void CManager::Update(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	m_pLight->Update();
	m_pInput->UpdateKeyboard();



	m_pPhaseChange->Update();

	m_Renderer->Update();
}

//◇-----------------------------------◇
//マネージャの描画処理
//◇-----------------------------------◇
void CManager::Draw(void)
{
	m_pPhaseChange->Draw();
	m_Renderer->Draw();
}

//◇-----------------------------------◇
//デバイスの取得処理（経由）
//◇-----------------------------------◇
LPDIRECT3DDEVICE9 CManager::GetDevice(void)
{
	return m_Renderer->GetDevice();
}

//◇-----------------------------------◇
//テクスチャマネージャのポインタのゲット処理
//◇-----------------------------------◇
CTextureManager *CManager::GetTextureManagerPointer(void)
{
	return m_pTexManager;
}

//◇-----------------------------------◇
//Xファイルマネージャのポインタのゲット処理
//◇-----------------------------------◇
CXFileManager *CManager::GetXFileManagerPointer(void)
{
	return m_pXFileManager;
}

//◇-----------------------------------◇
//カメラのポインタのゲット処理
//◇-----------------------------------◇
CCamera *CManager::GetCameraPointer(void)
{
	return m_pCamera;
}

//◇-----------------------------------◇
//フェイドチェンジのポインタのゲット処理
//◇-----------------------------------◇
CPhaseChange *CManager::GetPhaseChangePointer(void)
{
	return m_pPhaseChange;
}

//◇-----------------------------------◇
//ビルボードのため主観カメラセット処理
//◇-----------------------------------◇
void CManager::SetMainCameraPointer(CCamera *pCamera)
{
	m_pCamera = pCamera;
}
