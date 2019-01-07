//◇-------------------------------------------------------------------------◇
//
//	File:CSenecppファイル[CSene.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
//#include "CManager.h"
#include "CScene.h"
#include "CItemList.h"
#include <vector>

//◇-------------------------------------------------------------------------◇
//クラスのスタティック変数の初期化
//◇-------------------------------------------------------------------------◇
CScene *CScene::m_pTop[] = {NULL};
CScene *CScene::m_pCur[] = {NULL};

//◇----------------------------------◇
//コンストラクタ
//◇----------------------------------◇
CScene::CScene(int nPriority)
{
	m_Type = CTYPE_NONE;		//とりあえず何かしら入れておく
	m_nPriority = nPriority;	//優先順位を教える
	m_DeleteFlag = false;		//デスフラグの初期化

	m_CollisionHitJudge = false;
	m_CollisionHitNum = 0;

	LinkList();
}

//◇----------------------------------◇
//デストラクタ
//◇----------------------------------◇
CScene::~CScene()
{

}

//◇----------------------------------◇
//アップデートオール
//◇----------------------------------◇
void CScene::UpdateAll(void)
{
	for(int i = 0;i < PRIORITY_NUM;i++)
	{
		//デスフラグが立ってたらUnlinkListを呼ぶ
		for(CScene * pScene = m_pTop[i]; pScene != NULL;)
		{
			//ポインタの間違いをなくすため一時的にChangeSceneに入れてる
			CScene *ChangeScene = pScene;
			pScene = pScene->m_pNext;

			//デスフラグが立ってたらピンポイントで殺す
			if(ChangeScene->m_DeleteFlag)
			{
				ChangeScene->UnlinkList();
			}
			else
			{
				ChangeScene->Update();

				//Update内でフラグがたったら
				if(ChangeScene->m_DeleteFlag)
				{
					ChangeScene->UnlinkList();
				}
			}
		}
	}

	CollisionHitLoop();
}

//◇----------------------------------◇
//ドローオール
//◇----------------------------------◇
void CScene::DrawAll(void)
{
	for(int i = 0;i < PRIORITY_NUM;i++)
	{
		for(CScene *pScene = m_pTop[i];pScene != NULL;pScene = pScene-> m_pNext)
		{
			pScene->Draw();
		}
	}
}

//◇----------------------------------◇
//リリースオール
//◇----------------------------------◇
void CScene::ReleaseAll()
{
	for(int i = 0;i < PRIORITY_NUM;i++)
	{
		CScene *pScene = m_pTop[i];

		while(pScene != NULL)
		{
			//消える前に次を保存
			CScene *pNext = pScene->m_pNext;

			pScene->m_DeleteFlag = false;	//とりあえずデスフラグをつぶす
			pScene->Uninit();
			delete pScene;					//全部消していく
			pScene = NULL;
			pScene = pNext;
		}

		m_pTop[i] = NULL;		//画面遷移用に
		m_pCur[i] = NULL;		//画面遷移用に
	}
}

//◇----------------------------------◇
//リリース	デスフラグを立てる
//◇----------------------------------◇
void CScene::Release(void)
{
	m_DeleteFlag = true;
}

//◇-----------------------------------◇
//リストに登録
//◇-----------------------------------◇
void CScene::LinkList(void)
{
	//NULLだったら先頭のポインタを保存する ついでに末尾も
	if(m_pTop[m_nPriority] == NULL && m_pCur[m_nPriority] == NULL)
	{
		m_pTop[m_nPriority] = this;
		m_pCur[m_nPriority] = this;
	}

	//最後尾につけるリストにNULL代入
	m_pNext = NULL;

	//最後尾が現在だったらリストの先頭にNULL?
	if (m_pCur[m_nPriority] == this)
	{
		m_pPrev = NULL;
	}
	else
	{
		m_pPrev = m_pCur[m_nPriority];
		// 最後尾ひとつ手前のリストに追加したリストのポインタを渡す
		m_pCur[m_nPriority]->m_pNext = this;

		//末尾のポインタを入れる
		m_pCur[m_nPriority] = this;
	}
}

