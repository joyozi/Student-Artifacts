#ifndef _CSCENE_H_
#define _CSCENE_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "main.h"

//◇-----------------------------------◇
//マクロ定義
//◇-----------------------------------◇
#define PRIORITY_NUM (128)

/*/------プライオリティーライブラリ(プライオリティの順番について)------

０～５ : 空白(デバッグ用、実験用に)
６～２０ : CSceneの基本クラス
２１～３０ : ゲームの基礎となるものをいろいろ
３１～４０ : Mesh系
５０～PRIORITY_NUM : その他

特別枠
CFade : PRIORITY_NUM - 1 最後に描画したいから



//--------------------------------------------------------------------*/

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CScene
{
public:
	//PRIORITYとは、描画する順番である。最初から順に描画していって、描画順番をわかりやすくするために必要である
	//CScene(int nPriority = 0):m_nPriority(nPriority){}
	CScene(int nPriority = 6);
	virtual ~CScene();

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	//多態性をやる
	virtual void  SetPosition(float x,float y,float z) = 0;
	virtual void  SetPosition(D3DXVECTOR3 pos) = 0;

	virtual D3DXVECTOR3  GetPosition(void) = 0;

	virtual void SetRotation(float x,float y,float z) = 0;
	virtual void SetRotation(D3DXVECTOR3 pos) = 0;
	virtual D3DXVECTOR3 GetRotation(void) = 0;

	virtual void SetType(int nType) = 0;
	
	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	void Release(void);

	void LinkList(void);
	void UnlinkList(void);
	
	static CScene *SearchLinkList(CScene *irekoScene[],int searchType);

	virtual void CollisionHitCheckCircle(CScene *Scene);
	virtual float GetCollisionRadius(int Num);
	virtual D3DXVECTOR3 GetCollisionCenterPos(int Num);
	virtual bool CollisionTargetSheet(CLASS_TYPE Type);

	virtual void CollisionAction(CLASS_TYPE Type,int Num);		//どのタイプかと何番目のあたり位置が当たったか

	virtual void SetCollisionHitNum(int HitNum);
	virtual int GetCollisionHitNum(void);

	static void CollisionHitLoop(void);

private:
	static CScene*		m_pTop[PRIORITY_NUM];	// リストの先頭ポインタ
	static CScene*		m_pCur[PRIORITY_NUM];	// リストの末尾
	CScene*				m_pPrev;						// 自身の前へのポインタ
	CScene*				m_pNext;						// 自身の次へのポインタ

	int					m_nPriority;
	int					m_CollisionHitNum;

protected:
	bool				m_DeleteFlag;
	CLASS_TYPE			m_Type;						//セットタイプで使う変数
	bool				m_CollisionHitJudge;
};



#endif
