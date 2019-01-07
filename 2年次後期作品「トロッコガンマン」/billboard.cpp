//◇-------------------------------------------------------------------------◇
//
//	File	:ビルボードファイル[billboard.cpp]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "billboard.h"
#include "camera.h"
#include "input.h"
#include "light.h"
//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 g_pTextureBillboard;			//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard;	//

D3DXMATRIX g_mtxProjectionBillboard;				//プロジェクションマトリックス
D3DXMATRIX g_mtxViewBillboard;						//ビューマトリックス
D3DXMATRIX g_mtxWorldBillboard;						//ワールドマトリックス

D3DXVECTOR3 g_posBillboard;						//位置
D3DXVECTOR3 g_rotBillboard;						//向き
D3DXVECTOR3 g_sclBillboard;						//大きさ（基本変えない）
D3DXVECTOR3 g_posBillboardP;					//カメラの視点
D3DXVECTOR3 g_posBillboardR;					//カメラの注視点
D3DXVECTOR3 g_posBillboardU;					//カメラの上方向ベクトル

//◇-------------------------------------------------------------------------◇
//初期化処理
//◇-------------------------------------------------------------------------◇
void InitBillboard(void)
{
	//****位置、角度、スケールの初期化****
	g_posBillboard = D3DXVECTOR3(0.0f,100.0f,200.0f);
	g_rotBillboard = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_sclBillboard = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//***カメラの初期化***
	g_posBillboardP = D3DXVECTOR3(0.0f,100.0f,-150.0f);		//カメラの視点
	g_posBillboardR = D3DXVECTOR3(0.0f,0.0f,0.0f);			//カメラの注視点
	g_posBillboardU = D3DXVECTOR3(0.0f,1.0f,0.0f);			//カメラの上方向ベクトル

	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	VERTEX_3D *pVtx;

	//***テクステャの読み込み***
	D3DXCreateTextureFromFile(GetDevice(),"./data/TEXTURE/oumu.png",&g_pTextureBillboard);

	//***頂点情報の設定***

	//****頂点バッファの設定****
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D))*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffBillboard,NULL);

	//***頂点データをロック***
	g_pVtxBuffBillboard->Lock(0,0,(void**)&pVtx,0);

	//****頂点の位置の設定****
	pVtx[0].pos = D3DXVECTOR3(-30,20,0);
	pVtx[1].pos = D3DXVECTOR3(30,20,0);
	pVtx[2].pos = D3DXVECTOR3(-30,-20,0);
	pVtx[3].pos = D3DXVECTOR3(30,-20,0);

	//****何かの設定*****
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	//****カラーの設定****
	pVtx[0].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtx[1].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtx[2].col = D3DCOLOR_RGBA(255,255,255,55);
	pVtx[3].col = D3DCOLOR_RGBA(255,255,255,55);

	//****texの設定****
	pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0,1.0);


	//****頂点データのロック解除
	g_pVtxBuffBillboard->Unlock();
}

//◇---------------------------------◇
//終了処理
//◇---------------------------------◇
void UninitBillboard(void)
{
	if(g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
	
		//テクスチャの処理
	if(g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
}
//◇---------------------------------◇
//の更新処理
//◇---------------------------------◇
void UpdateBillboard(void)
{
	static D3DXVECTOR3 RotBillboard;

/*
	//****************************カメラの操作*************************************
	//===カメラの前移動=============
	//==============================
	if(GetKeyboardPress(DIK_UP) == true)
	{
		g_posBillboard.x += sinf(GetRotCamera().y) * BILLBOARD_MOVE;
		g_posBillboard.z += cosf(GetRotCamera().y) * BILLBOARD_MOVE;
	}
	
	//===カメラの後ろ移動===========
	//==============================
	if(GetKeyboardPress(DIK_DOWN) == true)
	{
		g_posBillboard.x -= sinf(GetRotCamera().y) * BILLBOARD_MOVE;
		g_posBillboard.z -= cosf(GetRotCamera().y) * BILLBOARD_MOVE;
	}


	//===カメラの左移動=============
	//==============================
	if(GetKeyboardPress(DIK_LEFT) == true)
	{
		g_posBillboard.x -= cosf(GetRotCamera().y) * BILLBOARD_MOVE;
		g_posBillboard.z += sinf(GetRotCamera().y) * BILLBOARD_MOVE;
	}
	//===カメラの右移動=============
	//==============================
	if(GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_posBillboard.x += cosf(GetRotCamera().y) * BILLBOARD_MOVE;
		g_posBillboard.z -= sinf(GetRotCamera().y) * BILLBOARD_MOVE;
	}
*/

}

//◇---------------------------------◇
//の描画処理
//◇---------------------------------◇
void DrawBillboard(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;	
	D3DXMATRIX mtxView;				//ビューマトリックス
	
	//****デバイス取得****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	mtxView = GetMtxView();

	//------ワールドマトリックスとかの設定--------------------------------------------------------------

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldBillboard);

	//逆行列を求める
	D3DXMatrixInverse(&g_mtxWorldBillboard,NULL,&mtxView);

	g_mtxWorldBillboard._41 = 0.0f;
	g_mtxWorldBillboard._42 = 0.0f;
	g_mtxWorldBillboard._43 = 0.0f;

	//****ワールドの設定****
	D3DXMatrixScaling(&mtxScl,g_sclBillboard.x,g_sclBillboard.y,g_sclBillboard.z);			//スケールを反映
	D3DXMatrixMultiply(&g_mtxWorldBillboard,&g_mtxWorldBillboard,&mtxScl);

/*	ここに付け加えたら後から使えるけど今は使えない現象が起こる
	//逆行列を元に戻す
	D3DXMatrixInverse(&g_mtxWorldBillboard,NULL,&mtxView);
*/

	//****その他の設定****
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotBillboard.y,g_rotBillboard.x,g_rotBillboard.z);		//ヨ－　ピッチ　ロール

	D3DXMatrixMultiply(&g_mtxWorldBillboard,&g_mtxWorldBillboard,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,g_posBillboard.x,g_posBillboard.y,g_posBillboard.z);	//位置を反映
	D3DXMatrixMultiply(&g_mtxWorldBillboard,&g_mtxWorldBillboard,&mtxTranslate);

	pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldBillboard);	//設定
	

	//------------------------------------------------------------------------------------------

	//****αテストの開始****
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

/*

D3DCMP_NEVER　でなくなっちゃう
D3DCMP_LESS　αブレンドの部分が出てくる
D3DCMP_EQUAL　同じ値だったら出てくる
D3DCMP_LESSEQUAL　同じ値だと出る。それ以外だとαブレンドの部分が出る？
D3DCMP_GREATER　値以上だと出てくる
D3DCMP_NOTEQUAL　同じ値だと出てこない
D3DCMP_GREATEREQUAL 値以上だと出てくる？
D3DCMP_ALWAYS 全部出てくる


*/
	//----------------3Dポリゴンの描画----------------------------------------------------------

	//頂点バッファをバインド
	pDevice->SetStreamSource(0,g_pVtxBuffBillboard,0,sizeof(VERTEX_3D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0,g_pTextureBillboard);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//------------------------------------------------------------------------------------------

	//****αテストの終了****
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
}

D3DXVECTOR3 GetPosBillboard(void)
{
	return g_posBillboard;
}