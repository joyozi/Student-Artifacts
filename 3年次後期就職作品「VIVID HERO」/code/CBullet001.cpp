//◇-------------------------------------------------------------------------◇
//
//	File:CBullet001のファイル[CBullet001.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CBullet001.h"
#include "CItemList.h"
#include "CExplosion000.h"
#include "CPhaseGame.h"
#include "CManager.h"
#include "CTextureManager.h"
#include "sound.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CBullet001のコンストラクタ
//◇-----------------------------------◇
CBullet001::CBullet001(int nPriority) : CDegeneracyPolygon(nPriority)
{
	m_Type = CTYPE_BULLET000;
	m_DegeneracyPolygon_Max = BULLET001_MAX;

	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_TexName = "./data/TEXTURE/Game/shadow000.jpg";

	BulletNumCounter = 0;
	m_TexSize = 50.0f;
	m_TexLength = 15.0f;
	
	m_AlphaBlendJudge = true;

	m_Speed = 200.0f;

	m_ShotTexNum	 = SHOT_TEXNUM;
	m_ShotNumMax	 = SHOT_NUMMAX;
	m_BulletMax		 = BULLET001_MAX;
}

//◇-----------------------------------◇
//CBullet001のデストラクタ
//◇-----------------------------------◇
CBullet001::~CBullet001()
{

}

