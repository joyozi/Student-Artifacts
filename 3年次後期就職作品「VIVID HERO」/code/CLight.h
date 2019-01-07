//◇-------------------------------------------------------------------------◇
//
//	File:CLightのヘッダーファイル[CLight.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CLIGHT_H_
#define _CLIGHT_H_

//◇-----------------------------------◇
//インクルードファイル　定数定義
//◇-----------------------------------◇
#include "main.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CLight
{
public:
	CLight();
	~CLight();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void  SetLight_Point(float x,float y,float z);
	void  SetLight_Point(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetLight_Point(void);

	void SetType(int nType);

private:
	D3DLIGHT9 m_Light[3];		//ライト情報

	D3DXVECTOR3 m_PosLight_Point;
	D3DXVECTOR3 m_RotLight_Directrical;
	
	static const float DEFFUSE_R;
	static const float DEFFUSE_G;
	static const float DEFFUSE_B;
	static const float DEFFUSE_A;

	static const float LIGHT_RANGE;
	static const float LIGHT_ATTENUATION;
};

#endif
