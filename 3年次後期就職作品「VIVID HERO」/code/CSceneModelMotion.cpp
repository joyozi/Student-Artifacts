//◇-------------------------------------------------------------------------◇
//
//	File:CSceneModelMotionのファイル[CSceneModelMotion.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CSceneModelMotion.h"
#include "CItemList.h"
#include "input.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//CSceneModelMotionのコンストラクタ
//◇-----------------------------------◇
CSceneModelMotion::CSceneModelMotion(int nPriority) : CScene(nPriority)
{
	m_Type = CTYPE_SCENEMODELMOTION;
	m_ModelAct = 0;
	m_ModelPartsNum = 0;
	m_ModelTxtName = NULL;

	m_pAnime = NULL;
	m_pModel = NULL;
	m_pModelMove = NULL;
	m_pModelStandard = NULL;


	m_Time = 0;
	m_ModelActNow = 0;						//前回との比較するよう
	m_MotionNumStart = 0;
	m_pKeyInterpolation = NULL;				//線形補間する中間の情報
	m_KeyInfterpolationjudge = false;		//線形補間をしているかしていないか

	m_MotionNum_deleted = 0;

	m_MotionEndJudge = false;
}

//◇-----------------------------------◇
//CSceneModelMotionのデストラクタ
//◇-----------------------------------◇
CSceneModelMotion::~CSceneModelMotion()
{

}

