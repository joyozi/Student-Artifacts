//◇-------------------------------------------------------------------------◇
//
//	File	:CSceneXファイル[CSceneX.cpp]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CSceneX.h"
#include "CManager.h"
#include "CTextureManager.h"

//◇----------------------------------◇
//コンストラクタ
//◇----------------------------------◇
CSceneX::CSceneX(int nPriority) : CScene(nPriority)
{
	//****位置、角度、スケールの初期化****
	m_Pos			 = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot			 = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl			 = D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_Texture		 = NULL;
	m_TextureName	 = NULL;
	m_XfileName		 = NULL;
}

//◇----------------------------------◇
//デストラクタ
//◇----------------------------------◇
CSceneX::~CSceneX()
{

}

//◇----------------------------------◇
//CSceneXの初期化処理
//◇----------------------------------◇
HRESULT CSceneX::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//***テクステャの読み込み***
	if(m_TextureName != NULL)
	{
		m_Texture = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_TextureName));
	}

	//モデルのロード
	m_XFile_Info = CManager::GetXFileManagerPointer()->GetXFile(CManager::GetXFileManagerPointer()->Load(m_XfileName));

	MatrixUpdate();

	return S_OK;
}

//◇----------------------------------◇
//CSceneXの終了処理
//◇----------------------------------◇
void CSceneX::Uninit(void)
{
	Release();
}

//◇----------------------------------◇
//CSceneXの更新処理
//◇----------------------------------◇
void CSceneX::Update(void)
{
	MatrixUpdate();
}

//◇----------------------------------◇
//CSceneXの描画処理
//◇----------------------------------◇
void CSceneX::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//マットのデフォルト

	pDevice -> SetTransform(D3DTS_WORLD,&m_mtxWorld);	//設定

	//モデルの描画
	pDevice -> GetMaterial(&matDef);
	pMat = (D3DXMATERIAL*)m_XFile_Info.BuffMat->GetBufferPointer();

	for(int nCntMat = 0;nCntMat < (int)m_XFile_Info.numMat;nCntMat++)
	{
		pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
		pDevice -> SetTexture(0,m_Texture);
		m_XFile_Info.Mesh -> DrawSubset(nCntMat);
	}
	pDevice -> SetMaterial(&matDef);
}

//◇----------------------------------◇
//CSceneXのマトリックスチェンジ
//◇----------------------------------◇
void  CSceneX::MatrixUpdate()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&mtxScl,m_Scl.x,m_Scl.y,m_Scl.z);	//スケールを反映

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_Rot.y,m_Rot.x,m_Rot.z);		//ヨ－　ピッチ　ロール

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);		//位置を反映

	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
}

//◇----------------------------------◇
//CSceneXのセットポジションその１
//◇----------------------------------◇
void  CSceneX::SetPosition(float x,float y,float z)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}

//◇----------------------------------◇
//CSceneXのセットポジションその２
//◇----------------------------------◇
void  CSceneX::SetPosition(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//◇----------------------------------◇
//CSceneXのゲットポジション
//◇----------------------------------◇
D3DXVECTOR3  CSceneX::GetPosition(void)
{
	return m_Pos;
}

//◇----------------------------------◇
//CSceneXのセットローテーションその１
//◇----------------------------------◇
void CSceneX::SetRotation(float x,float y,float z)
{
	m_Rot.x = x;
	m_Rot.y = y;
	m_Rot.z = z;
}

//◇----------------------------------◇
//CSceneXのセットローテーションその2
//◇----------------------------------◇
void CSceneX::SetRotation(D3DXVECTOR3 rot)
{
	m_Rot.x = rot.x;
	m_Rot.y = rot.y;
	m_Rot.z = rot.z;
}

//◇----------------------------------◇
//CSceneXのゲットローテーション
//◇----------------------------------◇
D3DXVECTOR3 CSceneX::GetRotation(void)
{
	return m_Rot;
}

//◇----------------------------------◇
//CSceneXのセットタイプ
//◇----------------------------------◇
void CSceneX::SetType(int nType)
{
	m_Type = CTYPE_SCENEX;
}


//◇----------------------------------◇
//CSceneXDの	クリエイト(引数付)
//TextureName:テクスチャの名前
//PosX,PosY,PosZ:テクスチャの座標
//◇----------------------------------◇
CSceneX *CSceneX::Create(LPCTSTR XfileName,D3DXVECTOR3 Pos)
{
	CSceneX *pSceneX;
	pSceneX = new CSceneX;

	pSceneX->m_XfileName	 = XfileName;
	pSceneX->m_Pos			 = Pos;
	
	pSceneX->Init();

	return pSceneX;
}