//◇----------------------------------◇
//CSceneのリストから削除
//◇----------------------------------◇
void CScene::UnlinkList(void)
{
	//****前のNEXT,次のPREVを変更する****

	//消す　前に何か入ってる時
	if(m_pPrev != NULL)
	{
		//前のポインタのNextに今のポインタのNextを入れる
		m_pPrev->m_pNext = m_pNext;
	}

	//消す　次に何か入ってる時
	if(m_pNext != NULL)
	{
		//次のポインタのPrevに今のポインタのPrevを入れる
		m_pNext->m_pPrev = m_pPrev;
	}

	//先頭のときのアンリスト
	if(m_pTop[m_nPriority] == this)
	{
		//次のポインタがあるとき、次のポインタのPrevをNULLに
		m_pTop[m_nPriority] = m_pNext;	//トップを入れ替える
	}

	//末尾のときのアンリスト
	if(m_pCur[m_nPriority] == this)
	{
		m_pCur[m_nPriority] = m_pPrev;	//最後尾を入れ替える
	}

	//デリートする
	delete this;
}

//◇-----------------------------------◇
//リストを検索
//searchType : main.hにあるCTYPEのリストを入れる
//◇-----------------------------------◇
CScene *CScene::SearchLinkList(CScene *irekoScene[],int searchType)
{
	int Num = 0;

	//プリオリティ数分繰り返す
	for(int i = 0;i < PRIORITY_NUM;i++)
	{
		for(CScene *pScene = m_pTop[i];pScene != NULL;pScene = pScene-> m_pNext)
		{
			//欲しいタイプだったら一時的に保存
			if(pScene->m_Type == searchType)
			{
				//一時的に保存
				irekoScene[Num] = pScene;
				Num++;
			}
		}
	}

	return *irekoScene;
}

//◇-----------------------------------◇
//あたり判定の半径をゲットする関数
//◇-----------------------------------◇
float CScene::GetCollisionRadius(int Num)
{
	return 0.0f;
}

//◇-----------------------------------◇
//あたり判定の半径をゲットする関数
//◇-----------------------------------◇
D3DXVECTOR3 CScene::GetCollisionCenterPos(int Num)
{
	return GetPosition();
}

//◇-----------------------------------◇
//当たる対象のシート
//◇-----------------------------------◇
bool CScene::CollisionTargetSheet(CLASS_TYPE Type)
{
	switch(Type)
	{
	case CTYPE_NONE:	return false;break;

	default:		return false;break;
	}
}

//◇-----------------------------------◇
//当たった時のアクション用関数
//◇-----------------------------------◇
void CScene::CollisionAction(CLASS_TYPE Type,int Num)
{
	m_CollisionHitJudge = true;
}

//◇-----------------------------------◇
//あたり判定の数セット
//◇-----------------------------------◇
void CScene::SetCollisionHitNum(int HitNum)
{
	m_CollisionHitNum = HitNum;
}

//◇-----------------------------------◇
//あたり判定の数取得
//◇-----------------------------------◇
int CScene::GetCollisionHitNum(void)
{
	return m_CollisionHitNum;
}


//◇-----------------------------------◇
//汚いからこっちに作る
//◇-----------------------------------◇
void CScene::CollisionHitLoop(void)
{
	//あたり判定の下準備

	// 総数分の配列を確保。
	std::vector<CScene*> aBucket;

	//あたり判定をするシーンをセットする
	for(int i = 0;i < PRIORITY_NUM;i++)
	{
		for(CScene * pScene = m_pTop[i]; pScene != NULL;)
		{
			CScene *ChangeScene = pScene;
			pScene = pScene->m_pNext;

			//あたり判定のループ
			if(ChangeScene->m_CollisionHitNum > 0)
			{
				aBucket.push_back(ChangeScene);
			}
		}
	}

	for(unsigned int i = 0;i < aBucket.size();i++)
	{
		for(unsigned int j = i + 1;j < aBucket.size();j++)
		{
			aBucket[i]->CollisionHitCheckCircle(aBucket[j]);
		}
	}
}

//◇-----------------------------------◇
//あたり判定の関数
//◇-----------------------------------◇
void CScene::CollisionHitCheckCircle(CScene *Scene)
{
	//自分のあたり判定の数　*　相手のあたり判定の数だけ繰り返す

	//どっちかが当たってくれるようにしてるなら当てる
	if(this->CollisionTargetSheet(Scene->m_Type) || Scene->CollisionTargetSheet(this->m_Type))
	{
		for(int i = 0;i < this->m_CollisionHitNum;i++)
		{
			for(int j = 0;j < Scene->m_CollisionHitNum;j++)
			{
				//お互いの距離を計算→半径以下か比較
				float Length = CItemList::GetLength(this->GetCollisionCenterPos(i),Scene->GetCollisionCenterPos(j));

				if(Length <= this->GetCollisionRadius(i) + Scene->GetCollisionRadius(j))
				{
					this->CollisionAction(Scene->m_Type,j);
			
					Scene->CollisionAction(this->m_Type,i);
				}
			}
		}
	}
}

//EOF