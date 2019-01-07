//◇-------------------------------------------------------------------------◇
//
//	File	:弾ファイル[bullet.cpp]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "bullet.h"
#include "camera.h"
#include "input.h"
#include "model.h"
#include "obstacle.h"
#include "gameUI.h"
#include "explosion.h"
#include "enemy_01.h"
#include "sound.h"
#include "score.h"

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//グローバル変数
//◇-------------------------------------------------------------------------◇
LPDIRECT3DTEXTURE9 g_pTextureBullet;						//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet;					//

D3DXMATRIX g_mtxWorldBullet;								//ワールドマトリックス
D3DXVECTOR3 g_posBullet[BULLET_MAX];						//位置
D3DXVECTOR3 g_rotBullet[BULLET_MAX];						//向き
D3DXVECTOR3 g_sclBullet[BULLET_MAX];						//大きさ（基本変えない）

bool bullet_hassha[BULLET_MAX];								//発射の正否
D3DXMATRIX posBullet_Original[BULLET_MAX];					//タマの発射時の腕の位置を保存しておく。後に位置が変わって依存されないため
PLAYER_MODE p_Bullet_shunkan[BULLET_MAX];					//弾が撃たれた瞬間の本体の位置、状態の保存をする変数
int BulletUpdate_num;										//弾の更新に使う数。

//◇-------------------------------------------------------------------------◇
//バレット初期化処理
//◇-------------------------------------------------------------------------◇
void InitBullet(void)
{
	//入れるかわからない
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	
	VERTEX_3D *pVtx;

	for(int nCnt = 0;nCnt < BULLET_MAX;nCnt++)
	{
		//左右の弾の位置の初期化
		//BAEM_TEXTURE_NUMのときは左手から出る BAEM_TEXTURE_NUM*2のときは右手
		if(nCnt % (BAEM_TEXTURE_NUM*2) >= 0 && nCnt % (BAEM_TEXTURE_NUM*2) < BAEM_TEXTURE_NUM)
		{
			//****位置、角度、スケールの初期化****
			g_posBullet[nCnt] = D3DXVECTOR3(-5.0f,2.0f,38.0f);
			g_rotBullet[nCnt] = D3DXVECTOR3(0.0f,0.0f,0.0f);
			g_sclBullet[nCnt] = D3DXVECTOR3(1.0f,1.0f,1.0f);
		}
		else if(nCnt % (BAEM_TEXTURE_NUM*2) >= BAEM_TEXTURE_NUM && nCnt % (BAEM_TEXTURE_NUM*2) < BAEM_TEXTURE_NUM*2)
		{
			//****位置、角度、スケールの初期化****
			g_posBullet[nCnt] = D3DXVECTOR3(5.0f,2.0f,38.0f);
			g_rotBullet[nCnt] = D3DXVECTOR3(0.0f,0.0f,0.0f);
			g_sclBullet[nCnt] = D3DXVECTOR3(1.0f,1.0f,1.0f);
		}
		//弾発射の初期化
		bullet_hassha[nCnt] = false;

		//弾を撃った瞬間の本体の情報の初期化
		p_Bullet_shunkan[nCnt] = GetModelOriginal();
	}
	
	BulletUpdate_num = 0;

	g_pTextureBullet = NULL;
	g_pVtxBuffBullet = NULL;

	//***テクステャの読み込み***
	D3DXCreateTextureFromFile(pDevice,"./data/TEXTURE/effect000.png",&g_pTextureBullet);

	//***頂点情報の設定***
	//****頂点バッファの設定****
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*4*BULLET_MAX,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffBullet,NULL);

	//***頂点データをロック***
	g_pVtxBuffBullet->Lock(0,0,(void**)&pVtx,0);

	for(int nCnt = 0;nCnt < BULLET_MAX;nCnt++)
	{
		//****頂点の位置の設定****
		pVtx[0 + nCnt*4].pos = D3DXVECTOR3(-BULLET_SIZE +(nCnt%BAEM_TEXTURE_NUM),BULLET_SIZE -(nCnt%BAEM_TEXTURE_NUM),0.0f);
		pVtx[1 + nCnt*4].pos = D3DXVECTOR3(BULLET_SIZE -(nCnt%BAEM_TEXTURE_NUM),BULLET_SIZE -(nCnt%BAEM_TEXTURE_NUM),0.0f);
		pVtx[2 + nCnt*4].pos = D3DXVECTOR3(-BULLET_SIZE +(nCnt%BAEM_TEXTURE_NUM),-BULLET_SIZE +(nCnt%BAEM_TEXTURE_NUM),0.0f);
		pVtx[3 + nCnt*4].pos = D3DXVECTOR3(BULLET_SIZE -(nCnt%BAEM_TEXTURE_NUM),-BULLET_SIZE +(nCnt%BAEM_TEXTURE_NUM),0.0f);

		//****何かの設定*****
		pVtx[0 + nCnt*4].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
		pVtx[1 + nCnt*4].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
		pVtx[2 + nCnt*4].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
		pVtx[3 + nCnt*4].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

		//****カラーの設定****
		pVtx[0 + nCnt*4].col = D3DCOLOR_RGBA(255,125,125,255);
		pVtx[1 + nCnt*4].col = D3DCOLOR_RGBA(255,125,125,255);
		pVtx[2 + nCnt*4].col = D3DCOLOR_RGBA(255,125,125,255);
		pVtx[3 + nCnt*4].col = D3DCOLOR_RGBA(255,125,125,255);

		//****texの設定****
		pVtx[0 + nCnt*4].tex = D3DXVECTOR2(0.0,0.0);
		pVtx[1 + nCnt*4].tex = D3DXVECTOR2(1.0,0.0);
		pVtx[2 + nCnt*4].tex = D3DXVECTOR2(0.0,1.0);
		pVtx[3 + nCnt*4].tex = D3DXVECTOR2(1.0,1.0);
	}
		//****頂点データのロック解除
		g_pVtxBuffBullet->Unlock();
	
}

