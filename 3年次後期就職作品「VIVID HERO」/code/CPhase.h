//��-------------------------------------------------------------------------��
//
//	File:CPhase�̃w�b�_�[�t�@�C��[CPhase.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CPHASE_H_
#define _CPHASE_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CFade.h"

class CPhase;			//�O���錾�B�ϐ�����ɒ�`����Ă��Ă�����ŉ���
class CPhaseChange;		//

//��-----------------------------------��
//�񋓌^
//��-----------------------------------��
typedef enum{
	PHASE_NONE,
	PHASE_TITLE,
	PHASE_GAME,
	PHASE_RESULT,
	PHASE_MAX
}PHASE;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CPhase
{
public:
	CPhase(PHASE Phase = PHASE_NONE){}
	virtual ~CPhase(){}

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	PHASE GetNowPhase(){return m_NowPhase;}

protected:
	CPhaseChange *GetPhaseChange(void)
	{
		return m_pPhaseChange;
	}

protected:
	PHASE m_NowPhase;

private:
	CPhaseChange *m_pPhaseChange;
};

#endif
