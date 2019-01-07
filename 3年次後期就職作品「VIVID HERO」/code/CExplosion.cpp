//◇-------------------------------------------------------------------------◇
//
//	File:CExplosionのファイル[CExplosion.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CExplosion.h"
#include "CTextureManager.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CExplosionのコンストラクタ
//◇-----------------------------------◇
CExplosion::CExplosion(int nPriority) : CSceneBillboard(nPriority)
{
	m_Type = CTYPE_EXPLOSION;

	m_CounterAnim = 0;
	m_PatternAnim = 0;

	m_Texture = NULL;
	m_VtxBuffer = NULL;
}

//◇-----------------------------------◇
//CExplosionの初期化処理
//ちょっとtexの関係で引き継げない
//◇-----------------------------------◇
HRESULT CExplosion::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	m_Texture = NULL;
	m_VtxBuffer = NULL;

	//***テクステャの読み込み***
	m_Texture = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_TextureName));

	//***頂点情報の設定***
	//****頂点バッファの設定****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_VtxBuffer,NULL);

	//背景画像の情報登録
	m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

	//頂点情報の設定
	m_pVtx[0].pos = D3DXVECTOR3(-TextureWidth / 2,TextureHeight / 2,0.0f);
	m_pVtx[1].pos = D3DXVECTOR3(TextureWidth / 2,TextureHeight / 2,0.0f);
	m_pVtx[2].pos = D3DXVECTOR3(-TextureWidth / 2,-TextureHeight / 2,0.0f);
	m_pVtx[3].pos = D3DXVECTOR3(TextureWidth / 2,-TextureHeight / 2,0.0f);

	//****何かの設定*****
	m_pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	m_pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	m_pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	m_pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	m_pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	m_pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	m_pVtx[1].tex = D3DXVECTOR2((1.0f / EXPLOSION_SEPARATE_NUM),0.0f);
	m_pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	m_pVtx[3].tex = D3DXVECTOR2((1.0f / EXPLOSION_SEPARATE_NUM),1.0f);

	m_VtxBuffer->Unlock();

	return S_OK;

}

//◇-----------------------------------◇
//CExplosionの更新処理
//◇-----------------------------------◇
void CExplosion::Update(void)
{
	//爆発の番号ごとの時間の計算をする
	m_CounterAnim++;

	//右辺以上になったら次のコマに移る
	if(m_CounterAnim >= EXPLOSION_COUNT)
	{
		//次の小間に移る
		m_PatternAnim++;
		//最初からカウントする
		m_CounterAnim = 0;

		//背景画像の情報登録
		m_VtxBuffer->Lock(0,0,(void**)&m_pVtx,0);

		//頂点情報の設定
		m_pVtx[0].tex = D3DXVECTOR2((1.0f / EXPLOSION_SEPARATE_NUM) * m_PatternAnim,0.0f);
		m_pVtx[1].tex = D3DXVECTOR2((1.0f / EXPLOSION_SEPARATE_NUM) * (m_PatternAnim + 1),0.0f);
		m_pVtx[2].tex = D3DXVECTOR2((1.0f / EXPLOSION_SEPARATE_NUM) * m_PatternAnim,1.0f);
		m_pVtx[3].tex = D3DXVECTOR2((1.0f / EXPLOSION_SEPARATE_NUM) * (m_PatternAnim + 1),1.0f);

		m_VtxBuffer->Unlock();

		//最後まで表示したら終わりにする
		if(m_PatternAnim >= EXPLOSION_SEPARATE_NUM)
		{
			Uninit();
		}

	}
}

//◇----------------------------------◇
//CSceneBillboardの	クリエイト(引数付)
//TextureName:テクスチャの名前
//PosX,PosY,PosZ:テクスチャの座標
//TexWidth,TexHeight:テクスチャのタテヨコの長さ
//◇----------------------------------◇
CExplosion *CExplosion::Create(LPCTSTR TextureName,float PosX,float PosY,float PosZ,float TexWidth,float TexHeight)
{
	CExplosion *pExplosion;
	pExplosion = new CExplosion;

	pExplosion->m_TextureName	 = TextureName;
	pExplosion->m_Pos			 = D3DXVECTOR3(PosX,PosY,PosZ);
	pExplosion->TextureWidth	 = TexWidth;
	pExplosion->TextureHeight	 = TexHeight;
	
	pExplosion->Init();

	return pExplosion;
}
