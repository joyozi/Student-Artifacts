//◇-------------------------------------------------------------------------◇
//
//	File:CExplosion000のファイル[CExplosion000.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CExplosion000.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CExplosion000のコンストラクタ
//◇-----------------------------------◇
CExplosion000::CExplosion000(int nPriority) : CDegeneracyAnimation(nPriority)
{
	m_DegeneracyPolygon_Max = m_NeedPolygonNum;

	m_LoopJudge = true;
	m_AnimationLoopJudge = false;
}

//◇-----------------------------------◇
//CExplosion000のクリエイト
//◇-----------------------------------◇
CExplosion000 *CExplosion000::Create(LPCTSTR TexName,int DivideNumX,int DivideNumY,int AnimTime,int NeedPolygonNum)
{
	CExplosion000 *pExplosion000;
	pExplosion000 = new CExplosion000;

	pExplosion000->m_TexName = TexName;
	pExplosion000->m_Anim_TexDivide_NumX = DivideNumX;
	pExplosion000->m_Anim_TexDivide_NumY = DivideNumY;
	pExplosion000->m_AnimTime = AnimTime;
	pExplosion000->m_DegeneracyPolygon_Max = NeedPolygonNum;

	pExplosion000->Init();

	return pExplosion000;
}

//◇-----------------------------------◇
//CExplosion000の単一ポリゴン設置
//◇-----------------------------------◇
int CExplosion000::ExplosionSet1Set(D3DXVECTOR3 Pos)
{
	return SetPolygon(Pos,D3DXVECTOR3(0.0f,0.0f,0.0f),50.0f,50.0f);
}

//◇-----------------------------------◇
//CExplosion000の単一ポリゴン設置
//◇-----------------------------------◇
int CExplosion000::ExplosionSet1Set(D3DXVECTOR3 Pos,float TexWidth,float TexHeight)
{
	return SetPolygon(Pos,D3DXVECTOR3(0.0f,0.0f,0.0f),TexWidth,TexHeight);
}

//◇-----------------------------------◇
//CExplosion000の3つのポリゴンセット
//◇-----------------------------------◇
void CExplosion000::ExplosionSet3Set(D3DXVECTOR3 Pos)
{
	SetPolygon(Pos + D3DXVECTOR3(0.0f,0.0f,-50.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),300.0f,300.0f);
	SetPolygon(Pos + D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),500.0f,500.0f);
	SetPolygon(Pos + D3DXVECTOR3(0.0f,0.0f,50.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),300.0f,300.0f);
}

//◇-----------------------------------◇
//CExplosion000の完全手動 弾セット
//◇-----------------------------------◇
void CExplosion000::ExplosionSetCustom(int SetNum,D3DXVECTOR3 Pos[],D3DXVECTOR3 Size[])
{
	for(int i = 0;i < SetNum;i++)
	{
		SetPolygon(Pos[0],D3DXVECTOR3(0.0f,0.0f,0.0f),Size[i].x,Size[i].y);
	}
}