//◇-----------------------------------◇
//CSceneModelMotionの初期化処理
//◇-----------------------------------◇
HRESULT CSceneModelMotion::Init(void)
{
	//motionテキストの読み込み
	FILE *fp;
	fp = fopen(m_ModelTxtName,"rt");

	if(fp == NULL)
	{	//エラー処理
		printf("ファイルオープンエラー\n",stderr);
		return -1;
	}

	char str[256];
	
	int ModelNameNum = 0;
	int ModelIndexNum = 0;
	int MotionNum = 0;
	int ModelTextureNameNum = 0;
	
	//#------------------------------------------------------------------------------
	//# キャラクター情報 までの読み込み
	//#------------------------------------------------------------------------------


	while(1)
	{	//それぞれの数の計算

		fscanf(fp,"%s",str);

		if(feof(fp) != 0)
		{
			break;
		}

		//モデルの目盛の確保。最初にやらねばならない
		if(strcmp(str,"NUM_MODEL") == 0)
		{
			fscanf(fp,"%s",str);
			fscanf(fp,"%d",&m_ModelPartsNum);

			m_pModel = new PART_INFO[m_ModelPartsNum];
			m_pModelMove = new PART_INFO[m_ModelPartsNum];
			m_pModelStandard = new KEY_DATA[m_ModelPartsNum];

			//モデルの線形補間のメモリ確保
			m_pKeyInterpolation = new KEY_DATA[m_ModelPartsNum];

			//判定のために最初にヌルを入れる
			for(int i = 0;i < m_ModelPartsNum;i++)
			{
				m_pModel[i].TexName[0] = NULL;
			}
		}

		if(strcmp(str,"MODEL_FILENAME") == 0)
		{
			fscanf(fp,"%s",str);
			fscanf(fp,"%s",m_pModel[ModelNameNum].ModelName);
			ModelNameNum++;
		}

		if(strcmp(str,"MODEL_TEXTURENAME") == 0)
		{
			fscanf(fp,"%s",str);
			fscanf(fp,"%s",m_pModel[ModelTextureNameNum].TexName);
			ModelTextureNameNum++;
		}

		if(strcmp(str,"INDEX") == 0)
		{
			fscanf(fp,"%s",str);
			fscanf(fp,"%d",&m_pModel[ModelIndexNum].IndexNumber);
		}

		if(strcmp(str,"PARENT") == 0)
		{
			fscanf(fp,"%s",str);
			fscanf(fp,"%d",&m_pModel[ModelIndexNum].ParentNumber);
		}

		if(strcmp(str,"POS") == 0)
		{
			if(ModelIndexNum < m_ModelPartsNum)
			{
				fscanf(fp,"%s",str);
				fscanf(fp,"%f",&m_pModel[ModelIndexNum].Pos.x);
				fscanf(fp,"%f",&m_pModel[ModelIndexNum].Pos.y);
				fscanf(fp,"%f",&m_pModel[ModelIndexNum].Pos.z);
			}
		}

		if(strcmp(str,"ROT") == 0)
		{
			if(ModelIndexNum < m_ModelPartsNum)
			{
				fscanf(fp,"%s",str);
				fscanf(fp,"%f",&m_pModel[ModelIndexNum].Rot.x);
				fscanf(fp,"%f",&m_pModel[ModelIndexNum].Rot.y);
				fscanf(fp,"%f",&m_pModel[ModelIndexNum].Rot.z);
			}
		}

		if(strcmp(str,"END_PARTSSET") == 0)
		{
			ModelIndexNum++;
		}

		//↑↑↑↑ここまでがパーツについて↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑


		if(strcmp(str,"END_KEYSET") == 0)
		{
			MotionNum++;
		}
	}

	//元の位置に戻す
	fseek(fp,0,SEEK_SET);

	//#------------------------------------------------------------------------------
	//# モーション情報
	//#------------------------------------------------------------------------------

	//メモリの確保
	m_pAnime = new KEY_ANIME[MotionNum];
	m_MotionNum_deleted = MotionNum;

		//メモリ確保
	for(int i = 0;i < MotionNum;i++)
	{
		m_pAnime[i].key = new KEY_DATA[m_ModelPartsNum];
	}

	MotionNum = 0;
	int KeyNum = 0;
	int LoopNum_KeyNum = 0;

	while(1)
	{
		fscanf(fp,"%s",str);

		if(feof(fp) != 0)
		{
			break;
		}


		if(strcmp(str,"END_KEY") == 0)
		{
			KeyNum++;
		}

		//モーションが終わったら次のに移る
		if(strcmp(str,"END_KEYSET") == 0)
		{
			KeyNum = 0;
			MotionNum++;
		}

		if(strcmp(str,"END_MOTIONSET") == 0)
		{
			LoopNum_KeyNum++;
		}

		if(strcmp(str,"LOOP") == 0)
		{	//無駄に数値が入る
			fscanf(fp,"%s",str);
			fscanf(fp,"%d",&m_pAnime[LoopNum_KeyNum].loopjudge);
		}

		if(strcmp(str,"NUM_KEY") == 0)
		{	//無駄に数値が入る
			fscanf(fp,"%s",str);
			fscanf(fp,"%d",&m_pAnime[LoopNum_KeyNum].num_key);
		}

		if(strcmp(str,"FRAME") == 0)
		{
			fscanf(fp,"%s",str);
			fscanf(fp,"%d",&m_pAnime[MotionNum].frame);
		}

		if(strcmp(str,"POS") == 0)
		{
			fscanf(fp,"%s",str);
			fscanf(fp,"%f",&m_pAnime[MotionNum].key[KeyNum].keyPos.x);
			fscanf(fp,"%f",&m_pAnime[MotionNum].key[KeyNum].keyPos.y);
			fscanf(fp,"%f",&m_pAnime[MotionNum].key[KeyNum].keyPos.z);
		}

		if(strcmp(str,"ROT") == 0)
		{
			fscanf(fp,"%s",str);
			fscanf(fp,"%f",&m_pAnime[MotionNum].key[KeyNum].keyRot.x);
			fscanf(fp,"%f",&m_pAnime[MotionNum].key[KeyNum].keyRot.y);
			fscanf(fp,"%f",&m_pAnime[MotionNum].key[KeyNum].keyRot.z);
		}
	}

	fclose(fp);



	for(int i = 0;i < m_ModelPartsNum;i++)
	{
		m_pModel[i].Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);
	
		//基礎情報の保存
		m_pModelStandard[i].keyPos = m_pModel[i].Pos;
		m_pModelStandard[i].keyRot = m_pModel[i].Rot;
	
		m_pModel[i].Pos += m_pAnime[0].key[i].keyPos;
		m_pModel[i].Rot += m_pAnime[0].key[i].keyRot;
	}



	return S_OK;
}

