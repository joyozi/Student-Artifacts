//��-------------------------------------------------------------------------��
//
//	File:CTimer�̃w�b�_�[�t�@�C��[CTimer.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CTIMER_H_
#define _CTIMER_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CScore.h"
#include "CScene2D.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CTimer : public CScore
{
public:
	CTimer(int nPriority = 26);
	virtual ~CTimer();
	virtual void Update(void);
	
	static CTimer *Create(LPCTSTR TextureName,int SetTime,int KetaNum,float Pos_Right,float TexWidth,float TexHeight);
	static void PlusTime(int time);

private:
	int				m_TimeCnt;
	static int		m_Time;									//���v�̐��l�B
};


#endif