//◇-----------------------------------◇
//CExplosion000のマズルフラッシュ
//◇-----------------------------------◇
void CExplosion000::ExplosionMuzzleFlash(D3DXVECTOR3 CenterPos)
{
	float Size = 80.0f;

	float Length = 10.0f;

	int kariNum[24];

	kariNum[0] = SetPolygon(CenterPos											,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);

	kariNum[1] = SetPolygon(CenterPos + D3DXVECTOR3(Length,Length,Length)		,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	kariNum[2] = SetPolygon(CenterPos + D3DXVECTOR3(Length*2,Length*2,Length*2)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	kariNum[3] = SetPolygon(CenterPos + D3DXVECTOR3(Length*3,Length*3,Length*3)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);

	kariNum[4] = SetPolygon(CenterPos + D3DXVECTOR3(Length,-Length,Length)		,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	kariNum[5] = SetPolygon(CenterPos + D3DXVECTOR3(Length*2,-Length*2,Length*2)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	kariNum[6] = SetPolygon(CenterPos + D3DXVECTOR3(Length*3,-Length*3,Length*3)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);

	kariNum[7] = SetPolygon(CenterPos + D3DXVECTOR3(Length,-Length,-Length)			,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	kariNum[8] = SetPolygon(CenterPos + D3DXVECTOR3(Length*2,-Length*2,-Length*2)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	kariNum[9] = SetPolygon(CenterPos + D3DXVECTOR3(Length*3,-Length*3,-Length*3)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);

	kariNum[10] = SetPolygon(CenterPos + D3DXVECTOR3(Length,Length,-Length)		,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	kariNum[11] = SetPolygon(CenterPos + D3DXVECTOR3(Length*2,Length*2,-Length*2)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	kariNum[12] = SetPolygon(CenterPos + D3DXVECTOR3(Length*3,Length*3,-Length*3)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);



	kariNum[13] = SetPolygon(CenterPos + D3DXVECTOR3(-Length,-Length,Length)			,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	kariNum[14] = SetPolygon(CenterPos + D3DXVECTOR3(-Length*2,-Length*2,Length*2)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	kariNum[15] = SetPolygon(CenterPos + D3DXVECTOR3(-Length*3,-Length*3,Length*3)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);

	kariNum[16] = SetPolygon(CenterPos + D3DXVECTOR3(-Length,-Length,-Length)			,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	kariNum[17] = SetPolygon(CenterPos + D3DXVECTOR3(-Length*2,-Length*2,-Length*2)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	kariNum[18] = SetPolygon(CenterPos + D3DXVECTOR3(-Length*3,-Length*3,-Length*3)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);

	kariNum[19] = SetPolygon(CenterPos + D3DXVECTOR3(-Length,Length,-Length)			,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	kariNum[20] = SetPolygon(CenterPos + D3DXVECTOR3(-Length*2,Length*2,-Length*2)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	kariNum[21] = SetPolygon(CenterPos + D3DXVECTOR3(-Length*3,Length*3,-Length*3)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);

	kariNum[22] = SetPolygon(CenterPos + D3DXVECTOR3(-Length,-Length,Length)			,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	kariNum[22] = SetPolygon(CenterPos + D3DXVECTOR3(-Length*2,-Length*2,Length*2)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	kariNum[23] = SetPolygon(CenterPos + D3DXVECTOR3(-Length*3,-Length*3,Length*3)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);

//	for(int i = 0; i < 24;i++)
//		ParticleSetColor(kariNum[i],D3DXCOLOR(1.0f,0.0f,0.0f,1.0f));
}

//◇-----------------------------------◇
//CExplosion000のプレイヤの弾に当たった時のエフェクト
//◇-----------------------------------◇
void CExplosion000::ExplosionPlayerBulletHit(D3DXVECTOR3 CenterPos)
{
	float Size = 500.0f;



	SetPolygon(CenterPos + D3DXVECTOR3(20.0f,0.0f,0.0f)		,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	SetPolygon(CenterPos + D3DXVECTOR3(0.0f,20.0f,10.0f)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	SetPolygon(CenterPos + D3DXVECTOR3(0.0f,50.0f,30.0f)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	SetPolygon(CenterPos + D3DXVECTOR3(20.0f,155.0f,130.0f)		,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);

	SetPolygon(CenterPos + D3DXVECTOR3(30.0f,160.0f,0.0f)		,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	SetPolygon(CenterPos + D3DXVECTOR3(120.0f,30.0f,-70.0f)		,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	SetPolygon(CenterPos + D3DXVECTOR3(150.0f,-150.0f,80.0f)		,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	SetPolygon(CenterPos + D3DXVECTOR3(0.0f,-40.0f,-90.0f)		,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);



	SetPolygon(CenterPos + D3DXVECTOR3(-20.0f,0.0f,0.0f)		,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	SetPolygon(CenterPos + D3DXVECTOR3(-0.0f,20.0f,10.0f)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	SetPolygon(CenterPos + D3DXVECTOR3(-0.0f,50.0f,30.0f)	,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	SetPolygon(CenterPos + D3DXVECTOR3(-20.0f,155.0f,130.0f)		,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	
	SetPolygon(CenterPos + D3DXVECTOR3(-30.0f,160.0f,0.0f)		,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	SetPolygon(CenterPos + D3DXVECTOR3(-120.0f,30.0f,-70.0f)		,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	SetPolygon(CenterPos + D3DXVECTOR3(-150.0f,-150.0f,80.0f)		,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);
	SetPolygon(CenterPos + D3DXVECTOR3(-0.0f,-40.0f,-90.0f)		,D3DXVECTOR3(0.0f,0.0f,0.0f),Size,Size);

}