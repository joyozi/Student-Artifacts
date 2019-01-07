//◇-------------------------------------------------------------------------◇
//
//	File:CSceneModelMotionのヘッダーファイル[CSceneModelMotion.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CSCENEMODELMOTION_H_
#define _CSCENEMODELMOTION_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CItemList.h"
#include "CScene.h"

//◇-----------------------------------◇
//構造体
//◇-----------------------------------◇
//モデルのニュートラル情報
typedef struct
{
	char		ModelName[256];
	char		TexName[256];
	int			ModelNumber;
	int			ParentNumber;
	int			IndexNumber;

	D3DXVECTOR3	Pos;
	D3DXVECTOR3	Rot;
	D3DXVECTOR3	Scl;
}PART_INFO;

// キーデータの定義
typedef struct
{
	D3DXVECTOR3 keyPos;
	D3DXVECTOR3 keyRot;
}KEY_DATA;

// アニメーションデータの定義
typedef struct
{
	int			loopjudge;
	int			num_key;
	int			frame;
	KEY_DATA*	key;
}KEY_ANIME;

typedef enum
{
	MODELACT_NEUTRAL = 0,
	MODELACT_WALK,
	MODELACT_RUN,
	MODELACT_PUNCH,
	MODELACT_KICK,
	MODELACT_HEADBUTT,
	MODELACT_MAX
}MODELACT;

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CSceneModelMotion : public CScene
{
public:
	CSceneModelMotion(int nPriority = 10);
	virtual ~CSceneModelMotion();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual void SetPosition(float x,float y,float z);
	virtual void SetPosition(D3DXVECTOR3 pos);
	virtual D3DXVECTOR3 GetPosition(void);

	virtual void SetRotation(float x,float y,float z);
	virtual void SetRotation(D3DXVECTOR3 pos);
	virtual D3DXVECTOR3 GetRotation(void);

	virtual void SetType(int nType);

	virtual PART_INFO *GetPart_Info(void);
	virtual int GetNowMotionNum();
	virtual bool GetMotionEndJudge(void){return m_MotionEndJudge;}
	static CSceneModelMotion *Create(LPCTSTR ModelTxtName);

	virtual void SetActCommand(int Act){m_ModelAct = Act;}
	virtual int GetActCommand(){return m_ModelAct;}
	
	int GetPart_Num(void);

private:
	D3DXVECTOR3				m_Pos;
	D3DXVECTOR3				m_Rot;
	LPCTSTR					m_ModelTxtName;
	PART_INFO*				m_pModel;						//モデルの基本情報
	PART_INFO*				m_pModelMove;					//モデルのキーフレーム情報
	KEY_DATA*				m_pModelStandard;					//モデルの何もしてないときのポーズの情報保管場所
	KEY_ANIME				*m_pAnime;

	int						m_ModelPartsNum;
	int						m_ModelAct;
	int						m_MotionNum_deleted;					//デリートで使う用
	
	//線形補間用のいろいろな数値
	float					m_Time;							//計算用
	int						m_ModelActNow;						//前回との比較するよう
	int						m_MotionNumStart;					//モーションの始まりの数値
	KEY_DATA*				m_pKeyInterpolation;				//線形補間する中間の情報
	bool					m_KeyInfterpolationjudge;				//線形補間をしているかしていないか
	bool					m_MotionEndJudge;
};

#endif
