//��-------------------------------------------------------------------------��
//
//	File:CTitleMenu�̃w�b�_�[�t�@�C��[CTitleMenu.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CTITLEMENU_H_
#define _CTITLEMENU_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "main.h"

class CScene2D;

enum TITLEMENU{
	TM_GAMESTART = 0,
	TM_END,
	TM_MAX
};

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CTitleMenu
{
public:
	CTitleMenu();
	virtual ~CTitleMenu();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

private:
	static const int		MENUMOVECNT = 10;

	CScene2D*				m_pScene2D[2 + TM_MAX];

	D3DXCOLOR		m_FlashCol[4];
	bool			m_FlashJudge;			//false�Ō����Ă�
	bool			m_EnterJudge;			//�G���^�[�������ꂽ���̏���
	int				m_EnteredFlashCnt;
	bool			m_GoMenuJudge;			//�_�Ō�Ƀ��j���[�ɍs��
	D3DXCOLOR		m_MenuFlashCol[4];
	TITLEMENU		m_NowSelectedMenu;
	int				m_MenuMoveCnt;
	bool			m_GameStartJudge;

	D3DXVECTOR3		m_MenuPos[TM_MAX];
	D3DXVECTOR3		m_MenuSize[TM_MAX];
	D3DXVECTOR3		m_MenuNowPos;
	D3DXVECTOR3		m_MenuNowSize;
	D3DXVECTOR3		m_FromPos;
	D3DXVECTOR3		m_FromSize;
};


#endif
