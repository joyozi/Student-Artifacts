//��-------------------------------------------------------------------------��
//
//	File:CPhaseTitle�̃w�b�_�[�t�@�C��[CPhaseTitle.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CPHASETITLE_H_
#define _CPHASETITLE_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CPhase.h"

class CTitleMenu;
class CCamera;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CPhaseTitle : public CPhase
{
public:
	CPhaseTitle(PHASE Phase = PHASE_TITLE);
	virtual ~CPhaseTitle();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

private:
	CTitleMenu*		m_pTitleMenu;
	CCamera*		m_pCamera;

};


#endif