//◇-----------------------------------◇
//CSceneModelMotionの終了処理
//◇-----------------------------------◇
void CSceneModelMotion::Uninit(void)
{
	//モーションの数だけ繰り返す
	for(int i = 0;i < m_MotionNum_deleted;i++)
	{
		SAFE_DELETE_ARRY(m_pAnime[i].key);
	}

	SAFE_DELETE_ARRY(m_pAnime);
	SAFE_DELETE_ARRY(m_pModel);
	SAFE_DELETE_ARRY(m_pModelMove);
	SAFE_DELETE_ARRY(m_pModelStandard);
	SAFE_DELETE_ARRY(m_pKeyInterpolation);
}

//◇-----------------------------------◇
//CSceneModelMotionの更新処理
//◇-----------------------------------◇
void CSceneModelMotion::Update(void)
{
	m_MotionEndJudge = false;

	//モーションの前回と違ったら変更する処理
	if(m_ModelActNow != m_ModelAct)
	{
		m_ModelActNow = m_ModelAct;

		//線形補間の設定
		m_KeyInfterpolationjudge = true;	//線形補間の開始

		m_Time = 0.0f;

		m_MotionNumStart = 0;
		for(int i = 0;i < m_ModelActNow;i++)
		{
			m_MotionNumStart += m_pAnime[i].num_key;
		}

		for(int i = 0;i < m_ModelPartsNum;i++)
		{	//まず補間
			m_pKeyInterpolation[i].keyPos = m_pModel[i].Pos - m_pModelStandard[i].keyPos;
			m_pKeyInterpolation[i].keyRot = m_pModel[i].Rot - m_pModelStandard[i].keyRot;
		}
	}

	//キーフレームの移動
	if(m_KeyInfterpolationjudge == false)
	{	//線形補間中でないか   //モーションが１個しかなかったらすぐ抜ける
		for(int i = 0;i < m_ModelPartsNum && m_pAnime[m_ModelActNow].num_key > 1;i++)
		{
			m_pModel[i].Pos = m_pModelStandard[i].keyPos + CItemList::Vec3lerp(m_pAnime[(int)m_Time].key[i].keyPos,
																			m_pAnime[((int)m_Time + 1)].key[i].keyPos,
																			m_Time - (int)m_Time);

			m_pModel[i].Rot = m_pModelStandard[i].keyRot + CItemList::Vec3lerp(m_pAnime[(int)m_Time].key[i].keyRot,
																			m_pAnime[((int)m_Time + 1)].key[i].keyRot,
																			m_Time - (int)m_Time);
		}

		m_Time += 1.0f / (float)m_pAnime[(int)m_Time + 1].frame;

		//時間を超えたら
		if(m_Time >= m_MotionNumStart + m_pAnime[m_ModelActNow].num_key - 1)
		{
			//1フレームだけ終わったと判定
			m_MotionEndJudge = true;

			if(m_pAnime[m_ModelActNow].loopjudge == 1)				//一周したら最初から
			{	//ループする
				m_Time = (float)m_MotionNumStart;
			}
			else if(m_pAnime[m_ModelActNow].loopjudge == 2)			//特殊ケースの作成
			{
				//とりあえずこれで
				m_Time -= 1.0f / (float)m_pAnime[(int)m_Time].frame;
			}
			else
			{	//ループしない
				m_ModelAct = 0;
			}
		}
	}
	else
	{
		for(int i = 0;i < m_ModelPartsNum;i++)
		{
			m_pModel[i].Pos = m_pModelStandard[i].keyPos + CItemList::Vec3lerp(m_pKeyInterpolation[i].keyPos,
																				m_pAnime[m_MotionNumStart].key[i].keyPos,
																				m_Time - (int)m_Time);

			m_pModel[i].Rot = m_pModelStandard[i].keyRot + CItemList::Vec3lerp(m_pKeyInterpolation[i].keyRot,
																				m_pAnime[m_MotionNumStart].key[i].keyRot,
																				m_Time - (int)m_Time);
		}

		m_Time += 1.0f / (float)m_pAnime[m_MotionNumStart].frame;

		if(m_Time >= 1.0f)
		{
			m_Time = (float)m_MotionNumStart;
			m_KeyInfterpolationjudge = false;
		}
	}
}

