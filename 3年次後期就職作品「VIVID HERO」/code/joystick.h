//��-------------------------------------------------------------------------��
//
//	File	:	joystick�w�b�_�[�v���O����[joystick.h]
//	Auther	:	Ikezawa Shintaro
//
//��-------------------------------------------------------------------------��
#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include<Windows.h>
#include"d3dx9.h"

#define FPS_DIRECTX (60)

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

enum JoystickCrossKeyPov
{
	JCKP_UP = 0,
	JCKP_RIGHT_UP,
	JCKP_RIGHT,
	JCKP_RIGHT_DOWN,
	JCKP_DOWN,
	JCKP_LEFT_DOWN,
	JCKP_LEFT,
	JCKP_LEFT_UP,
	JCKP_MAX
};


enum JoystickCrossKey
{
	JCK_UP = 0,
	JCK_RIGHT_UP,
	JCK_RIGHT,
	JCK_RIGHT_DOWN,
	JCK_DOWN,
	JCK_LEFT_DOWN,
	JCK_LEFT,
	JCK_LEFT_UP,
	JCK_RUP,
	JCK_RRIGHT_UP,
	JCK_RRIGHT,
	JCK_RRIGHT_DOWN,
	JCK_RDOWN,
	JCK_RLEFT_DOWN,
	JCK_RLEFT,
	JCK_RLEFT_UP,
	JCK_MAX
};

enum JoyStickKey
{
	JS_X = 0,
	JS_A,
	JS_B,
	JS_Y,
	JS_LB,
	JS_RB,
	JS_LT,
	JS_RT,
	JS_BACK,
	JS_START,
	JS_L3,
	JS_R3,
	JS_MAX
};

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��
HRESULT InitJoystick(HINSTANCE hInstance, HWND hWnd);	// ����������
void UninitJoystick(void);	// �I������
void UpdateJoystick(void);	// �X�V����
bool GetJoystickPress(int nKey);	// �v���X�擾(0~127)
bool GetJoystickTrigger(int nKey);	// �g���K�[�擾(0~127)
bool GetJoystickRelease(int nKey);	// �����[�X�擾
bool GetJoystickRepeatTrigger(int nKey);	// ���s�[�g�g���K�[�擾
bool GetJoystickRepeatPress(int nKey);		// ���s�[�g�v���X�擾

bool GetJoystickCrossPov(JoystickCrossKeyPov nKey);

bool GetJoystickCrossPress(JoystickCrossKey nKey);
bool GetJoystickCrossTrigger(JoystickCrossKey nKey);	// �g���K�[�擾(0~127)
bool GetJoystickCrossRelease(JoystickCrossKey nKey);	// �����[�X�擾
bool GetJoystickCrossRepeatTrigger(JoystickCrossKey nKey);	// ���s�[�g�g���K�[�擾
bool GetJoystickCrossRepeatPress(JoystickCrossKey nKey);		// ���s�[�g�v���X�擾

float GetJoysticklX();
float GetJoysticklY();
float GetJoysticklZ();
float GetJoysticklRx();
float GetJoysticklRy();
float GetJoysticklRz();
float GetJoysticklARx();
float GetJoysticklARy();
float GetJoysticklARz();

float GetJoysticklFX();
float GetJoysticklFY();
float GetJoysticklFZ();

float GetJoysticklFRx();
float GetJoysticklFRy();
float GetJoysticklFRz();

#endif
//EOF