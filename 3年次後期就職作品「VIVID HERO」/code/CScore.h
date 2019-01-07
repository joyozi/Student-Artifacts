//◇-------------------------------------------------------------------------◇
//
//	File:CScoreのヘッダーファイル[CScore.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CSCORE_H_
#define _CSCORE_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CScene.h"
#include "CScene2D.h"

#define SCORE_KETA_MAX (16)		//スコアの最大桁数

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CScore : public CScene
{
public:
	CScore(int nPriority = 70);
	virtual ~CScore();
	
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual void  SetPosition(float x,float y,float z);
	virtual void  SetPosition(D3DXVECTOR3 pos);

	virtual D3DXVECTOR3 GetPosition(void);

	virtual void SetRotation(float x,float y,float z);
	virtual void SetRotation(D3DXVECTOR3 pos);

	virtual D3DXVECTOR3 GetRotation(void);

	virtual void SetType(int nType);

	static CScore *Create(LPCTSTR TextureName,int KetaNum,float Pos_Right,float Pos_Up,float TexWidth,float TexHeight,int StartScore);
	void PlusScore(int score);
	void ResetScore(int score);

protected:
	int				SCORE_KETA_NUM;				//スコアの桁の数
	float			SCORE_POS_RIGHT;			//スコアの左端の位置
	float			SCORE_POS_UP;				//スコアの一番上の位置
	float			SCORE_POS_HEIGHT;			//スコアの縦幅
	float			SCORE_POS_WIDTH;			//一つのスコアの横幅

	D3DXVECTOR3		m_Pos;
	D3DXVECTOR3		m_Rot;

	LPCTSTR			m_ScoreTextureName;
	CScene2D*		m_pNumber[SCORE_KETA_MAX];

	int				m_Score;					//合計の数値。
	int				m_NowScore;					//変動中のスコア 表示用

};

#endif