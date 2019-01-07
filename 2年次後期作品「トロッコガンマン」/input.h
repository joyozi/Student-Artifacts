//��-------------------------------------------------------------------------��
//
//	�w�b�_�[[input.h]
//	AT12A271�@�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _INPUT_H_

HRESULT InitKeyboard(HINSTANCE hInstance,HWND hWnd);

void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);
bool GetKeyboardRepeat(int nKey);

#define Repeat_Num (30)		//�L�[���s�[�g�̑҂�����

#endif