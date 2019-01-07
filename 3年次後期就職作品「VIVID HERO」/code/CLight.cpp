//◇-------------------------------------------------------------------------◇
//
//	File:フィールド処理ファイル[CLight.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CLight.h"
//#include "CManager.h"

const float CLight::DEFFUSE_R = 1.0f;
const float CLight::DEFFUSE_G = 1.0f;
const float CLight::DEFFUSE_B = 1.0f;
const float CLight::DEFFUSE_A = 1.0f;

const float CLight::LIGHT_RANGE = 10000.0f;
const float CLight::LIGHT_ATTENUATION = 1.0f;		//たぶんライトの減衰の仕方

#define LIGHT_DIRECTIONAL
//#define LIGHT_POINT

//◇---------------------------------◇
//コンストラクタ
//◇---------------------------------◇
CLight::CLight()
{
	m_PosLight_Point = D3DXVECTOR3(0.0f,200.0f,0.0f);

	m_RotLight_Directrical = D3DXVECTOR3(0.0f,-1.0f,0.0f);
}
//◇---------------------------------◇
//デストラクタ
//◇---------------------------------◇
CLight::~CLight()
{

}
//◇---------------------------------◇
//初期化処理
//◇---------------------------------◇
void CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	
	//****ライトの初期化****
	D3DXVECTOR3 VecDir[3];

#ifdef LIGHT_DIRECTIONAL

	for(int i = 0;i < 3;i++)
	{
		switch(i)
		{
		case 0:
			m_RotLight_Directrical = D3DXVECTOR3(0.0f,-1.0f,0.0f);
			break;
		case 1:
			m_RotLight_Directrical = D3DXVECTOR3(0.0f,1.0f,0.0f);
			break;
		case 2:
			m_RotLight_Directrical = D3DXVECTOR3(0.0f,0.0f,1.0f);
			break;
		case 3:
			m_RotLight_Directrical = D3DXVECTOR3(0.0f,0.0f,-1.0f);
			break;
		}

		//****ライト1****
		//======================
		ZeroMemory(&m_Light[i],sizeof(D3DLIGHT9));
		m_Light[i].Type = D3DLIGHT_DIRECTIONAL;										//ライトの種類
		m_Light[i].Diffuse = D3DXCOLOR(DEFFUSE_R, DEFFUSE_G, DEFFUSE_B, DEFFUSE_A);	//ライトの色
		VecDir[i] = D3DXVECTOR3(m_RotLight_Directrical.x,m_RotLight_Directrical.y,m_RotLight_Directrical.z);	//ライトの方向

		D3DXVec3Normalize((D3DXVECTOR3*)&m_Light[i].Direction,&VecDir[i]);

		pDevice -> SetLight(i,&m_Light[i]);	//ライトを設定
		pDevice -> LightEnable(i,TRUE);			//ライトを有効にする
	}

#else if LIGHT_POINT

	//****ライト1****
	//======================
	ZeroMemory(&m_Light[0],sizeof(D3DLIGHT9));
	m_Light[0].Type = D3DLIGHT_POINT;													//ライトの種類
	m_Light[0].Diffuse = D3DXCOLOR(DEFFUSE_R, DEFFUSE_G, DEFFUSE_B, DEFFUSE_A);			//ライトの色

	m_Light[0].Position = D3DXVECTOR3(m_PosLight_Point.x,m_PosLight_Point.y,m_PosLight_Point.z);

	m_Light[0].Attenuation0 = LIGHT_ATTENUATION;
	m_Light[0].Range = LIGHT_RANGE;

	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light[0].Direction,&VecDir[0]);

	pDevice -> SetLight(0,&m_Light[0]);		//ライトを設定
	pDevice -> LightEnable(0,TRUE);			//ライトを有効にする

	//***ライト2***
	//========================
	ZeroMemory(&m_Light[1],sizeof(D3DLIGHT9));
	m_Light[1].Type = D3DLIGHT_POINT;												//ライトの種類
	m_Light[1].Diffuse = D3DXCOLOR(DEFFUSE_R, DEFFUSE_G, DEFFUSE_B, DEFFUSE_A);		//ライトの色

	m_Light[1].Position = D3DXVECTOR3(m_PosLight_Point.x,m_PosLight_Point.y,m_PosLight_Point.z);

	m_Light[1].Attenuation0 = LIGHT_ATTENUATION;
	m_Light[1].Range = LIGHT_RANGE;

	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light[1].Direction,&VecDir[1]);

	pDevice->SetLight(1,&m_Light[1]);		//ライトを設定
	pDevice->LightEnable(1,TRUE);			//ライトを有効にする

	//***ライト3***
	//========================
	ZeroMemory(&m_Light[2],sizeof(D3DLIGHT9));
	m_Light[2].Type = D3DLIGHT_POINT;											//ライトの種類
	m_Light[2].Diffuse = D3DXCOLOR(DEFFUSE_R, DEFFUSE_G, DEFFUSE_B, DEFFUSE_A);	//ライトの色

	m_Light[2].Position = D3DXVECTOR3(m_PosLight_Point.x,m_PosLight_Point.y,m_PosLight_Point.z);

	m_Light[2].Attenuation0 = LIGHT_ATTENUATION;
	m_Light[2].Range = LIGHT_RANGE;

	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light[2].Direction,&VecDir[2]);

	//****ライトの設定****
	pDevice -> SetLight(2,&m_Light[2]);		//ライトを設定
	pDevice -> LightEnable(2,TRUE);			//ライトを有効にする

#endif
}

//◇---------------------------------◇
//終了処理
//◇---------------------------------◇
void CLight::Uninit(void)
{

}

//◇---------------------------------◇
//更新処理
//◇---------------------------------◇
void CLight::Update(void)
{

}

//◇---------------------------------◇
//描画処理
//◇---------------------------------◇
void CLight::Draw(void)
{

}

//◇---------------------------------◇
//セットカメラ位置
//◇---------------------------------◇
void CLight::SetLight_Point(float x,float y,float z)
{
	m_PosLight_Point = D3DXVECTOR3(x,y,z);
}

//◇---------------------------------◇
//セットライト位置
//◇---------------------------------◇
void CLight::SetLight_Point(D3DXVECTOR3 pos)
{
	m_PosLight_Point = pos;
}

//◇---------------------------------◇
//ゲットライト位置
//◇---------------------------------◇
D3DXVECTOR3 CLight::GetLight_Point(void)
{
	return m_PosLight_Point;
}







