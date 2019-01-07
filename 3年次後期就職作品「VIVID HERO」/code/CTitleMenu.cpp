//◇-------------------------------------------------------------------------◇
//
//	File:CTitleMenuのファイル[CTitleMenu.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CTitleMenu.h"
#include "CScene2D.h"
#include "CManager.h"
#include "CPhaseChange.h"
#include "CPhaseGame.h"
#include "input.h"
#include "CItemList.h"
#include "CItemList.h"
#include "Renderer.h"
#include "CDebugProc.h"
#include "joystick.h"
#include "sound.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CTitleMenuのコンストラクタ
//◇-----------------------------------◇
CTitleMenu::CTitleMenu()
{
	for(int i = 0;i < 4;i++)
	{
		m_FlashCol[i] = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		m_MenuFlashCol[i] = D3DXCOLOR(1.0f,1.0f,1.0f,-2.0f);
	}

	m_FlashJudge = false;
	m_EnterJudge = false;
	m_GoMenuJudge = false;

	m_EnteredFlashCnt = 0;

	m_NowSelectedMenu = TM_GAMESTART;

	m_MenuMoveCnt = MENUMOVECNT;

	m_GameStartJudge = false;
}

//◇-----------------------------------◇
//CTitleMenuのデストラクタ
//◇-----------------------------------◇
CTitleMenu::~CTitleMenu()
{

}

//◇-----------------------------------◇
//CTitleMenuの初期化処理
//◇-----------------------------------◇
HRESULT CTitleMenu::Init(void)
{
	m_pScene2D[0] = CScene2D::Create(60,"./data/TEXTURE/Title/PressEnter00.png",D3DXVECTOR3(500.0f,400.0f,0.0f),D3DXVECTOR3(600.0f,100.0f,0.0f));



	return S_OK;
}

//◇-----------------------------------◇
//CTitleMenuの終了処理
//◇-----------------------------------◇
void CTitleMenu::Uninit(void)
{

}