//◇---------------------------------◇
//バレット終了処理
//◇---------------------------------◇
void UninitBullet(void)
{
	if(g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	
	}
	//テクスチャの処理
	if(g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}
//◇---------------------------------◇
//バレットの更新処理
//◇---------------------------------◇
void UpdateBullet(void)
{
	static int BulletShoot;		//おしっぱで撃てる計算をする

	if(BulletUpdate_num >= BULLET_MAX)
		BulletUpdate_num= 0;
	
	//タマの発射間隔ボタンを押したら初期値に戻すを数える
	if(GetKeyboardPress(DIK_RETURN) == false)
	{
		BulletShoot = BULLET_KANKAKU;
	}

	//=========================
	//弾の撃つ瞬間の処理
	//=========================

	//怯み状態以外のときは発射できる
	if(GetModelOriginal().Model_Muteki != 2)
	{
		BulletShoot++;
		if(BulletShoot >= BULLET_KANKAKU)
		{
			//タマの発射をする
			if(GetKeyboardPress(DIK_RETURN) == true)
			{
				//弾間隔の数え始め
				BulletShoot = 0;
				//発射した瞬間の弾と本体の関係を保存する
				//1発の一番前のテクスチャの分だけ保存する。ほかのは判定には使わないから
				p_Bullet_shunkan[BulletUpdate_num] = GetModelOriginal();
	
				PlaySound(SOUND_LABEL_GUNFIRE);				//弾の発射音

				//タマのテクステャ数だけ繰り返す
				for(int nCnt = 0;nCnt < BAEM_TEXTURE_NUM;nCnt++)
				{
					//弾のテクステャ5枚分を有効化
					bullet_hassha[BulletUpdate_num] = true;
		
					//タマの発射位置を保存する
					if(BulletUpdate_num % (BAEM_TEXTURE_NUM*2) >= 0 && BulletUpdate_num % (BAEM_TEXTURE_NUM*2) < BAEM_TEXTURE_NUM)
					{
						//左の銃の位置を保存
						posBullet_Original[BulletUpdate_num] = GetTranslate_juuL();
					}

					else if(BulletUpdate_num % (BAEM_TEXTURE_NUM*2) >= BAEM_TEXTURE_NUM && BulletUpdate_num % (BAEM_TEXTURE_NUM*2) < BAEM_TEXTURE_NUM*2)
					{
						//右の銃の位置を保存
						posBullet_Original[BulletUpdate_num] = GetTranslate_juuR();
					}

					g_posBullet[BulletUpdate_num].z -= (nCnt * 3);		//弾の位置を少しずらす
					BulletUpdate_num++;									//テクスチャ分プラス
				}
			}
		}
	}

	//有効化された弾の位置を移動させる
	for(int nCnt = 0;nCnt < BULLET_MAX;nCnt++)
	{
		//有効なら位置を移動する
		if(bullet_hassha[nCnt] == true)
		{
			//位置のプラス
			g_posBullet[nCnt].z += BULLET_SPEED + GetModel_SpeedUP();

			//射程距離外に出たら表示をやめる
			//位置が0からなのでこれで
			if(g_posBullet[nCnt].z > BULLET_LANGE)
			{
				g_posBullet[nCnt].z = 38.0f;
				bullet_hassha[nCnt] = false;
			}
		}
	}


	//あたり判定
	//もし、タマの先頭がモデルに当たったらモデルが消える、爆発する、ダメージを与える
}

//◇---------------------------------◇
//バレットの描画処理
//◇---------------------------------◇
void DrawBullet(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	D3DXMATRIX mtxView;				//ビューマトリックス　逆行列の入れ子
	
	//****デバイス取得****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//エフェクト処理　光る処理
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	//タマの数だけ繰り返す
	for(int nCnt = 0;nCnt < BULLET_MAX;nCnt++)
	{
		//弾が有効だったら描画する
		if(bullet_hassha[nCnt] == true)
		{
			mtxView = GetMtxView();

			//------ワールドマトリックスとかの設定--------------------------------------------------------------

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldBullet);

			//逆行列を求める
			D3DXMatrixInverse(&g_mtxWorldBullet,NULL,&mtxView);

			g_mtxWorldBullet._41 = 0.0f;
			g_mtxWorldBullet._42 = 0.0f;
			g_mtxWorldBullet._43 = 0.0f;

			//****ワールドの設定****

			//スケールの設定
			D3DXMatrixScaling(&mtxScl,g_sclBullet[nCnt].x,g_sclBullet[nCnt].y,g_sclBullet[nCnt].z);						//スケールを反映
			D3DXMatrixMultiply(&g_mtxWorldBullet,&g_mtxWorldBullet,&mtxScl);
	
			//角度の設定
			D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotBullet[nCnt].y,g_rotBullet[nCnt].x,g_rotBullet[nCnt].z);		//ヨ－　ピッチ　ロール
			D3DXMatrixMultiply(&g_mtxWorldBullet,&g_mtxWorldBullet,&mtxRot);
	
			//位置の設定
			D3DXMatrixTranslation(&mtxTranslate,g_posBullet[nCnt].x,g_posBullet[nCnt].y,g_posBullet[nCnt].z);			//位置を反映

			//位置の設定の前に弾の位置と銃の位置を加算する
			//位置だけ持ってこないと、ビルボードがおかしなことになってしまう
			D3DXMatrixMultiply(&mtxTranslate,&mtxTranslate,&posBullet_Original[nCnt]);

			//そして設定
			D3DXMatrixMultiply(&g_mtxWorldBullet,&g_mtxWorldBullet,&mtxTranslate);

			pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldBullet);	//設定
	
			//------------------------------------------------------------------------------------------

			//****αテストの開始****
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF,100);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

			//----------------3Dポリゴンの描画----------------------------------------------------------

			//頂点バッファをバインド
			pDevice->SetStreamSource(0,g_pVtxBuffBullet,0,sizeof(VERTEX_3D));
			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);
			//テクスチャの設定
			pDevice->SetTexture(0,g_pTextureBullet);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCnt*4,2);

			//------------------------------------------------------------------------------------------
		}
	}
	//エフェクトを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//****αテストの終了****
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
}

