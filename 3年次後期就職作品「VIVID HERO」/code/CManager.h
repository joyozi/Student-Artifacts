//◇-------------------------------------------------------------------------◇
//
//	File:マネージャのファイル[CManager.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CMANAGER_H_
#define _CMANAGER_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "main.h"

class CRenderer;
class CCamera;
class CLight;
class CTextureManager;
class CDebugProc;
class CInput;
class CPhaseChange;
class CPhaseGame;
class CXFileManager;
class CJoystick;
class CPhase;

//#define JOYSTIKON

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void);

	static CTextureManager *GetTextureManagerPointer(void);		//テクスチャのポインタをゲットする
	static CXFileManager *GetXFileManagerPointer(void);		//Xファイルのポインタをゲットする
	static CCamera *GetCameraPointer(void);						//カメラのポインタをゲットする
	static CPhaseChange *GetPhaseChangePointer(void);
	
	static void SetMainCameraPointer(CCamera *pCamera);				//ビルボードのために主観のカメラを持ってくる

private:
	static CRenderer *m_Renderer;
	static CLight *m_pLight;
	static CCamera *m_pCamera;
	static CTextureManager *m_pTexManager;
	static CInput *m_pInput;
	static CPhase *m_pPhase;
	static CPhaseChange *m_pPhaseChange;
	static CXFileManager *m_pXFileManager;

	static CJoystick *m_pJoystick;
};



#endif
