//��-------------------------------------------------------------------------��
//
//	File:CGameStart�̃w�b�_�[�t�@�C��[CGameStart.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CGAMESTART_H_
#define _CGAMESTART_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CScene2D.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CGameStart : public CScene2D
{
public:
	CGameStart(int nPriority = 120);
	virtual ~CGameStart();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual bool GetGameStartEnd(void);

	static CGameStart *Create(void);

private:
	static const int GAMESTARTLOGO_TIME = 120;
	static const int GAMESTARTLOGO_FADEOUT_TIME = 20;

	CScene2D*	m_pGameStart;
	int			m_GameStartTime;
	bool		m_EndJudge;
	D3DXVECTOR3	m_FadeOutSize;
	D3DXCOLOR	m_FadeOutCol;
};


#endif