void BULLET_HITJUDGE(void)
{
	PLAYER_MODE Hitjudge_ireko;		//あたり判定の入れ子

	//弾の数だけ繰り返す
	for(int nCnt = 0;nCnt < BULLET_MAX;nCnt++)
	{
		//弾が発射されたら判定を始める
		if(bullet_hassha[nCnt] == true)
		{
			//障害物の数だけ繰り返す
			for(int ObjectCnt = 0;ObjectCnt < OBSTACLE_NUM;ObjectCnt++)
			{
				//障害物の位置情報を入れる
				Hitjudge_ireko = GetObstacle_info(ObjectCnt);
		
				//正なら判定を行う
				if(Hitjudge_ireko.Thing_exist == true)
				{
					//まず、障害物のあたり判定
					//Z軸の判定
					if(p_Bullet_shunkan[nCnt].MOTO_pos.z + g_posBullet[nCnt].z > Hitjudge_ireko.MOTO_pos.z-50.0f
						&& p_Bullet_shunkan[nCnt].MOTO_pos.z + g_posBullet[nCnt].z < Hitjudge_ireko.MOTO_pos.z + 50.0f)
					{
						//X軸のあたり判定
						if(p_Bullet_shunkan[nCnt].LR_Judge == Hitjudge_ireko.LR_Judge)
						{
							//ここであたり判定が確定する。爆発の位置と有効化をする
							PlaySound(SOUND_LABEL_BULLET_EXPLOSION);
							SetExplosion(p_Bullet_shunkan[nCnt].MOTO_pos + g_posBullet[nCnt],nCnt,true,Hitjudge_ireko.LR_Judge);

							//テクスチャの数だけ非表示にする
							for(int KekkaCnt = 0;KekkaCnt < BAEM_TEXTURE_NUM;KekkaCnt++)
							{
								g_posBullet[nCnt + KekkaCnt].z = 38.0f;
								bullet_hassha[nCnt + KekkaCnt] = false;
							}
						}
					}
				}
			}

			//敵01の数だけ繰り返す
			for(int Enemy01Cnt = 0;Enemy01Cnt < ENEMY01_NUM;Enemy01Cnt++)
			{
				//敵01の位置情報を入れる
				Hitjudge_ireko = GetEnemy01_info(Enemy01Cnt);

				//正なら判定を行う
				if(Hitjudge_ireko.Thing_exist == true)
				{
				//まず、敵01のあたり判定
					//Z軸の判定
					if(p_Bullet_shunkan[nCnt].MOTO_pos.z + g_posBullet[nCnt].z > Hitjudge_ireko.MOTO_pos.z-60.0f
						&& p_Bullet_shunkan[nCnt].MOTO_pos.z + g_posBullet[nCnt].z < Hitjudge_ireko.MOTO_pos.z + 60.0f)
					{
						//X軸のあたり判定
						if(p_Bullet_shunkan[nCnt].LR_Judge == Hitjudge_ireko.LR_Judge)
						{
							//ここであたり判定が確定する。爆発の位置と有効化をする
							PlaySound(SOUND_LABEL_BULLET_EXPLOSION);
							SetExplosion(p_Bullet_shunkan[nCnt].MOTO_pos + g_posBullet[nCnt],nCnt,true,Hitjudge_ireko.LR_Judge);

							//ダメージを1与える
							Enemy01_DamageCnt(Enemy01Cnt);

							//テクスチャの数だけ非表示にする
							for(int KekkaCnt = 0;KekkaCnt < BAEM_TEXTURE_NUM;KekkaCnt++)
							{
								g_posBullet[nCnt + KekkaCnt].z = 38.0f;
								bullet_hassha[nCnt + KekkaCnt] = false;
							}
						}
					}
				}
			}
		}
	}
}