//◇-----------------------------------◇
//CSceneModelMotionの描画処理
//◇-----------------------------------◇
void CSceneModelMotion::Draw(void)
{

}

//◇----------------------------------◇
//CSceneModelMotionのセットポジションその１
//◇----------------------------------◇
void  CSceneModelMotion::SetPosition(float x,float y,float z)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}

//◇----------------------------------◇
//CSceneModelMotionのセットポジションその２
//◇----------------------------------◇
void  CSceneModelMotion::SetPosition(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//◇----------------------------------◇
//CSceneModelMotionのゲットポジション
//◇----------------------------------◇
D3DXVECTOR3  CSceneModelMotion::GetPosition(void)
{
	return m_Pos;
}

//◇----------------------------------◇
//CSceneModelMotionのセットローテーションその１
//◇----------------------------------◇
void CSceneModelMotion::SetRotation(float x,float y,float z)
{
	m_Rot.x = x;
	m_Rot.y = y;
	m_Rot.z = z;
}

//◇----------------------------------◇
//CSceneModelMotionのセットローテーションその2
//◇----------------------------------◇
void CSceneModelMotion::SetRotation(D3DXVECTOR3 rot)
{
	m_Rot.x = rot.x;
	m_Rot.y = rot.y;
	m_Rot.z = rot.z;
}

//◇----------------------------------◇
//CSceneModelMotionのゲットローテーション
//◇----------------------------------◇
D3DXVECTOR3 CSceneModelMotion::GetRotation(void)
{
	return m_Rot;
}

//◇----------------------------------◇
//CSceneModelMotionのセットタイプ
//◇----------------------------------◇
void CSceneModelMotion::SetType(int nType)
{

}

//◇----------------------------------◇
//CSceneModelMotionのセットタイプ
//◇----------------------------------◇
PART_INFO *CSceneModelMotion::GetPart_Info(void)
{
	return &m_pModel[0];
}

//◇----------------------------------◇
//CSceneModelMotionのパーツの数
//◇----------------------------------◇
int CSceneModelMotion::GetPart_Num(void)
{
	return m_ModelPartsNum;
}

//◇----------------------------------◇
//CSceneModelMotionのそのモーションの中で何番目のモーションかのゲット
//◇----------------------------------◇
int CSceneModelMotion::GetNowMotionNum()
{
	//線形補間中だったら-1を返す
	if(m_KeyInfterpolationjudge == true)
		return -1;

	int returnNum = (int)m_Time;

	for(int i = 0;i < m_ModelActNow;i++)
	{
		returnNum -= m_pAnime[i].num_key;
	}

	return returnNum;
}

//◇----------------------------------◇
//CSceneModelMotionのクリエイト(引数付)
//◇----------------------------------◇
CSceneModelMotion *CSceneModelMotion::Create(LPCTSTR ModelTxtName)
{
	CSceneModelMotion *pCSceneModelMotion;
	pCSceneModelMotion = new CSceneModelMotion;

	pCSceneModelMotion->m_ModelTxtName = ModelTxtName;
	
	pCSceneModelMotion->Init();
	
	return pCSceneModelMotion;
}
