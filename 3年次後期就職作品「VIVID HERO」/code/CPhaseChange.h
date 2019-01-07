//��-------------------------------------------------------------------------��
//
//	File:CPhaseChange�̃w�b�_�[�t�@�C��[CPhaseChange.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CPHASECHANGE_H_
#define _CPHASECHANGE_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "main.h"
#include "CPhase.h"
#include "CScene.h"

class CPhase;
class CPhaseChange;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CPhaseChange
{
public:
	CPhaseChange();
	virtual ~CPhaseChange();

	virtual HRESULT Init(CPhase *pStartPhase);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void PhaseChange(CPhase *PhaseNext)
	{
		if(m_pFade == NULL)
		{
			m_pPhaseNext = PhaseNext;
		}
		else
		{
			delete PhaseNext;
		}
	}

	CPhase *GetPhasePointer(){return m_pPhase;}

private:
	static CPhase*	m_pPhase;		//���̃t�F�[�Y
	CPhase*			m_pPhaseNext;			//���ɍs�������t�F�[�Y
	CFade*			m_pFade;
};


#endif
