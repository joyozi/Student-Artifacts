//◇-------------------------------------------------------------------------◇
//
//	フェイドcppファイル[.fadecpp]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include"main.h"
#include "fade.h"
#include "input.h"
#include "game.h"
#include "sound.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 f_pTexturePolygon = NULL;
LPDIRECT3DVERTEXBUFFER9 f_pVtxBuffPolygon = NULL;
VERTEX_2D *f_pVtx;		//画像の座標のポインタ
//FADE g_fade = FADE_IN;	//fade.hに移動
D3DXCOLOR g_colorFade;
FADE g_fade = FADE_IN;

MODE g_modeNext;

//◇-------------------------------------------------------------------------◇
//フェイドの初期化処理
//◇-------------------------------------------------------------------------◇
void InitFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&f_pVtxBuffPolygon,NULL);

	//背景画像の情報登録
	f_pVtxBuffPolygon->Lock(0,0,(void**)&f_pVtx,0);

	//頂点情報の設定
	f_pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	f_pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
	f_pVtx[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
	f_pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);

	f_pVtx[0].rhw = 1.0f;
	f_pVtx[1].rhw = 1.0f;
	f_pVtx[2].rhw = 1.0f;
	f_pVtx[3].rhw = 1.0f;

	f_pVtx[0].col = D3DCOLOR_RGBA(255,255,255,0);
	f_pVtx[1].col = D3DCOLOR_RGBA(255,255,255,0);
	f_pVtx[2].col = D3DCOLOR_RGBA(255,255,255,0);
	f_pVtx[3].col = D3DCOLOR_RGBA(255,255,255,0);

	f_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	f_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	f_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	f_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);

	f_pVtxBuffPolygon->Unlock();

}
//-------------------------------------
//フェイド終了処理
//-------------------------------------
void UninitFade(void)
{
	//バッファの処理
	if(f_pVtxBuffPolygon != NULL)
	{
		f_pVtxBuffPolygon->Release();
		f_pVtxBuffPolygon = NULL;
	}
	
	//テクスチャの処理
	if(f_pTexturePolygon != NULL)
	{
		f_pTexturePolygon->Release();
		f_pTexturePolygon = NULL;
	}
}
//-------------------------------------
//フェイドの更新処理
//-------------------------------------
void UpdateFade(void)
{
	static float color = 1.2f;
//	static FADE fadejudge = FADE_NONE;	//FADE_NONEのときのINOUTどっちに切り替えるかの前準備 ENTERを押したときにどっちに行くか

	switch(g_fade)
	{
	case FADE_NONE:

		switch(GetMode())
			{
			case MODE_TITTLE:
			case MODE_RESULT:

				//エンターを押したらフェードアウトが始まります
				if(GetKeyboardTrigger(DIK_RETURN) == true)
				{
					SetFade(FADE_OUT);
				}

				break;
				
			default:
				break;
			}
		
		break;

	case FADE_IN:
		color -= FADE_TIME;

		if(color < 0.0f)
		{
			SetFade(FADE_NONE);	//FADENONEのときのINOUTどっちに切り替えるかの前準備
		}
		break;

	case FADE_OUT:
		color += FADE_TIME;

		//フェードアウトの終了判定
		if(color > 1.0f)
		{	
			SetFade(FADE_IN);	//FADENONEのときのINOUTどっちに切り替えるかの前準備
			//ポーズ時に変更を要求されたらこれをポーズ時の選択肢の内容を適用する
			if(GetPause() == true)
			{
				SetMode(g_modeNext);
			}
			//フェードアウトが終了になったら画面遷移
			switch(GetMode())
			{
			case MODE_TITTLE:
				SetMode(MODE_GAME);
				break;

			case MODE_GAME:
				SetMode(MODE_RESULT);
				break;

			case MODE_RESULT:
				SetMode(MODE_TITTLE);
				break;

			case MODE_MAX:
				break;
			}
		}
		break;
	}	//switch(g_fade)終了


	g_colorFade = D3DXCOLOR(0.0f,0.0f,0.0f,color);

	//背景画像の情報登録
	f_pVtxBuffPolygon->Lock(0,0,(void**)&f_pVtx,0);

	//頂点情報の設定
	f_pVtx[0].col = g_colorFade;
	f_pVtx[1].col = g_colorFade;
	f_pVtx[2].col = g_colorFade;
	f_pVtx[3].col = g_colorFade;

	f_pVtxBuffPolygon->Unlock();

}
//-------------------------------------
//フェイドの描画処理
//-------------------------------------
void DrawFade(void)
{
	//背景の描画
	GetDevice()->SetStreamSource(0,f_pVtxBuffPolygon,0,sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	GetDevice()->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	GetDevice()->SetTexture(0,f_pTexturePolygon);
	//ポリゴンの描画
	GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	
}

//-------------------------------------
//セットフェイド処理
//-------------------------------------
void SetFade(FADE fade)
{
	g_fade = fade;

	switch(g_fade)
	{
		case FADE_NONE:
			break;
		case FADE_IN:
			break;
		case FADE_OUT:
			break;
		case FADE_MAX:
			break;
	}
}


FADE GetFade(void)
{
	return(g_fade);
}

//modeNextには多分表示したいモードのひとつ前を入れる?
void SetFade_2(FADE fade,MODE modeNext)
{
	g_fade = fade;

	g_modeNext = modeNext;
	
}