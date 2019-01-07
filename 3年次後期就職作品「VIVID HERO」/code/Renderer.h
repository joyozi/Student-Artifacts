//��-------------------------------------------------------------------------��
//
//	File:�}�l�[�W���̃t�@�C��[CManager.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _RENDERER_H_
#define _RENDERER_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "main.h"

class CDebugProc;

//��-----------------------------------��
//�v���g�^�C�v�錾
//��-----------------------------------��
HRESULT ChangeWindowSize(void);
HRESULT InitGraphics(void);
void CleanupDXGraphics(void);

HWND GethWnd();
HINSTANCE GetHInstance();

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CRenderer
{
public:
	CRenderer(){}		//private�̂Q��NULL�����邾��
	~CRenderer(){}

	//�啶����BOOL�͂S�o�C�g�Abool�͂P�r�b�g�Ƃ����낢��Ⴂ������炵��

	//�f���@�C�X�̐����Bbool�ō쐬�ł������ǂ�����������
	HRESULT Init(HINSTANCE hInstance);
	void Update(void);
	void Uninit(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void);

protected:
	static CDebugProc *m_pDebugProcPointer;

};


#endif