//◇-----------------------------------◇
//CBullet001の初期化処理
//◇-----------------------------------◇
HRESULT CBullet001::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	
	//***テクステャの読み込み***
	m_Texture = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_TexName));

	int Index_Max = m_DegeneracyPolygon_Max * 4 + ((m_DegeneracyPolygon_Max - 1) * 2);
	int Vtx_Max = m_DegeneracyPolygon_Max * 4;

	m_pLength = new float[m_DegeneracyPolygon_Max];
	m_pAngle = new float[m_DegeneracyPolygon_Max];
	m_pDegeneracyPolygonPos = new D3DXVECTOR3[m_DegeneracyPolygon_Max];
	m_pPolygonExistJudge = new bool[m_DegeneracyPolygon_Max];
	m_pDegeneracyPolygonRot = new D3DXVECTOR3[m_DegeneracyPolygon_Max];
	m_pPolygonUninitFlag = new bool[m_DegeneracyPolygon_Max];

	m_VtxBox = new VERTEX_3D[Vtx_Max];

	for(int i = 0;i < m_DegeneracyPolygon_Max;i++)
	{
		m_pPolygonExistJudge[i] = false;
		m_pLength[i] = 0.0f;
		m_pAngle[i] = 0.0f;
		m_pDegeneracyPolygonPos[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_pDegeneracyPolygonRot[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_pPolygonUninitFlag[i] = false;
	}
	
	//Bullet専用の初期化処理===================================================================
	m_pBulletInfo = new DEGENERACY_BULLET[m_ShotNumMax];

	for(int i = 0;i < m_ShotNumMax;i++)
	{
		m_pBulletInfo[i].Life		 = 0;
		m_pBulletInfo[i].Speed		 = m_Speed;
		m_pBulletInfo[i].Pos		 = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_pBulletInfo[i].StartPos	 = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_pBulletInfo[i].GoVec		 = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_pBulletInfo[i].ExistJudge	 = false;

		for(int i_2 = 0;i_2 < m_ShotTexNum;i_2++)
		{
			m_pBulletInfo[i].PolygonNum[i_2] = -1;
		}
	}

	//=========================================================================================

	//****インデックスバッファの確保****
	pDevice->CreateIndexBuffer(sizeof(WORD) * Index_Max,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&m_IdxBuffer,NULL);
	//****頂点バッファの設定****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*Vtx_Max,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_VtxBuffer,NULL);

	//頂点数分繰り返す
	for(int nCnt = 0;nCnt < Vtx_Max;nCnt++)
	{
		//最初に代入
		m_VtxBox[nCnt].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_VtxBox[nCnt].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		m_VtxBox[nCnt].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	}

	//****texの設定****
	float TexCntx = 0.0f;	//texでのみ使う
	float TexCnty = 0.0f;	//texでのみ使う

	for(int nCnt = 0;nCnt < Vtx_Max;nCnt++)
	{
		m_VtxBox[nCnt].tex = D3DXVECTOR2(TexCntx,TexCnty);
		TexCntx += 1.0f;

		//右側になったらみたいな
		if(nCnt % 2 == 1)
		{
			TexCntx = 0.0f;
			if(TexCnty == 0.0f)
				TexCnty += 1.0f;
			else
				TexCnty = 0.0f;
		}
	}

	//============インデックス情報を設定====================
	m_IdxBuffer -> Lock(0,0,(void**)&m_pIdx,0);

	//****m_pIdxへの段数入力****
	int IdxNum = -1;
	int IdxdansuuCnt = 1;

	int PolygonNumX = 1;		//横のポリゴンの数

	for(int nCnt = 0;nCnt < Index_Max;nCnt++)
	{
		if(nCnt % 2 == 0)
		{
			IdxNum += (2 + PolygonNumX);
		}
		else
		{
			IdxNum -= (1 + PolygonNumX);
		}

		//1 5 9 13
		if(IdxNum == (IdxdansuuCnt - 1) * 4 + 1 && IdxNum != (m_DegeneracyPolygon_Max - 1) * 4 + 1)
		{
			//まず二つの頂点を同じところにセットする
			m_pIdx[nCnt] = IdxNum;
			m_pIdx[nCnt + 1] = IdxNum;
			//左下のところに移動してからセットする。
			IdxNum += (4 + PolygonNumX);
			m_pIdx[nCnt + 2] = IdxNum;

			//三回代入したので3を足す　下のm_pIdx[nCnt] = IdxNumで結果的に同じところの数値を入れられる
			nCnt += 3;

			//Z軸方向にシフトする
			IdxdansuuCnt++;
		}

		m_pIdx[nCnt] = IdxNum;
	}

	//============インデックスバッファのロック解除============
	m_IdxBuffer -> Unlock();

	return S_OK;
}

//◇-----------------------------------◇
//CBullet001の終了処理
//◇-----------------------------------◇
void CBullet001::Uninit(void)
{
	Release();

	SAFE_RELEASE(m_VtxBuffer);
	SAFE_RELEASE(m_IdxBuffer);

	SAFE_DELETE_ARRY(m_pAngle);
	SAFE_DELETE_ARRY(m_pLength);
	SAFE_DELETE_ARRY(m_pDegeneracyPolygonPos);
	SAFE_DELETE_ARRY(m_pPolygonExistJudge);
	SAFE_DELETE_ARRY(m_pDegeneracyPolygonRot);
	SAFE_DELETE_ARRY(m_VtxBox);
	SAFE_DELETE_ARRY(m_pPolygonUninitFlag);
	SAFE_DELETE_ARRY(m_pBulletInfo);
}

//◇-----------------------------------◇
//CBullet001の更新処理
//◇-----------------------------------◇
void CBullet001::Update(void)
{
	int BulletNum = 0;

	for(int i = 0;i < m_ShotNumMax;i++)
	{
		//弾ひとつが存在してたら
		if(m_pBulletInfo[i].ExistJudge)
		{
			m_pBulletInfo[i].Pos += m_pBulletInfo[i].GoVec * m_pBulletInfo[i].Speed;
			
			//弾1つのテクスチャ枚数文移動させる
			for(int i_2 = 0;i_2 < m_ShotTexNum;i_2++)
			{
				ParticleSetPosition( m_pBulletInfo[i].PolygonNum[i_2],m_pBulletInfo[i].Pos - m_pBulletInfo[i].GoVec * (i_2 * m_TexLength));
			}

			m_pBulletInfo[i].Life++;
			if(m_pBulletInfo[i].Life >= BULLET001_LIFEMAX)
			{
				Bullet001ShotUninit(i);
			}
			else
			{
				//生きてたらあたり判定数のカウント
				BulletNum++;
			}
		}
	}
	SetCollisionHitNum(BulletNum);
}

//◇-----------------------------------◇
//CBullet001のあたり判定関数
//◇-----------------------------------◇
float CBullet001::GetCollisionRadius(int Num)
{
	return 5.0f;
}

//◇-----------------------------------◇
//CBullet001のあたり判定の位置
//◇-----------------------------------◇
D3DXVECTOR3 CBullet001::GetCollisionCenterPos(int Num)
{
	int a = 0;

	for(int i = 0;i < m_ShotNumMax;i++)
	{
		if(m_pBulletInfo[i].ExistJudge)
		{
			if(a == Num)
			{
				return m_pBulletInfo[i].Pos;
			}

			a++;
		}
	}

	return D3DXVECTOR3(0.0f,0.0f,0.0f);
}

//◇-----------------------------------◇
//CBullet001のアクション
//◇-----------------------------------◇
void CBullet001::CollisionAction(CLASS_TYPE Type,int Num)
{
	int a = 0;

	for(int i = 0;i < m_ShotNumMax;i++)
	{
		if(m_pBulletInfo[i].ExistJudge)
		{
			if(a == Num)
			{
				CPhaseGame::GetExplosionPointer(0)->ExplosionSet3Set(m_pBulletInfo[i].Pos);
				Bullet001ShotUninit(i);
				break;
			}
			a++;
		}

	}
}

//◇-----------------------------------◇
//CBullet001のあたり判定のチェックシート
//◇-----------------------------------◇
bool CBullet001::CollisionTargetSheet(CLASS_TYPE Type)
{
	switch(Type)
	{
	case CTYPE_ENEMY:	return true;break;

	default:			return false;break;
	}
}

//◇-----------------------------------◇
//CBullet001のクリエイト
//◇-----------------------------------◇
CBullet001 *CBullet001::Create()
{
	CBullet001 *pBullet001;
	pBullet001 = new CBullet001;

	pBullet001->Init();

	return pBullet001;
}


//◇-----------------------------------◇
//CBullet001の発射処理
//◇-----------------------------------◇
void CBullet001::Bullet001Shot(D3DXVECTOR3 ShotPos,D3DXVECTOR3 TargetPos)
{
	if(m_pBulletInfo[BulletNumCounter].ExistJudge == false)
	{
		PlaySound(SOUND_LABEL_WeaponShot);

		m_pBulletInfo[BulletNumCounter].Pos = ShotPos;
		m_pBulletInfo[BulletNumCounter].StartPos = ShotPos;
		m_pBulletInfo[BulletNumCounter].GoVec = TargetPos - ShotPos;

		D3DXVec3Normalize(&m_pBulletInfo[BulletNumCounter].GoVec,
							&m_pBulletInfo[BulletNumCounter].GoVec);

		for(int i = 0;i < m_ShotTexNum;i++)
		{
			m_pBulletInfo[BulletNumCounter].PolygonNum[i] = 
							SetPolygon(m_pBulletInfo[BulletNumCounter].StartPos - m_pBulletInfo[BulletNumCounter].GoVec * (i * m_TexLength),
							D3DXVECTOR3(0.0f,0.0f,0.0f),m_TexSize,m_TexSize);

			ParticleSetColor(m_pBulletInfo[BulletNumCounter].PolygonNum[i],D3DXCOLOR(1.0f,1.0f,0.0f,1.0f));
		}



		m_pBulletInfo[BulletNumCounter].ExistJudge = true;
		m_pBulletInfo[BulletNumCounter].Life = 0;

		BulletNumCounter++;

		if(BulletNumCounter >= m_ShotNumMax)
			BulletNumCounter = 0;
	}
}

//◇-----------------------------------◇
//CBullet001の弾の消去処理
//◇-----------------------------------◇
void CBullet001::Bullet001ShotUninit(int Num)
{
	if(Num >= m_ShotNumMax)
	{
		return;
	}

	if(m_pBulletInfo[Num].ExistJudge)
	{
		m_pBulletInfo[Num].ExistJudge = false;
		m_pBulletInfo[Num].Life = 0;

		for(int i = 0;i < m_ShotTexNum;i++)
		{
			m_pBulletInfo[Num].PolygonNum[i] = ParticleUninitPosition(m_pBulletInfo[Num].PolygonNum[i]);
		}
	}
}


