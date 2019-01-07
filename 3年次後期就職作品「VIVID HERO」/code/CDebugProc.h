//��-------------------------------------------------------------------------��
//
//	File:CDebugProc�̃w�b�_�[�t�@�C��[CDebugProc.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CDEBUGPROC_H_
#define _CDEBUGPROC_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "main.h"
//#include <stdarg.h>

//��-----------------------------------��
//�}�N����`
//��-----------------------------------��
#define INT_MAX_DIGITS (10)		//��сH

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��

class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static void Print(const char *fmt,...);
	static bool IsEnableDisp(void)		{ return m_bDisp; };
	static void EnableDisp(bool bDisp)	{ m_bDisp = bDisp; };
	
private:
	static LPD3DXFONT m_D3DXFont;
	static char m_aStr[1024];
	static bool m_bDisp;
};

#endif
