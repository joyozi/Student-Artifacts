//��-------------------------------------------------------------------------��
//
//	�w�b�_�[[input.h]
//	AT12A271�@�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CINPUT_H_
#define _CINPUT_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "main.h"

#define Repeat_Num (30)		//�L�[���s�[�g�̑҂�����

//��-----------------------------------��
//�N���X��`
//��-----------------------------------��
class CInput
{
public:
	CInput();
	~CInput();

	HRESULT InitKeyboard(HINSTANCE hInstance,HWND hWnd);
	void UninitKeyboard(void);
	void UpdateKeyboard(void);

	static bool GetKeyboardPress(int nKey);
	static bool GetKeyboardTrigger(int nKey);
	static bool GetKeyboardRelease(int nKey);
	static bool GetKeyboardRepeat(int nKey);

private:
	LPDIRECTINPUT8			g_pDInput;				//DirectInput�C���^�t�F�[�X�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard;	//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
	static BYTE				g_aKeyState[256];					//�L�[�{�[�h���

	static BYTE				g_aKeyStateTrigger[256];	//�L�[�g���K�[���
	static BYTE				g_aKeyStateRelease[256];	//�L�[�����[�X���
	static BYTE				g_aKeyStateRepeat[256];		//�L�[���s�[�g���
	static int				g_aKeyStateRepeatCount[256];		//���s�[�g�̃J�E���g

	CInput * m_pInput;
};

#endif