//◇-----------------------------------◇
//CTitleMenuの更新処理
//◇-----------------------------------◇
void CTitleMenu::Update(void)
{

	m_pScene2D[0]->SetVertex_Col(m_FlashCol);


	//最初の時
	if(m_EnterJudge == false)
	{
		for(int i = 0;i < 4;i++)
		{
			if(m_FlashJudge)
				m_FlashCol[i].a +=0.03f;
			else
				m_FlashCol[i].a -=0.03f;
		}

		//点滅させる
		if(m_FlashCol[0].a < 0.0f)
		{
			m_FlashJudge = true;
		}
		else if(m_FlashCol[0].a > 1.0f)
		{
			m_FlashJudge = false;
		}
	}





	//何かボタンををしたら
	if(CInput::GetKeyboardTrigger(DIK_RETURN) && m_EnterJudge == false)
	{
		PlaySound(SOUND_LABEL_Decision00);

		m_MenuPos[0] = D3DXVECTOR3(400.0f,400.0f,0.0f);
		m_MenuPos[1] = D3DXVECTOR3(300.0f,480.0f,0.0f);

		m_MenuSize[0] = D3DXVECTOR3(400.0f,80.0f,0.0f);
		m_MenuSize[1] = D3DXVECTOR3(180.0f,80.0f,0.0f);

		m_MenuNowPos = m_MenuPos[0];
		m_MenuNowSize = m_MenuSize[0];

		m_FromPos = m_MenuPos[0];
		m_FromSize = m_MenuSize[0];

		m_pScene2D[1] = CScene2D::Create(60,"./data/TEXTURE/Game/Pause/Carsol01.png",m_MenuPos[0],m_MenuSize[0]);
		m_pScene2D[1]->SetVertex_Col(m_MenuFlashCol);
		m_pScene2D[2] = CScene2D::Create(60,"./data/TEXTURE/Title/GameStart.png",m_MenuPos[0],m_MenuSize[0]);
		m_pScene2D[2]->SetVertex_Col(m_MenuFlashCol);
		m_pScene2D[3] = CScene2D::Create(60,"./data/TEXTURE/Title/End.png",m_MenuPos[1],m_MenuSize[1]);
		m_pScene2D[3]->SetVertex_Col(m_MenuFlashCol);

		m_EnterJudge = true;
	}



	if(m_EnterJudge && m_GoMenuJudge == false)
	{
		for(int i = 0;i < 4;i++)
		{
			if(m_FlashJudge)
				m_FlashCol[i].a +=0.25f;
			else
				m_FlashCol[i].a -=0.25f;
		}

		//点滅させる
		if(m_FlashCol[0].a < 0.0f)
		{
			m_EnteredFlashCnt++;
			m_FlashJudge = true;
		}
		else if(m_FlashCol[0].a > 1.0f)
		{
			m_FlashJudge = false;
		}
	
		m_pScene2D[0]->SetVertex_Col(m_FlashCol);


		if(m_EnteredFlashCnt >= 5)
			m_GoMenuJudge = true;
	}

	//点滅が終わったら
	if(m_GoMenuJudge)
	{
		D3DXCOLOR SelectIconCol[4] = {	D3DXCOLOR(0.5f,0.5f,1.0f,0.7f),
										D3DXCOLOR(0.5f,0.5f,1.0f,0.7f),
										D3DXCOLOR(0.5f,0.5f,1.0f,0.7f),
										D3DXCOLOR(0.5f,0.5f,1.0f,0.7f)};



		if(m_MenuFlashCol[0].a < 1.0f)
		{
			for(int i = 0;i < 4;i++)
				m_MenuFlashCol[i].a += 0.25f;

			m_pScene2D[1]->SetVertex_Col(SelectIconCol);
			m_pScene2D[2]->SetVertex_Col(m_MenuFlashCol);
			m_pScene2D[3]->SetVertex_Col(m_MenuFlashCol);

		}
		else			//メニューがちゃんと表示されたら
		{
			D3DXCOLOR SelectIconCol[4];

			for(int i = 0;i < 4;i++)
				SelectIconCol[i] = D3DXCOLOR(1.0f,1.0f,1.0f,0.3f);



			if(CInput::GetKeyboardTrigger(DIK_W))
			{
				PlaySound(SOUND_LABEL_GunKamae);

				switch(m_NowSelectedMenu)
				{
				case TM_GAMESTART:
					m_NowSelectedMenu = TM_END;
					break;


				case TM_END:
					m_NowSelectedMenu = TM_GAMESTART;

					break;

				default:
					break;
				}

				m_FromPos = m_MenuNowPos;
				m_FromSize = m_MenuNowSize;
				m_MenuMoveCnt = 0;
			}


			if(CInput::GetKeyboardTrigger(DIK_S))
			{
				PlaySound(SOUND_LABEL_GunKamae);

				switch(m_NowSelectedMenu)
				{
				case TM_GAMESTART:
					m_NowSelectedMenu = TM_END;
					break;

				case TM_END:
					m_NowSelectedMenu = TM_GAMESTART;

					break;

				default:
					break;
				}

				m_FromPos = m_MenuNowPos;
				m_FromSize = m_MenuNowSize;
				m_MenuMoveCnt = 0;
			}

			if(m_MenuMoveCnt < MENUMOVECNT)
			{
				m_MenuMoveCnt++;
				m_MenuNowPos += CItemList::Vec3lerp(m_FromPos,m_MenuPos[m_NowSelectedMenu],1.0f / MENUMOVECNT) - m_FromPos;
				m_MenuNowSize += CItemList::Vec3lerp(m_FromSize,m_MenuSize[m_NowSelectedMenu],1.0f / MENUMOVECNT) - m_FromSize;
				
				m_pScene2D[1]->SetSize(m_MenuNowSize);
				m_pScene2D[1]->SetPosition_Re(m_MenuNowPos);
			}

			int nID = 0;

			if(CInput::GetKeyboardTrigger(DIK_RETURN) && m_GameStartJudge == false)
			{
				switch(m_NowSelectedMenu)
				{
				case TM_GAMESTART:
					PlaySound(SOUND_LABEL_WeaponShot);

					m_GameStartJudge = true;
					CManager::GetPhaseChangePointer()->PhaseChange(new CPhaseGame());
					break;
					
				case TM_END:
					DestroyWindow(GethWnd());
					break;

				default:
					break;
				}
			}
		}
	}
}

//◇-----------------------------------◇
//CTitleMenuの描画処理
//◇-----------------------------------◇
void CTitleMenu::Draw(void)
{

}


