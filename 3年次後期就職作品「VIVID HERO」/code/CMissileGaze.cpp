//◇-------------------------------------------------------------------------◇
//
//	File:CMissileGazeのファイル[CMissileGaze.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CMissileGaze.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CMissileGazeのコンストラクタ
//◇-----------------------------------◇
CMissileGaze::CMissileGaze(int nPriority) : CScene2D(nPriority)
{

}

//◇-----------------------------------◇
//CMissileGazeのデストラクタ
//◇-----------------------------------◇
CMissileGaze::~CMissileGaze()
{

}

//◇-----------------------------------◇
//CMissileGazeの初期化処理
//◇-----------------------------------◇
HRESULT CMissileGaze::Init(void)
{
	float Adjustment = 60.0f;
	float sizeX = 200.0f;
	float sizeY = 200.0f;

//	CScene2D::Create(80,"./data/TEXTURE/Game/UI/MissileFrame00.png",
//		D3DXVECTOR3(SCREEN_WIDTH - sizeX/2 - Adjustment + 10.0f,SCREEN_HEIGHT - sizeY/2 - Adjustment - 10.0f,0.0f),D3DXVECTOR3(250.0f,300.0f,0.0f));
//
//	CScene2D::Create(80,"./data/TEXTURE/Game/UI/MissleTex001.png",
//		D3DXVECTOR3(SCREEN_WIDTH - sizeX/2 - Adjustment,SCREEN_HEIGHT - sizeY/2 - Adjustment,0.0f),D3DXVECTOR3(sizeX,sizeY,0.0f));
//	CScene2D::Create(80,"./data/TEXTURE/Game/UI/MissleTex002.png",
//		D3DXVECTOR3(SCREEN_WIDTH - sizeX/2 - Adjustment,SCREEN_HEIGHT - sizeY/2 - Adjustment,0.0f),D3DXVECTOR3(sizeX,sizeY,0.0f));


	return S_OK;
}

//◇-----------------------------------◇
//CMissileGazeの終了処理
//◇-----------------------------------◇
void CMissileGaze::Uninit(void)
{

}

//◇-----------------------------------◇
//CMissileGazeの更新処理
//◇-----------------------------------◇
void CMissileGaze::Update(void)
{

}

//◇-----------------------------------◇
//CMissileGazeの描画処理
//◇-----------------------------------◇
void CMissileGaze::Draw(void)
{

}

//◇-----------------------------------◇
//CMissileGazeのクリエイト
//◇-----------------------------------◇
CMissileGaze *CMissileGaze::Create()
{
	CMissileGaze *pMissileGaze;
	pMissileGaze = new CMissileGaze;

	pMissileGaze->Init();

	return pMissileGaze;

}

