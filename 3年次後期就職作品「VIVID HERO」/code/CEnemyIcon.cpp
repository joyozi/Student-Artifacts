//◇-------------------------------------------------------------------------◇
//
//	File:CEnemyIconのファイル[CEnemyIcon.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CEnemyIcon.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CEnemyIconのコンストラクタ
//◇-----------------------------------◇
CEnemyIcon::CEnemyIcon(int nPriority) : CScene2D(nPriority)
{
	m_DrawJudge = false;
}

//◇-----------------------------------◇
//CEnemyIconのデストラクタ
//◇-----------------------------------◇
CEnemyIcon::~CEnemyIcon()
{

}

//◇-----------------------------------◇
//CEnemyIconの描画処理
//◇-----------------------------------◇
void CEnemyIcon::Draw(void)
{
	if(m_DrawJudge)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = GetDevice();

		//背景の描画
		pDevice->SetStreamSource(0,m_VtxBuffer,0,sizeof(VERTEX_2D));
		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		//テクスチャの設定
		pDevice->SetTexture(0,m_Texture);
		//テクスチャの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	}
}

CEnemyIcon *CEnemyIcon::Create(LPCTSTR TextureName,D3DXVECTOR3 Pos,D3DXVECTOR3 Size)
{
	CEnemyIcon *pEnemyIcon;
	pEnemyIcon = new CEnemyIcon;

	pEnemyIcon->m_TextureName = TextureName;
	pEnemyIcon->m_Pos = Pos;
	pEnemyIcon->TextureWidth = Size.x;
	pEnemyIcon->TextureHeight = Size.y;
	
	pEnemyIcon->Init();

	return pEnemyIcon;

}
