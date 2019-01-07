//◇-------------------------------------------------------------------------◇
//
//	File:CTargetUIのファイル[CTargetUI.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CTargetUI.h"
#include "CCamera.h"
#include "CManager.h"
#include "CPlayerModel.h"
#include "CItemList.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CTargetUIのコンストラクタ
//◇-----------------------------------◇
CTargetUI::CTargetUI(int nPriority) : CSceneBillboard(nPriority)
{
	float TexSize = 400.0f;

	TextureWidth = TexSize;
	TextureHeight = TexSize;

	m_DrawJudge = true;
}

//◇-----------------------------------◇
//CTargetUIのデストラクタ
//◇-----------------------------------◇
CTargetUI::~CTargetUI()
{

}

//◇-----------------------------------◇
//CTargetUIの更新処理
//◇-----------------------------------◇
void CTargetUI::Update(void)
{
	float TargetFade_Start = 3000.0f;			//どの距離からターゲットが薄れていくか
	float TargetFade_End = 1500.0f;				//


	CScene *irekoScene = NULL;

	CScene::SearchLinkList(&irekoScene,CTYPE_PLAYERMODEL);

	if(irekoScene != NULL)
	{
		//ダウンキャスト
		CPlayerModel *pPlayer = (CPlayerModel*)irekoScene;
		CScene *pTargetEnemy = pPlayer->GetTargetEnemyPointer();

		if(pTargetEnemy != NULL)
		{
			m_DrawJudge = true;
			
			//ターゲットポスの設定
			D3DXVECTOR3 a = pTargetEnemy->GetCollisionCenterPos(0) - CManager::GetCameraPointer()->GetCameraP();
			D3DXVec3Normalize(&a,&a);

			m_Pos = pTargetEnemy->GetCollisionCenterPos(0) - (a * pTargetEnemy->GetCollisionRadius(0) * 2);



			//距離に応じてＵＩを透明にする
			float Length = CItemList::GetLengthSimple(pPlayer->GetPosition() - pTargetEnemy->GetCollisionCenterPos(0));

			if(Length <= TargetFade_Start)
			{
				if(Length <= TargetFade_End)
				{
					m_DrawJudge = false;
				}
				else
				{
					m_DrawJudge = true;

					//ターゲット透明度計算
					Length -= TargetFade_End;
					float Alpha = Length / (TargetFade_Start - TargetFade_End);

					SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,Alpha));
				}
			}
		}
		else	//目標が存在しなければ描画しない
		{
			m_DrawJudge = false;
		}
	}
}

//◇----------------------------------◇
//CTargetUIの描画処理
//◇----------------------------------◇
void CTargetUI::Draw(void)
{
	//****デバイス取得****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATRIX mtxView;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスの取得
	mtxView = CManager::GetCameraPointer()->GetMtxView();

	//逆行列を求める
	D3DXMatrixInverse(&m_mtxWorld,NULL,&mtxView);

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//****ワールドの設定****
	D3DXMatrixScaling(&mtxScl,m_Scl.x,m_Scl.y,m_Scl.z);					//スケールを反映
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

	//****位置の設定****
	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);		//位置を反映
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);

	pDevice -> SetTransform(D3DTS_WORLD,&m_mtxWorld);	//設定

	if(m_DrawJudge)
	{
		//これでライティングを無効にする
		pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE ,FALSE);

		//3Dポリゴンの描画
		pDevice->SetStreamSource(0,m_VtxBuffer,0,sizeof(VERTEX_3D));
		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);
		//テクスチャの設定
		pDevice->SetTexture(0,m_Texture);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE ,TRUE);
		pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);
	}
}

//◇----------------------------------◇
//CTargetUIのクリエイト
//◇----------------------------------◇
CTargetUI *CTargetUI::Create(LPCTSTR TextureName)
{
	CTargetUI *pTargetUI;
	pTargetUI = new CTargetUI;

	pTargetUI->m_TextureName = TextureName;
	
	pTargetUI->Init();

	return pTargetUI;
}
