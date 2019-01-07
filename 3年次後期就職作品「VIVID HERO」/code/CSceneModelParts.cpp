//◇-------------------------------------------------------------------------◇
//
//	File	:CSceneModelPartsファイル[CSceneModelParts.cpp]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CSceneModelParts.h"
#include "CManager.h"
#include "CTextureManager.h"

//◇----------------------------------◇
//コンストラクタ
//◇----------------------------------◇
CSceneModelParts::CSceneModelParts(int nPriority) : CScene(nPriority)
{
	m_Type = CTYPE_SCENEMODELPARTS;

	//****位置、角度、スケールの初期化****
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	for(int i = 0;i < 256;i++)
	{
		m_Texture[i] = NULL;
	}

	m_MotionParentPartsRot = D3DXVECTOR3(0.0f,0.0f,0.0f);

}

//◇----------------------------------◇
//デストラクタ
//◇----------------------------------◇
CSceneModelParts::~CSceneModelParts()
{

}

//◇----------------------------------◇
//CSceneModelPartsの初期化処理
//◇----------------------------------◇
HRESULT CSceneModelParts::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	m_pSceneModelMotion = CSceneModelMotion::Create(m_ModelTxtName);
	m_pModelParts = m_pSceneModelMotion->GetPart_Info();

	m_pmtxWorld = new D3DXMATRIX[m_pSceneModelMotion->GetPart_Num()];

	for(int i = 0;i < m_pSceneModelMotion->GetPart_Num();i++)
	{
		//***テクステャの読み込み***
		if(m_pModelParts[i].TexName[0] != NULL && strcmp(m_pModelParts[i].TexName,"NULL") != 0)
		{
			m_Texture[i] = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_pModelParts[i].TexName));
		}

		//モデルのロード
		if(m_pModelParts[i].ModelName != NULL)
		{
			m_XFile_Info[i] = CManager::GetXFileManagerPointer()->GetXFile(CManager::GetXFileManagerPointer()->Load(m_pModelParts[i].ModelName));
		}
	}

	return S_OK;
}

//◇----------------------------------◇
//CSceneModelPartsの終了処理
//◇----------------------------------◇
void CSceneModelParts::Uninit(void)
{
	Release();

	SAFE_DELETE_ARRY(m_pmtxWorld);
}

//◇----------------------------------◇
//CSceneModelPartsの更新処理
//◇----------------------------------◇
void CSceneModelParts::Update(void)
{

}

//◇-----------------------------------◇
//CSceneModelPartsの描画処理
//◇-----------------------------------◇
void CSceneModelParts::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//マットのデフォルト

	MatrixUpdate();
	for(int i = 0;i < m_pSceneModelMotion->GetPart_Num();i++)
	{
		pDevice -> SetTransform(D3DTS_WORLD,&m_pmtxWorld[i]);	//設定

		//モデルの描画
		pDevice -> GetMaterial(&matDef);
		pMat = (D3DXMATERIAL*)m_XFile_Info[i].BuffMat->GetBufferPointer();

		for(int nCntMat = 0;nCntMat < (int)m_XFile_Info[i].numMat;nCntMat++)
		{
			pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
			pDevice -> SetTexture(0,m_Texture[i]);
			m_XFile_Info[i].Mesh->DrawSubset(nCntMat);
		}

		pDevice -> SetMaterial(&matDef);
	}

}

//◇----------------------------------◇
//CSceneModelPartsのマトリックスの座標移動
//◇----------------------------------◇
void CSceneModelParts::MatrixUpdate()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXVECTOR3 Pos,Rot,Scl;

	for(int i = 0;i < m_pSceneModelMotion->GetPart_Num();i++)
	{
		if(m_pModelParts[i].ParentNumber == -1)
		{
			Pos = m_Pos + m_pModelParts[i].Pos;
			Rot = m_Rot + m_pModelParts[i].Rot;
			Scl = m_Scl + m_pModelParts[i].Scl;

			m_MotionParentPartsRot = Rot;
		}
		else
		{
			Pos = m_pModelParts[i].Pos;
			Rot = m_pModelParts[i].Rot;
			Scl = m_pModelParts[i].Scl;
		}

		//****ワールドの設定****
		D3DXMatrixIdentity(&m_pmtxWorld[i]);
		D3DXMatrixScaling(&mtxScl,Scl.x,
									Scl.y,
									Scl.z);	//スケールを反映

		D3DXMatrixMultiply(&m_pmtxWorld[i],&m_pmtxWorld[i],&mtxScl);

		//****その他の設定****
		D3DXMatrixRotationYawPitchRoll(&mtxRot,Rot.y,
										Rot.x,
										Rot.z);		//ヨ－　ピッチ　ロール

		D3DXMatrixMultiply(&m_pmtxWorld[i],&m_pmtxWorld[i],&mtxRot);

		D3DXMatrixTranslation(&mtxTranslate,Pos.x,Pos.y,Pos.z);		//位置を反映
		D3DXMatrixMultiply(&m_pmtxWorld[i],&m_pmtxWorld[i],&mtxTranslate);



		if(m_pModelParts[i].ParentNumber != -1)
		{
			D3DXMatrixMultiply(&m_pmtxWorld[i],&m_pmtxWorld[i],&m_pmtxWorld[m_pModelParts[i].ParentNumber]);
		}
	}
}
//◇----------------------------------◇
//CSceneModelPartsのセットポジションその１
//◇----------------------------------◇
void  CSceneModelParts::SetPosition(float x,float y,float z)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}

//◇----------------------------------◇
//CSceneModelPartsのセットポジションその２
//◇----------------------------------◇
void  CSceneModelParts::SetPosition(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//◇----------------------------------◇
//CSceneModelPartsのゲットポジション
//◇----------------------------------◇
D3DXVECTOR3  CSceneModelParts::GetPosition(void)
{
	return m_Pos;
}

//◇----------------------------------◇
//CSceneModelPartsのセットローテーションその１
//◇----------------------------------◇
void CSceneModelParts::SetRotation(float x,float y,float z)
{
	m_Rot.x = x;
	m_Rot.y = y;
	m_Rot.z = z;
}

//◇----------------------------------◇
//CSceneModelPartsのセットローテーションその2
//◇----------------------------------◇
void CSceneModelParts::SetRotation(D3DXVECTOR3 rot)
{
	m_Rot.x = rot.x;
	m_Rot.y = rot.y;
	m_Rot.z = rot.z;
}

//◇----------------------------------◇
//CSceneModelPartsのゲットローテーション
//◇----------------------------------◇
D3DXVECTOR3 CSceneModelParts::GetRotation(void)
{
	return m_Rot;
}

//◇----------------------------------◇
//CSceneModelPartsのセットタイプ
//◇----------------------------------◇
void CSceneModelParts::SetType(int nType)
{

}


//◇----------------------------------◇
//CSceneModelPartsDの	クリエイト(引数付)
//TextureName:テクスチャの名前
//PosX,PosY,PosZ:テクスチャの座標
//◇----------------------------------◇
CSceneModelParts *CSceneModelParts::Create(LPCTSTR ModelTxtName,D3DXVECTOR3 Pos)
{
	CSceneModelParts *pCSceneModelParts;
	pCSceneModelParts = new CSceneModelParts;

	pCSceneModelParts->m_ModelTxtName = ModelTxtName;
	pCSceneModelParts->m_Pos = Pos;

	pCSceneModelParts->Init();

	return pCSceneModelParts;
}
