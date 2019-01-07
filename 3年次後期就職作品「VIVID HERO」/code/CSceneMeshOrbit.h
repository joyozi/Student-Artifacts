//◇-------------------------------------------------------------------------◇
//
//	File:CSceneMeshOrbitのヘッダーファイル[CSceneMeshOrbit.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CSCENEMESHORBIT_H_
#define _CSCENEMESHORBIT_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "CScene3D.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CSceneMeshOrbit : public CScene3D
{
public:
	CSceneMeshOrbit(int nPriority = 100);
	virtual ~CSceneMeshOrbit();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void SetOrbitMatrix(D3DXMATRIX matrix);
	void SetOrbitPosition(D3DXVECTOR3 Pos);

	void SetOebitStopJudge(bool Judge){
		m_StopJudge = Judge;
	}


	static CSceneMeshOrbit *Create(D3DXVECTOR3 PosA,D3DXVECTOR3 PosB,D3DXCOLOR ColorA,D3DXCOLOR ColorB);

private:
	static const int NUM_ORBIT = 60;

	VERTEX_3D *m_pVtx;

	D3DXMATRIX m_mtxProjection;				//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;						//ビューマトリックス
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

	D3DXVECTOR3 m_PointPosA;
	D3DXVECTOR3 m_PointPosB;

	D3DXCOLOR m_PointColA;
	D3DXCOLOR m_PointColB;

	D3DXVECTOR3 m_aPosRecorder[NUM_ORBIT * 2 + 2];
	D3DXCOLOR m_aPosColor[NUM_ORBIT * 2 + 2];

	D3DXVECTOR3 m_TargetPos;
	D3DXMATRIX m_TargetMatrix;

	bool m_StopJudge;

	int m_PolygonNumCnt;

};


#endif
